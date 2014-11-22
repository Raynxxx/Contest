/*
** ZOJ 3643 Keep Deleting
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char sta[512010];
char a[300], b[512010];

int main() {

#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    while(scanf("%s%s", a, b) != EOF)
    {
        int lena = strlen(a);
        int lenb = strlen(b);
        int i = 0, top = 0;
        int times = 0;
        while(i < lenb)
        {
            sta[top++] = b[i++];
            sta[top] = '\0';
            if(top >= lena && strcmp(sta+top-lena, a) == 0)
            {
                times++;
                top -= lena;
            }
        }
        printf("%d\n", times);
    }
    return 0;
}
