/*
** HDU 4262 Juggler
** Created by Rayn @@ 2014/09/02
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
typedef long long LL;
const int MAXN = 100010;
const int INF = 0x3F3F3F3F;

template <typename T>
inline void readNumber(T& ret)
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
}

struct Operation
{
    int id;
    int order;
    bool operator < (const Operation& p) const {
        return order < p.order;
    }
};

int N;
int tree[MAXN];
int pre[MAXN], next[MAXN];
Operation op[MAXN];

inline int LowBit(int x)
{
    return x & (-x);
}
inline void Add(int x, int v)
{
    while(x <= N) {
        tree[x] += v;
        x += LowBit(x);
    }
}
inline int Sum(int x)
{
    int ret = 0;
    while(x > 0)
    {
        ret += tree[x];
        x -= LowBit(x);
    }
    return ret;
}
inline int getPos(int p)
{
    return p - Sum(p);
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d", &N) != EOF && N)
    {
        for(int i = 1; i <= N; ++i) {
            tree[i] = 0;
            pre[i] = i - 1;
            next[i] = i + 1;
            if(i == 1) pre[i] = N;
            if(i == N) next[i] = 1;
        }
        for(int i = 0; i < N; ++i) {
            readNumber(op[i].order);
            op[i].id = i + 1;
        }
        sort(op, op + N);
        int now = 1;
        LL res = 0LL;
        for(int i = 0; i < N; ++i) {
            int p = getPos(now), q = getPos(op[i].id);
            res += (LL)min(abs(p-q), N-i-abs(p-q));
            now = op[i].id;
            Add(now, 1);
            if(i < N-1) {
                int last = now;
                now = next[now];
                next[pre[last]] = next[last];
                pre[next[last]] = pre[last];
            }
            res++;
        }
        printf("%I64d\n", res);
    }
    return 0;
}
