// Priest John's Busiest Day
// UVa ID: 1420
// Verdict: Accepted
// Submission Date: 2025-12-17
// UVa Run Time: 0.060s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Wedding {
    long long start, endLimit, len;
};

bool compare(const Wedding& a, const Wedding& b) {
    return a.endLimit < b.endLimit;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n != 0) {
        vector<Wedding> weddings(n);
        for (int i = 0; i < n; ++i) {
            long long s, t;
            cin >> s >> t;
            long long len = (t - s) / 2 + 1; // 最短仪式时长
            weddings[i].start = s;
            weddings[i].endLimit = t - len; // 最晚开始时间
            weddings[i].len = len;
        }

        sort(weddings.begin(), weddings.end(), compare);

        long long currentTime = 0;
        bool possible = true;
        for (const auto& w : weddings) {
            long long startTime = max(currentTime, w.start);
            if (startTime > w.endLimit) {
                possible = false;
                break;
            }
            currentTime = startTime + w.len;
        }

        cout << (possible ? "YES" : "NO") << "\n";
    }
    return 0;
}
