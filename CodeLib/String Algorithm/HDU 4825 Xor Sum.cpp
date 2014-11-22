/*
** HDU 4825 Xor Sum
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
const int MAXL = 33;
const int MAXNODE = MAXN * MAXL;
const int CharSet = 2;

struct Trie {
    int sz;
    int ch[MAXNODE][CharSet];
    Long val[MAXNODE];

    void Init() {
        sz = 1;
        val[0] = 0;
        memset(ch[0], 0, sizeof(ch[0]));
    }
    void Insert(Long w) {
        int u = 0;
        for (int i = 32; i >= 0; --i) {
            int v = (w >> i) & 1;
            if (ch[u][v] == 0) {
                val[sz] = 0;
                memset(ch[sz], 0, sizeof(ch[sz]));
                ch[u][v] = sz++;
            }
            u = ch[u][v];
        }
        val[u] = w;
    }
    Long Find(Long w) {
        int u = 0;
        for (int i = 32; i >= 0; --i) {
            int v = ((w >> i) & 1) ^ 1;
            if (!ch[u][v]) {
                v = v ^ 1;
            }
            u = ch[u][v];
        }
        return val[u];
    }
};

Trie trie;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        trie.Init();
        for (int i = 1; i <= n; ++i) {
            Long K;
            scanf("%I64d\n", &K);
            trie.Insert(K);
        }
        printf("Case #%d:\n", ++cases);
        while (m--) {
            Long S;
            scanf("%I64d", &S);
            printf("%I64d\n", trie.Find(S));
        }
    }
    return 0;
}
