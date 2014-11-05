/*
** ZOJ 3826 Hierarchical Notation
** Created by Rayn @@ 2014/10/13
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

typedef long long LL;
const int MAXDOT = 10005;
const int MAXLEN = 40 * MAXDOT;

class Trie {
public:
	const static int MAXNODE = 20 * MAXDOT;
	const static int SIZE = 27;

	int ch[MAXNODE][SIZE];
	int val[MAXNODE][2];
	int sz;

	void Init() {
		sz = 1;
		memset(ch[0], 0, sizeof(ch[0]));
	}
	int Index(char c) {
		if (c == '.') return 26;
		return c - 'a';
	}
	int Insert(char *str, int u, int x, int y) {
		int len = strlen(str);
		for (int i = 0; i < len; ++i) {
			int v = Index(str[i]);
			if (!ch[u][v]) {
				memset(ch[sz], 0, sizeof(ch[sz]));
				val[sz][0] = val[sz][1] = 0;
				ch[u][v] = sz++;
			}
			u = ch[u][v];
		}
		val[u][0] = x, val[u][1] = y;
		return u;
	}
	int Find(char *str) {
		int len = strlen(str), u = 0;
		for (int i = 0; i < len; ++i) {
			int v = Index(str[i]);
			if (!ch[u][v]) {
				return -1;
			}
			u = ch[u][v];
		}
		return u;
	}
};

Trie trie;
char buf[MAXLEN];
char que[MAXLEN];
int head[MAXLEN];
int back[MAXLEN];

void CatchKey(int cur, int l, int r) {
	for (int i = l; i <= r; ++i) {
		que[cur++] = buf[i];
	}
	que[cur++] = '\0';
}
void readKey() {
	int len = 0;
	char ch = getchar();
	while (ch != '\n') {
		if (ch != '\"') {
			que[len++] = ch;
		}
		ch = getchar();
	}
	que[len++] = '\0';
}
void writeValue(int l, int r) {
	for (int i = l; i <= r; ++i) {
		putchar(buf[i]);
	}
	putchar('\n');
}
int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif
	int T, q;
	int u, l, r, x, y;
	scanf("%d%*c", &T);
	while (T--) {
		trie.Init();
		scanf("%s", buf);
		int len = strlen(buf);
		int top = 0, pt1 = 0, pt2 = 0;
		for (int i = 1; i < len - 1; ++i) {
			if (buf[i] == '{') {
				head[top++] = pt1++;
			} else if (buf[i] == '}') {
				back[head[--top]] = i;
			}
		}
		bool flag = false;
		top = u = 0;
		head[top++] = u;
		for (int i = 1; i < len - 1; ++i) {
			if (!flag && buf[i] == '\"') {
				flag = true;
				l = i + 1;
			} else if (flag && buf[i] == '\"') {
				flag = false;
				r = i - 1;
				i += 2;
				if (buf[i] == '{') {
					x = i;
					y = back[pt2++];
				} else {
					x = i++;
					while (i < len && buf[i] != '\"') {
						i++;
					}
					y = i;
				}
				if (top == 1) {
					CatchKey(0, l, r);
				} else {
					que[0] = '.';
					CatchKey(1, l, r);
				}
				u = trie.Insert(que, head[top-1], x, y);
				if (buf[i] == '{') {
					head[top++] = u;
				}
			} else if (buf[i] == '}') {
				top--;
			}
		}
		scanf("%d%*c", &q);
		while (q--) {
			readKey();
			u = trie.Find(que);
			if (u != -1) {
				l = trie.val[u][0];
				r = trie.val[u][1];
				writeValue(l, r);
			} else {
				puts("Error!");
			}
		}
	}
	return 0;
}
