/*
** POJ 2388 Who's in the Middle
** Created by Rayn @@ 2014/3/24
** ¼òµ¥¿ìÅÅ¾ÍOK
*/
#include <cstdio>
#include <algorithm>
using namespace std;
int arr[10010];

int main()
{
    int n;
    while(scanf("%d", &n) != EOF)
    {
        for(int i=0; i<n; ++i)
            scanf("%d", &arr[i]);
        sort(arr, arr+n);
        printf("%d", arr[n/2]);
    }
    return 0;
}
