/*
** ZOJ 3381 Osaisen Choudai!
** Created by Rayn @@ 2014/08/28
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int INF = 0x3F3F3F3F;
const int MAXN = 50005;

struct SegmentTree
{
    struct SegNode
    {
        int left, right;
        long long val;
        SegNode() {}
        SegNode(int l, int r, long long v):
            left(l), right(r), val(v) {}
        int getMid() {
            return (left + right) >> 1;
        }
    };
    SegNode tree[MAXN<<2];

    inline void BuildTree(int rt, int l, int r)
    {
        tree[rt] = SegNode(l, r, 0);
        if(l == r) {
            return ;
        }
        int mid = (l + r) >> 1;
        BuildTree(rt<<1, l, mid);
        BuildTree(rt<<1|1, mid+1, r);
    }
    inline void PushUp(int rt)
    {
        tree[rt].val = max(tree[rt<<1].val, tree[rt<<1|1].val);
    }
    inline void Update(int rt, int l, int r, LL val)
    {
        if(l <= tree[rt].left && tree[rt].right <= r)
        {
            tree[rt].val = max(tree[rt].val, val);
            return ;
        }
        int mid = tree[rt].getMid();
        if(l <= mid)
            Update(rt<<1, l, r, val);
        if(r > mid)
            Update(rt<<1|1, l, r, val);
        PushUp(rt);
    }
    inline LL getMax(int rt, int l, int r)
    {
        if(l <= tree[rt].left && tree[rt].right <= r)
        {
            return tree[rt].val;
        }
        LL ret = 0;
        int mid = tree[rt].getMid();
        if(l <= mid)
            ret = max(ret, getMax(rt<<1, l, r));
        if(r > mid)
            ret = max(ret, getMax(rt<<1|1, l, r));
        return ret;
    }
};

inline int nextInt()
{
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        ch = getchar();
    }
    int ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    return ret;
}

int s[MAXN], x[MAXN], y[MAXN];
SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int N;
    while(scanf("%d", &N) != EOF)
    {
        for(int i = 1; i <= N; ++i)
        {
            s[i] = nextInt();
            x[i] = nextInt();
            y[i] = nextInt();
        }
        Solver.BuildTree(1, 1, N);
        for(int i = N; i >= 1; i--)
        {
            int l = i + x[i];
            int r = min(i + y[i] - 1, N);
            Solver.Update(1, i, i, s[i] + Solver.getMax(1, l, r));
        }
        printf("%lld\n", Solver.getMax(1, 1, 1));
    }
    return 0;
}

