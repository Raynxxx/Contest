/*
** ZOJ 3816 Generalized Palindromic Number
** Created by Rayn @@ 2014/09/18
*/
#include <map>
#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <bitset>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 24;

long long N;
char num[MAXN];
int len, lnum[MAXN], rnum[MAXN];

LL getNumber(int l, int r)
{
    LL ret = 0;
    for(int i = 0; i < l; i++) {
        ret = ret * 10 + lnum[i];
    }
    for(int i = r-1; i >= 0; i--) {
        ret = ret * 10 + rnum[i];
    }
    if(ret < N) return ret;
    return -1;
}
LL Gao(int l, int r, int eq)
{
    if(l + r >= len)
        return getNumber(l, r);
    LL ret = -1;
    int m = eq? num[l] - '0' : 9;
    for(int i = m; i >= 0; i--) {
        lnum[l] = i;
        if((l == 0 || lnum[l] != lnum[l-1]) && (i || l) && (l + r + 1 < len)) {
            for(int k = 1; l + r + k <= len; ++k) {
                rnum[r+k-1] = i;
                ret = max(ret, Gao(l+1, r+k, (eq && i == m)));
            }
        } else {
            ret = max(ret, Gao(l+1, r, (eq && i == m)));
        }
        if(ret != -1) {
            return ret;
        }
    }
    return ret;
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%lld", &N);
        sprintf(num, "%lld", N);
        len = strlen(num);
        printf("%lld\n", Gao(0, 0, 1));
    }
    return 0;
}
