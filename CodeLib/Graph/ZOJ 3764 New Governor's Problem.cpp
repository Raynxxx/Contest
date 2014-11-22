/*
** ZOJ 3764 New Governor's Problem
** Created by Rayn @@ 2014/08/26
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL INF = 1LL << 60;

struct Edge
{
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w):
        u(u), v(v), w(w) {}
    bool operator < (const Edge& e) const
    {
        return w > e.w;
    }
};

int N, M, K;
vector<Edge> edge;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d%d%d", &N, &M, &K) != EOF)
    {
        edge.clear();
        for(int i = 0; i < M; ++i)
        {
            int A, B, C;
            scanf("%d%d%d", &A, &B, &C);
            edge.push_back(Edge(A-1, B-1, C));
        }
        sort(edge.begin(), edge.end());
        LL ret = INF;
        for(int mask = 0; mask < (1 << (N-2)); ++mask)
        {
            int now = mask << 1 | 1;
            LL sum = 0;
            for(int i = 0, s = K; i < M; ++i)
            {
                if(now & (1 << edge[i].v)) swap(edge[i].u, edge[i].v);
                if((now & (1 << edge[i].u)) && !(now & (1 << edge[i].v)))
                {
                    if(s == 0) {
                        sum += edge[i].w;
                    } else {
                        s--;
                    }
                }
            }
            if(sum < ret) ret = sum;
        }
        printf("%lld\n", ret);
    }
    return 0;
}

