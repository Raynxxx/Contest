/*
** UVA 10344 23 out of 5
** Created by Rayn @@ 2014/04/25
** È«ÅÅÁÐºÍDFS
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int flag, num[10];

void DFS(int ans, int cur)
{
    if(ans == 23 && cur == 5)
    {
        flag = 1;
        return ;
    }
    if(cur >= 5)
        return ;
    DFS(ans+num[cur], cur+1);
    DFS(ans-num[cur], cur+1);
    DFS(ans*num[cur], cur+1);
}
int main()
{
    while(1)
    {
        int zero = 0;
        for(int i=0; i<5; ++i)
        {
            scanf("%d", &num[i]);
            if(num[i] == 0)
                zero += 1;
        }
        if(zero == 5)
            break;

        flag = 0;
        sort(num, num+5);
        do{
            DFS(num[0], 1);
            if(flag)
                break;
        }while(next_permutation(num, num+5));

        if(flag)
            printf("Possible\n");
        else
            printf("Impossible\n");
    }
	return 0;
}
