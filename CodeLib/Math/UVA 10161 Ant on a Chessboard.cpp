/*
** UVA 10161 Ant on a Chessboard
** Created by Rayn @@ 2014/04/25
*/
#include <cstdio>
#include <cmath>

int main()
{
	int n;

	while(scanf("%d", &n) != EOF && n)
	{
	    int k = floor(sqrt(n));
	    if(k * k == n)
        {
            if(k&1)
                printf("%d %d\n", 1, k);
            else
                printf("%d %d\n", k, 1);
        }
        else
        {
            int t = n - k * k;
            int m = t % (k + 1);
            if(k&1)
            {
                if(t <= k+1)
                    printf("%d %d\n", t, k+1);
                else
                    printf("%d %d\n", k+1, k+1-m);
            }
            else
            {
                if (t <= k+1)
                    printf("%d %d\n", k+1, t);
                else
                    printf("%d %d\n", k+1-m, k+1);
            }
        }
	}
	return 0;
}
