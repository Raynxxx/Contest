/*
** HDU 4096 Universal Question Answering System
** Created by Rayn @@ 2014/10/07
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
#include <sstream>
#include <algorithm>

class String {
public:
	const static int L = 15;
	char ch[L];
	int length;

	void Fix() {
		ch[length - 1] = '\0';
		length--;
	}
	bool read() {
		scanf("%s", ch);
		length = strlen(ch);
		if (ch[length - 1] == '.' || ch[length - 1] == '?' || ch[length - 1] == '!') {
			return false;
		}
		return true;
	}
	bool operator < (const String& rhs) const {
		return strcmp(ch, rhs.ch) < 0;
	}
	bool operator == (const String& rhs) const {
		return strcmp(ch, rhs.ch) == 0;
	}
	bool operator != (const String& rhs) const {
		return strcmp(ch, rhs.ch) != 0;
	}
};

struct Graph {
	int u, v, next;
	Graph() {}
	Graph(int u, int v, int next) : u(u), v(v), next(next) {}
};

using namespace std;
typedef long long LL;
typedef map<String, int> HashStr;
const int MAXN = 1048;
const int MAXM = 15;

HashStr Noun, Verb;
Graph Edge[MAXN*MAXN];
String Phrase[MAXM];
int EdgeId, PhraseId;
int head[MAXN];
bool vis[MAXN];

void Init() {
	EdgeId = PhraseId = 0;
	Noun.clear();
	Verb.clear();
	memset(head, -1, sizeof(head));
}
void AddEdge(int u, int v) {
	Edge[EdgeId] = Graph(u, v, head[u]);
	head[u] = EdgeId++;
}
int GetID(const String& phrase, HashStr& box) {
	if (box.find(phrase) == box.end()) {
		box[phrase] = PhraseId++;
	}
	return box[phrase];
}
bool Judge(int u, int aim) {
	if (u == aim) return true;
	vis[u] = true;
	for (int i = head[u]; i != -1; i = Edge[i].next) {
		int v = Edge[i].v;
		if (!vis[v]) {
			if (Judge(v, aim)) {
				return true;
			}
		}
	}
	return false;
}
void Statement(String word[], int sz) {
	if (sz == 3) {
		if (word[1].ch[0] == 'a') {
			//noun_phrase are noun_phrase.
			int u = GetID(word[0], Noun);
			int v = GetID(word[2], Noun);
			AddEdge(u, v);
		} else {
			//noun_phrase can verb_phrase.
			int u = GetID(word[0], Noun);
			int v = GetID(word[2], Verb);
			AddEdge(u, v);
		}
	}
	else {
		if (word[4].ch[0] == 'a') {
			//everything which can verb_phrase are noun_phrase.
			int u = GetID(word[3], Verb);
			int v = GetID(word[5], Noun);
			AddEdge(u, v);
		}
		else {
			//everything which can verb_phrase can verb_phrase.
			int u = GetID(word[3], Verb);
			int v = GetID(word[5], Verb);
			AddEdge(u, v);
		}
	}
}
bool Question(String word[], int sz) {
	memset(vis, false, sizeof(vis));
	if (sz == 3) {
		if (word[0].ch[0] == 'a') {
			//are noun_phrase noun_phrase?
			int u = GetID(word[1], Noun);
			int v = GetID(word[2], Noun);
			return Judge(u, v);
		} else {
			//can noun_phrase verb_phrase?
			int u = GetID(word[1], Noun);
			int v = GetID(word[2], Verb);
			return Judge(u, v);
		}
	} else {
		if (word[0].ch[0] == 'c') {
			//can everything which can verb_phrase verb_phrase?
			int u = GetID(word[4], Verb);
			int v = GetID(word[5], Verb);
			return Judge(u, v);
		} else {
			//are everything which can verb_phrase noun_phrase?
			int u = GetID(word[4], Verb);
			int v = GetID(word[5], Noun);
			return Judge(u, v);
		}
	}
	return false;
}

int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T, cases = 0;
	scanf("%d", &T);
	while (T--) {
		Init();
		printf("Case #%d:\n", ++cases);
		while (true) {
			int sz = 0;
			while (Phrase[sz++].read());

			int len = Phrase[sz - 1].length;
			if (Phrase[sz - 1].ch[len - 1] == '!') {
				puts("");
				break;
			}
			if (Phrase[sz - 1].ch[len - 1] == '.') {
				Phrase[sz - 1].Fix();
				Statement(Phrase, sz);
			} else {
				Phrase[sz - 1].Fix();
				putchar(Question(Phrase, sz) ? 'Y' : 'M');
			}
		}
	}
	return 0;
}
