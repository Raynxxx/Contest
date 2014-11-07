/*
** HDU 4777 Rabbit Kingdom
** Created by Rayn @@ 2014/09/19
*/
#include <cstdio>
#include <cmath>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 200010;

struct BIT {
    int n;
    int c[MAXN];

    void Init(int n) {
        this->n = n;
        memset(c, 0, sizeof(int)*(n+2));
    }
    void Add(int x, int v)
    {
        if(x == 0) return ;
        while(x <= n) {
            c[x] += v;
            x += x & (-x);
        }
    }
    int Sum(int x)
    {
        int ret = 0;
        while(x > 0) {
            ret += c[x];
            x -= x & (-x);
        }
        return ret;
    }
};

struct QueryNode
{
    int l, r, id;
    QueryNode() {}
    QueryNode(int l, int r, int id):
        l(l), r(r), id(id) {}
    void read() {
        scanf("%d%d", &l, &r);
    }
    bool operator < (const QueryNode& p) const {
        return r < p.r;
    }
} op[MAXN];

bool flag[MAXN];
int cnt, prime[MAXN];
vector<int> fact[MAXN];


void Init()
{

    int range = (int)sqrt(1.0*MAXN);
    fill(flag, flag + MAXN, true);
    for(int i = 2; i <= range; ++i) {
        if(flag[i]) {
            for(int j = i * i; j < MAXN; j += i) {
                flag[j] = false;
            }
        }
    }
    cnt = 0;
    for(int i = 2; i < MAXN; ++i) {
        if(flag[i]) {
            prime[cnt++] = i;
        }
    }
    for(int i = 0; i < MAXN; ++i) {
        fact[i].clear();
        int num = i;
        for(int j = 0; num > 1 && prime[j] * prime[j] <= num; ++j) {
            if(num % prime[j] == 0) {
                fact[i].push_back(prime[j]);
                while(num % prime[j] == 0) {
                    num /= prime[j];
                }
            }
        }
        if(num > 1) fact[i].push_back(num);
    }
}

int n, m, w[MAXN];
int l[MAXN], r[MAXN];
int pos[MAXN];
int res[MAXN];
vector<int> save[MAXN];
BIT bit;

void preSolver()
{
    fill(pos, pos + MAXN, 0);
    for(int i = 1; i <= n; ++i) {
        l[i] = 1;
        vector<int>::iterator it;
        for(it = fact[w[i]].begin(); it != fact[w[i]].end(); ++it) {
            l[i] = max(pos[*it] + 1, l[i]);
            pos[*it] = i;
        }
        l[i]--;
    }
    fill(pos, pos + MAXN, n+1);
    for(int i = n; i > 0; --i) {
        r[i] = n;
        vector<int>::iterator it;
        for(it = fact[w[i]].begin(); it != fact[w[i]].end(); ++it) {
            r[i] = min(pos[*it] - 1, r[i]);
            pos[*it] = i;
        }
        r[i]++;
    }
}
void nextSolver()
{
    for(int i = 0; i < m; ++i) {
        op[i].read();
        op[i].id = i;
    }
    sort(op, op + m);
    bit.Init(n);
    for(int i = 1; i <= n + 1; ++i) {
        save[i].clear();
    }
    for(int i = 1; i <= n + 1; ++i) {
        save[r[i]].push_back(i);
    }
    int right = 1;
    for(int i = 0; i < m; ++i) {
        while(right <= n && right <= op[i].r) {
            bit.Add(l[right], 1);
            vector<int>::iterator it;
            for(it = save[right].begin(); it != save[right].end(); ++it) {
                int left = *it;
                bit.Add(l[left], -1);
                bit.Add(left, 1);
            }
            right++;
        }
        int cnt = bit.Sum(op[i].r) - bit.Sum(op[i].l - 1);
        res[op[i].id] = op[i].r - op[i].l + 1 - cnt;
    }
    for(int i = 0; i < m; ++i) {
        printf("%d\n", res[i]);
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Init();
    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(n == 0 && m == 0) break;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &w[i]);
        }
        preSolver();
        nextSolver();
    }
    return 0;
}
