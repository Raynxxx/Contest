/*
** ZOJ 3645 BiliBili
** Created by Rayn @@ 2014/07/29
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
const int MAXN = 1010;
typedef vector<double> Dvec;
typedef vector<vector<double> > Dvec2;

double arr[20][20];
double ma[20][20];
double r[20], line[20];

vector<double> Gauss_Jordan(const Dvec2& A, const Dvec& t, int n)
{
    Dvec2 B(15, Dvec(15));

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            B[i][j] = A[i][j];
        }
        B[i][n] = t[i];
    }
    for(int i = 0; i < n; i++)
    {
        int rp = i;
        for(int j = i+1; j < n; j++)
        {
            if(fabs(B[j][i]) > fabs(B[rp][i]))
                rp = j;
        }
        if(rp != i)
        {
            swap(B[i], B[rp]);
        }

        for(int k = i+1; k < n; ++k)
        {
            double f = B[k][i] / B[i][i];
            for(int j = i; j <= n; ++j)
            {
                B[k][j] -= f * B[i][j];
            }
        }
    }
    for(int i = n-1; i >= 0; --i)
    {
        for(int j = i+1; j < n; j++)
        {
            B[i][n] -= B[j][n] * B[i][j];
        }
        B[i][n] /= B[i][i];
    }
    Dvec res(15);
    for(int i = 0; i < n; ++i)
    {
        res[i] = B[i][n];
    }
    return res;
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn
    int T;
    scanf("%d", &T);
    while (T--)
    {
        for(int i = 0; i < 12 ; i++)
        {
            for(int j = 0; j < 12; ++j)
            {
                scanf("%lf", &arr[i][j]);
            }
        }
        for(int i = 0 ; i < 12; i++)
        {
            r[i] = 0;
            for(int j = 0; j < 11; j++)
            {
                r[i] += arr[i][j] * arr[i][j];
            }
            r[i] -= arr[i][11] * arr[i][11];
            r[i] /= 2;
        }
        for(int i = 0; i < 11; i++)
        {
            line[i] = r[i] - r[i+1];
            for ( int j = 0; j < 11; j++)
            {
                ma[i][j] = arr[i][j] - arr[i+1][j];
            }
        }
        Dvec2 martix(15, Dvec(15));
        Dvec other(15), ans;
        for(int i = 0; i < 11; i++)
        {
            other[i] = line[i];
            for(int j = 0; j < 11; j++)
            {
                martix[i][j] = ma[i][j];
            }
        }
        ans = Gauss_Jordan(martix, other, 11);
        for(int i = 0; i < 11; i++)
        {
            printf("%.2f%c", ans[i], (i == 10)?'\n':' ');
        }
    }
    return 0;
}
