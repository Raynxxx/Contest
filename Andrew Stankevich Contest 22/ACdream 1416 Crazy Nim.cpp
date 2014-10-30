/*
** ACdream 1416 Crazy Nim
** Created by Rayn @@ 2014/10/30
*/
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;
const int MAXN = 20010;

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int a, b, c;
	while (scanf("%d%d%d", &a, &b, &c) != EOF && (a || b || c)) {
		int ret = (a + 1) ^ (b + 1) ^ (c + 1);
		if (ret > 0) {
			puts("Alice wins the game.");
		} else {
			puts("Bob wins the game.");
		}
	}
	return 0;
}
