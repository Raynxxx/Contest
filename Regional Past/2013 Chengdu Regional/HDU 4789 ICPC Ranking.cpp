/*
** HDU 4789 ICPC Ranking
** Created by Rayn @@ 2014/10/28
*/
#include <map>
#include <set>
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long Long;
typedef map<string, int> Hash;
const int MAXN = 50010;
const int MAXM = 26;

int n, m, TotalTime, ForzenTime;

class Team {
public:
	string name;
	int solved;
	int penalty;
	int AC_Time[MAXM];
	int NO_Count[MAXM];
	int LastSolved[MAXM];
	int SubmitForzen[MAXM];
	int SubmitFinal[MAXM];
	bool AC_Forzen[MAXM];
	bool AC_Final[MAXM];
	vector<int> submit;

	void Init(string& s) {
		name = s;
		solved = penalty = 0;
		fill_n(LastSolved, m, 0);
		fill_n(NO_Count, m, 0);
		fill_n(SubmitForzen, m, 0);
		fill_n(SubmitFinal, m, 0);
		fill_n(AC_Forzen, m, false);
		fill_n(AC_Final, m, false);
		submit.clear();
	}
	bool operator < (const Team& b) const {
		if (solved != b.solved) return solved > b.solved;
		if (penalty != b.penalty) return penalty < b.penalty;
		for (int i = solved - 1; i >= 0; --i) {
			if (LastSolved[i] != b.LastSolved[i]) {
				return LastSolved[i] < b.LastSolved[i];
			}
		}
		return name > b.name;
	}
	void Pending(int id, int time, int status) {
		if (AC_Forzen[id]) return;
		if (AC_Final[id]) {
			if (time >= ForzenTime) {
				++SubmitFinal[id];
			}
			return;
		}
		if (status == 0) {
			if (time < ForzenTime) {
				AC_Forzen[id] = true;
				AC_Time[id] = time;
				penalty += AC_Time[id] + NO_Count[id] * 20;
				int j = solved++;
				LastSolved[j] = time;
				while (j > 0 && LastSolved[j] < LastSolved[j - 1]) {
					swap(LastSolved[j], LastSolved[j - 1]);
					--j;
				}
			} else {
				AC_Final[id] = true;
				AC_Time[id] = time;
				++SubmitFinal[id];
			}
		} else if (status == 1) {
			++NO_Count[id];
			if (time < ForzenTime) {
				++SubmitForzen[id];
			} else {
				++SubmitFinal[id];
			}
		} else {
			if (time < ForzenTime) return;
			++SubmitFinal[id];
		}
	}
	void Relax() {
		int id = submit.back();
		if (AC_Final[id]) {
			penalty += AC_Time[id] + NO_Count[id] * 20;
			int j = solved++;
			LastSolved[j] = AC_Time[id];
			while (j > 0 && LastSolved[j] < LastSolved[j - 1]) {
				swap(LastSolved[j], LastSolved[j - 1]);
				--j;
			}
		}
		submit.pop_back();
	}
	void Forzen() {
		for (int i = m - 1; i >= 0; --i) {
			if (SubmitFinal[i]) {
				submit.push_back(i);
			}
		}
	}
};

struct Submit {
	int TeamId, ProblemId, Time;
	int status;
	Submit() {}
	Submit(int tid, int pid, int t, int s) : TeamId(tid), ProblemId(pid), Time(t), status(s) {}
	bool operator < (const Submit& b) const {
		return Time < b.Time || (Time == b.Time && status > b.status);
	}
};

Team team[MAXN];
Submit pend[MAXN];
Hash TeamName;
int TeamCnt;

struct Index {
	int id;
	Index(){}
	Index(int id) :id(id) {}
	bool operator < (const Index &b) const {
		return team[id] < team[b.id];
	}
};

Index idx[MAXN];
set<Index> box;

int GetStatus(char *ret) {
	if (ret[0] == 'Y') return 0;
	else if (ret[0] == 'N') return 1;
	else return 2;
}
void Forzen() {
	box.clear();
	for (int i = 1; i <= TeamCnt; ++i) {
		box.insert(Index(i));
	}
	int Rank = 0;
	for (set<Index>::iterator it = box.begin(); it != box.end(); ++it) {
		Team& cur = team[it->id];
		printf("%s %d %d %d", cur.name.c_str(), ++Rank, cur.solved, cur.penalty);
		for (int i = 0; i < m; ++i) {
			if (cur.AC_Forzen[i]) {
				printf(" +");
				if (cur.NO_Count[i] != 0) {
					printf("%d", cur.NO_Count[i]);
				}
			} else if (cur.SubmitFinal[i]) {
				if (cur.SubmitForzen[i] == 0) {
					printf(" 0/%d", cur.SubmitFinal[i]);
				} else {
					printf(" -%d/%d", cur.SubmitForzen[i], cur.SubmitFinal[i]);
				}
			} else if (cur.SubmitForzen[i]) {
				printf(" -%d", cur.SubmitForzen[i]);
			} else {
				printf(" .");
			}
		}
		putchar('\n');
	}
}
void Process() {
	for (int i = 1; i <= TeamCnt; ++i) {
		team[i].Forzen();
	}
	while (!box.empty()) {
		set<Index>::iterator it = box.end();
		--it;
		Team& cur = team[it->id];
		Index next = Index(it->id);
		box.erase(it);
		if (cur.submit.empty()) continue;
		cur.Relax();
		set<Index>::iterator pit = box.upper_bound(next);
		if (pit != box.end()) {
			printf("%s %s %d %d\n", cur.name.c_str(), team[pit->id].name.c_str(), cur.solved, cur.penalty);
		}
		box.insert(pit, next);
	}
}
void Final() {
	for (int i = 1; i <= TeamCnt; ++i) {
		idx[i].id = i;
	}
	sort(idx + 1, idx + 1 + TeamCnt);
	for (int i = 1; i <= TeamCnt; ++i) {
		Team& cur = team[idx[i].id];
		printf("%s %d %d %d", cur.name.c_str(), i, cur.solved, cur.penalty);
		for (int j = 0; j < m; ++j) {
			if (cur.AC_Forzen[j] || cur.AC_Final[j]) {
				printf(" +");
				if (cur.NO_Count[j] != 0) {
					printf("%d", cur.NO_Count[j]);
				}
			} else if (cur.NO_Count[j] != 0) {
				printf(" -%d", cur.NO_Count[j]);
			} else {
				printf(" .");
			}
		}
		putchar('\n');
	}
}
int main() {
#ifdef _Rayn
	freopen("in.txt", "r", stdin);
#endif
	int C, cases = 0;
	scanf("%d", &C);
	while (C--) {
		TeamName.clear();
		TeamCnt = 0;
		scanf("%d%d%d%d", &n, &m, &TotalTime, &ForzenTime);
		char name[25], problem[25], result[25];
		for (int i = 0; i < n; ++i) {
			int time;
			scanf("%s%s%d%s", name, problem, &time, result);
			string t(name);
			if (!TeamName.count(t)) {
				TeamName[t] = ++TeamCnt;
				team[TeamCnt].Init(t);
			}
			int status = GetStatus(result);
			pend[i] = Submit(TeamName[t], problem[0] - 'A', time, status);
		}
		sort(pend, pend + n);
		for (int i = 0; i < n; ++i) {
			int tid = pend[i].TeamId;
			int pid = pend[i].ProblemId;
			team[tid].Pending(pid, pend[i].Time, pend[i].status);
		}
		printf("Case #%d:\n", ++cases);
		Forzen();
		Process();
		Final();
	}
	return 0;
}
