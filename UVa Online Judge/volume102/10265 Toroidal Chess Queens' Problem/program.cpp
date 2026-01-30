// Toroidal Chess Queens' Problem
// UVa ID: 10265
// Verdict: Accepted
// Submission Date: 2026-01-19
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int M, N, K;  // M列，N行
vector<pair<int, int>> solution;
bool found;

// 预计算：maskDiag[row][col] 表示与(row,col)冲突的所有位置掩码
vector<vector<unsigned long long>> diagMask1, diagMask2; // 每个位置的对角线冲突掩码

// 初始化对角线冲突掩码
void initDiagMasks() {
    diagMask1.assign(N, vector<unsigned long long>(M, 0));
    diagMask2.assign(N, vector<unsigned long long>(M, 0));
    for (int r1 = 0; r1 < N; r1++) {
        for (int c1 = 0; c1 < M; c1++) {
            unsigned long long mask1 = 0, mask2 = 0;
            // 检查所有其他位置
            for (int r2 = 0; r2 < N; r2++) {
                for (int c2 = 0; c2 < M; c2++) {
                    if (r1 == r2 && c1 == c2) continue;
                    int dr = (r2 - r1 + N) % N;
                    bool conflict = false;
                    // 快速对角线检查
                    for (int k = 0; k < M && !conflict; k++) {
                        int t = dr + k * N;
                        if ((c1 + t) % M == c2 || (c1 - t + M * N) % M == c2) {
                            conflict = true;
                        }
                    }
                    if (conflict) {
                        int idx = r2 * M + c2;
                        if (idx < 64) mask1 |= (1ULL << idx);
                        else mask2 |= (1ULL << (idx - 64));
                    }
                }
            }
            diagMask1[r1][c1] = mask1;
            diagMask2[r1][c1] = mask2;
        }
    }
}

// 快速冲突检查（使用预计算的掩码）
bool canPlaceFast(int r, int c, unsigned long long used1, unsigned long long used2) {
    // 检查对角线冲突
    if ((used1 & diagMask1[r][c]) || (used2 & diagMask2[r][c])) return false;
    return true;
}

// 搜索函数
void dfs(int row, int placed, unsigned long long used1, unsigned long long used2, 
         int colMask, vector<pair<int, int>>& queens) {
    if (found) return;
    if (placed == K) {
        solution = queens;
        found = true;
        return;
    }
    if (row >= N) return;
    if (N - row < K - placed) return; // 剩余行数不足
    // 生成当前行可放置的列
    for (int c = 0; c < M; c++) {
        if (colMask & (1 << c)) continue; // 列已被占用
        // 快速对角线检查
        if (!canPlaceFast(row, c, used1, used2)) continue;
        // 放置皇后
        queens.push_back({row, c});
        int idx = row * M + c;
        unsigned long long newUsed1 = used1;
        unsigned long long newUsed2 = used2;
        if (idx < 64) newUsed1 |= (1ULL << idx);
        else newUsed2 |= (1ULL << (idx - 64));
        dfs(row + 1, placed + 1, newUsed1, newUsed2, colMask | (1 << c), queens);
        queens.pop_back();
        if (found) return;
    }
    // 不放皇后
    dfs(row + 1, placed, used1, used2, colMask, queens);
}

int main() {
    while (cin >> M >> N >> K) {
        if (K > min(M, N)) {
            cout << "0 0\n";
            continue;
        }
        // 初始化对角线掩码
        initDiagMasks();
        solution.clear();
        found = false;
        vector<pair<int, int>> queens;
        dfs(0, 0, 0ULL, 0ULL, 0, queens);
        if (found) {
            for (auto& p : solution) {
                cout << p.second + 1 << " " << p.first + 1 << "\n";
            }
        } else cout << "0 0\n";
    }
    return 0;
}
