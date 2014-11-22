/*
** ZOJ 3659 Conquer a New Region
** Created by Rayn @@ 2014/09/09
*/
#include <cstdio>
#include <cmath>
#include <map>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 200010;

struct Edge
{
    int u, v, c;
    Edge() {}
    Edge(int u, int v, int c): u(u), v(v), c(c) {}
    bool operator < (const Edge& p) const {
        return c > p.c;
    }
};

vector<Edge> road;
int pa[MAXN], sz[MAXN];
LL value[MAXN];

void Init(int n)
{
    road.clear();
    for(int i = 0; i <= n; ++i) {
        pa[i] = i;
        sz[i] = 1;
        value[i] = 0;
    }
}
inline int FindSet(int x)
{
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF)
    {
        Init(n);
        for(int i = 0; i < n-1; ++i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            road.push_back(Edge(a, b, c));
        }
        sort(road.begin(), road.end());
        for(vector<Edge>::iterator it = road.begin(); it != road.end(); ++it) {
            int px = FindSet(it->u);
            int py = FindSet(it->v);
            LL v1 = value[px] + (LL)sz[py] * it->c;
            LL v2 = value[py] + (LL)sz[px] * it->c;
            if(v1 > v2) {
                pa[py] = px;
                sz[px] += sz[py];
                value[px] = v1;
            } else {
                pa[px] = py;
                sz[py] += sz[px];
                value[py] = v2;
            }
        }
        printf("%lld\n", value[FindSet(1)]);
    }
    return 0;
}
