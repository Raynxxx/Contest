/*
** ZOJ 3769 Diablo III
** Created by Rayn @@ 2014/08/12
*/
#include <cstdio>
#include <iostream>
#include <vector>
#include <tr1/unordered_map>
#include <cstring>
#include <algorithm>
using namespace std;
using namespace std::tr1;
const int MAXM = 50000 + 10;

struct Equip
{
    int D, T;
    Equip() {}
    Equip(int d, int t): D(d), T(t) {}
};

int dp[13][MAXM];
unordered_map<string, int> equip_id;

void InitMap()
{
    equip_id["Finger"] = 0;
    equip_id["Head"] = 1;
    equip_id["Shoulder"] = 2;
    equip_id["Neck"] = 3;
    equip_id["Torso"] = 4;
    equip_id["Hand"] = 5;
    equip_id["Wrist"] = 6;
    equip_id["Waist"] = 7;
    equip_id["Legs"] = 8;
    equip_id["Feet"] = 9;
    equip_id["Shield"] = 10;
    equip_id["Weapon"] = 11;
    equip_id["Two-Handed"] = 12;
}
inline void takemax(int &a, int b)
{
    if(a < b) a = b;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    InitMap();
    int T, N, M;
    char buf[1000];

    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &N, &M);

        vector<Equip> E[13];
        for(int i=0; i<N; ++i)
        {
            int d, t;
            scanf("%s%d%d", buf, &d, &t);
            E[equip_id[buf]].push_back(Equip(d, t));
        }
        E[0].push_back(Equip(0, 0));
        memset(dp, -1, sizeof(dp));
        dp[0][0] = 0;
        for(int i = 0; i < (int) E[0].size(); ++i)
        {
            for(int j = 0; j < i; ++j)
            {
                takemax(dp[0][min(E[0][i].T + E[0][j].T, M)], E[0][i].D + E[0][j].D);
            }
        }
        int ans = -1;
        for(int i = 1; i <= 12; ++i)
        {
            int p = (i == 12)? 9 : i - 1;
            memcpy(dp[i], dp[p], sizeof(dp[p]));
            for(int k = 0; k < E[i].size(); ++k)
            {
                for(int j = 0; j <= M; ++j)
                {
                    if(dp[p][j] < 0)
                        continue;
                    takemax(dp[i][min(j + E[i][k].T, M)], dp[p][j] + E[i][k].D);
                }
            }
            takemax(ans, dp[i][M]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
