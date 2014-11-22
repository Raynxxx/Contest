/*
** UVA 11987 Almost Union-Find
** Created by Rayn @@ 2014/04/07
** 操作2实际上相当于先把x删掉然后再和y合并，因此和
** 普通的并查集相比只是多了一个删除某个点的操作。
**
**  对于删除x的操作，是不能随便改变原来树中pa[x]的指向
** 的，比较容易能够举出反例。其实我们只是想在不影响其
** 他元素的前提下把x删掉，但不如换个思路，将x这个点对
** 它所在的集合的“影响”变为0。然后再新开一个节点表示x，
** 这样就相当于把x从原来的集合中剥离出来了。因此相比原
** 来的并查集，需要多一个id[x]数组表示点x现在的标号，有
** 了上面的思路其余的操作就不难写出来了
*/
#include <cstdio>
using namespace std;
const int MAX = 200010;
int pa[MAX], num[MAX], id[MAX], cnt;
long long rnk[MAX];

int FindSet(int x)
{
    if(x != pa[x])
    {
        pa[x] = FindSet(pa[x]);
    }
    return pa[x];
}
int main()
{
    int n, m;

    while(scanf("%d%d", &n, &m) != EOF)
    {
        cnt = n;
        for(int i=1; i<=n; ++i)
        {
            id[i] = pa[i] = rnk[i] = i;
            num[i] = 1;
        }

        int order, x, y;
        while(m--)
        {
            scanf("%d", &order);
            if(order == 1)
            {
                scanf("%d %d", &x, &y);
                int tx = FindSet(id[x]);
                int ty = FindSet(id[y]);
                if(tx != ty)
                {
                    pa[tx] = ty;
                    num[ty] += num[tx];
                    rnk[ty] += rnk[tx];
                }
            }
            else if(order == 2)
            {
                scanf("%d %d", &x, &y);
                int tx = FindSet(id[x]);
                int ty = FindSet(id[y]);
                if(tx != ty)
                {
                    num[tx]--;
                    rnk[tx] -= x;
                    id[x] = ++cnt;
                    pa[id[x]] = id[x];
                    num[id[x]] = 1;
                    rnk[id[x]] = x;
                    int tx = FindSet(id[x]);
                    pa[tx] = ty;
                    num[ty] += num[tx];
                    rnk[ty] += rnk[tx];
                }
            }
            else if(order == 3)
            {
                scanf("%d", &x);
                int tx = FindSet(id[x]);
                printf("%d %lld\n", num[tx], rnk[tx]);
            }
        }
    }
    return 0;
}
