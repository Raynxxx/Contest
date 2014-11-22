/*
** UVA 11991 Easy Problem from Rujia Liu?
** Created by Rayn @@ 2014/3/30
** 初步熟悉关联容器map的使用
*/
#include <cstdio>
#include <vector>
#include <map>
using namespace std;

map<int, vector<int>> arr;

int main()
{

#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif

    int n, m, x;

    while(scanf("%d%d", &n, &m) != EOF)
    {
        arr.clear();

        for(int i=0; i<n; ++i)
        {
            scanf("%d", &x);
            if(!arr.count(x))
                arr[x] = vector<int>();
            arr[x].push_back(i+1);
        }

        int k, v;
        while(m--)
        {
            scanf("%d%d", &k, &v);
            if(!arr.count(v) || arr[v].size()<k)
                printf("0\n");
            else
                printf("%d\n", arr[v][k-1]);
        }
    }
    return 0;
}
