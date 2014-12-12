/*
** UVA 105 The Skyline Problem
** Created by Rayn on 2014/12/12
*/
#include <stack>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

inline void gmax(int &x, int y) {
    if (y > x) {
        x = y;
    }
}

struct Building {
    int l, r, h;
    Building() {}
    Building(int l, int r, int h) : l(l), r(r), h(h) {}
};

const int MAXN = 5000 + 10;
const int MAXL = 10000 + 10;

#define lson (rt << 1)
#define rson (rt << 1|1)

struct SegmentTree {
    struct SegNode {
        int l, r, maxv;
        bool tag;
        inline int Mid() {
            return (l + r) >> 1;
        }
    };

    SegNode tree[MAXL << 2];

    void Build(int rt, int l, int r) {
        tree[rt].l = l, tree[rt].r = r;
        tree[rt].maxv = tree[rt].tag = 0;
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid);
        Build(rson, mid + 1, r);
    }
    void PushDown(int rt) {
        if (tree[rt].tag) {
            gmax(tree[lson].maxv, tree[rt].maxv);
            gmax(tree[rson].maxv, tree[rt].maxv);
            tree[lson].tag = true;
            tree[rson].tag = true;
            tree[rt].maxv = 0;
            tree[rt].tag = false;
        }
    }
    void Update(int rt, int x, int y, int val) {
        if (x <= tree[rt].l && tree[rt].r <= y) {
            gmax(tree[rt].maxv, val);
            tree[rt].tag = true;
            return;
        }
        int mid = tree[rt].Mid();
        PushDown(rt);
        if (x <= mid)
            Update(lson, x, y, val);
        if (mid < y)
            Update(rson, x, y, val);
    }
    int Find(int rt, int pos) {
        if (tree[rt].l == tree[rt].r && tree[rt].l == pos) {
            return tree[rt].maxv;
        }
        int mid = tree[rt].Mid();
        PushDown(rt);
        if (pos <= mid)
            return Find(lson, pos);
        else
            return Find(rson, pos);
    }
};

Building build[MAXN];
SegmentTree seg;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int l, r, h;
    int n = 0, bounds = 0;
    while (cin >> l >> h >> r) {
        build[n++] = Building(l, r, h);
        bounds = max(bounds, r);
    }
    seg.Build(1, 1, bounds);
    for (int i = 0; i < n; ++i) {
        seg.Update(1, build[i].l, build[i].r - 1, build[i].h);
    }
    vector<int> ret;
    int pre = -1;
    for (int idx = 1; idx <= bounds; ++idx) {
        int cur = seg.Find(1, idx);
        if (cur != pre) {
            pre = cur;
            ret.push_back(idx);
            ret.push_back(pre);
        }
    }
    int sz = ret.size();
    for (int i = 0; i < sz; ++i) {
        cout << ret[i] << (i == sz - 1 ? '\n' : ' ');
    }
    return 0;
}