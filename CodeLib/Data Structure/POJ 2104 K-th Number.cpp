/*
** POJ 2104 K-th Number
** Created by Rayn @@ 2014/09/30
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN = 100005;
const int MAXM = 5005;

class SegmentTree {
public:
    struct SegNode {
        int val;
        SegNode *Left, *Right;
        SegNode(int v = 0, SegNode* Left = NULL, SegNode* Right = NULL):
            val(v), Left(Left), Right(Right) {}
    };

    SegNode pool[MAXN*20];
    SegNode *root[MAXN];
    int n, tail;
    int st, ed, x;

    SegNode* Build(int l, int r)
    {
        if(l == r) {
            pool[tail] = SegNode();
            return &pool[tail++];
        }
        int mid = (l + r) >> 1;
        SegNode *rt = &pool[tail++];
        rt->val = 0;
        rt->Left = Build(l, mid);
        rt->Right = Build(mid+1, r);
        return rt;
    }
    SegNode* Update(SegNode* pre, int l, int r)
    {
        SegNode *rt = &pool[tail++];
        *rt = *pre;
        if(l == r) {
            rt->val = pre->val + x;
            return rt;
        }
        int mid = (l + r) >> 1;
        if(st <= mid)
            rt->Left = Update(pre->Left, l, mid);
        if(mid < ed)
            rt->Right = Update(pre->Right, mid+1, r);
        rt->val = rt->Left->val + rt->Right->val;
        return rt;
    }
    int Query(SegNode* p1, SegNode* p2, int l, int r, int k)
    {
        if(l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        int cnt = p2->Left->val - p1->Left->val;
        if(k <= cnt)
            return Query(p1->Left, p2->Left, l, mid, k);
        else
            return Query(p1->Right, p2->Right, mid+1, r, k-cnt);
    }
    inline void Init(int n)
    {
        this->n = n;
    }
    inline SegNode* NewArchive(SegNode* latest, int index, int val)
    {
        st = ed = index;
        x = val;
        return Update(latest, 1, n);
    }
    inline int QueryKth(int left, int right, int k)
    {
        st = left, ed = right;
        return Query(root[left-1], root[right], 1, n, k);
    }
};

SegmentTree st;
int a[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m, sz;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        vector<int> v;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            v.push_back(a[i]);
        }
        sort(v.begin(), v.end());
        v.resize(sz = unique(v.begin(), v.end()) - v.begin());
        st.Init(sz);
        st.root[0] = st.Build(1, sz);
        for(int i = 1; i <= n; ++i) {
            int p = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
            st.root[i] = st.NewArchive(st.root[i-1], p, 1);
        }
        while(m--) {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            printf("%d\n", v[st.QueryKth(l, r, k) - 1]);
        }
    }
    return 0;
}
