/*
** HDU 4938 Seeing People
** Created by Rayn @@ 2014/08/15
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<LL, int> PLLI;
const int MAXN = 100000 + 10;

struct Person
{
    int id;
    long long t, p, w;

    Person() {}
    Person(int id, LL t, LL p, LL w):
        id(id), t(t), p(p), w(w) {}
};

int n, cnt1, cnt2;
int res[MAXN];
long long v1, v2;
long long see[MAXN];
Person p1[MAXN], p2[MAXN];
PLLI q1[MAXN], q2[MAXN];

void gao(Person *a, int n, Person *b, int m, LL v1, LL v2)
{
    for (int i = 0; i < n; ++i) {
        q1[i] = make_pair(a[i].p*v1 - v1*v2*a[i].t, i);
    }
    for (int i = 0; i < m; ++i) {
        q2[i] = make_pair(b[i].p*v2 - v2*v1*b[i].t, i);
    }
    sort(q1, q1+n);
    sort(q2, q2+m);
    for (int i = 0; i < m; ++i) {
        see[i] = q2[i].first;
    }
    for (int i = 0; i < n; ++i) {
        res[a[q1[i].second].id] = upper_bound(see, see+m, q1[i].first + a[q1[i].second].w) - lower_bound(see, see+m, q1[i].first);
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%I64d%I64d", &n, &v1, &v2);
        cnt1 = cnt2 = 0;
        for (int i = 0, type; i < n; ++i)
        {
            LL t, p, w;
            scanf("%d%I64d%I64d%I64d", &type, &t, &p, &w);
            if (type == 1) {
                p1[cnt1++] = Person(i, t, p, w*v1);
            } else if(type == 2) {
                p2[cnt2++] = Person(i, t, p, w*v2);
            }
        }
        gao(p1, cnt1, p2, cnt2, v1, v2);
        gao(p2, cnt2, p1, cnt1, v2, v1);
        printf("Case #%d:\n", ++cases);
        for (int i = 0; i < n; ++i)
        {
            printf("%d\n", res[i]);
        }
    }
    return 0;
}
