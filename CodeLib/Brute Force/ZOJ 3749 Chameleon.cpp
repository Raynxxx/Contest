/*
** ZOJ 3749 Chameleon
** Created by Rayn @@ 2014/08/21
*/
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 100010;
const int INF = 0x3F3F3F3F;

int N, Q;
vector<int> arr[MAXN];
vector<int>::const_iterator it;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    while(scanf("%d", &N) != EOF)
    {
        for(int i = 1; i <= N; ++i)
        {
            int m, x;
            arr[i].clear();
            scanf("%d", &m);
            while(m--)
            {
                scanf("%d", &x);
                arr[i].push_back(x);
            }
            sort(arr[i].begin(), arr[i].end());
        }
        scanf("%d", &Q);
        while(Q--)
        {
            int x, y, ret = 0;
            scanf("%d%d", &x, &y);
            if(arr[x].size() > arr[y].size()) {
                swap(x, y);
            }
            int pre = 0;
            for(it = arr[x].begin(); it != arr[x].end(); ++it)
            {
                int cur = lower_bound(arr[y].begin() + pre, arr[y].end(), *it) - arr[y].begin();
                //printf("pre: %d cur: %d %d %d\n", pre, cur, *it, arr[y][cur]);
                if(cur != pre) {
                    if(it == arr[x].begin()) {
                        ret += 1;
                    } else {
                        ret += 2;
                    }
                }
                pre = cur;
            }
            if(lower_bound(arr[y].begin() + pre, arr[y].end(), *(--it)) != arr[y].end()) {
                ret++;
            }
            printf("%d\n", ret);
        }
    }
    return 0;
}

