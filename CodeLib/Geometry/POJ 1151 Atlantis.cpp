/*
** POJ 1151 Atlantis
** Created by Rayn @@ 2014/07/10
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN = 210;
const double EPS = 1e-8;
const double INF = 1e20;

struct Line
{
    double left, right, h;
    int flag;
    Line() {}
    Line(double l, double r, double h, int f):
        left(l), right(r), h(h), flag(f) {}
    bool operator < (const Line& rhs) const {
        return h < rhs.h;
    }
};

struct TreeNode
{
    int l, r, flag;
    double left, right, len;
    TreeNode() {}
    TreeNode(int l, int r, int flag, double left, double right, double len):
        l(l), r(r), flag(flag), left(left), right(right), len(len) {}
};

vector<double> realX;
vector<Line> line;
map<double, int> mp;

struct SegmentTree
{
    TreeNode tree[MAXN*4];

    SegmentTree()
    {
        memset(tree, 0, sizeof(tree));
    }
    void BuildTree(int l, int r, int rt)
    {
        if(l == r)
        {
            tree[rt] = TreeNode(l, r, 0, realX[l-1], realX[l], 0);
            return ;
        }
        int mid = (l + r) >> 1;
        BuildTree(l, mid, rt<<1);
        BuildTree(mid+1, r, rt<<1|1);
        tree[rt] = TreeNode(l, r, 0, tree[rt<<1].left, tree[rt<<1|1].right, 0);
    }
    void Update(int s, int e, int rt, int flag)
    {
        if(s <= tree[rt].l && e >= tree[rt].r)
        {
            tree[rt].flag += flag;
            CalcLen(rt, flag);
        }
        else
        {
            int mid = (tree[rt].l + tree[rt].r) >> 1;
            if(s <= mid)
                Update(s, e, rt<<1, flag);
            if(mid < e)
                Update(s, e, rt<<1|1, flag);
            CalcLen(rt, flag);
        }
    }
    double CalcLen(int rt, int cnt)
    {
        if(tree[rt].flag)
            tree[rt].len = tree[rt].right - tree[rt].left;
        else if(tree[rt].l == tree[rt].r)
            tree[rt].len = 0;
        else
            tree[rt].len = tree[rt<<1].len + tree[rt<<1|1].len;
    }
};

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n, cases = 0;
    double x1, x2, y1, y2;

    while(scanf("%d", &n) != EOF && n)
    {
        realX.clear();
        line.clear();
        for(int i = 0; i < n; ++i)
        {
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            if(y1 < y2)
                swap(y1, y2);
            line.push_back(Line(x1, x2, y1, -1)); //上边-1
            line.push_back(Line(x1, x2, y2, 1));  //下边+1
            realX.push_back(x1);
            realX.push_back(x2);
        }
        //离散化
        sort(line.begin(), line.end());
        sort(realX.begin(), realX.end());
        realX.erase(unique(realX.begin(), realX.end()), realX.end());
        for(int i = 1; i <= (int) realX.size(); ++i)
        {
            mp[realX[i-1]] = i;
        }
        //建立线段树
        SegmentTree solver;
        solver.BuildTree(1, realX.size()-1, 1);
        double res = 0;
        printf("Test case #%d\n", ++cases);
        for(int i = 0; i < (int) line.size(); ++i)
        {
            if(i != 0)
                res += (line[i].h - line[i-1].h) * solver.tree[1].len;
            solver.Update(mp[line[i].left], mp[line[i].right]-1, 1, line[i].flag);
            /*
            printf("tree[1]: %.2f\n", solver.tree[1].len);
            printf("line[%d]: %.2f %.2f\n", i+1, line[i].left, line[i].right);
            printf(" %d-%d  flag: %d\n\n", mp[line[i].left], mp[line[i].right], line[i].flag);
            //*/
        }
        printf("Total explored area: %.2f\n\n", res);
    }
    return 0;
}
