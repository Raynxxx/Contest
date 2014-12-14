/*
** UVA 109 SCUD Busters
** Created by Rayn on 2014/12/13
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXK = 20 + 10;
const int MAXN = 100 + 10;
const int INF = 0x3F3F3F3F;
const double EPS = 1e-8;

inline int dcmp(double x) {
    if (fabs(x) < EPS) 
        return 0;
    return (x < 0) ? -1 : 1;
}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    friend Point operator + (const Point &A, const Point &B) {
        return Point(A.x + B.x, A.y + B.y);
    }
    friend Point operator - (const Point &A, const Point &B) {
        return Point(A.x - B.x, A.y - B.y);
    }
    friend bool operator < (const Point& A, const Point &B) {
        return dcmp(A.x - B.x) < 0 || (dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) < 0);
    }
    friend bool operator == (const Point& A, const Point &B) {
        return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0;
    }
};

double Dot(const Point& A, const Point& B) {
    return A.x * B.x + A.y * B.y;
}

double Cross(const Point &A, const Point &B) {
    return A.x * B.y - A.y * B.x;
}

bool OnSegment(Point p, Point a1, Point a2) {
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}

int isPointInPolygon(Point p, const vector<Point> &poly) {
    int wn = 0;
    for (int i = 0, sz = poly.size(); i < sz; ++i) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % sz];
        if (p1 == p || p2 == p || OnSegment(p, p1, p2)) {
            return -1;
        }
        int k = dcmp(Cross(p2 - p1, p - p1));
        int d1 = dcmp(p1.y - p.y);
        int d2 = dcmp(p2.y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if (wn != 0) return 1;
    return 0;
}

vector<Point> ConvexHull(vector<Point> &p) {
    sort(p.begin(), p.end());
    int n = p.size(), m = 0;
    vector<Point> ch(n + 1);
    for (int i = 0; i < n; ++i) {
        while (m > 1 && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) < 0) {
            m--;
        }
        ch[m++] = p[i];
    }
    int k = m;
    for (int i = n - 2; i >= 0; --i) {
        while (m > k && Cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) < 0) {
            m--;
        }
        ch[m++] = p[i];
    }
    if (n > 1) m--;
    ch.resize(m);
    return ch;
}

double PolygonArea(const vector<Point> &p) {
    double ret = 0;
    for (int i = 1, sz = p.size(); i < sz - 1; ++i) {
        ret += Cross(p[i] - p[0], p[i + 1] - p[0]);
    }
    return fabs(ret / 2.0);
}


vector<Point> kingdom[MAXK];
vector<Point> missile;

int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, x, y;
    int count = 0;
    while (cin >> n && n != -1) {
        vector<Point> pt;
        for (int i = 0; i < n; ++i) {
            cin >> x >> y;
            pt.push_back(Point(x, y));
        }
        kingdom[count++] = ConvexHull(pt);
    }
    vector<double> area(count);
    for (int i = 0; i < count; ++i) {
        area[i] = PolygonArea(kingdom[i]);
    }
    missile.clear();
    while (cin >> x >> y) {
        missile.push_back(Point(x, y));
    }
    double ret = 0;
    vector<bool> destroy(count, false);
    for (int i = 0, msz = missile.size(); i < msz; ++i) {
        Point& cur = missile[i];
        for (int j = 0; j < count; ++j) {
            if (!destroy[j] && isPointInPolygon(cur, kingdom[j]) != 0) {
                destroy[j] = true;
                ret += area[j];
                break;
            }
        }
    }
    cout << fixed << setprecision(2) << ret << endl;
    return 0;
}