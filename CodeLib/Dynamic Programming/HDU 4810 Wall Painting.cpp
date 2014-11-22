/*
** HDU 4810 Wall Painting
** Created by Rayn @@ 2014/09/26
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
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
const int BIT = 32;
const int INF = 0x3F3F3F3F;
const int MOD = (int)1e6 + 3;

int comb[MAXN][MAXN];
int pow2[BIT];
int bit[BIT];

void Init() {
    comb[0][0] = 1;
    for(int i = 1; i < MAXN; ++i) {
        comb[i][0] = comb[i][i] = 1;
        for(int j = 1; j < i; ++j) {
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
            comb[i][j] %= MOD;
        }
    }
    pow2[0] = 1;
    for(int i = 1; i < BIT; ++i) {
        pow2[i] = (pow2[i-1] * 2) % MOD;
    }
}
void Gao(int x) {
    int index = 0;
    while(x) {
        if(x & 1) bit[index]++;
        index++;
        x >>= 1;
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Init();
    int n;
    while(scanf("%d", &n) != EOF)
    {
        memset(bit, 0, sizeof(bit));
        for(int i = 0; i < n; ++i) {
            Gao(nextInt());
        }
        for(int d = 1; d <= n; ++d) {
            LL ret = 0;
            for(int i = 0; i < BIT; ++i) {
                for(int j = 1; j <= d; j += 2) {
                    LL t = ((LL)comb[bit[i]][j] * comb[n-bit[i]][d-j] * pow2[i]) % MOD;
                    ret = (ret + t) % MOD;
                }
            }
            printf("%I64d%c", ret, (d == n)? '\n' : ' ');
        }
    }
    return 0;
}
