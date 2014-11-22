/*
** POJ 1389 Area of Simple Polygons
** Created by Rayn @@ 2014/07/11
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
const int MAXN = 2010;
const int INF = 0x3F3F3F3F;

struct Line
{
    int l, r, h;
    int flag;
    Line() {}
    Line(int l, int r, int h, int flag):
        l(l), r(r), h(h), flag(flag) {}
    bool operator < (const Line& rhs) const
    {
        return h < rhs.h;
    }
};

struct TreeNode
{
    int l, r, flag;
    int left, right, len;
    TreeNode() {}
    TreeNode(int l, int r, int flag, int left, int right, int len):
        l(l), r(r), flag(flag), left(left), right(right), len(len) {}
};

vector<Line> line;
vector<int> DX;
map<int, int> mp;

struct SegmentTree
{
    TreeNode tree[MAXN<<2];

    void Init()
    {
        memset(tree, 0, sizeof(tree));
        mp.clear();
        DX.clear();
        DX.reserve(MAXN);
        line.clear();
        line.reserve(MAXN);
    }
    void BuildTree(int rt, int l, int r)
    {
        if(l == r)
        {
            tree[rt] = TreeNode(l, r, 0, DX[l-1], DX[l], 0);
            return ;
        }
        int mid = (l + r) >> 1;
        BuildTree(rt<<1, l, mid);
        BuildTree(rt<<1|1, mid+1, r);
        tree[rt] = TreeNode(l, r, 0, tree[rt<<1].left, tree[rt<<1|1].right, 0);
    }
    void Update(int rt, int s, int e, int v)
    {
        if(s <= tree[rt].l && tree[rt].r <= e)
        {
            tree[rt].flag += v;
            Maintain(rt);
        }
        else
        {
            int mid = (tree[rt].l + tree[rt].r) >> 1;
            if(s <= mid)
                Update(rt<<1, s, e, v);
            if(mid < e)
                Update(rt<<1|1, s, e, v);
            Maintain(rt);
        }
    }
    void Maintain(int rt)
    {
        if(tree[rt].flag)
            tree[rt].len = tree[rt].right - tree[rt].left;
        else if(tree[rt].l == tree[rt].r && !tree[rt].flag)
            tree[rt].len = 0;
        else
            tree[rt].len = tree[rt<<1].len + tree[rt<<1|1].len;
    }
};

SegmentTree solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int x1, x2, y1, y2;
    while(scanf("%d%d%d%d", &x1, &y1, &x2, &y2))
    {
        solver.Init();
        if(x1 == -1 && y1 == -1 && x2 == -1 && y2 == -1)
            break;
        //printf("%d %d %d %d\n", x1, y1, x2, y2);
        line.push_back(Line(x1, x2, y1, 1));
        line.push_back(Line(x1, x2, y2, -1));
        DX.push_back(x1);
        DX.push_back(x2);
        while(scanf("%d%d%d%d", &x1, &y1, &x2, &y2))
        {
            if(x1 == -1 && y1 == -1 && x2 == -1 && y2 == -1)
                break;
            //printf("%d %d %d %d\n", x1, y1, x2, y2);
            line.push_back(Line(x1, x2, y1, 1));
            line.push_back(Line(x1, x2, y2, -1));
            DX.push_back(x1);
            DX.push_back(x2);
        }
        sort(line.begin(), line.end());
        sort(DX.begin(), DX.end());
        DX.erase(unique(DX.begin(), DX.end()), DX.end());
        for(int i = 1; i <= (int) DX.size(); ++i)
        {
            mp[DX[i-1]] = i;
        }
        //printf("DX.size():  %d\n", DX.size());
        //printf("line.size():  %d\n", line.size());
        solver.BuildTree(1, 1, DX.size()-1);
        int res = 0;
        for(int i = 0; i < (int) line.size(); ++i)
        {
            if(i > 0)
                res += (line[i].h - line[i-1].h) * solver.tree[1].len;
            solver.Update(1, mp[line[i].l], mp[line[i].r]-1, line[i].flag);
            //printf("%d - %d flag: %d\n", mp[line[i].l], mp[line[i].r]-1, line[i].flag);
        }
        printf("%d\n", res);
    }
    return 0;
}
