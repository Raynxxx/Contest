/*
** HDU 2768 Cat vs. Dog
** Created by Rayn @@ 2014/07/25
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 510;

struct Voter
{
    char like[10];
    char hate[10];
};

int CatN, DogN;
bool used[MAXN];
int link[MAXN];
int maps[MAXN][MAXN];
Voter CatLove[MAXN], DogLove[MAXN];

bool Find(int u)
{
    for(int i = 1; i < DogN; ++i)
    {
        if(!used[i] && maps[u][i])
        {
            used[i] = true;
            if(link[i] == -1 || Find(link[i]))
            {
                link[i] = u;
                return true;
            }
        }
    }
    return false;
}
int MaxMatch()
{
    int cnt = 0;
    memset(link, -1, sizeof(link));
    for(int i = 1; i < CatN; ++i)
    {
        memset(used, false, sizeof(used));
        if(Find(i))
            cnt++;
    }
    return cnt;
}


int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, C, D, V;
    char like[10], hate[10];

    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &C, &D, &V);
        CatN = 1; DogN = 1;
        for(int i = 1; i <= V; ++i)
        {
            scanf("%s %s", like, hate);
            if(like[0] == 'C')
            {

                strcpy(CatLove[CatN].like, like);
                strcpy(CatLove[CatN].hate, hate);
                CatN++;
            }
            else
            {
                strcpy(DogLove[DogN].like, like);
                strcpy(DogLove[DogN].hate, hate);
                DogN++;
            }
        }
        memset(maps, 0, sizeof(maps));
        for(int i = 1; i < CatN; ++i)
        {
            for(int j = 1; j < DogN; ++j)
            {
                if(strcmp(CatLove[i].like, DogLove[j].hate) == 0 ||
                   strcmp(CatLove[i].hate, DogLove[j].like) == 0)
                {
                    maps[i][j] = 1;
                }
            }
        }
        printf("%d\n", V - MaxMatch());
    }
    return 0;
}
