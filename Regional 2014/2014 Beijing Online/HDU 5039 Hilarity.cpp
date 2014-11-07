/*
** HDU 5039 Hilarity
** Created by Rayn @@ 2014/09/23
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <bitset>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define lson (rt<<1)
#define rson (rt<<1|1)
typedef long long LL;

inline int nextInt()
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    int ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    if(flag) ret = -ret;
    return ret;
}

const int MAXN = 30010;
const int MAXM = MAXN * 2;

struct Edge {
    int v, color, next;
    Edge() {}
    Edge(int v, int color, int next):
        v(v), color(color), next(next) {}
};

Edge edge[MAXM];
int sz, head[MAXN];
int tsz, in[MAXN], out[MAXN], col[MAXN];
map<string, int> city_name;

void AddEdge(int u, int v, int color)
{
    edge[sz] = Edge(v, color, head[u]);
    head[u] = sz++;
    edge[sz] = Edge(u, color, head[v]);
    head[v] = sz++;
}
void dfs(int u, int pa, int c)
{
    for(int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if(v == pa) continue;
        in[i/2] = ++tsz;
        col[tsz] = c ^ edge[i].color;
        dfs(v, u, c ^ edge[i].color);
        out[i/2] = tsz;
    }
}
struct SegmentTree
{
    int sum[MAXN<<2];
    int flip[MAXN<<2];

    inline void PushUp(int rt)
    {
        sum[rt] = sum[lson] + sum[rson];
    }
    inline void PushDown(int rt, int l, int r)
    {
        if(flip[rt]) {
            flip[lson] ^= 1;
            flip[rson] ^= 1;
            int mid = (l + r) >> 1;
            sum[lson] = (mid - l + 1) - sum[lson];
            sum[rson] = (r - mid) - sum[rson];
            flip[rt] = 0;
        }
    }
    void Build(int rt, int l, int r)
    {
        flip[rt] = 0;
        if(l == r) {
            sum[rt] = col[l];
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid);
        Build(rson, mid+1, r);
        PushUp(rt);
    }
    void Update(int rt, int l, int r, int x, int y)
    {
        if(x <= l && r <= y) {
            flip[rt] ^= 1;
            sum[rt] = (r - l + 1) - sum[rt];
            return ;
        }
        int mid = (l + r) >> 1;
        PushDown(rt, l, r);
        if(x <= mid)
            Update(lson, l, mid, x, y);
        if(mid < y)
            Update(rson, mid+1, r, x, y);
        PushUp(rt);
    }
};


SegmentTree st;

void Init(int n)
{
    city_name.clear();
    sz = tsz = 0;
    memset(head, -1, sizeof(int)*(n+2));
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    char buf[20];
    T = nextInt();
    while(T--)
    {
        int n = nextInt();
        Init(n);
        for(int i = 1; i <= n; ++i) {
            scanf("%s", buf);
            city_name[string(buf)] = i;
        }
        for(int i = 1; i <= n-1; ++i) {
            int u, v, s;
            scanf("%s", buf);
            u = city_name[string(buf)];
            scanf("%s", buf);
            v = city_name[string(buf)];
            scanf("%d", &s);
            AddEdge(u, v, s);
        }
        dfs(1, -1, 0);
        st.Build(1, 1, tsz);
        int m = nextInt();
        printf("Case #%d:\n", ++cases);
        while(m--) {
            scanf("%s", buf);
            if(buf[0] == 'M') {
                int i = nextInt();
                st.Update(1, 1, tsz, in[i-1], out[i-1]);
            } else if(buf[0] == 'Q') {
                LL x = st.sum[1];
                printf("%I64d\n", x * (n - x) * 2);
            }
        }
    }
    return 0;
}
