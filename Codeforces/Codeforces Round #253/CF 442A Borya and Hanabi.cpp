/*
** CF 442A Borya and Hanabi
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
const int INF = 0x3F3F3F3F;
const int MAXN = 105;

int n;
map<char, int> ColorIndex;

void Init() {
	ColorIndex['R'] = 0;
	ColorIndex['G'] = 1;
	ColorIndex['B'] = 2;
	ColorIndex['Y'] = 3;
	ColorIndex['W'] = 4;
}
int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	Init();
	while (scanf("%d", &n) != EOF)
	{
		int card = 0;
		for (int i = 0; i < n; ++i) {
			char buf[5];
			scanf("%s", buf);
			int c = ColorIndex[buf[0]];
			int v = buf[1] - '1';
			card |= 1 << (c * 5 + v);
		}
		int ret = INF;
		for (int c = 0; c < (1 << 5); ++c) {
			for (int v = 0; v < (1 << 5); ++v) {
				vector<int> hint(25, 0);
				int sz = 0;
				for (int i = 0; i < 5; ++i) {
					if ((c >> i) & 1) {
						sz++;
						for (int j = 0; j < 5; ++j) {
							hint[i * 5 + j] |= (1 << i);
						}
					}
				}
				for (int j = 0; j < 5; ++j) {
					if ((v >> j) & 1) {
						sz++;
						for (int i = 0; i < 5; ++i) {
							hint[i * 5 + j] |= (1 << (j + 5));
						}
					}
				}
				vector<int> state;
				for (int i = 0; i < 25; ++i) {
					if ((card >> i) & 1) {
						state.push_back(hint[i]);
					}
				}
				sort(state.begin(), state.end());
				if (unique(state.begin(), state.end()) == state.end()) {
					ret = min(ret, sz);
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
