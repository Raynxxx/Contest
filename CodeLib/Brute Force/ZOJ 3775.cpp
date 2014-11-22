/*
** ZOJ 3775 ?(>_o)!
** Created by Rayn @@ 2014/05/10
** Ä£Äâ
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

bool Check(string& s)
{
    string tmp = "";
    for(int i=0; i<s.length(); ++i)
    {
        if(s[i] == '_')
            tmp += s;
        else if(s[i] == '!')
            tmp += "Hello, world!";
        if(tmp.length() > s.length())
            return false;
    }
    return s == tmp;
}
int main()
{
    int t;
    string str;

    scanf("%d%*c", &t);
    while(t--)
    {
        getline(cin, str);
        if(Check(str))
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
