/*
** HDU 4744 Starloop System
** Created by Rayn @@ 2014/09/15
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#define sqr(x) ((x)*(x))
typedef long long LL;
typedef pair<int, int> PII;
const int MAXN = 210;
const int MAXM = MAXN*MAXN;
const int INF = 0x3F3F3F3F;

class ZKW_MCMF
{
private:
    struct Edge
    {
        int from, to, cap, cost;
        int next;
        Edge() {}
        Edge(int from, int to, int cap, int cost, int next):
            from(from), to(to), cap(cap), cost(cost), next(next) {}
    };

    int n, m;
    int source, sink;
    int head[MAXN];
    bool used[MAXN];
    int dis[MAXN];
    Edge edge[MAXM];

    void SPFA()
    {
        memset(dis, INF, sizeof(dis));
        priority_queue<PII> pq;
        dis[source] = 0;
        pq.push(make_pair(0, source));
        while(!pq.empty()) {
            int u = pq.top().second;
            int d = -pq.top().first;
            pq.pop();
            if(dis[u] != d) continue;
            for(int i = head[u]; i != -1; i = edge[i].next)
            {
                int& v = edge[i].to;
                if(edge[i].cap && dis[v] > d + edge[i].cost)
                {
                    dis[v] = d + edge[i].cost;
                    pq.push(make_pair(-dis[v], v));
                }
            }
        }
        for(int i = 0; i < n; ++i) {
            dis[i] = dis[sink] - dis[i];
        }
    }
    int AddFlow(int u, int f, int& cost, int& flow)
    {
        if(u == sink) {
            flow += f;
            cost += dis[source] * f;
            return f;
        }
        used[u] = true;
        int now = f;
        for(int i = head[u]; i != -1; i = edge[i].next)
        {
            int& v = edge[i].to;
            if(edge[i].cap && !used[v] && dis[u] == dis[v] + edge[i].cost)
            {
                int tmp = AddFlow(v, min(now, edge[i].cap), cost, flow);
                edge[i].cap -= tmp;
                edge[i^1].cap += tmp;
                now -= tmp;
                if(now == 0) break;
            }
        }
        return f - now;
    }
    bool ModifyLabel() {
        int d = INF;
        for(int u = 0; u < n; ++u) {
            if(!used[u]) continue;
            for(int i = head[u]; i != -1; i = edge[i].next)
            {
                int& v = edge[i].to;
                if(edge[i].cap && !used[v]) {
                    d = min(d, dis[v] + edge[i].cost - dis[u]);
                }
            }
        }
        if(d == INF) return false;
        for(int i = 0; i < n; ++i) {
            if(used[i]) {
                dis[i] += d;
            }
        }
        return true;
    }

public:
    void Init(int n)
    {
        this->n = n;
        this->m = 0;
        memset(head, -1, sizeof(head));
    }
    void AddEdge(int from, int to, int cap, int cost)
    {
        edge[m] = Edge(from, to, cap, cost, head[from]);
        head[from] = m++;
        edge[m] = Edge(to, from, 0, -cost, head[to]);
        head[to] = m++;
    }
    pair<int, int> MinCost(int s, int t)
    {
        this->source = s;
        this->sink = t;
        int flow = 0, cost = 0;
        SPFA();
        while(true) {
            while(true) {
                memset(used, false, sizeof(used));
                if(!AddFlow(source, INF, cost, flow)) break;
            }
            if(!ModifyLabel()) break;
        }
        return make_pair(cost, flow);
    }
};

template <typename T>
struct Point3
{
    T x, y, z;
    Point3() {}
    Point3(T x, T y, T z):
        x(x), y(y), z(z) {}
    void read() {
        cin >> x >> y >> z;
    }
    int Dist(const Point3& b) {
        int d = sqrt(sqr(x-b.x) + sqr(y-b.y) + sqr(z-b.z));
        return (int)floor(d);
    }
};

ZKW_MCMF Net;
Point3<double> star[MAXN];
int energy[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int N;
    while(scanf("%d", &N) != EOF && N)
    {
        int energy_sum = 0;
        for(int i = 1; i <= N; ++i) {
            star[i].read();
            scanf("%d", &energy[i]);
            energy_sum += energy[i];
        }
        int S = 0, T = N + N + 1;
        Net.Init(N+N+2);
        for(int i = 1; i <= N; ++i) {
            Net.AddEdge(S, i, energy[i], 0);
            Net.AddEdge(i+N, T, energy[i], 0);
            for(int j = i+1; j <= N; ++j) {
                int cost = star[i].Dist(star[j]);
                Net.AddEdge(i, j+N, INF, cost);
                Net.AddEdge(j, i+N, INF, cost);
            }
        }
        pair<int, int> res = Net.MinCost(S, T);
        int mincost = res.first;
        int maxflow = res.second;
        if(maxflow == energy_sum) {
            printf("%d\n", mincost);
        } else {
            printf("%d\n", -1);
        }
    }
    return 0;
}
