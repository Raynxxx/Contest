/*
** HDU 5012 Dice
** Created by Rayn @@ 2014/09/18s
*/
#include <map>
#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

const int INF = 0x3F3F3F3F;
const int MAX_State = 700000;
const int FACE = 6;

int x[FACE], tmp[FACE];
bool vis[MAX_State];

int encode(int x[])
{
    int ret = 0;
    for(int i = 0; i < FACE; ++i) {
        ret = ret * 10 + x[i];
    }
    return ret;
}
void decode(int code, int x[])
{
    for(int i = FACE - 1; i >= 0; --i) {
        x[i] = code % 10;
        code /= 10;
    }
}
int Left_Rotation(int code)
{
    decode(code, x);
    tmp[0] = x[3];
    tmp[1] = x[2];
    tmp[2] = x[0];
    tmp[3] = x[1];
    tmp[4] = x[4];
    tmp[5] = x[5];
    return encode(tmp);
}
int Right_Rotation(int code)
{
    decode(code, x);
    tmp[0] = x[2];
    tmp[1] = x[3];
    tmp[2] = x[1];
    tmp[3] = x[0];
    tmp[4] = x[4];
    tmp[5] = x[5];
    return encode(tmp);
}
int Front_Rotation(int code)
{
    decode(code, x);
    tmp[0] = x[5];
    tmp[1] = x[4];
    tmp[2] = x[2];
    tmp[3] = x[3];
    tmp[4] = x[0];
    tmp[5] = x[1];
    return encode(tmp);
}
int Back_Rotation(int code)
{
    decode(code, x);
    tmp[0] = x[4];
    tmp[1] = x[5];
    tmp[2] = x[2];
    tmp[3] = x[3];
    tmp[4] = x[1];
    tmp[5] = x[0];
    return encode(tmp);
}
int bfs(int start, int last)
{
    memset(vis, false, sizeof(vis));
    queue<PII> que;
    que.push(make_pair(start, 0));
    vis[start] = true;
    while(!que.empty())
    {
        PII cur = que.front();
        que.pop();
        int state = cur.first, step = cur.second;
        if(state == last) {
            return step;
        }
        int cur_state;
        cur_state = Left_Rotation(state);
        if(!vis[cur_state]) {
            vis[cur_state] = true;
            que.push(make_pair(cur_state, step + 1));
        }
        cur_state = Right_Rotation(state);
        if(!vis[cur_state]) {
            vis[cur_state] = true;
            que.push(make_pair(cur_state, step + 1));
        }
        cur_state = Front_Rotation(state);
        if(!vis[cur_state]) {
            vis[cur_state] = true;
            que.push(make_pair(cur_state, step + 1));
        }
        cur_state = Back_Rotation(state);
        if(!vis[cur_state]) {
            vis[cur_state] = true;
            que.push(make_pair(cur_state, step + 1));
        }
    }
    return -1;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int a, b;
    while(scanf("%d", &a) != EOF)
    {
        int start = a;
        for(int i = 1; i < FACE; ++i) {
            scanf("%d", &a);
            start = start * 10 + a;
        }
        int last = 0;
        for(int i = 0; i < FACE; ++i) {
            scanf("%d", &b);
            last = last * 10 + b;
        }
        printf("%d\n", bfs(start, last));
    }
    return 0;
}
