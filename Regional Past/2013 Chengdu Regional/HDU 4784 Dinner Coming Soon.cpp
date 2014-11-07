/*
** HDU 4784 Dinner Coming Soon
** Created by Rayn @@ 2014/10/28
*/
#include <map>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;
const int INF = 0x3F3F3F3F;
const int MAXN = 110;
const int MAXM = 210;
const int MAXT = 210;
const int MAXB = 6;
const int MAXK = 6;

struct Edge {
	int v, time, money;
	int next;
	Edge() {}
	Edge(int v, int t, int m, int next) : v(v), time(t), money(m), next(next) {}
};

Edge edge[MAXM];
int nEdge, head[MAXN];

void GraphClear(int n) {
	nEdge = 0;
	fill_n(head, n + 5, -1);
}
void AddEdge(int u, int v, int time, int money) {
	edge[nEdge] = Edge(v, time, money, head[u]);
	head[u] = nEdge++;
}

struct State {
	int city, time, k, salt;
	State() {}
	State(int u, int t, int k, int s): city(u), time(t), k(k), salt(s) {}
	bool operator < (const State& rhs) const {
		return time > rhs.time;
	}
};

int N, M, B, K, R, T;
int price[MAXK][MAXN];
int dist[MAXN][MAXT][MAXK][MAXB];
bool inq[MAXN][MAXT][MAXK][MAXB];

void PushState(priority_queue<State>& pq, const State& s, int money) {
	dist[s.city][s.time][s.k][s.salt] = money;
	if (!inq[s.city][s.time][s.k][s.salt]) {
		pq.push(s);
		inq[s.city][s.time][s.k][s.salt] = true;
	}
}
int spfa(int st, int ed) {
	memset(dist, -1, sizeof(dist));
	memset(inq, false, sizeof(inq));
	priority_queue<State> pq;
	PushState(pq, State(st, 0, 0, 0), R);
	bool arrive = false;
	while (!pq.empty()) {
		State cur = pq.top();
		pq.pop();
		if (cur.city == ed) continue;
		if (cur.time > T) break;

		int u = cur.city;
		//cur universe
		for (int i = head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			int money = dist[u][cur.time][cur.k][cur.salt] - edge[i].money;
			int time = cur.time + edge[i].time;
			if (time > T || money < 0) continue;
			if (v == ed && cur.k != 0) continue;
			if (v == ed && cur.k == 0) {
				arrive = true;
			}
			State next = State(v, time, cur.k, cur.salt);
			if (u != st && u != ed) {
				//buy one bag of salt
				if (cur.salt + 1 <= B && money - price[cur.k][u] > dist[next.city][next.time][next.k][cur.salt + 1]) {
					next.salt = cur.salt + 1;
					PushState(pq, next, money - price[cur.k][u]);
				}
				//sell one bag of salt
				if (cur.salt - 1 >= 0 && money + price[cur.k][u] > dist[next.city][next.time][next.k][cur.salt - 1]) {
					next.salt = cur.salt - 1;
					PushState(pq, next, money + price[cur.k][u]);
				}
			}
			//do nothing
			if (money > dist[v][time][next.k][cur.salt]) {
				next.salt = cur.salt;
				PushState(pq, next, money);
			}
		}
		//transported to the another universe
		if (u != st && u != ed) {
			int money = dist[u][cur.time][cur.k][cur.salt];
			State next = State(u, cur.time + 1, (cur.k + 1) % K, cur.salt);
			if (next.time > T) continue;
			//buy one bag of salt
			if (cur.salt + 1 <= B && money - price[cur.k][u] > dist[u][next.time][next.k][cur.salt + 1]) {
				next.salt = cur.salt + 1;
				PushState(pq, next, money - price[cur.k][u]);
			}
			//sell one bag of salt
			if (cur.salt - 1 >= 0 && money + price[cur.k][u] > dist[u][next.time][next.k][cur.salt - 1]) {
				next.salt = cur.salt - 1;
				PushState(pq, next, money + price[cur.k][u]);
			}
			//do nothing
			if (money > dist[u][next.time][next.k][cur.salt]) {
				next.salt = cur.salt;
				PushState(pq, next, money);
			}
		}
	}
	if (!arrive) return -1;
	int ret = 0;
	for (int i = 0; i <= T; ++i) {
		for (int j = 0; j <= B; ++j) {
			ret = max(ret, dist[ed][i][0][j]);
		}
	}
	return ret;
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int C, cases = 0;
	scanf("%d", &C);
	while (C--) {
		scanf("%d%d%d%d%d%d", &N, &M, &B, &K, &R, &T);
		for (int i = 0; i < K; ++i) {
			for (int j = 1; j <= N; ++j) {
				scanf("%d", &price[i][j]);
			}
		}
		GraphClear(N);
		for (int i = 0; i < M; ++i) {
			int a, b, t, m;
			scanf("%d%d%d%d", &a, &b, &t, &m);
			AddEdge(a, b, t, m);
		}
		int ret = spfa(1, N);
		printf("Case #%d: ", ++cases);
		if (ret != -1) {
			printf("%d\n", ret);
		} else {
			printf("Forever Alone\n");
		}
	}
	return 0;
}
