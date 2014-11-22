/*
** LA 6145 Version Controlled IDE
** Created by Rayn @@ 2014/08/05
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

crope l[50055];
char str[1000005];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, d = 0, version = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            ++version;
            int p;
            scanf("%d%s", &p, str);
            p -= d;
            l[version] = l[version-1];
            l[version].insert(p, str);
        }
        else if(type == 2)
        {
            ++version;
            int p, c;
            scanf("%d%d", &p, &c);
            p -= d, c -= d;
            l[version] = l[version-1];
            l[version].erase(p-1, c);
        }
        else
        {
            int v, p, c;
            scanf("%d%d%d", &v, &p, &c);
            v -= d, p -= d, c -= d;
            crope fuck = l[v].substr(p-1, c);
            d += count(fuck.begin(), fuck.end(), 'c');
            printf("%s\n", fuck.c_str());
        }
    }
    return 0;
}
