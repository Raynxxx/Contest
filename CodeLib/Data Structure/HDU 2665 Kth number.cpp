/*
** HDU 2665 Kth number
** Created by Rayn @@ 2014/08/18
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 100010;

struct SegTree
{
    int l, r;
    int mid() {
        return (l + r) >> 1;
    }
};

int sorted[MAXN];
int toLeft[20][MAXN];
int val[20][MAXN];
SegTree tree[MAXN*4];

void BuildTree(int rt, int l, int r, int d)
{
    tree[rt].l = l;
    tree[rt].r = r;
    if(tree[rt].l == tree[rt].r)
        return ;
    int mid = tree[rt].mid();
    int lsame = mid - l + 1;
    for(int i = l; i <= r; ++i)
    {
        if(val[d][i] < sorted[mid]) {
            lsame--;
        }
    }
    int lpos = l, rpos = mid+1;
    int same = 0;
    for(int i = l ; i <= r; ++i)
    {
        if(i == l) {
            toLeft[d][i] = 0;
        } else {
            toLeft[d][i] = toLeft[d][i-1];
        }
        if(val[d][i] < sorted[mid]) {
            toLeft[d][i]++;
            val[d+1][lpos++] = val[d][i];
        } else if(val[d][i] > sorted[mid]) {
            val[d+1][rpos++] = val[d][i];
        } else {
            if(same < lsame) {
                same++;
                toLeft[d][i]++;
                val[d+1][lpos++] = val[d][i];
            } else {
                val[d+1][rpos++] = val[d][i];
            }
        }
    }
    BuildTree(rt<<1, l, mid, d+1);
    BuildTree(rt<<1|1, mid+1, r, d+1);
}
int Query(int rt, int d, int l, int r, int k)
{
    if(l == r) {
        return val[d][l];
    }
    int s, ss;
    if(l == tree[rt].l) {
        s = toLeft[d][r];
        ss = 0;
    } else {
        s = toLeft[d][r] - toLeft[d][l-1];
        ss = toLeft[d][l-1];
    }
    if(s >= k) {
        int newl = tree[rt].l + ss;
        int newr = tree[rt].l + ss + s - 1;
        return Query(rt<<1, d+1, newl, newr, k);
    } else {
        int mid = tree[rt].mid();
        int bb = l - tree[rt].l - ss;
        int b = r - l + 1 - s;
        int newl = mid + bb + 1;
        int newr = mid + bb + b;
        return Query(rt<<1|1, d+1, newl, newr, k-s);
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, n, m;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d", &val[0][i]);
            sorted[i] = val[0][i];
        }
        sort(sorted+1, sorted+1+n);
        BuildTree(1, 1, n, 0);
        while(m--)
        {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", Query(1, 0, l, r, k));
        }
    }
    return 0;
}
