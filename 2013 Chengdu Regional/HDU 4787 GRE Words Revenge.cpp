/*
** HDU 4787 GRE Words Revenge
** Created by Rayn @@ 2014/10/28
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;
const int Limit = 2000;
const int MAXN = 5000010;
const int MaxNode = 100010 << 2;
const int CharSet = 2;

class AC_Automaton {
public:
	int ch[MaxNode][CharSet];
	int fail[MaxNode];
	bool val[MaxNode];
	int sz;

	void Init() {
		sz = 1;
		memset(ch[0], 0, sizeof(ch[0]));
		memset(fail, 0, sizeof(fail));
		memset(val, false, sizeof(val));
	}
	int new_node() {
		memset(ch[sz], 0, sizeof(ch[sz]));
		return sz++;
	}
	int Index(char ch) {
		return ch - '0';
	}
	int Insert(char *pattern) {
		int u = 0;
		for (int i = 0; pattern[i]; ++i) {
			int c = Index(pattern[i]);
			if (!ch[u][c]) {
				ch[u][c] = new_node();
			}
			u = ch[u][c];
		}
		val[u] = true;
		return u;
	}
	bool Search(char *pattern) {
		int u = 0;
		for (int i = 0; pattern[i]; ++i) {
			int c = Index(pattern[i]);
			if (!ch[u][c]) {
				return 0;
			}
			u = ch[u][c];
		}
		return val[u];
	}
	void GetFail() {
		queue<int> que;
		for (int i = 0; i < CharSet; ++i) {
			if (ch[0][i]) {
				que.push(ch[0][i]);
			}
		}
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			for (int c = 0; c < CharSet; ++c) {
				int v = ch[u][c];
				if (!v) continue;
				que.push(v);
				int ptr = fail[u];
				while (ptr && ch[ptr][c] == 0) {
					ptr = fail[ptr];
				}
				fail[v] = ch[ptr][c];
			}
		}
	}
	int Find(char *text) {
		int u = 0, ret = 0;
		for (int i = 0; text[i]; ++i) {
			int c = Index(text[i]);
			while (u && !ch[u][c]) {
				u = fail[u];
			}
			u = ch[u][c];
			int ptr = u;
			while (ptr) {
				ret += (int) val[ptr];
				ptr = fail[ptr];
			}
		}
		return ret;
	}
};

AC_Automaton box, buf;
char str[MAXN], text[MAXN];

void Init() {
	box.Init();
	buf.Init();
}
void Shift(int len, int L) {
	text[0] = str[0];
	L %= len;
	for (int i = 0; i < len; ++i) {
		text[i + 1] = str[(i + L) % len + 1];
	}
	text[len + 1] = '\0';
}
void dfs(int u, int v) {
	for (int i = 0; i < CharSet; ++i) {
		if (buf.ch[v][i]) {
			int p2 = buf.ch[v][i];
			if (!box.ch[u][i]) {
				box.ch[u][i] = box.new_node();
			}
			int p1 = box.ch[u][i];
			box.val[p1] |= buf.val[p2];
			dfs(p1, p2);
		}
	}
}
void Merge() {
	dfs(0, 0);
	buf.Init();
	box.GetFail();
}
void Gao(int n) {
	int L = 0;
	while (n--) {
		scanf("%s", str);
		int len = strlen(str + 1);
		Shift(len, L);
		if (text[0] == '+') {
			if (box.Search(text + 1) || buf.Search(text + 1)) continue;
			buf.Insert(text + 1);
			buf.GetFail();
			if (buf.sz > Limit) {
				Merge();
			}
		} else {
			L = box.Find(text + 1) + buf.Find(text + 1);
			printf("%d\n", L);
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
		int n;
		scanf("%d", &n);
		printf("Case #%d:\n", ++cases);
		Init();
		Gao(n);
	}
	return 0;
}
