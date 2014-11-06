/*
** HDU 5030 Rabbit's String
** Created by Rayn @@ 2014/11/06
*/
#include <map>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 100100;

class SuffixArray {
private:
    int n, str[MAXN];
    int sa[MAXN], rank[MAXN], height[MAXN];
    int t1[MAXN], t2[MAXN], c[MAXN];
    Long dp[MAXN];

    bool cmp(int *r, int a, int b, int k) {
        return r[a] == r[b] && r[a + k] == r[b + k];
    }
    void build_sa(int m) {
        int i, p, k, *x = t1, *y = t2;
        for(i = 0; i < m; ++i) c[i] = 0;
        for(i = 0; i < n; ++i) c[x[i] = str[i]]++;
        for(i = 1; i < m; ++i) c[i] += c[i-1];
        for(i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
        for(k = 1, p = 1; k < n; k *= 2) {
            for(p = 0, i = n - k; i < n; ++i) y[p++] = i;
            for(i = 0; i < n; ++i) {
                if(sa[i] >= k) y[p++] = sa[i] - k;
            }
            for(i = 0; i < m; ++i) c[i] = 0;
            for(i = 0; i < n; i++) c[x[y[i]]]++;
            for(i = 1; i < m; ++i) c[i] += c[i-1];
            for(i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for(i = 1; i < n; ++i) {
                x[sa[i]] = cmp(y, sa[i-1], sa[i], k) ? p - 1 : p++;
            }
            if(p >= n) break;
            m = p;
        }
    }
    void build_height() {
        int i, j, k;
        for (i = 0; i < n; ++i) rank[sa[i]] = i;
        --n;
        for (i = 0; i < n; ++i) {
            if (k) --k;
            j = sa[rank[i] - 1];
            while (str[i + k] == str[j + k]) k++;
            height[rank[i]] = k;
        }
    }
    void Build_dp() {
        //dp[i] 代表排名前i的后缀中不同字串的数目
        dp[0] = 0;
        for(int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + (n - sa[i] - height[i]);
        }
    }
    bool Judge(Long m, int k) {
        fill_n(c, n + 1, -1);
        int pt = lower_bound(dp + 1, dp + 1 + n, m) - dp;
        int len = (n - (dp[pt] - m + 1)) - sa[pt] + 1;
        c[sa[pt]] = len;
        for(int i = pt + 1; i <= n; ++i) {
            len = min(len, height[i]);
            if(len == 0) return false;
            c[sa[i]] = len;
        }
        int ret = 0, p = n + 1;
        for(int i = 0; i < n; ++i) {
            if(i == p) {
                ret++;
                p = n + 1;
            }
            if(c[i] != -1) {
                p = min(p, i + c[i]);
            }
            if(ret >= k)
                return false;
        }
        return true;
    }

public:
    void Init(char *orgin) {
        n = strlen(orgin);
        for(int i = 0; i < n; ++i) {
            str[i] = int(orgin[i] - 'a' + 1);
        }
        str[n++] = 0;
    }
    void Build() {
        build_sa(64);
        build_height();
        Build_dp();
    }
    void Gao(char *orgin, int k) {
        Long l = 1, r = dp[n];
        for(int i = 0; i < 70; ++i) {
            Long mid = (l + r) / 2;
            if(Judge(mid, k)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        int t = lower_bound(dp + 1, dp + 1 + n, r) - dp;
        int ed = n - (dp[t] - r + 1);
        for(int i = sa[t]; i <= ed; ++i) {
            putchar(orgin[i]);
        }
        putchar('\n');
    }
};

SuffixArray Solver;
char orgin[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int k;
    while(scanf("%d", &k) != EOF && k) {
        scanf("%s", orgin);
        Solver.Init(orgin);
        Solver.Build();
        Solver.Gao(orgin, k);
    }
    return 0;
}
