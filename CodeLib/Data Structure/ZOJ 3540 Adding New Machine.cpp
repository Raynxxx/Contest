/*
** ZOJ 3540 Adding New Machine
** Created by Rayn @@ 2014/09/16
*/
#include <map>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#define lson (rt<<1)
#define rson (rt<<1|1)
typedef long long LL;
const int MAXN = 50100;

struct ScanLine
{
    int l, r, h, type;
    ScanLine() {}
    ScanLine(int l, int r, int h, int type):
        l(l), r(r), h(h), type(type) {}
    bool operator < (const ScanLine& rhs) const
    {
        return h < rhs.h || (h == rhs.h && type > rhs.type);
    }
};

int W, H, N, M, SZ;
int tx1[MAXN], ty1[MAXN];
int tx2[MAXN], ty2[MAXN];
int Dx[MAXN<<1];
ScanLine line[MAXN<<1];

class SegmentTree
{
public:

    int sum[MAXN<<3];
    int cover[MAXN<<3];

    void Init()
    {

        memset(sum, 0, sizeof(sum));
        memset(cover, 0, sizeof(cover));
    }
    void PushUp(int rt, int l, int r)
    {
        if(cover[rt] >= 1) {
            sum[rt] = Dx[r+1] - Dx[l];
        } else if(l == r) {
            sum[rt] = 0;
        } else {
            sum[rt] = sum[lson] + sum[rson];
        }
    }
    void Update(int rt, int l, int r, int x, int y, int type)
    {
        if(x <= l && r <= y) {
            cover[rt] += type;
            PushUp(rt, l, r);
            return ;
        }
        int mid = (l + r) >> 1;
        if(x <= mid)
            Update(lson, l, mid, x, y, type);
        if(mid < y)
            Update(rson, mid+1, r, x, y, type);
        PushUp(rt, l, r);
    }
};

SegmentTree st;

LL Gao()
{
    st.Init();
    SZ = 0;
    for(int i = 0; i < N; ++i) {
        Dx[SZ] = tx1[i]-1;
        line[SZ++] = ScanLine(tx1[i]-1, tx2[i], max(0, ty1[i]-M), 1);
        Dx[SZ] = tx2[i];
        line[SZ++] = ScanLine(tx1[i]-1, tx2[i], ty2[i], -1);
    }
    Dx[SZ] = 0;
    line[SZ++] = ScanLine(0, W, max(0, H-M+1), 1);
    Dx[SZ] = W;
    line[SZ++] = ScanLine(0, W, H, -1);

    sort(line, line + SZ);
    sort(Dx, Dx + SZ);
    int range = unique(Dx, Dx + SZ) - Dx;
    long long ret = 0;
    for(int i = 0; i < SZ; ++i) {
        if(i != 0) {
            ret += (LL)st.sum[1] * (line[i].h - line[i-1].h);
        }
        int left = lower_bound(Dx, Dx + range, line[i].l) - Dx;
        int right = lower_bound(Dx, Dx + range, line[i].r) - Dx - 1;
        if(left <= right) {
            st.Update(1, 0, range - 1, left, right, line[i].type);
        }
    }
    return (LL)W * H - ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d%d%d", &W, &H, &N, &M) != EOF)
    {
        for(int i = 0; i < N; ++i) {
            scanf("%d%d%d%d", &tx1[i], &ty1[i], &tx2[i], &ty2[i]);
        }
        long long res = Gao();
        if(M != 1) {
            swap(W, H);
            for(int i = 0; i < N; ++i) {
                swap(tx1[i], ty1[i]);
                swap(tx2[i], ty2[i]);
            }
            res += Gao();
        }
        printf("%lld\n", res);
    }
    return 0;
}
