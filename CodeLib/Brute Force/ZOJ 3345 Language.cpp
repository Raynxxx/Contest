/*
** ZOJ 3345 Language
** Created by Rayn @@ 2014/10/18
*/
#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const string Table[17][2] = {
		{ "Chinese", "[pn] shi [n]" },
		{ "Chinese", "[pn] [vi]" },
		{ "Chinese", "[pn] [vt] [n]" },
		{ "Chinese", "ni hao" },
		{ "English", "[pn] [vi]" },
		{ "English", "[pn] [vt] [n]" },
		{ "English", "There is a [n]" },
		{ "English", "Happy new year" },
		{ "Japanese", "[pn] ha [n] desu" },
		{ "Japanese", "[pn] ha [n] da" },
		{ "Japanese", "[pn] ha [n] ga [adj] desu" },
		{ "Japanese", "[n] saikou" },
		{ "Japanese", "yoi otoshiwo" },
		{ "German", "Ich habe ein [n]" },
		{ "German", "Ich bin [n]" },
		{ "German", "Ich heisse [n]" },
		{ "German", "Du hast [n]" },
};

const int TableSize = 17;
typedef pair<string, string> PSS;
typedef set<PSS> langInfo;
typedef map<string, langInfo> langBox;

int N, Q;
langBox box;

bool JudgeLanguage(int index, const string& sentence) {
	stringstream sent(sentence);
	stringstream catalog(Table[index][1]);
	langInfo& info = box[Table[index][0]];
	string t1, t2;
	while (true) {
		if (sent.eof() && catalog.eof()) return true;
		if (sent.eof() || catalog.eof()) return false;
		sent >> t1;
		catalog >> t2;
		if (t1 != t2 && info.find(make_pair(t1, t2)) == info.end()) {
			return false;
		}
	}
	return true;
}

int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	string buf;
	int T, cases = 0;
	cin >> T;
	while (T--) {
		cin >> N >> Q;
		box.clear();
		for (int i = 0; i < N; ++i) {
			string lang, catalog, pattern;
			cin >> lang >> catalog >> pattern;
			box[lang].insert(make_pair(pattern, catalog));
		}
		getline(cin, buf);
		cout << "Case #" << ++cases << ":" << endl;
		for (int i = 0; i < Q; ++i) {
			string sentence;
			getline(cin, sentence);
			bool ok = false;
			for (int id = 0; id < TableSize; ++id) {
				if (JudgeLanguage(id, sentence)) {
					ok = true;
					cout << Table[id][0] << endl;
					break;
				}
			}
			if (!ok) {
				cout << "I don't know." << endl;
			}
		}
	}
	return 0;
}
