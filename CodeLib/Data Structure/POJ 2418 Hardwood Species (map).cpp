/*
** POJ 2418 Hardwood Species
** Created by Rayn @@ 2014/04/30
** 用map水看看
*/
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    string str;
    int cnt = 0;
    map<string, int> tree;
    while(getline(cin, str))
    {
        tree[str]++;
        cnt++;
    }
    map<string, int>::iterator i;
    for(i = tree.begin(); i != tree.end(); ++i)
    {
        cout << i->first;
        printf(" %.4f\n",(i->second*100.0) / cnt);
    }
    return 0;
}
