// Klingon Levels
// UVa ID: 12196
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.150s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N && N != 0) {
        vector<vector<int>> prefs;          // 每个班级的前缀计数数组
        prefs.reserve(N);

        for (int i = 0; i < N; ++i) {
            int K;
            cin >> K;
            vector<int> cnt(1001, 0);       // 分数 0..1000
            for (int j = 0; j < K; ++j) {
                int score;
                cin >> score;
                ++cnt[score];
            }

            vector<int> pref(1002, 0);      // pref[t] = 分数 < t 的人数
            for (int s = 0; s <= 1000; ++s)
                pref[s + 1] = pref[s] + cnt[s];

            prefs.push_back(move(pref));
        }

        int best = INT_MAX;
        for (int T = 0; T <= 1001; ++T) {
            int sum = 0;
            for (const auto& pref : prefs) {
                int basic = pref[T];                // 分数 < T 的人数
                int total = pref[1001];             // 班级总人数
                int diff = abs(2 * basic - total);
                sum += diff;
            }
            if (sum < best) best = sum;
        }

        cout << best << '\n';
    }

    return 0;
}
