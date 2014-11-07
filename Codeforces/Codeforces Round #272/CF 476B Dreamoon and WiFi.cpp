/*
** CF 476B Dreamoon and WiFi
** Created by Rayn @@ 2014/10/21
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

typedef long long Long;
const int MAXN = 25;

string command;
string recognize;
int length;
int s1, s2;
int sum[MAXN];

void dfs(int pos, int step) {
	if (pos == length) {
		sum[step + 10]++;
		s2++;
		return;
	}
	if (recognize[pos] == '+') {
		dfs(pos + 1, step + 1);
	} else if (recognize[pos] == '-') {
		dfs(pos + 1, step - 1);
	} else {
		dfs(pos + 1, step + 1);
		dfs(pos + 1, step - 1);
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	while (cin >> command) {
		cin >> recognize;
		length = command.length();
		s1 = s2 = 0;
		for (int i = 0; i < length; ++i) {
			if (command[i] == '+') {
				s1++;
			} else {
				s1--;
			}
		}
		dfs(0, 0);
		printf("%.10f\n", sum[s1 + 10] * 1.0 / s2);
	}
	return 0;
}
