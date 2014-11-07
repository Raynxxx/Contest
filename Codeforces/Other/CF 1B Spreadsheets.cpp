/*
** CodeForces 1B Spreadsheets
** Created by Rayn @@ 2014/05/19
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
typedef long long LL;
const int MAX = 100010;

char coor[MAX], col[MAX];

void GetRow(char *str, int &r, int &c)
{
	int flag = 1;
	r = c = 0;
	for (int i = 1; i < strlen(str); ++i)
	{
		if (isdigit(str[i]) && flag)
		{
			r = r * 10 + str[i] - '0';
		}
		if (isdigit(str[i]) && !flag)
		{
			c = c * 10 + str[i] - '0';
		}
		if (str[i] == 'C')
		{
			flag = 0;
		}
	}
}
void GetCol(char *str, char *col, int &r)
{
	int cnt = 0;
	r = 0;
	for (int i = 0; i < strlen(str); ++i)
	{
		if (isalpha(str[i]))
		{
			col[cnt++] = str[i];
		}
		if (isdigit(str[i]))
		{
			r = r * 10 + str[i] - '0';
		}
	}
}
int main()
{
#ifdef _Rayn
	//freopen("in.txt", "r", stdin);
#endif

	int t;
	scanf("%d%*c", &t);
	while (t--)
	{
		memset(col, 0, sizeof(col));
		gets(coor);
		int type = 0;
		if (coor[0] == 'R' && isdigit(coor[1]))
		{
			for (int i = 2; i < strlen(coor); ++i)
			{
				if (coor[i] == 'C')
				{
					type = 1;
					break;
				}
			}
		}
		if (type == 1)
		{
			int rown = 0, coln = 0, cnt = 0;
			GetRow(coor, rown, coln);
			while (coln)
			{
				coln--;
				int t1 = coln % 26;
				col[cnt++] = t1 + 'A';
				coln /= 26;
			}
			for (int i = cnt - 1; i >= 0; --i)
			{
				printf("%c", col[i]);
			}
			printf("%d\n", rown);
		}
		else if (type == 0)
		{
			int rown = 0, coln = 0;
			GetCol(coor, col, rown);
			coln = 0;
			for (int i = 0; i < strlen(col); ++i)
			{
				coln = coln * 26 + (col[i] - 'A');
				coln++;
				//printf("%d\n", coln);
			}
			printf("R%dC%d\n",rown, coln);
		}
	}
	return 0;
}
