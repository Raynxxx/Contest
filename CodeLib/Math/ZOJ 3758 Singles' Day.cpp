/*
** ZOJ 3758 Singles' Day
** Created by Rayn @@ 2014/08/27
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ULL;

int N, B;

bool check(ULL M)
{
    if(M < 2) return false;
    if(M == 2) return true;
    for(ULL i = 2; i * i <= M; ++i)
    {
        if(M % i == 0) return false;
    }
    return true;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d", &B, &N) != EOF)
    {
        ULL M = 0;
        while(N--) {
            M = M * B + 1;
        }
        if(check(M))
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}

