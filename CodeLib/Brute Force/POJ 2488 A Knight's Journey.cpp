/*
** POJ 2488 A Knight's Journey
** Created by Rayn @@ 2014/05/09
** DFS搜索,看来自己搜索的功力还是不够
*/
#include <cstdio>
#include <cstring>

int p, q, sign;
int vis[10][10]; //标记
int px[64],py[64];  //记录行进路线
int dir[8][2] = {
    {-1,-2},{ 1,-2},{-2,-1},{ 2,-1},
    {-2, 1},{ 2, 1},{-1, 2},{ 1, 2}
};
/*  dir[8][2]
** knight前进步调
** lexicographically - 字典序的
** 这么难的单词唬弄啊！！
*/

void DFS(int x, int y, int step)
{
    if(step == p*q)
    {
        sign = 1;
        return ;
    }
    for(int i=0; i<8 && !sign; ++i)
    {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        if(!vis[tx][ty] && tx >= 0 && tx < p && ty >= 0 && ty < q)
        {
            px[step] = tx;
            py[step] = ty;
            vis[tx][ty] = 1;
            DFS(tx, ty, step+1);
            vis[tx][ty] = 0;
        }
    }
}
int main()
{
    int i, n, cases = 0;

    scanf("%d", &n);
    while(n--)
    {
        memset(vis, 0, sizeof(vis));
        memset(px, 0, sizeof(px));
        memset(py, 0, sizeof(py));

        scanf("%d%d", &p, &q);

        printf("Scenario #%d:\n", ++cases);

        vis[0][0] = 1;
        sign = 0;
        DFS(0,0,1);
        if(sign)
        {
            for(int i=0; i<p*q; ++i)
                printf("%c%d",'A'+py[i], px[i]+1);
        }
        else
        {
            printf("impossible");
        }
        printf("\n\n");
    }
	return 0;
}
