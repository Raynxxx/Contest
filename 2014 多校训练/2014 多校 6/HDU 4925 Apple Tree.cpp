/*
** HDU 4925 Apple Tree
** Created by Rayn @@ 2014/08/08
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int t, n, m;

int Fuck(int flag)
{
    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(flag)
            {
                int cnt = 1;
                for(int k = 0; k < 4; k++)
                {
                    int tx = i + dir[k][0];
                    int ty = j + dir[k][1];
                    if (tx < 0 || tx >= n || ty < 0 || ty >= m)
                        continue;
                    cnt *= 2;
                }
                ans += cnt;
            }
            flag ^= 1;
        }
    }
    return ans;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        printf("%d\n", max(Fuck(1), Fuck(0)));
    }
    return 0;
}
