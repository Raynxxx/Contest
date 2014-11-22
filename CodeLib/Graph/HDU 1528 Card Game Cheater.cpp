/*
** HDU 1528 Card Game Cheater
** Created by Rayn @@ 2014/07/20
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 110;

struct Edge
{
    int from, to, weight;
    Edge(int from, int to, int weight):
        from(from), to(to), weight(weight) {}
};

struct Hungarian
{
    int n;
    vector<Edge> edge;
    vector<int> G[MAXN];
    bool used[MAXN];
    int link[MAXN];

    void Init(int n)
    {
        this->n = n;
        for(int i = 0; i <= n; ++i)
        {
            G[i].clear();
        }
        edge.clear();
        edge.reserve(MAXN);
    }
    void AddEdge(int from, int to, int weight)
    {
        edge.push_back(Edge(from, to, weight));
        int m = edge.size();
        G[from].push_back(m-1);
    }
    int MaxMatch()
    {
        int sum = 0;
        memset(link, -1, sizeof(link));
        for(int i = 1; i <= n; ++i)
        {
            memset(used, false, sizeof(used));
            if(Find(i))
                sum++;
        }
        return sum;
    }
    bool Find(int u)
    {
        for(int i = 0; i < (int) G[u].size(); ++i)
        {
            int v = edge[G[u][i]].to;
            if(!used[v])
            {
                used[v] = true;
                if(link[v] == -1 || Find(link[v]))
                {
                    link[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
};

const char card[52][3] = {
    "2C", "2D", "2S", "2H",
    "3C", "3D", "3S", "3H",
    "4C", "4D", "4S", "4H",
    "5C", "5D", "5S", "5H",
    "6C", "6D", "6S", "6H",
    "7C", "7D", "7S", "7H",
    "8C", "8D", "8S", "8H",
    "9C", "9D", "9S", "9H",
    "TC", "TD", "TS", "TH",
    "JC", "JD", "JS", "JH",
    "QC", "QD", "QS", "QH",
	"KC", "KD", "KS", "KH",
	"AC", "AD", "AS", "AH"};

Hungarian Solver;
map<string, int> value;
char Adam[30][3];
char Eve[30][3];

void Init()
{
    for(int i = 0; i < 52; ++i)
    {
        value[card[i]] = i + 1;
    }
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    Init();

    int t, k;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &k);
        for(int i = 1; i <= k; ++i)
        {
            scanf("%s", Adam[i]);
        }
        for(int i = 1; i <= k; ++i)
        {
            scanf("%s", Eve[i]);
        }
        Solver.Init(52);
        for(int i = 1; i <= k; ++i)
        {
            for(int j = 1; j <= k; ++j)
            {
                int v1 = value[Eve[i]];
                int v2 = value[Adam[j]];
                if(v1 > v2)
                {
                    Solver.AddEdge(i, j, 1);
                }
            }
        }
        int res = Solver.MaxMatch();
        printf("%d\n", res);
    }
    return 0;
}
