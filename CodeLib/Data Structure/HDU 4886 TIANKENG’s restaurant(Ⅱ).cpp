/*
** HDU 4886 TIANKENG's restaurant(Ⅱ)
** Created by Rayn @@ 2014/08/22
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1000010;

int N, mod[10];
char str[MAXN];
bool vis[MAXN];

void Init()
{
    mod[0] = 1;
    for(int i = 1; i <= 8; i++) {
        mod[i] = mod[i-1] * 8;
    }
}
bool Gao(int len)
{
    memset(vis, false, sizeof(vis));
    int fuck = 0;
    for(int i = 0; i < len; ++i) {
        fuck = fuck * 8 + str[i] - 'A';
    }
    vis[fuck] = true;
    for(int i = len; i < N; ++i) {
        fuck = fuck % mod[len-1];
        fuck = fuck * 8 + str[i] - 'A';
        vis[fuck] = true;
    }
    for(fuck = 0; vis[fuck]; ++fuck);
    if(fuck < mod[len])
    {
        string ret = "";
        for(int i = len-1; i >= 0; --i) {
            ret += (char)('A' + fuck / mod[i]);
            fuck %= mod[i];
        }
        printf("%s\n", ret.c_str());
        return true;
    }
    return false;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Init();
    int Test;
    scanf("%d", &Test);
    while(Test--)
    {
        scanf("%s", str);
        N = strlen(str);
        for(int len = 1; ; ++len) {
            if(Gao(len)) break;
        }
    }
    return 0;
}
