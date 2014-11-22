/*
** ZOJ 3526 Weekend Party
** Created by Rayn @@ 2014/10/05
*/
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const int INF = 0x3F3F3F3F;
const int MAXN = 64;
const int MAXCNT[] = { 1, 1, 1, 2, 2, 2, 2 };

vector<string> Like;
vector<string> seat;
bool link[MAXN][MAXN];
bool vis[MAXN];
bool circle;
int sz;

void Init() {
	Like.resize(7);
	Like[0] = "A";
	Like[1] = "C";
	Like[2] = "G";
	Like[3] = "AC";
	Like[4] = "AG";
	Like[5] = "CG";
	Like[6] = "ACG";
}
bool Check(string& A, string& B) {
	for (int i = 0; i < (int) A.length(); ++i) {
		for (int j = 0; j < (int) B.length(); ++j) {
			if (A[i] == B[j]) {
				return true;
			}
		}
	}
	return false;
}
void dfs(int u, int dep) {
	if (circle) return;
	for (int id = 0; id < sz && !circle; ++id) {
		if (link[u][id]) {
			if (id == 0 && dep == sz) {
				circle = true;
				return;
			}
			if (!vis[id]) {
				vis[id] = true;
				dfs(id, dep + 1);
				vis[id] = false;
			}
		}
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	Init();
	int n;
	while (scanf("%d", &n) != EOF) {
		vector<int> cnt(7, 0);
		for (int i = 0; i < n; ++i) {
			char type[15];
			scanf("%*s %s", type);
			int len = strlen(type);
			sort(type, type + len);
			for (int i = 0; i < 7; ++i) {
				if (Like[i] == string(type) && cnt[i] < MAXCNT[i]) {
					cnt[i]++;
				}
			}
		}
		seat.clear();
		for (int i = 0; i < 7; ++i) {
			for (int j = 0; j < cnt[i]; ++j) {
				seat.push_back(Like[i]);
			}
		}
		sz = seat.size();
		if (sz == 1) {
			puts("Yes");
			continue;
		}
		memset(link, false, sizeof(link));
		memset(vis, false, sizeof(vis));
		for (int i = 0; i < sz; ++i) {
			for (int j = i + 1; j < sz; ++j) {
				if (Check(seat[i], seat[j])) {
					link[i][j] = link[j][i] = true;
				}
			}
		}
		circle = false;
		vis[0] = true;
		dfs(0, 1);
		if (circle) {
			puts("Yes");
		} else {
			puts("No");
		}
	}
	return 0;
}
