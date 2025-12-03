// Overlapping Characters
// UVa ID: 12586
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    string order;
    cin >> order;

    // 将字符映射到其在order中的索引
    unordered_map<char, int> charToIndex;
    for (int i = 0; i < n; ++i)
        charToIndex[order[i]] = i;

    // 存储每个字符的网格
    vector<vector<string>> grids(n);
    for (int chIdx = 0; chIdx < n; ++chIdx) {
        vector<string> grid(16);
        for (int row = 0; row < 16; ++row)
            cin >> grid[row];
        grids[chIdx] = grid;
        // 跳过每个字符描述后的空行
        string emptyLine;
        getline(cin, emptyLine); // 处理可能的换行符残留
        getline(cin, emptyLine); // 读取真正的空行
    }

    // 处理每个查询
    for (int queryId = 1; queryId <= q; ++queryId) {
        string queryStr;
        cin >> queryStr;
        int m = queryStr.size();

        // 叠加层，用字符填充，'#'表示重叠，'.'表示空
        vector<vector<char>> overlay(16, vector<char>(43, '.'));

        // 叠加所有字符
        for (int i = 0; i < m; ++i) {
            char ch = queryStr[i];
            int idx = charToIndex[ch];
            const vector<string>& grid = grids[idx];
            for (int row = 0; row < 16; ++row)
                for (int col = 0; col < 43; ++col)
                    if (grid[row][col] == '*') {
                        if (overlay[row][col] == '.') // 空，标记为当前字符
                            overlay[row][col] = ch;
                        else if (overlay[row][col] != ch) // 已被其他字符占据
                            overlay[row][col] = '#'; // 标记为重叠
                    }
        }

        // 判断每个字符是否能被检测
        string result(m, 'N');
        for (int i = 0; i < m; ++i) {
            char ch = queryStr[i];
            int idx = charToIndex[ch];
            const vector<string>& grid = grids[idx];
            bool canDetect = false;
            // 检查该字符的每个'*'位置，在叠加层中是否仍然是该字符（未被覆盖）
            for (int row = 0; row < 16; ++row) {
                for (int col = 0; col < 43; ++col)
                    if (grid[row][col] == '*' && overlay[row][col] == ch) {
                        canDetect = true;
                        break;
                    }
                if (canDetect) break;
            }
            if (canDetect) result[i] = 'Y';
        }

        cout << "Query " << queryId << ": " << result << endl;
    }

    return 0;
}
