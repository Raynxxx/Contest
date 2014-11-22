/*
** POJ 1269 Intersecting Lines
** Created by Rayn @@ 2014/05/23
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#define EPS 1e-10
using namespace std;
const int MAX = 50;

struct Point {
	double x, y;
	Point(double x=0, double y=0) :
		x(x), y(y) {}
	Point operator - (const Point& b) {
		return Point(x - b.x, y - b.y);
	}
} dot[MAX];
typedef Point Vector;

int dcmp(double x)
{
	if (fabs(x) < EPS)
		return 0;
	else
		return (x < 0) ? -1 : 1;
}
double Cross(Vector A, Vector B)
{
	return A.x*B.y - A.y*B.x;
}
int OnSegment(Point p1, Point p2, Point p3)
{
	return dcmp(Cross(p2-p1, p3-p1)) == 0;
}
int Parallel(Point p1, Point p2, Point p3, Point p4)
{
	return dcmp((p1.x - p2.x)*(p3.y - p4.y) - (p1.y - p2.y)*(p3.x - p4.x)) == 0;
}
Point GetInsert(Point p1, Point p2, Point p3, Point p4)
{
	double a1 = p1.y - p2.y;
	double b1 = p2.x - p1.x;
	double c1 = p1.x*p2.y - p2.x*p1.y;
	double a2 = p3.y - p4.y;
	double b2 = p4.x - p3.x;
	double c2 = p3.x*p4.y - p4.x*p3.y;
	//printf("%.2f %.2f %.2f\n", a1, b1, c1);
	//printf("%.2f %.2f %.2f\n", a2, b2, c2);
	double x0 = (b1*c2 - b2*c1) / (a1*b2 - a2*b1);
	double y0 = (a1*c2 - a2*c1) / (b1*a2 - b2*a1);
	return Point(x0, y0);
}
int main()
{
	int n;

	scanf("%d", &n);
	double x1, x2, x3, x4;
	double y1, y2, y3, y4;
	for (int i = 1; i <= 4*n; i+=4)
	{
		scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
		scanf("%lf%lf%lf%lf", &x3, &y3, &x4, &y4);
		dot[i] = Point(x1, y1);
		dot[i+1] = Point(x2, y2);
		dot[i+2] = Point(x3, y3);
		dot[i+3] = Point(x4, y4);
	}
	printf("INTERSECTING LINES OUTPUT\n");
	for (int i = 1; i <= 4*n; i+=4)
	{
		Point p1 = dot[i], p2 = dot[i+1];
		Point p3 = dot[i+2], p4 = dot[i+3];
		if (OnSegment(p1, p2, p3) && OnSegment(p1, p2, p4))
		{
			printf("LINE\n");
			continue;
		}
		if (Parallel(p1, p2, p3, p4))
		{
			printf("NONE\n");
			continue;
		}
		Point ans = GetInsert(p1, p2, p3, p4);
		printf("POINT %.2f %.2f\n", ans.x, ans.y);
	}
	printf("END OF OUTPUT\n");
	return 0;
}