/*
** CF 483D Interesting Array
** Created by Rayn @@ 2014/11/14
*/
#include <map>
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
const int BITS = 30;

#define lson (rt << 1)
#define rson (rt << 1|1)

struct SegmentTree {
    struct SegNode {
        int l, r;
        int sum;
        inline int Mid() {
            return (l + r) >> 1;
        }
    };

    SegNode tree[MAXN << 2];

    void PushUp(int rt) {
        tree[rt].sum = tree[lson].sum & tree[rson].sum;
    }
    void Build(int rt, int l, int r, int val[]) {
        tree[rt].l = l, tree[rt].r = r;
        if (l == r) {
            tree[rt].sum = val[l];
            return;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid, val);
        Build(rson, mid + 1, r, val);
        PushUp(rt);
    }
    int Query(int rt, int l, int r) {
        if (l <= tree[rt].l && tree[rt].r <= r) {
            return tree[rt].sum;
        }
        int mid = tree[rt].Mid();
        if (r <= mid) {
            return Query(lson, l, r);
        } else if (mid < l) {
            return Query(rson, l, r);
        } else {
            return Query(lson, l, mid) & Query(rson, mid + 1, r);
        }
    }
};

struct LimitNode {
    int l, r, q;
    void read() {
        cin >> l >> r >> q;
    }
};

SegmentTree seg;
LimitNode limit[MAXN];
int arr[MAXN];
int tag[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= m; ++i) {
            limit[i].read();
        }
        fill_n(arr, n + 1, 0);
        for (int i = 0; i <= BITS; ++i) {
            fill_n(tag, n + 1, 0);
            for (int j = 1; j <= m; ++j) {
                if ((1 << i) & limit[j].q) {
                    tag[limit[j].l]++;
                    tag[limit[j].r + 1]--;
                }
            }
            int sum = 0;
            for (int j = 1; j <= n; ++j) {
                sum += tag[j];
                if (sum) {
                    arr[j] |= (1 << i);
                }
            }
        }
        seg.Build(1, 1, n, arr);
        bool ok = true;
        for (int i = 1; i <= m; ++i) {
            if (seg.Query(1, limit[i].l, limit[i].r) != limit[i].q) {
                ok = false;
                break;
            }
        }
        if (ok) {
            puts("YES");
            for (int i = 1; i <= n; ++i) {
                printf("%d%c", arr[i], (i == n) ? '\n' : ' ');
            }
        } else {
            puts("NO");
        }
    }
    return 0;
}       