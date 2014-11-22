/*
** ZOJ 3767 Elevator
** Created by Rayn @@ 2014/05/10
** ˮ�⣬ģ��
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {

    int t;
    scanf("%d", &t);
    while(t--)
    {
        int n, m, sum = 0;
        scanf("%d%d", &n, &m);
        for (int i=0; i<n; i++)
        {
            int x;
            scanf("%d", &x);
            sum += x;
        }
        if (sum > m)
        {
            printf("Warning\n");
        }
        else
        {
            printf("Safe\n");
        }
    }
    return 0;
}
