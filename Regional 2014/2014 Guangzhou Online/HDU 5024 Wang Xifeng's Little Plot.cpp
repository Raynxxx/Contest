/*
** HDU 5024 Wang Xifeng's Little Plot
** Created by Rayn @@ 2014/09/22
*/
#include <set>
#include <map>
#include <cstdio>
#include <bitset>
#include <cmath>
#include <queue>
#include <vector>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 105;
const int INF = 0x3F3F3F3F;
const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int n;
char maze[MAXN][MAXN];
int dp[MAXN][MAXN][8];

bool out(int x, int y)
{
    if(x < 0 || x >= n || y < 0 || y >= n)
        return true;
    return false;
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 0; i < n; ++i) {
            scanf("%s", maze[i]);
        }
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(maze[i][j] == '.') {
                    for(int d = 0; d < 8; ++d) {
                        int px = i;
                        int py = j;
                        int cnt = 0;
                        while(true) {
                            px += dx[d];
                            py += dy[d];
                            if(out(px, py) || maze[px][py] == '#')
                                break;
                            cnt++;
                        }
                        dp[i][j][d] = cnt;
                    }
                }
            }
        }
        int res = -1;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(maze[i][j] == '.') {
                    res = max(res, dp[i][j][0] + dp[i][j][2] + 1);
                    res = max(res, dp[i][j][1] + dp[i][j][4] + 1);
                    res = max(res, dp[i][j][2] + dp[i][j][7] + 1);
                    res = max(res, dp[i][j][4] + dp[i][j][6] + 1);
                    res = max(res, dp[i][j][5] + dp[i][j][7] + 1);
                    res = max(res, dp[i][j][3] + dp[i][j][6] + 1);
                    res = max(res, dp[i][j][0] + dp[i][j][5] + 1);
                    res = max(res, dp[i][j][1] + dp[i][j][3] + 1);
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
