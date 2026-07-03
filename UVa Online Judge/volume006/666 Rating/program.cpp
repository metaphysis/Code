// Rating
// UVa ID: 666
// Verdict: Accepted
// Submission Date: 2026-07-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int place1[110], place2[110];

bool isBetter(int a, int b) {
    int a1 = place1[a], a2 = place2[a];
    int b1 = place1[b], b2 = place2[b];
    if (a1 <= b1 && a2 <= b2 && (a1 < b1 || a2 < b2)) return true;
    if (b1 <= a1 && b2 <= a2 && (b1 < a1 || b2 < a2)) return false;
    int diff1 = b1 - a1, diff2 = b2 - a2;
    return diff1 + diff2 > 0;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int M;
    cin >> M;
    for (int ds = 0; ds < M; ++ds) {
        memset(place1, 0, sizeof place1);
        memset(place2, 0, sizeof place2);
        int N1; cin >> N1; cin.ignore(128, '\n');
        int total = 0;
        for (int i = 0; i < N1; ++i) {
            string line; getline(cin, line);
            stringstream ss(line);
            int id;
            int p = total + 1;
            while (ss >> id) { place1[id] = p; ++total; }
        }
        int N2; cin >> N2; cin.ignore(128, '\n');
        total = 0;
        for (int i = 0; i < N2; ++i) {
            string line; getline(cin, line);
            stringstream ss(line);
            int id;
            int p = total + 1;
            while (ss >> id) { place2[id] = p; ++total; }
        }
        vector<int> twoTeams;
        for (int id = 1; id <= 100; id++)
            if (place1[id] && place2[id])
                twoTeams.push_back(id);
        sort(twoTeams.begin(), twoTeams.end(), isBetter);
        vector<vector<int>> rows;
        for (int i = 0; i < (int)twoTeams.size();) {
            vector<int> row;
            row.push_back(twoTeams[i]);
            int j = i + 1;
            while (j < (int)twoTeams.size() &&
                   !isBetter(twoTeams[i], twoTeams[j]) &&
                   !isBetter(twoTeams[j], twoTeams[i])) {
                row.push_back(twoTeams[j]);
                ++j;
            }
            rows.push_back(row);
            i = j;
        }
        map<int, vector<int>> posTeams; // 位置 -> 待插入队伍
        for (int id = 1; id <= 100; id++) {
            if (place1[id] && place2[id]) continue;
            if (!place1[id] && !place2[id]) continue;
            int c = (place1[id] ? 1 : 2);
            int p = (c == 1 ? place1[id] : place2[id]);
            // 规则 A
            vector<int> matched;
            for (int t : twoTeams) {
                if (c == 1 && place1[t] == p) matched.push_back(t);
                else if (c == 2 && place2[t] == p) matched.push_back(t);
            }
            if (!matched.empty()) {
                int rowIdx = -1;
                bool ok = true;
                for (int t : matched) {
                    int idx = -1;
                    for (int i = 0; i < (int)rows.size(); ++i) {
                        if (find(rows[i].begin(), rows[i].end(), t) != rows[i].end()) {
                            idx = i; break;
                        }
                    }
                    if (idx == -1) { ok = false; break; }
                    if (rowIdx == -1) rowIdx = idx;
                    else if (rowIdx != idx) { ok = false; break; }
                }
                // 能唯一确定则添加
                if (ok) rows[rowIdx].push_back(id);
                // 不能唯一确定则不列出
                continue;
            }
            // 规则 B
            int R = rows.size();
            vector<int> validPos;
            for (int k = 0; k <= R; ++k) {
                bool valid = true;
                for (int i = 0; i < k; ++i) {
                    for (int t : rows[i]) {
                        int pt = (c == 1 ? place1[t] : place2[t]);
                        if (pt && pt >= p) { valid = false; break; }
                    }
                    if (!valid) break;
                }
                if (!valid) continue;
                for (int i = k; i < R; ++i) {
                    for (int t : rows[i]) {
                        int pt = (c == 1 ? place1[t] : place2[t]);
                        if (pt && pt <= p) { valid = false; break; }
                    }
                    if (!valid) break;
                }
                if (valid) validPos.push_back(k);
            }
            if (validPos.size() == 1) posTeams[validPos[0]].push_back(id);
        }
        // 插入规则 B 产生的行
        vector<int> keys;
        for (auto &kv : posTeams) keys.push_back(kv.first);
        sort(keys.begin(), keys.end(), greater<int>());
        for (int pos : keys) {
            vector<int> &v = posTeams[pos];
            sort(v.begin(), v.end(), [&](int a, int b) {
                int pa = (place1[a] ? place1[a] : place2[a]);
                int pb = (place1[b] ? place1[b] : place2[b]);
                return pa < pb;
            });
            vector<vector<int>> groups;
            for (int i = 0; i < (int)v.size();) {
                int j = i + 1;
                int pa = (place1[v[i]] ? place1[v[i]] : place2[v[i]]);
                while (j < (int)v.size() &&
                       (place1[v[j]] ? place1[v[j]] : place2[v[j]]) == pa) ++j;
                vector<int> group(v.begin() + i, v.begin() + j);
                groups.push_back(group);
                i = j;
            }
            for (int g = (int)groups.size() - 1; g >= 0; --g)
                rows.insert(rows.begin() + pos, groups[g]);
        }
        // 输出
        for (int i = 0; i < rows.size(); ++i) {
            for (int j = 0; j < rows[i].size(); ++j) {
                if (j) cout << ' ';
                cout << rows[i][j];
            }
            cout << '\n';
        }
        if (ds != M - 1) cout << '\n';
    }
    return 0;
}
