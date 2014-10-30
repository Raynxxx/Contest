/*
** HDU 4967 Handling the Past
** Created by Rayn @@ 2014/08/28
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 50010;

struct Operation
{
    char order[10];
    int x, t;
    Operation() {}
    Operation(char *str, int x, int t) {
        strcpy(order, str);
        x = x, t = t;
    }
    int type() {
        if(order[1] == 'u') return 1;
        else if(order[1] == 'o') return 2;
        else if(order[1] == 'e') return 3;
    }
};

struct SegNode
{
    int left, right;
    int sum, rmax;
    int getMid() {
        return (left + right) >> 1;
    }
};
struct SegmentTree
{
    int val[MAXN<<2];
    int vis;
    SegNode tree[MAXN << 2];

    void BuildTree(int rt, int l, int r)
    {
        tree[rt].left = l;
        tree[rt].right = r;
        tree[rt].sum = tree[rt].rmax = 0;
        if(l == r) return ;
        int mid = (l + r) >> 1;
        BuildTree(rt<<1, l, mid);
        BuildTree(rt<<1|1, mid+1, r);
    }
    inline void PushUp(int rt)
    {
        tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
        tree[rt].rmax = max(tree[rt<<1|1].rmax, tree[rt<<1].rmax + tree[rt<<1|1].sum);
    }
    void Update(int rt, int l, int r, int d)
    {
        if(l <= tree[rt].left && tree[rt].right <= r)
        {
            val[rt] = d;
            if(d >= 0) {
                tree[rt].sum = tree[rt].rmax = 1;
            } else {
                tree[rt].sum = -1;
                tree[rt].rmax = 0;
            }
            return ;
        }
        int mid = tree[rt].getMid();
        if(l <= mid)
            Update(rt<<1, l, r, d);
        if(mid < r)
            Update(rt<<1|1, l, r, d);
        PushUp(rt);
    }
    int Query(int rt, int pos)
    {
        if(tree[rt].right <= pos) {
            int s = tree[rt].rmax + vis;
            if(s <= 0) {
                vis += tree[rt].sum;
                return -1;
            }
        }
        if(tree[rt].left == tree[rt].right)
            return val[rt];

        int mid = tree[rt].getMid();
        if(mid < pos) {
            int ret = Query(rt<<1|1, pos);
            if(ret != -1) return ret;
        }
        return Query(rt<<1, pos);
    }
};

inline int getID(int arr[], int len, int x)
{
    return lower_bound(arr + 1, arr + len + 1, x) - arr;
}
inline void nextString(char *str)
{
    char ch = getchar();
    while(ch < 'a' || ch > 'z') {
        ch = getchar();
    }
    int sz = 0;
    while(ch >= 'a' && ch <= 'z') {
        str[sz++] = ch;
        ch = getchar();
    }
    str[sz] = '\0';
}
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

int N;
int DT[MAXN], DN;
Operation op[MAXN];
SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int cases = 0;
    while(scanf("%d", &N) != EOF && N)
    {
        DN = 1;
        for(int i = 0; i < N; ++i)
        {
            nextString(op[i].order);
            if(op[i].type() == 1)
            {
                op[i].x = nextInt();
                op[i].t = nextInt();
            }
            else
            {
                op[i].t = nextInt();
            }
            if(op[i].type() != 3) {
                DT[DN++] = op[i].t;
            }
        }
        sort(DT + 1, DT + DN + 1);
        Solver.BuildTree(1, 1, DN);
        printf("Case #%d:\n", ++cases);
        for(int i = 0; i < N; ++i)
        {
            int id = getID(DT, DN, op[i].t);
            if(op[i].type() == 1)
            {
                Solver.Update(1, id, id, op[i].x);
            }
            else if(op[i].type() == 2)
            {
                Solver.Update(1, id, id, -1);
            }
            else if(op[i].type() == 3)
            {
                if(id == 1) {
                    printf("-1\n");
                } else {
                    Solver.vis = 0;
                    printf("%d\n", Solver.Query(1, id-1));
                }
            }
        }
    }
    return 0;
}
