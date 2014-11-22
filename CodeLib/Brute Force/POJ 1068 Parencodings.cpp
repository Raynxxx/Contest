/*
** POJ 1068 Parencodings
** Created by Rayn @@ 2014/05/07
** Ä£ÄâÕ»²Ù×÷
*/
#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;
const int MAX = 25;

int P[MAX], W[MAX];
int str[MAX];

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r",stdin);
#endif
    int t, n;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);

        int cnt = 0;
        P[0] = 0;
        for(int i=1; i<=n; ++i)
        {
            scanf("%d", &P[i]);
            for(int j=cnt; j<cnt+P[i]-P[i-1]; ++j)
            {
                str[j] = j + 1;
            }
            str[cnt+P[i]-P[i-1]] = -(cnt+P[i]-P[i-1]+1);
            cnt = cnt+P[i]-P[i-1] + 1;
        }
        stack<int> box;
        int cnt2 = 0;
        for(int i=0; i<cnt; ++i)
        {
            if(str[i] > 0)
            {
                box.push(str[i]);
            }
            else if(str[i] < 0)
            {
                W[cnt2++] = (-str[i]-box.top())/2+1;
                box.pop();
            }
        }
        for(int i=0; i<cnt2; ++i)
        {
            printf("%d%c", W[i], (i==cnt2-1)? '\n':' ');
        }
    }
    return 0;
}
