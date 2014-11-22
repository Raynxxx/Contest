/*
** ZOJ 3686 A Simple Tree Problem
** Created by Rayn @@ 2014/07/16
*/
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 100010;

vector<int> edge[MAXN];
int cnt, lhs[MAXN], rhs[MAXN];

void DFS(int u)
{
    lhs[u] = ++cnt;
    //printf("lhs[%d] : %d\n", u, lhs[u]);
    for(int i = 0; i < (int) edge[u].size(); ++i)
    {
        DFS(edge[u][i]);
    }
    rhs[u] = cnt;
    //printf("rhs[%d] : %d\n", u, rhs[u]);
}

struct SegNode
{
    int l, r, sum, tag;
    int Range() {
        return r - l + 1;
    }
};

struct SegmentTree
{
    SegNode tree[MAXN<<2];

    void Init()
    {
        cnt = 0;
        memset(tree, 0, sizeof(tree));
        for(int i = 0; i < MAXN; ++i)
        {
            edge[i].clear();
            edge[i].reserve(3);
        }
    }
    void PushUp(int rt)
    {
        tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
    }
    void PushDown(int rt)
    {
        if(tree[rt].tag)
        {
            tree[rt<<1].tag ^= 1;
            tree[rt<<1|1].tag ^= 1;
            tree[rt<<1].sum = tree[rt<<1].Range() - tree[rt<<1].sum;
            tree[rt<<1|1].sum = tree[rt<<1|1].Range() - tree[rt<<1|1].sum;
            tree[rt].tag = 0;
        }
    }
    void BuildTree(int rt, int l, int r)
    {
        tree[rt].l = l;
        tree[rt].r = r;
        tree[rt].sum = tree[rt].tag = 0;
        if(l == r) {
            return ;
        }
        int mid = (l + r) >> 1;
        BuildTree(rt<<1, l, mid);
        BuildTree(rt<<1|1, mid+1, r);
    }
    void Update(int rt, int x, int y)
    {
        if(x <= tree[rt].l && tree[rt].r <= y)
        {
            tree[rt].tag ^= 1;
            tree[rt].sum = tree[rt].Range() - tree[rt].sum;
            return ;
        }
        PushDown(rt);
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(x <= mid)
            Update(rt<<1, x, y);
        if(mid < y)
            Update(rt<<1|1, x, y);
        PushUp(rt);
    }
    int Query(int rt, int x, int y)
    {
        if(x <= tree[rt].l && tree[rt].r <= y)
        {
            return tree[rt].sum;
        }
        PushDown(rt);
        int ans = 0;
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
#endif // _Rayn

    int n, m, head, node;
    char op[4];

    while(scanf("%d%d", &n, &m) != EOF)
    {
        Solver.Init();
        for(int i = 2; i <= n; ++i)
        {
            scanf("%d", &head);
            edge[head].push_back(i);
        }
        DFS(1);
        Solver.BuildTree(1, 1, n);
        while(m--)
        {
            scanf("%s %d", op, &node);
            if(op[0] == 'o')
            {
                Solver.Update(1, lhs[node], rhs[node]);
            }
            else if(op[0] == 'q')
            {
                printf("%d\n", Solver.Query(1, lhs[node], rhs[node]));
            }
        }
        printf("\n");
    }
    return 0;
}
