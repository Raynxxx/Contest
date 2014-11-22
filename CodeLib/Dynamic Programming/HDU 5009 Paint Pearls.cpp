/*
** HDU 5009 Paint Pearls
** Created by Rayn @@ 2014/09/18
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const int INF = 0x3F3F3F3F;
const int MAXN = 50010;

struct Node
{
    int val, id, rnk;
};

bool cmpv(const Node& a, const Node& b) {
    return a.val < b.val;
}
bool cmpid(const Node& a, const Node& b) {
    return a.id < b.id;
}


bool vis[MAXN];
int dp[MAXN];
vector<int> save;
Node pearl[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &pearl[i].val);
            pearl[i].id = i;
        }
        sort(pearl + 1, pearl + 1 + n, cmpv);
        pearl[1].rnk = 0;
        for(int i = 2, s = 0; i <= n; ++i) {
            if(pearl[i].val != pearl[i-1].val)
                ++s;
            pearl[i].rnk = s;
        }
        sort(pearl + 1, pearl + 1 + n, cmpid);
        memset(vis, false, sizeof(vis));
        memset(dp, INF, sizeof(dp));
        dp[0] = 0;
        dp[n] = n;
        for(int i = 0; i < n; ++i) {
            if(dp[i] > dp[i+1]) continue;
            int cnt = 0;
            for(int j = i + 1; j <= n; ++j) {
                if(!vis[pearl[j].rnk]) {
                    vis[pearl[j].rnk] = true;
                    save.push_back(pearl[j].rnk);
                    cnt++;
                }
                if(dp[i] + cnt*cnt >= dp[n]) break;
                dp[j] = min(dp[j], dp[i] + cnt*cnt);
            }
            for(vector<int>::iterator it = save.begin(); it != save.end(); ++it) {
                vis[*it] = false;
            }
            save.clear();
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}
