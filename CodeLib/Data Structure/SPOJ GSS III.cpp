/*
** SPOJ Can you answer these queries III
** Created by Rayn @@ 2014/08/31
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 50000 + 10;
const int INF = 0x3F3F3F3F;

inline int nextInt()
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    int ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    if(flag) ret = -ret;
    return ret;
}

int N, M;
int arr[MAXN];

struct SegmentTree
{
    struct SegNode
    {
        int sum, lmax, rmax, submax;
        inline void makeNode(const int& val) {
            sum = lmax = rmax = submax = val;
        }
    };

    SegNode tree[MAXN<<2];

    inline SegNode PushUp(const SegNode& L, const SegNode& R)
    {
        SegNode ret;
        ret.sum = L.sum + R.sum;
        ret.lmax = max(L.lmax, L.sum + R.lmax);
        ret.rmax = max(R.rmax, L.rmax + R.sum);
        ret.submax = max(max(L.submax, R.submax), L.rmax + R.lmax);
        return ret;
    }
    inline void Build(int rt, int l, int r)
    {
        if(l == r) {
            tree[rt].makeNode(arr[l]);
            return ;
        }
        int mid = (l + r) >> 1;
        Build(rt<<1, l, mid);
        Build(rt<<1|1, mid+1, r);
        tree[rt] = PushUp(tree[rt<<1], tree[rt<<1|1]);
    }
    inline void Modify(int rt, int l, int r, int pos, int val)
    {
        if(l == r && l == pos)
        {
            tree[rt].makeNode(val);
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) {
            Modify(rt<<1, l, mid, pos, val);
        } else if(mid < pos) {
            Modify(rt<<1|1, mid+1, r, pos, val);
        }
        tree[rt] = PushUp(tree[rt<<1], tree[rt<<1|1]);
    }
    inline SegNode Query(int rt, int l, int r, int x, int y)
    {
        if(x <= l && r <= y)
        {
            return tree[rt];
        }
        int mid = (l + r) >> 1;
        if(y <= mid) {
            return Query(rt<<1, l, mid, x, y);
        } else if(mid < x) {
            return Query(rt<<1|1, mid+1, r, x, y);
        } else {
            return PushUp(Query(rt<<1, l, mid, x, mid), Query(rt<<1|1, mid+1, r, mid+1, y));
        }
    }
    int GaoGaoGao(int x, int y)
    {
        return Query(1, 1, N, x, y).submax;
    }
};

SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d", &N) != EOF)
    {
        for(int i = 1; i <= N; ++i) {
            arr[i] = nextInt();
        }
        Solver.Build(1, 1, N);
        M = nextInt();
        while(M--)
        {
            int op, x, y;
            op = nextInt();
            x = nextInt();
            y = nextInt();
            if(op == 0) {
                Solver.Modify(1, 1, N, x, y);
            } else {
                printf("%d\n", Solver.GaoGaoGao(x, y));
            }
        }
    }
	return 0;
}
