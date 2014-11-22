/*
** ZOJ 3646 Matrix Transformer
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 210;

int n;
char martix[MAXN][MAXN];
bool cover[MAXN];
int link[MAXN];

bool Find(int u)
{
    for(int i = 0; i < n; ++i)
    {
        if(martix[u][i] == 'U' && !cover[i])
        {
            cover[i] = true;
            if(link[i] == -1 || Find(link[i]))
            {
                link[i] = u;
                return true;
            }
        }
    }
    return false;
}
int MaxMatch()
{
    int cnt = 0;
    memset(link, -1, sizeof(link));
    for(int i = 0; i < n; ++i)
    {
        memset(cover, false, sizeof(cover));
        if(Find(i))
            cnt++;
    }
    return cnt;
}
int main()
{
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i < n; ++i)
        {
            scanf("%s", martix[i]);
        }
        int cnt = MaxMatch();
        printf("%s\n", (cnt == n)? "YES" : "NO");
    }
    return 0;
}
