/*
** POJ 2886 Who Gets the Most Candies
** Created by Rayn @@ 2014/05/09
** 线段树
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAX = 500100;

struct Child {
    char name[12];
    int A;
} child[MAX];

int n, k, tree[MAX<<2], candy[MAX];

void GetCandy() //计算约数
{
    memset(candy, 0, sizeof(candy));
    int limit = (int)sqrt(MAX);
    for(int i=1; i<limit; ++i)
    {
        for(int j=i+1; j*i<MAX; ++j)
        {
            candy[i*j] += 2;
        }
        candy[i*i]++;
    }
    /*
    for(int i=1; i<=50; ++i)
        printf("candy[%d]: %d\n",i, candy[i]);
    printf("\n");
    //*/
}
void BuildTree(int rt, int l, int r)
{
    tree[rt] = r - l + 1;
    if(l == r)
    {
        return ;
    }
    int mid = (l + r) >> 1;
    BuildTree(rt<<1, l, mid);
    BuildTree(rt<<1|1, mid+1, r);
}
int Update(int rt, int l, int r, int val)
{
    tree[rt]--;
    if(l == r)
    {
        return l;
    }
    int ans, mid = (l + r) >> 1;
    if(val <= tree[rt<<1])
        ans = Update(rt<<1, l, mid, val);
    else
        ans = Update(rt<<1|1, mid+1, r, val-tree[rt<<1]);
    tree[rt] = tree[rt<<1] + tree[rt<<1|1];
    return ans;
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    GetCandy();
    while(scanf("%d%d", &n, &k) != EOF)
    {
        memset(tree, 0, sizeof(tree));
        BuildTree(1, 1, n);
        for(int i=1; i<=n; ++i)
        {
            scanf("%s%d", child[i].name, &child[i].A);
        }
        int maxVal = -1, maxPos, pos;
        int num = n;
        for(int i=1; i<=n; ++i)
        {
            pos = Update(1, 1, n, k);
            num--;
            if(candy[i] > maxVal)
            {
                maxVal = candy[i];
                maxPos = pos;
            }

            if(num == 0)
                break;
            /*
            ** 因为取模结果总是0~num-1,所以取模要编号k-1，求出结果后再+1。
            ** A>0, 因为这个人出去了，那么后面的人的编号都会先减一
            ** 所以这里的k要再-1.
            ** A<0，因为这个人出去，对前面的人是没有影响的。
            ** Tips: 为何模两次就对了呢?(问了迪迪才知道)
            ** 有负数的时候必须模两次，比如-14%6，(-14+6)%6和((-14)%6+6)%6的
            ** 结果是不一样的，也就是说n%k，当n大于k的负两倍时，第一次模能够
            ** 让它保证值落在-1倍~1倍之间，第二次模让它变成正数。
            */
            if(child[pos].A > 0)
            {
                k = ((k-2 + child[pos].A) % num + num) % num + 1;
            }
            else
            {

                k = ((k-1 + child[pos].A) % num + num) % num + 1;
            }
        }
        printf("%s %d\n", child[maxPos].name, maxVal);
    }
	return 0;
}
