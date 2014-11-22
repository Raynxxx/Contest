/*
** POJ 3168 Barn Expansion
** Created by Rayn @@ 2014/04/01
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define MAX 25005
using namespace std;

struct wall{
    int id, pos;
    int beg, end;

    wall(int id=0, int beg=0, int end=0, int pos=0):
        id(id), beg(beg), end(end), pos(pos) {}

    bool operator < (const wall &a) const {
        if(pos == a.pos)
            return beg < a.beg;
        return pos < a.pos;
    };

};

wall vert[MAX*2], hori[MAX*2], tmp[MAX*2];
int sign[MAX];

void Solve(wall *arr, int n)
{
    int i, j, k;
    for(i=0 ; i<n; i=j)
    {
        for(j=i; j<n; ++j)
        {
            if(arr[i].pos != arr[j].pos)
                break;
        }
        int ed = arr[i].end;
        for(k=i+1; k<j; ++k)
        {
            if(arr[k].beg <= ed)
            {
                sign[arr[k].id] = 1;
                sign[arr[k-1].id] = 1;
            }
            ed = max(ed, arr[k].end);
        }
    }
}
int main()
{

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int n, a, b, c, d;

    scanf("%d", &n);
    for(int i=0; i<n; ++i)
    {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        vert[i*2] = wall(i, b, d, a);
        vert[i*2+1] = wall(i, b, d, c);
        hori[i*2] = wall(i, a, c, b);
        hori[i*2+1] = wall(i, a, c, d);
    }
    /*test for input
    printf(" id pos beg end\n");
    for(int i=0; i<n*2; ++i)
        printf("%2d%4d%4d%4d\n",vert[i].id, vert[i].pos, vert[i].beg, vert[i].end);
    printf("----------------\n");
    for(int i=0; i<n*2; ++i)
        printf("%2d%4d%4d%4d\n",hori[i].id, hori[i].pos, hori[i].beg, hori[i].end);
    //*/
    sort(vert, vert + n*2);
    sort(hori, hori + n*2);
    /*test for sort
    printf(" id pos beg end\n");
    for(int i=0; i<n*2; ++i)
        printf("%2d%4d%4d%4d\n",vert[i].id, vert[i].pos, vert[i].beg, vert[i].end);
    printf("----------------\n");
    for(int i=0; i<n*2; ++i)
        printf("%2d%4d%4d%4d\n",hori[i].id, hori[i].pos, hori[i].beg, hori[i].end);
    //*/
    memset(sign, 0, sizeof(sign));
    Solve(vert, n*2);
    Solve(hori, n*2);

    int ans = 0;
    for(int i=0; i<n; ++i)
    {
        if(sign[i] == 0)
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}
