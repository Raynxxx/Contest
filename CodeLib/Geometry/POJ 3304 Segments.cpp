/*
** POJ 3304 Segments
** Created by Rayn @@ 2014/05/23
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#define EPS 1e-8
using namespace std;
const int MAX = 210;

typedef struct Point {
	double x, y;
	Point(double x = 0, double y = 0) :
		x(x), y(y) {}
	Point operator - (const Point& b) {
		return Point(x - b.x, y - b.y);
	}
} Vector;

Point point[MAX];

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
int main()
{
	int t, n;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		double x1, y1, x2, y2;
		for (int i = 1; i <= 2*n; i+=2)
		{
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			point[i] = Point(x1, y1);
			point[i+1] = Point(x2, y2);
		}
		int flag = 0;
		for (int i = 1; i <= 2*n && !flag; ++i)
		{
			for (int j = 1; j <= 2*n && !flag; ++j)
			{
				Point p1 = point[i], p2 = point[j];
				if (dcmp(p1.x-p2.x)==0 && dcmp(p1.y-p2.y)==0)	//ÅÐ¶ÏÏß¶ÎÖØºÏ
					continue;
				flag = 1;
				for (int k = 1; k <= 2*n; k+=2)
				{
					if (Cross(p1-point[k], p2-point[k]) * Cross(p1-point[k+1], p2-point[k+1]) > EPS)
					{
						flag = 0;
						break;
					}
				}
			}
		}
		if (flag)
			printf("Yes!\n");
		else
			printf("No!\n");
	}
	return 0;
}
