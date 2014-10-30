/*
** HDU 4866 Shooting
** Created by Rayn @@ 2014/08/18
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int INF = 0x3F3F3F3F;
const int MAXN = 100005;
const int MAXM = 10005;

struct Shoot
{
    int x, d, flag;
    Shoot() {}
    Shoot(int x, int d, int flag):
        x(x), d(d), flag(flag) {}
    bool operator < (const Shoot& a) const
    {
        return x < a.x;
    }
};

struct SegTree
{
    int cnt;
    LL d;
    SegTree *son[2];
};

int N, M, X, P, top;
long long D[MAXN];
Shoot st[MAXN*2];
SegTree base[MAXN*40];
SegTree *root[MAXN*2];

void Init()
{
    top = 0;
}
SegTree* new_node()
{
    return &base[top++];
}
SegTree* Build(int l, int r)
{
    SegTree* rt = new_node();
    rt->d = rt->cnt = 0;
    if(l < r)
    {
        int mid = (l + r) >> 1;
        rt->son[0] = Build(l, mid);
        rt->son[1] = Build(mid+1, r);
    }
    return rt;
}
SegTree* Modify(SegTree* rt, int pos, int l, int r, int flag)
{
    SegTree* nrt = new_node();
    *nrt = *rt;
    if(l == r)
    {
        nrt->cnt += flag;
        nrt->d += (LL) flag * D[l];
    }
    else
    {
        int mid = (l + r) >> 1;
        if(pos <= mid) {
            nrt->son[0] = Modify(rt->son[0], pos, l, mid, flag);
        } else {
            nrt->son[1] = Modify(rt->son[1], pos, mid+1, r, flag);
        }
        nrt->d = nrt->son[0]->d + nrt->son[1]->d;
        nrt->cnt = nrt->son[0]->cnt + nrt->son[1]->cnt;
    }
    return nrt;
}
LL Query(SegTree* rt, int l, int r, int k)
{
    if(l == r)
    {
        if(rt->cnt > k)
            return (LL)rt->d / rt->cnt * k;
        else
            return rt->d;
    }
    else
    {
        int mid = (l + r) >> 1;
        if(rt->son[0]->cnt > k)
            return Query(rt->son[0], l, mid, k);
        else
            return rt->son[0]->d + Query(rt->son[1], mid+1, r, k-rt->son[0]->cnt);
    }
}
int BinarySearch(int l, int r, int val)
{
    int ret = 0;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if(st[mid].x <= val) {
            l = mid + 1;
            ret = mid;
        } else {
            r = mid - 1;
        }
    }
    return ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d%d%d", &N, &M, &X, &P) != EOF)
    {
        Init();
        for(int i = 1; i <= N; ++i)
        {
            int l, r, d;
            scanf("%d%d%d", &l, &r, &d);
            st[i] = Shoot(l, d, 1);
            st[i+N] = Shoot(r+1, d, -1);
            D[i] = d;
        }
        sort(st+1, st+1+N*2);
        sort(D+1, D+1+N);
        int PN = unique(D+1, D+1+N) - (D+1);
        root[0] = Build(1, PN);
        for(int i = 1; i <= 2*N; ++i)
        {
            int pos = lower_bound(D+1, D+1+PN, st[i].d) - D;
            root[i] = Modify(root[i-1], pos, 1, PN, st[i].flag);
        }
        LL pre = 1LL;
        while(M--)
        {
            int x, a, b, c;
            scanf("%d%d%d%d", &x, &a, &b, &c);
            int k = (a*pre + b) % (LL)c;
            if(k == 0) {
                printf("0\n");
                pre = 0;
            } else {
                int pos = BinarySearch(1, 2*N, x);
                if(pos == 0) {
                    pre = 0;
                } else if(pre > P) {
                    pre = 2 * Query(root[pos], 1, PN, k);
                } else {
                    pre = Query(root[pos], 1, PN, k);
                }
                printf("%I64d\n", pre);
            }
        }
    }
    return 0;
}
