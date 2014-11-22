/*
** HDU 1249 三角形
** Created by Rayn @@ 2014/05/05
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
    int n, m;

    scanf("%d", &n);
    while(n--)
    {
        scanf("%d", &m);
        printf("%d\n", m*3*(m-1)+2);
    }
    return 0;
}
