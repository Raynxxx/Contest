/*
** CF 479A Expression
** Created by Rayn @@ 2014/11/10
*/
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int a, b, c;
    while (scanf("%d%d%d", &a, &b, &c) != EOF) {
        int ret = -1;
        ret = max(ret, a + b + c);
        ret = max(ret, a + b * c);
        ret = max(ret, a * b + c);
        ret = max(ret, a * b * c);
        ret = max(ret, a * (b + c));
        ret = max(ret, (a + b) * c);
        printf("%d\n", ret);
    }
    return 0;
}
