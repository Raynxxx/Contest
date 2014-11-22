/*
** HDU 4099 Revenge of Fibonacci
** Created by Rayn @@ 2014/10/07
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

class BigInt {
public:
	const static int MAXL = 50;

	int arr[100];
	int length;

	BigInt() {
		memset(arr, 0, sizeof(arr));
		length = 1;
	}
	BigInt(const int& x) {
		memset(arr, 0, sizeof(arr));
		length = 0;
		arr[length++] = x;
	}
	friend BigInt operator + (BigInt& A, BigInt& B) {
		BigInt ret;
		ret.length = max(A.length, B.length);
		int reminder = 0;
		for (int i = 0; i < ret.length; ++i) {
			int cur = reminder + A.arr[i] + B.arr[i];
			ret.arr[i] = cur % 10;
			reminder = cur / 10;
		}
		if (reminder != 0) {
			ret.arr[ret.length++] = 1;
		}
		if (ret.length > MAXL) {
			for (int i = 0; i < MAXL; ++i) {
				A.arr[i] = A.arr[i + 1];
			}
			for (int i = 0; i < MAXL; ++i) {
				B.arr[i] = B.arr[i + 1];
			}
			for (int i = 0; i < MAXL; ++i) {
				ret.arr[i] = ret.arr[i + 1];
			}
			--A.length, --B.length, --ret.length;
		}
		return ret;
	}
	void OutPut() {
		for (int i = length-1; i >= 0; --i) {
			printf("%d", arr[i]);
		}
		printf("\n");
	}
};

class Trie {
public:
	const static int MAXNODE = 4000000;
	const static int SIZE = 10;

	int ch[MAXNODE][SIZE];
	int val[MAXNODE];
	int sz;

	void Init() {
		sz = 1;
		memset(ch[0], 0, sizeof(ch[0]));
		memset(val, -1, sizeof(val));
	}
	void Insert(BigInt& str, int index) {
		int cur = 0;
		for (int i = str.length - 1; i >= max(str.length - 41, 0); --i) {
			int v = str.arr[i];
			if (!ch[cur][v]) {
				memset(ch[sz], 0, sizeof(ch[sz]));
				if (val[sz] == -1) {
					val[sz] = index;
				}
				ch[cur][v] = sz++;
			}
			cur = ch[cur][v];
		}
	}
	int Search(char *str) {
		int cur = 0;
		for (int i = 0; str[i] != '\0'; ++i) {
			int c = str[i] - '0';
			if (!ch[cur][c]) {
				return -1;
			}
			cur = ch[cur][c];
		}
		return val[cur];
	}
};

Trie trie;
BigInt Fib[3];

void Init() {
	Fib[0] = Fib[1] = BigInt(1);
	trie.Init();
	trie.Insert(Fib[1], 0);
	for (int i = 2; i < 100000; ++i) {
		Fib[i % 3] = Fib[(i + 1) % 3] + Fib[(i + 2) % 3];
		trie.Insert(Fib[i % 3], i);
	}
}
int main()
{
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	Init();
	int T, cases = 0;
	char buf[100];
	scanf("%d", &T);
	while (T--) {
		scanf("%s", buf);
		printf("Case #%d: %d\n", ++cases, trie.Search(buf));
	}
	return 0;
}
