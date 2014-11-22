/*
** CF 282E Sausage Maximization
** Created by Rayn @@ 2014/11/09
*/
#include <set>
#include <map>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 100010;
const int MAXNODE = MAXN * 64;
const int CharSet = 2;

struct Trie {
    int sz;
    int ch[MAXNODE][CharSet];

    void Init() {
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
    }
    void Insert(Long w) {
        int u = 0;
        for (int i = 60; i >= 0; --i) {
            int v = (w >> i) & 1;
            if (ch[u][v] == 0) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                ch[u][v] = sz++;
            }
            u = ch[u][v];
        }
    }
    Long Find(Long w) {
        int u = 0;
        Long ret = 0;
        for (int i = 60; i >= 0; --i) {
            int v = ((w >> i) & 1) ^ 1;
            if (ch[u][v]) {
                ret |= (1LL << i);
            } else {
                v = v ^ 1;
            }
            u = ch[u][v];
        }
        return ret;
    }
};

Trie trie;
Long sausage[MAXN], prefix[MAXN], suffix[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%I64d", &sausage[i]);
        }
        prefix[0] = suffix[n + 1] = 0;
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] ^ sausage[i];
        }
        for (int i = n; i >= 1; --i) {
            suffix[i] = suffix[i + 1] ^ sausage[i];
        }
        Long ret = 0;
        trie.Init();
        for (int i = 0; i <= n; ++i) {
            trie.Insert(prefix[i]);
            ret = max(ret, trie.Find(suffix[i + 1]));
        }
        printf("%I64d\n", ret);
    }
    return 0;
}
