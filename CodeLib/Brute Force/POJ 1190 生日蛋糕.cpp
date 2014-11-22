/*
** POJ 1190 生日蛋糕
** Created by Rayn @@ 2014/04/13
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int INF = 2147483647;
int N, M, S, r, h;
int mins[21], minv[21];

void Init()
{
    /*
    ** mins表示从最上面一层到 i 层的最小表面积(这里仅仅算了侧面)
    ** minv表示从最上面一层到 i 层的最小体积
    */
    mins[0] = minv[0] = 0;
    for(int i=1; i<=20; ++i)
    {
        mins[i] = mins[i-1] + 2*i*i;
        minv[i] = minv[i-1] + i*i*i;
    }
}
/*
** dfs从M层开始向上搜索，一直搜索到0层结束
** deep表示该层层数，sums表示在deep + 1 -> m得到的表面
** 积， sumv表示deep + 1 -> m得到的体积，r表示deep+1的
** 半径，h表示deep + 1的高度
*/
void DFS(int deep, int sums, int sumv, int r, int h)
{
    if(deep == 0)
    {
        if(sumv == N && sums < S)
            S = sums;
        return ;
    }
    /*
    ** 这里用到的三个剪枝
    ** sums + mins[deep]> best 表示以前的到的deep + 1层到 m 层的表面积加上从顶层到deep层的最小表面积如果都大于了已经得到的best,那么1到deep层是无论半径和高度取何值都是无效的
    ** sumv + minv[deep] > n同理
    ** 2 * (n - sumv) / r + sums >= best 这是该题的精髓，如果没有的话会造成超时，是为了把sumv和sums联系起来，原因如下:
    ** 假设能够得到best时(为什么这样假设呢，因为如果得不到的话那么就已经被第一个剪枝滤去了,所以在第三个剪枝验证时表示已经通过了第一个剪枝的要求)，
    ** n - sumv = h[1] * r[1] * r[1] + ... + h[deep] * r[deep] * r[deep] < h[1] * r[1] * r + ... + h[deep] * r[deep] * r （因为r是deep + 1层的半径）
    ** 其中h[1]...h[deep]表示在函数的形参情况下，1到deep层应该取得h值，r[1]同理
    ** 两边同时处以r 再乘以2得 2 * (n - sumv) / r < 2 * (h[1] * r[1] + ... + h[deep] * r[deep])
    ** 2 * (n - sumv) / r < best - sums
    ** 2 * (n - sumv) / r + sums < best 成立 ，则可得剪枝条件
    */
    if(sums+mins[deep] > S || sumv+minv[deep]>N || 2*(N-sumv)/r+sums >= S)
        return ;
    for(int i=r-1; i>=deep; --i)
    {
        if(deep == M)
            sums = i * i;
        int maxh = min(N-sumv-minv[deep-1]/i*i, h-1);
        for(int j=h-1; j>=deep; --j)
            DFS(deep-1, sums+2*i*j, sumv+j*i*i, i, j);
    }
}
int main()
{
    S = INF;
    scanf("%d%d", &N, &M);
    Init();
    DFS(M, 0, 0, sqrt(N)+1, N+1);
    if(S == INF)
        printf("0\n");
    else
        printf("%d\n", S);
    return 0;
}
