/*
** HDU 4865 Peter's Hobby
** Created by Rayn @@ 2014/07/24
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const double INF = 1e8;

double leaf[3][4] =
{
    {0.60, 0.20, 0.15, 0.05},
    {0.25, 0.30, 0.20, 0.25},
    {0.05, 0.10, 0.35, 0.50}
};
double weather[3][3] =
{
    {0.500, 0.375, 0.125},
    {0.250, 0.125, 0.625},
    {0.250, 0.375, 0.375}
};
const char res[3][10] = {"Sunny", "Cloudy", "Rainy"};

int t, n, cases;
map<string, int> mp;
int humi[55];
int pre[55][5];
double dp[55][5];

void Init()
{
    mp["Dry"] = 0;
    mp["Dryish"] = 1;
    mp["Damp"] = 2;
    mp["Soggy"] = 3;
    cases = 0;
}
void OutPut(int cur, int id)
{
    if(cur == 0)
        return ;
    OutPut(cur-1, pre[cur][id]);
    printf("%s\n", res[id]);
}
void Solve()
{
    int id;
    double maxv, tmp;
    dp[1][0] = 0.63 * leaf[0][humi[1]];
    dp[1][1] = 0.17 * leaf[1][humi[1]];
    dp[1][2] = 0.20 * leaf[2][humi[1]];
    for(int i = 2; i <= n; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            maxv = -INF;
            for(int k = 0; k < 3; ++k)
            {
                tmp = dp[i-1][k] * weather[k][j] * leaf[j][humi[i]];
                if(tmp > maxv)
                {
                    maxv = tmp;
                    id = k;
                }
            }
            dp[i][j] = maxv;
            pre[i][j] = id;
        }
    }
    maxv = -INF;
    for(int i = 0; i < 3; ++i)
    {
        if(dp[n][i] > maxv)
        {
            maxv = dp[n][i];
            id = i;
        }
    }
    printf("Case #%d:\n", ++cases);
    OutPut(n, id);
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    Init();
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        char Humidity[20];
        for(int i = 1; i <= n; ++i)
        {
            scanf("%s", Humidity);
            humi[i] = mp[Humidity];
        }
        Solve();
    }
    return 0;
}
