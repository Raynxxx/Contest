/*
** UVA 2191 Potentiometers
** Created by Rayn @@ 2014/04/14
** Ê÷×´Êý×é
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200010;
int N, res, tree[MAXN];

inline int lowbit(int x)
{
	return x & (-x);
}
void Update(int x, int val)
{
	while(x <= N)
	{
		tree[x] += val;
		x += lowbit(x);
	}
}
long long GetSum(int x)
{
	long long sum = 0;
	while(x > 0)
	{
		sum += tree[x];
		x -= lowbit(x);
	}
	return sum;
}
int main()
{
	//freopen("in.txt", "r", stdin);
	int cases = 0;
	char op[10];

	while(scanf("%d", &N) != EOF && N)
	{
		memset(tree, 0, sizeof(tree));

		for(int i=1; i<=N; ++i)
		{
			scanf("%d", &res);
			Update(i, res);
		}

		if(cases > 0)
			printf("\n");
		printf("Case %d:\n", ++cases);

		int x, y, r;
		while(scanf("%s", op) !=EOF && op[0] != 'E')
		{
			if(op[0] == 'S')
			{
				scanf("%d%d", &x, &r);
				long long tmp = GetSum(x)-GetSum(x-1);
				Update(x, r-tmp);
			}
			if(op[0] == 'M')
			{
				scanf("%d%d", &x, &y);
				printf("%lld\n", GetSum(y)-GetSum(x-1));
			}
		}
	}
	return 0;
}

