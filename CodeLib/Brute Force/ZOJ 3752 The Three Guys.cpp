/*
** ZOJ 3752 The Three Guys
** Created by Rayn @@ 2014/07/11
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAX = 1200;
const int INF = 0x3F3F3F3F;

double GetArea(int a, int b, int c)
{
    if(a + b <= c || a + c <= b || b + c <= a)
        return 0;
    double p = (a + b + c) / 2.0;
    return sqrt(p*(p-a)*(p-b)*(p-c));
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn
    int arr[5][5];
    while(scanf("%d%d", &arr[0][0], &arr[0][1]) != EOF)
    {
        for(int i = 1; i < 3; ++i)
            scanf("%d%d", &arr[i][0], &arr[i][1]);

        int sqe[] = {0, 1, 2};
        double res = 0;
        do
        {
            for(int i = 0; i < 8; ++i)
            {
                for(int j = 0; j < 3; ++j)
                {
                    if((1 << j) & i)
                        swap(arr[sqe[j]][0], arr[sqe[j]][1]);
                }
                int c[10], t = 0;
                for(int j = 0; j < 3; ++j)
                {
                    c[t++] = arr[j][0];
                    c[t++] = arr[j][1];
                }
                int len[7] = {0};
                for(int j = 0; j < 6; ++j)
                {
                    len[j+1] = len[j] + c[j];
                }
                for(int j = 0; j < 6; ++j)
                {
                    for(int k = j+1; k < 6; ++k)
                    {
                        for(int p = k+1; p < 6; ++p)
                        {
                            int a = len[k+1] - len[j+1];
                            int b = len[p+1] - len[k+1];
                            int c = len[6] - a - b;
                            res = max(res, GetArea(a, b, c));
                        }
                    }
                }
            }
        } while(next_permutation(sqe, sqe+3));
        printf("%.9f\n", res);
    }
    return 0;
}

