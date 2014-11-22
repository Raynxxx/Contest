/*
** LightOJ 1129 Consistency Checker
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

const int MAXN = 10005;
const int MAXL = 15;
const int MAXNODE = MAXN * MAXL;
const int CharSet = 10;

class Trie {
public:
    int sz;
    int ch[MAXNODE][CharSet];
    bool occur[MAXNODE];

    void Init() {
        sz = 1;
        occur[0] = false;
        memset(ch[0], 0, sizeof(ch[0]));
    }
    int Index(char ch) {
        return ch - '0';
    }
    void Insert(char *pattern) {
        int u = 0, n = strlen(pattern);
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            if (ch[u][v] == 0) {
                occur[sz] = false;
                memset(ch[sz], 0, sizeof(ch[sz]));
                ch[u][v] = sz++;
            }
            u = ch[u][v];
        }
        occur[u] = true;
    }
    bool Check(char *pattern) {
        int u = 0, n = strlen(pattern);
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            if (occur[u]) {
                return true;
            }
            u = ch[u][v];
        }
        return false;
    }
};

Trie trie;
char phone[MAXN][MAXL];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        trie.Init();
        for (int i = 0; i < n; ++i) {
            scanf("%s", phone[i]);
            trie.Insert(phone[i]);
        }
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            if (trie.Check(phone[i])) {
                ok = false;
                break;
            }
        }
        printf("Case %d: ", ++cases);
        if (ok) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}
