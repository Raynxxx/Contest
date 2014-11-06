/*
** ACdream 1430 SETI
** Created by Rayn @@ 2014/10/31
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 10024;
const int INF = 0x3F3F3F3F;

class SuffixArray {
public:
	int n, orgin[MAXN];
	int sa[MAXN], rank[MAXN], height[MAXN];
	int t[MAXN], t2[MAXN], c[MAXN];
	int m;

	void init_sa(char *str) {
		n = strlen(str);
		for (int i = 0; i < n; ++i) {
			orgin[i] = int(str[i] - 'a' + 1);
		}
		m = 60;
	}
	bool cmp(int *r, int a, int b, int k){
		return r[a] == r[b] && r[a + k] == r[b + k];
	}
	void build_sa() {
		int i, k, p, *x = t, *y = t2;
		orgin[n++] = 0;
		for (i = 0; i < m; i++) c[i] = 0;
		for (i = 0; i < n; i++) c[x[i] = orgin[i]]++;
		for (i = 1; i < m; i++) c[i] += c[i - 1];
		for (i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
		for (k = 1, p = 1; k < n; k *= 2, m = p) {
			for (p = 0, i = n - k; i < n; i++) y[p++] = i;
			for (i = 0; i < n; i++) if (sa[i] >= k) y[p++] = sa[i] - k;
			for (i = 0; i < m; i++) c[i] = 0;
			for (i = 0; i < n; i++) c[x[y[i]]]++;
			for (i = 1; i < m; i++) c[i] += c[i - 1];
			for (i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
			swap(x, y);
			p = 1;
			x[sa[0]] = 0;
			for (i = 1; i < n; i++) {
				x[sa[i]] = cmp(y, sa[i - 1], sa[i], k) ? p - 1 : p++;
			}
			if (p >= n) break;
			m = p;
		}
		n--;
	}
	void build_height() {
		int i, j, k = 0;
		for (i = 0; i <= n; ++i) rank[sa[i]] = i;
		for (i = 0; i < n; ++i) {
			if (k) --k;
			j = sa[rank[i] - 1];
			while (orgin[i + k] == orgin[j + k]) k++;
			height[rank[i]] = k;
		}
	}

	void Init(char *str) {
		init_sa(str);
		build_sa();
		build_height();
	}
	int Gao(int k, int len) {
		int maxv = 0, minv = INF;
		int ret = 0;
		for (int i = 2; i <= len + 1; ++i) {
			if (height[i] < k || i == len + 1) {
				if (maxv - minv >= k) {
					ret++;
				}
				maxv = 0, minv = INF;
			}
			else {
				maxv = max(maxv, max(sa[i - 1], sa[i]));
				minv = min(minv, min(sa[i - 1], sa[i]));
			}
		}
		return ret;
	}
};

SuffixArray Solver;
char buf[MAXN];

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%s", &buf) != EOF) {
		Solver.Init(buf);
		int len = strlen(buf);
		int ret = 0;
		for (int i = 1; i <= len / 2; ++i) {
			ret += Solver.Gao(i, len);
		}
		printf("%d\n", ret);
	}
	return 0;
}
