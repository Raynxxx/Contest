/*
** ZOJ 3373 Gensokyo Forbidden Words
** Created by Rayn @@ 2014/08/30
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;

int main()
{
	int ch;
	while ((ch = getchar()) != EOF)
    {
		switch (ch) {
			case '.':
				putchar('[');
				putchar('.');
				putchar(']');
				break;
			case '?':
				putchar('.');
				break;
			case '*':
				putchar('.');
				putchar('*');
				break;
			case '[':
				putchar('[');
				ch = getchar();
				if (ch == '!') {
					putchar('^');
					ch = getchar();
				}
				do {
					putchar(ch);
					ch = getchar();
				} while (ch != ']');
				putchar(']');
				break;
			default:
				putchar(ch);
				break;
		}
	}
	return 0;
}
