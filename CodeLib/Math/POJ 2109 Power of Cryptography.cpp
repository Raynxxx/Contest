/*
** POJ 2109 Power of Cryptography
** Created by Rayn @@ 2014/3/23
** 数学
** 现在才知道double，在G++编译器,读用%lf，写必须用%f
*/
#include <cstdio>
#include <cmath>

int main()
{
    double n, p;

    while(scanf("%lf%lf", &n, &p) != EOF)
    {
        printf("%.0f\n", pow(p, 1.0/n));   //少加了一个\n，毁人不倦啊
    }
    return 0;
}
