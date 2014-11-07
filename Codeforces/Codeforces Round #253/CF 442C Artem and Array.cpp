/*
** CF 442C Artem and Array
** Created by Rayn @@ 2014/10/04
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 500005;

int box[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF) {
        long long ret = 0;
        int top = -1;
        for(int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            while(top >= 1 && box[top-1] >= box[top] && x > box[top]) {
                ret += min(box[top-1], x);
                --top;
            }
            box[++top] = x;
        }
        sort(box, box + top + 1);
        for(int i = 0; i <= top - 2; ++i) {
            ret += box[i];
        }
        printf("%I64d\n", ret);
    }
    return 0;
}
