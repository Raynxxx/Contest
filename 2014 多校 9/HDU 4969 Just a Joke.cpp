/*
** HDU 4969 Just a Joke
** Created by Rayn @@ 2014/08/27
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    double v1, v2, R, D;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%lf %lf %lf %lf", &v1, &v2, &R, &D);
        double t = R / v1 * asin(v1 / v2);
        if(t*v2 > D) {
            printf("Why give up treatment\n");
        } else {
            printf("Wake up to code\n");
        }
    }
    return 0;
}
