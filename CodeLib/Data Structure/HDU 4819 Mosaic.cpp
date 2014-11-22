/*
** HDU 4819 Mosaic
** Created by Rayn @@ 2014/09/10
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

#define lson (rt<<1)
#define rson (rt<<1|1)
#define xlson (xrt<<1)
#define xrson (xrt<<1|1)
typedef long long LL;
const int MAXN = 810;
const int INF = 0x3F3F3F3F;

int cell[MAXN][MAXN];

class SegmentTree2D
{
public:
    int n, maxr, minr;
    int x1, y1, x2, y2;
    int maxv[MAXN<<2][MAXN<<2];
    int minv[MAXN<<2][MAXN<<2];

    void Init(int n)
    {
        this->n = n;
        Build2D(1, 1, n);
    }
    inline void PushUp(int xrt, int rt)
    {
        maxv[xrt][rt] = max(maxv[xrt][lson], maxv[xrt][rson]);
        minv[xrt][rt] = min(minv[xrt][lson], minv[xrt][rson]);
    }
    void Build1D(int xrt, int xl, int xr, int rt, int l, int r)
    {
        if(l == r) {
            if(xl == xr) {
                maxv[xrt][rt] = minv[xrt][rt] = cell[xl][l];
            } else {
                maxv[xrt][rt] = max(maxv[xlson][rt], maxv[xrson][rt]);
                minv[xrt][rt] = min(minv[xlson][rt], minv[xrson][rt]);
            }
            return ;
        }
        int mid = (l + r) >> 1;
        Build1D(xrt, xl, xr, lson, l, mid);
        Build1D(xrt, xl, xr, rson, mid+1, r);
        PushUp(xrt, rt);
    }
    void Build2D(int rt, int l, int r)
    {
        if(l == r) {
            Build1D(rt, l, r, 1, 1, n);
            return ;
        }
        int mid = (l + r) >> 1;
        Build2D(lson, l, mid);
        Build2D(rson, mid+1, r);
        Build1D(rt, l, r, 1, 1, n);
    }
    void Modify1D(int xrt, int xl, int xr, int rt, int l, int r, int val)
    {
        if(l == r) {
            if(xl == xr) {
                maxv[xrt][rt] = minv[xrt][rt] = val;
            } else {
                maxv[xrt][rt] = max(maxv[xlson][rt], maxv[xrson][rt]);
                minv[xrt][rt] = min(minv[xlson][rt], minv[xrson][rt]);
            }
            return ;
        }
        int mid = (l + r) >> 1;
        if(x2 <= mid)
            Modify1D(xrt, xl, xr, lson, l, mid, val);
        else
            Modify1D(xrt, xl, xr, rson, mid+1, r, val);
        PushUp(xrt, rt);
    }
    void Modify2D(int rt, int l, int r, int val)
    {
        if(l == r) {
            Modify1D(rt, l, r, 1, 1, n, val);
            return ;
        }
        int mid = (l + r) >> 1;
        if(x1 <= mid)
            Modify2D(lson, l, mid, val);
        else
            Modify2D(rson, mid+1, r, val);
        Modify1D(rt, l, r, 1, 1, n, val);
    }
    void Query1D(int xrt, int rt, int l, int r)
    {
        if(x2 <= l && r <= y2) {
            maxr = max(maxr, maxv[xrt][rt]);
            minr = min(minr, minv[xrt][rt]);
            return ;
        }
        int mid = (l + r) >> 1;
        if(x2 <= mid)
            Query1D(xrt, lson, l, mid);
        if(mid < y2)
            Query1D(xrt, rson, mid+1, r);
    }
    void Query2D(int rt, int l, int r)
    {
        if(x1 <= l && r <= y1) {
            Query1D(rt, 1, 1, n);
            return ;
        }
        int mid = (l + r) >> 1;
        if(x1 <= mid)
            Query2D(lson, l, mid);
        if(mid < y1)
            Query2D(rson, mid+1, r);
    }
    int Query(int x, int y, int L)
    {
        L = (L + 1) / 2;
        x1 = max(1, x - L + 1);
        y1 = min(x + L - 1, n);
        x2 = max(1, y - L + 1);
        y2 = min(y + L - 1, n);
        maxr = -INF, minr = INF;
        Query2D(1, 1, n);
        return (maxr + minr) / 2;
    }
    void Modify(int x, int y, int val)
    {
        x1 = x, x2 = y;
        Modify2D(1, 1, n, val);
    }
};

SegmentTree2D Tree;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int T, Q, n, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                scanf("%d", &cell[i][j]);
            }
        }
        Tree.Init(n);
        scanf("%d", &Q);
        printf("Case #%d:\n", ++cases);
        while(Q--)
        {
            int x, y, L;
            scanf("%d%d%d", &x, &y, &L);
            int val = Tree.Query(x, y, L);
            printf("%d\n", val);
            Tree.Modify(x, y, val);
        }
    }
    return 0;
}
