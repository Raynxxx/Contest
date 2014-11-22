/*
** ZOJ 2313 Chinese Girls' Amusement
** Created by Rayn @@ 2014/08/09

** 求最大的k<=n/2使得gcd(n,k)=1。
** 如果n是2m+1形式的，那么k=m就是答案；
** 如果n是4m形式的，那么k=2m-1就是答案；
** 如果n是4m+2形式的，那么k=2m-1就是答案。
** 证明略，需要简单的高精度。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

inline int ChrToInt(const char ch)
{
	return ch - '0';
}

inline char IntToChr(const int i)
{
	return '0' + i;
}

bool isodd(char *p, const int l)
{
	return (p[l - 1] & 1) != 0;
}

char* div2(char *p, const int l)
{
	for (int i = 0; i < l; i++) {
		if(p[i] & 1)
			p[i + 1] += 10;
		p[i] >>= 1;
	}
	p[l] = 0;
	while(*p == 0)
		++p;

	return p;
}

char* dec1(char *p, const int l)
{
	int i = l - 1;

	while(p[i] == 0)
		p[i--] = 9;
	--p[i];
	while(*p == 0)
		++p;

	return p;
}

char buf[2005];

int main(void)
{
	int re, len;
	char *p;

	scanf("%d ", &re);
	while(re--) {
		gets(buf);
		scanf("\n");
		len = strlen(buf);
		for (int i = 0; i < len; i++)
			buf[i] = ChrToInt(buf[i]);
		if(isodd(buf, len)) {
			p = div2(buf, len);
		}
		else {
			p = div2(buf, len);
			p = dec1(buf, len);
			if(!isodd(buf, len))
				p = dec1(buf, len);
		}
		for (int i = 0; i < len; i++)
			buf[i] = IntToChr(buf[i]);
		puts(p);
		if(re)
			putchar('\n');
	}
}
