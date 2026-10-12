// Many Paths One Destination
// UVa ID: 988
// Verdict: Accepted
// Submission Date: 2026-10-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int eventCount, i, j, choiceCount, nextCount;
    bool firstCase = true;
    while (cin >> eventCount) {
        vector<vector<int>> nextEvents(eventCount);
        for (i = 0; i < eventCount; ++i) {
            cin >> choiceCount;
            nextEvents[i].resize(choiceCount);
            for (j = 0; j < choiceCount; ++j) cin >> nextEvents[i][j];
        }
        vector<long long> pathCount(eventCount, 0);
        for (i = eventCount - 1; i >= 0; --i) {
            if (nextEvents[i].empty()) pathCount[i] = 1;
            else {
                nextCount = nextEvents[i].size();
                for (j = 0; j < nextCount; ++j) pathCount[i] += pathCount[nextEvents[i][j]];
            }
        }
        if (!firstCase) cout << '\n';
        cout << pathCount[0] << '\n';
        firstCase = false;
    }
    return 0;
}
