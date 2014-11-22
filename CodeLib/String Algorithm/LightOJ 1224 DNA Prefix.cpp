/*
** LightOJ 1224 DNA Prefix
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

const int MAXN = 50010;
const int MAXL = 56;
const int MAXNODE = MAXN * MAXL;
const int CharSet = 4;

class Trie {
public:
    int sz;
    int ch[MAXNODE][CharSet];
    int val[MAXNODE];

    void Init() {
        sz = 1;
        val[0] = 0;
        memset(ch[0], 0, sizeof(ch[0]));
    }
    int Index(char ch) {
        if(ch == 'A') {
            return 0;
        } else if(ch == 'G') {
            return 1;
        } else if(ch == 'C') {
            return 2;
        } else {
            return 3;
        }
    }
    void Insert(char *pattern) {
        int u = 0, n = strlen(pattern);
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            if (ch[u][v] == 0) {
                val[sz] = 0;
                memset(ch[sz], 0, sizeof(ch[sz]));
                ch[u][v] = sz++;
            }
            u = ch[u][v];
            val[u]++;
        }
    }
    void Query(int &ret, int u, int dep) {
        ret = max(ret, dep * val[u]);
        for(int i = 0; i < CharSet; ++i) {
            if(ch[u][i]) {
                Query(ret, ch[u][i], dep + 1);
            }
        }
    }
};

Trie Solver;
char buf[MAXL];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--) {
        Solver.Init();
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) {
            scanf("%s", buf);
            Solver.Insert(buf);
        }
        int ret = 0;
        Solver.Query(ret, 0, 0);
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}
