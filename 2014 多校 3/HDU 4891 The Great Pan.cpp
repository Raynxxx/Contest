/*
** HDU 4891 The Great Pan
** Created by Rayn @@ 2014/08/18
*/
#include<iostream>
#include<string>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int doge = 1e5;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int n;
    char ch;
    while(scanf("%d%*c", &n) != EOF)
    {
        int s1 = 0, s2 = 0;
        long long ans = 1;
        int line = 0;
        while(line < n)
        {
            ch = getchar();
            if(ch == '\n') {
                line++;
            }
            else if(ans > (LL)doge) {
                continue;
            }
            else if(ch == '{') {
                s1 = 1;
            }
            else if(ch == '|' && s1 > 0) {
                s1++;
            }
            else if(ch == '}') {
                if(s1 != 0)
                    ans *= (LL)s1;
                s1 = 0;
            }
            else if(ch == '$' && s2 == 0) {
                s2 = 1;
            }
            else if(ch == '$') {
                if(s2 != 0)
                    ans *= (LL)s2;
                s2 = 0;
            }
            else if(ch == ' ' && s2 > 0) {
                s2++;
            }
            else if(s2 > 0) {
                ans *= (LL)s2;
                s2 = 1;
            }
        }
        if(ans > doge)
            printf("doge\n");
        else
            printf("%I64d\n", ans);
    }
    return 0;
}
