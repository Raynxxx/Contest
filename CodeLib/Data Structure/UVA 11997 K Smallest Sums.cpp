/*
** UVA 11997 K Smallest Sums
** Created by Rayn @@ 2014/3/30
** 优先队列处理多路归并
*/
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX = 768;
int arr[MAX][MAX];


struct item{
    int sum, b;
    item(int sum, int b):sum(sum), b(b) {}
    bool operator < (const item &rhs) const{
        return sum > rhs.sum;
    }
};

void Merge(int *A, int *B, int k)
{
    priority_queue<item> pque;

    for(int i=0; i<k; ++i)
    {
        pque.push(item(A[i]+B[0], 0));
    }
    for(int i=0; i<k; ++i)
    {
        item now = pque.top();
        pque.pop();
        A[i] = now.sum;
        int b = now.b;
        if(b+1 < k)
            pque.push(item(now.sum-B[b]+B[b+1], b+1));
    }
}
int main() {

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int k;

    while(scanf("%d", &k) != EOF && k > 1)
    {
        for(int i=0; i<k; ++i)
        {
            for(int j=0; j<k; ++j)
                scanf("%d", &arr[i][j]);
            sort(arr[i],arr[i]+k);
        }
        for(int i=1; i<k; ++i)
            Merge(arr[0], arr[i], k);   //两两合并，最后存在arr[0]里面

        printf("%d", arr[0][0]);
        for(int i=1; i<k; ++i)
            printf(" %d", arr[0][i]);
        printf("\n");

    }
    return 0;
}
