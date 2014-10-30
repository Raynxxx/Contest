/*
** Hero¡¯s assistant
** Created by Rayn @@ 2014/08/18
*/
#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <algorithm>
#define sqr(x) ((x)*(x))
using namespace std;
typedef pair<int, int> PII;
const double EPS = 1e-10;
const double INF = 1e100;
const int MAXN = 110;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}

    void Read()
    {
        scanf("%lf%lf", &x, &y);
    }
};
typedef Point Vector;

Vector operator + (const Point& A, const Point& B)
{
    return Vector(A.x + B.x, A.y + B.y);
}
Vector operator - (const Point& A, const Point& B)
{
    return Vector(A.x - B.x, A.y - B.y);
}
Vector operator * (const Point& A, double p)
{
    return Vector(A.x * p, A.y * p);
}
Vector operator / (const Point& A, double p)
{
    return Vector(A.x / p, A.y / p);
}
int dcmp(double x)
{
    return (x < -EPS)? -1 : x > EPS;
}
double Dot(Vector A, Vector B)
{
    return A.x*B.x + A.y*B.y;
}
double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
bool IsParallel(Point p1, Point p2, Point q1, Point q2, Point& is)
{
	double m = Cross(q2-q1, p1-q1);
	double n = Cross(q2-q1, p2-q1);
	if(dcmp(n-m) == 0)
        return false;
	is = (p1*n - p2*m) / (n - m);
	return true;
}
Vector Rotate(Vector A, double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
Vector Normal(Vector A)
{
    return Vector(-A.y, A.x);
}
bool OnSegment(Point p, Point a, Point b)
{
    return dcmp(Cross(a-p, b-p)) == 0 && dcmp(Dot(a-p, b-p)) < 0;
}
bool OnLine(Point is, Point p, Point q)
{
	if(dcmp(is.x - min(p.x, q.x)) >= 0 && dcmp(is.y - min(p.y, q.y)) >= 0 &&
        dcmp(is.x - max(p.x, q.x)) <= 0 && dcmp(is.y - max(p.y, q.y)) <= 0)
        return true;
	return false;
}

double PolygonArea(const vector<Point>& p)
{
    int n = p.size();
    double ret = 0;
    for(int i = 0; i < n; i++) {
        ret += Cross(p[i]-p[0], p[(i+1)%n]-p[0]);
    }
    return ret / 2;
}

vector<Point> ConvexCut(const vector<Point>& pt, Point q1, Point q2)
{
    int n = pt.size();
	vector<Point> poly;
	for(int i = 0; i < n; ++i)
    {
		Point p1 = pt[i], p2 = pt[(i+1)%n];
		int d1 = dcmp(Cross(q2-q1, p1-q1));
		int d2 = dcmp(Cross(q2-q1, p2-q1));
		if(d1 >= 0) {
			poly.push_back(p1);
		}
		if(d1*d2 < 0) {
			Point inter;
			bool flag = IsParallel(p1, p2, q1, q2, inter);
			if (flag)
                poly.push_back(inter);
		}
	}
	return poly;
}

double Cut(vector<Point>& p, double x)
{
    int n = p.size();
    double ly = INF, ry = -INF;
    Point inter;
    for(int i = 0; i < n; ++i)
    {
        bool flag = IsParallel(p[i], p[(i+1)%n], Point(x, 0), Point(x, 1), inter);
        if(flag && OnLine(inter, p[i], p[(i+1)%n]))
        {
            ry = max(ry, inter.y);
            ly = min(ly, inter.y);
        }
    }
    return ry - ly;
}
double Gao(vector<Point>& p, double x)
{
    vector<double> st;
    for(int i = 0; i < (int) p.size(); ++i)
    {
        st.push_back(p[i].x);
    }
    sort(st.begin(), st.end());
    double ret = 0;
    for(int i = 1; i < (int) st.size(); ++i)
    {
        double a = st[i-1], d = st[i];
        double b = (a + d) / 2;
        double fa = Cut(p, a), fb = Cut(p, b), fd = Cut(p, d);
        ret += (sqr(a-x)*fa + sqr(b-x)*fb*4 + sqr(d-x)*fd) * ((d-a) / 6);
    }
    return ret;
}
vector<Point> AddLine(vector<Point>& p, Point p1, Point p2)
{
	Point m = (p1 + p2) / 2;
	Point r = Normal(p2-p1);
	return ConvexCut(p, m, m+r);
}
Point p[MAXN];
vector<Point> maze;

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n, X, Y;
        scanf("%d%d%d", &n, &X, &Y);
        for(int i = 0; i < n; ++i)
        {
            p[i].Read();
        }
        double tot = X*Y, res = 0;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(i == j)
                    continue;
                maze.clear();
                maze.push_back(Point(0, 0));
                maze.push_back(Point(X, 0));
                maze.push_back(Point(X, Y));
                maze.push_back(Point(0, Y));
                maze = AddLine(maze, p[i], p[j]);
                for(int k = 0; k < n; ++k)
                {
                    if(k != i && k != j)
                    {
                        if(dcmp(PolygonArea(maze)) <= 0)
                            break;
                        maze = AddLine(maze, p[i], p[k]);
                        if(dcmp(PolygonArea(maze)) <= 0)
                            break;
                        maze = AddLine(maze, p[j], p[k]);
                    }
                }
                res += Gao(maze, p[j].x);
                for(int k = 0; k < (int) maze.size(); ++k) {
                    swap(maze[k].x, maze[k].y);
                }
                res += Gao(maze, p[j].y);
            }
        }
        printf("%.10f\n", res/tot);
    }
    return 0;
}
