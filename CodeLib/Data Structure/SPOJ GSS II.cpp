/*
** SPOJ Can you answer these queries II
** Created by Rayn @@ 2014/08/31
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
typedef long long LL;
const int MAXN = 100000 + 10;
const int MAXV = 2 * MAXN + 10;
const int INF = 0x3F3F3F3F;

template <typename T>
inline void readNumber(T& ret)
{
    char ch = getchar();
    bool flag = false;
    while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if(ch == '-') {
        flag = true;
        ch = getchar();
    }
    ret = 0;
    while(ch >= '0' && ch <= '9') {
        ret = ret * 10 + (ch - '0');
        ch = getchar();
    }
    if(flag) ret = -ret;
}

struct Question
{
    int l, r, id;
    bool operator < (const Question& p) const {
        return r < p.r;
    }
    inline void read() {
        readNumber(l);
        readNumber(r);
    }
};

struct SegmentTree
{
    struct Node
    {
        int left, right;
        int curmax, curtag, evermax, evertag;
        inline void makeNode(const int& val) {
            curmax = curtag = evermax = evertag = val;
        }
        inline int getMid() {
            return (left + right) >> 1;
        }
    };

    Node tree[MAXN<<2];

    inline void PushUp(int rt)
    {
        tree[rt].curmax = max(tree[lson].curmax, tree[rson].curmax);
        tree[rt].evermax = max(tree[lson].evermax, tree[rson].evermax);
    }
    inline void PushDown(int rt)
    {
        tree[lson].evertag = max(tree[lson].evertag, tree[lson].curtag + tree[rt].evertag);
        tree[lson].evermax = max(tree[lson].evermax, tree[lson].curmax + tree[rt].evertag);
        tree[lson].curtag += tree[rt].curtag;
        tree[lson].curmax += tree[rt].curtag;

        tree[rson].evertag = max(tree[rson].evertag, tree[rson].curtag + tree[rt].evertag);
        tree[rson].evermax = max(tree[rson].evermax, tree[rson].curmax + tree[rt].evertag);
        tree[rson].curtag += tree[rt].curtag;
        tree[rson].curmax += tree[rt].curtag;

        tree[rt].curtag = tree[rt].evertag = 0;
    }
    void Build(int rt, int l, int r)
    {
        tree[rt].left = l;
        tree[rt].right = r;
        tree[rt].makeNode(0);
        if(l == r) {
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid);
        Build(rson, mid+1, r);
    }
    void Update(int rt, int x, int y, int val)
    {
        if(x <= tree[rt].left && tree[rt].right <= y)
        {
            tree[rt].curtag += val;
            tree[rt].evertag = max(tree[rt].evertag, tree[rt].curtag);
            tree[rt].curmax += val;
            tree[rt].evermax = max(tree[rt].evermax, tree[rt].curmax);
            return ;
        }
        PushDown(rt);
        int mid = tree[rt].getMid();
        if(x <= mid)
            Update(lson, x, y, val);
        if(mid < y)
            Update(rson, x, y, val);
        PushUp(rt);
    }
    int Query(int rt, int x, int y)
    {
        if(x == tree[rt].left && tree[rt].right == y)
        {
            return tree[rt].evermax;
        }
        PushDown(rt);
        int mid = tree[rt].getMid();
        if(y <= mid) {
            return Query(lson, x, y);
        } else if(mid < x) {
            return Query(rson, x, y);
        } else {
            return max(Query(lson, x, mid), Query(rson, mid+1, y));
        }
    }
};

int N, Q;
int arr[MAXN];
int last[MAXV];
int res[MAXN];
Question ques[MAXN];
SegmentTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    while(scanf("%d", &N) != EOF)
    {
        Solver.Build(1, 1, N);
        for(int i = 1; i <= N; ++i) {
            readNumber(arr[i]);
        }
        readNumber(Q);
        for(int i = 0; i < Q; ++i) {
            ques[i].read();
            ques[i].id = i;
        }
        sort(ques, ques + Q);
        memset(last, 0, sizeof(last));
        for(int i = 1, q = 0; i <= N; ++i) {
            Solver.Update(1, last[arr[i]+MAXN]+1, i, arr[i]);
            last[arr[i]+MAXN] = i;
            while(q < Q && ques[q].r == i) {
                res[ques[q].id] = Solver.Query(1, ques[q].l, ques[q].r);
                q++;
            }
            if(q >= Q) break;
        }
        for(int i = 0; i < Q; ++i) {
            printf("%d\n", res[i]);
        }
    }
	return 0;
}
