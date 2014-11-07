/*
** CodeForces 1A Theatre Square
** Created by Rayn @@ 2014/05/18
*/
#include <cstdio>
#include <cmath>
typedef long long LL;

int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif

	int n, m, a;
	scanf("%d%d%d", &n, &m, &a);
	//LL l1 = (n + a - 1) / a; //另一种写法，很巧妙
	//LL l2 = (m + a - 1) / a;
	LL l1 = n / a;
	if (n % a != 0)
		l1++;
	LL l2 = m / a;
	if (m % a != 0)
		l2++;
	//printf("%I64d %I64d\n", l1, l2);
	LL ans = l1 * l2;
	printf("%I64d\n", ans);
	return 0;
}
