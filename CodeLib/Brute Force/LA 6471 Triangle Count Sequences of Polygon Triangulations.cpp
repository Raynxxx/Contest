/*
** LA 6471 Triangle Count Sequences of Polygon Triangulations
** Created by Rayn @@ 2014/08/04
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
typedef long long LL;

struct Tri
{
    int a, b, c;
    Tri() {}
    Tri(int a, int b, int c): a(a), b(b), c(c) {}
    bool operator < (const Tri& p) const
    {
        return a < p.a || (a == p.a && b < p.b) ||
            (a == p.a && b == p.b && c < p.c);
    }
};

Tri tri[25];
int v[25], b[3];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, n, cases;
    int j;

    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d", &cases, &n);
        for(int i = 0; i < n; ++i)
        {
            scanf("%d", &v[i]);
        }
        bool flag = true;
        for(int i = 0; i < n-2; ++i)
        {
            for(j = 0; j < n; ++j)
            {
                if(v[j] == 1)
                {
                    break;
                }
            }
            if(j == n)
            {
                flag = false;
                break;
            }
            int l = j-1, r = j+1;
            if(l < 0)
                l = n-1;
            while(v[l] == 0)
            {
                l--;
                if(l < 0)
                    l = n-1;
            }

            if(r == n)
                r = 0;
            while(v[r] == 0)
            {
                r++;
                if(r == n)
                    r = 0;
            }
            v[j]--;
            v[l]--;
            v[r]--;
            int b[3] = {j, l, r};
            sort(b, b+3);
            tri[i] = Tri(b[0], b[1], b[2]);
            if(j == l || l == r || j == r)
            {
                flag = false;
                break;
            }
        }
        if(!flag)
        {
            printf("%d N\n", cases);
        }
        else
        {
            printf("%d Y\n", cases);
            sort(tri, tri+n-2);
            for(int i = 0; i < n-2; i++)
            {
                printf("%d %d %d\n", tri[i].a+1, tri[i].b+1, tri[i].c+1);
            }
        }
    }
    return 0;
}
