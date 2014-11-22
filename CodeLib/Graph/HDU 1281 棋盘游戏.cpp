/*
** HDU 1281 ∆Â≈Ã”Œœ∑
** Created by Rayn @@ 2014/07/17
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 110;

struct Edge
{
    int from, to, weight;
    Edge() {}
    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}
};

struct Hungarian
{
    int left, right;
    int tab[MAXN][MAXN];
    int link[MAXN];
    bool used[MAXN];

    void Init(int n, int m)
    {
        this->left = n;
        this->right = m;
        memset(tab, 0, sizeof(tab));
    }
    void AddEdge(int from, int to, int weight)
    {
        tab[from][to] = weight;
    }
    bool Find(int u)
    {
        for(int i = 1; i <= right; ++i)
        {
            if(!used[i] && tab[u][i])
            {
                used[i] = true;
                if(link[i] == -1 || Find(link[i]))
                {
                    link[i] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int MaxMatch()
    {
        int cnt = 0;
        memset(link, -1, sizeof(link));
        for(int i = 1; i <= left; ++i)
        {
            memset(used, false, sizeof(used));
            if(Find(i)) {
                cnt++;
            }
        }
        return cnt;
    }
};

Hungarian Solver;
int x[MAXN], y[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int n, m, k;
    int cases = 0;
    while(scanf("%d%d%d", &n, &m, &k) != EOF)
    {
        Solver.Init(n, m);
        for(int i = 0; i < k; ++i)
        {
            scanf("%d%d", &x[i], &y[i]);
            Solver.AddEdge(x[i], y[i], 1);
        }
        int match = Solver.MaxMatch();
        int cnt = 0;
        for(int i = 0; i < k; ++i)
        {
            Solver.AddEdge(x[i], y[i], 0);
            if(Solver.MaxMatch() < match)
                cnt++;
            Solver.AddEdge(x[i], y[i], 1);
        }
        printf("Board %d have %d important blanks for %d chessmen.\n", ++cases, cnt, match);
    }
    return 0;
}
