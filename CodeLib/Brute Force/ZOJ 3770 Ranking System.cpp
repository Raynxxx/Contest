/*
** ZOJ 3770 Ranking System
** Created by Rayn @@ 2014/05/10
** Ä£Äâ
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 2005;

struct Member{
    int num;
    int ID, date, score;
    int degree;
} man[MAX];

int cmp1(const Member& A, const Member &B)
{
    if(A.score != B.score)
        return A.score < B.score;
    if(A.date != B.date)
        return A.date > B.date;
    else
        return A.ID > B.ID;
}
int cmp2(const Member& A, const Member &B)
{
    return A.num < B.num;
}
int main() {

#ifdef HotWhite
    //freopen("in.txt", "r", stdin);
#endif

    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        memset(man, 0, sizeof(man));
        scanf("%d", &n);
        int cnt = 0;
        for(int i=0; i<n; ++i)
        {
            int y,m,d;
            scanf("%d %d/%d/%d %d", &man[i].ID, &y,&m,&d, &man[i].score);
            man[i].num = i+1;
            man[i].date = d + m*100 + y*10000;
            if(man[i].score > 0)
                cnt++;
        }
        sort(man, man+n, cmp1);
        /*
        for(int i=0; i<n; ++i)
        {
            printf("%d %d %d\n", man[i].ID, man[i].date, man[i].score);
        }
        //*/
        int lv[7];
        lv[1] = n - cnt;
        lv[3] = (int)(cnt * 0.3);
        lv[4] = (int)(cnt * 0.2);
        lv[5] = (int)(cnt * 0.07);
        lv[6] = (int)(cnt * 0.03);
        lv[2] = cnt-lv[3]-lv[4]-lv[5]-lv[6];
        for(int i=0, k=1; i<n; ++k)
        {
            for(int j=1; j<=lv[k]; ++j, ++i)
            {
                man[i].degree = k;
            }
        }
        sort(man, man+n, cmp2);
        for(int i=0; i<n; ++i)
        {
            printf("LV%d\n", man[i].degree);
        }
    }
    return 0;
}
