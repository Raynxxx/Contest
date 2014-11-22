/*
** HDU 1698 Just a Hook
** Created by Rayn @@ 2014/07/12
** Ïß¶ÎÊ÷
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 100005;

struct TreeNode
{
    int l, r, sum;
    int add;
    TreeNode() {}
    TreeNode(int l, int r, int sum, int add):
        l(l), r(r), sum(sum), add(add) {}
};

struct SegmentTree
{
    TreeNode tree[MAXN<<2];

    void PushUp(int rt)
    {
        tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
    }
    void PushDown(int rt, int range)
    {
        if(tree[rt].add)
        {
            tree[rt<<1].add = tree[rt<<1|1].add = tree[rt].add;
            tree[rt<<1].sum = (range - range/2) * tree[rt].add;
            tree[rt<<1|1].sum = (range/2) * tree[rt].add;
            tree[rt].add = 0;
        }
    }
    void BuildTree(int rt, int l, int r, int InitVal)
    {
        tree[rt].l = l;
        tree[rt].r = r;
        tree[rt].add = 0;
        if(l == r)
        {
            tree[rt].sum = InitVal;
            return ;
        }
        int mid = (l + r) >> 1;
        BuildTree(rt<<1, l, mid, InitVal);
        BuildTree(rt<<1|1, mid+1, r, InitVal);
        PushUp(rt);
    }
    void Update(int rt, int x, int y, int val)
    {
        int range = tree[rt].r - tree[rt].l + 1;
        if(x <= tree[rt].l && tree[rt].r <= y)
        {
            tree[rt].add = val;
            tree[rt].sum = val * range;
            return ;
        }
        PushDown(rt, range);
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(x <= mid)
            Update(rt<<1, x, y, val);
        if(mid < y)
            Update(rt<<1|1, x, y, val);
        PushUp(rt);
    }
};

SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int T, N, Q, cas = 0;
    int x, y, z;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &N, &Q);
        Solver.BuildTree(1, 1, N, 1);
        while(Q--)
        {
            scanf("%d%d%d", &x, &y, &z);
            Solver.Update(1, x, y, z);
        }
        int res = Solver.tree[1].sum;
        printf("Case %d: The total value of the hook is %d.\n", ++cas, res);
    }
	return 0;
}
