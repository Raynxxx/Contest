/*
** HDU 4947 GCD Array
** Created by Rayn @@ 2014/08/26
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 200020;

int L, Q;
bool vis[MAXN];
int prime[MAXN];
int mu[MAXN];
LL data[MAXN];
vector<int> fact[MAXN];

inline int nextInt()
{
    char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();

    int x = 0;
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x;
}
inline int Lowbit(int x)
{
    return x & (-x);
}
inline void Add(int x, int val)
{
    while(x <= L)
    {
        data[x] += val;
        x += Lowbit(x);
    }
}
inline LL getSum(int x)
{
    LL ret = 0;
    while(x > 0)
    {
        ret += data[x];
        x -= Lowbit(x);
    }
    return ret;
}

void Mobius()
{
    memset(vis, false, sizeof(vis));
    mu[1] = 1;
    int tot = 0;
    for(int i = 2; i < MAXN; ++i)
    {
        if(!vis[i])
        {
            prime[tot++] = i;
            mu[i] = -1;
        }
        for(int j = 0; j < tot; ++j)
        {
            if(i * prime[j] >= MAXN) break;
            vis[i * prime[j]] = true;
            if(i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
}
void Init()
{
    Mobius();
    for(int i = 1; i < MAXN; ++i) {
        for(int j = i; j < MAXN; j += i) {
            fact[j].push_back(i);
        }
    }
}
void Update(int n, int d, int v)
{
    if(n % d != 0) return ;
    n = n/d;
    for(int i = 0; i < (int) fact[n].size(); ++i)
    {
        int p = fact[n][i];
        Add(p*d, mu[p]*v);
    }
}
LL Query(int pos)
{
    LL ret = 0;
    LL pre = 0, cur = 0;
    for(int i = 1, last; i <= pos; i = last + 1)
    {
        last = pos / (pos / i);
        pre = cur;  //·Ö¿é¼ÓËÙ
        cur = getSum(last);
        ret += (LL)(pos / i) * (cur - pre);
    }
    return ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Init();
    int cases = 0;
    while(scanf("%d%d", &L, &Q) != EOF && (L && Q))
    {
        memset(data, 0, sizeof(data));
        printf("Case #%d:\n", ++cases);
        while(Q--)
        {
            int op;
            scanf("%d", &op);
            if(op == 1) {
                int n, d, v;
                n = nextInt();
                d = nextInt();
                v = nextInt();
                //scanf("%d%d%d", &n, &d, &v);
                Update(n, d, v);
            } else if(op == 2) {
                int x;
                x = nextInt();
                //scanf("%d", &x);
                printf("%I64d\n", Query(x));
            }
        }
    }
    return 0;
}
