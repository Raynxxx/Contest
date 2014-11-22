/*
** HDU 1754 I Hate It
** Created by Rayn @@ 2014/04/11
** Ïß¶ÎÊ÷
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 200010;
const int INF = -214748364;

int arr[MAX], maxv[MAX*4];
int N, M, A, B;

void Build(int o, int L, int R)
{
    if(L == R)
    {
        maxv[o] = arr[L];
        return ;
    }
    int mid = L + (R - L) / 2;
    if(L <= mid)
        Build(2*o, L, mid);
    if(mid < R)
        Build(2*o+1, mid+1, R);
    maxv[o] = max(maxv[2*o], maxv[2*o+1]);
}
void Update(int o, int L, int R)
{
    if(L == R)
        maxv[o] = B;
    else
    {
        int mid = L + (R - L) / 2;
        if(A <= mid)
            Update(2*o, L, mid);
        else
            Update(2*o+1, mid+1, R);
        maxv[o] = max(maxv[2*o], maxv[2*o+1]);
    }
}
int GetMax(int o, int L, int R)
{
    int mid = L + (R - L) / 2, ans = INF;
    if(A <= L && R <= B)
        return maxv[o];
    if(A <= mid)
        ans = max(ans, GetMax(2*o, L, mid));
    if(mid < B)
        ans = max(ans, GetMax(2*o+1, mid+1, R));
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
