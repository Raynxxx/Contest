/*
** ZOJ 3818 Pretty Poem
** Created by Rayn @@ 2014/09/18
*/
#include <map>
#include <set>
#include <cmath>
#include <cstdio>
#include <vector>
#include <bitset>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 410;

bool is_pretty1(string s)
{
    if(s.length() < 5) return false;
    for(int lenA = 1; lenA * 3 < s.length(); lenA++) {
        string A = s.substr(0, lenA);
        for(int lenB = 1; lenA * 3 + lenB * 2 <= s.length(); lenB++) {
            if(lenA * 3 + lenB * 2 != s.length()) continue;
            string B = s.substr(lenA, lenB);
            if(A != B) {
                string AA = s.substr(lenA + lenB, lenA);
                string BB = s.substr(lenA * 2 + lenB, lenB);
                string AAA = s.substr(lenA * 2 + lenB * 2, lenA);
                if(A == AA && A == AAA && B == BB)
                    return true;
            }
        }
    }
    return false;
}

bool is_pretty2(string s)
{
    if(s.length() < 7) return false;
    for(int lenA = 1; lenA * 3 < s.length(); lenA++) {
        string A = s.substr(0, lenA);
        for(int lenB = 1; lenA * 3 + lenB * 3 < s.length(); lenB++) {
            string B = s.substr(lenA, lenB);
            if(A != B) {
                int lenC = s.length() - 3 * lenA - 3 * lenB;
                string AA = s.substr(lenA + lenB, lenA);
                string BB = s.substr(lenA * 2 + lenB, lenB);
                string C = s.substr(lenA * 2 + lenB * 2, lenC);
                string AAA = s.substr(lenA * 2 + lenB * 2 + lenC, lenA);
                string BBB = s.substr(lenA * 3 + lenB * 2 + lenC, lenB);
                if(A == AA && A == AAA && B == BB && B == BBB && A != C && B != C)
                    return true;
            }
        }
    }
    return false;
}

bool is_pretty(string s)
{
    return is_pretty1(s) || is_pretty2(s);
}

int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    string tmp;
    scanf("%d", &T);
    while(T--)
    {
        cin >> tmp;
        string str = "";
        for(int i = 0; i < (int) tmp.length(); i++) {
            if(isalpha(tmp[i])) {
                str += tmp[i];
            }
        }
        if(is_pretty(str)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}
