/*
** CF 222E Little Elephant and Inversions
** Created by Rayn @@ 2014/10/12
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
const int MAXN = 100050;

class BinaryIndexedTree {
public:
	int n;
	int tree[MAXN];
	void Init(int n) {
		this->n = n;
		fill_n(tree, n + 10, 0);
	}
	inline int LowBit(int x) {
		return x & (-x);
	}
	void Change(int idx, int v) {
		while (idx <= n) {
			tree[idx] += v;
			idx += LowBit(idx);
		}
	}
	int Query(int idx) {
		int sum = 0;
		while (idx > 0) {
			sum += tree[idx];
			idx -= LowBit(idx);
		}
		return sum;
	}
};

BinaryIndexedTree pre;
BinaryIndexedTree last;
pair<int, int> arr[MAXN];
vector<int> refer;

void Init(int n) {
	refer.resize(n + 1);
	pre.Init(n);
	last.Init(n);
}
void InputData(int n) {
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &arr[i].first);
		arr[i].second = i;
	}
	sort(arr + 1, arr + 1 + n);
	for (int i = 1; i <= n; ++i) {
		if (arr[i].first != arr[i - 1].first) {
			refer[arr[i].second] = refer[arr[i - 1].second] + 1;
		}
		else {
			refer[arr[i].second] = refer[arr[i - 1].second];
		}
	}
}

void TwoPoint(int n, long long k) {
	long long inver = 0, ret = 0;
	for (int i = 1; i <= n; ++i) {
		last.Change(refer[i], +1);
		inver += (last.Query(n) - last.Query(refer[i]));
	}
	int j = 1;
	for (int i = 1; i <= n; ++i) {
		while (j <= i) {
			last.Change(refer[j], -1);
			inver -= last.Query(refer[j] - 1) + (pre.Query(n) - pre.Query(refer[j]));
			++j;
		}
		pre.Change(refer[i], +1);
		inver += last.Query(refer[i] - 1) + (pre.Query(n) - pre.Query(refer[i]));
		while (j <= n && inver > k) {
			last.Change(refer[j], -1);
			inver -= last.Query(refer[j] - 1) + (pre.Query(n) - pre.Query(refer[j]));
			j++;
		}
		ret += n - j + 1;
	}
	printf("%I64d\n", ret);
}
int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int n;
	long long k;
	while (scanf("%d%I64d", &n, &k) != EOF) {
		Init(n);
		InputData(n);
		TwoPoint(n, k);
	}
	return 0;
}
