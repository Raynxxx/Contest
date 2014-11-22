/*
** POJ 1177 Picture
** Created by Rayn @@ 2014/07/23
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 10010;
const int INF = 0x3F3F3F3F;

struct Segment
{
    int y1, y2, x;
    int flag;
    Segment() {}
    Segment(int y1, int y2, int x, int f):
        y1(y1), y2(y2), x(x), flag(f) {}
    bool operator < (const Segment& rhs) const
    {
        return x < rhs.x || (x == rhs.x && flag > rhs.flag);
    }
};

struct TreeNode
{
    int l, r;
    int cnt, line;
    int lbd, rbd, sum;
};

vector<Segment> scan;
vector<int> DY;
map<int, int> mp;

struct SegmentTree
{
    TreeNode tree[MAXN<<3];

    void Init()
    {
        scan.clear();
        DY.clear();
        mp.clear();
    }
    void BuildTree(int rt, int l, int r)
    {
        tree[rt].l = l;
        tree[rt].r = r;
        tree[rt].cnt = tree[rt].sum = tree[rt].line = 0;
        if(l + 1 == r)
        {
            return ;
        }
        int mid = (l + r) >> 1;
        BuildTree(rt<<1, l, mid);
        BuildTree(rt<<1|1, mid, r);
    }
    void Update(int rt)
    {
        if(tree[rt].cnt > 0)
        {
            tree[rt].lbd = tree[rt].rbd = tree[rt].line = 1;
            tree[rt].sum = DY[tree[rt].r-1] - DY[tree[rt].l-1];
        }
        else if(tree[rt].l + 1 == tree[rt].r)
        {
            tree[rt].lbd = tree[rt].rbd = tree[rt].line = tree[rt].sum = 0;
        }
        else
        {
            tree[rt].lbd = tree[rt<<1].lbd;
            tree[rt].rbd = tree[rt<<1|1].rbd;
            tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
            tree[rt].line = tree[rt<<1].line + tree[rt<<1|1].line - tree[rt<<1].rbd*tree[rt<<1|1].lbd;
        }
    }
    void Insert(int rt, int x, int y, int flag)
    {
        if(x <= DY[tree[rt].l-1] && DY[tree[rt].r-1] <= y)
        {
            tree[rt].cnt += flag;
            Update(rt);
            return ;
        }
        if(tree[rt].l + 1 == tree[rt].r)
        {
            return ;
        }
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(x <= DY[mid-1])
            Insert(rt<<1, x, y, flag);
        if(DY[mid-1] < y)
            Insert(rt<<1|1, x, y, flag);
        Update(rt);
    }
};

SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    int n;
    int x1, y1, x2, y2;
    while(scanf("%d", &n) != EOF)
    {
        Solver.Init();
        for(int i = 0; i < n; ++i)
        {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            scan.push_back(Segment(y1, y2, x1, +1));
            scan.push_back(Segment(y1, y2, x2, -1));
            DY.push_back(y1);
            DY.push_back(y2);
        }
        sort(scan.begin(), scan.end());
        sort(DY.begin(), DY.end());
        DY.erase(unique(DY.begin(), DY.end()), DY.end());
        for(int i = 1; i <= (int) DY.size(); ++i)
        {
            mp[DY[i-1]] = i;
        }
        Solver.BuildTree(1, 1, DY.size());
        int perimeter = 0;
        int presum = 0, preline = 0;
        for(int i = 0; i < 2*n; ++i)
        {
            Solver.Insert(1, scan[i].y1, scan[i].y2, scan[i].flag);
            if(i >= 1)
            {
                perimeter += 2 * preline * (scan[i].x - scan[i-1].x);
            }
            perimeter += abs(Solver.tree[1].sum - presum);
            presum = Solver.tree[1].sum;
            preline = Solver.tree[1].line;
        }
        printf("%d\n", perimeter);
    }
    return 0;
}
