/*
** HDU 4112 Break the Chocolate
** Created by Rayn @@ 2014/10/31
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <string>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long Long;
const int MAXN = 100100;

Long f(int x) {
	return (Long)ceil(log(x * 1.0) / log(2.0));
}
int main() {
#ifdef _Rayn
	//freopen("in.txt", "r", stdin);
#endif
	int T, cases = 0;
	scanf("%d", &T);
	while (T--) {
		int n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		Long A = (Long)n * m * k - 1;
		Long B = f(n) + f(m) + f(k);
		printf("Case #%d: %I64d %I64d\n", ++cases, A, B);
	}
	return 0;
}
