/*
** ZOJ 3532 Kevin Bacon
** Created by Rayn @@ 2014/06/15
*/
#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 1200;
const int INF = 0x3F3F3F3F;

int EdgeSize, cnt;
int edge[MAX][MAX], dis[MAX], vis[MAX];
char str[300];
string center = "Kevin, Bacon";
map<string, int> mp;
vector<int> idx;

void Init()
{
    cnt = EdgeSize = 0;
    mp.clear();
    for(int i = 0; i < MAX; ++i)
    {
        for(int j = 0; j < MAX; ++j)
        {
            edge[i][j] = INF;
        }
    }
}
void CreatGraph(int rnk)
{
    int s = idx.size();
    for(int i = 0; i < s; ++i)
    {
        for(int j = i+1; j < s; ++j)
        {
            edge[idx[i]][idx[j]] = rnk;
            edge[idx[j]][idx[i]] = rnk;
        }
    }
}
void Dijkskra(int s)
{
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < cnt; ++i)
        dis[i] = (i == s)? 0 : INF;

    for(int i = 0; i < cnt; ++i)
    {
        int x, minval = INF;
        for(int j = 0; j < cnt; ++j)
        {
            if(!vis[j] && dis[j] < minval)
            {
                minval = dis[j];
                x = j;
            }
        }
        vis[x] = 1;
        for(int j = 0; j < cnt; ++j)
        {
            if(dis[x] + edge[x][j] < dis[j])
            {
                dis[j] = dis[x] + edge[x][j];
            }
        }
    }
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif // _Rayn

    int n, p, k, cases = 0;

    while(scanf("%d%d", &p, &n) != EOF && (p && n))
    {
        Init();
        mp[center] = cnt++;
        for(int i = 0; i < p; ++i)
        {
            idx.clear();

            scanf("%d%*c", &k);
            gets(str);
            //printf("%s\n", str);
            int comma = 0;
            string name = "";
            for(int j = 0, len = strlen(str); j < len; ++j)
            {
                if(str[j] == ' ')
                    continue;

                if(str[j] == ',')
                {
                    comma++;
                    if(comma%2 == 0)
                    {
                        if(!mp.count(name))
                        {
                            mp[name] = cnt++;
                        }
                        idx.push_back(mp[name]);
                        //cout << name << endl;
                        name = "";
                    }
                    else
                    {
                        name += ", ";
                    }
                }
                else if(str[j] == ':')
                {
                    if(!mp.count(name))
                    {
                        mp[name] = cnt++;
                    }
                    idx.push_back(mp[name]);
                    //cout << name << endl;
                    CreatGraph(k);
                    break;
                }
                else
                {
                    name += str[j];
                }
            }
        }
        Dijkskra(0);

        string dat;
        printf("Database %d\n", ++cases);
        for(int i = 0; i < n; ++i)
        {
            getline(cin, dat);
            cout << dat << ": ";
            if(!mp.count(dat))
            {
                printf("infinity\n");
                continue;
            }
            int pos = mp[dat];
            //cout << pos << endl;
            if(dis[pos] == INF)
            {
                printf("infinity\n");
            }
            else
            {
                printf("%d\n", dis[pos]);
            }
        }
        printf("\n");
    }
    return 0;
}

