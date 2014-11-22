/*
** ZOJ 3790 Consecutive Blocks
** Created by Rayn @@ 2014/08/12
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100005;

struct Ball
{
    int c, pos;
    bool operator <(const Ball& rhs) const
    {
        return c < rhs.c || (c == rhs.c && pos < rhs.pos);
    }
} arr[MAXN];

int main() {

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int n, k;
    while(scanf("%d%d", &n, &k) != EOF)
    {
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d", &arr[i].c);
            arr[i].pos = i;
        }
        sort(arr+1, arr+n+1);

        int res = -1;
        int rek = k, ans = 1, cnt = 1, left = 1;
        for(int i = 2; i <= n; ++i)
        {
            if(arr[i-1].c == arr[i].c)
            {
                rek -= arr[i].pos - (arr[i-1].pos + 1);
                cnt++;
                while(rek < 0)
                {
                    rek += arr[left+1].pos - (arr[left].pos + 1);
                    left++;
                    cnt--;
                }
                ans = max(ans, cnt);
            }
            else
            {
                res = max(res, ans);
                rek = k;
                cnt = ans = 1;
                left = i;
            }
        }
        res = max(res, ans);
        printf("%d\n", res);
    }
    return 0;
}
