/*
** CF 468B Two Sets
** Created by Rayn @@ 2014/10/08
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

using namespace std;

typedef long long LL;
typedef map<int, int> Hash;
typedef Hash::iterator Pointer;

const int MAXN = 100000 + 10;

class UnionSet {
public:
	int pa[MAXN];
	void Init(int n) {
		for (int i = 0; i <= n + 10; ++i) {
			pa[i] = i;
		}
	}
	int Find(int x) {
		if (x != pa[x])
			pa[x] = Find(pa[x]);
		return pa[x];
	}
	void Union(int x, int y) {
		int px = Find(x);
		int py = Find(y);
		pa[px] = py;
	}
};

#define SetA (n + 1)
#define SetB (n + 2)
UnionSet us;
Hash refer;
int p[MAXN];

void Init(int n) {
	us.Init(n);
	refer.clear();
}
void Solver(int n, int a, int b) {
	for (int i = 1; i <= n; ++i) {
		if (refer[a - p[i]]) {
			us.Union(i, refer[a - p[i]]);
		} else {
			us.Union(i, SetB);
		}
		if (refer[b - p[i]]) {
			us.Union(i, refer[b - p[i]]);
		} else {
			us.Union(i, SetA);
		}
	}
	if (us.Find(SetA) == us.Find(SetB)) {
		printf("NO\n");
	} else {
		printf("YES\n");
		for (int i = 1; i <= n; ++i) {
			if (us.Find(i) == us.Find(SetA)) {
				putchar('0');
			} else {
				putchar('1');
			}
			if (i != n) putchar(' ');
		}
		printf("\n");
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, a, b;
	while (scanf("%d%d%d", &n, &a, &b) != EOF) {
		Init(n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &p[i]);
			refer[p[i]] = i;
		}
		Solver(n, a, b);
	}
	return 0;
}
