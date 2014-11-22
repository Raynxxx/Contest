/*
** POJ 1436 Horizontally Visible Segments
** Created by Rayn @@ 2014/09/01
*/
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
typedef long long LL;
const int MAXN = 20000;
const int MAXY = 16000+10;
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

struct Line
{
    int y1, y2, x;
    Line() {}
    Line(int y1, int y2, int x): y1(y1), y2(y2), x(x) {}
    bool operator < (const Line& p) const {
        return x < p.x;
    }
};

int N, M, high;
Line seg[MAXN];
vector<int> gao[MAXN];

struct SegmentTree
{
    struct Node
    {
        int left, right;
        int tag;
        inline int getMid() {
            return (left + right) >> 1;
        }
    };

    Node tree[MAXY<<2];
    int Hash[MAXN];

    void Init(int n)
    {
        Build(1, 1, MAXY);
        memset(Hash, -1, sizeof(Hash));
        for(int i = 0; i < n; ++i) gao[i].clear();
    }
    inline void Build(int rt, int l, int r)
    {
        tree[rt].left = l;
        tree[rt].right = r;
        tree[rt].tag = -1;
        if(l == r) {
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid);
        Build(rson, mid+1, r);
    }
    inline void PushDown(int rt)
    {
        if(tree[rt].tag != -1)
        {
            tree[lson].tag = tree[rson].tag = tree[rt].tag;
            tree[rt].tag = -1;
        }
    }
    void Update(int rt, int x, int y, int id)
    {
        if(x <= tree[rt].left && tree[rt].right <= y)
        {
            tree[rt].tag = id;
            return ;
        }
        PushDown(rt);
        int mid = tree[rt].getMid();
        if(x <= mid)
            Update(lson, x, y, id);
        if(mid < y)
            Update(rson, x, y, id);
    }
    void Query(int rt, int x, int y, int id)
    {
        if(tree[rt].tag != -1) {
            if(Hash[tree[rt].tag] != id) {
                gao[tree[rt].tag].push_back(id);
                Hash[tree[rt].tag] = id;
            }
            return ;
        }
        if(tree[rt].left == tree[rt].right) {
            return ;
        }
        PushDown(rt);
        int mid = tree[rt].getMid();
        if(x <= mid)
            Query(lson, x, y, id);
        if(mid < y)
            Query(rson, x, y, id);
    }
};

SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        readNumber(N);
        Solver.Init(N);
        for(int i = 0; i < N; ++i) {
            readNumber(seg[i].y1);
            readNumber(seg[i].y2);
            readNumber(seg[i].x);
            seg[i].y1++, seg[i].y2++;
            seg[i].y1 <<= 1;
            seg[i].y2 <<= 1;
        }
        sort(seg, seg + N);
        for(int i = 0; i < N; ++i) {
            //printf("%d: %d -- %d\n", i, seg[i].y1, seg[i].y2);
            Solver.Query(1, seg[i].y1, seg[i].y2, i);
            Solver.Update(1, seg[i].y1, seg[i].y2, i);
        }
        for(int i = 0; i < N; ++i) {
            sort(gao[i].begin(), gao[i].end());
        }
        int ret = 0;
        for(int i = 0; i < N; ++i) {
            int sz = (int) gao[i].size();
            for(int j = 0; j < sz; ++j) {
                for(int k = j+1; k < sz; ++k) {
                    int a = gao[i][j];
                    int b = gao[i][k];
                    if(binary_search(gao[a].begin(), gao[a].end(), b)) {
                        ret++;
                    }
                }
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
