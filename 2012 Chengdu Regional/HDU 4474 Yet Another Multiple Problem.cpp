/*
** HDU 4474 Yet Another Multiple Problem
** Created by Rayn @@ 2014/10/03
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
typedef pair<string, int> PSI;
const int MAXN = 10240;

bool illegal[15];
bool vis[MAXN];

string bfs(int n) {
	queue<PSI> que;
	que.push(make_pair(string(""), 0));
	while (!que.empty()) {
		PSI cur = que.front();
		que.pop();
		for (int i = 0; i <= 9; ++i) {
			if (cur.first == "" && i == 0) continue;
			if (illegal[i]) continue;
			string str = cur.first + char('0' + i);
			int num = (cur.second * 10 + i) % n;
			//cout << str << "  " << num << endl;
			if (!vis[num]) {
				if (num % n == 0) {
					return str;
				}
				que.push(make_pair(str, num));
				vis[num] = true;
			}
		}
	}
	return string("-1");
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif
	int n, m, cases = 0;
	while (scanf("%d%d", &n, &m) != EOF) {
		fill(illegal, illegal + 15, false);
		fill(vis, vis + n + 2, false);
		for (int i = 0, x; i < m; ++i) {
			scanf("%d", &x);
			illegal[x] = true;
		}
		printf("Case %d: %s\n", ++cases, bfs(n).c_str());
	}
}
