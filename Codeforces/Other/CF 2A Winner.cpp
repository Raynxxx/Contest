/*
** CodeForces 2A Winner
** Created by Rayn @@ 2014/05/19
*/
#include <iostream>
#include <cstdio>
#include <map>
#include <string>
using namespace std;
const int MAX = 1010;
const int INF = 100000000;

map <string, int> play, game;
string name[MAX];
int score[MAX];

int main()
{
#ifdef _Rayn
	//freopen("in.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> name[i] >> score[i];
		play[name[i]] += score[i];
	}
	int M = 0;
	for (int i = 0; i < n; ++i)
	{
		if (play[name[i]] > M)
			M = play[name[i]];
	}
	int i;
	for (i = 0; ; ++i)
	{
		if (play[name[i]] >= M && (game[name[i]] += score[i]) >= M)
			break;
	}
	cout << name[i] << endl;

	return 0;
}