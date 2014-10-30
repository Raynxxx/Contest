/*
** HDU 4970 Killing Monsters
** Created by Rayn @@ 2014/08/27
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100010;

int N, M, K;
LL attack[maxn];
LL sum[maxn];

template <typename T> void read(T& ret)
{
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9')
    {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int l, r, d, X;
    long long H;

    while(scanf("%d", &N) != EOF && N)
    {
        scanf("%d", &M);
        memset(attack, 0, sizeof(LL)*(N+1));
        for(int i = 0; i < M; ++i)
        {
            read(l); read(r); read(d);
            attack[l] += d;
            attack[r+1] -= d;
        }
        for(int i = 1; i <= N; ++i)
        {
            attack[i] += attack[i-1];
        }
        sum[N] = attack[N];
        for(int i = N-1; i >= 1; --i)
        {
            sum[i] = sum[i+1] + attack[i];
        }
        scanf("%d", &K);
        int ret = 0;
        while(K--)
        {
            read(H);
            read(X);
            if(H > sum[X]) {
                ret++;
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
