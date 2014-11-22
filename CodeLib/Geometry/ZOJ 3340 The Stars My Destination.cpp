/*
** ZOJ 3340 The Stars My Destination
** Created by Rayn @@ 2014/08/06
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const double INF = 1e20;
struct Point3
{
    double x, y, z;
    Point3() {}
    Point3(double x, double y, double z):
        x(x), y(y), z(z) {}

    void read()
    {
        scanf("%lf%lf%lf", &x, &y, &z);
    }
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
double Dot(const Vector3& A, const Vector3& B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}
double Length(const Vector3& A)
{
    return sqrt(Dot(A, A));
}
Vector3 Cross(const Vector3& A, const Vector3& B)
{
    return Vector3(A.y*B.z-A.z*B.y, A.z*B.x-A.x*B.z, A.x*B.y-A.y*B.x);
}
double DisToLine(Point3 P, Point3 A, Point3 B)
{
    Vector3 v1 = B-A, v2 = P-A;
    return Length(Cross(v1, v2)) / Length(v1);
}
double Distance(Point3 A, Point3 B)
{
    return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y) + (A.z-B.z)*(A.z-B.z));
}
bool Judge(Point3 P, Vector3 A, Vector3 B)
{
    if(Dot(B-A, P-A) < 0)
        return false;
    return true;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    Point3 s1, s2, aster;

    while(scanf("%d", &n) != EOF)
    {
        s1.read();
        s2.read();
        double MaxDis = -INF, d;
        for(int i = 0; i < n; ++i)
        {
            aster.read();
            if(Judge(aster, s1, s2))
            {
                d = DisToLine(aster, s1, s2);
                if(d > MaxDis)
                    MaxDis = d;
            }
            else
            {
                d = Distance(aster, s1);
                if(d > MaxDis)
                    MaxDis = d;
            }
        }
        printf("%.2f\n", MaxDis);
    }
    return 0;
}
