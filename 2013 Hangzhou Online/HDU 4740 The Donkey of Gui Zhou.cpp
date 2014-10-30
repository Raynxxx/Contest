/*
** HDU 4740 The Donkey of Gui Zhou
** Created by Rayn @@ 2014/09/15
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 1005;
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int n;
bool donkey[MAXN][MAXN];
bool tiger[MAXN][MAXN];
bool meet, stop;
bool donkey_stop, tiger_stop;

bool IsOut(int x, int y)
{
    if(x < 0 || y < 0 || x >= n || y >= n)
        return true;
    return false;
}
void dfs(int dx, int dy, int d1, int tx, int ty, int d2)
{
    donkey[dx][dy] = true;
    tiger[tx][ty] = true;
    if(meet || stop) return ;
    if(dx == tx && dy == ty) {
        meet = true;
        printf("%d %d\n", dx, dy);
        return ;
    }
    if(donkey_stop && tiger_stop) {
        stop = true;
        printf("-1\n");
        return ;
    }
    int pdx, pdy, ptx, pty;
    if(donkey_stop) {
        pdx = dx;
        pdy = dy;
    } else {
        pdx = dx + dir[d1][0];
        pdy = dy + dir[d1][1];
        if(IsOut(pdx, pdy) || donkey[pdx][pdy] == true) {
            d1 = (d1 + 1) % 4;
            pdx = dx + dir[d1][0];
            pdy = dy + dir[d1][1];
            if(IsOut(pdx, pdy) || donkey[pdx][pdy] == true) {
                donkey_stop = true;
                pdx = dx;
                pdy = dy;
            }
        }
    }
    if(tiger_stop) {
        ptx = tx;
        pty = ty;
    } else {
        ptx = tx + dir[d2][0];
        pty = ty + dir[d2][1];
        if(IsOut(ptx, pty) || tiger[ptx][pty] == true) {
            d2 = (d2 - 1 + 4) % 4;
            ptx = tx + dir[d2][0];
            pty = ty + dir[d2][1];
            if(IsOut(ptx, pty) || tiger[ptx][pty] == true) {
                tiger_stop = true;
                ptx = tx;
                pty = ty;
            }
        }
    }
    dfs(pdx, pdy, d1, ptx, pty, d2);
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int dx, dy, d1, tx, ty, d2;
    while(scanf("%d", &n) != EOF && n)
    {
        scanf("%d%d%d", &dx, &dy, &d1);
        scanf("%d%d%d", &tx, &ty, &d2);
        memset(donkey, false, sizeof(donkey));
        memset(tiger, false, sizeof(tiger));
        meet = stop = false;
        donkey_stop = tiger_stop = false;
        dfs(dx, dy, d1, tx, ty, d2);
    }
    return 0;
}
