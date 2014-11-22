/*
** POJ 2001 Shortest Prefixes
** Created by Rayn @@ 2014/11/07
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

const int MAXN = 1010;
const int MAXL = 25;
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
            val[u]++;
        }
    }
    string Find(char *pattern) {
        int u = 0, n = strlen(pattern);
        string ret = "";
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            u = ch[u][v];
            ret += pattern[i];
            if(val[u] == 1) {
                return ret;
            }
        }
        return ret;
    }
    void Debug(char *pattern) {
        int u = 0, n = strlen(pattern);
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            u = ch[u][v];
            printf("%c %d\n", pattern[i], val[u]);
        }
    }
};

Trie Solver;
char word[MAXN][MAXL];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Solver.Init();
    int n = 0;
    while(scanf("%s", word[n]) != EOF) {
        Solver.Insert(word[n]);
        ++n;
    }
    for(int i = 0; i < n; ++i) {
        printf("%s %s\n", word[i], Solver.Find(word[i]).c_str());
    }
    return 0;
}
