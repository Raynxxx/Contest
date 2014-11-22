/*
** POJ 2528 Mayor’s posters
** Created by Rayn @@ 2014/07/12
** 离散化 + 线段树区间更新
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
const int MAXN = 10010;

struct Node
{
    int left, right;
    Node() {}
    Node(int l, int r): left(l), right(r) {}
};

vector<Node> poster;
vector<int> DX;
map<int, int> mp;

struct SegmentTree
{
    struct Seg
    {
        int l, r, add;
        Seg(int l = 0, int r = 0, int add = 0):
            l(l), r(r), add(add) {}
    };

    int cnt;
    bool Hash[MAXN];
    Seg tree[MAXN<<3];

    void Init()
    {
        cnt = 0;
        mp.clear();
        DX.clear();
        poster.clear();
        memset(tree, 0, sizeof(tree));
        memset(Hash, false, sizeof(Hash));
    }
    void PushDown(int rt)
    {
        if(tree[rt].add != -1)
        {
            tree[rt<<1].add = tree[rt<<1|1].add = tree[rt].add;
            tree[rt].add = -1;
        }
    }
    void BuildTree(int rt, int l, int r, int val)
    {
        tree[rt] = Seg(l, r, val);
        if(l == r)
        {
            return ;
        }
        int mid = (l + r) >> 1;
        BuildTree(rt<<1, l, mid, val);
        BuildTree(rt<<1|1, mid+1, r, val);
    }
    void Update(int rt, int x, int y, int val)
    {
        if(x <= tree[rt].l && tree[rt].r <= y)
        {
            tree[rt].add = val;
            return ;
        }
        PushDown(rt);
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(x <= mid)
            Update(rt<<1, x, y, val);
        if(mid < y)
            Update(rt<<1|1, x, y, val);
    }
    void Query(int rt, int l, int r)
    {
        if(tree[rt].add != -1)
        {
            if(!Hash[tree[rt].add])
                cnt++;
            Hash[tree[rt].add] = true;
            return ;
        }
        if(l == r)
            return ;
        int mid = (l + r) >> 1;
        Query(rt<<1, l, mid);
        Query(rt<<1|1, mid+1, r);
    }
};

SegmentTree solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int c, n;
    int left, right;

    scanf("%d", &c);
    while(c--)
    {
        solver.Init();
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
        {
            scanf("%d%d", &left, &right);
            poster.push_back(Node(left, right));
            DX.push_back(left);
            DX.push_back(right);
        }
        sort(DX.begin(), DX.end());
        DX.erase(unique(DX.begin(), DX.end()), DX.end());
        for(int i = 1; i <= (int) DX.size(); ++i)
        {
            //printf("DX[%d]:  %d\n", i-1, DX[i-1]);
            mp[DX[i-1]] = i;
        }
        solver.BuildTree(1, 1, DX.size(), -1);
        for(int i = 0; i < n; ++i)
        {
            solver.Update(1, mp[poster[i].left], mp[poster[i].right], i);
        }
        solver.Query(1, 1, DX.size());
        printf("%d\n", solver.cnt);
    }
	return 0;
}
