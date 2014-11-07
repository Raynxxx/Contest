/*
** CodeForces 1C Ancient Berland Circus
** Created by Rayn @@ 2014/05/19
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#define EPS 1e-5
typedef long long LL;
const int MAX = 1010;
const double PI = acos(-1.0);

struct Pillar
{
	double x, y;
} point[5];

double Length(Pillar a, Pillar b)
{
	return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}
double GetS(double a, double b, double c)
{
	double p = (a + b + c) / 2;
	return sqrt(p*(p - a)*(p - b)*(p - c));
}
double fgcd(double x, double y)
{
	while (fabs(x) > EPS && fabs(y) > EPS)
	{
		if (x > y)
			x -= floor(x / y)*y;
		else
			y -= floor(y / x)*x;
	}
	return x + y;
}
int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	double la, lb, lc, S, R;
	double angA, angB, angC;
	
	for (int i = 0; i < 3; ++i)
	{
		scanf("%lf%lf", &point[i].x, &point[i].y);
	}
	la = Length(point[0], point[1]);
	lb = Length(point[0], point[2]);
	lc = Length(point[1], point[2]);
	S = GetS(la, lb, lc);
	R = la * lb * lc / (4 * S);

	angA = acos((lb*lb + lc*lc - la*la) / (2 * lb * lc));
	angB = acos((la*la + lc*lc - lb*lb) / (2 * la * lc));
	angC = acos((la*la + lb*lb - lc*lc) / (2 * la * lb));
	double n = PI / fgcd(fgcd(angA, angB), angC);
	double ans = n/2 * sin(2 * PI / n) * R*R;
	printf("%.6f\n", ans);

	return 0;
}