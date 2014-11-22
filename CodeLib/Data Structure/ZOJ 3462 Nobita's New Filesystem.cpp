/*
** ZOJ 3462 Nobita's New Filesystem
** Created by Rayn @@ 2014/08/11
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <map>
#include <string>
using namespace std;
typedef long long LL;

char buf[1024], *l, *r;
long long byte[1025];
bitset<1024> mask;
map<string, bitset<1024> > mp;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n, q;
    while(scanf("%d", &n) != EOF)
    {
        mp.clear();
        for(int i = 0; i < n; i++) {
            scanf("%s %lld", buf, &byte[i]);
            l = buf;
            while((l = strchr(l, '[')) != NULL)
            {
                r = strchr(l, ']');
                string tag = string(l+1, r);
                mp[tag].set(i, true);
                l = r;
            }
        }
        scanf("%d", &q);
        while (q--) {
            scanf("%s", buf);

            mask.reset();
            mask.flip();

            l = buf;
            while((l = strchr(l, '[')) != NULL)
            {
                r = strchr(l, ']');
                string tag = string(l+1, r);
                if(!mp.count(tag)) {
                    mask.reset();
                    break;
                } else {
                    mask &= mp[tag];
                }
                l = r;
            }
            long long res = 0;
            for (int i = 0; i < n; i++) {
                if (mask[i]) {
                    res += byte[i];
                }
            }
            printf("%lld\n", res);
        }
    }
    return 0;
}
