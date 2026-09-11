// Unique Story
// UVa ID: 11775
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.250s

#include <bits/stdc++.h>
using namespace std;

const int MOD = 10000007;

void parseScenes(const string& s, vector<string>& scenes, vector<string>& allScenes) {
    int i = 0, n = s.size();
    while (i < n) {
        char ch = s[i++];
        string scene(1, ch);
        while (i < n && isdigit(s[i])) {
            scene.push_back(s[i++]);
        }
        scenes.push_back(scene);
        allScenes.push_back(scene);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        string s1, s2;
        cin >> s1 >> s2;

        vector<string> scenes1, scenes2, allScenes;
        parseScenes(s1, scenes1, allScenes);
        parseScenes(s2, scenes2, allScenes);

        sort(allScenes.begin(), allScenes.end());
        allScenes.erase(unique(allScenes.begin(), allScenes.end()), allScenes.end());
        unordered_map<string, int> idMap;
        for (int i = 0; i < (int)allScenes.size(); ++i) {
            idMap[allScenes[i]] = i + 1;
        }

        int n = scenes1.size();
        int m = scenes2.size();
        vector<int> A(n + 1), B(m + 1);
        for (int i = 0; i < n; ++i) A[i + 1] = idMap[scenes1[i]];
        for (int i = 0; i < m; ++i) B[i + 1] = idMap[scenes2[i]];

        int K = allScenes.size();

        vector<vector<int>> preA(n + 1, vector<int>(K + 1, 0));
        for (int i = 1; i <= n; ++i) {
            preA[i] = preA[i - 1];
            preA[i][A[i]] = i;
        }
        vector<vector<int>> preB(m + 1, vector<int>(K + 1, 0));
        for (int j = 1; j <= m; ++j) {
            preB[j] = preB[j - 1];
            preB[j][B[j]] = j;
        }

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i <= n; ++i) dp[i][0] = 1;
        for (int j = 0; j <= m; ++j) dp[0][j] = 1;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                long long val = (dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1]) % MOD;
                if (val < 0) val += MOD;
                if (A[i] == B[j]) {
                    int c = A[i];
                    int p = preA[i - 1][c];
                    int q = preB[j - 1][c];
                    if (p == 0 && q == 0) {
                        val = (val + dp[i - 1][j - 1]) % MOD;
                    } else if (p > 0 && q > 0) {
                        val = (val + dp[i - 1][j - 1] - dp[p - 1][q - 1]) % MOD;
                        if (val < 0) val += MOD;
                    }
                }
                dp[i][j] = (int)val;
            }
        }

        vector<int> pow2(max(n, m) + 1, 1);
        for (int i = 1; i <= max(n, m); ++i) pow2[i] = (pow2[i - 1] * 2) % MOD;

        int totalA = (pow2[n] - 1 + MOD) % MOD;
        int totalB = (pow2[m] - 1 + MOD) % MOD;
        int common = (dp[n][m] - 1 + MOD) % MOD;

        int ans = (totalA + totalB - 2LL * common) % MOD;
        if (ans < 0) ans += MOD;

        cout << "Case " << tc << ": " << ans << "\n";
    }
    return 0;
}
