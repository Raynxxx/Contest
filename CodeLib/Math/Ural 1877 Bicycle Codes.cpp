/*
** Ural 1877 Bicycle Codes
** Created by Rayn @@ 2014/05/25
*/
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    char str[5];
    int x, y;

    scanf("%s", str);
    sscanf(str, "%d", &x);
    scanf("%s", str);
    sscanf(str, "%d", &y);

    if(x%2==1 && y%2==0)
        puts("no");
    else
        puts("yes");

    return 0;
}
