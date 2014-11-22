/*
** SPOJ Can you answer these queries I
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
        int left, right;
        int sum, lmax, rmax, submax;

        inline void makeNode(int val) {
            sum = lmax = rmax = submax = val;
        }
        inline int getMid() {
            return (left + right) >> 1;
        }
    };

    SegNode tree[MAXN<<2];

    inline SegNode PushUp(const SegNode& lson, const SegNode& rson)
    {
        SegNode ret;
        ret.left = lson.left;
        ret.right = rson.right;
        ret.sum = lson.sum + rson.sum;
        ret.lmax = max(lson.lmax, lson.sum + rson.lmax);
        ret.rmax = max(rson.rmax, lson.rmax + rson.sum);
        ret.submax = max(lson.rmax + rson.lmax, max(lson.submax, rson.submax));
        return ret;
    }
    void Build(int rt, int l, int r)
    {
        tree[rt].left = l, tree[rt].right = r;
        if(l == r)
        {
            tree[rt].makeNode(arr[l]);
            return ;
        }
        int mid = (l + r) >> 1;
        Build(rt<<1, l, mid);
        Build(rt<<1|1, mid+1, r);
        tree[rt] = PushUp(tree[rt<<1], tree[rt<<1|1]);
    }
    inline SegNode Query(int rt, int x, int y)
    {
        if(x <= tree[rt].left && tree[rt].right <= y)
        {
            return tree[rt];
        }
        int mid = tree[rt].getMid();
        if(y <= mid) {
            return Query(rt<<1, x, y);
        } else if(mid < x) {
            return Query(rt<<1|1, x, y);
        } else {
            return PushUp(Query(rt<<1, x, mid), Query(rt<<1|1, mid+1, y));
        }
    }
    int Gao(int x, int y)
    {
        return Query(1, x, y).submax;
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
        for(int i = 1; i <= N; ++i)
        {
            arr[i] = nextInt();
        }
        Solver.Build(1, 1, N);
        M = nextInt();
        while(M--)
        {
            int x, y;
            x = nextInt();
            y = nextInt();
            printf("%d\n", Solver.Gao(x, y));
        }
    }
	return 0;
}
