/*
** LA 6465 Islands in the Data Stream
** Created by Rayn @@ 2014/08/05
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[20];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int T;
    scanf("%d", &T);
    while (T--)
    {
        int cases;
        scanf("%d", &cases);
        for (int i = 1; i <= 15; i++)
        {
            scanf("%d", &a[i]);
        }
        int res = 0;
        while(true)
        {
            int cnt = 0;
            for(int i = 1; i <= 15; i++)
            {
                if(a[i] != 0 && a[i-1] == 0) {
                    cnt++;
                }
            }
            if(cnt == 0) {
                break;
            }
            res += cnt;
            for(int i = 1; i <= 15; i++)
            {
                if(a[i] > 0) {
                    a[i]--;
                }
            }
        }
        printf("%d %d\n", cases, res);
    }
    return 0;
}
