/*
** POJ 2513 Colored Sticks
** Created by Rayn @@ 2014/11/07
*/
#include <map>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;
typedef pair<int, int> PII;

const int MAXN = 500010;
const int MAXL = 15;
const int MAXNODE = MAXN * MAXL;
const int CharSet = 26;

class Trie {
public:
    int sz;
    int ch[MAXNODE][CharSet];
    int val[MAXNODE];

    void Init();
    int Index(char ch);
    int Insert(char *pattern);
};

Trie Solver;
int V, E;
int pa[MAXN];
int degree[MAXN];
PII edge[MAXN];

int FindSet(int x) {
    if(x != pa[x])
        pa[x] = FindSet(pa[x]);
    return pa[x];
}
bool EulerPath(int V, int E) {
    int cnt = 0;
    for(int i = 1; i <= V; ++i) {
        if(degree[i] & 1) {
            cnt++;
        }
        if(cnt > 2) return false;
    }
    for(int i = 0; i < E; ++i) {
        int px = FindSet(edge[i].first);
        int py = FindSet(edge[i].second);
        if(px != py) {
            pa[px] = py;
        }
    }
    for(int i = 2; i <= V; ++i) {
        if(FindSet(i) != FindSet(1)) {
            return false;
        }
    }
    return true;
}

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Solver.Init();
    V = E = 0;
    char c1[MAXL], c2[MAXL];
    while(scanf("%s%s", c1, c2) != EOF) {
        int u = Solver.Insert(c1);
        int v = Solver.Insert(c2);
        degree[u]++;
        degree[v]++;
        edge[E++] = make_pair(u, v);
    }
    if(EulerPath(V, E)) {
        puts("Possible");
    } else {
        puts("Impossible");
    }
    return 0;
}

void Trie::Init() {
    sz = 1;
    val[0] = 0;
    memset(ch[0], 0, sizeof(ch[0]));
}
int Trie::Index(char ch) {
    return ch - 'a';
}
int Trie::Insert(char *pattern) {
    int u = 0, n = strlen(pattern);
    for (int i = 0; i < n; ++i) {
        int v = Index(pattern[i]);
        if (ch[u][v] == 0) {
            val[sz] = 0;
            memset(ch[sz], 0, sizeof(ch[sz]));
            ch[u][v] = sz++;
        }
        u = ch[u][v];
    }
    if(val[u] == 0) {
        val[u] = ++V;
        pa[V] = V;
        degree[V] = 0;
    }
    return val[u];
}
