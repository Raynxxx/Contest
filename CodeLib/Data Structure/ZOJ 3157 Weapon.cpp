/*
** ZOJ 3157 Weapon
** Created by Rayn @@ 2014/08/02
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 10010;
const double EPS = 1e-8;

struct Point
{
    double x, y;

    Point() {}
    Point(double x, double y): x(x), y(y) {}

    void read() {
        scanf("%lf%lf", &x, &y);
    }
    void write() {
        printf("%.2f %.2f\n", x, y);
    }
};

struct Line
{
    int id;
    double yl, yr;
    Point a, b;

    Line() {}
    Line(Point a, Point b): a(a), b(b) {}

    void read() {
        a.read();
        b.read();
    }
    void gao(double l, double r) {
        double k = (b.y-a.y) / (b.x-a.x);
        yl = k * (l - a.x) + a.y;
        yr = k * (r - a.x) + a.y;
    }
    void setID(int id) {
        this->id = id;
    }
};

int n;
double l, r;
int cot[maxn];
int tree[maxn];
Line seg[maxn];

inline int LowBit(int x)
{
    return x & (-x);
}
void Update(int x, int val)
{
    while(x <= n) {
        tree[x] += val;
        x += LowBit(x);
    }
}
int Sum(int x)
{
    int res = 0;
    while(x > 0) {
        res += tree[x];
        x -= LowBit(x);
    }
    return res;
}
bool cmp1(const Line& a, const Line& b)
{
    if(fabs(a.yl - b.yl) >= EPS)
        return a.yl < b.yl;
    return a.yr < b.yr;
}
bool cmp2(const Line& a, const Line& b)
{
    if(fabs(a.yr - b.yr) >= EPS)
        return a.yr < b.yr;
    return a.yl < b.yl;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d", &n) != EOF)
    {
        for(int i = 1; i <= n; ++i) {
            seg[i].read();
        }
        scanf("%lf%lf", &l, &r);
        for(int i = 1; i <= n; ++i) {
            seg[i].gao(l, r);
        }
        sort(seg+1, seg+n+1, cmp1);
        for(int i = 1; i <= n; ++i) {
            seg[i].setID(i);
        }
        sort(seg+1, seg+n+1, cmp2);
        for(int i = 1; i <= n; ++i) {
            cot[seg[i].id] = i;
            //printf("%d\n", seg[i].id);
        }
        int res = 0;
        memset(tree, 0, sizeof(tree));
        for(int i = 1; i <= n; ++i) {
            Update(cot[i], 1);
            res += i - Sum(cot[i]);
        }
        printf("%d\n", res);
    }
    return 0;
}
