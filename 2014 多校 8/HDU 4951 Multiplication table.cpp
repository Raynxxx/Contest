/*
** HDU 4950 Monster
** Created by Rayn @@ 2014/08/25
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <cctype>
using namespace std;
typedef pair<int, int> PII;
const int maxn = 512;

inline int nextInt()
{
    char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();

    int x = 0;
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    return x;
}

int p;
PII num[maxn][maxn];
int mapped[maxn];
bool times[maxn];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int cases = 0;
    while(scanf("%d", &p) != EOF && p)
    {
        for(int i = 0; i < p; ++i)
        {
            for(int j = 0; j < p; ++j)
            {
                num[i][j].first = nextInt();
                num[i][j].second = nextInt();
            }
        }
        for(int i = 0; i < p; ++i)
        {
            memset(times, false, sizeof(times));
            int cnt = 0;
            for(int j = 0; j < p; ++j)
            {
                if(!times[num[i][j].first])
                {
                    times[num[i][j].first] = true;
                    cnt++;
                }
            }
            if(cnt == 1 && num[i][0].second == num[i][1].second) {
                cnt = 0;
            }
            mapped[cnt] = i;
        }
        printf("Case #%d: ", ++cases);
        for(int i = 0; i < p; ++i)
        {
            printf("%d%c", mapped[i], (i == p-1 ? '\n' : ' '));
        }
    }
    return 0;
}
