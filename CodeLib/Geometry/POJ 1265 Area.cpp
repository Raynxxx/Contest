/*
** POJ 1265 Area
** Created by Rayn @@ 2014/06/10

** ����Ŀ���⡿
** ��һ��ƽ���ϵļ򵥶���Σ�����ϵĵ㣬���
** ���ڵĵ㣬����������

** ������˼·��
** 1���Ը��ӵ�Ϊ������߶Σ����ǵĵ�ĸ���
** ΪGCD(dx,dy)������dx dy�ֱ�Ϊ�߶κ���ռ
** �ĵ���������ռ�ĵ��������dx��dyΪ0����
** ���ǵĵ���Ϊdy��dx��

** 2��Pick��ʽ��ƽ�����Ը��ӵ�Ϊ����ļ�
** ����ε����=���ϵĵ���/2+�ڲ��ĵ���-1.

** 3������һ������ε�������ڰ�˳��������
** ��������ԭ����ɵ������Ĳ��֮�͡�
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
typedef long long LL;
const int MAX = 110;
char str[MAX];

struct Point {
    int x, y;
    Point(int x=0, int y=0) :
        x(x), y(y) {}
} po[MAX];
typedef Point Vector;

Vector operator - (const Point& a, const Point& b) {
    return Point(a.x-b.x, a.y-b.y);
}
int IntAbs(int x)
{
    return (x > 0)? x : -x;
}
int gcd(int m, int n)
{
    return (n == 0)? m : gcd(n, m%n);
}
double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
double Area2(Point A, Point B, Point C)
{
    return Cross(B-A, C-A);
}
int main()
{
    int t, m, dx, dy;
    int cases = 0, first = 1;

    scanf("%d", &t);
    while(t--)
    {
        if(!first)
            printf("\n");
        first = 0;
        scanf("%d", &m);
        Point now(0, 0);
        po[0] = now;

        int EdgeP = 0;
        double Area = 0.0;
        for(int i = 1; i <= m; ++i)
        {
            scanf("%d%d", &dx, &dy);
            now.x += dx;
            now.y += dy;
            po[i] = now;
            EdgeP += gcd(IntAbs(dx), IntAbs(dy));
            Area += Area2(po[0], po[i], po[i-1]);
        }
        Area = fabs(Area) / 2;
        int InsideP = Area - EdgeP / 2 + 1;

        printf("Scenario #%d:\n", ++cases);
        printf("%d %d %.1f\n", InsideP, EdgeP, Area);
    }
    return 0;
}
