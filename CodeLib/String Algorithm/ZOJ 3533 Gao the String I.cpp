/*
** ZOJ 3533 Gao the String I
** Created by Rayn @@ 2014/11/11
*/
#include <set>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;
typedef unsigned long long uLong;

const uLong RP = 233;
const int MAXN = 100100;

uLong magic[MAXN];

void InitMagic() {
    magic[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        magic[i] = magic[i - 1] * RP;
    }
}

struct Node *null;
struct Node {
    Node *ch[2];
    int sz;
    bool flip;
    int val;
    uLong h1, h2;
    inline int cmp(int k) const {
        int d = k - ch[0]->sz;
        if (d == 1) return -1;
        return (d <= 0) ? 0 : 1;
    }
    inline void Change(int v) {
        h1 = h2 = val = v;
    }
    inline void Reverse() {
        if (this == null) return;
        flip ^= 1;
        swap(h1, h2);
        swap(ch[0], ch[1]);
    }
    inline void PushDown() {
        if (this == null) return;
        if (flip) {
            ch[0]->Reverse();
            ch[1]->Reverse();
            flip = false;
        }
    }
    inline void PushUp() {
        if (this == null) return;
        sz = ch[0]->sz + ch[1]->sz + 1;
        h1 = (ch[0]->h1 * RP + val) * magic[ch[1]->sz] + ch[1]->h1;
        h2 = (ch[1]->h2 * RP + val) * magic[ch[0]->sz] + ch[0]->h2;
    }
};


struct SplayTree {
    Node pool[MAXN << 1];
    Node *root, *cur;
    int top, box[MAXN];
    int p[MAXN << 1], s[MAXN << 1];

    Node *new_Node(int val = 0) {
        cur->ch[0] = cur->ch[1] = null;
        cur->sz = 1;
        cur->val = val;
        cur->h1 = cur->h2 = val;
        cur->flip = false;
        return cur++;
    }
    void Rotate(Node *&o, int d) {
        Node* k = o->ch[d ^ 1];
        o->ch[d ^ 1] = k->ch[d];
        k->ch[d] = o;
        o->PushUp();
        k->PushUp();
        o = k;
    }
    void Splay(Node* &o, int k) {
        o->PushDown();
        int d = o->cmp(k);
        if (d == 1) {
            k -= o->ch[0]->sz + 1;
        }
        if (d != -1) {
            Node* p = o->ch[d];
            p->PushDown();
            int d2 = p->cmp(k);
            int k2 = (d2 == 0) ? k : k - p->ch[0]->sz - 1;
            if (d2 != -1) {
                Splay(p->ch[d2], k2);
                if (d == d2) Rotate(o, d ^ 1);
                else Rotate(o->ch[d], d);
            }
            Rotate(o, d ^ 1);
        }
    }
    void Update_dummy() {
        root->ch[1]->PushUp();
        root->PushUp();
    }
    Node* last() const {
        return root->ch[1]->ch[0];
    }
    Node*& getRange(int L, int R) {
        Splay(root, L);
        Splay(root->ch[1], R - L + 1);
        return root->ch[1]->ch[0];
    }
    Node* Build(int l, int r, char *str) {
        if (l > r) return null;
        int mid = (l + r) >> 1;
        Node *x = new_Node(str[mid]);
        x->ch[0] = Build(l, mid - 1, str);
        x->ch[1] = Build(mid + 1, r, str);
        x->PushUp();
        return x;
    }
    void Build(char *str, int n) {
        cur = pool;
        null = new_Node(0);
        null->sz = 0;
        null->ch[0] = null->ch[1] = null;
        root = new_Node(0);
        root->ch[1] = new_Node(0);
        root->ch[1]->ch[0] = Build(0, n - 1, str);
        Update_dummy();
    }
    void Reverse(int l, int r) {
        getRange(l, r + 1)->Reverse();
        Update_dummy();
    }
    void Modify(int pos, char c) {
        getRange(pos, pos + 1)->Change(c);
        Update_dummy();
    }
    int LCP(int x, int y) {
        int l = 0, r = root->sz - y;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            uLong h1 = getRange(x, x + mid)->h1;
            uLong h2 = last()->h2;
            h1 -= getRange(y, y + mid)->h1;
            h2 -= last()->h2;
            if (!h1 && !h2) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return l;
    }
    void Travel(Node *x) {
        if (x == null) return;
        x->PushDown();
        Travel(x->ch[0]);
        box[top++] = x->val;
        Travel(x->ch[1]);
    }
    int Manacher(int *str, int len) {
        int ret = 1, mx = 0;
        for (int i = 1, j = 0; i < len; ++i) {
            if (mx > i) {
                p[i] = min(p[2 * j - i], mx - i);
            } else {
                p[i] = 1;
            }
            for (; str[i + p[i]] == str[i - p[i]]; p[i]++);
            if (i + p[i] > mx) {
                mx = i + p[i];
                j = i;
            }
            ret = max(ret, p[i] - 1);
        }
        return ret;
    }
    int Palindrome(int n) {
        top = 0;
        Travel(root);
        int tot = 0;
        s[tot++] = '$';
        s[tot++] = '#';
        for (int i = 1; i <= n; ++i) {
            s[tot++] = box[i];
            s[tot++] = '#';
        }
        s[tot] = '\0';
        return Manacher(s, tot);
    }
    void Debug() {
        top = 0;
        Travel(root);
        printf("Debug: ");
        for (int i = 0; i < top; ++i) {
            printf("%c", box[i]);
        }
        printf("\n");
    }
};

SplayTree st;
char buf[MAXN];

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    InitMagic();
    int n, m;
    while (scanf("%s", buf) != EOF) {
        n = strlen(buf);
        scanf("%d", &m);
        st.Build(buf, n);
        while (m--) {
            char op[20];
            scanf("%s", op);
            if (op[0] == 'R') {
                int a, b;
                scanf("%d%d", &a, &b);
                if (a > b) swap(a, b);
                st.Reverse(a, b);
            } else if (op[0] == 'M') {
                int p; char ch[5];
                scanf("%d%s", &p, ch);
                st.Modify(p, ch[0]);
            } else if (op[0] == 'L') {
                int a, b;
                scanf("%d%d", &a, &b);
                if (a > b) swap(a, b);
                printf("%d\n", st.LCP(a, b));
            } else if (op[0] == 'P') {
                printf("%d\n", st.Palindrome(n));
            }
        }
    }
    return 0;
}
