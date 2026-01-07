// Lines of Containers
// UVa ID: 12652
// Verdict: Accepted
// Submission Date: 2025-12-31
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, C;
    while (cin >> L >> C) {
        vector<vector<int>> grid(L, vector<int>(C));
        for (int i = 0; i < L; i++) 
            for (int j = 0; j < C; j++) 
                cin >> grid[i][j];

        vector<int> rowId(L, -1), colId(C, -1);
        bool possible = true;

        // 1. 检查每一行
        for (int i = 0; i < L && possible; i++) {
            int minVal = *min_element(grid[i].begin(), grid[i].end());
            // 检查最小值是否是 k*C + 1 的形式
            if ((minVal - 1) % C != 0) {
                possible = false;
                break;
            }
            int base = (minVal - 1) / C; // 转换为0-based行号
            // 检查该行是否包含连续C个数
            vector<int> sortedRow = grid[i];
            sort(sortedRow.begin(), sortedRow.end());
            for (int j = 0; j < C; j++) {
                if (sortedRow[j] != base * C + 1 + j) {
                    possible = false;
                    break;
                }
            }
            if (!possible) break;
            rowId[i] = base;
        }

        // 2. 检查行号集合是否为 {0..L-1}
        if (possible) {
            vector<bool> rowUsed(L, false);
            for (int i = 0; i < L; i++) {
                if (rowId[i] < 0 || rowId[i] >= L || rowUsed[rowId[i]]) {
                    possible = false;
                    break;
                }
                rowUsed[rowId[i]] = true;
            }
        }

        // 3. 检查每一列
        if (possible) {
            for (int j = 0; j < C && possible; j++) {
                int modVal = (grid[0][j] - 1) % C; // 转换为0-based模值
                // 检查整列同余
                for (int i = 0; i < L; i++) {
                    if ((grid[i][j] - 1) % C != modVal) {
                        possible = false;
                        break;
                    }
                }
                if (!possible) break;
                colId[j] = modVal;
            }
        }

        // 4. 检查列模值集合是否为 {0..C-1}
        if (possible) {
            vector<bool> colUsed(C, false);
            for (int j = 0; j < C; j++) {
                if (colId[j] < 0 || colId[j] >= C || colUsed[colId[j]]) {
                    possible = false;
                    break;
                }
                colUsed[colId[j]] = true;
            }
        }

        // 5. 整体验证公式
        if (possible) {
            for (int i = 0; i < L && possible; i++) {
                for (int j = 0; j < C; j++) {
                    int expected = rowId[i] * C + colId[j] + 1; // 转回1-based
                    if (grid[i][j] != expected) {
                        possible = false;
                        break;
                    }
                }
            }
        }

        if (!possible) {
            cout << "*\n";
            continue;
        }

        // 6. 计算最少行交换次数
        int rowSwaps = 0;
        vector<int> rowTemp = rowId;
        for (int i = 0; i < L; i++) {
            if (rowTemp[i] != i) {
                int pos = i;
                while (rowTemp[pos] != i) pos++;
                swap(rowTemp[i], rowTemp[pos]);
                rowSwaps++;
            }
        }

        // 7. 计算最少列交换次数
        int colSwaps = 0;
        vector<int> colTemp = colId;
        for (int i = 0; i < C; i++) {
            if (colTemp[i] != i) {
                int pos = i;
                while (colTemp[pos] != i) pos++;
                swap(colTemp[i], colTemp[pos]);
                colSwaps++;
            }
        }

        cout << rowSwaps + colSwaps << "\n";
    }

    return 0;
}
