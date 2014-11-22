/*
** LightOJ 1269 Consecutive Sum
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

const int MAXN = 50010;
const int MAXNODE = MAXN * 35;
const int CharSet = 2;

struct Trie {
    int sz;
    int ch[MAXNODE][CharSet];
    int cnt[MAXNODE];

    void Init() {
        sz = 1;
        cnt[0] = 0;
        memset(ch[0], 0, sizeof(ch[0]));
    }
    void Insert(int w) {
        int u = 0;
        for (int i = 30; i >= 0; --i) {
            int v = (w >> i) & 1;
            if (ch[u][v] == 0) {
                cnt[sz] = 0;
                memset(ch[sz], 0, sizeof(ch[sz]));
                ch[u][v] = sz++;
            }
            u = ch[u][v];
            cnt[u]++;
        }
    }
    int FindMax(int w) {
        int ret = 0, u = 0;
        for (int i = 30; i >= 0; --i) {
            int v = ((w >> i) & 1) ^ 1;
            if (ch[u][v]) {
                ret |= (1 << i);
            } else {
                v = v ^ 1;
            }
            u = ch[u][v];
        }
        return ret;
    }
    int FindMin(int w) {
        int ret = 0, u = 0;
        for (int i = 30; i >= 0; --i) {
            int v = (w >> i) & 1;
            if (ch[u][v] == 0 || (ch[u][v^1] && cnt[ch[u][v]] <= 1)) {
                v = v ^ 1;
                ret |= (1 << i);
            }
            u = ch[u][v];
        }
        return ret;
    }
};

Trie trie;
int arr[MAXN];

int main() {
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        trie.Init();
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            arr[i] = arr[i - 1] ^ x;
        }
        for (int i = 0; i <= n; ++i) {
            trie.Insert(arr[i]);
        }
        int maxv = 0, minv = (1LL << 31) - 1;
        for (int i = 0; i <= n; ++i) {
            maxv = max(maxv, trie.FindMax(arr[i]));
            minv = min(minv, trie.FindMin(arr[i]));
        }
        printf("Case %d: %d %d\n", ++cases, maxv, minv); 
    }
    return 0;
}
