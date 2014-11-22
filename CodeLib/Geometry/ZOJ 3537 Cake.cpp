/*
** ZOJ 3537 Cake
** Created by Rayn @@ 2014/06/20
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 310;
const int INF = 0x3F3F3F3F;
const double EPS = 1e-8;

int n, p;
int dp[MAX][MAX];
int cost[MAX][MAX];

struct Point
{
    int x, y;
    Point(int x=0, int y=0): x(x),y(y) {}
    bool operator < (const Point& rhs) const
    {
        return y < rhs.y || (y == rhs.y && x < rhs.x);
    }
    bool operator == (const Point& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
};
typedef Point Vector;

Vector operator + (const Point& A, const Point& B)
{
    return Vector(A.x+B.x, A.y+B.y);
}
Vector operator - (const Point& A, const Point& B)
{
    return Vector(A.x-B.x, A.y-B.y);
}

int Cross(const Vector& A, const Vector& B)
{
    return A.x*B.y - A.y*B.x;
}
vector<Point> ConvexHull(vector<Point>& p)
{
    sort(p.begin(), p.end());

    int m = 0, n = p.size();
    vector<Point> ch(n+1);
    for(int i = 0; i < n; ++i)
    {
        while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-1]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; i--)
    {
        while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-1]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    if(n > 1)
        m--;
    ch.resize(m);
    return ch;
}
int GetCost(const Point& a, const Point& b)
{
    return (abs(a.x+b.x) * abs(a.y+b.y)) % p;
}
int main()
{
#ifdef _Rayn
    //freopen("in.txt", "r", stdin);
#endif // _Rayn
    int x, y;
    while(scanf("%d%d", &n, &p) != EOF)
    {
        vector<Point> p;
        for(int i = 0; i < n; ++i)
        {
            scanf("%d%d", &x, &y);
            p.push_back(Point(x, y));
        }
        vector<Point> ch = ConvexHull(p);
        int m = ch.size();
        if(m < n)
        {
            printf("I can't cut.\n");
            continue;
        }
        for(int i = 0; i < m; ++i)
        {
            for(int j = i+2; j < m; ++j)
            {
                cost[i][j] = cost[j][i] = GetCost(ch[i], ch[j]);
            }
        }
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < m; ++j)
                dp[i][j] = INF;
            dp[i][(i+1)%m] = 0;
        }
        //因为要保证在算dp[i][j]时dp[i][k]和dp[k][j]时已经计算，所以i为逆序，j要升序.
        for(int i = m-3; i >= 0; --i)
        {
            for(int j = i+2; j < m; ++j)
            {
                for(int k = i+1; k < j; ++k)
                {
                    dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j]+cost[i][k]+cost[k][j]);
                }
            }
        }
        printf("%d\n", dp[0][m-1]);
    }
    return 0;
}

