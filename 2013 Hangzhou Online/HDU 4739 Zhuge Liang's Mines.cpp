/*
** HDU 4739 Zhuge Liang's Mines
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
typedef vector<int> VI;
const int MAXN = 21;

struct Point
{
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    bool operator < (const Point& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
    void read() {
        scanf("%d%d", &x, &y);
    }
};


Point mine[MAXN];
int dp[1 << 20];
vector<VI> Squre;

bool Judge(int a, int b, int c, int d)
{
    if(mine[a].x == mine[b].x && mine[a].y == mine[b].y)
        return false;
    if(mine[a].x != mine[b].x || mine[c].x != mine[d].x)
        return false;
    if(mine[a].y != mine[c].y || mine[b].y != mine[d].y)
        return false;
    if(abs(mine[a].x - mine[c].x) != abs(mine[a].y - mine[b].y))
        return false;
    return true;
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF && (n != -1))
    {
        for(int i = 0; i < n; ++i) {
            mine[i].read();
        }
        sort(mine, mine + n);
        Squre.clear(); Squre.resize(n);
        for(int i = 0; i < n; ++i) {
            for(int j = i+1; j < n; ++j) {
                for(int k = j+1; k < n; ++k) {
                    for(int l = k+1; l < n; ++l) {
                        if(Judge(i, j, k, l)) {
                            int status = 0;
                            status |= (1 << i);
                            status |= (1 << j);
                            status |= (1 << k);
                            status |= (1 << l);
                            Squre[i].push_back(status);
                        }
                    }
                }
            }
        }
        int all = (1 << n) - 1;
        memset(dp, 0, sizeof(dp));
        for(int s = 0; s <= all; ++s) {
            for(int i = 0; i < n; ++i) {
                if((s & (1 << i)) == 0) continue;
                vector<int>::iterator sub;
                for(sub = Squre[i].begin(); sub != Squre[i].end(); ++sub) {
                    if((s | (*sub)) == s)
                        dp[s] = max(dp[s], dp[s^(*sub)] + 4);
                }
            }
        }
        printf("%d\n", dp[all]);
    }
    return 0;
}
