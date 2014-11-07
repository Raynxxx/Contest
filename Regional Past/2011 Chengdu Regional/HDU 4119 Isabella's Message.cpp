/*
** HDU 4119 Isabella's Message
** Created by Rayn @@ 2014/10/31
*/
#include <map>
#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 105;

char matrix[MAXN][MAXN];
char mask[MAXN][MAXN];
set<string> dic, ret;

void ReadData(int& n, int& m) {
	scanf("%d%*c", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%s", matrix[i]);
		for (int j = 0; j < n; ++j) {
			if (matrix[i][j] == '.') {
				matrix[i][j] = ' ';
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		scanf("%s", mask[i]);
	}
	scanf("%d", &m);
	dic.clear();
	char word[MAXN];
	for (int i = 0; i < m; ++i) {
		scanf("%s", word);
		dic.insert(string(word));
	}
}
void Rotate(int n) {
	char tmp[MAXN][MAXN];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			tmp[j][n - i - 1] = mask[i][j];
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			mask[i][j] = tmp[i][j];
		}
	}
}
void Process(int n, string& ret) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (mask[i][j] == '*') {
				ret += char(matrix[i][j]);
			}
		}
	}
}
bool Check(string& mess) {
	istringstream is(mess);
	vector<string> box;
	while (is >> mess) {
		if (!dic.count(mess)) return false;
		box.push_back(mess);
	}
	mess.clear();
	for (int i = 0; i < (int) box.size(); ++i) {
		mess += box[i];
		if (i < (int) box.size() - 1) {
			mess += char(' ');
		}
	}
	return true;
}
void GetMessage(int n) {
	string word[4];
	for (int s = 0; s < 4; ++s) {
		if (s > 0) Rotate(n);
		Process(n, word[s]);
	}
	ret.clear();
	vector<string> box;
	bool ok = false;
	for (int i = 0; i < 4; ++i) {
		string mess;
		for (int j = 0; j < 4; ++j) {
			mess += word[(i + j) % 4];
		}
		if (Check(mess)) {
			ret.insert(mess);
		}
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T, cases = 0;
	scanf("%d", &T);
	while (T--) {
		int n, m;
		ReadData(n, m);
		GetMessage(n);
		printf("Case #%d: ", ++cases);
		int sz = ret.size();
		if (sz == 0) {
			puts("FAIL TO DECRYPT");
		} else {
			printf("%s\n", ret.begin()->c_str());
		}
	}
	return 0;
}
