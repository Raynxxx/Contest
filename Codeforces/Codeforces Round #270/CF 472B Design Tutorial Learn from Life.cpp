/*
** CF 472B Design Tutorial Learn from Life
** Created by Rayn @@ 2014/10/13
*/
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long LL;
const int MAXN = 2010;

int f[MAXN];

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, k;
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &f[i]);
		}
		sort(f + 1, f + 1 + n);
		int ret = 0;
		for (int i = n; i >= 1; i -= k) {
			ret += (f[i] - 1) * 2;
		}
		printf("%d\n", ret);
	}
	return 0;
}
