/*
** POJ 3764 The xor-longest Path
** Created by Rayn @@ 2014/11/08
*/
#include <map>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 100010;
const int MAXL = 32;
const int MAXNODE = MAXN * MAXL;
const int CharSet = 2;

struct Edge {
    int u, v, w, next;
    Edge() {}
    Edge(int u, int v, int w, int next) : u(u), v(v), w(w), next(next) {}
};

struct Trie {
    int sz;
    int ch[MAXNODE][CharSet];

    void Init() {
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
    }
    void Insert(int val) {
        int u = 0;
        for (int i = 31; i >= 0; --i) {
            int v = (val >> i) & 1;
            if (ch[u][v] == 0) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                ch[u][v] = sz++;
            }
            u = ch[u][v];
        }
    }
    int Find(int s) {
        int u = 0, ret = 0;
        for (int i = 31; i >= 0; --i) {
            int v = ((s >> i) & 1) ^ 1;
            if (ch[u][v]) {
                ret |= (1 << i);
            }
            else {
                v = v ^ 1;
            }
            u = ch[u][v];
        }
        return ret;
    }
};

Edge edge[MAXN << 1];
int nEdge, head[MAXN];
Trie trie;
vector<int> rec;

void GraphInit(int n) {
    nEdge = 0;
    rec.clear();
    fill_n(head, n + 3, -1);
}
void AddEdge(int u, int v, int w) {
    edge[nEdge] = Edge(u, v, w, head[u]);
    head[u] = nEdge++;
}
void Process(int u, int pre, int w) {
    trie.Insert(w);
    rec.push_back(w);
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if (v == pre) continue;
        Process(v, u, w ^ edge[i].w);
    }
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while (scanf("%d", &n) != EOF) {
        GraphInit(n);
        trie.Init();
        for (int i = 1; i < n; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            AddEdge(u, v, w);
            AddEdge(v, u, w);
        }
        Process(0, 0, 0);
        int ret = 0;
        for (int i = 0; i < (int)rec.size(); ++i) {
            ret = max(ret, trie.Find(rec[i]));
        }
        printf("%d\n", ret);
    }
    return 0;
}