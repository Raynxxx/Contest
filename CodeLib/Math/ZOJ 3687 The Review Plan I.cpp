/*
** ZOJ 3686 The Review Plan I
** Created by Rayn @@ 2014/07/15
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MOD 55566677
using namespace std;
typedef long long LL;

LL C[55], ans;
int da[55], ch[55];
bool day[55], chap[55], dont[55][55];
int n, m, limit;

void Init()
{
    C[0] = 1;
    C[1] = 1;
    for(int i = 2; i <= 54; ++i)
    {
        C[i] = (C[i-1] * (LL)i) % MOD;
        //printf("C[%d]:  %lld\n", i, C[i]);
    }
}
void DFS(int x, int y)
{
    if(x >= limit)
    {
        if(y > n)
            return ;
        if(y&1)
            ans -= C[n-y];
        else
            ans += C[n-y];
        ans = (ans + MOD) % MOD;
        return ;
    }
    DFS(x+1, y);
    if(!day[da[x]] && !chap[ch[x]])
    {
        day[da[x]] = true;
        chap[ch[x]] = true;
        DFS(x+1, y+1);
        day[da[x]] = false;
        chap[ch[x]] = false;
    }
}
int main()
{
    Init();
    int d, c;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        memset(dont, false, sizeof(dont));
        memset(day,  false, sizeof(day));
        memset(chap, false, sizeof(chap));
        limit = 0;
        for(int i = 0; i < m; ++i)
        {
            scanf("%d%d", &d, &c);
            if(!dont[d][c])
            {
                da[limit] = d;
                ch[limit] = c;
                limit++;
                dont[d][c] = true;
            }
        }
        ans = 0ll;
        DFS(0, 0);
        printf("%lld\n", ans);
    }
    return 0;
}
