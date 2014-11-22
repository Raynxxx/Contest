/*
** UVA 12722 Cryptography of the Floating Key
** Created by Rayn @@ 2014/10/01
*/
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int MAXN = 124;
const int MAXL = 10100;

int n, m;
char str[MAXL];
char ret[MAXL];
char before[MAXN][MAXN];
char after[MAXN][MAXN];

void Gao(int cases, int length)
{
    while(n * m < length) {
        if(n < m) {
            n += m;
        } else if(n > m) {
            m += n;
        } else {
            m *= 2;
        }
    }
    memset(before, 0, sizeof(before));
    int t = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = m-1; j >= 0; --j) {
            if(t++ < length) {
                before[j][i] = 1;
            }
        }
    }
    t = 0;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            if(before[i][j]) {
                before[i][j] = str[t++];
            }
        }
    }
    /*
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            printf("%c ", a[i][j]);
        }
        puts("");
    }
    //*/
    int maxi = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            after[i][j] = before[m-j-1][i];
            if(after[i][j]) {
                maxi = max(maxi, i);
            }
        }
    }
    t = 0;
    int x, y;
    for(int i = 0; i < maxi; ++i) {
        if(i & 1) {
            for(int j = m-1; j >= 0; --j) {
                if(t & 1) {
                    swap(after[i][j], after[x][y]);
                }
                t++;
                x = i, y = j;
            }
        } else {
            for(int j = 0; j < m; ++j) {
                if(t & 1) {
                    swap(after[i][j], after[x][y]);
                }
                t++;
                x = i, y = j;
            }
        }
    }
    /*
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            printf("%c ", b[i][j]);
        }
        puts("");
    }
    //*/
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            after[i][j] = (after[i][j] - 'a' - i - j - 2);
            after[i][j] %= 26;
            after[i][j] += 26;
            after[i][j] %= 26;
            after[i][j] += 'a';
        }
    }
    /*
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            printf("%c ", b[i][j]);
        }
        puts("");
    }
    //*/
    t = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            ret[t++] = after[i][j];
        }
    }
    ret[length] = '\0';
    printf("Case #%d: %s\n", cases, ret);
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T, cases = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s%d%d", str, &n, &m);
        Gao(++cases, strlen(str));
    }
    return 0;
}
