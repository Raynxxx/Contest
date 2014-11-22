/*
** Ural 1880 Psych Up's Eigenvalues
** Created by Rayn @@ 2014/05/25
*/
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

set<int> b[3];

int main()
{
    #ifdef HotWhite
    freopen("in.txt", "r", stdin);
    #endif
    int cnt[3], num, mini = 10000000;
    for (int i = 0; i < 3; ++i) {
        scanf("%d", cnt+i);
        if (mini == 10000000 || cnt[i] < mini) {
            mini = i;
        }
        for (int j = 0; j < cnt[i]; ++j) {
            scanf("%d", &num);
            b[i].insert(num);
        }
    }
    set<int>::iterator ite = b[mini].begin();
    int res = 0;
    for ( ; ite != b[mini].end(); ++ite) {
        if (b[0].count(*ite) && b[1].count(*ite) && b[2].count(*ite)) {
            res++;
        }
    }
    printf("%d\n", res);
    return 0;
}
