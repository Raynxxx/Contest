/*
** ZOJ 3772 Calculate the Function
** Created by Rayn @@ 2014/05/10
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 1000000007
using namespace std;
typedef long long LL;
const int MAXN = 100005;

struct Martix
{
    LL arr[2][2];
    Martix(int x11=0, int x12=0, int x21 =0, int x22=0)
    {
        arr[0][0] = x11; arr[0][1] = x12;
        arr[1][0] = x21; arr[1][1] = x22;
    }
    Martix operator * (const Martix& b) const
    {
        Martix res(0, 0, 0, 0);
        for(int i=0; i<2; ++i)
        {
            for(int j=0; j<2; ++j)
            {
                for(int k=0; k<2; ++k)
                {
                    res.arr[i][j] += arr[i][k] * b.arr[k][j];
                    res.arr[i][j] %= MOD;
                }
            }
        }
        return res;
    }
};
struct SegmentTree
{
    int l, r;
    Martix val;
} tree[MAXN<<2];

int A[MAXN];

void BuildTree(int l, int r, int root)
{
    tree[root].l = l;
    tree[root].r = r;
    if(l == r)
    {
        tree[root].val = Martix(1, 1, A[l], 0);
        return ;
    }
    int mid = (l + r) >> 1;
    BuildTree(l, mid, root<<1);
    BuildTree(mid+1, r, root<<1|1);
    tree[root].val = tree[root<<1].val * tree[root<<1|1].val;
}
Martix Query(int left, int right, int root)
{
    if(left <= tree[root].l && tree[root].r <= right)
    {
        return tree[root].val;
    }
    Martix res(1, 0, 0, 1);
    int mid = (tree[root].l + tree[root].r) >> 1;
    if(left <= mid)
        res = res * Query(left, right, root<<1);
    if(right > mid)
        res = res * Query(left, right, root<<1|1);
    return res;
}
int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int N, M;
        scanf("%d%d", &N, &M);
        for(int i=1; i<=N; ++i)
        {
            scanf("%d", &A[i]);
        }
        BuildTree(1, N, 1);
        while(M--)
        {
            int L, R;
            scanf("%d%d", &L, &R);
            if(R - L <= 1)
            {
                printf("%d\n", A[R]);
            }
            else
            {
                Martix res = Query(L+2, R, 1);
                LL ans = (A[L+1]*res.arr[0][0] + A[L]*res.arr[1][0]) % MOD;
                printf("%lld\n", ans);
            }
        }

    }
    return 0;
}
