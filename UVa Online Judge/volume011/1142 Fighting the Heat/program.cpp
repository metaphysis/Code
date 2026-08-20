// Fighting the Heat
// UVa ID: 1142
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.110s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rows, cols;
    while (cin >> rows >> cols) {
        int wordCount;
        cin >> wordCount;
        vector<string> words(wordCount);
        for (int i = 0; i < wordCount; ++i) cin >> words[i];
        vector<string> grid(rows);
        for (int i = 0; i < rows; ++i) cin >> grid[i];
        vector<vector<bool>> highlighted(rows, vector<bool>(cols, false));
        int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        for (const string& word : words) {
            int wordLen = (int)word.size();
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    for (int d = 0; d < 8; ++d) {
                        int endR = r + dr[d] * (wordLen - 1);
                        int endC = c + dc[d] * (wordLen - 1);
                        if (endR < 0 || endR >= rows || endC < 0 || endC >= cols) continue;
                        bool match = true;
                        for (int t = 0; t < wordLen; ++t) {
                            int nr = r + dr[d] * t;
                            int nc = c + dc[d] * t;
                            if (grid[nr][nc] != word[t]) {
                                match = false;
                                break;
                            }
                        }
                        if (match) {
                            for (int t = 0; t < wordLen; ++t) {
                                int nr = r + dr[d] * t;
                                int nc = c + dc[d] * t;
                                highlighted[nr][nc] = true;
                            }
                        }
                    }
                }
            }
        }
        string answer;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (!highlighted[r][c]) answer.push_back(grid[r][c]);
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
