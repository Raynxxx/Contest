/*
** ZOJ 3796 Left 4 Dead
** Created by Rayn @@ 2014/08/12
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef pair<int, int> PII;
const int SIZE = 360005;
const int MAXN = 15;

struct Node
{
    int x, y, p, q;
    Node() {}
    Node(int x, int y, int p, int q):
        x(x), y(y), p(p), q(q) {}
};

int F, D, N, M;
int PX[MAXN], PT[MAXN];
int RX[MAXN], RT[MAXN];
int dp[2][205][205][3][3];
bool vis[205][205][3][3];
Node state[2][SIZE];
int cnt[2];

inline void update(int t, int x, int y, int pill, int injection, int damage, int now)
{
    for (int a = 0; a <= pill; a++)
    for (int i = 0; i <= injection; ++i)
    for (int b = 0; a + b <= pill; ++b)
    for (int j = 0; i + j <= injection; ++j)
    for (int c = 0; a + b + c <= pill; ++c)
    for (int k = 0; i + j + k <= injection; ++k)
    for (int d = 0; a + b + c + d <= pill; ++d)
    for (int l = 0; i + j + k + l <= injection; ++l) {
        int u = (x ? min(x + a*50 + i*25, 200) : 0);
        int v = (y ? min(y + b*50 + j*25, 200) : 0);
        u = max(0, u-damage);
        if (u) {
            u = min(u + c*50 + k*25, 200);
        }
        if (v) {
            v = min(v + d*50 + l*25, 200);
        }
        int alive = (u > 0) + (v > 0);
        int p = min(pill-a-b-c-d, alive);
        int q = min(injection-i-j-k-l, alive);
        if (u < v) swap(u, v);
        if (!vis[u][v][p][q]) {
            state[t][cnt[t]++] = Node(u, v, p, q);
            vis[u][v][p][q] = true;
        }
        if(dp[t][u][v][p][q] < now)
            dp[t][u][v][p][q] = now;
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d%d%d", &F, &D, &N, &M) != EOF)
    {
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &PX[i], &PT[i]);
        }
        for (int i = 0; i < M; ++i) {
            scanf("%d%d", &RX[i], &RT[i]);
        }
        RX[M] = D; RT[M++] = 0;
        int s = 0, t = 1, ret = 0;
        memset(dp[s], -1, sizeof(dp[s]));
        cnt[0] = cnt[1] = 0;
        state[0][cnt[0]++] = Node(100, 100, 0, 0);
        dp[0][100][100][0][0] = 0;
        int i = 0, j = 0, pre = 0;
        while(i < N || j < M)
        {
            memset(dp[t], -1, sizeof(dp[t]));
            memset(vis, false, sizeof(vis));
            cnt[t] = 0;
            int dmg = 0, drug = 0;
            int now = D;
            if (i < N) {
                now = min(now, PX[i]);
            }
            if (j < M) {
                now = min(now, RX[j]);
            }
            if (i < N && now == PX[i]) {
                dmg = PT[i++];
            }
            if (j < M && now == RX[j]) {
                drug = RT[j++];
            }
            int delta = now - pre;
            for (int k = 0; k < cnt[s]; k++) {
                int x = state[s][k].x, y = state[s][k].y;
                int p = state[s][k].p, q = state[s][k].q;
                if(dp[s][x][y][p][q] == -1) {
                    continue;
                }
                int score = dp[s][x][y][p][q] + delta * ((x > 0) + (y > 0));
                int u = (x > 100) ? max(100, x - delta) : x;
                int v = (y > 100) ? max(100, y - delta) : y;
                ret = max(ret, dp[s][x][y][p][q] * 100 / D);
                if (u)
                    update(t, u, v, p + (drug == 1), q + (drug == 2), dmg, score);
                if (v)
                    update(t, v, u, p + (drug == 1), q + (drug == 2), dmg, score);
            }
            swap(s, t);
            pre = now;
        }
        for (int x = 0; x <= 200; ++x) {
            for (int y = 0; y <= x; ++y) {
                for (int p = 0; p < 3; ++p) {
                    for (int q = 0; q < 3; ++q) {
                        if(dp[s][x][y][p][q] == -1)
                            continue;
                        int score = dp[s][x][y][p][q] * 100 / D + ((x > 0) + (y > 0)) * (x + y) * F;
                        ret = max(ret, score);
                    }
                }
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
