/*
** POJ 2886 Who Gets the Most Candies
** Created by Rayn @@ 2014/05/09
** �߶���
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

void GetCandy() //����Լ��
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
            ** ��Ϊȡģ�������0~num-1,����ȡģҪ���k-1������������+1��
            ** A>0, ��Ϊ����˳�ȥ�ˣ���ô������˵ı�Ŷ����ȼ�һ
            ** ���������kҪ��-1.
            ** A<0����Ϊ����˳�ȥ����ǰ�������û��Ӱ��ġ�
            ** Tips: Ϊ��ģ���ξͶ�����?(���˵ϵϲ�֪��)
            ** �и�����ʱ�����ģ���Σ�����-14%6��(-14+6)%6��((-14)%6+6)%6��
            ** ����ǲ�һ���ģ�Ҳ����˵n%k����n����k�ĸ�����ʱ����һ��ģ�ܹ�
            ** ������ֵ֤����-1��~1��֮�䣬�ڶ���ģ�������������
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
