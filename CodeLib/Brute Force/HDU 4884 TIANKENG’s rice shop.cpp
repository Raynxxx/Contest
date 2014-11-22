/*
** HDU 4884 TIANKENG's rice shop
** Created by Rayn @@ 2014/08/22
*/
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int MAXN = 1010;

int arrive[MAXN], id[MAXN], num[MAXN], ret[MAXN];

void out(int t)
{
    t %= 1440;
    printf("%02d:%02d\n", t / 60, t % 60);
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int Test;
    scanf("%d", &Test);
    while(Test--)
    {
        int N, T, K, M;
        scanf("%d%d%d%d", &N, &T, &K, &M);
        for(int i = 0; i < M; ++i)
        {
            int hh, mm;
            scanf("%d:%d %d %d", &hh, &mm, &id[i], &num[i]);
            arrive[i] = hh * 60 + mm;
            ret[i] = -1;
        }
        int now = 0;
        for(int i = 0; i < M; ++i)
        {
            if(ret[i] == -1)
            {
                int need = (num[i] + K - 1) / K;
                int ed = max(now, arrive[i]) + (need - 1) * T;
                int rest = need * K;
                for(int j = i; j < M; ++j)
                {
                    if(arrive[j] > ed || rest == 0) break;
                    if(id[j] == id[i]) {
                        int del = min(rest, num[j]);
                        rest -= del;
                        num[j] -= del;
                        if(num[j] == 0 && ret[j] == -1) {
                            ret[j] = ed + T;
                        }
                    }
                }
                now = ed + T;
            }
            out(ret[i]);
        }
        if(Test > 0)
            puts("");
    }
    return 0;
}
