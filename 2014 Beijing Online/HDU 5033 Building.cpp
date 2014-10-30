/*
** HDU 5033 Building
** Created by Rayn @@ 2014/09/22
*/
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 100005;
const double EPS = 1e-8;
const double INF = 1e10;
const double PI = acos(-1.0);

struct Node
{
    int x, h;
    Node() {}
    Node(int x, int h): x(x), h(h) {}
    bool operator < (const Node& rhs) const {
        return x < rhs.x;
    }
};

int n, q;
Node build[MAXN];
Node matt[MAXN];
Node que[MAXN];
double res[MAXN];

inline double get(Node A, Node B)
{
    return ((double)A.h*B.x - (double)B.h*A.x) / (A.h - B.h);
}
void Gao(int flag)
{
    if(!flag) {
        for(int i = 1; i <= n; ++i) build[i].x *= -1;
        for(int i = 1; i <= q; ++i) matt[i].x *= -1;
    }
    sort(build + 1, build + 1 + n);
    sort(matt + 1, matt + 1 + q);
    int head = 1, tail = 0;
    for(int i = 1, j = 1; i <= q; ++i) {
        while(j <= n && build[j].x < matt[i].x) {
            while(tail - head + 1 >= 1 && build[j].h >= que[tail].h) {
                --tail;
            }
            while(tail - head + 1 >= 2 && get(que[tail], build[j]) >= get(que[tail-1], que[tail])) {
                --tail;
            }
            que[++tail] = build[j++];
        }
        while(tail - head + 1 >= 2 && get(que[tail-1], que[tail]) < matt[i].x) {
            --tail;
        }
        res[matt[i].h] += atan((double)(matt[i].x - que[tail].x) / que[tail].h);
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d%d", &build[i].x, &build[i].h);
        }
        scanf("%d", &q);
        fill(res, res + 1 + q, 0);
        for(int i = 1; i <= q; ++i) {
            scanf("%d", &matt[i].x);
            matt[i].h = i;
        }
        Gao(1);
        Gao(0);
        printf("Case #%d:\n", ++cases);
        for(int i = 1; i <= q; ++i) {
            printf("%.10f\n", res[i] * 180.0 / PI);
        }
    }
    return 0;
}
