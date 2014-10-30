/*
** HDU 4964 Emmet
** Created by Rayn @@ 2014/08/28
*/
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;

string orgin;

string getHeader(const string& TagName, const string& TagId, const vector<string>& TagClass)
{
    string res = "<" + TagName;
    if(!TagId.empty()) {
        res += " id=\"" + TagId + "\"";
    }
    if(!TagClass.empty()) {
        res += " class=\"";
        for(int i = 0; i < (int) TagClass.size(); ++i) {
            if(i != 0)
                res += " ";
            res += TagClass[i];
        }
        res += "\"";
    }
    res += ">";
    return res;
}
string getTail(const string& TagName)
{
    return "</" + TagName + ">";
}
string Gao(int be, int ed)
{
    if(be >= ed)
        return "";

    string res, tmp, tag, id;
    vector<string> Class;
    int times = 1, l = be, r = be;
    if(orgin[be] == '(')
    {
        for(int p = 0; r < ed; r++)
        {
            if(orgin[r] == '(') {
                p++;
            } else if(orgin[r] == ')') {
                p--;
            }
            if(p == 0) {
                res = Gao(be+1, r) + Gao(r+1, ed);
                break;
            }
        }
        return res;
    }
    string body;
    while(r < ed)
    {
        if(orgin[r] == '>') {
            r++;
            if(r < ed) body = Gao(r, ed);
            break;
        } else if(!ispunct(orgin[r])) {
            while(!ispunct(orgin[r]) && r < ed) {
                tag += orgin[r++];
            }
        } else if(orgin[r] == '.') {
            r++;
            tmp.clear();
            while(!ispunct(orgin[r]) && r < ed) {
                tmp += orgin[r++];
            }
            Class.push_back(tmp);
        } else if(orgin[r] == '#') {
            r++;
            while(!ispunct(orgin[r]) && r < ed) {
                id += orgin[r++];
            }
        } else if(orgin[r] == '*') {
            r++;
            times = 0;
            while(isdigit(orgin[r]) && r < ed) {
                times = times * 10 + (orgin[r] - '0');
                r++;
            }
        }
    }
    if(!tag.empty()) {
        for(int i = 0; i < times; ++i) {
            res += getHeader(tag, id, Class);
            res += body;
            res += getTail(tag);
        }
    } else {
        res += body;
    }
    return res;
}
int main()
{
#ifdef _Rayn
    freopen("in.txt", "r", stdin);
#endif
    int T;
    scanf("%d", &T);
    while(T--)
    {
        cin >> orgin;
        cout << Gao(0, orgin.length()) << endl;
    }
    return 0;
}
