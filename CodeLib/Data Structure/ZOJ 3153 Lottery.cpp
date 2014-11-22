/*
** ZOJ 3153 Lottery
** Created by Rayn @@ 2014/08/06
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 200010;

int N, M;
int a1, a2, b;
int A, B;
char name[100];

void checkmin(int& t, int x)
{
    if(x == -1)
        return ;
    if(t == -1 || x < t)
        t = x;
}
struct Ticket
{
    string name;
    int a1, a2, b;

    Ticket() {}
    Ticket(string name, int a1, int a2, int b):
        name(name), a1(a1), a2(a2), b(b) {}
} rec[maxn];

struct SegTree
{
    struct Node
    {
        int l, r;
        map<int, set<int> > Bmap;
    };

    int cnt;
    long long money;
    Node tree[maxn<<2];
    map<int, set<int> >::iterator it;
    map<string, long long>::iterator mit;
    set<int>::iterator id;

    void Init(int l, int r)
    {
        cnt = 0;
        money = (LL)M;
        Build(1, l, r);
    }
    void Build(int rt, int l, int r)
    {
        tree[rt].l = l;
        tree[rt].r = r;
        tree[rt].Bmap.clear();
        if(l == r)
        {
            return ;
        }
        int mid = (l + r) >> 1;
        Build(rt<<1, l, mid);
        Build(rt<<1|1, mid+1, r);
    }
    void Insert()
    {
        scanf("%s %d%d%d", name, &a1, &a2, &b);
        rec[cnt] = Ticket(name, a1, a2, b);
        Update(1, a1, a2, cnt, b);
        money += (LL)a2 - a1 + 1;
        ++cnt;
    }
    void Ask()
    {
        scanf("%d%d", &A, &B);
        int minb = Query(1, A, B);
        if(minb == -1)
        {
            printf("0\n");
            return ;
        }
        set<int> ticket_list;
        Find(1, A, B+minb, ticket_list);
        Find(1, A, B-minb, ticket_list);

        LL prize = money / (LL)ticket_list.size();
        money %= (LL)ticket_list.size();

        map<string, long long> res;
        for(id = ticket_list.begin(); id != ticket_list.end(); ++id)
        {
            res[rec[*id].name] += prize;
            Remove(1, rec[*id].a1, rec[*id].a2, rec[*id].b, *id);
        }
        printf("%d\n", res.size());
        for(mit = res.begin(); mit != res.end(); ++mit)
        {
            printf("%s %lld\n", mit->first.c_str(), mit->second);
        }
    }
    void Update(int rt, int l, int r, int rid, int b)
    {
        if(l <= tree[rt].l && tree[rt].r <= r)
        {
            tree[rt].Bmap[b].insert(rid);
            return ;
        }
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(l <= mid)
            Update(rt<<1, l, r, rid, b);
        if(mid < r)
            Update(rt<<1|1, l, r, rid, b);
    }
    void Find(int rt, int a, int b, set<int>& ticket_list)
    {
        it = tree[rt].Bmap.find(b);
        if(it != tree[rt].Bmap.end()) {
            ticket_list.insert(it->second.begin(), it->second.end());
        }
        if(tree[rt].l == tree[rt].r) {
            return ;
        }
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(a <= mid)
            Find(rt<<1, a, b, ticket_list);
        else
            Find(rt<<1|1, a, b, ticket_list);
    }
    int Query(int rt, int A, int B)
    {
        int res = -1;
        it = tree[rt].Bmap.lower_bound(B);
        if(it != tree[rt].Bmap.end()) {
            checkmin(res, it->first - B);
        }
        if(it != tree[rt].Bmap.begin()) {
            it--;
            checkmin(res, B - it->first);
        }
        if(tree[rt].l == tree[rt].r) {
            return res;
        }
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(A <= mid)
            checkmin(res, Query(rt<<1, A, B));
        else
            checkmin(res, Query(rt<<1|1, A, B));
        return res;
    }
    void Remove(int rt, int l, int r, int b, int rid)
    {
        it = tree[rt].Bmap.find(b);
        if(it != tree[rt].Bmap.end()) {
            it->second.erase(rid);
            if(it->second.empty()) {
                tree[rt].Bmap.erase(it);
            }
        }
        if(l <= tree[rt].l && tree[rt].r <= r)
        {
            return ;
        }
        int mid = (tree[rt].l + tree[rt].r) >> 1;
        if(l <= mid)
            Remove(rt<<1, l, r, b, rid);
        if(mid < r)
            Remove(rt<<1|1, l, r, b, rid);
    }
};

SegTree Solver;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    while(scanf("%d%d", &N, &M) != EOF)
    {
        Solver.Init(1, 10000);
        while(N--)
        {
            int op;
            scanf("%d", &op);
            if(op == 1)
            {
                Solver.Insert();
            }
            else if(op == 2)
            {
                Solver.Ask();
            }
        }
    }
    return 0;
}
