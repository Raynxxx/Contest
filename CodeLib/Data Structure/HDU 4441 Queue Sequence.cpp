/*
** HDU 4441 Queue Sequence
** Created by Rayn @@ 2014/10/16
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
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
const int MAXN = 200050;
const int INF = 100001;

struct Node *null;
struct Node{
	Node *ch[2], *fa;
	int key;
	int sz;
	int neg;
	Long sum;
	Node() {
		fa = ch[0] = ch[1] = NULL;
		sum = key = neg = sz = 0;
	}
	void Init(const int& v) {
		neg = (v < 0);
		sum = key = v;
		sz = 1;
	}
	void PushUp() {
		if (this == null) return;
		sz = ch[0]->sz + ch[1]->sz + 1;
		sum = key + ch[0]->sum + ch[1]->sum;
		neg = (key < 0 ? 1 : 0) + ch[0]->neg + ch[1]->neg;
	}
};

class SplayTree {
private:
	Node pool[MAXN];
	Node *root;
	Node *Stack[MAXN];
	Node *plus_tag[MAXN];
	Node *neg_tag[MAXN];
	int tail, top, Size;

	Node* NewNode(int& val) {
		Node *cur;
		if (top) {
			cur = Stack[top--];
		} else {
			cur = &pool[tail++];
		}
		cur->Init(val);
		cur->fa = cur->ch[0] = cur->ch[1] = null;
		return cur;
	}
	void Rotate(Node *x, int d) {
		Node *y = x->fa;
		y->ch[d ^ 1] = x->ch[d];
		x->fa = y->fa;
		if (x->ch[d] != null)
			x->ch[d]->fa = y;
		if (y->fa != null) {
			y->fa->ch[y->fa->ch[1] == y] = x;
		}
		y->fa = x;
		x->ch[d] = y;
		if (y == root) root = x;
		y->PushUp();
	}
	void Splay(Node *x, Node *f) {
		for (; x->fa != f; ) {
			if (x->fa->fa == f) {
				Rotate(x, x->fa->ch[0] == x);
			} else {
				Node *y = x->fa, *z = y->fa;
				if (z->ch[0] == y) {
					if (y->ch[0] == x) {
						Rotate(y, 1), Rotate(x, 1);
					} else {
						Rotate(x, 0), Rotate(x, 1);
					}
				} else {
					if (y->ch[1] == x) {
						Rotate(y, 0), Rotate(x, 0);
					} else {
						Rotate(x, 1), Rotate(x, 0);
					}
				}
			}
		}
		x->PushUp();
	}
	Node* Kth(Node *x, int k) {
		if (x->ch[0]->sz + 1 == k) return x;
		if (x->ch[0]->sz >= k) {
			return Kth(x->ch[0], k);
		} else {
			return Kth(x->ch[1], k - x->ch[0]->sz - 1);
		}
	}
	Node* NegKth(Node *x, int k) {
		if (x == null) return null;
		if (x->ch[0]->neg + (x->key < 0) > k) {
			return NegKth(x->ch[0], k);
		} else {
			k -= x->ch[0]->neg + (x->key < 0);
			Node* ret = NegKth(x->ch[1], k);
			return (ret == null ? x : ret);
		}
	}
	void Insert(Node *&x, Node* pre, int val) {
		if (x == null) {
			x = NewNode(val);
			x->fa = pre;
			Splay(x, null);
			return;
		}
		if (val <= x->key) {
			Insert(x->ch[0], x, val);
		} else if (val > x->key) {
			Insert(x->ch[1], x, val);
		}
	}
	Node* RightMost(Node *x) {
		for (; x->ch[1] != null; x = x->ch[1]);
		return x;
	}
	Node* LeftMost(Node *x) {
		for (; x->ch[0] != null; x = x->ch[0]);
		return x;
	}
	Node* Merge(Node* x, Node *y) {
		if (x == null) return y;
		if (y == null) return x;
		Splay(x = RightMost(x), null);
		x->ch[1] = y;
		y->fa = x;
		x->PushUp();
		return x;
	}
	void Erase(Node *x) {
		Splay(x, null);
		x->ch[0]->fa = x->ch[1]->fa = null;
		root = Merge(x->ch[0], x->ch[1]);
		Stack[++top] = x;
		return;
	}
	void Build() {
		Insert(root, null, INF);
		Insert(root->ch[1], root, -INF);
		plus_tag[INF] = root;
		neg_tag[INF] = root->ch[1];
	}
public:
	void Init() {
		null = new Node;
		null->fa = null->ch[0] = null->ch[1] = null;
		top = tail = 0;
		root = null;
		Build();
	}
	void Insert(int p, set<int>& qset) {
		p++;
		int num = *qset.begin();
		qset.erase(num);
		Node* x = Kth(root, p);
		Node* y = Kth(root, p + 1);
		Splay(x, null);
		Splay(y, x);
		int plus_cnt = x->ch[0]->sz - x->ch[0]->neg - 1 + (x->key > 0);
		//计算出插入位置前面有多少个正数。减1为虚拟结点
		//printf("%d %d\n", x->ch[0]->sz, x->ch[0]->neg);
		Insert(y->ch[0], y, num);
		plus_tag[num] = root;
		x = NegKth(root, plus_cnt);
		Splay(x, null);
		y = Kth(root, x->ch[0]->sz + 2);
		Splay(y, x);
		Insert(y->ch[0], y, -num);
		neg_tag[num] = root;
	}
	void Remove(int p, set<int>& qset) {
		Erase(plus_tag[p]);
		Erase(neg_tag[p]);
		qset.insert(p);
	}
	Long Query(int p) {
		Splay(plus_tag[p], null);
		Splay(neg_tag[p], root);
		return root->ch[1]->ch[0]->sum;
	}
};

SplayTree st;

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, cases = 0;
	char op[15];
	while (scanf("%d", &n) != EOF) {
		printf("Case #%d:\n", ++cases);
		st.Init();
		set<int> qset;
		for (int i = 1; i <= n; ++i) {
			qset.insert(i);
		}
		for (int i = 0; i < n; ++i) {
			scanf("%s", op);
			if (op[0] == 'i') {
				int p = nextInt();
				st.Insert(p, qset);
			} else if (op[0] == 'r') {
				int p = nextInt();
				st.Remove(p, qset);
			} else {
				int p = nextInt();
				outInteger(st.Query(p));
				newline();
			}
		}
	}
	return 0;
}
