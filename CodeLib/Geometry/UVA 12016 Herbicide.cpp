/*
** UVA 12016 Herbicide
** Created by Rayn @@ 2014/07/18
*/
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 1010;

struct Point
{
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B)
{
    return Vector(A.x+B.x, A.y+B.y);
}
Vector operator - (const Vector& A, const Vector& B)
{
    return Vector(A.x-B.x, A.y-B.y);
}

int Dot(const Vector& A, const Vector& B)
{
    return A.x*B.x + A.y*B.y;
}
int Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
}

struct Polygon
{
    int n;
    int left, right, bottom, top;
    int vertex[MAXN];
    Point p[MAXN];

    void Init()
    {
        left = right = bottom = top = 0;
    }
    bool InRectBox(const Point& pt)
    {
        return (left <= pt.x && pt.x <= right) &&
            (bottom <= pt.y && pt.y <= top);
    }
};

Point weed[MAXN];
Polygon Herbicide[MAXN];
int weedCnt, PolyCnt;


bool OnSegment(const Point& pt, const Point& A, const Point& B)
{
    return Cross(A-pt, B-pt) == 0 && Dot(A-pt, B-pt) <= 0;
}
bool IsPointInPolygon(const Point& pt, const Polygon& poly)
{
    int CrossNumber = 0;
    for(int i = 0; i < poly.n; ++i)
    {
        int j = (i + 1) % poly.n;
        if((poly.p[i].y <= pt.y && pt.y <= poly.p[j].y) ||
           (poly.p[j].y <= pt.y && pt.y <= poly.p[i].y))
        {
            int c = Cross(poly.p[i]-poly.p[j], pt-poly.p[j]);
            if(c == 0 && ((poly.p[i].x <= pt.x && pt.x <= poly.p[j].x) ||
               (poly.p[j].x <= pt.x && pt.x <= poly.p[i].x)))
            {
                return true;
            }
            if((c > 0 && poly.p[i].y > poly.p[j].y && pt.y != poly.p[i].y) ||
               (c < 0 && poly.p[i].y < poly.p[j].y && pt.y != poly.p[j].y))
            {
                CrossNumber++;
            }
        }
    }
    return (CrossNumber & 1);
}
int CountWeed(Polygon& poly)
{
    int cnt = 0;
    for(int i = 0; i < poly.n+1; ++i)
    {
        for(int j = poly.vertex[i]+1; j <= poly.vertex[i+1]-1; ++j)
        {
            if(poly.InRectBox(weed[j]))
            {
                if(IsPointInPolygon(weed[j], poly))
                    cnt++;
            }
        }
    }
    return cnt + poly.n;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int t, n, cases = 0;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &weedCnt);
        for(int i = 1; i <= weedCnt; ++i)
        {
            scanf("%d%d", &weed[i].x, &weed[i].y);
        }
        scanf("%d", &PolyCnt);
        for(int i = 0; i < PolyCnt; ++i)
        {
            Herbicide[i].Init();
            scanf("%d", &n);

            Herbicide[i].n = n;
            for(int j = 0; j < n; ++j)
            {
                int index;
                scanf("%d", &index);
                Herbicide[i].p[j] = weed[index];
                Herbicide[i].vertex[j+1] = index;

                if(Herbicide[i].top < weed[index].y)
					Herbicide[i].top = weed[index].y;
				if(Herbicide[i].left > weed[index].x)
					Herbicide[i].left = weed[index].x;
				if(Herbicide[i].bottom > weed[index].y)
					Herbicide[i].bottom = weed[index].y;
				if(Herbicide[i].right < weed[index].x)
					Herbicide[i].right = weed[index].x;
            }
            Herbicide[i].vertex[0] = 0;
            Herbicide[i].vertex[n+1] = weedCnt + 1;
            sort(Herbicide[i].vertex, Herbicide[i].vertex+n+1);
        }
        printf("Case #%d:\n", ++cases);
        for(int i = 0; i < PolyCnt; ++i)
        {
            printf("%d\n", CountWeed(Herbicide[i]));
        }
    }
	return 0;
}
