/*
** UVA 1203 Argus
** Created by Rayn @@ 2014/3/30
** 优先队列处理多路归并
*/
#include <cstdio>
#include <queue>
using namespace std;

struct item{
    int Qnum, period;
    int time;
    bool operator < (const item &a) const{
        return time > a.time || (time == a.time && Qnum > a.Qnum);
    }
};

int main()
{
    #ifdef _Rayn
        freopen("in.txt", "r", stdin);
    #endif

    priority_queue<item> pque;
    char s[20];

    while(scanf("%s", s) != EOF && s[0] != '#')
    {
        item tmp;
        scanf("%d%d", &tmp.Qnum, &tmp.period);
        tmp.time = tmp.period;
        pque.push(tmp);
    }

    int k;
    scanf("%d", &k);
    while(k--)
    {
        item now = pque.top();
        pque.pop();
        printf("%d\n", now.Qnum);
        now.time += now.period;
        pque.push(now);
    }
    return 0;
}
