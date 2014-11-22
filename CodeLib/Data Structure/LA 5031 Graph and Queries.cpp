/*
** LA 5031 Graph and Queries
** Created by Rayn @@ 2014/09/02
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 20010;
const int MAXM = 60010;
const int MAXC = 500000 + 10;
const int INF = 0x3F3F3F3F;

template <typename T>
inline void readNumber(T& ret)
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
}

struct Node
{
    Node* ch[2];
    int r, v, s;
    Node(int v): v(v) {
        ch[0] = ch[1] = NULL;
        r = rand(); s = 1;
    }
    bool operator < (const Node& rhs) const {
        return r < rhs.r;
    }
    int cmp(int x) const {
        if(x == v) return -1;
        return (x < v)? 0 : 1;
    }
    void PushUp() {
        s = 1;
        if(ch[0] != NULL) s += ch[0]->s;
        if(ch[1] != NULL) s += ch[1]->s;
    }
};

void Rotate(Node* &o, int d) {
    Node* k = o->ch[d^1];
    o->ch[d^1] = k->ch[d];
    k->ch[d] = o;
    o->PushUp();
    k->PushUp();
    o = k;
}
void Insert(Node* &o, int x) {
    if(o == NULL) {
        o = new Node(x);
    } else {
        int d = (x < o->v) ? 0 : 1;
        Insert(o->ch[d], x);
        if(o->ch[d]->r > o->r) {
            Rotate(o, d^1);
        }
    }
    o->PushUp();
}
void Remove(Node* &o, int x)
{
    int d = o->cmp(x);
    int ret = 0;
    if(d == -1) {
        if(o->ch[0] != NULL && o->ch[1] != NULL) {
            int d2 = (o->ch[0]->r > o->ch[1]->r) ? 1 : 0;
            Rotate(o, d2);
            Remove(o->ch[d2], x);
        } else {
            if(o->ch[0] == NULL) {
                o = o->ch[1];
            } else {
                o = o->ch[0];
            }
        }
    } else {
        Remove(o->ch[d], x);
    }
    if(o != NULL) o->PushUp();
}

int getKth(Node* o, int k)
{
    if(o == NULL || k <= 0 || k > o->s) return 0;
    int s = (o->ch[1] == NULL)? 0 : o->ch[1]->s;
    if(k == s+1) {
        return o->v;
    } else if(k <= s) {
        return getKth(o->ch[1], k);
    } else {
        return getKth(o->ch[0], k-s-1);
    }
}
void MergeTo(Node* &src, Node* &dest)
{
    if(src->ch[0] != NULL) {
        MergeTo(src->ch[0], dest);
    }
    if(src->ch[1] != NULL) {
        MergeTo(src->ch[1], dest);
    }
    Insert(dest, src->v);
    delete src;
    src = NULL;
}
void RemoveTree(Node* &x) {
    if(x->ch[0] != NULL) RemoveTree(x->ch[0]);
    if(x->ch[1] != NULL) RemoveTree(x->ch[1]);
    delete x;
    x = NULL;
}

struct Command
{
    char type;
    int x, p;
    Command() {}
    Command(char type, int x, int p):
        type(type), x(x), p(p) {}
};

int N, M;
int query_cnt;
LL query_tot;
int pa[MAXN];
int weight[MAXN];
int removed[MAXM];
int from[MAXM];
int to[MAXM];
Command cmd[MAXC];
Node* root[MAXN];

int FindSet(int x)
{
    if(x != pa[x]) {
        pa[x] = FindSet(pa[x]);
    }
    return pa[x];
}

void AddEdge(int x)
{
    int u = FindSet(from[x]);
    int v = FindSet(to[x]);
    if(u != v) {
        if(root[u]->s < root[v]->s) {
            pa[u] = v;
            MergeTo(root[u], root[v]);
        } else {
            pa[v] = u;
            MergeTo(root[v], root[u]);
        }
    }
}
void Query(int x, int k)
{
    query_cnt++;
    query_tot += getKth(root[FindSet(x)], k);
}
void ChangeWeight(int x, int v)
{
    int u = FindSet(x);
    Remove(root[u], weight[x]);
    Insert(root[u], v);
    weight[x] = v;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int cases = 0;
    while(scanf("%d%d", &N, &M) != EOF && (N && M))
    {
        memset(removed, 0, sizeof(removed));
        for(int i = 1; i <= N; ++i) {
            scanf("%d", &weight[i]);
        }
        for(int i = 1; i <= M; ++i) {
            scanf("%d%d", &from[i], &to[i]);
        }
        int c = 0;
        while(true)
        {
            char op[2];
            int x, k, v;
            scanf("%s", op);
            if(op[0] == 'E') {
                break;
            }
            if(op[0] == 'D') {
                scanf("%d", &x);
                removed[x] = 1;
            } else if(op[0] == 'Q') {
                scanf("%d%d", &x, &k);
            } else if(op[0] == 'C') {
                scanf("%d%d", &x, &v);
                k = weight[x];
                weight[x] = v;
            }
            cmd[c++] = Command(op[0], x, k);
        }
        for(int i = 1; i <= N; ++i) {
            pa[i] = i;
            if(root[i] != NULL) {
                RemoveTree(root[i]);
            }
            root[i] = new Node(weight[i]);
        }
        for(int i = 1; i <= M; ++i) {
            if(!removed[i]) {
                AddEdge(i);
            }
        }
        query_cnt = query_tot = 0;
        for(int i = c-1; i >= 0; --i) {
            if(cmd[i].type == 'D') {
                AddEdge(cmd[i].x);
            } else if(cmd[i].type == 'Q') {
                Query(cmd[i].x, cmd[i].p);
            } else if(cmd[i].type == 'C') {
                ChangeWeight(cmd[i].x, cmd[i].p);
            }
        }
        printf("Case %d: %.6f\n", ++cases, query_tot / (double)query_cnt);
    }
    return 0;
}
