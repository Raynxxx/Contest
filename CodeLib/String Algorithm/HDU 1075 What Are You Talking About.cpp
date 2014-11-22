/*
** HDU 1075 What Are You Talking About
** Created by Rayn @@ 2014/11/06
*/
#include <map>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;
typedef long long Long;

const int MAXN = 100000;
const int MAXNODE = 1000000;
const int CharSet = 26;

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
        return ch - 'a';
    }
    int new_node() {
        val[sz] = 0;
        memset(ch[sz], 0, sizeof(ch[sz]));
        return sz++;
    }
    void Insert(string pattern, int x) {
        int u = 0, n = pattern.length();
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            if (ch[u][v] == 0) {
                ch[u][v] = new_node();
            }
            u = ch[u][v];
        }
        val[u] = x;
    }
    int Find(string pattern) {
        int u = 0, n = pattern.length();
        for (int i = 0; i < n; ++i) {
            int v = Index(pattern[i]);
            if (ch[u][v] == 0) {
                return 0;
            }
            u = ch[u][v];
        }
        return val[u];
    }
};

Trie Solver;
string dic[MAXNODE];

bool isLetter(char ch) {
    return ch >= 'a' && ch <= 'z';
}
void WriteWord(string& word) {
    if (word.length() == 0) return;
    int p = Solver.Find(word);
    if (p) {
        printf("%s", dic[p].c_str());
    }
    else {
        printf("%s", word.c_str());
    }
    word.clear();
}
void Read_Dictionary() {
    string buf;
    int n = 1;
    while (cin >> buf && buf != "END") {
        if (buf == "START") continue;
        dic[n] = buf;
        cin >> buf;
        Solver.Insert(buf, n++);
    }
}
void Translate_Book() {
    string buf, word;
    getline(cin, buf);
    while (getline(cin, buf) && buf != "END") {
        if (buf == "START") continue;
        int len = buf.length();
        for (int i = 0; i < len; ++i) {
            if (isLetter(buf[i])) {
                word += buf[i];
                if (i == len - 1) {
                    WriteWord(word);
                }
            } else {
                WriteWord(word);
                putchar(buf[i]);
            }
        }
        putchar('\n');
    }
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    Solver.Init();
    Read_Dictionary();
    Translate_Book();
    return 0;
}
