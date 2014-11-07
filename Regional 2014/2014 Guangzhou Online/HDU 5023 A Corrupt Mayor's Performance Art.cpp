/*
** HDU 5023 A Corrupt Mayor's Performance Art
** Created by Rayn @@ 2014/11/05
*/
#include <map>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

namespace FastIO {
    /* Input >> int & long long */
    template <typename T>
    inline void readInteger(T& ret) {
        char ch = getchar();
        bool flag = false;
        while ((ch < '0' || ch > '9') && ch != '-') {
            ch = getchar();
        }
        if (ch == '-') {
            flag = true;
            ch = getchar();
        }
        ret = 0;
        while (ch >= '0' && ch <= '9') {
            ret = ret * 10 + (ch - '0');
            ch = getchar();
        }
        if (flag) ret = -ret;
    }
    inline int nextInt() {
        int x;
        readInteger(x);
        return x;
    }
    inline long long nextLong() {
        long long x;
        readInteger(x);
        return x;
    }

    /* Output << int & long long */
    template <typename T>
    inline void outInteger(T x) {
        if (x < 0) {
            putchar('-');
            x = -x;
        }
        if (x >= 10) {
            outInteger(x / 10);
        }
        putchar(x % 10 + '0');
    }
    inline void newline() {
        putchar('\n');
    }
};

using namespace std;
using namespace FastIO;
typedef long long Long;

const int MAXN = 1000010;

#define lson (rt << 1)
#define rson (rt << 1|1)

class SegmentTree {
public:
    int color[MAXN << 2];
    int tag[MAXN << 2];

    inline void PushUp(int rt) {
        color[rt] = color[lson] | color[rson];
    }
    inline void PushDown(int rt) {
        if(tag[rt]) {
            tag[lson] = tag[rson] = tag[rt];
            color[lson] = color[rson] = tag[rt];
            tag[rt] = 0;
        }
    }
    inline void Build(int rt, int l, int r, int v) {
        tag[rt] = 0;
        if(l == r) {
            color[rt] = 1 << (v - 1);
            return ;
        }
        int mid = (l + r) >> 1;
        Build(lson, l, mid, v);
        Build(rson, mid+1, r, v);
        PushUp(rt);
    }
    inline void Update(int rt, int l, int r, int x, int y, int v) {
        if(x <= l && r <= y) {
            color[rt] = 1 << (v - 1);
            tag[rt] = 1 << (v - 1);
            return ;
        }
        PushDown(rt);
        int mid = (l + r) >> 1;
        if(x <= mid)
            Update(lson, l, mid, x, y, v);
        if(mid < y)
            Update(rson, mid+1, r, x, y, v);
        PushUp(rt);
    }
    inline int Query(int rt, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return color[rt];
        }
        PushDown(rt);
        int mid = (l + r) >> 1;
        int ret = 0;
        if(x <= mid)
            ret |= Query(lson, l, mid, x, y);
        if(mid < y)
            ret |= Query(rson, mid+1, r, x, y);
        return ret;
    }
};

SegmentTree st;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF && (n || m)) {
        st.Build(1, 1, n, 2);
        while(m--) {
            char op[10];
            scanf("%s", op);
            if(op[0] == 'P') {
                int a = nextInt();
                int b = nextInt();
                int c = nextInt();
                st.Update(1, 1, n, a, b, c);
            } else if(op[0] == 'Q') {
                int a = nextInt();
                int b = nextInt();
                int color = st.Query(1, 1, n, a, b);
                bool first = true;
                for(int i = 0; i < 30; ++i) {
                    if(color & (1 << i)) {
                        if(!first) putchar(' ');
                        first = false;
                        printf("%d", i + 1);
                    }
                }
                putchar('\n');
            }
        }
    }
    return 0;
}
