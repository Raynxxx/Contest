/*
** UVA 10905 Children's Game
** Created by Rayn @@ 2014/04/24
** 用string和排序水过了
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string num[55];

bool cmp(const string &a, const string &b)
{
    return (a+b > b+a);
}
int main()
{
    int N;

    while(cin>>N && N)
    {
        for(int i=0; i<N; ++i)
            cin>>num[i];

        sort(num, num+N, cmp);

        for(int i=0; i<N; ++i)
        {
            cout<<num[i];
        }
        cout<<endl;
    }
    return 0;
}
