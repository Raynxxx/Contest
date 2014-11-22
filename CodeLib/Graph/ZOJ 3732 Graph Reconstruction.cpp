/*
** ZOJ 3732 Graph Reconstruction
** Created by Rayn @@ 2014/08/31
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 110;
const int MAXM = MAXN * MAXN;

struct Node
{
    int u;
    int degree;
    Node() {}
    Node(int u, int degree): u(u), degree(degree) {}
    bool operator < (const Node& rhs) const {
        return degree > rhs.degree;
    }
};
struct Edge
{
    int u, v;
    Edge() {}
    Edge(int u, int v): u(u), v(v) {}
};

int n, m1, m2, flag;
Node vert1[MAXN], vert2[MAXN];
Edge edge1[MAXM], edge2[MAXM];

void getAnotherGraph(int st, int pos)
{
    memcpy(vert2, vert1, sizeof(Node)*n);
    memcpy(edge2, edge1, sizeof(Edge)*m1);
    swap(vert2[pos], vert2[pos+1]);
    m2 = m1;
    for(int i = st; i < n; ++i) {
        if(i != st) {
            sort(vert2+i, vert2+n);
        }
        if(vert2[i].degree == 0) {
            break;
        }
        int ed = i + vert2[i].degree;
        if(ed >= n || vert2[ed].degree < 1) {
            flag = -1;
            return ;
        }
        for(int j = i+1; j <= ed; ++j) {
            edge2[m2++] = Edge(vert2[i].u, vert2[j].u);
            vert2[j].degree--;
        }
    }
}
void GaoGaoGao()
{
    for(int i = 0; i < n; ++i) {
        sort(vert1+i, vert1+n);
        if(vert1[i].degree == 0) {
            break;
        }
        int ed = i + vert1[i].degree;
        if(ed >= n || vert1[ed].degree < 1) {
            flag = -1;
            return ;
        }
        if(flag == 0 && ed + 1 < n && vert1[ed].degree == vert1[ed+1].degree) {
            flag = 1;
            getAnotherGraph(i, ed);
            if(flag == -1) {
                return ;
            }
        }
        for(int j = i+1; j <= ed; ++j) {
            edge1[m1++] = Edge(vert1[i].u, vert1[j].u);
            vert1[j].degree--;
        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i < n; ++i) {
            scanf("%d", &vert1[i].degree);
            vert1[i].u = i;
        }
        m1 = m2 = flag = 0;
        GaoGaoGao();
        if(flag == -1) {
            printf("IMPOSSIBLE\n");
            continue;
        }
        if(flag == 0) {
            printf("UNIQUE\n");
            printf("%d %d\n", n, m1);
            for(int i = 0; i < m1; ++i) {
                if(i) putchar(' ');
                printf("%d", edge1[i].u + 1);
            }
            puts("");
            for(int i = 0; i < m1; ++i) {
                if(i) putchar(' ');
                printf("%d", edge1[i].v + 1);
            }
            puts("");
        } else if(flag == 1) {
            printf("MULTIPLE\n");
            printf("%d %d\n", n, m1);
            for(int i = 0; i < m1; ++i) {
                if(i) putchar(' ');
                printf("%d", edge1[i].u + 1);
            }
            puts("");
            for(int i = 0; i < m1; ++i) {
                if(i) putchar(' ');
                printf("%d", edge1[i].v + 1);
            }
            puts("");
            printf("%d %d\n", n, m2);
            for(int i = 0; i < m2; ++i) {
                if(i) putchar(' ');
                printf("%d", edge2[i].u + 1);
            }
            puts("");
            for(int i = 0; i < m2; ++i) {
                if(i) putchar(' ');
                printf("%d", edge2[i].v + 1);
            }
            puts("");
        }
    }
	return 0;
}
