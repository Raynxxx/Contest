/*
** HDU 2066 一个人的旅行
** Created by Rayn @@ 2014/06/30
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 160;
const int INF = 0x3F3F3F3F;

struct Edge
{
    int from, to, time;
    Edge(int u=0, int v=0, int t=0): from(u), to(v), time(t) {}
};
struct HeapNode
{
    int u, time;
    HeapNode(int u=0, int t=0): u(u), time(t) {}
    bool operator < (const HeapNode& rhs) const
    {
        return time > rhs.time;
    }
};

vector<Edge> edge;
vector<int> G[MAXN];
map<string, int> mp;
int V, E;
bool vis[MAXN];
int dis[MAXN];
int Sarr[MAXN], Darr[MAXN];

void Init(int n)
{
    for(int i = 0; i < n; ++i)
        G[i].clear();
    edge.clear();
    mp.clear();
}
void AddEdge(int from, int to, int time)
{
    edge.push_back(Edge(from, to, time));
    E = edge.size();
    G[from].push_back(E-1);
}
void Dijkstra(int s)
{
    memset(vis, false, sizeof(vis));
    for(int i = 0; i < V; ++i)
    {
        dis[i] = (i == s)? 0 : INF;
    }
    priority_queue<HeapNode> q;
    q.push(HeapNode(s, 0));
    while(!q.empty())
    {
        HeapNode now = q.top(); q.pop();
        int u = now.u;
        if(vis[u])
            continue;
        vis[u] = true;
        for(int i = 0; i < G[u].size(); ++i)
        {
            Edge& e = edge[G[u][i]];
            if(dis[e.to] > dis[u] + e.time)
            {
                dis[e.to] = dis[u] + e.time;
                q.push(HeapNode(e.to, dis[e.to]));
            }
        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    char Start[35], End[35], s[35], e[35];
    int n, time, flag;

    while(scanf("%d", &n) != EOF && n != -1)
    {
        Init(MAXN);
        flag = 0;
        scanf("%s%s", Start, End);
        if(strcmp(Start, End) == 0)
            flag = 1;

        int cnt = 0;
        mp.insert(make_pair(Start, cnt++));
        for(int i = 0; i < n; ++i)
        {
            scanf("%s%s%d", s, e, &time);
            if(!mp.count(s))
                mp.insert(make_pair(s, cnt++));
            if(!mp.count(e))
                mp.insert(make_pair(e, cnt++));
            AddEdge(mp[s], mp[e], time);
            AddEdge(mp[e], mp[s], time);
        }
        if(!mp.count(End))
            mp.insert(make_pair(End, cnt++));
        if(flag == 1)
        {
            printf("0\n");
            continue;
        }
        V = cnt + 1;
        Dijkstra(mp[Start]);
        printf("%d\n", (dis[mp[End]] == INF)? -1 : dis[mp[End]]);
    }
    return 0;
}
