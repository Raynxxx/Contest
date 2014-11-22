/*
** ZOJ 3548 Chess Board
** Created by Rayn @@ 2014/09/17
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int INF = 1 << 28;
const int MAXN = 256;
const int MAXH = 2050;
const int MAXM = MAXN * MAXN;

class Hungarian {
private:
    struct Edge {
        int from, to, next;
        Edge() {}
        Edge(int from, int to, int next):
            from(from), to(to), next(next) {}
    };
    int n, m;
    bool vis[MAXN];
    int link[MAXN];
    int head[MAXN];
    Edge edge[MAXM];

public:
    void Init(int n)
    {
        this->n = n;
        this->m = 0;
        memset(head, -1, sizeof(head));
    }
    void AddEdge(int from, int to)
    {
        edge[m] = Edge(from, to, head[from]);
        head[from] = m++;
    }
    bool Find(int u)
    {
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if(!vis[v]) {
                vis[v] = true;
                if(link[v] == -1 || Find(link[v])) {
                    link[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int MaxMatch()
    {
        int ret = 0;
        memset(link, -1, sizeof(link));
        for(int i = 0; i <= n; ++i) {
            memset(vis, false, sizeof(vis));
            if(Find(i)) {
                ret++;
            }
        }
        return ret;
    }
};

bool Judge(int H, int n, int a)
{
    int b = H - n * a;
    if(b <= 0 || b % (n+1)) {
        return false;
    }
    b /= n + 1;
    if(b > a) {
        return false;
    } else {
        return true;
    }
}

Hungarian hg;
char line[MAXH][MAXH];
int sum[MAXH][MAXH];
int row_cnt[MAXN];
int col_cnt[MAXN];
vector<int> may;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int H, W, n, m, T;
    while(scanf("%d%d%d%d%d", &H, &W, &n, &m, &T) != EOF)
    {
        for(int i = 0; i < H; ++i) {
            scanf("%s", &line[i]);
        }
        may.clear();
        if(n == m) {
            if(H == W) {
                for(int w = 1; w * n < W; ++w) {
                    if(Judge(H, n, w)) {
                        may.push_back(w);
                    }
                }
            } else {
                printf("-1\n");
                continue;
            }
        } else {
            int w = ((m + 1) * H - (n + 1) * W) / (n - m);
            if(w <= 0) {
                printf("-1\n");
                continue;
            }
            int border = (H - w * n) / (n + 1);
            int h1 = w * n + border * (n + 1);
            int w1 = w * m + border * (m + 1);
            if(border <= 0 || border > w || h1 != H ||  w1 != W) {
                printf("-1\n");
                continue;
            }
            may.push_back(w);
        }
        //子矩阵和
        memset(sum, 0, sizeof(sum));
        for(int i = 1; i <= H; ++i) {
            for(int j = 1, k = 0; j <= W; ++j) {
                k += line[i-1][j-1] - '0';
                sum[i][j] = sum[i-1][j] + k;
            }
        }
        int res = INF;
        for(int s = 0; s < (int) may.size(); ++s) {
            int a = may[s], b = (H - a * n) / (n + 1);
            int w = a + b, cnt = 0;
            //枚举需要染色的方块
            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= m; ++j) {
                    int subsum = sum[i*w][j*w] - sum[i*w-a][j*w]
                        - sum[i*w][j*w-a] + sum[i*w-a][j*w-a];
                    if(subsum != a * a) {
                        cnt++;
                    }
                }
            }
            /*
            ** 枚举间隙相交的黑色方块，row_cnt和col_cnt记录
            ** 的是某行和某列上，仅位于相交黑色方块上得白色
            ** 点的个数，若等于该行或列上所有白色点的个数，
            ** 则该行不必一定染色，则构造二分图
            */
            memset(row_cnt, 0, sizeof(row_cnt));
            memset(col_cnt, 0, sizeof(col_cnt));
            for(int i = 0; i <= n; ++i) {
                for(int j = 0; j <= m; ++j) {
                    int subsum = sum[i*w+b][j*w+b] - sum[i*w+b][j*w]
                        - sum[i*w][j*w+b] + sum[i*w][j*w];
                    row_cnt[i] += subsum;
                    col_cnt[j] += subsum;
                }
            }
            hg.Init(n);
            for(int i = 0; i <= n; ++i) {
                for(int j = 0; j <= m; ++j) {
                    int subsum = sum[i*w+b][j*w+b] - sum[i*w+b][j*w]
                        - sum[i*w][j*w+b] + sum[i*w][j*w];
                    if(subsum == 0) continue;
                    if(row_cnt[i] != (sum[i*w+b][W] - sum[i*w][W]))
                        continue;
                    if(col_cnt[j] != (sum[H][j*w+b] - sum[H][j*w]))
                        continue;
                    hg.AddEdge(i, j);
                }
            }
            //枚举一定要染色的行和列
            for(int i = 0; i <= n; ++i) {
                if(row_cnt[i] != (sum[i*w+b][W] - sum[i*w][W])) {
                    cnt++;
                }
            }
            for(int j = 0; j <= m; ++j) {
                if(col_cnt[j] != (sum[H][j*w+b] - sum[H][j*w])) {
                    cnt++;
                }
            }
            //二分匹配: 最小点覆盖
            cnt += hg.MaxMatch();
            res = min(res, cnt);
        }
        printf("%d\n", T * res);
    }
    return 0;
}
