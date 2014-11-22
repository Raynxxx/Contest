/*
** POJ 1442 Black Box
** Created by Rayn @@ 2014/3/25
*/
#include <cstdio>
#include <cstring>
#include <queue>
#define MAX 30005
using namespace std;

int m, n, a[MAX], add[MAX];

int main()
{
    int get;
    while(scanf("%d %d", &m, &n) != EOF)
    {
        for(int i=0; i<m; ++i)
            scanf("%d", &a[i]);

        int cnt = 0;
        priority_queue<int, vector<int>, greater<int> > minq; //Ð¡¶¥¶Ñ
        priority_queue<int, vector<int>, less<int> > maxq; //´ó¶¥¶Ñ

        for(int i=0; i<n; ++i)
        {
            scanf("%d", &get);
            while(cnt < get)
            {
                minq.push(a[cnt]);
                cnt++;
            }
            while(!maxq.empty() && maxq.top() > minq.top())
            {
                int tmp = maxq.top();
                maxq.pop();
                maxq.push(minq.top());
                minq.pop();
                minq.push(tmp);

            }
            printf("%d\n", minq.top());
            maxq.push(minq.top());
            minq.pop();
        }
    }
    return 0;
}
