/*
** POJ 3784 Running Median
** Created by Rayn @@ 2014/3/28
*/
#include <cstdio>
#include <cstring>
#include <queue>
#define MAX 30005
using namespace std;

int m, n, a[MAX];

int main()
{
    int p, get, cases;

    scanf("%d", &p);
    while(p--)
    {
        scanf("%d %d", &cases, &m);
        for(int i=1; i<=m; ++i)
            scanf("%d", &a[i]);

        priority_queue<int, vector<int>, greater<int> > minq; //Ð¡¶¥¶Ñ
        priority_queue<int, vector<int>, less<int> > maxq; //´ó¶¥¶Ñ

        printf("%d %d\n", cases, (m+1)/2);


        for(int i=1; i<=m; ++i)
        {
            minq.push(a[i]);
            if(i&1)
            {
                while(!maxq.empty() && maxq.top() > minq.top())
                {
                    int tmp = maxq.top();
                    maxq.pop();
                    maxq.push(minq.top());
                    minq.pop();
                    minq.push(tmp);

                }
                printf("%d%c", minq.top(), (((i+1)/2)%10==0 || (i+1)/2==(m+1)/2) ? '\n':' ');
                maxq.push(minq.top());
                minq.pop();
            }
        }
    }
    return 0;
}
