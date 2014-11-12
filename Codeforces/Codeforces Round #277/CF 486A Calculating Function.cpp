/*
** CF 486A Calculating Function
** Created by Rayn @@ 2014/11/12
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 512;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Long n;
    while (scanf("%I64d", &n) != EOF) {
        Long ret = 0;
        if (n & 1) {
            ret = (n / 2) - n;
        } else {
            ret = (n / 2);
        }
        printf("%I64d\n", ret);
    }
    return 0;
}
 