/*
** CF 464C Substitutes in Number
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
const int MAXN = 100000 + 10;
const int MOD = 1000000007;

inline void Add(int& x, int y) {
	x += y;
	if (x >= MOD) x -= MOD;
}
inline int Mul(int x, int y) {
	return (LL)x * y % MOD;
}

string orgin, buf;
string query[MAXN];
char digit[MAXN];
int expo[MAXN], val[MAXN];

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);

	string orgin, buf;
	int q;
	while (cin >> orgin >> q) {
		int n = (int) orgin.length();
		for (int i = 0; i < q; ++i) {
			cin >> buf;
			digit[i] = buf[0];
			query[i].clear();
			for (int j = 3; j < buf.length(); j++) {
				query[i].push_back(buf[j]);
			}
		}
		for (int d = 0; d < 10; ++d) {
			val[d] = d;
			expo[d] = 10;
		}
		for (int i = q - 1; i >= 0; --i) {
			int d = digit[i] - '0';
			int nexp = 1, nval = 0;
			int sz = query[i].length();
			for (int j = 0; j < sz; ++j) {
				int to = query[i][j] - '0';
				nval = Mul(nval, expo[to]);
				Add(nval, val[to]);
				nexp = Mul(nexp, expo[to]);
			}
			expo[d] = nexp;
			val[d] = nval;
		}
		int res = 0;
		for (int i = 0; i < n; ++i) {
			int t = orgin[i] - '0';
			res = Mul(res, expo[t]);
			Add(res, val[t]);
		}
		cout << res << endl;
	}
	return 0;
}
