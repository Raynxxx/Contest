/*
** HDU 4863 Centroid of a Tree
** Created by Rayn @@ 2014/10/19
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

namespace FastIO {
	/* Input >> int & long long */
	template <typename T>
	inline void readInteger(T& ret) {
		char ch = getchar();
		bool flag = false;
		while ((ch < '0' || ch > '9') && ch != '-') {
			ch = getchar();
		}
		if (ch == '-') {
			flag = true;
			ch = getchar();
		}
		ret = 0;
		while (ch >= '0' && ch <= '9') {
			ret = ret * 10 + (ch - '0');
			ch = getchar();
		}
		if (flag) ret = -ret;
	}
	inline int nextInt() {
		int x;
		readInteger(x);
		return x;
	}
	inline long long nextLong() {
		long long x;
		readInteger(x);
		return x;
	}

	/* Output << int & long long */
	template <typename T>
	inline void outInteger(T x) {
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		if (x >= 10) {
			outInteger(x / 10);
		}
		putchar(x % 10 + '0');
	}
	inline void newline() {
		putchar('\n');
	}
};

using namespace std;
using namespace FastIO;

typedef long long Long;
typedef vector<int> VI;
typedef VI::iterator Iter;
const int MAXN = 210;
const int MOD = 10007;
const int INF = 0x3F3F3F3F;

vector<int> edges[MAXN];
int n, minsz, root1, root2;
int sz[MAXN], w[MAXN][MAXN];
int tw[MAXN], f[MAXN], tf[MAXN];

inline void GraphInit() {
	minsz = INF;
	root1 = root2 = -1;
	memset(w, 0, sizeof(w));
	for (int i = 0; i <= n; ++i) {
		edges[i].clear();
	}
}
inline void AddEdge(int u, int v) {
	edges[u].push_back(v);
	edges[v].push_back(u);
}
void FindCentroid(int u, int fa) {
	sz[u] = 1;
	int maxsz = 0;
	for (Iter it = edges[u].begin(); it != edges[u].end(); ++it) {
		int v = *it;
		if (v == fa) continue;
		FindCentroid(v, u);
		sz[u] += sz[v];
		maxsz = max(maxsz, sz[v]);
	}
	maxsz = max(maxsz, n - sz[u]);
	if (maxsz < minsz) {
		minsz = maxsz;
		root1 = u;
		root2 = -1;
	} else if (maxsz == minsz) {
		root2 = u;
	}
}
void dfs(int u, int fa) {
	sz[u] = 1;
	w[u][1] = 1;
	for (Iter it = edges[u].begin(); it != edges[u].end(); ++it) {
		int v = *it;
		if (v == fa) continue;
		dfs(v, u);
		for (int i = 0; i <= sz[u]; ++i) {
			tw[i] = w[u][i];
		}
		for (int i = 1; i <= sz[u]; ++i) {
			for (int j = 1; j <= sz[v]; ++j) {
				w[u][i + j] = (w[u][i + j] + tw[i] * w[v][j]) % MOD;
			}
		}
		sz[u] += sz[v];
	}
}
int Gao() {
	int ret = 0;
	if (root2 == -1) {
		dfs(root1, 0);
		for (Iter it = edges[root1].begin(); it != edges[root1].end(); ++it) {
			int v = *it;
			fill_n(f, MAXN, 0);
			f[0] = 1;
			for (Iter it2 = edges[root1].begin(); it2 != edges[root1].end(); ++it2) {
				int v2 = *it2;
				if (v2 == v) continue;
				for (int i = 0; i <= sz[v] - 1; ++i) {
					tf[i] = f[i];
				}
				for (int i = 1; i <= sz[v2]; ++i) {
					for (int j = sz[v] - 1; j >= i; --j) {
						f[j] = (f[j] + tf[j - i] * w[v2][i]) % MOD;
					}
				}
			}
			for (int i = 1; i <= sz[v]; ++i) {
				for (int j = 0; j < i; ++j) {
					ret = (ret + f[j] * w[v][i]) % MOD;
				}
			}
		}
		int all = 0;
		for (int i = 1; i <= n; ++i) {
			all = (all + w[root1][i]) % MOD;
		}
		ret = ((all - ret) % MOD + MOD) % MOD;
	}
	else {
		dfs(root1, root2);
		dfs(root2, root1);
		for (int i = 1; i * 2 <= n; ++i) {
			ret = (ret + w[root1][i] * w[root2][i]) % MOD;
		}
	}
	return ret;
}

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int cases = 0;
	int T = nextInt();
	while (T--) {
		n = nextInt();
		GraphInit();
		for (int i = 1; i < n; ++i) {
			int x = nextInt();
			int y = nextInt();
			AddEdge(x, y);
		}
		FindCentroid(1, 0);
		printf("Case %d: %d\n", ++cases, Gao());
	}
	return 0;
}
