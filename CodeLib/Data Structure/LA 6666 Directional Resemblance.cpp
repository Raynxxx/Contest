/*
** LA 6666 Directional Resemblance
** Created by Rayn @@ 2014/10/15
*/
#include <map>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int MAXN = 2000050;
const double EPS = 1e-9;
const double DINF = 1e30;

inline int dcmp(double x) {
	if (fabs(x) < EPS)
		return 0;
	return (x < 0) ? -1 : 1;
}
inline double sqr(double x) {
	return x * x;
}

struct Point3 {
	double x, y, z;
	int id;
	Point3() {}
	Point3(double x, double y, double z):
		x(x), y(y), z(z) {}
	Point3 operator + (const Point3 &a) const {
		return Point3(x + a.x, y + a.y, z + a.z);
	}
	Point3 operator - (const Point3 &a) const {
		return Point3(x - a.x, y - a.y, z - a.z);
	}
	Point3 operator * (const double &k) const {
		return Point3(k * x, k * y, k * z);
	}
	Point3 operator / (const double &k) const {
		return  Point3(x / k, y / k, z / k);
	}
	bool operator < (const Point3 &a) const {
		if (dcmp(x - a.x)) return dcmp(x - a.x) < 0;
		if (dcmp(y - a.y)) return dcmp(y - a.y) < 0;
		if (dcmp(z - a.z)) return dcmp(z - a.z) < 0;
		return id < a.id;
	}
	bool operator == (const Point3 &a) const {
		return !dcmp(x - a.x) && !dcmp(y - a.y) && !dcmp(z - a.z);
	}
	bool operator != (const Point3 &a) const {
		return dcmp(x - a.x) || dcmp(y - a.y) || dcmp(z - a.z);
	}
	void read() {
		scanf("%lf %lf %lf", &x, &y, &z);
	}
	void print() {
		printf("%.6f %.6f %.6f\n", x, y, z);
	}
	bool isZero() {
		return !dcmp(x) && !dcmp(y) && !dcmp(z);
	}
};

typedef Point3 Vector3;

inline double Dist(const Point3& A, const Point3& B) {
	return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y) + sqr(A.z - B.z));
}
inline double Length(const Vector3& A) {
	return sqrt(sqr(A.x) + sqr(A.y) + sqr(A.z));
}

struct Node {
	int x, y, z;
	Node() {}
	Node(int x, int y, int z) : x(x), y(y), z(z) {}
	bool operator < (const Node& rhs) const {
		if (x != rhs.x) return x < rhs.x;
		if (y != rhs.y) return y < rhs.y;
		return z < rhs.z;
	}
	bool operator == (const Node& rhs) const {
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}
	inline double Length() {
		return sqrt(sqr(x) + sqr(y) + sqr(z));
	}
};

int n, m, S, W;
int Rank[MAXN];
Node orgin[MAXN];
Point3 pt[MAXN];

bool cmpRank(const int& a, const int& b) {
	return dcmp(pt[a].y - pt[b].y) < 0;
}
double Merge(int l, int r, PII& ret) {
	if (l == r) {
		ret = make_pair(-1, -1);
		return DINF;
	}
	if (r - l == 1) {
		ret = make_pair(min(pt[l].id, pt[r].id), max(pt[l].id, pt[r].id));
		return Dist(pt[l], pt[r]);
	}
	int mid = (l + r) >> 1;
	PII Leftret, Rightret;
	double LeftVal, RightVal, Val;
	LeftVal = Merge(l, mid, Leftret);
	RightVal = Merge(mid + 1, r, Rightret);
	if(dcmp(LeftVal - RightVal) < 0) {
		Val = LeftVal;
		ret = Leftret;
	} else if (dcmp(RightVal - LeftVal) < 0) {
		Val = RightVal;
		ret = Rightret;
	} else {
		Val = LeftVal;
		ret = min(Leftret, Rightret);
	}
	int sz = 0;
	for (int i = l; i <= r; ++i) {
		if (dcmp(fabs(pt[i].x - pt[mid].x) - Val) < 0) {
			Rank[sz++] = i;
		}
	}
	sort(Rank, Rank + sz, cmpRank);
	for (int i = 0; i < sz; i++) {
		for (int j = i + 1; j < sz && dcmp(fabs(pt[Rank[i]].y - pt[Rank[j]].y) - Val) < 0; j++) {
			double d = Dist(pt[Rank[i]], pt[Rank[j]]);
			int x = min(pt[Rank[i]].id, pt[Rank[j]].id);
			int y = max(pt[Rank[i]].id, pt[Rank[j]].id);
			PII t = make_pair(x, y);
			if (dcmp(Val - d) > 0) {
				Val = d;
				ret = t;
			} else if (dcmp(Val - d) == 0) {
				ret = min(ret, t);
			}
		}
	}
	return Val;
}

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	while (scanf("%d%d%d%d", &m, &n, &S, &W) && (m || n || S || W)) {
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &orgin[i].x, &orgin[i].y, &orgin[i].z);
		}
		int g = S;
		for (int i = m; i < m + n; i++) {
			orgin[i].x = (g / 7) % 100 + 1;
			orgin[i].y = (g / 700) % 100 + 1;
			orgin[i].z = (g / 70000) % 100 + 1;
			if (g % 2 == 0) {
				g = g / 2;
			} else {
				g = (g / 2) ^ W;
			}
		}
		n += m;
		sort(orgin, orgin + n);
		for (int i = 0; i < n; ++i) {
			double len = orgin[i].Length();
			pt[i] = Point3(orgin[i].x, orgin[i].y, orgin[i].z);
			pt[i] = pt[i] / len;
			pt[i].id = i;
		}
		sort(pt, pt + n);
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			if (pt[i] != pt[i - 1]) {
				pt[cnt++] = pt[i];
			}
		}
		PII ret = make_pair(-1, -1);
		double d = Merge(0, cnt - 1, ret);
		int i = ret.first;
		int j = ret.second;
		printf("%d %d %d ", orgin[i].x, orgin[i].y, orgin[i].z);
		printf("%d %d %d\n", orgin[j].x, orgin[j].y, orgin[j].z);
	}
	return 0;
}
