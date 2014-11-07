/*
** CodeForces 447B DZY Loves Strings
** Created by Rayn @@ 2014/07/13
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
const int MAXN = 1010;

map<char, int> mp;
char str[MAXN];

int main()
{
    int k, val;
    while(scanf("%s%d", str, &k) != EOF)
    {
        int maxval = -1;
        for(int i = 0; i < 26; ++i)
        {
            scanf("%d", &val);
            mp['a' + i] = val;
            if(val > maxval)
                maxval = val;
        }
        int i, ans = 0;
        int len = strlen(str);
        for(i = 0; i < len; ++i)
        {
            ans += mp[str[i]] * (i + 1);
        }
        for( ; i < len + k; ++i)
        {
            ans += maxval * (i + 1);
        }
        printf("%d\n", ans);
    }
    return 0;
}
