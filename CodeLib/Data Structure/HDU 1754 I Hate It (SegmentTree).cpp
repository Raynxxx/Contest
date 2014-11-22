/*
** HDU 1754 I Hate It (SegmentTree)
** Created by Rayn @@ 2014/04/11
** Ïß¶ÎÊ÷
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 200010;
const int INF = 0x3F3F3F3F;

int arr[MAX], maxv[MAX<<2];
int N, M, A, B;

void Build(int rt, int L, int R)
{
    if(L == R)
    {
        maxv[rt] = arr[L];
        return ;
    }
    int mid = (L + R) >> 1;
    if(L <= mid)
        Build(rt<<1, L, mid);
    if(mid < R)
        Build(rt<<1|1, mid+1, R);
    maxv[rt] = max(maxv[rt<<1], maxv[rt<<1|1]);
}
void Update(int rt, int L, int R)
{
    if(L == R)
    {
        maxv[rt] = B;
    }
    else
    {
        int mid = (L + R) >> 1;
        if(A <= mid)
            Update(rt<<1, L, mid);
        else
            Update(rt<<1|1, mid+1, R);
        maxv[rt] = max(maxv[rt<<1], maxv[rt<<1|1]);
    }
}
int GetMax(int rt, int L, int R)
{
    int ans = -INF;
    if(A <= L && R <= B)
    {
        return maxv[rt];
    }
    int mid = (L + R) >> 1;
    if(A <= mid)
        ans = max(ans, GetMax(rt<<1, L, mid));
    if(mid < B)
        ans = max(ans, GetMax(rt<<1|1, mid+1, R));
    return ans;
}
int main()
{
    char C[10];

    while(scanf("%d%d", &N, &M) != EOF)
    {
        for(int i=1; i<=N; ++i)
            scanf("%d", &arr[i]);

        Build(1, 1, N);
        while(M--)
        {
            scanf("%s%d%d", C, &A, &B);
            if(C[0] == 'Q')
            {
                printf("%d\n", GetMax(1, 1, N));
            }
            else if(C[0] == 'U')
            {
                Update(1, 1, N);
            }
        }
    }
    return 0;
}
