/*
** HDU 1548 A strange lift
** Created by Rayn @@ 2014/06/30
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
const int MAX = 210;

struct Node
{
    int floor;
    int time;
    Node(int f=0, int t=0): floor(f), time(t) {}
};

int k[MAX];
int vis[MAX];

int BFS(int N, int A, int B)
{
    queue<Node> q;
    memset(vis, 0, sizeof(vis));
    int maybe;

    q.push(Node(A, 0));
    vis[A] = 1;
    while(!q.empty())
    {
        Node now = q.front();
        q.pop();
        if(now.floor == B)
        {
            return now.time;
        }
        Node next;
        // UP
        maybe = now.floor + k[now.floor];
        if(maybe <= N && !vis[maybe])
        {
            vis[maybe] = 1;
            next.floor = maybe;
            next.time = now.time + 1;
            q.push(next);
        }
        //DOWN
        maybe = now.floor - k[now.floor];
        if(maybe >= 1 && !vis[maybe])
        {
            vis[maybe] = 1;
            next.floor = maybe;
            next.time = now.time + 1;
            q.push(next);
        }
    }
    return -1;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    int n, a, b;
    while(scanf("%d%d%d", &n, &a, &b) != EOF && n)
    {
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d", &k[i]);
        }
        printf("%d\n", BFS(n, a, b));
    }
    return 0;
}

