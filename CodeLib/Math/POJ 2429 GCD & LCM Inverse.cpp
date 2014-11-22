/*
** POJ 2429 GCD & LCM Inverse
** Created by Rayn @@ 2014/10/29
*/
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;
const int seed = 20;

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
// (x ^ n) % m
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
	// n - 1 = 2^k * q (q是奇素数)
	// n是素数的话，一定满足下面条件
	// (i) a^q ≡ 1 (mod n)
	// (ii) a^q, a^2q,..., a^(k-1)q 中的任何一个对n求模都为-1
	//
	// 所以、当不满足(i)(ii)中的任何一个的时候，就有3/4的概率是合成数

	for (int i = 0; i < times; ++i) {
		Long a = rand() % (n - 1) + 1; // 从1,..,n-1随机挑一个数
		Long x = mod_pow(a, q, n);
		// 检查条件(i)
		if (x == 1) continue;
		// 检查条件(ii)
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

const int MAXP = 200010;
const Long INF = 1LL << 60;
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
bool IsPrime(Long n) {
	if (n < MAXP)
		return is_prime[n];
	return MillerRabin(n, 20);
}
void FindFactor(Long n, map<Long, int>& fact) {
	if (IsPrime(n)) {
		fact[n]++;
	} else {
		for (int i = 0; i < pcnt; ++i) {
			int p = prime[i];
			while (n % p == 0) {
				fact[p]++;
				n /= p;
			}
		}
		if (n != 1) {
			if (IsPrime(n)) {
				fact[n]++;
			} else {
				Long d = Pollard_rho(n, 1);
				FindFactor(d, fact);
				FindFactor(n / d, fact);
			}
		}
	}
}
pair<Long, Long> Gao(Long a, Long b) {
	Long c = b / a;
	map<Long, int> fact;
	FindFactor(c, fact);
	vector<Long> fact_mult;
	for (map<Long, int>::iterator it = fact.begin(); it != fact.end(); ++it) {
		Long mul = 1;
		while (it->second) {
			mul *= it->first;
			it->second--;
		}
		fact_mult.push_back(mul);
	}
	Long ret = INF, retx = 1, rety = c;
	int sz = fact_mult.size();
	for (int s = 0; s < (1 << sz); ++s) {
		Long x = 1;
		for (int i = 0; i < sz; ++i) {
			if (s & (1 << i)) {
				x *= fact_mult[i];
			}
		}
		Long y = c / x;
		if (x < y && x + y < ret) {
			ret = x + y;
			retx = x;
			rety = y;
		}
	}
	return make_pair(retx * a, rety * a);
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	prime_table();
	Long GCD, LCM;
	while (scanf("%lld%lld", &GCD, &LCM) != EOF) {
		pair<Long, Long> ret = Gao(GCD, LCM);
		printf("%lld %lld\n", ret.first, ret.second);
	}
	return 0;
}
