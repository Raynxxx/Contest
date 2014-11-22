/*
** POJ 2632 Crashing Robots
** Created by Rayn @@ 2014/04/16
** 坑爹的模拟题，脑壳不清晰的就要被坑惨了
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 110;

struct pos{
    int id, dir; /* N-0,E-1,S-2,W-3 */
    int x, y;
};

pos rob[MAX];
int HaveRob[MAX][MAX];
int K, A, B, N, M;
int mov[4][2] = {{0, 1},{1, 0},{0, -1},{-1, 0}};

int DirToNum(char ch)
{
    switch(ch)
    {
        case 'N':
            return 0;
        case 'E':
            return 1;
        case 'S':
            return 2;
        case 'W':
            return 3;
        default:
            break;
    }
    return -1;
}
int CrashWall(int x, int y)
{
    if(x<=0 || x>A || y<=0 || y>B)
        return 1;
    return 0;
}
int main()
{
    char str[10], act[10];
    int num, rep;

    scanf("%d", &K);
    while(K--)
    {
        memset(HaveRob, 0, sizeof(HaveRob));
        scanf("%d%d%d%d", &A, &B, &N, &M);
        for(int i=1; i<=N; ++i)
        {
            scanf("%d %d %s", &rob[i].x, &rob[i].y, str);
            rob[i].dir = DirToNum(str[0]);
            rob[i].id = i;
            HaveRob[rob[i].x][rob[i].y] = i;
        }

        int first = 1, ok = 1, tx, ty;
        while(M--)
        {
            scanf("%d %s %d", &num, act, &rep);
            if(!first)
                continue;
            while(rep--)
            {
                if(act[0] == 'L')
                {
                    rob[num].dir = (rob[num].dir + 3) % 4;
                }
                if(act[0] == 'R')
                {
                    rob[num].dir = (rob[num].dir + 1) % 4;
                }
                if(act[0] == 'F')
                {
                    tx = rob[num].x + mov[rob[num].dir][0];
                    ty = rob[num].y + mov[rob[num].dir][1];
                    if(CrashWall(tx, ty) && first)
                    {
                        printf("Robot %d crashes into the wall\n", num);
                        first = ok = 0;
                    }
                    if(HaveRob[tx][ty] && first)
                    {
                        printf("Robot %d crashes into robot %d\n", num, HaveRob[tx][ty]);
                        first = ok = 0;
                    }
                    HaveRob[rob[num].x][rob[num].y] = 0;
                    rob[num].x = tx;
                    rob[num].y = ty;
                    HaveRob[rob[num].x][rob[num].y] = num;
                }
            }
        }
        if(ok)
            printf("OK\n");
    }
    return 0;
}
