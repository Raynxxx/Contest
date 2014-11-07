/*
** HDU 5093 Battle ships
** Created by Rayn @@ 2014/11/02
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <string>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long Long;
const int MAXN = 60;
const int MAXM = 2500;

struct Edge {
    int u, v;
    Edge() {}
    Edge(int u, int v) : u(u), v(v) {}
};

class Hungarian {
public:
    int n, m;
    vector<Edge> edge;
    vector<int> head[MAXM];
    int link[MAXM];
    bool used[MAXM];
    typedef vector<int>::iterator Iter;

    void Init(int n, int m) {
        this->n = n;
        this->m = m;
        for (int i = 0; i <= n + m; ++i) {
            head[i].clear();
        }
        edge.clear();
    }
    void AddEdge(int u, int v) {
        edge.push_back(Edge(u, v));
        head[u].push_back(edge.size() - 1);
        edge.push_back(Edge(v, u));
        head[v].push_back(edge.size() - 1);
    }
    bool Find(int u) {
        for (Iter it = head[u].begin(); it != head[u].end(); ++it) {
            int v = edge[*it].v;
            if (!used[v]) {
                used[v] = true;
                if (link[v] == -1 || Find(link[v])) {
                    link[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int MaxMatch() {
        int cnt = 0;
        fill_n(link, n + m + 1, -1);
        for (int i = 1; i <= n; ++i) {
            fill_n(used, n + m + 1, false);
            if (Find(i)) cnt++;
        }
        return cnt;
    }
};

Hungarian Solver;
char maze[MAXN][MAXN];
int row[MAXN][MAXN], RowCnt;
int col[MAXN][MAXN], ColCnt;

void InitData(int&m, int& n) {
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; ++i) {
        scanf("%s", maze[i]);
    }
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    for (int i = 0, id = 1; i < m; ++i, ++id) {
        for (int j = 0; j < n; ++j) {
            if (maze[i][j] == '*') {
                row[i][j] = id;
            } else if (maze[i][j] == '#') {
                ++id;
            }
        }
    }
    for (int j = 0, id = 1; j < n; ++j, ++id) {
        for (int i = 0; i < m; ++i) {
            if (maze[i][j] == '*') {
                col[i][j] = id;
            } else if (maze[i][j] == '#') {
                ++id;
            }
        }
    }
}
void PreBuild(int m, int n) {
    RowCnt = ColCnt = 0;
    int pre = -1;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (row[i][j]) {
                if (row[i][j] == pre) {
                    row[i][j] = RowCnt;
                } else {
                    pre = row[i][j];
                    row[i][j] = ++RowCnt;
                }
            }
        }
    }
    pre = -1;
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            if (col[i][j]) {
                if (col[i][j] == pre) {
                    col[i][j] = ColCnt;
                } else {
                    pre = col[i][j];
                    col[i][j] = ++ColCnt;
                }
            }
        }
    }
}
void BuildGraph(int m, int n, int& ret) {
    Solver.Init(RowCnt, ColCnt);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (row[i][j] && col[i][j]) {
                Solver.AddEdge(row[i][j], col[i][j] + RowCnt);
            }
        }
    }
    ret = Solver.MaxMatch();
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--) {
        int m, n, ret;
        InitData(m, n);
        PreBuild(m, n);
        BuildGraph(m, n, ret);
        printf("%d\n", ret);
    }
    return 0;
}
