/*
** POJ 3347 Kadj Squares
** Created by Rayn @@ 2014/06/03
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int MAX = 100;

struct Square {
    int len, l, r;
    Square(int len=0, int l=0, int r=0):
        len(len), l(l), r(r) {}
    bool operator < (const Square& a) const {
        return len < a.len;
    }
} s[MAX];

int main()
{
    int n;
    double x, y;

    while(scanf("%d", &n) != EOF && n)
    {
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d", &s[i].len);
            s[i].l = 0;
            for(int j = 1; j < i; ++j)
            {
                s[i].l = max(s[i].l, s[j].r-abs(s[i].len-s[j].len));
            }
            s[i].r = s[i].l + s[i].len*2;
        }
        for(int i = 2; i <= n; ++i)
        {
            for(int j = 1; j < i; ++j)
            {
                if(s[j].l < s[j].r)
                {
                    if(s[i].l < s[j].r && s[i].len < s[j].len)
                        s[i].l = s[j].r;
                    if(s[i].l < s[j].r && s[i].len > s[j].len)
                        s[j].r = s[i].l;
                }
            }
        }
        for(int i = 1; i <= n; ++i)
        {
            if(s[i].l < s[i].r)
            {
                printf("%d ", i);
            }
        }
        printf("\n");
    }
    return 0;
}
