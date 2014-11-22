/*
** ZOJ 3545 Rescue the Rabbit
** Created by Rayn @@ 2014/09/16
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1 << 28;
const int MAXN = 1024;
const int CHARSET = 4;

struct AhoCorasick {

    int root, sz;
    int tag[MAXN];
    int fail[MAXN];
    int trie[MAXN][CHARSET];

    int new_node() {
        tag[sz] = 0;
        fill(trie[sz], trie[sz] + CHARSET, -1);
        return sz++;
    }
    void init() {
        sz = 0;
        root = new_node();
    }
    int idx(char ch) {
        switch(ch) {
            case 'A': return 0;
            case 'C': return 1;
            case 'G': return 2;
            default : return 3; //'T'
        }
    }
    void Insert(const char* buf, int k) {
        int len = strlen(buf);
        int cur = root;
        for(int i = 0; i < len; ++i) {
            int c = idx(buf[i]);
            if(trie[cur][c] == -1) {
                trie[cur][c] = new_node();
            }
            cur = trie[cur][c];
        }
        tag[cur] |= (1 << k);
    }
    void Build() {
        queue<int> q;
        for(int i = 0; i < CHARSET; ++i) {
            if(trie[root][i] == -1) {
                trie[root][i] = root;
            } else {
                fail[trie[root][i]] = root;
                q.push(trie[root][i]);
            }
        }
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            tag[cur] |= tag[fail[cur]];
            for(int i = 0; i < CHARSET; ++i) {
                if(trie[cur][i] == -1) {
                    trie[cur][i] = trie[fail[cur]][i];
                } else {
                    fail[trie[cur][i]] = trie[fail[cur]][i];
                    q.push(trie[cur][i]);
                }
            }
        }
    }
};

AhoCorasick ac;
int N, L, w[20];
char DNA[MAXN];
bool vis[MAXN][MAXN];
vector<int> dp[2][MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d", &N, &L) != EOF)
    {
        ac.init();
        for(int i = 0; i < N; ++i) {
            scanf("%s%d", DNA, &w[i]);
            ac.Insert(DNA, i);
        }
        ac.Build();
        int cur = 0, pre = 1;
        for(int s = 0; s < (1 << N); ++s) {
            dp[cur][s].clear();
        }
        dp[cur][0].push_back(ac.root);
        for(int i = 1; i <= L; ++i) {
            swap(cur, pre);
            memset(vis, false, sizeof(vis));
            for(int s = 0; s < (1 << N); ++s) {
                dp[cur][s].clear();
            }
            for(int s = 0; s < (1 << N); ++s) {
                vector<int>::iterator it;
                for(it = dp[pre][s].begin(); it != dp[pre][s].end(); ++it) {
                    for(int k = 0; k < CHARSET; ++k) {
                        int id = ac.trie[*it][k];
                        int status = s | ac.tag[id];
                        if(!vis[status][id]) {
                            dp[cur][status].push_back(id);
                            vis[status][id] = true;
                        }
                    }
                }
            }
        }
        int res = -INF;
        for(int s = 0; s < (1 << N); ++s) {
            if(!dp[cur][s].empty()) {
                int get = 0;
                for(int i = 0; i < N; ++i) {
                    if((s >> i) & 1) {
                        get += w[i];
                    }
                }
                res = max(res, get);
            }
        }
        if(res < 0) {
            printf("No Rabbit after 2012!\n");
        } else {
            printf("%d\n", res);
        }
    }
    return 0;
}
