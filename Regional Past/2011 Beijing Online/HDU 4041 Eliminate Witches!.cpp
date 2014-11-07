/*
** HDU 4041 Eliminate Witches!
** Created by Rayn @@ 2014/11/04
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
const int MAXN = 1000010;

char buf[MAXN];
vector<string> witch;

bool isLowerLetter(char ch) {
    return ch >= 'a' && ch <= 'z';
}
int main() {
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", buf);
        int buf_len = strlen(buf);
        witch.clear();
        bool word = false;
        string name;
        for (int i = 0; i < buf_len; ++i) {
            if (isLowerLetter(buf[i])) {
                name += buf[i];
                word = true;
            } else {
                if (!word) continue;
                witch.push_back(name);
                name = "";
                word = false;
            }
        }
        if (word) {
            witch.push_back(name);
            word = false;
        }
        int witch_cnt = witch.size();
        printf("%d\n", witch_cnt);
        for (int i = 0; i < witch_cnt; ++i) {
            printf("%s\n", witch[i].c_str());
        }
        stack<int> box;
        int id = 1;
        for (int i = 0; i < buf_len; ++i) {
            if (buf[i] == '(') {
                continue;
            }
            if (isLowerLetter(buf[i]) && (i + 1 >= buf_len || !isLowerLetter(buf[i + 1]))) {
                if (box.size() > 0) {
                    printf("%d %d\n", box.top(), id);
                }
                box.push(id++);
            }
            if (buf[i] == ',' || buf[i] == ')') {
                int from = box.top();
                box.pop();
                int to = box.top();
                printf("%d %d\n", from, to);
            }
        }
        printf("\n");
    }
    return 0;
}
