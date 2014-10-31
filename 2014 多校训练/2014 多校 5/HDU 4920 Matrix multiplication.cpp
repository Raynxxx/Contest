/*
** HDU 4920 Matrix multiplication
** Created by Rayn @@ 2014/08/18
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 810;

int a[maxn][maxn], b[maxn][maxn];
int martix[maxn][maxn];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                scanf("%d", &a[i][j]);
                a[i][j] %= 3;
            }
        }
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                scanf("%d", &b[i][j]);
                b[i][j] %= 3;
            }
        }
        memset(martix, 0, sizeof(martix));
        for(int k = 0; k < n; ++k)
        {
            for(int i = 0; i < n; ++i)
            {
                if(a[i][k] == 0)
                    continue;
                for(int j = 0; j < n; ++j)
                {
                    martix[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                printf("%d%c", martix[i][j]%3, ((j == n-1)? '\n':' '));
            }
        }
    }
    return 0;
}
