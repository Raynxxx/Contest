/*
** HDU 4775 Infinite Go
** Created by Rayn @@ 2014/09/16
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

typedef pair<int, int> PII;
typedef long long LL;
const int MAXN = 10010;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

map<PII, int> id, chess;
set<PII> space[MAXN];

class DisjoinSet {
public:
    int pa[MAXN];

    void Init(int n) {
        for(int i = 0; i <= n; ++i) {
            pa[i] = i;
            space[i].clear();
        }
    }
    int Findset(int x) {
        if(x != pa[x])
            pa[x] = Findset(pa[x]);
        return pa[x];
    }
    void Union(int x, int y) {
        int px = Findset(x), py = Findset(y);
        if(space[px].size() > space[py].size()) {
            pa[py] = px;
            set<PII>::iterator it = space[py].begin();
            for(; it != space[py].end(); ++it) {
                space[px].insert(*it);
            }
            space[py].clear();
        } else {
            pa[px] = py;
            set<PII>::iterator it = space[px].begin();
            for(; it != space[px].end(); ++it) {
                space[py].insert(*it);
            }
            space[px].clear();
        }
    }
};

DisjoinSet us;

void Init(int n)
{
    id.clear();
    chess.clear();
    us.Init(n);
}

void Del(int x, int y, int c)
{
    queue<PII> que;
    que.push(make_pair(x, y));
    while(!que.empty()) {
        PII u = que.front();
        que.pop();
        chess.erase(u);
        for(int i = 0; i < 4; ++i) {
            int px = u.first + dx[i];
            int py = u.second + dy[i];
            if(px <= 0 || py <= 0) continue;
            PII v = make_pair(px, py);
            if(!chess.count(v)) continue;
            if(chess[v] == c) {
                que.push(v);
            } else {
                int vid = us.Findset(id[v]);
                space[vid].insert(u);
            }
        }
    }
}
void put(int x, int y, int c)
{
    PII u = make_pair(x, y);
    chess[u] = c;
    for(int i = 0; i < 4; ++i) {
        int px = x + dx[i];
        int py = y + dy[i];
        if(px <= 0 || py <= 0) continue;
        PII v = make_pair(px, py);
        if(!chess.count(v)) {
            space[us.Findset(id[u])].insert(v);
        } else if(chess[v] == c) {
            us.Union(id[u], id[v]);
        } else {
            int vid = us.Findset(id[v]);
            space[vid].erase(u);
            if(space[vid].empty()) {
                Del(px, py, c^1);
            }
        }
    }
    int uid = us.Findset(id[u]);
    space[uid].erase(u);
    if(space[uid].empty()) {
        Del(x, y, c);
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n;
        scanf("%d", &n);
        Init(n);
        for(int i = 1; i <= n; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            id[make_pair(x, y)] = i;
            put(x, y, i&1);
        }
        int black = 0, white = 0;
        map<PII, int>::iterator it = chess.begin();
        for(; it != chess.end(); ++it) {
            if(it->second == 0) {
                white++;
            } else {
                black++;
            }
        }
        printf("%d %d\n", black, white);
    }
    return 0;
}
