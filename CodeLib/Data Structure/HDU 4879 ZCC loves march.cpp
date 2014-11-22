/*
** HDU 4879 ZCC loves march
** Created by Rayn @@ 2014/08/18
*/
#include <cstdio>
#include <map>
#include <set>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#define MOD 1000000007
using namespace std;
typedef long long LL;
const int MAXN = 200010;

template <typename T>
inline void readNumber(T& x)
{
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        ch = getchar();
    }
    x = 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
}
struct Troop
{
    LL x, y, num;
    Troop() {}
    Troop(LL x, LL y, LL num): x(x), y(y), num(num) {}
};

long long pa[MAXN];
Troop troop[MAXN];
map<LL, set<LL> > setx;
map<LL, set<LL> > sety;
set<LL>::iterator it;

void Init()
{
    setx.clear();
    sety.clear();
}
LL FindSet(LL x)
{
    if(pa[x] != x)
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    LL n, m, t, a, b, x, y, d;
    char op[12];
    while(scanf("%I64d%I64d", &n, &m) != EOF)
    {
        Init();
        for(int i = 1; i <= n; ++i)
        {
            readNumber(x);
            readNumber(y);
            //scanf("%I64d%I64d", &x, &y);
            troop[i] = Troop(x, y, 1);
            pa[i] = i;
            setx[x].insert(i);
            sety[y].insert(i);
        }
        LL cnt = n+1, ans = 0, num = 0;
        scanf("%I64d", &t);
        while(t--)
        {
            scanf("%s", op);
            if(op[0] != 'Q') {
                readNumber(a);
                readNumber(d);
                //scanf("%I64d%I64d", &a, &d);
                a ^= ans;
                LL root = FindSet(a);
                x = troop[root].x;
                y = troop[root].y;
                troop[root].num--;

                if(troop[root].num == 0) {
                    setx[x].erase(root);
                    sety[y].erase(root);
                }
                if (op[0] == 'U') {
                    troop[a] = Troop(x-d, y, 1);
                    pa[a] = a;
                    setx[x-d].insert(a);
                    sety[y].insert(a);
                } else if(op[0] == 'L') {
                    troop[a] = Troop(x, y-d, 1);
                    pa[a] = a;
                    setx[x].insert(a);
                    sety[y-d].insert(a);
                } else if(op[0] == 'D') {
                    troop[a] = Troop(x+d, y, 1);
                    pa[a] = a;
                    setx[x+d].insert(a);
                    sety[y].insert(a);
                } else if(op[0] == 'R') {
                    troop[a] = Troop(x, y+d, 1);
                    pa[a] = a;
                    setx[x].insert(a);
                    sety[y+d].insert(a);
                }
            } else if(op[0] == 'Q') {
                readNumber(a);
                //scanf("%I64d", &a);
                a ^= ans;
                LL root = FindSet(a);
                x = troop[root].x;
                y = troop[root].y;

                num = ans = 0;
                for(it = setx[x].begin(); it != setx[x].end(); ++it)
                {
                    num += troop[*it].num;
                    LL tmp = abs(troop[*it].y - y) % MOD;
                    ans = (ans + ((tmp * tmp) % MOD * troop[*it].num) % MOD) % MOD;
                    pa[*it] = cnt;
                    sety[troop[*it].y].erase(*it);
                }
                for(it = sety[y].begin(); it != sety[y].end(); ++it)
                {
                    num += troop[*it].num;
                    LL tmp = abs(troop[*it].x - x) % MOD;
                    ans = (ans + ((tmp * tmp) % MOD * troop[*it].num) % MOD) % MOD;
                    pa[*it] = cnt;
                    setx[troop[*it].x].erase(*it);
                }
                pa[cnt] = cnt;
                troop[cnt] = Troop(x, y, num);
                setx[x].clear();
                setx[x].insert(cnt);
                sety[y].clear();
                sety[y].insert(cnt);
                cnt++;
                printf("%I64d\n", ans);
            }
        }
    }
    return 0;
}
