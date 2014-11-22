/*
** HDU 1394 Minimum Inversion Number
** Created by Rayn @@ 2014/04/14
** 线段树or暴力or树状数组
**
** ##思路##
** 开始可以用其上任意一种计算出初始数列的逆序数sum
** 这里我比较懒，就直接用的暴力找的sum
** 对于a[i](0~~n-1)，每挪一个，用sum减去挪之前它右边
** 比它小的数的个数（也就是a[i]个），再用sum加上挪之
** 后左边比它大的数的个数（也就是n-a[i]-1个），就是
** 挪了a[i]之后的逆序数了。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 5010;
int arr[MAX], ans;

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    int N;
    while(scanf("%d", &N) != EOF && N)
    {
        for(int i=0; i<N; ++i)
        {
            scanf("%d", &arr[i]);
        }
        int sum = 0;
        for(int i=0; i<N; ++i)
        {
            for(int j=i+1; j<N; ++j)
            {
                if(arr[i] > arr[j])
                        sum++;
            }
        }
        ans = sum;
        for(int i=0; i<N-1; ++i)
        {
            sum = (sum - arr[i]) + (N - arr[i] - 1);
            ans = min(ans, sum);
        }
        printf("%d\n", ans);
    }
    return 0;
}
