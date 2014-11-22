/*
** ZOJ 3794 Greedy Driver
** Created by Rayn @@ 2014/08/12
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn = 1010;
const int maxm = 100010;
const int INF = 0x3F3F3F3F;
typedef pair<int, int> PII;

int N, M, C, P, Q;
bool fuel[maxn], inq[maxn];
int MaxFuel[maxn], MinUse[maxn];
vector<PII> G1[maxm], G2[maxm];

void Init(int n)
{
    memset(fuel, false, sizeof(fuel));
    for (int i = 0; i <= n; ++i) {
        G1[i].clear();
        G2[i].clear();
    }
}
void SPFA_Find_MaxFuel()
{
    fill(inq, inq+N+1, false);
    fill(MaxFuel, MaxFuel+N+1, -1);
    queue<int> Q;
    MaxFuel[1] = C;
    Q.push(1);
    inq[1] = true;
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        inq[u] = false;
        for(int i = 0; i < (int) G1[u].size(); ++i)
        {
            int v = G1[u][i].first;
            int w = G1[u][i].second;
            if(MaxFuel[u] < w)
                continue;
            if (fuel[v]) {
                if (MaxFuel[v] < C) {
                    MaxFuel[v] = C;
                    if (!inq[v]) {
                        Q.push(v);
                        inq[v] = true;
                    }
                }
            } else {
                if (MaxFuel[v] < MaxFuel[u] - w) {
                    MaxFuel[v] = MaxFuel[u] - w;
                    if (!inq[v]) {
                        Q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
    }
}
void SPFA_Find_MinUse()
{
    fill(inq, inq+N+1, false);
    fill(MinUse, MinUse+N+1, INF);
    queue<int> Q;
    MinUse[N] = 0;
    Q.push(N);
    inq[N] = true;
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        inq[u] = false;
        for(int i = 0; i < (int) G2[u].size(); ++i)
        {
            int v = G2[u][i].first;
            int w = G2[u][i].second;
            if(MinUse[u] > C - w)
                continue;
            if(fuel[v]) {
                if (MinUse[v] > 0) {
                    MinUse[v] = 0;
                    if (!inq[v]) {
                        Q.push(v);
                        inq[v] = true;
                    }
                }
            } else {
                if (MinUse[v] > MinUse[u] + w) {
                    MinUse[v] = MinUse[u] + w;
                    if (!inq[v]) {
                        Q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d%d%d", &N, &M, &C) != EOF)
    {
        Init(N);
        for (int i = 0; i < M; ++i) {
            int A, B, L;
            scanf("%d%d%d", &A, &B, &L);
            G1[A].push_back(make_pair(B, L));
            G2[B].push_back(make_pair(A, L));
        }
        scanf("%d", &P);
        for (int i = 0,x; i < P; ++i) {
            scanf("%d", &x);
            fuel[x] = true;
        }
        SPFA_Find_MaxFuel();
        SPFA_Find_MinUse();

        int res = 0;
        scanf("%d", &Q);
        for (int i = 0; i < Q; ++i) {
            int city, price;
            scanf("%d%d", &city, &price);
            if (MinUse[city] <= C && MaxFuel[city] >= 0) {
                if(fuel[city]) {
                    res = max(res, C * price);
                } else {
                    res = max(res, (MaxFuel[city]-MinUse[city])*price);
                }
            }
        }
        if (MaxFuel[N] == -1)
            puts("-1");
        else
            printf("%d\n", res);
    }
    return 0;
}
