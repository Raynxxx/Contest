/*
** POJ 1190 ���յ���
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
    ** mins��ʾ��������һ�㵽 i �����С�����(����������˲���)
    ** minv��ʾ��������һ�㵽 i �����С���
    */
    mins[0] = minv[0] = 0;
    for(int i=1; i<=20; ++i)
    {
        mins[i] = mins[i-1] + 2*i*i;
        minv[i] = minv[i-1] + i*i*i;
    }
}
/*
** dfs��M�㿪ʼ����������һֱ������0�����
** deep��ʾ�ò������sums��ʾ��deep + 1 -> m�õ��ı���
** ���� sumv��ʾdeep + 1 -> m�õ��������r��ʾdeep+1��
** �뾶��h��ʾdeep + 1�ĸ߶�
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
    ** �����õ���������֦
    ** sums + mins[deep]> best ��ʾ��ǰ�ĵ���deep + 1�㵽 m ��ı�������ϴӶ��㵽deep�����С�����������������Ѿ��õ���best,��ô1��deep�������۰뾶�͸߶�ȡ��ֵ������Ч��
    ** sumv + minv[deep] > nͬ��
    ** 2 * (n - sumv) / r + sums >= best ���Ǹ���ľ��裬���û�еĻ�����ɳ�ʱ����Ϊ�˰�sumv��sums��ϵ������ԭ������:
    ** �����ܹ��õ�bestʱ(Ϊʲô���������أ���Ϊ����ò����Ļ���ô���Ѿ�����һ����֦��ȥ��,�����ڵ�������֦��֤ʱ��ʾ�Ѿ�ͨ���˵�һ����֦��Ҫ��)��
    ** n - sumv = h[1] * r[1] * r[1] + ... + h[deep] * r[deep] * r[deep] < h[1] * r[1] * r + ... + h[deep] * r[deep] * r ����Ϊr��deep + 1��İ뾶��
    ** ����h[1]...h[deep]��ʾ�ں������β�����£�1��deep��Ӧ��ȡ��hֵ��r[1]ͬ��
    ** ����ͬʱ����r �ٳ���2�� 2 * (n - sumv) / r < 2 * (h[1] * r[1] + ... + h[deep] * r[deep])
    ** 2 * (n - sumv) / r < best - sums
    ** 2 * (n - sumv) / r + sums < best ���� ����ɵü�֦����
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
