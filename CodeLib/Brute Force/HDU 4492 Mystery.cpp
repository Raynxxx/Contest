snha/*
** HDU 4492 Mystery
** Created by Rayn @@ 2014/04/27
*/
#include <cstdio>
#include <cmath>
#include <cstring>

char str[100];
int next[520];

int main()
{
    int P, N, cases;

    scanf("%d", &P);
    while(P--)
    {
        scanf("%d%*c", &cases);
        gets(str);
        scanf("%d", &N);
        for(int i=0; i<N; ++i)
            scanf("%d", &next[i]);

        printf("%d ", cases);
        int length = strlen(str);
        int pos = 0;
        for(int i=0; i<N; ++i)
        {
            pos = (pos + next[i] + length) % length;
            putchar(str[pos]);
        }
        printf("\n");
    }

    return 0;
}
