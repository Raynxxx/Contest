/*
** HDU 5098 Smart Software Installer
** Created by Rayn @@ 2014/11/03
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <string>
#include <cctype>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long Long;
const int MAXN = 1010;

struct Edge {
    int u, v, next;
    Edge() {}
    Edge(int u, int v, int next) : u(u), v(v), next(next) {}
};

Edge edge[MAXN * MAXN];
int nEdge, head[MAXN];
int vcnt, dp[MAXN];
int restart[MAXN];
int degree[MAXN];
bool vis[MAXN];
map<string, int> refer;

void Init() {
    vcnt = nEdge = 0;
    refer.clear();
    fill_n(head, MAXN, -1);
    fill_n(vis, MAXN, false);
    fill_n(restart, MAXN, 0);
    fill_n(degree, MAXN, 0);
    fill_n(dp, MAXN, 0);
}
void AddEdge(int u, int v) {
    edge[nEdge] = Edge(u, v, head[u]);
    head[u] = nEdge++;
}
int dfs(int u) {
    if (dp[u]) return dp[u];
    int ret = 0;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        ret = max(ret, dfs(v));
    }
    return dp[u] = ret + restart[u];
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    string buf;
    int n, cases = 0;
    scanf("%d", &n);
    getline(cin, buf);
    getline(cin, buf);
    while (n--) {
        Init();
        while (getline(cin, buf) && buf != "") {
            istringstream scin(buf);
            string tmp, id1, id2;
            scin >> tmp;
            int len = tmp.length();
            bool flag = false;
            for (int i = 0; i < len && tmp[i] != ':'; ++i) {
                if (tmp[i] == '*') {
                    flag = true;
                } else {
                    id1 += tmp[i];
                }
            }
            if (refer.find(id1) == refer.end()) {
                refer[id1] = ++vcnt;
            }
            restart[refer[id1]] = flag;
            while (scin >> id2) {
                if (refer.find(id2) == refer.end()) {
                    refer[id2] = ++vcnt;
                }
                AddEdge(refer[id2], refer[id1]);
                degree[refer[id1]]++;
            }
        }
        int ret = 0;
        for (int i = 1; i <= vcnt; ++i) {
            if (degree[i] == 0) {
                ret = max(ret, dfs(i));
            }
        }
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}
