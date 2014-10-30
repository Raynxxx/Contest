/*
** HDU 4782 Beautiful Soup
** Created by Rayn @@ 2014/10/27
*/
#include <map>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long Long;

string tag;
vector<string> doc;

void ReadTag(string& tag, vector<string>& doc) {
	tag = "";
	char ch = getchar();
	while (true) {
		while (ch == ' ' || ch == '\n' || ch == '\t') {
			ch = getchar();
		}
		if (ch == '<') {
			tag += '<';
			while (ch != '>') {
				ch = getchar();
				tag += ch;
			}
			doc.push_back(tag);
			if (tag == "</html>") {
				break;
			}
			tag = "";
			ch = getchar();
		} else {
			while (ch != '<' && ch != ' ' && ch != '\n' && ch != '\t') {
				tag += ch;
				ch = getchar();
			}
			doc.push_back(tag);
			tag = "";
		}
	}
}
void PutTag(int sz, const string& cur, bool enter) {
	for (int i = 0; i < sz; ++i) {
		putchar(' ');
	}
	printf("%s", cur.c_str());
	if (enter) putchar('\n');
}
void Debug(const vector<string>& doc) {
	for (int i = 0; i < (int)doc.size(); ++i) {
		cout << doc[i] << endl;
	}
}
void BeautyfulSoup(const vector<string>& doc) {
	bool firstText = true;
	int blankCnt = 0;
	for (int i = 0; i < (int) doc.size(); ++i) {
		string cur = doc[i];
		if (cur[0] == '<') {
			firstText = true;
			if (cur[1] != '/') {
				PutTag(blankCnt, cur, true);
				int len = cur.length();
				if (cur[len - 2] != '/') {
					blankCnt++;
				}
			} else {
				blankCnt--;
				PutTag(blankCnt, cur, true);
			}
		} else {
			if (firstText) {
				PutTag(blankCnt, cur, false);
				firstText = false;
			} else {
				PutTag(1, cur, false);
			}
			string next = doc[i + 1];
			if (next[0] == '<') {
				putchar('\n');
			}
		}
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int T, cases = 0;
	scanf("%d", &T);
	while (T--) {
		ReadTag(tag, doc);
		//Debug(doc);
		printf("Case #%d:\n", ++cases);
		BeautyfulSoup(doc);
	}
	return 0;
}