/*
** LA 6041 Retrenchment
** Created by Rayn @@ 2014/10/05
*/
#include <map>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;
typedef pair<LL, int> PLLI;

const int DIV = 2;

struct Point
{
    long long x, y;
    Point() {}
    Point(LL x, LL y):
        x(x), y(y) {}
};
typedef Point Vector;

Vector operator - (const Point& A, const Point& B)
{
    return Vector(A.x-B.x, A.y-B.y);
}
LL Dot(const Vector& A, const Vector& B)
{
    return A.x*B.x + A.y*B.y;
}
LL Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
}
bool IsPointOnSegment(Point p, Point a, Point b)
{
    return Cross(a-p, b-p) == 0 && Dot(a-p, b-p) <= 0;
}
int IsPointInPolygon(Point pt, Point* poly, int n)
{
    int wn = 0;
    for(int i = 0; i < n; ++i)
    {
        int j = (i + 1) % n;
        if(IsPointOnSegment(pt, poly[i], poly[j]))
            return -1;
        LL k = Cross(poly[j]-poly[i], pt-poly[i]);
        LL d1 = poly[i].y - pt.y;
        LL d2 = poly[j].y - pt.y;
        if(k > 0 && d1 <= 0 && d2 > 0)
            wn++;
        if(k < 0 && d2 <= 0 && d1 > 0)
            wn--;
    }
    return (wn != 0);
}

struct Node
{
    long long val[Dimension];
    int id;
};

struct KDNode
{
    Node now;
    int left, right;
};

Point region[25], p[20010];
Node tp[20010];
KDNode tree[20010];

int axis;
priority_queue<PLLI> que;

bool cmp(const Node& A, const Node& B)
{
    return A.val[axis] < B.val[axis];
}
LL Dis2(const Node& A, const Node& B)
{
    LL res = 0;
    for(int i = 0; i < 2; ++i)
    {
        res += (A.val[i] - B.val[i]) * (A.val[i] - B.val[i]);
    }
    return res;
}
void BuildTree(Node* tp, int s, int e, int dep, int& index)
{
    if(s > e)
        return ;
    axis = dep % Dimension;
    sort(tp+s, tp+e+1, cmp);

    int mid = (s + e) / 2;
    ++index;
    int pre = index;
    tree[pre].now = tp[mid];

    if(mid != s)
        tree[pre].left = index + 1;
    else
        tree[pre].left = 0;
    BuildTree(tp, s, mid-1, dep+1, index);

    if(mid != e)
        tree[pre].right = index + 1;
    else
        tree[pre].right = 0;
    BuildTree(tp, mid+1, e, dep+1, index);
}
void UpdateTree(int rt, int index, int dep, Node query)
{
    if(rt == 0)
        return ;
    que.push(make_pair(Dis2(tree[rt].now, query), tree[rt].now.id));
    if(que.size() > 2)
        que.pop();
    axis = dep % Dimension;
    LL t = tree[rt].now.val[axis] - query.val[axis];
    if(t >= 0)  //go to left
    {
        UpdateTree(tree[rt].left, index, dep+1, query);
        if(que.top().first >= t*t || que.size() < 2)    //there is a chance of less
            UpdateTree(tree[rt].right, index, dep+1, query);
    }
    else  //go to left
    {
        UpdateTree(tree[rt].right, index, dep+1, query);
        if(que.top().first >= t*t || que.size() < 2)    //there is a chance of less
            UpdateTree(tree[rt].left, index, dep+1, query);
    }
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn
    int cases = 0;
    int T, N, R, B, M;
    Node query;

    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &N);
        for(int i = 1; i <= N; ++i)
        {
            scanf("%lld%lld", &p[i].x, &p[i].y);
        }
        printf("Case #%d:\n", ++cases);
        scanf("%d", &R);
        for(int ri = 1; ri <= R; ++ri)
        {
            scanf("%d", &B);
            for(int j = 0; j < B; ++j)
            {
                scanf("%lld%lld", &region[j].x, &region[j].y);
            }
            printf("Region %d\n", ri);
            int cnt = 0;
            for(int i = 1; i <= N; ++i)
            {
                if(IsPointInPolygon(p[i], region, B))
                {
                    cnt++;
                    tp[cnt].val[0] = p[i].x;
                    tp[cnt].val[1] = p[i].y;
                    tp[cnt].id = i;
                }
            }
            int index = 0;
            BuildTree(tp, 1, cnt, 0, index);
            scanf("%d", &M);
            while(M--)
            {
                while(!que.empty())
                    que.pop();
                scanf("%lld%lld", &query.val[0], &query.val[1]);
                UpdateTree(1, index, 0, query);
                int id2 = que.top().second;
                que.pop();
                int id1 = que.top().second;
                que.pop();
                printf("%d %d\n", id1, id2);
            }
        }
    }
    return 0;
}
