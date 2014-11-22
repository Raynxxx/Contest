/*
** LA 3942 Remember the Word
** Created by Rayn @@ 2014/11/12
*/
#include <set>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;

const int MAXN = 4010;
const int MAXL = 300010;
const int MOD = 20071027;
const int MAXNODE = MAXN * 100;
const int CharSet = 26;

struct Trie {
    int sz;
    int ch[MAXNODE][CharSet];
    int val[MAXNODE];

    void Init() {
        sz = 1;
        val[0] = 0;
        memset(ch[0], 0, sizeof(ch[0]));
    }
    inline int Index(char ch) {
        return ch - 'a';
    }
    void Insert(char *pattern, int c) {
        int u = 0, n = strlen(pattern);
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            if (ch[u][v] == 0) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][v] = sz++;
            }
            u = ch[u][v];
        }
        val[u] = c;
    }
    void FindPrefix(char *pattern, int len, vector<int>& box) {
        int u = 0;
        for (int i = 0; i < len && pattern[i] != '\0'; ++i) {
            int v = Index(pattern[i]);
            if (ch[u][v] == 0) break;
            u = ch[u][v];
            if (val[u] != 0) {
                box.push_back(val[u]);
            }
        }
    }
};

Trie trie;
char text[MAXL];
int dp[MAXL], len[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int S, cases = 0;
    char word[110];
    while (scanf("%s", text) != EOF) {
        scanf("%d", &S);
        int L = strlen(text);
        trie.Init();
        for (int i = 1; i <= S; ++i) {
            scanf("%s", word);
            len[i] = strlen(word);
            trie.Insert(word, i);
        }
        memset(dp, 0, sizeof(dp));
        dp[L] = 1;
        for (int i = L - 1; i >= 0; --i) {
            vector<int> p;
            trie.FindPrefix(text + i, L - i, p);
            for (int j = 0; j < (int) p.size(); ++j) {
                dp[i] = (dp[i] + dp[i + len[p[j]]]) % MOD;
            }
        }
        printf("Case %d: %d\n", ++cases, dp[0]);
    }
    return 0;
}
