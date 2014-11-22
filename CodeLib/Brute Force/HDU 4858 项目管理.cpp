/*
** HDU 4858 项目管理
** Created by Rayn @@ 2014/08/22
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 100010;

int n, m, power[MAXN];
vector<int> edge[MAXN];
vector<int>::iterator it;

int getPower(int u)
{
    int ret = 0;
    for(it = edge[u].begin(); it != edge[u].end(); ++it) {
        ret += power[*it];
    }
    return ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        for(int i = 0; i <= n; ++i) {
            edge[i].clear();
            power[i] = 0;
        }
        for(int i = 0; i < m; ++i)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            edge[a].push_back(b);
            edge[b].push_back(a);
        }
        int Q;
        scanf("%d", &Q);
        while(Q--)
        {
            int op, u, v;
            scanf("%d", &op);
            if(op == 0) {
                scanf("%d%d", &u, &v);
                power[u] += v;
            } else if(op == 1) {
                scanf("%d", &u);
                printf("%d\n", getPower(u));
            }
        }
    }
    return 0;
}
