/*
** HDU 4972 A simple dynamic programming problem
** Created by Rayn @@ 2014/08/29
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 100010;

int n;
int a[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        bool flag = true;
        a[0] = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            if(abs(a[i] - a[i-1]) > 3) flag = false;
            if(a[i] == a[i-1] && a[i] != 1) flag = false;
        }
        if(!flag) {
            printf("Case #%d: 0\n", ++cases);
            continue;
        }
        int ans = 0;
        for(int i = 2; i <= n; i++) {
            if(a[i] == 1 && a[i-1] == 2) {
                ans++;
            } else if(a[i] == 2 && a[i-1] == 1) {
                ans++;
            }
        }
        printf("Case #%d: ", ++cases);
        if(a[n] == 0) {
            printf("%d\n", ans + 1);
        } else {
            printf("%d\n", 2*ans + 2);
        }
    }
    return 0;
}
