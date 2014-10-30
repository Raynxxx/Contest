/*
** HDU 4968 Improving the GPA
** Created by Rayn @@ 2014/08/27
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
const double INF = 1e12;

double GPA[105];
double dp1[12][1010];
double dp2[12][1010];

void Init()
{
    for(int i = 60; i <= 69; ++i)  GPA[i] = 2.0;
    for(int i = 70; i <= 74; ++i)  GPA[i] = 2.5;
    for(int i = 75; i <= 79; ++i)  GPA[i] = 3.0;
    for(int i = 80; i <= 84; ++i)  GPA[i] = 3.5;
    for(int i = 85; i <= 100; ++i) GPA[i] = 4.0;

    for(int i = 1; i <= 10; ++i) {
        fill(dp1[i], dp1[i] + 1010, 0.0);
        fill(dp2[i], dp2[i] + 1010, INF);
    }
    for(int i = 60; i <= 100; ++i) {
        dp1[1][i] = dp2[1][i] = GPA[i];
    }
    for(int i = 2; i <= 10; ++i) {
        for(int j = 60; j <= 100; ++j) {
            for(int k = j; k <= 100*i; ++k) {
                if(dp1[i-1][k-j] != 0) {
                    dp1[i][k] = max(dp1[i][k], dp1[i-1][k-j] + GPA[j]);
                }
                if(dp2[i-1][k-j] != INF) {
                    dp2[i][k] = min(dp2[i][k], dp2[i-1][k-j] + GPA[j]);
                }
            }
        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Init();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int aver, n;
        scanf("%d%d", &aver, &n);
        printf("%.4f %.4f\n", dp2[n][aver*n]/n, dp1[n][aver*n]/n);
    }
    return 0;
}
