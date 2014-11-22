/*
** HDU 4883 TIANKENG's restaurant
** Created by Rayn @@ 2014/07/27
*/
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 20010;

struct Node
{
    int num;
    double time;
    int flag;
    Node() {}
    Node(int num, double time, int flag):
        num(num), time(time), flag(flag) {}
    bool operator < (const Node& rhs) const
    {
        if(time != rhs.time)
            return time < rhs.time;
        else
            return flag < rhs.flag;
    }
};

Node peo[MAXN];

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn
    int t, n;
    int xi, st1, st2, ed1, ed2;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        int cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            scanf("%d %d:%d %d:%d", &xi, &st1, &st2, &ed1, &ed2);
            peo[cnt++] = Node(xi, st1+0.01*st2, +1);
            peo[cnt++] = Node(xi, ed1+0.01*ed2, -1);
        }
        sort(peo, peo+cnt);
        int now = 0, chair = 0;
        for(int i = 0; i < cnt; ++i)
        {
            now += peo[i].num * peo[i].flag;
            chair = max(chair, now);
        }
        printf("%d\n", chair);
    }
    return 0;
}
