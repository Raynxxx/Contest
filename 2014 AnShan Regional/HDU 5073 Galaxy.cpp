/*
** HDU 5073 Galaxy
** Created by Rayn @@ 2014/10/30
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long Long;
const int MAXN = 50010;

int n, k;
Long star[MAXN];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) {
			scanf("%I64d", &star[i]);
		}
		if (n == k) {
			printf("0\n");
			continue;
		}
		sort(star + 1, star + 1 + n);
		Long sum = 0, sum2 = 0;
		for (int i = 1; i <= n - k; ++i) {
			sum += star[i];
			sum2 += star[i] * star[i];
		}
		Long cnt = n - k;
		Long ret = cnt * sum2 - sum * sum;
		for (int i = n - k + 1, pit = 1; i <= n; ++i, ++pit) {
			sum = sum + star[i] - star[pit];
			sum2 = sum2 + star[i] * star[i] - star[pit] * star[pit];
			Long tmp = cnt * sum2 - sum * sum;
			ret = min(ret, tmp);
		}
		printf("%.9f\n", (double)ret / cnt);
	}
	return 0;
}
