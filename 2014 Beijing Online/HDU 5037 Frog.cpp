/*
** HDU 5037 Frog
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

const int MAXN = 200005;

int rock[MAXN];


int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        int n, m, l;
        scanf("%d%d%d", &n, &m, &l);
        for(int i = 0; i < n; ++i) {
            rock[i] = nextInt();
        }
        rock[n++] = 0;
        rock[n++] = m;
        sort(rock, rock + n);
        int res = 0, pre = l;
        for(int i = 1; i < n; ++i) {
            int x = (rock[i] - rock[i-1]) % (l + 1);
            int y = (rock[i] - rock[i-1]) / (l + 1);
            if(pre + x >= l + 1) {
                pre = x;
                res += y * 2 + 1;
            } else {
                pre = pre + x;
                res += y * 2;
            }
        }
        printf("Case #%d: %d\n", ++cases, res);
    }
    return 0;
}
