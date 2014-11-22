/*
** POJ 1703 Find them, Catch them
** Created by Rayn @@ 2014/04/11
** 加权并查集
*/
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 100010;
int pa[MAX], rnk[MAX];

int FindSet(int x)
{
    if(x != pa[x])
    {
        int root = pa[x];
        pa[x] = FindSet(pa[x]);
        rnk[x] = (rnk[x] + rnk[root]) % 2;
    }
    return pa[x];
}
int main()
{
    int T, n, m, a, b;
    char op;

    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%*c", &n, &m);
        for(int i=0; i<=n; ++i)
        {
            pa[i] = i;
            rnk[i] = 0;
        }
        while(m--)
        {
            scanf("%c%d%d%*c", &op, &a, &b);
            if(op == 'A')
            {
                int ta = FindSet(a);
                int tb = FindSet(b);
                if(ta == tb)
                {
                    if(rnk[a] == rnk[b])
                        printf("In the same gang.\n");
                    else
                        printf("In different gangs.\n");
                }
                else
                    printf("Not sure yet.\n");
            }
            else if(op == 'D')
            {
                int ta = FindSet(a);
                int tb = FindSet(b);
                if(ta != tb)
                {
                    pa[ta] = tb;
                    rnk[ta] = (rnk[a]+rnk[b]+1) % 2;
                }
            }
        }
    }
	return 0;
}
