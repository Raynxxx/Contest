/*
** POJ 2191 Mersenne Composite Numbers
** Created by Rayn @@ 2014/10/30
*/
#include <map>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;
const int MAXN = 20010;

inline void FixMod(Long& x, Long MOD) {
	while (x >= MOD) x -= MOD;
	while (x < 0) x += MOD;
}
// (a * b) % m
Long mod_mult(Long a, Long b, Long MOD) {
	Long ret = 0;
	Long exp = a % MOD;
	while (b) {
		if (b & 1) {
			ret += exp;
			FixMod(ret, MOD);
		}
		exp <<= 1;
		FixMod(exp, MOD);
		b >>= 1;
	}
	return ret;
}
// (a ^ b) % m
Long mod_pow(Long x, Long n, Long MOD) {
	Long ret = 1;
	Long exp = x % MOD;
	while (n) {
		if (n & 1)
			ret = mod_mult(ret, exp, MOD);
		exp = mod_mult(exp, exp, MOD);
		n >>= 1;
	}
	return ret;
}

bool MillerRabin(Long n, Long times) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (!(n & 1)) return false;
	Long q = n - 1, k = 0;
	while (q % 2 == 0) {
		k++;
		q >>= 1;
	}
	// n - 1 = 2^k * q (q��������)
	// n�������Ļ���һ��������������
	// (i) a^q �� 1 (mod n)
	// (ii) a^q, a^2q,..., a^(k-1)q �е��κ�һ����n��ģ��Ϊ-1
	//
	// ���ԡ���������(i)(ii)�е��κ�һ����ʱ�򣬾���3/4�ĸ����Ǻϳ���

	for (int i = 0; i < times; ++i) {
		Long a = rand() % (n - 1) + 1; // ��1,..,n-1�����һ����
		Long x = mod_pow(a, q, n);
		// �������(i)
		if (x == 1) continue;
		// �������(ii)
		bool found = false;
		for (int j = 0; j < k; ++j) {
			if (x == n - 1) {
				found = true;
				break;
			}
			x = mod_mult(x, x, n);
		}
		if (found) continue;
		return false;
	}
	return true;
}

const int MAXP = 100;
bool is_prime[MAXP];
int pcnt, prime[MAXP];

void prime_table() {
	fill_n(is_prime, MAXP, true);
	is_prime[0] = is_prime[1] = false;
	pcnt = 0;
	for (int i = 2; i < MAXP; ++i) {
		if (is_prime[i]) {
			prime[pcnt++] = i;
			for (int j = i * 2; j < MAXP; j += i) {
				is_prime[j] = false;
			}
		}
	}
}
Long gcd(Long a, Long b) {
	if (a == 0) return 1;
	if (a < 0) return gcd(-a, b);
	return (b == 0) ? a : gcd(b, a % b);
}

Long Pollard_rho(Long n, Long c) {
	Long x = 2, y = 2, d = 1;
	while (d == 1) {
		x = mod_mult(x, x, n) + c;
		y = mod_mult(y, y, n) + c;
		y = mod_mult(y, y, n) + c;
		d = gcd((x >= y ? x - y : y - x), n);
	}
	if (d == n)
		return Pollard_rho(n, c + 1);
	return d;
}

void FindFactor(Long n, vector<Long>& ret) {
	if (MillerRabin(n, 10)) {
		ret.push_back(n);
		return;
	}
	Long p = n;
	while (p >= n) {
		p = Pollard_rho(n, rand() % (n - 1) + 1);
	}
	FindFactor(p, ret);
	FindFactor(n / p, ret);
}

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	prime_table();
	int k;
	while (scanf("%d", &k) != EOF) {
		for (int i = 1; prime[i] <= k; ++i) {
			Long n = (1LL << prime[i]) - 1;
			if (MillerRabin(n, 10)) {
				continue;
			}
			vector<Long> ret;
			FindFactor(n, ret);
			sort(ret.begin(), ret.end());
			for (int j = 0; j < (int) ret.size() - 1; ++j) {
				printf("%lld * ", ret[j]);
			}
			printf("%lld = %lld = ( 2 ^ %d ) - 1\n", ret[ret.size() - 1], n, prime[i]);
		}
	}
	return 0;
}
