/*
** HDU 1232 ³©Í¨¹¤³Ì
** Created by Rayn @@ 2014/07/01
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1010;

int pa[MAXN];

void Init(int n)
{
    for(int i = 0; i <= n; ++i)
        pa[i] = -1;
}
int FindSet(int x)
{
    if(pa[x] == -1)
        return x;
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int n, m;
    int x, y;
    while(scanf("%d%d", &n, &m) != EOF && n)
    {
        Init(n);
        while(m--)
        {
            scanf("%d%d", &x, &y);
            int px = FindSet(x);
            int py = FindSet(y);
            if(px != py)
            {
                pa[py] = px;
            }
        }
        int cnt = 0;
        for(int i = 1; i <= n; ++i)
        {
            //printf("%d %d\n", i, pa[i]);
            if(pa[i] == -1)
                cnt++;
        }
        printf("%d\n", cnt-1);
    }
    return 0;
}
