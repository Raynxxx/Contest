/*
** ZOJ 3755 Mines
** Created by Rayn @@ 2014/10/02
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 15;
const int INF = 0x3F3F3F3F;

int n, m, odd, ret;
int grid[MAXN][MAXN];
int mine[MAXN][MAXN];

void dfs(int dep)
{
    if(dep >= n)
    {
        int row = dep - 1;
        bool flag = true;
        for(int i = 0; i < odd-1; ++i) {
            if(grid[row][i] != mine[row][i] + mine[row-1][i] + mine[row][i+1] + mine[row-1][i+1]) {
                flag = false;
                break;
            }
        }
        if(!flag) return ;
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < odd; ++j) {
                if(mine[i][j]) {
                    sum++;
                }
            }
        }
        ret = min(ret, sum);
    }
    for(int i = 0; i < 2; ++i) {
        mine[dep][0] = i;
        bool flag = true;
        for(int j = 1; j < odd; ++j) {
            mine[dep][j] = grid[dep-1][j-1] - mine[dep-1][j] - mine[dep][j-1] - mine[dep-1][j-1];
            if(dep > 1) {
                mine[dep][j] -= mine[dep-2][j] + mine[dep-2][j-1];
            }
            if(mine[dep][j] > 1 || mine[dep][j] < 0) {
                flag = false;
                break;
            }
        }
        if(flag) {
            dfs(dep+1);
        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d", &n, &m) != EOF)
    {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                scanf("%d", &grid[i][j]);
            }
        }
        odd = m + 1;
        ret = INF;
        for(int i = 0; i < (1 << odd); ++i) {
            for(int j = 0; j < odd; ++j) {
                mine[0][j] = (i >> j) & 1;
            }
            bool flag = true;
            for(int j = 0; j < odd-1; ++j) {
                if(mine[0][j] + mine[0][j+1] > grid[0][j]) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                dfs(1);
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}

