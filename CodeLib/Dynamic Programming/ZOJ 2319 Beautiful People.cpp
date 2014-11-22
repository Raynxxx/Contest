/*
** ZOJ 2319 Beautiful People
** Created by Rayn @@ 2014/08/10
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const int INF = 0x3F3F3F3F;

struct Member
{
    int id;
    int s, b;
    Member() {}
    Member(int id, int s, int b) : id(id), s(s), b(b) {}

    bool operator < (const Member& rhs) const {
        return s < rhs.s || (s == rhs.s && b > rhs.b);
    }
    void read(int i) {
        this->id = i;
        scanf("%d%d", &s, &b);
    }
};

int pre[maxn];
int box[maxn];
Member peo[maxn];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            peo[i].read(i + 1);
        }
        sort(peo, peo + n);
        fill(box, box + n + 1, INF);
        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            int k = lower_bound(box + 1, box + n + 1, peo[i].b) - box;
            box[k] = peo[i].b;
            pre[i] = k;
            res = max(res, k);
        }
        printf("%d\n", res);
        for (int i = n - 1; i >= 0; --i)
        {
            if (pre[i] == res)
            {
                printf("%d%c", peo[i].id, (res == 1) ? '\n' : ' ');
                res--;
            }
        }
        if (t > 0)
            puts("");
    }
    return 0;
}
