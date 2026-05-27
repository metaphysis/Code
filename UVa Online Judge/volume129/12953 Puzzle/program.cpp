// Puzzle
// UVa ID: 12953
// Verdict: Accepted
// Submission Date: 2026-05-27
// UVa Run Time: 0.330s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int L, C;
    while (cin >> L >> C) {
        vector<vector<string>> grid(L, vector<string>(C));
        vector<long long> rowSum(L), colSum(C);
        
        // 读入网格和行和
        for (int i = 0; i < L; ++i) {
            for (int j = 0; j < C; ++j)
                cin >> grid[i][j];
            cin >> rowSum[i];
        }
        
        // 读入列和
        for (int j = 0; j < C; ++j)
            cin >> colSum[j];
        
        // 记录每个变量出现的位置
        map<string, vector<pair<int, int>>> varPos;
        for (int i = 0; i < L; ++i)
            for (int j = 0; j < C; ++j)
                varPos[grid[i][j]].emplace_back(i, j);
        
        // 记录每个变量是否已求解
        map<string, bool> solved;
        map<string, long long> value;
        
        // 记录每个格子是否已确定值
        vector<vector<bool>> cellKnown(L, vector<bool>(C, false));
        
        // 记录每行/列当前已知值的和
        vector<long long> rowKnownSum(L, 0), colKnownSum(C, 0);
        
        // 记录每行/列中还有多少个格子的变量未知
        vector<int> rowUnknownVars(L), colUnknownVars(C);
        for (int i = 0; i < L; ++i) rowUnknownVars[i] = C;
        for (int j = 0; j < C; ++j) colUnknownVars[j] = L;
        
        // 用于判断某行/列是否只有一个不同的未知变量
        // 返回该变量名和出现次数
        auto getUniqueUnknownVar = [&](int row, bool isRow) {
            map<string, int> varCount;
            if (isRow) {
                for (int j = 0; j < C; ++j) {
                    if (!cellKnown[row][j]) {
                        string var = grid[row][j];
                        varCount[var]++;
                    }
                }
            } else {
                int col = row; // 复用参数
                for (int i = 0; i < L; ++i) {
                    if (!cellKnown[i][col]) {
                        string var = grid[i][col];
                        varCount[var]++;
                    }
                }
            }
            if (varCount.size() == 1)
                return make_pair(varCount.begin()->first, varCount.begin()->second);
            return make_pair(string(""), 0);
        };
        
        // 求解变量
        auto solveVariable = [&](string var, long long val) {
            if (solved[var]) return;
            solved[var] = true;
            value[var] = val;
            
            // 更新所有包含该变量的格子
            for (auto& pos : varPos[var]) {
                int r = pos.first, c = pos.second;
                if (!cellKnown[r][c]) {
                    cellKnown[r][c] = true;
                    rowKnownSum[r] += val;
                    colKnownSum[c] += val;
                    rowUnknownVars[r]--;
                    colUnknownVars[c]--;
                }
            }
        };
        
        // 不断求解直到所有变量都解出
        bool progress = true;
        while (progress) {
            progress = false;
            
            // 检查每一行
            for (int i = 0; i < L; ++i) {
                if (rowUnknownVars[i] == 0) continue;
                
                auto [varName, cnt] = getUniqueUnknownVar(i, true);
                if (varName.empty()) continue;
                
                // 该行只有一个未知变量
                if (cnt == rowUnknownVars[i]) {
                    long long totalUnknown = rowSum[i] - rowKnownSum[i];
                    if (cnt > 1) {
                        // 变量出现多次，需要确保能整除
                        if (totalUnknown % cnt == 0) {
                            solveVariable(varName, totalUnknown / cnt);
                            progress = true;
                        }
                    } else {
                        solveVariable(varName, totalUnknown);
                        progress = true;
                    }
                }
            }
            
            // 检查每一列
            for (int j = 0; j < C; ++j) {
                if (colUnknownVars[j] == 0) continue;
                
                auto [varName, cnt] = getUniqueUnknownVar(j, false);
                if (varName.empty()) continue;
                
                // 该列只有一个未知变量
                if (cnt == colUnknownVars[j]) {
                    long long totalUnknown = colSum[j] - colKnownSum[j];
                    if (cnt > 1) {
                        if (totalUnknown % cnt == 0) {
                            solveVariable(varName, totalUnknown / cnt);
                            progress = true;
                        }
                    } else {
                        solveVariable(varName, totalUnknown);
                        progress = true;
                    }
                }
            }
        }
        
        // 按字典序输出
        for (auto& p : varPos) {
            cout << p.first << " " << value[p.first] << "\n";
        }
    }
    return 0;
}
