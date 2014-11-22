/*
** LA 6466 Von Neumann¡¯s Fly
** Created by Rayn @@ 2014/08/05
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif

    int T;
    scanf("%d", &T);
    while (T--)
    {
        int cases;
        double D, A, B, F;
        scanf("%d%lf%lf%lf%lf", &cases, &D, &A, &B, &F);
        printf("%d %.2f\n", cases, D/(A+B)*F);
    }
    return 0;
}
