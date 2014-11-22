/*
** HDU 3662 3D Convex Hull
** Created by Rayn @@ 2014/07/07
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <stdlib.h>
using namespace std;
const double EPS = 1e-8;
const int MAXN = 310;

struct Point3
{
    double x, y, z;
    Point3() {}
    Point3(double x, double y, double z): x(x), y(y), z(z) {}
};
typedef Point3 Vector3;
Vector3 operator + (const Vector3& A, const Vector3& B)
{
    return Vector3(A.x+B.x, A.y+B.y, A.z+B.z);
}
Vector3 operator - (const Vector3& A, const Vector3& B)
{
    return Vector3(A.x-B.x, A.y-B.y, A.z-B.z);
}
Vector3 operator * (const Vector3& A, const double& p)
{
    return Vector3(A.x*p, A.y*p, A.z*p);
}
Vector3 operator / (const Vector3& A, const double& p)
{
    return Vector3(A.x/p, A.y/p, A.z/p);
}

double Dot(const Vector3& A, const Vector3& B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}
double VectorLength(const Vector3& A)
{
    return sqrt(Dot(A, A));
}
Vector3 Cross(const Vector3& A, const Vector3& B)
{
    return Vector3(A.y*B.z-A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x);
}

struct Face
{
    int a, b, c;
    bool ok;
    Face() {}
    Face(int a, int b, int c, bool ok): a(a), b(b), c(c), ok(ok) {}
};

struct ConvexHull3D
{
    int n;
    int TriCnt;
    Point3 poly[MAXN];
    Face Tri[MAXN];
    int Belong[MAXN][MAXN]; //点i到j属于哪个面

    ConvexHull3D() {}
    ConvexHull3D(int n): n(n) {}

    double Area2(const Point3& A, const Point3& B, const Point3& C)
    {
        return VectorLength(Cross(B-A, C-A));
    }
    double Volume6(const Point3& A, const Point3& B, const Point3& C, const Point3& D)
    {
        return Dot(Cross(B-A, C-A), D-A);
    }
    double PointToPlane(const Point3& P, const Face& F)
    {
        Vector3 v1 = poly[F.b] - poly[F.a],
            v2 = poly[F.c] - poly[F.a],
            t = P - poly[F.a];
        return Dot(Cross(v1, v2), t);
    }
    void Deal(int p, int a, int b)
    {
        int f = Belong[a][b];
        Face add;
        if(Tri[f].ok)
        {
            if(PointToPlane(poly[p], Tri[f]) > EPS)
            {
                DFS(p, f);
            }
            else
            {
                add = Face(b, a, p, true);
                Belong[p][b] = Belong[a][p] = Belong[b][a] = TriCnt;
                Tri[TriCnt++] = add;
            }
        }
    }
    void DFS(int p, int cnt)
    {
        Tri[cnt].ok = false;
        Deal(p, Tri[cnt].b, Tri[cnt].a);
        Deal(p, Tri[cnt].c, Tri[cnt].b);
        Deal(p, Tri[cnt].a, Tri[cnt].c);
    }
    bool SameFace(int s, int e)
    {
        Point3 a = poly[Tri[s].a], b = poly[Tri[s].b], c = poly[Tri[s].c];
        return fabs(Volume6(a, b, c, poly[Tri[e].a])) < EPS
            && fabs(Volume6(a, b, c, poly[Tri[e].b])) < EPS
            && fabs(Volume6(a, b, c, poly[Tri[e].c])) < EPS;
    }
    void Construct()
    {
        TriCnt = 0;
        if(n < 4)
            return ;
        bool flag = true;
        for(int i = 1; i < n; ++i)
        {
            if(VectorLength(poly[0]-poly[i]) > EPS)
            {
                swap(poly[1], poly[i]);
                flag = false;
                break;
            }
        }
        if(flag)
            return ;
        flag = true;
        for(int i = 2; i < n; ++i)
        {
            if(VectorLength(Cross(poly[0]-poly[1], poly[1]-poly[i])) > EPS)
            {
                swap(poly[2], poly[i]);
                flag = false;
                break;
            }
        }
        if(flag)
            return ;
        flag = true;
        for(int i = 3; i < n; ++i)
        {
            if(fabs(Dot(Cross(poly[0]-poly[1], poly[1]-poly[2]), poly[0]-poly[i])) > EPS)
            {
                swap(poly[3], poly[i]);
                flag = false;
                break;
            }
        }
        if(flag)
            return ;
        Face add;
        for(int i = 0; i < 4; ++i)
        {
            add = Face((i+1)%4, (i+2)%4, (i+3)%4, true);
            if(PointToPlane(poly[i], add) > 0)
            {
                swap(add.b, add.c);
            }
            Belong[add.a][add.b] = Belong[add.b][add.c] = Belong[add.c][add.a] = TriCnt;
            Tri[TriCnt++] = add;
        }
        for(int i = 4; i < n; ++i)
        {
            for(int j = 0; j < TriCnt; ++j)
            {
                if(Tri[j].ok && PointToPlane(poly[i], Tri[j]) > EPS)
                {
                    DFS(i, j);
                    break;
                }
            }
        }
        int cnt = TriCnt;
        TriCnt = 0;
        for(int i = 0; i < cnt; ++i)
        {
            if(Tri[i].ok)
                Tri[TriCnt++] = Tri[i];
        }
    }
    double FaceArea()
    {
        double ans = 0;
        for(int i = 0; i < TriCnt; ++i)
        {
            ans += Area2(poly[Tri[i].a], poly[Tri[i].b], poly[Tri[i].c]);
        }
        return ans/2;
    }
    double TotalVolume()
    {
        Point3 p(0, 0, 0);
        double ans = 0;
        for(int i = 0; i < TriCnt; ++i)
        {
            ans += Volume6(p, poly[Tri[i].a], poly[Tri[i].b], poly[Tri[i].c]);
        }
        return fabs(ans/6);
    }
    int FaceTriCnt()
    {
        return TriCnt;
    }
    int FaceCnt()
    {
        int ans = 0;
        for(int i = 0; i < TriCnt; ++i)
        {
            int k = 1;
            for(int j = 0; j < i; ++j)
            {
                if(SameFace(i, j))
                {
                    k = 0;
                    break;
                }
            }
            ans += k;
        }
        return ans;
    }
};

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n;
    double x, y, z;
    while(scanf("%d", &n) != EOF && n)
    {
        ConvexHull3D hull(n);
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf%lf", &x, &y, &z);
            hull.poly[i] = Point3(x, y, z);
        }
        hull.Construct();
        printf("%d\n", hull.FaceCnt());
    }
    return 0;
}
