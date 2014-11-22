/*
** ZOJ 3653 Sleeper's Schedule
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 0x3F3F3F3F;

vector<pair<int, int> > e[11000];
int dp[11000][150];
int n, t, k, l;
int st, ed, val;

void Init()
{
    for(int i = 0; i < 11000; ++i) {
        e[i].clear();
        for(int j = 0; j < 150; ++j) {
            dp[i][j] = -INF;
        }
    }
}
void checkmax(int& a, int b)
{
    a = (a > b)? a : b;
}
int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        Init();
        scanf("%d%d%d%d", &n, &t, &k, &l);
        for(int i = 0; i < n; ++i)
        {
            scanf("%d%d%d", &st, &ed, &val);
            e[st].push_back(make_pair(ed, val));
        }
        int ans = 0;
        dp[0][0] = 0;
        for(int i = 0; i < 10100; ++i)
        {
            for(int j = 0; j <= t+l; ++j)
            {
                if(dp[i][j] > -INF)
                {
                    //time j+1 : wake up
                    if(j < t + l)
                        checkmax(dp[i+1][j+1], dp[i][j]);
                    // make event
                    for(int m = 0; m < (int) e[i].size(); m++)
                    {
                        st = i;
                        ed = e[i][m].first;
                        val = e[i][m].second;
                        int len = j + ed - st;
                        if(len > t + l)
                            continue;
                        checkmax(dp[ed][len], dp[i][j] + val);
                    }
                    // time j+1 : sleep k time unit, minus dt^2
                    if(j >= t)
                    {
                        checkmax(dp[i+k+j-t][0], dp[i][j] - (j-t)*(j-t));
                    }
                }
            }
            checkmax(ans, dp[i][0]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
