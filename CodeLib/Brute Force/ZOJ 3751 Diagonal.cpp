/*
** ZOJ 3751 Diagonal
** Created by Rayn @@ 2014/07/11
*/
#include <cstdio>

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        printf("%d\n", (n*n-n+2)*(n-1) + (n*n-2*(n-2))/2);
    }
    return 0;
}
