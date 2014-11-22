/*
** HDU 4490 Mad Veterinarian
** Created by Rayn @@ 2014/04/26
** Special Judge, 所以sample不对，调了我半天
*/
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node {
    int val[3], step;
    void input() {
        for(int i=0; i<3; ++i)
            scanf("%d", &val[i]);
        step = 0;
    }
    bool operator < (const Node& rhs) const {
        return step > rhs.step;
    }
};

Node beg, ed;
char str[10] = "ABCabc";
bool vis[200][200][200];
int trans[5][5], pre[200000], path[200000];

inline int Hash(Node x)
{
    return x.val[0]*1008 + x.val[1]*108 + x.val[2];
}
void PrintPath(int x)
{
    if(pre[x] == -1)
        return ;
    PrintPath(pre[x]);
    putchar(str[path[x]]);
}
bool Convert(Node x, Node& y, int type)
{
    y = x;
    if(type < 3)
    {
        if(x.val[type] > 0)
        {
            y.val[type]--;
            for(int i=0; i<3; ++i)
            {
                y.val[i] += trans[type][i];
            }
            return !vis[y.val[0]][y.val[1]][y.val[2]];
        }
        return false;
    }
    else
    {
        type = type - 3;
        for(int i=0; i<3; ++i)
        {
            if(y.val[i] < trans[type][i])
                return false;
        }
        for(int i=0; i<3; ++i)
        {
            y.val[i] -= trans[type][i];
        }
        y.val[type]++;
        return !vis[y.val[0]][y.val[1]][y.val[2]];
    }
    return false;
}

bool BFS()
{
    memset(vis, 0, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    vis[beg.val[0]][beg.val[1]][beg.val[2]] = 1;

    priority_queue<Node> q;
    q.push(beg);
    while(!q.empty())
    {
        Node x = q.top(), y;
        q.pop();
        if(x.val[0] == ed.val[0] && x.val[1] == ed.val[1] && x.val[2] == ed.val[2])
        {
            ed.step = x.step;
            return true;
        }
        for(int i=0; i<3; ++i)
        {
            if(x.val[i] > 100)
                return false;
        }
        for(int i=0; i<6; ++i)
        {
            if(Convert(x, y, i))
            {
                y.step = x.step + 1;
                pre[Hash(y)] = Hash(x);
                path[Hash(y)] = i;
                vis[y.val[0]][y.val[1]][y.val[2]] = 1;
                q.push(y);
            }
        }
    }
    return false;
}
int main()
{
    int p, cases, n, id;

    scanf("%d", &p);
    while(p--)
    {
        scanf("%d%d", &cases, &n);
        for(int i=0; i<3; ++i)
        {
            for(int j=0; j<3; ++j)
            {
                scanf("%d", &trans[i][j]);
            }
        }
        printf("%d %d\n", cases, n);
        while(n--)
        {
            scanf("%d ", &id);
            beg.input();
            ed.input();
            if(!BFS())
            {
                printf("%d NO SOLUTION\n", id);
            }
            else
            {
                printf("%d %d ", id, ed.step);
                PrintPath(Hash(ed));
                printf("\n");
            }
        }
    }
    return 0;
}
