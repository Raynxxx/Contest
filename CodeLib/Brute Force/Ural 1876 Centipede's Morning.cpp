/*
** Ural 1876 Centipede's Morning
** Created by Rayn @@ 2014/05/25
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main()
{
    int a, b;
    scanf("%d%d",&a,&b);
    printf("%d\n", max(40+2*b, 39+2*a));
    return 0;
}
