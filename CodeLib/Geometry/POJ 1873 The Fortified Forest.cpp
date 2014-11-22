/*
** POJ 1873 The Fortified Forest
** Created by Rayn @@ 2014/06/05
*/
///*
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int MAX = 30;
const double INF = 1e18;

struct Point {
    double x, y, val, len;
    Point() {}
    Point(double x, double y, double val, double len) :
        x(x), y(y), val(val), len(len) {}
    void Print()
    {
        printf("%.1f  %.1f\n", x, y);
    }
} left[MAX], tree[MAX], tubao[MAX], base;

int dcmp(double x)
{
    if(x < EPS)
        return 0;
    else
        return (x < 0)? -1 : 1;
}
double Cross(Point p0, Point p1, Point p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y) - (p1.y-p0.y)*(p2.x-p0.x);
}
double Dis(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
bool cmp1(const Point& a, const Point& b)
{
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}
/*
//另外一种凸包求法
bool cmp2(Point a, Point b)
{
    //极角排序
    double res = Cross(base, a, b);
    if(dcmp(res) > 0)
        return true;
    else if(dcmp(res) == 0 && dcmp(Dis(a, base) - Dis(b, base)) < 0)
        return true;
    else
        return false;
}
double GrahamScan(Point *p, int n, Point *ch)
{
    base = p[0];
    int id = 0;
    for(int i = 0; i < n; ++i)
    {
        if(cmp1(p[i], base))
        {
            base = p[i];
            id = i;
        }
    }
    swap(p[id], p[0]);
    sort(p+1, p+n, cmp2);
    ch[0] = p[0];
    int k = 1, pos = 0;
    while(k < n)
    {
        while(pos > 0 && Cross(ch[pos-1], p[k], ch[pos]) >= 0)
            pos--;
        ch[++pos] = p[k++];
    }
    pos++;
    double len = 0.0;
    for(int i = 0; i < pos; i++)
    {
        //ch[i].Print();
        len += Dis(ch[i], ch[(i+1)%pos]);
    }
    return len;
}
////**/
double ConvexHull(Point *p, int n, Point *ch)
{
    sort(p, p+n, cmp1);
    int m = 0;
    for(int i = 0; i < n; ++i)
    {
        while(m > 1 && Cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; i--)
    {
        while(m > k && Cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    if(n > 1)
        m--;
    double len = 0.0;
    for(int i = 0; i < m; i++)
    {
        //ch[i].Print();
        len += Dis(ch[i], ch[(i+1)%m]);
    }
    return len;
}
//*/
int main()
{
    int n, cases = 0;
    double x, y, val, len;

    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf%lf%lf", &x, &y, &val, &len);
            tree[i] = Point(x, y, val, len);
        }

        double minval = INF;
        double tubaolen, cutlen, cutval;
        double best_tubaolen, best_cutlen;

        int ans[MAX], ansCnt, leftCnt;
        for(int i = 1; i < (1 << n); ++i)
        {
            cutlen = cutval = 0.0;
            leftCnt = 0;
            for(int j = 0; j < n; ++j)
            {
                if((1 << j) & i)
                {
                    cutlen += tree[j].len;
                    cutval += tree[j].val;
                }
                else
                {
                    left[leftCnt++] = tree[j];
                }
            }
            if(cutval > minval)
                continue;
            tubaolen = ConvexHull(left, leftCnt, tubao);
            //tubaolen = GrahamScan(left, leftCnt, tubao);
            //printf("tubaolen : %.2f\n", tubaolen);
            if(tubaolen <= cutlen && cutval < minval)
            {
                minval = cutval;
                best_cutlen = cutlen;
                best_tubaolen = tubaolen;
                ansCnt = 0;
                for(int j = 0; j < n; ++j)
                {
                    if((1 << j) & i)
                        ans[ansCnt++] = j + 1;
                }
            }
            //printf("%d\n", ansCnt);
            //printf("%.2f %.2f\n", cutlen, cutval);
        }
        printf("Forest %d\n", ++cases);
        printf("Cut these trees: ");
        //printf("%d\n", ansCnt);
        for(int i = 0; i < ansCnt; ++i)
        {
            printf("%d%c", ans[i], (i != ansCnt-1)? ' ':'\n');
        }
        printf("Extra wood: %.2f\n\n", best_cutlen - best_tubaolen);
    }
    return 0;
}
