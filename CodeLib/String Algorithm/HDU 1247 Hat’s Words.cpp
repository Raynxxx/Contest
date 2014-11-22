/*
** HDU 1247 Hat’s Words
** Created by Rayn @@ 2014/11/06
*/
#include <map>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 50010;
const int MAXL = 105;
const int MAXNODE = MAXN * MAXL;
const int CharSet = 26;

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
        return ch - 'a';
    }
    int new_node() {
        val[sz] = 0;
        memset(ch[sz], 0, sizeof(ch[sz]));
        return sz++;
    }
    void Insert(char *pattern) {
        int u = 0, n = strlen(pattern);
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            if (ch[u][v] == 0) {
                ch[u][v] = new_node();
            }
            u = ch[u][v];
        }
        val[u] = 1;
    }
    bool Find(char *pattern) {
        int u = 0, n = strlen(pattern);
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            if (ch[u][v] == 0) {
                return false;
            }
            u = ch[u][v];
        }
        return val[u];
    }
};

Trie Solver;
char dic[MAXN][MAXL];
char buf[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Solver.Init();
    int n = 0;
    while(scanf("%s", buf) != EOF) {
        strcpy(dic[n++], buf);
        Solver.Insert(buf);
    }
    for(int i = 0; i < n; ++i) {
        int len = strlen(dic[i]);
        for(int j = 1; j < len; ++j) {
            strncpy(buf, dic[i], j);
            buf[j] = '\0';
            //printf("%s + %s\n", buf, dic[i] + j);
            if(Solver.Find(buf) && Solver.Find(dic[i] + j)) {
                printf("%s\n", dic[i]);
                break;
            }
        }
    }
    return 0;
}
