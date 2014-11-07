/*
** HDU 5071 Chat
** Created by Rayn @@ 2014/10/28
*/
#include <map>
#include <queue>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

struct Window {
	int u;
	Long w;
	Window() {}
	Window(int u, Long w) : u(u), w(w) {}
};

map<int, Long> words;
queue<Window> manager;
bool OnTop;
int TopGirl;

void Clear() {
	OnTop = false;
	TopGirl = -1;
	words.clear();
	while (!manager.empty()) {
		manager.pop();
	}
}
void Add(int u) {
	if (!words.count(u)) {
		puts("success.");
		manager.push(Window(u, 0));
		words[u] = 0;
	} else {
		puts("same priority.");
	}
}
void Close(int u) {
	if (!words.count(u)) {
		puts("invalid priority.");
	} else {
		queue<Window> tmp;
		while (!manager.empty()) {
			Window top = manager.front();
			manager.pop();
			if (top.u == u) {
				printf("close %d with %I64d.\n", u, words[u]);
			} else {
				tmp.push(top);
			}
		}
		manager = tmp;
		words.erase(words.find(u));
		if (OnTop && TopGirl == u) {
			OnTop = false;
			TopGirl = -1;
		}
	}
}
void Chat(int w) {
	if (OnTop == true) {
		words[TopGirl] += w;
		puts("success.");
		return ;
	}
	if (!manager.empty()) {
		Window top = manager.front();
		words[top.u] += w;
		top.w += w;
		puts("success.");
	} else {
		puts("empty.");
	}
}
void Rotate(int x) {
	if (x < 1 || x >(int) manager.size()) {
		puts("out of range.");
		return;
	}
	int idx = 0;
	Window top;
	queue<Window> tmp;
	while (!manager.empty()) {
		Window cur = manager.front();
		manager.pop();
		if (++idx == x) {
			top = cur;
		} else {
			tmp.push(cur);
		}
	}
	manager.push(top);
	while (!tmp.empty()) {
		manager.push(tmp.front());
		tmp.pop();
	}
	puts("success.");
}
void Prior() {
	if (manager.empty()) {
		puts("empty.");
		return;
	}
	int maxu = -1;
	queue<Window> tmp(manager);
	while (!tmp.empty()) {
		Window cur = tmp.front();
		tmp.pop();
		maxu = max(maxu, cur.u);
	}
	Window top;
	while (!manager.empty()) {
		Window cur = manager.front();
		manager.pop();
		if (cur.u == maxu) {
			top = cur;
		} else {
			tmp.push(cur);
		}
	}
	manager.push(top);
	while (!tmp.empty()) {
		manager.push(tmp.front());
		tmp.pop();
	}
	puts("success.");
}
void Choose(int u) {
	if (!words.count(u)) {
		puts("invalid priority.");
	} else {
		Window top;
		queue<Window> tmp;
		while (!manager.empty()) {
			Window cur = manager.front();
			manager.pop();
			if (cur.u == u) {
				top = cur;
			} else {
				tmp.push(cur);
			}
		}
		manager.push(top);
		while (!tmp.empty()) {
			manager.push(tmp.front());
			tmp.pop();
		}
		puts("success.");
	}
}
void Top(int u) {
	if (words.count(u)) {
		OnTop = true;
		TopGirl = u;
		puts("success.");
	} else {
		puts("invalid priority.");
	}
}
void UnTop() {
	if (OnTop == true) {
		OnTop = false;
		TopGirl = -1;
		puts("success.");
	} else {
		puts("no such person.");
	}
}
void Bye() {
	if (OnTop && words[TopGirl] > 0) {
		printf("Bye %d: %I64d\n", TopGirl, words[TopGirl]);
	}
	while (!manager.empty()) {
		Window cur = manager.front();
		manager.pop();
		if (OnTop && cur.u == TopGirl) {
			continue;
		}
		if (words[cur.u] > 0) {
			printf("Bye %d: %I64d\n", cur.u, words[cur.u]);
		}
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T, n;
	char cmd[20];
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		Clear();
		for (int i = 1; i <= n; ++i) {
			scanf("%s", cmd);
			printf("Operation #%d: ", i);
			if (strcmp(cmd, "Add") == 0) {
				int u;
				scanf("%d", &u);
				Add(u);;
			} else if (strcmp(cmd, "Close") == 0) {
				int u;
				scanf("%d", &u);
				Close(u);
			} else if (strcmp(cmd, "Chat") == 0) {
				int w;
				scanf("%d", &w);
				Chat(w);
			} else if (strcmp(cmd, "Rotate") == 0) {
				int x;
				scanf("%d", &x);
				Rotate(x);
			} else if (strcmp(cmd, "Prior") == 0) {
				Prior();
			} else if (strcmp(cmd, "Choose") == 0) {
				int u;
				scanf("%d", &u);
				Choose(u);
			} else if (strcmp(cmd, "Top") == 0) {
				int u;
				scanf("%d", &u);
				Top(u);
			} else if (strcmp(cmd, "Untop") == 0) {
				UnTop();
			}
		}
		Bye();
	}
	return 0;
}
