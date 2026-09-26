#include <bits/stdc++.h>
using namespace std;

vector<int> buildAnswers(int maxN, int m) {
    vector<int> val(maxN + 1, 0);
    int x, b, a, r, maxA, idx, upper, bestA, bestB;
    for (x = 1; x <= maxN; x++) {
        vector<vector<array<int, 2>>> dp(x + 1, vector<array<int, 2>>(x + 1));
        vector<deque<int>> colMin(x + 1);
        for (b = x - 1; b >= 0; b--) {
            deque<int> rowMax;
            maxA = x - b - 1;
            for (a = maxA; a >= 0; a--) {
                r = x - a - b;
                idx = a + 1;
                if (idx <= maxA) {
                    while (!rowMax.empty() && dp[rowMax.back()][b][1] <= dp[idx][b][1]) rowMax.pop_back();
                    rowMax.push_back(idx);
                }
                upper = a + m;
                while (!rowMax.empty() && rowMax.front() > upper) rowMax.pop_front();
                bestA = -1000000000;
                if (!rowMax.empty()) bestA = dp[rowMax.front()][b][1];
                if (r <= m) bestA = max(bestA, x - val[b]);
                dp[a][b][0] = bestA;
                idx = b + 1;
                if (idx <= x - a - 1) {
                    while (!colMin[a].empty() && dp[a][colMin[a].back()][0] >= dp[a][idx][0]) colMin[a].pop_back();
                    colMin[a].push_back(idx);
                }
                upper = b + m;
                while (!colMin[a].empty() && colMin[a].front() > upper) colMin[a].pop_front();
                bestB = 1000000000;
                if (!colMin[a].empty()) bestB = dp[a][colMin[a].front()][0];
                if (r <= m) bestB = min(bestB, val[a]);
                dp[a][b][1] = bestB;
            }
        }
        val[x] = dp[0][0][0];
    }
    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pair<int, int>> tests;
    vector<int> maxNByM(101, 0);
    vector<vector<int>> answers(101);
    int n, m, k;
    size_t i;
    while (cin >> n >> m) {
        tests.push_back({n, m});
        maxNByM[m] = max(maxNByM[m], n);
    }
    for (k = 1; k <= 100; k++)
        if (maxNByM[k] > 0) answers[k] = buildAnswers(maxNByM[k], k);
    for (i = 0; i < tests.size(); i++) cout << answers[tests[i].second][tests[i].first] << '\n';
    return 0;
}
