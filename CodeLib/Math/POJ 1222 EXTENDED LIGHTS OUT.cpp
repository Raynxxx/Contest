/*
** POJ 1222 EXTENDED LIGHTS OUT
** Created by Rayn @@ 2014/08/08
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int martix[31][31];  //ÏµÊý¾ØÕó
int res[31];

void Gauss(int a[][31], int n)
{
	for(int i = 0, k; i < n; i++)
    {
		for(k = i; k < n; k++)
		{
			if(a[k][i] != 0)
			    break;
		}
		for(int j = 0; j <= n; j++)
        {
			swap(a[i][j], a[k][j]);
		}
		for(int j = 0; j < n; j++)
        {
			if(i != j && a[j][i])
			{
				for(int k = 0; k <= n; k++)
                {
					a[j][k] = a[i][k]^a[j][k];
                }
			}
		}
	}
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

	int T, cases = 0;
	scanf("%d", &T);
	while(T--)
    {
		memset(martix, 0, sizeof(martix));
		for(int i = 0;i < 30; i++)
		{
			scanf("%d", &martix[i][30]);
			res[i] = 0;
		}
		for(int i = 0;i < 30; i++)
		{
			martix[i][i] = 1;
			if(i%6 != 0)
				martix[i-1][i] = 1;
			if(i%6 != 5)
				martix[i+1][i] = 1;
			if(i > 5)
				martix[i-6][i] = 1;
			if(i < 24)
				martix[i+6][i] = 1;
		}
		Gauss(martix, 30);
		for(int i = 0; i < 30; i++)
		{
		    res[i] = martix[i][30];
		}
        printf("PUZZLE #%d\n", ++cases);
        for(int i = 0; i < 30; ++i)
        {
            printf("%d%c", res[i], (i%6 == 5)?'\n':' ');
        }
	}
	return 0;
}
