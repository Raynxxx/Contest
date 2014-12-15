/*
** UVA 110 Meta-Loopless Sorts
** Created by Rayn on 2014/12/15
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXK = 20 + 10;
const int MAXN = 100 + 10;
const int INF = 0x3F3F3F3F;
const char *alphabet = "abcdefgh";

string Indent(int cnt) {
    string ret = "";
    for (int i = 0; i < cnt; ++i) {
        ret += "  ";
    }
    return ret;
}
void MetaSort(int dep, int bounds, string &var) {
    if (dep == bounds) {
        cout << Indent(dep) << "writeln(";
        for (int i = 0, sz = var.size(); i < sz; ++i) {
            cout << var[i] << (i == sz - 1 ? ")\n" : ",");
        }
        return;
    }
    cout << Indent(dep);
    for (int i = 0; i < (int) var.size(); ++i) {
        cout << "if " << alphabet[dep] << " < " << var[i] << " then" << endl;
        var.insert(i, alphabet + dep, 1);
        MetaSort(dep + 1, bounds, var);
        var.erase(i, 1);
        cout << Indent(dep) << "else ";
    }
    cout << endl;
    var.insert(var.size(), alphabet + dep, 1);
    MetaSort(dep + 1, bounds, var);
    var.erase(var.size() - 1, 1);
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int m, n;
    cin >> m;
    while (m--) {
        cin >> n;
        string variable = "";
        for (int i = 0; i < n; ++i) {
            variable.push_back('a' + i);
            if (i != n - 1) {
                variable.push_back(',');
            }
        }
        cout << "program sort(input,output);" << endl;
        cout << "var" << endl;
        cout << variable << " : integer;" << endl;
        cout << "begin" << endl;
        cout << Indent(1) << "readln(" << variable << ");" << endl;
        string init_var = "a";
        MetaSort(1, n, init_var);
        cout << "end." << endl;
        if (m > 0) {
            cout << endl;
        }
    }
    return 0;
}

