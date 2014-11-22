/*
** POJ 3468 A Simple Problem with Integers
** Created by Rayn @@ 2014/07/13
*/
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100010;
typedef long long LL;

struct Segment
{
    int l, r;
    long long sum, add;
    Segment(int l = 0, int r = 0, LL sum = 0, LL add = 0):
        l(l), r(r), sum(sum), add(add) {}
    int range()
    {
        return r - l + 1;
    }
};

struct SegmentTree
{
    long long arr[MAXN];
    Segment tree[MAXN<<2];

    void Init()
    {
        memset(arr, 0, sizeof(arr));
        memset(tree, 0, sizeof(tree));
    }
    void PushUp(int rt)
    {
        tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
    }
    void PushDown(int rt, int range)
    {
        if(tree[rt].add)
        {
            tree[rt<<1].add += tree[rt].add;
            tree[rt<<1|1].add += tree[rt].add;
            tree[rt<<1].sum += (range - range/2) * tree[rt].add;
            tree[rt<<1|1].sum += (range/2) * tree[rt].add;
            tree[rt].add = 0;
        }
    }
    void BuildTree(int rt, int l, int r)
    {
        tree[rt].l = l;
        tree[rt].r = r;
        tree[rt].add = 0;
        if(l == r)
        {
            tree[rt].sum = arr[l];
            return ;
        }
        int mid = (l + r) >> 1;
        BuildTree(rt<<1, l, mid);
        BuildTree(rt<<1|1, mid+1, r);
        PushUp(rt);
    }
    void Update(int rt, int x, int y, int add)
    {
        int range = tree[rt].range();
        if(x <= tree[rt].l && tree[rt].r <= y)
        {
            tree[rt].add += add;
            tree[rt].sum += (long long) add * range;
            return ;
        }
        PushDown(rt, range);
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(x <= mid)
            Update(rt<<1, x, y, add);
        if(mid < y)
            Update(rt<<1|1, x, y, add);
        PushUp(rt);
    }
    long long Query(int rt, int x, int y)
    {
        int range = tree[rt].range();
        if(x <= tree[rt].l && tree[rt].r <= y)
        {
            return tree[rt].sum;
        }
        PushDown(rt, range);
        long long ans = 0;
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(x <= mid)
            ans += Query(rt<<1, x, y);
        if(mid < y)
            ans += Query(rt<<1|1, x, y);
        return ans;
    }
};

SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int N, Q, a, b, val;
    char op[10];

    while(scanf("%d%d", &N, &Q) != EOF)
    {
        Solver.Init();
        for(int i = 1; i <= N; ++i)
        {
            scanf("%lld", &Solver.arr[i]);
        }
        Solver.BuildTree(1, 1, N);
        while(Q--)
        {
            scanf("%s", op);
            if(op[0] == 'Q')
            {
                scanf("%d%d", &a, &b);
                printf("%lld\n", Solver.Query(1, a, b));
            }
            else if(op[0] == 'C')
            {
                scanf("%d%d%d", &a, &b, &val);
                Solver.Update(1, a, b, val);
            }
        }
    }
	return 0;
}
