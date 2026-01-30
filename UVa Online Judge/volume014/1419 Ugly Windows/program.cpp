// Ugly Windows
// UVa ID: 1419
// Verdict: Accepted
// Submission Date: 2026-01-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<string> grid;
bool isTop[26];

void checkTop(char ch) {
    int sr = -1, sc = -1;
    // 找左上角
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            if (grid[i][j] == ch) {
                sr = i; sc = j;
                break;
            }
        if (sr != -1) break;
    }
    if (sr == -1) return; // 没找到该字母
    // 向右延伸
    int width = 1;
    while (sc + width < m && grid[sr][sc + width] == ch) width++;
    // 向下延伸
    int height = 1;
    while (sr + height < n && grid[sr + height][sc] == ch) height++;
    // 检查是否满足最小尺寸（避免把尺寸 1 的窗口视为合法窗口）
    if (width < 3 || height < 3) return;
    // 检查下边和右边是否全是 ch
    // 下边
    for (int j = sc; j < sc + width; j++)
        if (grid[sr + height - 1][j] != ch) return;
    // 右边
    for (int i = sr; i < sr + height; i++)
        if (grid[i][sc + width - 1] != ch) return;
    // 检查内部是否全是 '.'（没有被其他窗口覆盖）
    for (int i = sr + 1; i < sr + height - 1; i++)
        for (int j = sc + 1; j < sc + width - 1; j++)
            if (grid[i][j] != '.') return;
    isTop[ch - 'A'] = true;
}

int main() {
    while (cin >> n >> m && (n || m)) {
        grid.resize(n);
        for (int i = 0; i < n; i++) cin >> grid[i];
        memset(isTop, 0, sizeof isTop);
        for (char ch = 'A'; ch <= 'Z'; ch++) checkTop(ch);
        for (int i = 0; i < 26; i++)
            if (isTop[i]) cout << char('A' + i);
        cout << endl;
    }
    return 0;
}
