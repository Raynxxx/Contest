/*
** ZOJ 3650 Toy Blocks
** Created by Rayn @@ 2014/08/01
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 110000;
const int INF = 0x7FFFFFFF;

int n, m;
int x[MAXN], h[MAXN];
int gl[MAXN], gr[MAXN];
int dp[MAXN];
map<int, int> mp;

template <class T> void checkmax(T& t, T x)
{
    if(x > t) t = x;
}
template <class T> void checkmin(T& t, T x)
{
    if(x < t) t = x;
}

struct SegTree
{
    struct Node
    {
        int l, r;
        int maxv, minv, tag;
    };

    Node tree[MAXN<<2];

    void PushDown(int rt)
    {
        if(tree[rt].tag != INF)
        {
            checkmin(tree[rt].minv, tree[rt].tag);
            if(tree[rt].l != tree[rt].r)
            {
                checkmin(tree[rt<<1].tag, tree[rt].tag);
                checkmin(tree[rt<<1|1].tag, tree[rt].tag);
            }
            tree[rt].tag = INF;
        }
    }
    void Update(int rt)
    {
        PushDown(rt<<1);
        PushDown(rt<<1|1);
        if(tree[rt].l != tree[rt].r)
        {
            tree[rt].maxv = max(tree[rt<<1].maxv, tree[rt<<1|1].maxv);
            tree[rt].minv = min(tree[rt<<1].minv, tree[rt<<1|1].minv);
        }
    }
    void Build(int rt, int l, int r, int w)
    {
        tree[rt].l = l;
        tree[rt].r = r;
        tree[rt].maxv = tree[rt].minv = w;
        tree[rt].tag = INF;
        if(l == r)
        {
            return ;
        }
        int mid = (l + r) >> 1;
        Build(rt<<1, l, mid, w);
        Build(rt<<1|1, mid+1, r, w);
    }
    void Set(int rt, int x, int w)
    {
        PushDown(rt);
        if(tree[rt].l == tree[rt].r)
        {
            tree[rt].maxv = tree[rt].minv = w;
            return ;
        }
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(x <= mid)
            Set(rt<<1, x, w);
        else
            Set(rt<<1|1, x, w);
        Update(rt);
    }
    void PushMin(int rt, int x, int y, int w)
    {
        PushDown(rt);
        if(x <= tree[rt].l && tree[rt].r <= y)
        {
            checkmin(tree[rt].tag, w);
            return ;
        }
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(x <= mid)
            PushMin(rt<<1, x, y, w);
        if(mid < y)
            PushMin(rt<<1|1, x, y, w);
        Update(rt);
    }
    int getMax(int rt, int x, int y)
    {
        PushDown(rt);
        if(x <= tree[rt].l && tree[rt].r <= y)
        {
            return tree[rt].maxv;
        }
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        int ret = -INF;
        if(x <= mid)
            checkmax(ret, getMax(rt<<1, x, y));
        if(mid < y)
            checkmax(ret, getMax(rt<<1|1, x, y));
        Update(rt);
        return ret;
    }
    int getMin(int rt, int x, int y)
    {
        PushDown(rt);
        if(x <= tree[rt].l && tree[rt].r <= y)
        {
            return tree[rt].minv;
        }
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        int ret = INF;
        if(x <= mid)
            checkmin(ret, getMin(rt<<1, x, y));
        if(mid < y)
            checkmin(ret, getMin(rt<<1|1, x, y));
        Update(rt);
        return ret;
    }
};

SegTree Solver;

void Gao()
{
    Solver.Build(1, 0, m-1, INF);
    for(int i = 0; i < m; ++i)
    {
        if(gl[i] == 0)
        {
            Solver.PushMin(1, i, i, 1);
        }
        else
        {
            Solver.PushMin(1, i, i, Solver.getMin(1, gl[i]-1, i-1)+1);
        }
        int pre = i ? dp[i-1] : 0;
        Solver.PushMin(1, i, gr[i], pre+1);
        dp[i] = Solver.getMin(1, i, i);
    }
    printf("%d\n", dp[m-1]);
}

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d", &n) != EOF)
    {
        mp.clear();
        for(int i = 0, xx, hh; i < n; ++i)
        {
            scanf("%d%d", &xx, &hh);
            checkmax(mp[xx], hh);
        }
        m = 0;
        map<int, int>::iterator it;
        for(it = mp.begin(); it != mp.end(); ++it)
        {
            x[m] = it->first;
            h[m++] = it->second;
        }
        gl[0] = 0;
        for(int i = 1; i < m; ++i)
        {
            int l = 0, r = i;
            while(l < r)
            {
                int mid = (l + r) >> 1;
                if(x[i] - x[mid] <= h[i])
                    r = mid;
                else
                    l = mid + 1;
            }
            gl[i] = l;
        }
        Solver.Build(1, 0, m-1, 0);
        for(int i = 0; i < m; ++i)
        {
            Solver.Set(1, i, gl[i]);
            gl[i] = Solver.getMin(1, gl[i], i);
            Solver.Set(1, i, gl[i]);
        }
        gr[m-1] = m-1;
        for(int i = m-2; i >= 0; --i)
        {
            int l = i, r = m-1;
            while(l < r)
            {
                int mid = (l + r + 1) >> 1;
                if(x[mid] - x[i] <= h[i])
                    l = mid;
                else
                    r = mid - 1;
            }
            gr[i] = l;
        }
        Solver.Build(1, 0, m-1, 0);
        for(int i = m-1; i >= 0; --i)
        {
            Solver.Set(1, i, gr[i]);
            gr[i] = Solver.getMax(1, i, gr[i]);
            Solver.Set(1, i, gr[i]);
        }
        Gao();
    }
    return 0;
}
