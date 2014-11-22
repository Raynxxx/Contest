/*
** HDU 1298 T9
** Created by Rayn @@ 2014/11/06
*/
#include <map>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 1010;
const int MAXL = 110;
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
    void Insert(char *pattern, int x) {
        int u = 0, n = strlen(pattern);
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            if (ch[u][v] == 0) {
                ch[u][v] = new_node();
            }
            u = ch[u][v];
            val[u] += x;
        }
    }
    void Debug(char *pattern) {
        int u = 0, n = strlen(pattern);
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            printf("%c %d\n", pattern[i], val[u]);
            u = ch[u][v];
        }
    }
};

const char board[10][5] = {
    "", "", "abc", "def",
    "ghi",  "jkl", "mno",
    "pqrs", "tuv", "wxyz"
};

Trie Solver;
int maxc[MAXL];
char buf[MAXL];
char tmp[MAXL];
char ret[MAXL][MAXL];

void Search(char *word, int dep, int u) {
    if(dep > 0) {
        if(Solver.val[u] > maxc[dep]) {
            maxc[dep] = Solver.val[u];
            strncpy(ret[dep], tmp, dep);
        }
    }
    if(word[dep] == '\0' || word[dep] == '1') {
        return ;
    }
    int x = word[dep] - '0';
    for(int i = 0; board[x][i] != '\0'; ++i) {
        int v = Solver.Index(board[x][i]);
        if(Solver.ch[u][v] == 0)
            continue;
        tmp[dep] = board[x][i];
        Search(word, dep + 1, Solver.ch[u][v]);
    }
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--) {
        int n, m;
        scanf("%d", &n);
        Solver.Init();
        for(int i = 0, p; i < n; ++i) {
            scanf("%s%d", buf, &p);
            Solver.Insert(buf, p);
        }
        //Solver.Debug("hell");
        printf("Scenario #%d:\n", ++cases);
        scanf("%d", &m);
        while(m--) {
            scanf("%s", buf);
            fill_n(maxc, MAXL, 0);
            Search(buf, 0, 0);
            for(int x = 1; buf[x - 1] != '1'; ++x) {
                if(maxc[x] == 0) {
                    puts("MANUALLY");
                } else {
                    for(int i = 0; i < x; ++i) {
                        putchar(ret[x][i]);
                    }
                    putchar('\n');
                }
            }
            putchar('\n');
        }
        putchar('\n');
    }
    return 0;
}
