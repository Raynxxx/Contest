/*
** HDU 4347 The Closest M Points
** Created by Rayn @@ 2014/09/25
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

const int MAXN = 50010;
const int DIV = 8;
const int INF = 0x3F3F3F3F;

inline double sqr(double x) {
    return x * x;
}
namespace KDTree {
    int K;
    struct Point {
        int x[DIV];

        void read() {
            for(int i = 0; i < K; ++i) {
                scanf("%d", &x[i]);
            }
        }
        void write() {
            for(int i = 0; i < K; ++i) {
                printf("%d%c", x[i], (i == K-1? '\n' : ' '));
            }
        }
        double Dist2(const Point& b) const {
            double ret = 0;
            for(int i = 0; i < K; ++i) {
                ret += sqr(x[i] - b.x[i]);
            }
            return ret;
        }
    };

    struct QNode {
        Point p;
        double dis;
        QNode() {}
        QNode(Point p, double dis): p(p), dis(dis) {}

        bool operator < (const QNode& rhs) const {
            return dis < rhs.dis;
        }
    };

    struct cmpx {
        int div;
        cmpx() {}
        cmpx(const int& div): div(div) {}
        bool operator () (const Point& A, const Point& B) {
            for(int i = 0; i < K; ++i) {
                if(A.x[(div+i)%K] != B.x[(div+i)%K]) {
                    return A.x[(div+i)%K] < B.x[(div+i)%K];
                }
            }
            return true;
        }
    };
    bool cmp(const Point& A, const Point& B, int div) {
        cmpx cp = cmpx(div);
        return cp(A, B);
    }

    struct Node {
        Point e;
        Node *lc, *rc;
        int div;
    };

    Node pool[MAXN], *tail, *root;
    priority_queue<QNode> pq;

    void Init() {
        tail = pool;
    }
    Node* Build(Point *a, int l, int r, int div) {
        if(l >= r) return NULL;
        Node *p = tail++;
        p->div = div;
        int mid = (l + r) >> 1;
        nth_element(a + l, a + mid, a + r, cmpx(div));
        p->e = a[mid];
        p->lc = Build(a, l, mid, (div + 1) % K);
        p->rc = Build(a, mid+1, r, (div + 1) % K);
        return p;
    }
    void Search(Point p, Node *x, int div, int m) {
        if(x == NULL) return ;
        if(cmp(p, x->e, div)) {
            Search(p, x->lc, (div + 1) % K, m);
            if(pq.size() < m) {
                pq.push(QNode(x->e, p.Dist2(x->e)));
                Search(p, x->rc, (div + 1) % K, m);
            } else {
                if(p.Dist2(x->e) < pq.top().dis) {
                    pq.pop();
                    pq.push(QNode(x->e, p.Dist2(x->e)));
                }
                if(sqr(x->e.x[div] - p.x[div]) < pq.top().dis) {
                    Search(p, x->rc, (div + 1) % K, m);
                }
            }
        } else {
            Search(p, x->rc, (div + 1) % K, m);
            if(pq.size() < m) {
                pq.push(QNode(x->e, p.Dist2(x->e)));
                Search(p, x->lc, (div + 1) % K, m);
            } else {
                if(p.Dist2(x->e) < pq.top().dis) {
                    pq.pop();
                    pq.push(QNode(x->e, p.Dist2(x->e)));
                }
                if(sqr(x->e.x[div] - p.x[div]) < pq.top().dis) {
                    Search(p, x->lc, (div + 1) % K, m);
                }
            }
        }
    }
    void Search(Point p, int m) {
        while(!pq.empty()) pq.pop();
        Search(p, root, 0, m);
    }
}

KDTree::Point p[MAXN];
KDTree::Point ini;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, k;
    while(scanf("%d%d", &n, &k) != EOF)
    {
        KDTree::K = k;
        for(int i = 0; i < n; ++i) {
            p[i].read();
        }
        KDTree::Init();
        KDTree::root = KDTree::Build(p, 0, n, 0);
        int Q;
        scanf("%d", &Q);
        while(Q--) {
            ini.read();
            int m;
            scanf("%d", &m);
            KDTree::Search(ini, m);
            printf("the closest %d points are:\n", m);
            int cnt = 0;
            while(!KDTree::pq.empty()) {
                p[cnt++] = KDTree::pq.top().p;
                KDTree::pq.pop();
            }
            for(int i = 0; i < m; ++i) {
                p[cnt-i-1].write();
            }
        }
    }
    return 0;
}
