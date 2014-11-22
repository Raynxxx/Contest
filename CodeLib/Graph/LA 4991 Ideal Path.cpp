/*
** LA 4991 Ideal Path
** Created by Rayn @@ 2014/11/14
*/
#include <map>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;
typedef pair<int, int> pii;

const int MAXN = 100005;
const int MAXM = 200005;
const int INF = 0x3F3F3F3F;

struct Edge {
    int u, v, color, next;
    Edge() {}
    Edge(int u, int v, int w, int next) : u(u), v(v), color(w), next(next) {}
};

struct Graph {
    int n, m;
    int st, ed;
    int head[MAXN];
    int dist[MAXN];
    int path[MAXN];
    int level[MAXN];
    Edge edge[MAXM << 1];

    void Init(int n, int st, int ed) {
        this->n = n;
        this->m = 0;
        this->st = st;
        this->ed = ed;
        fill_n(head, n + 1, -1);
    }
    void AddEdge(int u, int v, int w) {
        edge[m] = Edge(u, v, w, head[u]);
        head[u] = m++;
    }
    void bfs_level() {
        fill_n(level, n + 1, 0);
        queue<int> que;
        que.push(ed);
        level[ed] = 0;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i = head[u]; i != -1; i = edge[i].next) {
                int v = edge[i].v;
                if (level[v] == 0 && v != ed) {
                    level[v] = level[u] + 1;
                    que.push(v);
                }
            }
        }
    }
    int Gao(vector<int>& ret) {
        fill_n(path, n + 1, INF);
        fill_n(dist, n + 1, INF);
        queue<pii> que;
        que.push(make_pair(st, 0));
        while (!que.empty()) {
            pii cur = que.front();
            que.pop();
            int u = cur.first;
            int k = level[u];
            if (cur.second > path[k])
                continue;
            for (int i = head[u]; i != -1; i = edge[i].next) {
                int v = edge[i].v;
                if (level[v] == k - 1 && edge[i].color <= path[k - 1]) {
                    path[k - 1] = edge[i].color;
                    if (edge[i].color < dist[v]) {
                        dist[v] = edge[i].color;
                        que.push(make_pair(v, edge[i].color));
                    }
                }
            }
        }
        ret.clear();
        for (int i = level[st] - 1; i >= 0; --i) {
            ret.push_back(path[i]);
        }
        return level[st];
    }
};

Graph Solver;
vector<int> path;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        Solver.Init(n, 1, n);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            Solver.AddEdge(u, v, w);
            Solver.AddEdge(v, u, w);
        }
        Solver.bfs_level();
        printf("%d\n", Solver.Gao(path));
        int sz = path.size();
        for (int i = 0; i < sz; ++i) {
            printf("%d%c", path[i], (i == sz - 1) ? '\n' : ' ');
        }
    }
    return 0;
}
