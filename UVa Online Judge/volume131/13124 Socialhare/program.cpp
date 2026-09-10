// Socialhare
// UVa ID: 13124
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.780s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rowNum, colNum, wordNum;
    while (cin >> rowNum >> colNum >> wordNum) {
        vector<string> grid(rowNum);
        for (int i = 0; i < rowNum; ++i) cin >> grid[i];
        int answer = 0;
        int dr[4] = {0, 1, 1, 1};
        int dc[4] = {1, 0, 1, -1};
        for (int w = 0; w < wordNum; ++w) {
            string word;
            cin >> word;
            int len = (int)word.size();
            if (len > max(rowNum, colNum)) continue;
            array<int, 26> target{};
            for (char ch : word) target[ch - 'a']++;
            bool found = false;
            for (int i = 0; i < rowNum && !found; ++i) {
                for (int j = 0; j < colNum && !found; ++j) {
                    for (int d = 0; d < 4 && !found; ++d) {
                        int endR = i + (len - 1) * dr[d];
                        int endC = j + (len - 1) * dc[d];
                        if (endR < 0 || endR >= rowNum || endC < 0 || endC >= colNum) continue;
                        array<int, 26> cur{};
                        int r = i, c = j;
                        for (int k = 0; k < len; ++k) {
                            cur[grid[r][c] - 'a']++;
                            r += dr[d];
                            c += dc[d];
                        }
                        if (cur == target) found = true;
                    }
                }
            }
            if (found) answer++;
        }
        cout << answer << '\n';
    }
    return 0;
}
