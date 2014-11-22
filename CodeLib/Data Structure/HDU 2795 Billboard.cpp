/*
** HDU 2795 Billboard
** Created by Rayn @@ 2014/07/12
** Ïß¶ÎÊ÷
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 200005;

struct TreeNode
{
    int l, r, val;
    TreeNode() {}
    TreeNode(int l, int r, int v): l(l), r(r), val(val) {}
};
struct SegmentTree
{
    TreeNode tree[MAXN<<2];

    void Init()
    {
        memset(tree, 0, sizeof(tree));
    }
    void BuildTree(int rt, int l, int r, int InitVal)
    {
        tree[rt].l = l;
        tree[rt].r = r;
        if(l == r)
        {
            tree[rt].val = InitVal;
            return ;
        }
        int mid = (l + r) >> 1;
        BuildTree(rt<<1, l, mid, InitVal);
        BuildTree(rt<<1|1, mid+1, r, InitVal);
        tree[rt].val = max(tree[rt<<1].val, tree[rt<<1|1].val);
    }
    int Query(int rt, int val)
    {
        if(tree[rt].l == tree[rt].r && tree[rt].val >= val)
        {
            tree[rt].val -= val;
            return tree[rt].l;
        }
        int data = -1;
        if(val <= tree[rt<<1].val)
        {
            data = Query(rt<<1, val);
        }
        else if(val <= tree[rt<<1|1].val)
        {
            data = Query(rt<<1|1, val);
        }
        else
        {
            data = -1;
        }
        tree[rt].val = max(tree[rt<<1].val, tree[rt<<1|1].val);
        return data;
    }
};

SegmentTree solver;

int main()
{
    int h, w, n, wi;
    while(scanf("%d%d%d", &h, &w, &n) != EOF)
    {
        solver.Init();
        solver.BuildTree(1, 1, min(h, n), w);
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &wi);
            printf("%d\n", solver.Query(1, wi));
        }
    }
	return 0;
}
