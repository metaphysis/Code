// Timetable
// UVa ID: 1725
// Verdict: Accepted
// Submission Date: 2026-09-19
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;

struct Train {
	int dep, arr, to, dp, suf;
};

int parseTime(const string &s) {
	return ((s[0] - '0') * 10 + s[1] - '0') * 60 + (s[3] - '0') * 10 + s[4] - '0';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	while (cin >> n) {
		vector<vector<Train>> timetables(n + 1);
		vector<vector<pair<int, int>>> buckets(1440);
		for (int city = 1; city <= n; city++) {
			int m;
			cin >> m;
			timetables[city].reserve(m);
			for (int i = 0; i < m; i++) {
				string depStr, arrStr;
				int to, dep, arr;
				cin >> depStr >> arrStr >> to;
				dep = parseTime(depStr);
				arr = parseTime(arrStr);
				timetables[city].push_back({dep, arr, to, inf, inf});
				buckets[dep].push_back({city, i});
			}
		}
		for (int tm = 1439; tm >= 0; tm--) {
			for (const pair<int, int> &pos : buckets[tm]) {
				int city = pos.first, idx = pos.second;
				Train &tr = timetables[city][idx];
				if (tr.to == n) tr.dp = tr.arr;
				if (tr.to != n) {
					const vector<Train> &nextTrains = timetables[tr.to];
					auto it = lower_bound(nextTrains.begin(), nextTrains.end(), tr.arr, [](const Train &cur, int needTime) {
						return cur.dep < needTime;
					});
					if (it != nextTrains.end()) tr.dp = it->suf;
				}
			}
			for (auto it = buckets[tm].rbegin(); it != buckets[tm].rend(); it++) {
				int city = it->first, idx = it->second, nextSuf = inf;
				vector<Train> &cityTrains = timetables[city];
				if (idx + 1 < (int)cityTrains.size()) nextSuf = cityTrains[idx + 1].suf;
				cityTrains[idx].suf = min(cityTrains[idx].dp, nextSuf);
			}
		}
		vector<int> minArr(1440, inf);
		for (const Train &tr : timetables[1]) minArr[tr.dep] = min(minArr[tr.dep], tr.dp);
		vector<pair<int, int>> ans;
		int bestArr = inf;
		for (int dep = 1439; dep >= 0; dep--) {
			if (minArr[dep] < bestArr) {
				ans.push_back({dep, minArr[dep]});
				bestArr = minArr[dep];
			}
		}
		reverse(ans.begin(), ans.end());
		cout << ans.size() << '\n';
		cout << setfill('0');
		for (const pair<int, int> &item : ans) cout << setw(2) << item.first / 60 << ':' << setw(2) << item.first % 60 << ' ' << setw(2) << item.second / 60 << ':' << setw(2) << item.second % 60 << '\n';
	}
	return 0;
}
