/*
** HDU 4885 TIANKENG's travel
** Created by Rayn @@ 2014/07/27
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
const int MAXN = 1010;
const int INF = 0x3F3F3F3F;
typedef pair<int, int> PII;
typedef long long LL;

struct Point
{
    int x, y;
    int id;
    Point() {}
    Point(int x, int y, int id):
        x(x), y(y), id(id) {}
    void Read(int id)
    {
        scanf("%d%d", &x, &y);
        this->id = id;
    }
    bool operator < (const Point& rhs) const
    {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

struct Edge
{
    int from, to, next;
    Edge() {}
    Edge(int from, int to, int next):
        from(from), to(to), next(next) {}
};


int L, sz;
int head[MAXN];
int dis[MAXN];
Point p[MAXN];
Edge edge[MAXN*MAXN];

bool Distance(Point a, Point b)
{
    LL dis = (LL)(a.x-b.x)*(a.x-b.x) + (LL)(a.y-b.y)*(a.y-b.y);
    if(dis <= (LL)L*L)
        return true;
    return false;
}
void Init()
{
    sz = 0;
    memset(head, -1, sizeof(head));
    memset(edge, 0, sizeof(edge));
}
void AddEdge(int from, int to)
{
    edge[sz] = Edge(from, to, head[from]);
    head[from] = sz++;
}
int SPFA(int s, int e)
{
    memset(dis, INF, sizeof(dis));
    queue<int> que;
    dis[s] = 0;
    que.push(s);
    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        for(int i = head[u]; i != -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(dis[v] > dis[u] + 1)
            {
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
    }
    return dis[e];
}
int main()
{
    int T, n;

    scanf("%d", &T);
    while(T--)
    {
        Init();
        scanf("%d%d", &n, &L);
        p[0].Read(0);
        p[n+1].Read(n+1);
        for(int i = 1; i <= n; ++i)
        {
            p[i].Read(i);
        }
        sort(p, p+n+2);
        for(int i = 0; i <= n+1; ++i)
        {
            set<PII> st;
            for(int j = i+1; j <= n+1; ++j)
            {
                if(Distance(p[i], p[j]))
                {
                    int x = p[j].x - p[i].x;
                    int y = p[j].y - p[i].y;
                    int d = __gcd(x, y);
                    if(d < 0) d = -d;
                    x /= d;
                    y /= d;
                    if(st.count(make_pair(x, y)))
                        continue;
                    st.insert(make_pair(x, y));
                    AddEdge(i, j);
                    AddEdge(j, i);
                }
            }
        }
        int s, e;
        for(int i = 0; i <= n+1; ++i)
        {
            if(p[i].id == 0)
                s = i;
            if(p[i].id == n+1)
                e = i;
        }
        int ans = SPFA(s, e);
        if(ans >= INF)
        {
            printf("impossible\n");
        }
        else
        {
            printf("%d\n", ans-1);
        }
    }
    return 0;
}
