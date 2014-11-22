/*
** HDU 5008 Boring String Problem
** Created by Rayn @@ 2014/09/19
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const int INF = 0x3F3F3F3F;
const int MAXN = 100010;

struct SuffixArray {

    char str[MAXN];
    int s[MAXN], n;
    int sa[MAXN], t[MAXN], t2[MAXN], c[MAXN];
    int rnk[MAXN], height[MAXN];
    long long sum[MAXN];

    void Build_sa(int m) {
        n++;
        int i, *x = t, *y = t2;
        for(i = 0; i < m; i++) c[i] = 0;
        for(i = 0; i < n; i++) c[x[i] = s[i]]++;
        for(i = 1; i < m; i++) c[i] += c[i-1];
        for(i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
        for(int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for(i = n - k; i < n; i++) y[p++] = i;
            for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
            for(i = 0; i < m; i++) c[i] = 0;
            for(i = 0; i < n; i++) c[x[y[i]]]++;
            for(i = 0; i < m; i++) c[i] += c[i-1];
            for(i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1;
            x[sa[0]] = 0;
            for(i = 1; i < n; i++)
                x[sa[i]] = (y[sa[i-1]] == y[sa[i]] && y[sa[i-1] + k] == y[sa[i] + k]) ? p - 1 : p++;
            if(p >= n) break;
            m = p;
        }
        n--;
    }
    void GetHeight() {
        int k = 0;
        for(int i = 1; i <= n; ++i) {
            rnk[sa[i]] = i;
        }
        for(int i = 0; i < n; ++i) {
            if(k) k--;
            int j = sa[rnk[i]-1];
            while(s[i+k] == s[j+k]) {
                k++;
            }
            height[rnk[i]] = k;
        }
    }
    void GetSum() {
        sum[0] = 0LL;
        for(int i = 1; i <= n; ++i) {
            sum[i] = sum[i-1] + n - sa[i] - height[i];
        }
    }
    void Init() {
        n = strlen(str);
        for(int i = 0; i < n; ++i) {
            s[i] = str[i] - 'a' + 1;
        }
        s[n] = 0;
        Build_sa(27);
        GetHeight();
        GetSum();
    }
    void Query(LL& ls, LL& rs, LL k) {
        int p = lower_bound(sum + 1, sum + 1 + n, k) - sum;
        if(p == n + 1) {
            ls = rs = 0;
            printf("%I64d %I64d\n", ls, rs);
            return ;
        }
        int len = k - sum[p-1] + height[p];
        int st = sa[p];
        for(int i = p; i > 1; --i) {
            if(height[i] < len) break;
            st = min(st, sa[i-1]);
        }
        for(int i = p + 1; i <= n; ++i) {
            if(height[i] < len) break;
            st = min(st, sa[i]);
        }
        ls = st + 1, rs = st + len;
        printf("%I64d %I64d\n", ls, rs);
    }
    void Gao() {
        Init();
        LL l = 0, r = 0, v;
        int q;
        scanf("%d", &q);
        while(q--) {
            scanf("%I64d\n", &v);
            LL k = (l^r^v) + 1;
            Query(l, r, k);
        }
    }
};

SuffixArray sa;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%s", sa.str) != EOF) {
        sa.Gao();
    }
    return 0;
}
