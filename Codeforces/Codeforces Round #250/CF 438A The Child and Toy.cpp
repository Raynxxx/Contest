/*
** CF 438A The Child and Toy
** Created by Rayn @@ 2014/10/01
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 1005;
const int MAXM = 2005;

struct Node
{
    int id;
    int v;
    Node() {}
    Node(int id, int v): id(id), v(v) {}
    bool operator < (const Node& rhs) const {
        return v > rhs.v;
    }
};

int value[MAXN];
bool removed[MAXN];
Node part[MAXN];
vector<int> G[MAXN];
vector<int>::iterator it;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        memset(removed, false, sizeof(removed));
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &value[i]);
            part[i] = Node(i, value[i]);
            G[i].clear();
        }
        sort(part+1, part+1+n);
        for(int i = 0; i < m; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            G[x].push_back(y);
            G[y].push_back(x);
        }
        LL energy = 0LL;
        for(int i = 1; i <= n; ++i) {
            int u = part[i].id;
            for(it = G[u].begin(); it != G[u].end(); ++it) {
                int v = *it;
                if(!removed[v]) {
                    energy += value[v];
                }
            }
            removed[u] = true;
        }
        printf("%I64d\n", energy);
    }
    return 0;
}
