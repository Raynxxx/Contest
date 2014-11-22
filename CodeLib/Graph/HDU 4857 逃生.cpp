/*
** HDU 4857 逃生
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
const int MAXN = 30010;

int n, m, res[MAXN];
int cnt, degree[MAXN];
vector<int> g[MAXN];
vector<int>::iterator it;

void gao()
{
    priority_queue<int> pq;
    for(int i = 1; i <= n; ++i) {
        if(degree[i] == 0) {
            pq.push(i);
        }
    }
    while(!pq.empty())
    {
        int u = pq.top();
        pq.pop();
        for(it = g[u].begin(); it != g[u].end(); ++it)
        {
            degree[*it]--;
            if(degree[*it] == 0) {
                pq.push(*it);
            }
        }
        res[cnt++] = u;
    }
    for(int i = cnt-1; i >= 0; --i)
    {
        printf("%d%c", res[i], (i == 0 ? '\n' : ' '));
    }
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
            g[i].clear();
            degree[i] = 0;
        }
        for(int i = 0; i < m; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g[v].push_back(u);
            degree[u]++;
        }
        cnt = 0;
        gao();
    }
    return 0;
}
