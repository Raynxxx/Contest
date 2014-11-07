/*
** CF 434A Ryouko's Memory Note
** Created by Rayn @@ 2014/10/04
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
typedef map<int, vector<int> >::iterator Pointer;
const int MAXN = 100005;

int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF) {
		vector<int> a(m);
		map<int, vector<int> > box;
		for (int i = 0; i < m; ++i) {
			scanf("%d", &a[i]);
		}
		for (int i = 0; i < m; ++i) {
			if (i > 0 && a[i - 1] != a[i]) {
				box[a[i]].push_back(a[i - 1]);
			}
			if (i < m - 1 && a[i + 1] != a[i]) {
				box[a[i]].push_back(a[i + 1]);
			}
		}
		LL reduce = 0;
		for (Pointer it = box.begin(); it != box.end(); ++it) {
			vector<int>& pt = it->second;
			sort(pt.begin(), pt.end());
			LL tmp = 0, mid = pt[(int) pt.size() / 2];
			for (int i = 0; i < (int) pt.size(); ++i) {
				tmp += abs(it->first - pt[i]) - abs(mid - pt[i]);
			}
			reduce = max(reduce, tmp);
		}
		LL all = 0;
		for (int i = 0; i < m - 1; ++i) {
			all += abs(a[i] - a[i + 1]);
		}
		printf("%I64d\n", all - reduce);
	}
	return 0;
}
