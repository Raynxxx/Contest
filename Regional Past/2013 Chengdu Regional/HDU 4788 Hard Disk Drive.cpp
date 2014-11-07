/*
** HDU 4788 Hard Disk Drive
** Created by Rayn @@ 2014/10/27
*/
#include <map>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

double kilo1[15];
double kilo2[15];

void Init() {
	kilo1[1] = kilo2[1] = 1;
	for (int i = 2; i <= 9; ++i) {
		kilo1[i] = kilo1[i - 1] * 1000.0;
		kilo2[i] = kilo2[i - 1] * 1024.0;
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	Init();
	int T, cases = 0;
	scanf("%d", &T);
	while (T--) {
		int sz;
		char unit[10];
		scanf("%d%s", &sz, unit);
		double ret;
		if (!strcmp(unit, "[B]")) {
			ret = 1 - kilo1[1] / kilo2[1];
		} else if (!strcmp(unit, "[KB]")) {
			ret = 1 - kilo1[2] / kilo2[2];
		} else if (!strcmp(unit, "[MB]")) {
			ret = 1 - kilo1[3] / kilo2[3];
		} else if (!strcmp(unit, "[GB]")) {
			ret = 1 - kilo1[4] / kilo2[4];
		} else if (!strcmp(unit, "[TB]")) {
			ret = 1 - kilo1[5] / kilo2[5];
		} else if (!strcmp(unit, "[PB]")) {
			ret = 1 - kilo1[6] / kilo2[6];
		} else if (!strcmp(unit, "[EB]")) {
			ret = 1 - kilo1[7] / kilo2[7];
		} else if (!strcmp(unit, "[ZB]")) {
			ret = 1 - kilo1[8] / kilo2[8];
		} else if (!strcmp(unit, "[YB]")) {
			ret = 1 - kilo1[9] / kilo2[9];
		}
		printf("Case #%d: %.2f%%\n", ++cases, ret * 100);
	}
	return 0;
}