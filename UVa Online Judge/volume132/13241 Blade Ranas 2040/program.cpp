#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testNum;
    cin >> testNum;
    while (testNum--) {
        int rows, cols;
        cin >> rows >> cols;
        vector<string> grid(rows);
        for (int i = 0; i < rows; i++) cin >> grid[i];
        vector<vector<int>> sum(rows, vector<int>(cols, 0));
        vector<vector<int>> val(rows, vector<int>(cols, 0));
        int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        for (int d = 0; d < 8; d++) {
            int rBeg = dr[d] == 1 ? rows - 1 : 0, rEnd = dr[d] == 1 ? -1 : rows, rStep = dr[d] == 1 ? -1 : 1;
            int cBeg = dc[d] == 1 ? cols - 1 : 0, cEnd = dc[d] == 1 ? -1 : cols, cStep = dc[d] == 1 ? -1 : 1;
            for (int r = rBeg; r != rEnd; r += rStep) {
                for (int c = cBeg; c != cEnd; c += cStep) {
                    if (grid[r][c] == '#') {
                        val[r][c] = 0;
                    } else {
                        int nr = r + dr[d], nc = c + dc[d];
                        val[r][c] = grid[r][c] == 'R' ? 1 : 0;
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) val[r][c] += val[nr][nc];
                        sum[r][c] += val[r][c];
                    }
                }
            }
        }
        int bestRow = 0, bestCol = 0, bestNum = -1;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int curNum = 0;
                if (grid[r][c] != '#') {
                    curNum = sum[r][c];
                    if (grid[r][c] == 'R') curNum -= 7;
                }
                if (curNum > bestNum) {
                    bestNum = curNum;
                    bestRow = r;
                    bestCol = c;
                }
            }
        }
        cout << bestRow + 1 << ' ' << bestCol + 1 << '\n';
    }
    return 0;
}
