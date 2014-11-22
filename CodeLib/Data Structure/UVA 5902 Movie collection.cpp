/*
** UVA 5902 Movie collection
** Created by Rayn @@ 2014/04/14
** Ê÷×´Êý×é
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
int n, m, id;
int pos[MAXN], tree[MAXN*2];

inline int lowbit(int x)
{
	return x & (-x);
}
void Update(int x, int val)
{
	while(x <= MAXN*2)
	{
		tree[x] += val;
		x += lowbit(x);
	}
}
int GetSum(int x)
{
	int sum = 0;
	while(x > 0)
	{
		sum += tree[x];
		x -= lowbit(x);
	}
	return sum;
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

	int T;

    scanf("%d", &T);
	while(T--)
	{
	    memset(pos, 0, sizeof(pos));
	    memset(tree, 0, sizeof(tree));

	    scanf("%d%d", &n, &m);
	    int top = MAXN;
		for(int i=1; i<=n; ++i)
        {
            Update(top+i, 1);
            pos[i] = top + i;
        }

		for(int i=1; i<=m; ++i)
		{
			scanf("%d", &id);
			int ans = GetSum(pos[id]-1);
			Update(pos[id],-1);
			pos[id] = --top;
			Update(pos[id], 1);
            printf("%d%c", ans, (i == m)? '\n' : ' ');
		}
	}
	return 0;
}

