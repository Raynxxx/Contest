/*
** CF 469A I Wanna Be the Guy
** Created by Rayn @@ 2014/10/08
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int MAXN = 128;

bool pass[MAXN];

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, p, a;
	while (cin >> n) {
		fill_n(pass, n + 1, false);
		cin >> p;
		for (int i = 0; i < p; ++i) {
			cin >> a;
			pass[a] = true;
		}
		cin >> p;
		for (int i = 0; i < p; ++i) {
			cin >> a;
			pass[a] = true;
		}
		bool win = true;
		for (int i = 1; i <= n; ++i) {
			if (!pass[i]) {
				win = false;
				break;
			}
		}
		win ? puts("I become the guy.") : puts("Oh, my keyboard!");
	}
	return 0;
}
