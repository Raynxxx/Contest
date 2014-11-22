/*
** HDU 4908 BestCoder Sequence
** Created by Rayn @@ 2014/08/22
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 80010;

int N, M, pos;
int arr[MAXN];
int cnt[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d", &N, &M) != EOF)
    {
        for(int i = 0; i < N; ++i)
        {
            scanf("%d", &arr[i]);
            if(arr[i] == M) {
                pos = i;
            }
        }
        fill(cnt, cnt + 2*N+1, 0);
        cnt[N] = 1;
        for(int i = pos+1, sum = 0; i < N; ++i)
        {
            if(arr[i] > M) sum++;
            else sum--;
            ++cnt[N+sum];
        }
        long long ret = cnt[N];
        for(int i = pos-1, sum = 0; i >= 0; --i)
        {
            if(arr[i] < M) sum++;
            else sum--;
            ret += cnt[N+sum];
        }
        printf("%I64d\n", ret);
    }
    return 0;
}
