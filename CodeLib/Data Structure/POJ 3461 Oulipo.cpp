/*
** POJ 3461 Oulipo
** Created by Rayn @@ 2014/04/28
** ≥ı ‘KMP
*/
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXT = 1000010;
const int MAXP = 10010;

char T[MAXT], P[MAXP];
int next[MAXP];

void getNext()
{
    //memset(next, 0, sizeof(next));
    int i = 0, j = -1;
    int len = strlen(P);
    next[0] = -1;
    while(i < len)
    {
        if(j == -1 || P[i] == P[j])
        {
            next[i++] = j++;
        }
        else
        {
            j = next[j];
        }
    }
}
int KMP()
{
    int i = 0, j = 0, ans = 0;
    int m = strlen(T);
    int n = strlen(P);
    getNext();
    while(i < m)
    {
        if(j == -1 || T[i] == P[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
        if(j == n)
        {
            ans++;
            j = next[j];
        }
    }
    return ans;
}
int main()
{
    int t;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%s%s", P, T);
        printf("%d\n", KMP());
    }
    return 0;
}
