/*
** HDU 4907 Task schedule
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
const int MAXN = 100010;

int N, M;
int t[MAXN];
int f[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &N, &M);
        for(int i = 0; i < N; ++i)
        {
            scanf("%d", &t[i]);
        }
        sort(t, t + N);
        f[N-1] = t[N-1] + 1;
        for(int i = N-2; i >= 0; --i)
        {
            if(t[i] + 1 == t[i+1]) {
                f[i] = f[i+1];
            } else {
                f[i] = t[i] + 1;
            }
        }
        while(M--)
        {
            int q;
            scanf("%d", &q);
            int idx = lower_bound(t, t + N, q) - t;
            if(t[idx] != q || idx == N) {
                printf("%d\n", q);
            } else {
                printf("%d\n", f[idx]);
            }
        }
    }
    return 0;
}
