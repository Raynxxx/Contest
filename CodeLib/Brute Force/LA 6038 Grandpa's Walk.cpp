/*
** LA 6038 Grandpa's Walk
** Created by Rayn @@ 2014/07/21
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 55;

int n, m, res;
int arr[MAXN][MAXN];
int dir[][2] = {{0, -1}, {1, 0},
                {-1, 0}, {0, 1}};


bool OK(int x, int y)
{
    if(x >= n || y >= m || x < 0 || y < 0)
        return false;
	return true;
}
void DFS(int x, int y)
{
    int flag = 1;
    for(int i = 0; i < 4; ++i)
    {
        int px = x + dir[i][0];
        int py = y + dir[i][1];
        if(OK(px, py) && arr[x][y] > arr[px][py])
        {
            DFS(px, py);
            flag = 0;
        }
    }
    if(flag)
        res++;
}
int main()
{
#ifdef HotWhite
    freopen("in.txt", "r", stdin);
#endif
    int t, cases = 0;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                scanf("%d", &arr[i][j]);
            }
        }
        res = 0;
		for(int i = 0; i < n; ++i)
        {
			for(int j = 0; j < m; ++j)
			{
				int flag = 1;
				for(int s = 0; s < 4; ++s)
				{
				    int px = i + dir[s][0];
                    int py = j + dir[s][1];
					if(OK(px, py) && arr[i][j] < arr[px][py])
						flag = 0;
				}
				if(flag)
                    DFS(i, j);
			}
		}
		printf("Case #%d: %d\n", ++cases, res);
    }
    return 0;
}
