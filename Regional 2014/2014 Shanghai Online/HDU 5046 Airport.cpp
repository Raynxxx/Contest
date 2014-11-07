/*
** HDU 5046 Airport
** Created by Rayn @@ 2014/09/29
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
typedef long long LL;

const int MAXN = 64;
const int MAXNODE = MAXN * MAXN;
const LL INF = 1LL << 60;

class DancingLinksX {
public:
    int n, m, sz;
    int U[MAXNODE], D[MAXNODE], R[MAXNODE], L[MAXNODE];
    int row[MAXNODE], col[MAXNODE];
    int H[MAXN], S[MAXN];
    bool v[MAXNODE];
    int ands, res[MAXN];

    void Init(int n, int m)
    {
        this->n = n;
        this->m = m;
        for(int i = 0; i <= m; ++i) {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i - 1;
            R[i] = i + 1;
        }
        R[m] = 0, L[0] = m;
        sz = m;
        for(int i = 1; i <= n; ++i) {
            H[i] = -1;
        }
    }
    void Link(int r, int c)
    {
        ++S[col[++sz] = c];
        row[sz] = r;
        D[sz] = D[c];
        U[D[c]] = sz;
        U[sz] = c;
        D[c] = sz;
        if(H[r] < 0) {
            H[r] = L[sz] = R[sz] = sz;
        } else {
            R[sz] = R[H[r]];
            L[R[H[r]]] = sz;
            L[sz] = H[r];
            R[H[r]] = sz;
        }
    }
    void Remove(int c)
    {
        for(int i = D[c]; i != c; i = D[i]) {
            L[R[i]] = L[i];
            R[L[i]] = R[i];
        }
    }
    void Resume(int c)
    {
        for(int i = U[c]; i != c; i = U[i]) {
            L[R[i]] = R[L[i]] = i;
        }
    }
    int Rank()
    {
        int ret = 0;
        for(int c = R[0];c != 0;c = R[c]) {
            v[c] = true;
        }
        for(int c = R[0];c != 0;c = R[c]) {
            if(v[c]) {
                ret++;
                v[c] = false;
                for(int i = D[c]; i != c; i = D[i]) {
                    for(int j = R[i]; j != i; j = R[j]) {
                        v[col[j]] = false;
                    }
                }
            }
        }
        return ret;
    }
    bool Dance(int d, int K)
    {
        if(d + Rank() > K) return false;
        if(R[0] == 0) return d <= K;
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i]) {
            if(S[i] < S[c]) {
                c = i;
            }
        }
        for(int i = D[c]; i != c; i = D[i]) {
            Remove(i);
            for(int j = R[i]; j != i; j = R[j]) {
                Remove(j);
            }
            if(Dance(d+1, K))
                return true;
            for(int j = L[i]; j != i; j = L[j]) {
                Resume(j);
            }
            Resume(i);
        }
        return false;
    }
};

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    void read() {
        scanf("%d%d", &x, &y);
    }
};
LL Dist(Point a, Point b)
{
    return abs((LL)a.x-b.x) + abs((LL)a.y-b.y);
}

Point city[MAXN];
LL dist[MAXN][MAXN];
LL Hash[MAXNODE];
DancingLinksX Solver;

int PreGao(int n)
{
    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        for(int j = i + 1; j < n; ++j) {
            dist[i][j] = dist[j][i] = Dist(city[i], city[j]);
            Hash[++cnt] = dist[i][j];
        }
    }
    sort(Hash+1, Hash+1+cnt);
    return cnt;
}
LL nextGao(int n, int k, int sz)
{
    int l = 1, r = sz, id = sz;
    while(l <= r) {
        int mid = (l + r) >> 1;
        Solver.Init(n, n);
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(dist[i][j] <= Hash[mid]) {
                    Solver.Link(i+1, j+1);
                }
            }
        }
        if(Solver.Dance(0, k)) {
            r = mid - 1;
            id = mid;
        } else {
            l = mid + 1;
        }
    }
    if(n == 1) return 0;
    return Hash[id];
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
        int n, k;
        scanf("%d%d", &n, &k);
        for(int i = 0; i < n; ++i) {
            city[i].read();
        }
        if(k >= n) {
            printf("Case #%d: 0\n", ++cases);
            continue;
        }
        int cnt = PreGao(n);
        LL ret = nextGao(n, k, cnt);
        printf("Case #%d: %I64d\n", ++cases, ret);
    }
    return 0;
}
