/*
** HDU 4909 String
** Created by Rayn @@ 2014/08/29
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <map>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 20010;

char str[MAXN];

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s", str);
        int N = strlen(str);
        int ret = 0;

        map<int, int> left;
        map<int, int> right;
        bool has_mark = false;
        int mask = 0; left[mask]++;
        for(int i = 0; i < N; ++i) {
            if(str[i] != '?') {
                mask ^= (1 << (str[i] - 'a'));
            } else {
                has_mark = true;
            }
            if(!has_mark) {
                if(left.count(mask)) ret += left[mask];
                left[mask]++;
            } else {
                if(left.count(mask)) ret += left[mask];
                if(right.count(mask)) ret += right[mask];
                for(int j = 0; j < 26; ++j) {
                    if(left.count(mask ^ (1 << j))) {
                        ret += left[mask ^ (1 << j)];
                    }
                }
                right[mask]++;
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
