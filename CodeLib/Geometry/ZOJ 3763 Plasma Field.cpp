/*
** ZOJ 3763 Plasma Field
** Created by Rayn @@ 2014/04/19
*/
#include <cstdio>
#define eps 1e-10

int n;
double x0, y0, c, T;
double x, y, vx, vy;
double A, B, C;

double F(double x)
{
    return A*x*x+B*x+C;
}
double GetMax(double L, double R)
{
    double lv = F(L);
    double rv = F(R);
    while(R-L > eps)
    {
        double m1 = L + (R-L)/3.0;
        double m2 = R - (R-L)/3.0;
        if(F(L) < F(R))
            L = m1;
        else
            R = m2;
    }
    double maxv = F(L);
    if(lv*maxv<eps || rv*maxv<eps || lv*rv <eps)
        return 1;
    else
        return 0;
}
double GetMin(double L, double R)
{
    double lv = F(L);
    double rv = F(R);
    while(R-L > eps)
    {
        double m1 = L + (R-L)/3.0;
        double m2 = R - (R-L)/3.0;
        if(F(L) < F(R))
            R = m2;
        else
            L = m1;
    }
    double minv = F(R);
    if(lv*minv<eps || rv*minv<eps || lv*rv <eps)
        return 1;
    else
        return 0;
}
int JudgeT()
{
    A = vx*vx + vy*vy - c*c;
    B = 2*((x-x0)*vx + (y-y0)*vy);
    C = (x-x0)*(x-x0) + (y-y0)*(y-y0);
    if(A <= 0)
    {
        if(GetMax(0, T))
            return 1;
    }
    else
    {
        if(GetMin(0, T))
            return 1;
    }
    return 0;
}
int Judge2T()
{
    A = vx*vx + vy*vy - c*c;
    B = 2*((x-x0)*vx + (y-y0)*vy) + 4*T*c*c;
    C = (x-x0)*(x-x0) + (y-y0)*(y-y0) - 4*T*T*c*c;
    if(A <= 0)
    {
        if(GetMin(T, 2*T))
            return 1;
    }
    else
    {
        if(GetMax(T, 2*T))
            return 1;
    }
    return 0;
}
int main()
{
    while(scanf("%lf%lf%lf%lf", &x0, &y0, &c, &T) != EOF)
    {
        scanf("%d", &n);
        int ans = 0;
        for(int i=0; i<n; ++i)
        {
            scanf("%lf%lf%lf%lf", &x, &y, &vx, &vy);
            if(JudgeT() || Judge2T())
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
