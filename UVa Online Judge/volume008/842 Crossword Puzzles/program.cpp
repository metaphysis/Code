// Crossword Puzzles
// UVa ID: 842
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

struct Constraint {
    int other;
    int posS;
    int posOther;
};

long long solveCase(const vector<string>& grid, const vector<string>& dict) {
    int hId[10][10], vId[10][10], hPos[10][10], vPos[10][10];
    memset(hId, -1, sizeof(hId));
    memset(vId, -1, sizeof(vId));
    memset(hPos, -1, sizeof(hPos));
    memset(vPos, -1, sizeof(vPos));

    vector<int> segLen;
    vector<vector<Constraint>> cons;

    // 水平段
    int segId = 0;
    for (int r = 0; r < 10; ++r) {
        int c = 0;
        while (c < 10) {
            if (grid[r][c] == '#') { ++c; continue; }
            int start = c;
            while (c < 10 && grid[r][c] == '.') ++c;
            int len = c - start;
            int id = segId++;
            segLen.push_back(len);
            for (int k = 0; k < len; ++k) {
                int col = start + k;
                hId[r][col] = id;
                hPos[r][col] = k;
            }
        }
    }

    // 垂直段
    for (int c = 0; c < 10; ++c) {
        int r = 0;
        while (r < 10) {
            if (grid[r][c] == '#') { ++r; continue; }
            int start = r;
            while (r < 10 && grid[r][c] == '.') ++r;
            int len = r - start;
            int id = segId++;
            segLen.push_back(len);
            for (int k = 0; k < len; ++k) {
                int row = start + k;
                vId[row][c] = id;
                vPos[row][c] = k;
            }
        }
    }

    int M = segId;
    cons.assign(M, {});

    // 建立交叉约束
    for (int r = 0; r < 10; ++r)
        for (int c = 0; c < 10; ++c) {
            if (grid[r][c] == '.') {
                int h = hId[r][c], v = vId[r][c];
                int ph = hPos[r][c], pv = vPos[r][c];
                cons[h].push_back({v, ph, pv});
                cons[v].push_back({h, pv, ph});
            }
        }

    // 字典按长度索引
    unordered_map<int, vector<string>> byLen;
    unordered_set<string> dictSet(dict.begin(), dict.end());
    for (const string& w : dictSet)
        if (w.size() >= 2) byLen[w.size()].push_back(w);

    // 候选列表
    vector<vector<string>> cand(M);
    for (int i = 0; i < M; ++i) {
        int len = segLen[i];
        if (len >= 2) {
            auto it = byLen.find(len);
            if (it != byLen.end()) cand[i] = it->second;
        } else {
            cand[i].resize(26);
            for (char ch = 'a'; ch <= 'z'; ++ch)
                cand[i][ch - 'a'] = string(1, ch);
        }
    }

    vector<bool> assigned(M, false);
    vector<string> assignment(M);
    long long ans = 0;

    auto propagate = [&](int startId) -> bool {
        queue<int> q;
        q.push(startId);
        while (!q.empty()) {
            int id = q.front(); q.pop();
            if (!assigned[id]) continue;
            string& word = assignment[id];
            for (const Constraint& con : cons[id]) {
                int other = con.other;
                int posS = con.posS;
                int posOther = con.posOther;
                char c = word[posS];
                if (assigned[other]) {
                    if (assignment[other][posOther] != c) return false;
                } else {
                    vector<string> newCand;
                    for (const string& w : cand[other])
                        if (w[posOther] == c) newCand.push_back(w);
                    if (newCand.empty()) return false;
                    if (newCand.size() == cand[other].size()) continue;
                    cand[other] = move(newCand);
                    if (cand[other].size() == 1) {
                        assignment[other] = cand[other][0];
                        assigned[other] = true;
                        q.push(other);
                    }
                }
            }
        }
        return true;
    };

    function<void()> dfs = [&]() {
        bool allAssigned = true;
        int sel = -1, minCand = INT_MAX;
        for (int i = 0; i < M; ++i) {
            if (!assigned[i]) {
                allAssigned = false;
                int sz = cand[i].size();
                if (sz < minCand) {
                    minCand = sz;
                    sel = i;
                    if (minCand == 0) break;
                }
            }
        }
        if (allAssigned) { ++ans; return; }
        if (sel == -1 || minCand == 0) return;

        vector<vector<string>> backupCand = cand;
        vector<bool> backupAssigned = assigned;
        vector<string> backupAssignment = assignment;

        for (const string& word : cand[sel]) {
            cand = backupCand;
            assigned = backupAssigned;
            assignment = backupAssignment;
            assignment[sel] = word;
            assigned[sel] = true;
            if (propagate(sel)) dfs();
        }

        cand = backupCand;
        assigned = backupAssigned;
        assignment = backupAssignment;
    };

    dfs();
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> tokens;
    string token;
    while (cin >> token) tokens.push_back(token);
    if (tokens.empty()) return 0;

    int T = stoi(tokens[0]);
    int idx = 1;

    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        vector<string> grid(10);
        for (int i = 0; i < 10; ++i)
            grid[i] = tokens[idx++];

        vector<string> dict;
        while (idx < (int)tokens.size()) {
            string w = tokens[idx];
            if (w[0] == '#' || w[0] == '.') break;
            dict.push_back(w);
            ++idx;
        }

        long long ans = solveCase(grid, dict);
        cout << ans << '\n';
        if (caseNo < T) cout << '\n';
    }

    return 0;
}
