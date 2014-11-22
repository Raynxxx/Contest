/*
** SPOJ Can you answer these queries IV
** Created by Rayn @@ 2014/09/01
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
typedef long long LL;
const int MAXN = 100000 + 10;

template <typename T>
inline void readNumber(T& ret)
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    if(flag) ret = -ret;
}

int N, M;
LL arr[MAXN];

struct SegmentTree
{
    struct SegNode
    {
        int left, right;
        long long sum;
        inline int getMid()
        {
            return (left + right) >> 1;
        }
        inline bool OK()
        {
            return right - left + 1 == sum;
        }
    };

    SegNode tree[MAXN<<2];

    inline void PushUp(int rt)
    {
        tree[rt].sum = tree[lson].sum + tree[rson].sum;
    }
    inline void Build(int rt, int l, int r)
    {
        tree[rt].left = l;
        tree[rt].right = r;
        if(l == r)
        {
            tree[rt].sum = arr[l];
            return ;
        }
        int mid = (l + r) >> 1;
        Build(rt<<1, l, mid);
        Build(rt<<1|1, mid+1, r);
        PushUp(rt);
    }
    inline void Modify(int rt, int x, int y)
    {
        if(tree[rt].OK()) return ;
        if(tree[rt].left == tree[rt].right)
        {
            tree[rt].sum = (LL)sqrt((double)tree[rt].sum);
            return ;
        }
        int mid = tree[rt].getMid();
        if(x <= mid)
            Modify(lson, x, y);
        if(mid < y)
            Modify(rson, x, y);
        PushUp(rt);
    }
    inline LL Query(int rt, int x, int y)
    {
        if(x <= tree[rt].left && tree[rt].right <= y)
        {
            return tree[rt].sum;
        }
        int mid = tree[rt].getMid();
        long long ret = 0LL;
        if(x <= mid)
            ret += Query(lson, x, y);
        if(mid < y)
            ret += Query(rson, x, y);
        return ret;
    }
};

SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int cases = 0;
    while(scanf("%d", &N) != EOF)
    {
        for(int i = 1; i <= N; ++i) {
            readNumber(arr[i]);
        }
        Solver.Build(1, 1, N);
        readNumber(M);
        printf("Case #%d:\n", ++cases);
        while(M--)
        {
            int op, x, y;
            readNumber(op);
            readNumber(x);
            readNumber(y);
            if(x > y) swap(x, y);
            if(op == 0) {
                Solver.Modify(1, x, y);
            } else {
                printf("%lld\n", Solver.Query(1, x, y));
            }
        }
        puts("");
    }
	return 0;
}
