/*
** ZOJ 3637 Education Manage System
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
using namespace std;
const int maxn = 100010;
const int maxm = 530000;
typedef pair<int, int> PII;

const char month[][12] =
{
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
const int day[] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};
double credit[maxn], dp[maxm];
pair<int, int> arr[maxn];
vector<int> vec[maxm];
vector<int>::iterator it;

void Init()
{
    for(int i = 0; i < maxm; ++i)
        vec[i].clear();
}
int GetTime()
{
    char s1[10], s2[10];
    int m, d, hh, mm;
    scanf("%s", s1);
    for(int i = 0; i < 12; ++i)
    {
        if(strcmp(s1, month[i]) == 0)
        {
            m = i;
            break;
        }
    }
    scanf("%d%s %d:%d %s", &d, s1, &hh, &mm, s2);
    if(s2[0] == 'p') {
        hh += 12;
    }
    return (day[m] + d) * 24 * 60 + hh * 60 + mm + 1;
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    int n;
    int st, ed;

    while(scanf("%d", &n) != EOF)
    {
        Init();
        for(int i = 1; i <= n; ++i)
        {
            st = GetTime();
            ed = GetTime() + 5;
            scanf("%lf", &credit[i]);
            arr[i] = make_pair(st, ed);
            vec[ed].push_back(i);
        }
        memset(dp, 0, sizeof(dp));
        for(int i = 1; i < maxm; ++i)
        {
            dp[i] = dp[i-1];
            for(it = vec[i].begin(); it != vec[i].end(); ++it)
            {
                dp[i] = max(dp[i], dp[arr[*it].first] + credit[*it]);
            }
        }
        printf("%.1f\n", dp[maxm-1]);
    }
    return 0;
}
