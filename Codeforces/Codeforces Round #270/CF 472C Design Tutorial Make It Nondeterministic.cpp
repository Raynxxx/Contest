/*
** CF 472C Design Tutorial Make It Nondeterministic
** Created by Rayn @@ 2014/10/13
*/
#include <map>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;
typedef pair<string, string> PSS;
const int MAXN = 100010;

int p[MAXN];
string name[MAXN << 1];
map<string, int> refer;

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	int n;
	while (cin >> n) {
		refer.clear();
		for (int i = 0; i < n; ++i) {
			cin >> name[i] >> name[i + n];
			refer[name[i]] = i + 1;
			refer[name[i + n]] = i + 1;
		}
		for (int i = 0; i < n; ++i) {
			cin >> p[i];
		}
		sort(name, name + n + n);
		int cnt = 0;
		for (int i = 0; i < n + n; ++i) {
			if (refer[name[i]] == p[cnt]) {
				cnt++;
				if (cnt == n) break;
			}
		}
		if (cnt == n) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
	return 0;
}
