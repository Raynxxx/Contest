/*
** POJ 1556 The Doors
** Created by Rayn @@ 2014/05/26

** ���⣺
** һ�������η����У������ɶ�ǽ��ǽ��ֱ��x����ռ��y�᷽��ÿ��ǽ���������ſ�ͨ����
** �����ŵ����꣬��ӷ�������е㵽�����ұ��е����̾��롣(������⣬�кܶ���
** �����ԭ�����)

** ��⣺�߶��ཻ + Dijkstra
** ��һ��ǽ����һ��ǽ����̾���ض�����ֱ�ߣ����������ֱ�ߣ��������·���ض��Ǿ���
** �ŵ����㣬�����Ҫ�ҳ��������е�ǽ����֮���ͨ�е��Ƿ������ӳ�һ���߶�(����ǽ�ཻ)��
** �Դ�Ϊ������ͼ�����ཻ��ӱߣ��ཻ����ֱ�ӵ��������dijstra�����·��

** ע�⣺�кܶ�ϸ�ڵĿ���
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define EPS 1e-8
using namespace std;
const int MAX = 105*4;
const int INF = 0x7FFFFFFF;

typedef struct Point {
	double x, y;
	Point(double x=0, double y=0) :
		x(x), y(y) {}
	Point operator - (const Point& b) {
		return Point(x - b.x, y - b.y);
	}
} Vector;
struct Wall {
	Point po[5];
} dot[105];


double Map[MAX][MAX], dis[MAX];
bool vis[MAX];

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
double Dot(Vector A, Vector B)
{
    return A.x*B.x + A.y*B.y;
}
double Distance(Point A, Point B)
{
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
bool OnSegment(Point p, Point a1, Point a2)
{
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}
bool SegIntersect(Point a1, Point a2, Point b1, Point b2)
{
    double d1 = Cross(a2-a1, b1-a1), d2 = Cross(a2-a1, b2-a1);
    double d3 = Cross(b2-b1, a1-b1), d4 = Cross(b2-b1, a2-b1);
    if (dcmp(d1)*dcmp(d2) < 0 && dcmp(d3)*dcmp(d4) < 0)
        return true;
    else if (d1 == 0 && OnSegment(a1, a2, b1))
        return true;
    else if (d2 == 0 && OnSegment(a1, a2, b2))
        return true;
    else if (d3 == 0 && OnSegment(b1, b2, a1))
        return true;
    else if (d4 == 0 && OnSegment(b1, b2, a2))
        return true;
    else
        return false;
}
/* �ж��߶�ab�Ƿ���ǽl��ǽr���ཻ */
bool HasIntersect(Point a, Point b, int left, int right)
{
    Point bot, top;   //ÿһ��ǽ�ĵײ��Ͷ�������
    bot.y = 0; top.y = 10;
    for(int i = left; i <= right; ++i)
    {
        bot.x = dot[i].po[0].x;
        top.x = dot[i].po[0].x;
        //ÿһ��ǽ����������γ��������߶�
        if (SegIntersect(a, b, bot, dot[i].po[0]))
            return true;
        else if (SegIntersect(a, b, dot[i].po[1], dot[i].po[2]))
            return true;
        else if (SegIntersect(a, b, dot[i].po[3], top))
            return true;
    }
    return false;
}
double Dijkstra(int n)
{
    memset(vis, false, sizeof(vis));
    for (int i = 0; i <= n; ++i)
    {
        dis[i] = Map[0][i];
    }
    vis[0] = true;
    int k;
    for(int i = 1; i <= n; ++i)
    {
        double Min = INF;
        for(int j = 1; j <= n; ++j)
        {
            if(!vis[j] && dis[j] < Min)
            {
                Min = dis[j];
                k = j;
            }
        }
        vis[k] = true;
        for(int j = 1; j <= n; ++j)
        {
            if(dis[k] + Map[k][j] < dis[j])
            {
                dis[j] = dis[k] + Map[k][j];
            }
        }
    }
    return dis[n];
}
int main()
{
	int n;
	Point Start = Point(0, 5);
	Point End = Point(10, 5);
	while (scanf("%d", &n) && n != -1)
	{
		double x, y1, y2, y3, y4;
		for (int i = 1; i <= n; ++i)
		{
			scanf("%lf%lf%lf%lf%lf", &x, &y1, &y2, &y3, &y4);
			dot[i].po[0] = Point(x, y1);
			dot[i].po[1] = Point(x, y2);
			dot[i].po[2] = Point(x, y3);
			dot[i].po[3] = Point(x, y4);
		}
		for (int i = 0; i <= 4*n+1; ++i)
		{
            for (int j = 0; j <= 4*n+1; ++j)
            {
                Map[i][j] = INF;
            }
		}
		if (n == 0)  //û��ǽ,ֱ��������
        {
            printf("%.2f\n", Distance(Start, End));
            continue;
        }
        if (!HasIntersect(Start, End, 1, n)) //������յ��������ֱ�����
        {
            printf("%.2f\n", Distance(Start, End));
            continue;
        }
        /* ��ͼ */
        // ��㵽�������е�
        for (int i = 0; i < 4; ++i)
        {
            Map[0][i+1] = Distance(Start, dot[1].po[i]);
        }
        for (int i = 2; i <= n; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (!HasIntersect(Start, dot[i].po[j], 1, i-1))
                {
                    Map[0][(i-1)*4+j+1] = Distance(Start, dot[i].po[j]);
                }
            }
        }
        // �м�ǽ���е㵽�յ�
        for (int i = 0; i < 4; ++i)
        {
            Map[(n-1)*4+i+1][4*n+1] = Distance(dot[n].po[i], End);
        }
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if(!HasIntersect(dot[i].po[j], End, i+1, n))
                {
                    Map[(i-1)*4+j+1][4*n+1] = Distance(dot[i].po[j], End);
                }
            }
        }
        // �м��ǽ��ǽ֮������ӵĵ�ӱ�
        for (int i = 1; i < n; i++)
        {
            for (int j = i+1; j <= n; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    for (int l = 0; l < 4; l++)
                    {
                        if (i+1 == j)   //����ǽ����
                        {
                            Map[(i-1)*4+k+1][(j-1)*4+l+1] = Distance(dot[i].po[k], dot[j].po[l]);
                        }
                        else   //���������ж��ܷ�ֱ�ӵ���
                        {
                            if (!HasIntersect(dot[i].po[k], dot[j].po[l], i+1, j-1))
                                Map[4*(i-1)+k+1][(j-1)*4+l+1] = Distance(dot[i].po[k], dot[j].po[l]);
                        }
                    }
                }
            }
        }
        printf("%.2f\n", Dijkstra(n*4+1));
	}
	return 0;
}
