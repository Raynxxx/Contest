/*
** POJ 1664 ·ÅÆ»¹û
** Created by Rayn @@ 2014/04/13
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int PutApple(int m, int n)
{
    if(m < n)
        return PutApple(m, m);
    if(m<=1 || n==1)
        return 1;
    return PutApple(m-n, n) + PutApple(m, n-1);
}
int main()
{
    int t, n, m;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &m, &n);
        printf("%d\n", PutApple(m, n));
    }
    return 0;
}
