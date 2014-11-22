/*
** UVA 11136 Hoax or what
** Created by Rayn @@ 2014/04/04
** 原来还可以用Multiset水过去啊
*/
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

const int MAX = 1000010;
int maxnum, minnum;
multiset<int> urn;

int main()
{
    int n, k;

    while(scanf("%d", &n) != EOF && n)
    {
        urn.clear();
        long long ans = 0;
        while(n--)
        {
            scanf("%d", &k);
            for(int i=0; i<k; ++i)
            {
                int input;
                scanf("%d", &input);
                urn.insert(input);
            }
            ans += (*(--urn.end()) - *urn.begin());
            urn.erase(urn.begin());
            urn.erase(--urn.end());
        }
        printf("%lld\n", ans);
    }
    return 0;
}
