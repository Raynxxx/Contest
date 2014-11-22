/*
** ZOJ 3523 Bookcase
** Created by Rayn @@ 2014/10/05
*/
#include <map>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;

vector<string> books;

int Gao(int m, vector<string>& books) {
	vector<int> dp(m, 1);
	int ret = 0;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < i; ++j) {
			if (books[j] <= books[i]) {
				if (dp[j] + 1 > dp[i]) {
					dp[i] = dp[j] + 1;
				}
			}
		}
		ret = max(ret, dp[i]);
	}
	return m - ret;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m;
	while (cin >> n >> m) {
		getchar();
		books.resize(m);
		int energy = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				getline(cin, books[j]);
			}
			energy += Gao(m, books);
		}
		cout << energy << endl;
	}
	return 0;
}
