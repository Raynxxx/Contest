/*
** CF 484E Sign on Fence
** Created by Rayn @@ 2014/11/14
*/
#include <set>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;
typedef pair<int, int> pii;

const int MAXN = 100010;
const int INF = 0x3F3F3F3F;

#define lson (tree[rt].lc)
#define rson (tree[rt].rc)

// PersistentSegTree
class SegTree {
private:
    struct SegNode {
        int l, r;
        int lc, rc;
        int pre, suf, sub;
        SegNode() {}
        SegNode(int l, int r) :l(l), r(r) {
            lc = rc = 0;
            pre = suf = sub = 0;
        }
        inline void Add() {
            pre++, suf++, sub++;
        }
        inline int Mid() {
            return (l + r) >> 1;
        }
        inline int Length() {
            return (r - l + 1);
        }
    };

    int sz, root[MAXN];
    SegNode tree[MAXN << 5];

    inline int newNode() {
        return sz++;
    }
    inline void PushUp(int rt) {
        tree[rt].pre = tree[lson].pre + (tree[lson].pre == tree[lson].Length() ? tree[rson].pre : 0);
        tree[rt].suf = tree[rson].suf + (tree[rson].suf == tree[rson].Length() ? tree[lson].suf : 0);
        tree[rt].sub = max(max(tree[rt].sub, tree[lson].suf + tree[rson].pre), max(tree[lson].sub, tree[rson].sub));
    }
    inline SegNode Merge(SegNode L, SegNode R) {
        SegNode ret(L.l, R.r);
        ret.pre = L.pre + (L.pre == L.Length() ? R.pre : 0);
        ret.suf = R.suf + (R.suf == R.Length() ? L.suf : 0);
        ret.sub = max(max(ret.sub, L.suf + R.pre), max(L.sub, R.sub));
        return ret;
    }
    inline void Build(int &rt, int l, int r) {
        if (rt == 0) rt = newNode();
        tree[rt] = SegNode(l, r);
        if (l == r) {
            return;
        }
        int mid = tree[rt].Mid();
        Build(lson, l, mid);
        Build(rson, mid + 1, r);
    }
    inline int Update(int last, int pos) {
        int rt = newNode();
        tree[rt] = tree[last];
        if (tree[rt].l == tree[rt].r && tree[rt].l == pos) {
            tree[rt].Add();
            return rt;
        }
        int mid = tree[rt].Mid();
        if (pos <= mid)
            lson = Update(tree[last].lc, pos);
        else
            rson = Update(tree[last].rc, pos);
        PushUp(rt);
        return rt;
    }
    inline SegNode Query(int rt, int l, int r) {
        if (l <= tree[rt].l && tree[rt].r <= r) {
            return tree[rt];
        }
        int mid = tree[rt].Mid();
        if (r <= mid) {
            return Query(lson, l, r);
        } else if (mid < l) {
            return Query(rson, l, r);
        } else {
            return Merge(Query(lson, l, mid), Query(rson, mid + 1, r));
        }
    }
public:
    inline void Init(int n) {
        sz = 1;
        Build(root[0], 1, n);
    }
    inline void NewSegTree(int cur, int last, int pos) {
        root[cur] = Update(root[last], pos);
    }
    inline int Gao(int idx, int l, int r) {
        return Query(root[idx], l, r).sub;
    }
};

SegTree seg;
pii fence[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &fence[i].first);
            fence[i].second = i;
        }
        sort(fence + 1, fence + 1 + n, greater<pii>());
        seg.Init(n);
        for (int i = 1; i <= n; ++i) {
            seg.NewSegTree(i, i - 1, fence[i].second);
        }
        scanf("%d", &m);
        while (m--) {
            int l, r, w;
            scanf("%d%d%d", &l, &r, &w);
            int L = 1, R = n;
            while (L < R) {
                int mid = (L + R) >> 1;
                if (seg.Gao(mid, l, r) >= w) {
                    R = mid;
                } else {
                    L = mid + 1;
                }
            }
            printf("%d\n", fence[R].first);
        }

    }
    return 0;
}