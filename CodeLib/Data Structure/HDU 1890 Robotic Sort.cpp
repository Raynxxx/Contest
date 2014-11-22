/*
** HDU 1890 Robotic Sort
** Created by Rayn @@ 2014/09/04
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
#define lson ch[x][0]
#define rson ch[x][1]
using namespace std;
typedef long long LL;
const int MAXN = 100010;

pair<int, int> sample[MAXN];

class SplayTree
{
private:
    int ch[MAXN][2];
    int pre[MAXN];
    int sz[MAXN];
    int root, top;
    /*视题意确定节点维护值*/
    int flip[MAXN];
    int val[MAXN];

    inline void PushUp(int x)
    {
        sz[x] = sz[lson] + sz[rson] + 1;
    }
    inline void PushDown(int x)
    {
        if(flip[x]) {
            flip[x] = 0;
            flip[lson] ^= 1;
            flip[rson] ^= 1;
            swap(lson, rson);
        }
    }
    /* Rotate(x, f):f=0-将x点左旋; f=1-将x点右旋 */
    void Rotate(int x, int f)
    {
        int y = pre[x];
        PushDown(y);
        PushDown(x);
        ch[y][!f] = ch[x][f];
        pre[ch[x][f]] = y;
        pre[x] = pre[y];
        if(pre[x]) {
            ch[pre[y]][ch[pre[y]][1] == y] = x;
        }
        ch[x][f] = y;
        pre[y] = x;
        PushUp(y);
    }
    //将x节点旋转到goal的下面
    void Splay(int x, int goal)
    {
        PushDown(x);
        while(pre[x] != goal) {
            PushDown(pre[pre[x]]);
            PushDown(pre[x]);
            PushDown(x);
            if(pre[pre[x]] == goal) {
                Rotate(x, ch[pre[x]][0] == x);
            } else {
                int y = pre[x], z = pre[y];
                int f = (ch[z][0] == y);
                if(ch[y][f] == x) {
                    Rotate(x, !f);
                    Rotate(x, f);
                } else {
                    Rotate(y, f);
                    Rotate(x, f);
                }
            }
        }
        PushUp(x);
        if(goal == 0) root = x;
    }
    //将第k位数旋转到goal的下面
    void RTO(int k, int goal)
    {
        int x = root;
        PushDown(x);
        while(sz[lson] + 1 != k) {
            if(k < sz[lson] + 1) {
                x = lson;
            } else {
                k -= sz[lson] + 1;
                x = rson;
            }
            PushDown(x);
        }
        Splay(x, goal);
    }
    void Visit(int x)
    {
        if(x) {
            printf("结点%2d : ", x);
            printf("左  %2d   右  %2d ", lson, rson);
            printf("val:%2d  flip:%d\n", val[x], flip[x]);
            Visit(lson);
            Visit(rson);
        }
    }
    inline void newNode(int &x, int v, int fa, int pos)
    {
        x = pos;
        pre[x] = fa;
        lson = rson = 0;
        val[x] = v;
        flip[x] = 0;
        sz[x] = 1;
    }
    void Build(int &x, int L, int R, int fa)
    {
        if(L > R) return ;
        int M = (L + R) >> 1;
        newNode(x, sample[M].first, fa, M);
        Build(lson, L, M-1, x);
        Build(rson, M+1, R, x);
        PushUp(x);
    }
    void Delete()
    {
        int t = root;
        if(ch[root][1]) {
            root = ch[root][1];
            RTO(1, 0);
            ch[root][0] = ch[t][0];
            if(ch[root][0]) {
                pre[ch[root][0]] = root;
            }
        } else {
            root = ch[root][0];
        }
        pre[root] = 0;
        PushUp(root);
    }
public:
    void Init(int n)
    {
        root = top = 0;
        pre[0] = ch[0][0] = ch[0][1] = 0;
        sz[0] = flip[0] = val[0] = 0;
        Build(root, 1, n, 0);
    }
    int Query(int id)
    {
        Splay(sample[id].second, 0);
        int res = id + sz[ch[root][0]];
        flip[ch[root][0]] ^= 1;
        Delete();
        return res;
    }
};

SplayTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int N;
    while(scanf("%d", &N) != EOF && N)
    {
        for(int i = 1; i <= N; ++i) {
            scanf("%d", &sample[i].first);
            sample[i].second = i;
        }
        Solver.Init(N);
        sort(sample+1, sample+1+N);
        for(int i = 1; i <= N; ++i)
        {
            printf("%d%c", Solver.Query(i), (i == N)? '\n' : ' ');
        }
    }
    return 0;
}
