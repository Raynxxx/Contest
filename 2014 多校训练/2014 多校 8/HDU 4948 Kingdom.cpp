/*
** HDU 4948 Kingdom
** Created by Rayn @@ 2014/08/25
*/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#define MOD 998244353
using namespace std;
typedef pair<int, int> PII;
typedef long long LL;
const int MAXN = 512;

struct Node
{
    int id;
    int degree;
    bool operator < (const Node& p) const
    {
        return degree > p.degree;
    }
};

Node dot[512];
char maps[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d%*c", &n) != EOF && n)
    {
        for(int i = 0; i < n; ++i) {
            dot[i].id = i + 1;
            dot[i].degree = 0;
        }
        for(int i = 0; i < n; ++i) {
            gets(maps);
            for(int j = 0; j < n; ++j) {
                if(maps[j] == '1')
                    dot[j].degree++;
            }
        }
        sort(dot, dot+n);
        for(int i = n-1; i >= 0; --i)
        {
            printf("%d%c", dot[i].id, (i == 0 ? '\n' : ' '));
        }
    }
    return 0;
}
