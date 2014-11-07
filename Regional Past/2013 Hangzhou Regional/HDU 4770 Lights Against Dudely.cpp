/*
** HDU 4770 Lights Against Dudely
** Created by Rayn @@ 2014/09/11
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int MAXN = 210;
const int INF = 0x3F3F3F3F;
const int dir[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int n, m;
int maze[MAXN][MAXN];
PII light[16];

inline bool stop(int x, int y)
{
    return (maze[x][y] == -1);
}
inline bool out(int x, int y)
{
    if(x < 0 || x >= n || y < 0 || y >= m)
        return true;
    return false;
}
string toBinary(int x)
{
    string ret;
    while(x) {
        ret = (char)(x % 2 + '0') + ret;
        x /= 2;
    }
    return ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    char line[MAXN];
    while(scanf("%d%d", &n, &m) != EOF && (n && m))
    {
        memset(maze, -1, sizeof(maze));
        int aim = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%s", line);
            for(int j = 0; j < m; ++j) {
                if(line[j] == '.') {
                    maze[i][j] = (1 << aim);
                    light[aim++] = make_pair(i, j);
                }
            }
        }
        if(aim == 0) {
            printf("0\n");
            continue;
        }
        int res = INF;
        int allcover = (1 << aim) - 1;
        //printf("%d - %s\n", aim, toBinary(allcover).c_str());
        for(int s = 0; s < (1 << aim); ++s)
        {   //枚举状态
            int cnt = 0;
            for(int i = 0; i < aim; ++i) {
                if(s & (1 << i)) cnt++;
            }
            for(int i = 0; i < aim; i++)
            {  //枚举特殊灯
                if((s & (1 << i)) == 0)
                    continue;
                bool flag = true;
                int cur = s;
                for(int j = 0; j < aim; ++j)
                {
                    if(j == i) continue;
                    if(s & (1 << j))
                    {
                        int x = light[j].first;
                        int y = light[j].second;
                        if(!out(x-1, y)) {
                            if(stop(x-1, y)) {
                                flag = false;
                            } else {
                                cur |= maze[x-1][y];
                            }
                        }
                        if(!out(x, y+1)) {
                            if(stop(x, y+1)) {
                                flag = false;
                            } else {
                                cur |= maze[x][y+1];
                            }
                        }
                    }
                    if(!flag) break;
                }
                if(!flag) continue;

                int tx = light[i].first;
                int ty = light[i].second;
                for(int k = 0; k < 4; ++k)
                {   //枚举特殊灯方向
                    int px1 = tx + dir[k][0], py1 = ty + dir[k][1];
                    int px2 = tx + dir[k+1][0], py2 = ty + dir[k+1][1];
                    int tmp = cur;
                    if(!out(px1, py1)) {
                        if(stop(px1, py1)) {
                            continue;
                        } else {
                            tmp |= maze[px1][py1];
                        }
                    }
                    if(!out(px2, py2)) {
                        if(stop(px2, py2)) {
                            continue;
                        } else {
                            tmp |= maze[px2][py2];
                        }
                    }
                    if(tmp == allcover) {
                        res = min(res, cnt);
                    }
                }
            }
        }
        if(res == INF) res = -1;
        printf("%d\n", res);
    }
    return 0;
}
