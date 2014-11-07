/*
** CodeForces 447D DZY Loves Modification
** Created by Rayn @@ 2014/09/08
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1010;
const int MAXK = 1000010;
const LL INF = 1LL << 60;

int arr[MAXN][MAXN];
LL dp1[MAXK], dp2[MAXK];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m, k, p;
    while(scanf("%d%d%d%d", &n, &m, &k, &p) != EOF)
    {
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                scanf("%d", &arr[i][j]);
            }
        }
        priority_queue<LL> row;
        for(int i = 1; i <= n; ++i) {
            LL sum = 0;
            for(int j = 1; j <= m; ++j) {
                sum += arr[i][j];
            }
            row.push(sum);
        }
        priority_queue<LL> col;
        for(int j = 1; j <= m; ++j) {
            LL sum = 0;
            for(int i = 1; i <= n; ++i) {
                sum += arr[i][j];
            }
            col.push(sum);
        }
        dp1[0] = dp2[0] = 0LL;
        for(int i = 1; i <= k; ++i) {
            LL sum = row.top();
            row.pop();
            dp1[i] = dp1[i-1] + sum;
            sum -= (LL)p * m;
            row.push(sum);
        }
        for(int i = 1; i <= k; ++i) {
            LL sum = col.top();
            col.pop();
            dp2[i] = dp2[i-1] + sum;
            sum -= (LL)p * n;
            col.push(sum);
        }
        LL ret = -INF;
        for(int i = 0; i <= k; ++i) {
            ret = max(ret, dp1[i] + dp2[k-i] - (LL)i* (k-i) * p);
        }
        printf("%I64d\n", ret);
    }
    return 0;
}
