/*
** ZOJ 3641 Information Sharing
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#include <string>
using namespace std;
const int maxn = 100010;

map<string, int> mp;
set<int> st[maxn];
int id, pa[maxn];

void Init()
{
    id = 0;
    mp.clear();
    for(int i = 0; i < maxn; ++i)
    {
        pa[i] = i;
        st[i].clear();
    }
}
int FindSet(int x)
{
    if(x != pa[x])
        return pa[x] = FindSet(pa[x]);
    return pa[x];
}
void Union(int x, int y)
{
    int px = FindSet(x);
    int py = FindSet(y);
    if(px == py)
        return ;
    pa[px] = py;
    set<int>::iterator it;
    for(it = st[px].begin(); it != st[px].end(); ++it)
    {
        st[py].insert(*it);
    }
    st[px].clear();
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    char op[20], name[20], name1[20], name2[20];

    while(scanf("%d", &n) != EOF)
    {
        Init();
        for(int i = 0; i < n; ++i)
        {
            scanf("%s", op);
            if(op[0] == 'a')
            {
                scanf("%s", name);
                if(!mp.count(name))
                    mp[name] = ++id;
                int fa = FindSet(mp[name]);
                scanf("%d", &m);
                for(int i = 0, ai; i < m; ++i)
                {
                    scanf("%d", &ai);
                    st[fa].insert(ai);
                }
            }
            else if(op[0] == 's')
            {
                scanf("%s%s", name1, name2);
                Union(mp[name1], mp[name2]);
            }
            else if(op[0] == 'c')
            {
                scanf("%s", name);
                int fa = FindSet(mp[name]);
                printf("%d\n", st[fa].size());
            }
        }
    }
    return 0;
}
