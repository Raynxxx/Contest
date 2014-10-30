/*
** HDU 4941 Magical Forest
** Created by Rayn @@ 2014/08/18
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;
typedef pair<int, int> PII;

map<PII, int> query;
map<int, int> row, col;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, Q, cases = 0;
    int n, m, k;
    scanf("%d", &T);
    while(T--)
    {
        query.clear();
        row.clear();
        col.clear();
        scanf("%d%d%d", &n, &m, &k);
        for(int i = 0; i < k; ++i)
        {
            int x, y, c;
            scanf("%d%d%d", &x, &y, &c);
            query[make_pair(x, y)] = c;
            row[x] = x;
            col[y] = y;
        }
        printf("Case #%d:\n", ++cases);
        scanf("%d", &Q);
        while(Q--)
        {
            int op, a, b;
            scanf("%d%d%d", &op, &a, &b);
            if(op == 1) {
                swap(row[a], row[b]);
            } else if (op == 2) {
                swap(col[a], col[b]);
            } else if (op == 3) {
                printf("%d\n", query[make_pair(row[a], col[b])]);
            }
        }
    }
    return 0;
}
