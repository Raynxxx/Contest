/*
** HDU 1305 Immediate Decodability
** Created by Rayn @@ 2014/11/06
*/
#include <map>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXNODE = 10000;
const int CharSet = 2;

class Trie {
public:
    int sz;
    int ch[MAXNODE][CharSet];
    int val[MAXNODE];

    void Init() {
        sz = 1;
        val[0] = 0;
        memset(ch[0], 0, sizeof(ch[0]));
    }
    int Index(char ch) {
        return ch - '0';
    }
    int new_node() {
        val[sz] = 0;
        memset(ch[sz], 0, sizeof(ch[sz]));
        return sz++;
    }
    void Insert(string& pattern) {
        int u = 0;
        for(int i = 0; pattern[i] != '\0'; ++i) {
            int v = Index(pattern[i]);
            if(ch[u][v] == 0) {
                ch[u][v] = new_node();
            }
            u = ch[u][v];
        }
        val[u] = 1;
    }
    bool Search(string& pattern) {
        int u = 0;
        for(int i = 0; pattern[i] != '\0'; ++i) {
            int v = Index(pattern[i]);
            if(val[u]) {
                return true;
            }
            u = ch[u][v];
        }
        return false;
    }
};

Trie Solver;
vector<string> codeBox;
string code;

bool ReadData() {
    Solver.Init();
    codeBox.clear();
    while(getline(cin, code) && code != "9") {
        codeBox.push_back(code);
        Solver.Insert(code);
    }
    return codeBox.size() > 0;
}
bool Check() {
    int n = codeBox.size();
    for(int i = 0; i < n; ++i) {
        if(Solver.Search(codeBox[i])) {
            return false;
        }
    }
    return true;
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int step = 1;
    while(ReadData()) {
        printf("Set %d ", step++);
        if(Check()) {
            puts("is immediately decodable");
        } else {
            puts("is not immediately decodable");
        }
    }
    return 0;
}
