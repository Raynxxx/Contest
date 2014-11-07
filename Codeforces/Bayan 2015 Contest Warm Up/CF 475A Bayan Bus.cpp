/*
** CF 475A Bayan Bus
** Created by Rayn @@ 2014/10/14
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

string bus[10];

void InitBus() {
	bus[0] = "+------------------------+";
	bus[1] = "|#.#.#.#.#.#.#.#.#.#.#.|D|)";
	bus[2] = "|#.#.#.#.#.#.#.#.#.#.#.|.|";
	bus[3] = "|#.......................|";
	bus[4] = "|#.#.#.#.#.#.#.#.#.#.#.|.|)";
	bus[5] = "+------------------------+";
}
int main()
{
#ifdef _Rayn
	//freopen("in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	int k;
	while (cin >> k) {
		InitBus();
		int row = 1;
		while (k) {
			for (int i = 1; i < 5; ++i) {
				if (bus[i][row] == '#') {
					bus[i][row] = 'O';
					if (--k == 0) break;
				}
			}
			row += 2;
		}
		for (int i = 0; i < 6; ++i) {
			cout << bus[i] << endl;
		}
	}
	return 0;
}
