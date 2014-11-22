/*
** SPOJ Can you answer these queries V
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
const int MAXN = 10000 + 10;

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
int arr[MAXN];

struct SegmentTree
{
    struct Node
    {
        int sum, lmax, rmax, smax;
        Node(int val = 0) {
            sum = lmax = rmax = smax = val;
        }
        inline void makeNode(const int& val) {
            sum = lmax = rmax = smax = val;
        }
    };

    Node tree[MAXN<<2];

    inline Node PushUp(const Node& L, const Node& R)
    {
        Node ret;
        ret.sum = L.sum + R.sum;
        ret.lmax = max(L.lmax, L.sum + R.lmax);
        ret.rmax = max(R.rmax, L.rmax + R.sum);
        ret.smax = max(max(L.smax, R.smax), L.rmax + R.lmax);
        return ret;
    }
    void Build(int rt, int l, int r)
    {
        if(l == r)
        {
            tree[rt].makeNode(arr[l]);
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid);
        Build(rson, mid+1, r);
        tree[rt] = PushUp(tree[lson], tree[rson]);
    }
    Node Query(int rt, int l, int r, int x, int y)
    {
        if(x > y) {
            Node ret; ret.makeNode(0);
            return ret;
        }
        if(x <= l && r <= y)
        {
            return tree[rt];
        }
        int mid = (l + r) >> 1;
        if(y <= mid) {
            return Query(lson, l, mid, x, y);
        } else if(mid < x) {
            return Query(rson, mid+1, r, x, y);
        } else {
            return PushUp(Query(lson, l, mid, x, mid), Query(rson, mid+1, r, mid+1, y));
        }
    }
    int GaoGaoGao(int x1, int y1, int x2, int y2)
    {
        int ret = 0;
        if(y1 < x2) {
            ret += Query(1, 1, N, x1, y1).rmax;
            ret += Query(1, 1, N, y1+1, x2-1).sum;
            ret += Query(1, 1, N, x2, y2).lmax;
        } else if(y1 == y2) {
            Node L = Query(1, 1, N, x1, x2-1);
            Node R = Query(1, 1, N, x2, y2);
            ret = max(R.smax, L.rmax + R.lmax);
        } else {
            Node L = Query(1, 1, N, x1, x2-1);
            Node M = Query(1, 1, N, x2, y1);
            Node R = Query(1, 1, N, y1+1, y2);
            ret = max(M.smax, L.rmax + M.sum + R.lmax);
            ret = max(ret, L.rmax + M.lmax);
            ret = max(ret, M.rmax + R.lmax);
        }
        return ret;
    }
};

SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    int x1, y1, x2, y2;
    scanf("%d", &T);
    while(T--)
    {
        readNumber(N);
        for(int i = 1; i <= N; ++i) {
            readNumber(arr[i]);
        }
        Solver.Build(1, 1, N);
        readNumber(M);
        while(M--)
        {
            readNumber(x1);
            readNumber(y1);
            readNumber(x2);
            readNumber(y2);
            printf("%d\n", Solver.GaoGaoGao(x1, y1, x2, y2));
        }
    }
	return 0;
}
