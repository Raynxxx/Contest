/*
** HDU 4460 Friend Chains
** Created by Rayn @@ 2014/07/17
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 1010;
const int MAXM = 20010;
const int INF = 0x3F3F3F3F;

struct Edge
{
    int from, to, dist;
    int next;
    Edge() {}
    Edge(int from, int to, int dist, int next):
        from(from), to(to), dist(dist), next(next) {}
};

map<string, int> mp;
Edge edge[MAXM];
int sz, head[MAXN];
int dis[MAXN][MAXN];
bool vis[MAXN];

void Init()
{
    mp.clear();
    sz = 0;
    memset(head, -1, sizeof(head));
    memset(dis, INF, sizeof(dis));
}
void AddEdge(int from, int to, int dist)
{
    edge[sz] = Edge(from, to, dist, head[from]);
    head[from] = sz++;
}
void BFS(int s)
{
    memset(vis, false, sizeof(vis));
    queue<int> que;
    que.push(s);
    vis[s] = true;
    dis[s][s] = 0;
    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(dis[s][v] > dis[s][u] + edge[i].dist)
            {
                dis[s][v] = dis[s][u] + edge[i].dist;
                if(!vis[v])
                {
                    vis[v] = true;
                    que.push(v);
                }
            }

        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int n, m;
    char name[20], s1[20], s2[20];
    while(scanf("%d", &n) != EOF && n)
    {
        Init();
        for(int i = 0; i < n; ++i)
        {
            scanf("%s", name);
            mp[name] = i;
        }
        scanf("%d", &m);
        for(int i = 0; i < m; i++)
        {
            scanf("%s%s", s1, s2);
            AddEdge(mp[s1], mp[s2], 1);
            AddEdge(mp[s2], mp[s1], 1);
        }
        for(int i = 0; i < n; i++)
        {
            BFS(i);
        }
        int res = 0;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                res = max(res, dis[i][j]);
            }
        }
        if (res == INF)
        {
            printf("-1\n");
        }
        else
        {
            printf("%d\n", res);
        }
    }
    return 0;
}
