/*
** HDU 5036 Explosion
** Created by Rayn @@ 2014/09/22
*/
#include <cmath>
#include <cstdio>
#include <bitset>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;

inline int nextInt()
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    int ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    if(flag) ret = -ret;
    return ret;
}

const int MAXN = 1005;

bitset<MAXN> edge[MAXN];

void MakeGraph(int n)
{
    for(int i = 1; i <= n; ++i) {
        edge[i].reset();
        edge[i][i] = 1;
    }
    for(int i = 1; i <= n; ++i) {
        int k, v;
        k = nextInt();
        for(int j = 1; j <= k; ++j) {
            v = nextInt();
            edge[i][v] = 1;
        }
    }
}
double GaoGraph(int n)
{
    MakeGraph(n);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(edge[j][i]) {
                edge[j] |= edge[i];
            }
        }
    }
    double res = 0.0;
    for(int i = 1; i <= n; ++i) {
        int cnt = 0;
        for(int j = 1; j <= n; ++j) {
            if(edge[j][i]) {
                cnt++;
            }
        }
        res += 1.0 / cnt;
    }
    return res;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        int n;
        scanf("%d", &n);
        printf("Case #%d: %.5f\n", ++cases, GaoGraph(n));
    }
    return 0;
}
