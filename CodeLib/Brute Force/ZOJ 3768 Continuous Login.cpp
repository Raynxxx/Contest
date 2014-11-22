/*
** ZOJ 3768 Continuous Login
** Created by Rayn @@ 2014/05/10
** ±©Á¦Ã¶¾Ù
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 0x3f3f3f3f
using namespace std;
int a[50000], sz;

void init()
{
    for (int i = 1; (i*(i+1)/2)<=123456789;i++)
    {
        a[i] = i*(i+1)/2;
        sz = i;
    }
    sz++;
}

int main()
{
    init();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        int k = lower_bound(a+1,a+sz,n) - a;
        int flag=0;
        if (a[k]==n)
        {
            flag = 1;
            printf("%d\n",k);
        }
        else
        {
            for (int i = 1; a[i] <= n; i++)
            {
                int l = n - a[i];
                int j = lower_bound(a+1,a+sz,l) - a;
                if (a[j]== l)
                {
                    printf("%d %d\n",i,j);
                    flag = 1;
                    break;
                }

            }
        }
        if (!flag)
        {
            for (int i = 1; a[i]<= n; i++)
            {
                for (int j = 1; a[i]+a[j]<=n && !flag;j++)
                {
                    int l = n - a[i] - a[j];
                    int k = lower_bound(a+1,a+sz,l) - a;
                    if (a[k] == l)
                    {
                        printf("%d %d %d\n",i,j,k);
                        flag = 1;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
