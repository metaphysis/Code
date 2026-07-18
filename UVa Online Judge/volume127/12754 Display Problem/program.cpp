// Display Problem
// UVa ID: 12754
// Verdict: Accepted
// Submission Date: 2026-07-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    cin.ignore(64, '\n');
    string line;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ": ";
        vector<string> grid;
        while (getline(cin, line)) {
            if (line.front() == '*') break;
            grid.push_back(line);
        }
        bool ok = true;
        int R = (int)grid.size();
        int D = R - 3;
        if (D < 0 || D % 2 == 1) ok = false;
        D /= 2;
        for (const auto& row : grid) {
            if ((int)row.size() != D + 2) {
                ok = false;
                break;
            }
        }
        auto checkDashRow = [&](int idx) -> bool {
            const string& s = grid[idx];
            if (s[0] != '.' || s[D + 1] != '.') return false;
            for (int j = 1; j <= D; j++) {
                if (s[j] != '-') return false;
            }
            return true;
        };
        auto checkPipeRow = [&](int idx) -> bool {
            const string& s = grid[idx];
            if (s[0] != '|' || s[D + 1] != '|') return false;
            for (int j = 1; j <= D; j++) {
                if (s[j] != '.') return false;
            }
            return true;
        };
        if (ok) {
            if (!checkDashRow(0) || !checkDashRow(D + 1) || !checkDashRow(R - 1))
                ok = false;
        }
        if (ok) {
            for (int i = 0; i < R; i++) {
                if (i == 0 || i == D + 1 || i == R - 1) continue;
                if (!checkPipeRow(i)) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) cout << D;
        else cout << "Bad";
        cout << '\n';
    }
    return 0;
}
