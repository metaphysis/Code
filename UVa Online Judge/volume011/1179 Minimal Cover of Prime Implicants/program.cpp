#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, p, caseId = 0;
    while (cin >> n >> m >> p) {
        if (n == 0 && m == 0 && p == 0) break;
        vector<string> mt(m), pi(p);
        for (int i = 0; i < m; ++i) cin >> mt[i];
        for (int i = 0; i < p; ++i) cin >> pi[i];
        vector<vector<int>> cover(p, vector<int>(m, 0));
        vector<int> cost(p, 0), covered(m, 0);
        for (int i = 0; i < p; ++i) {
            for (int k = 0; k < n; ++k) if (pi[i][k] != '-') ++cost[i];
            for (int j = 0; j < m; ++j) {
                bool match = true;
                for (int k = 0; k < n; ++k) {
                    if (pi[i][k] != '-' && pi[i][k] != mt[j][k]) {
                        match = false;
                        break;
                    }
                }
                cover[i][j] = match;
            }
        }
        int remaining = m, answer = 0;
        while (remaining > 0) {
            int bestId = -1, bestCount = 0;
            for (int i = 0; i < p; ++i) {
                int count = 0;
                for (int j = 0; j < m; ++j) if (!covered[j] && cover[i][j]) ++count;
                if (count == 0) continue;
                if (bestId == -1 || count > bestCount || (count == bestCount && cost[i] < cost[bestId])) {
                    bestId = i;
                    bestCount = count;
                }
            }
            if (bestId == -1) break;
            ++answer;
            for (int j = 0; j < m; ++j) {
                if (!covered[j] && cover[bestId][j]) {
                    covered[j] = 1;
                    --remaining;
                }
            }
        }
        cout << "Test #" << ++caseId << ": ";
        if (remaining == 0) cout << "No of required PIs = " << answer << '\n';
        else cout << "PIs don't cover all MTs\n";
    }
    return 0;
}
