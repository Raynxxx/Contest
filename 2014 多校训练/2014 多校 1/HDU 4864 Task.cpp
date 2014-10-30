/*
** HDU 4864 Task
** Created by Rayn @@ 2014/07/24
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;

struct Node
{
    int x, y;
    bool operator < (const Node& rhs) const
    {
        return x > rhs.x || (x == rhs.x && y > rhs.y);
    }
};
Node a[100005], b[100005];
map<int, int> mp;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF)
    {
        mp.clear();
        for (int i = 0; i < n; i++)
            scanf("%d%d", &a[i].x, &a[i].y);
        for (int i = 0; i < m; i++)
            scanf("%d%d", &b[i].x, &b[i].y);
        sort(a, a + n);
        sort(b, b + m);

        int j = 0;
        int num = 0;
        long long money = 0;
        for (int i = 0; i < m; i++)
        {
            while (j < n && a[j].x >= b[i].x)
            {
                mp[a[j].y]++;
                j++;
            }
            map<int, int>::iterator it = mp.lower_bound(b[i].y);
            if (it != mp.end())
            {
                num++;
                money += b[i].x * 500 + b[i].y * 2;
                int t = it->first;
                mp[t]--;
                if (mp[t] == 0)
                    mp.erase(t);
            }
        }
        printf("%d %I64d\n", num, money);
    }
    return 0;
}
