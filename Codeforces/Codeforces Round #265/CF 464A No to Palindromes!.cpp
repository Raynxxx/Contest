/*
** CF 464A No to Palindromes!
** Created by Rayn @@ 2014/10/11
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
#include <algorithm>

using namespace std;

typedef long long LL;
const int MAXN = 1000 + 10;

char Change(string& orgin, int pos, int pre) {
	for (char i = orgin[pos] + 1; i < 'a' + pre; ++i) {
		if (i != orgin[pos - 1] && i != orgin[pos - 2]) {
			return i;
		}
	}
	return 0;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	int n, p, pos;
	string orgin;
	while (cin >> n >> p >> orgin) {
		for (pos = n - 1; pos >= 0; --pos) {
			char ch = Change(orgin, pos, p);
			if (ch) {
				orgin[pos] = ch;
				break;
			}
		}
		if (pos == -1) {
			puts("NO");
			continue;
		}
		//Greed Construct
		for (int i = pos + 1; i < n; ++i) {
			orgin[i] = 'a' - 1;
			orgin[i] = Change(orgin, i, p);
		}
		cout << orgin << endl;
	}
	return 0;
}
