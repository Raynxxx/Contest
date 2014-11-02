/*
** HDU 5090 Game with Pearls
** Created by Rayn @@ 2014/11/02
*/
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

typedef long long Long;

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, k;
		scanf("%d%d", &n, &k);
		priority_queue<int, vector<int>, greater<int> > pq;
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			pq.push(x);
		}
		bool win = true;
		int cur = 1;
		while (cur <= n) {
			int pearl = pq.top();
			pq.pop();
			if (pearl > cur) {
				win = false;
				break;
			} else if (pearl == cur) {
				++cur;
			} else {
				pq.push(pearl + k);
			}
		}
		if (win) {
			puts("Jerry");
		} else {
			puts("Tom");
		}
	}
	return 0;
}
