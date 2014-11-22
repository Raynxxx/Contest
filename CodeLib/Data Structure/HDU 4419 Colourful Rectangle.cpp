/*
** HDU 4419 Colourful Rectangle
** Created by Rayn @@ 2014/09/09
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
typedef long long LL;
const int MAXN = 20005;

struct ScanLine
{
    int l, r, h;
    int type;
    ScanLine() {}
    ScanLine(int l, int r, int h, int type):
        l(l), r(r), h(h), type(type) {}
    bool operator < (const ScanLine& p) const {
        return h < p.h || (h == p.h && type < p.type);
    }
};

int n, tot;
int DX[MAXN];
LL res[1<<3];
ScanLine line[MAXN];

class SegmentTree
{
private:
    struct SegNode
    {
        int l, r;
        int cover[4];
        LL sum[1<<3];

        inline void Init(const int& x) {
            for(int i = 0; i <= 3; ++i) cover[i] = 0;
            for(int i = 1; i < 8; ++i) sum[i] = 0;
            sum[0] = x;
        }
        inline int getMid() {
            return (l + r) >> 1;
        }
    };
    inline void PushUp(int rt, int l, int r) {
        int cur = 0;
        for(int i = 1; i <= 3; ++i) {
            if(T[rt].cover[i]) {
                cur |= (1 << (i-1));
            }
        }
        fill_n(T[rt].sum, 8, 0);
        if(l == r) {
            T[rt].sum[cur] = DX[r] - DX[l-1];
        } else {
            for(int i = 0; i < 8; ++i) {
                T[rt].sum[i|cur] += T[lson].sum[i] + T[rson].sum[i];
            }
        }
    }
public:
    SegNode T[MAXN<<2];

    void Build(int rt, int l, int r)
    {
        T[rt].l = l, T[rt].r = r;
        T[rt].Init(DX[r] - DX[l-1]);
        if(l == r) {
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid);
        Build(rson, mid+1, r);
        PushUp(rt, l, r);
    }
    void Update(int rt, int x, int y, int type)
    {
        if(x <= T[rt].l && T[rt].r <= y) {
            if(type > 0) {
                T[rt].cover[type]++;
            } else {
                T[rt].cover[-type]--;
            }
            PushUp(rt, T[rt].l, T[rt].r);
            return ;
        }
        int mid = T[rt].getMid();
        if(x <= mid) Update(lson, x, y, type);
        if(mid < y) Update(rson, x, y, type);
        PushUp(rt, T[rt].l, T[rt].r);
    }
};

void Init()
{
    tot = 0;
    memset(res, 0, sizeof(res));
}
inline int getType(char *s)
{
    if(s[0] == 'R') return 1;
    if(s[0] == 'G') return 2;
    if(s[0] == 'B') return 3;
}

SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;

    scanf("%d", &T);
    while(T--)
    {
        Init();
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            char str[3];
            int x1, y1, x2, y2;
            scanf("%s%d%d%d%d", str, &x1, &y1, &x2, &y2);
            int type = getType(str);
            DX[tot] = x1;
            line[tot++] = ScanLine(x1, x2, y1, type);
            DX[tot] = x2;
            line[tot++] = ScanLine(x1, x2, y2, -type);
        }
        sort(DX, DX + tot);
        sort(line, line + tot);
        int m = unique(DX, DX + tot) - DX;
        Solver.Build(1, 1, m-1);
        for(int i = 0; i < tot; ++i) {
            for(int j = 1; j < 8 & i != 0; ++j) {
                res[j] += Solver.T[1].sum[j] * (line[i].h - line[i-1].h);
            }
            int left = lower_bound(DX, DX + m, line[i].l) - DX;
            int right = lower_bound(DX, DX + m, line[i].r) - DX;
            Solver.Update(1, left + 1, right, line[i].type);
        }
        printf("Case %d:\n", ++cases);
        printf("%I64d\n", res[1]);
        printf("%I64d\n", res[2]);
        printf("%I64d\n", res[4]);
        printf("%I64d\n", res[3]);
        printf("%I64d\n", res[5]);
        printf("%I64d\n", res[6]);
        printf("%I64d\n", res[7]);
    }
    return 0;
}
