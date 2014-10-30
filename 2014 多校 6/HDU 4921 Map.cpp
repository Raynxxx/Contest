/*
** HDU 4921 Map
** Created by Rayn @@ 2014/08/09
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 20010;
const int maxm = 20;
const int INF = 0x3F3F3F3F;

int n, m;
bool degree[maxn];
int val[maxn], son[maxn], len[maxm];
int frag[maxm][maxn];

void Init()
{
    memset(son, -1, sizeof(son));
    memset(degree, false, sizeof(degree));
    for(int i = 0; i < maxm; ++i) {
        len[i] = 1;
    }
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    int T;
    scanf("%d", &T);
    while (T--)
    {
        Init();
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &val[i]);
        }
        for(int i = 0, A, B; i < m; ++i)
        {
            scanf("%d%d", &A, &B);
            son[A] = B;
            degree[B] = true;
        }
        int fragCnt = 0, maxlen = 0;
        double all = 1.0;
        for(int i = 0; i < n; ++i)
        {
            if(!degree[i])
            {
                int now = i, sum = 0;
                while(now != -1)
                {
                    sum += val[now];
                    frag[fragCnt][len[fragCnt]++] = sum;
                    now = son[now];
                }
                maxlen = max(maxlen, len[fragCnt]);
                all *= (double)len[fragCnt];
                fragCnt++;
            }
        }
        all--;

        double res = 0;
        for(int i = 1; i < maxlen; ++i)
        {
            for(int j = 0; j < (1<<fragCnt); ++j)
            {
                int y = 0, x = 0;
                bool flag = false;
                double sum = 0, tot = 1;
                for(int k = 0; k < fragCnt; ++k)
                {
                    if(i < len[k]) {
                        x++;
                    }
                    if(j & (1<<k))
                    {
                        if(i >= len[k])
                        {
                            flag = true;
                            break;
                        }
                        tot *= len[k] - i;
                        sum += frag[k][i] - frag[k][i-1];
                        y++;
                    }
                    else
                    {
                        if(i >= len[k])
                        {
                            tot *= len[k];
                        }
                        else
                        {
                            tot *= i;
                        }
                    }
                }
                if(flag) {
                    continue;
                }
                if(y > 1)
                {
                    res += (sum + sum*y/(double)x) * tot/all;
                }
                else
                {
                    res += (double)sum * tot/all;
                }
            }
        }
        printf("%.3f\n", res);
    }
    return 0;
}
