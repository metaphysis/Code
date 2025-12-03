// Stacking Plates
// UVa ID: 1289
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MaxN = 50;
const int MaxH = 50;

int main() {
    int n, caseId = 1;
    while (cin >> n) {
        vector<pair<int, int>> plates;
        int totPlates = 0;
        for (int i = 1; i <= n; i++) {
            int h;
            cin >> h;
            for (int j = 0; j < h; j++) {
                int sizeVal;
                cin >> sizeVal;
                plates.push_back({sizeVal, i});
                totPlates++;
            }
        }
        sort(plates.begin(), plates.end());
        int c = unique(plates.begin(), plates.end()) - plates.begin();
        vector<vector<bool>> hasPlate;
        vector<int> cnt;
        int typeCnt = 0;
        for (int i = 0; i < c; i++) {
            int start = i;
            while (i + 1 < c && plates[i + 1].first == plates[i].first) i++;
            hasPlate.push_back(vector<bool>(n + 1, false));
            cnt.push_back(i - start + 1);
            for (int j = start; j <= i; j++)
                hasPlate[typeCnt][plates[j].second] = true;
            typeCnt++;
        }
        vector<vector<int>> dp(typeCnt + 1, vector<int>(n + 1, INF));
        for (int j = 1; j <= n; j++)
            if (hasPlate[0][j]) dp[1][j] = cnt[0];
        for (int i = 1; i < typeCnt; i++)
            for (int j = 1; j <= n; j++)
                if (hasPlate[i][j])
                    for (int k = 1; k <= n; k++)
                        if (dp[i][k] != INF)
                            if (hasPlate[i][k] && (cnt[i] == 1 || k != j))
                                dp[i + 1][j] = min(dp[i + 1][j], dp[i][k] + cnt[i] - 1);
                            else dp[i + 1][j] = min(dp[i + 1][j], dp[i][k] + cnt[i]);
        int minCost = INF;
        for (int j = 1; j <= n; j++)
            minCost = min(minCost, dp[typeCnt][j]);
        int result = 2 * minCost - n - 1;
        cout << "Case " << caseId++ << ": " << result << endl;
    }
    return 0;
}
