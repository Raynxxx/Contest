/*
** HDU 4026 Unlock the Cell Phone
** Created by Rayn @@ 2014/09/06
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

int n, m, aim;
int key[6][6];
int state[31];
int edge[31][31];
LL dp[31][(1 << 16)+10];

int gcd(int a, int b)
{
    return b ? gcd(b, a%b) : a;
}
int Gao(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1, dy = y2 - y1;
    int d = gcd(abs(dx), abs(dy));
    dx /= d, dy /= d;
    int x = x1 + dx, y = y1 + dy;
    int status = 0;
    while(x != x2 || y != y2) {
        if(key[x][y] == 1) return -1;
        status |= state[x*m+y];
        x += dx;
        y += dy;
    }
    return status;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d", &n, &m) != EOF) {
        memset(state, 0, sizeof(state));
        memset(edge, -1, sizeof(edge));
        aim = 0;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                scanf("%d", &key[i][j]);
                if(key[i][j] == 0) {
                    state[i*m+j] = 1 << aim;
                    aim++;
                }
            }
        }
        int maze = n * m;
        //预处理路径
        for(int i = 0; i < maze; ++i) {
            if(!state[i]) continue;
            for(int j = i+1; j < maze; ++j) {
                if(!state[j]) continue;
                edge[i][j] = edge[j][i] = Gao(i/m, i%m, j/m, j%m);
            }
        }
        //DP过程
        for(int i = 0; i < maze; ++i) {
            fill(dp[i], dp[i] + (1 << aim), 0);
            if(state[i]) {
                dp[i][state[i]] = 1;
            }
        }
        for(int status = 0; status < (1 << aim); ++status) {
            for(int i = 0; i < maze; ++i) {
                if(!dp[i][status]) continue;
                for(int j = 0; j < maze; ++j) {
                    if(edge[i][j] != -1) {
                        int next = status | state[j];
                        if(next == status || (~next) & edge[i][j])
                            continue;
                        dp[j][next] += dp[i][status];
                    }
                }
            }
        }
        LL res = 0LL;
        for(int i = 0; i < maze; ++i) {
            res += dp[i][(1 << aim) - 1];
        }
        printf("%I64d\n", res);
    }
    return 0;
}
