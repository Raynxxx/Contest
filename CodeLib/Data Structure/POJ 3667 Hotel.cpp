/*
** POJ 3667 Hotel
** Created by Rayn @@ 2014/09/01
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
typedef long long LL;
const int MAXN = 50005;
const int INF = 0x3F3F3F3F;

template <typename T>
inline void readNumber(T& ret)
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
}

int N, M;

struct SegmentTree
{
    struct Node
    {
        int left, right;
        int cover;
        int lsum, rsum, msum;
        inline int Length() {
            return (right - left + 1);
        }
        inline int getMid() {
            return (left + right) >> 1;
        }
        inline void setNode(const int& val) {
            cover = -1;
            lsum = rsum = msum = val;
        }
    };

    Node T[MAXN<<2];

    inline void PushUp(int rt)
    {
        T[rt].lsum = T[lson].lsum;
        if(T[lson].lsum == T[lson].Length()) {
            T[rt].lsum += T[rson].lsum;
        }
        T[rt].rsum = T[rson].rsum;
        if(T[rson].rsum == T[rson].Length()) {
            T[rt].rsum += T[lson].rsum;
        }
        T[rt].msum = max(T[lson].rsum + T[rson].lsum, max(T[lson].msum, T[rson].msum));
    }
    inline void PushDown(int rt)
    {
        if(T[rt].cover != -1)
        {
            T[lson].cover = T[rson].cover = T[rt].cover;
            T[lson].msum = T[lson].lsum = T[lson].rsum = T[rt].cover ? 0 : T[lson].Length();
            T[rson].msum = T[rson].lsum = T[rson].rsum = T[rt].cover ? 0 : T[rson].Length();
            T[rt].cover = -1;
        }
    }
    inline void Build(int rt, int l, int r)
    {
        T[rt].left = l;
        T[rt].right = r;
        T[rt].setNode(r - l + 1);
        if(l == r) {
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid);
        Build(rson, mid+1, r);
    }
    void Update(int rt, int x, int y, int c)
    {
        if(x <= T[rt].left && T[rt].right <= y)
        {
            T[rt].lsum = T[rt].rsum = T[rt].msum = c ? 0 : T[rt].Length();
            T[rt].cover = c;
            return ;
        }
        PushDown(rt);
        int mid = T[rt].getMid();
        if(x <= mid)
            Update(lson, x, y, c);
        if(mid < y)
            Update(rson, x, y, c);
        PushUp(rt);
    }
    int Find(int rt, int w)
    {
        if(T[rt].left == T[rt].right) {
            return T[rt].left;
        }
        PushDown(rt);
        int mid = T[rt].getMid();
        if(T[lson].msum >= w) {
            return Find(lson, w);
        } else if(T[lson].rsum + T[rson].lsum >= w) {
            return mid - T[lson].rsum + 1;
        } else {
            return Find(rson, w);
        }
    }
};

SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d", &N, &M) != EOF)
    {
        Solver.Build(1, 1, N);
        while(M--)
        {
            int op;
            readNumber(op);
            if(op == 1) {
                int Di;
                readNumber(Di);
                if(Solver.T[1].msum < Di) {
                    puts("0");
                } else {
                    int P = Solver.Find(1, Di);
                    printf("%d\n", P);
                    Solver.Update(1, P, P+Di-1, 1);
                }
            } else if(op == 2) {
                int Xi, Di;
                readNumber(Xi);
                readNumber(Di);
                Solver.Update(1, Xi, Xi+Di-1, 0);
            }
        }
    }
    return 0;
}
