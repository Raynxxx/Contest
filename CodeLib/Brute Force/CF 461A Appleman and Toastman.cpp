/*
** CF 461A Appleman and Toastman
** Created by Rayn @@ 2014/10/17
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;
const int MAXN = 300005;

int n;
int a[MAXN];

int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d", &n) != EOF) {
		Long sum = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			sum += a[i];
		}
		sort(a, a + n);
		Long ret = sum;
		for (int i = 0; i < n - 1; ++i) {
			ret += sum;
			sum -= a[i];
		}
		printf("%I64d\n", ret);
	}
	return 0;
}
