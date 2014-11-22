/*
** HDU 2791 Government Help
** Created by Rayn @@ 2014/05/16
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int a[50005];
int main() {
    int n;
    while(scanf("%d",&n))
    {
        if (!n) break;
        for (int i = 0; i < n; i++)
        {
            scanf("%d",&a[i]);
        }
        sort(a,a+n);
        printf("%d-A",a[0]);
        int k=0;
        for (int i = n-1; i >=1; i--,k++)
        {
            printf(" %d-%c",a[i],k&1?'A':'B');
        }
        printf("\n");
    }
    return 0;
}
