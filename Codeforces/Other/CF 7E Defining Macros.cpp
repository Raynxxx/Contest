/*
** CF 7E Defining Macros
** Created by Rayn @@ 2014/09/09
*/
#include <cstdio>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1024;
const int SUS = 0;
const int ADD = 1;
const int MUL = 2;
const int ATOM = 3;

char buf[MAXN];
map<string, int> macro;
map<char, int> prior;

int Gao(string& str, int l, int r)
{
    int p = 0, minv = 3, pos = -1;
    for(int i = r; i >= l; --i) {
        if(str[i] == ')') p++;
        if(str[i] == '(') p--;
        if(p == 0 && prior.count(str[i]) && prior[str[i]] < minv) {
            minv = prior[str[i]];
            pos = i;
        }
    }
    if(minv == 3) {
        if(str[l] == '(') {
            return Gao(str, l+1, r-1) == SUS ? SUS : ATOM;
        } else {
            string t = str.substr(l, r-l+1);
            return macro.count(t)? macro[t] : ATOM;
        }
    }
    int lv = Gao(str, l, pos-1);
    int rv = Gao(str, pos+1, r);
    if(lv == SUS || rv == SUS) {
        return SUS;
    } else if(str[pos] == '+') {
        return ADD;
    } else if(str[pos] == '-') {
        return rv == ADD ? SUS : ADD;
    } else if(lv == ADD || rv == ADD) {
        return SUS;
    } else if(str[pos] == '*') {
        return MUL;
    } else {
        return rv == MUL ? SUS : MUL;
    }
}
inline string getExpression()
{
    gets(buf);
    int n = strlen(buf);
    string ret;
    for(int i = 0; i < n; ++i) {
        if(buf[i] != ' ') ret += buf[i];
    }
    return ret;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int n;
    prior['+'] = ADD;
    prior['-'] = ADD;
    prior['*'] = MUL;
    prior['/'] = MUL;
    while(scanf("%d ", &n) != EOF)
    {
        macro.clear();
        for(int i = 0; i < n; ++i) {
            string name, expr;
            scanf(" #%*s %s", buf);
            name = string(buf);
            expr = getExpression();
            macro[name] = Gao(expr, 0, expr.length() - 1);
        }
        string expr = getExpression();
        int ret = Gao(expr, 0, expr.length() - 1);
        if(ret == SUS) {
            printf("Suspicious\n");
        } else {
            printf("OK\n");
        }
    }
    return 0;
}

