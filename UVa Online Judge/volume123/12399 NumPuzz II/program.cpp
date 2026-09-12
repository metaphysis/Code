// NumPuzz II
// UVa ID: 12399
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int initialBoard[3][3];
int press[3][3];

int bestCount;
string bestAnswer;

// 将数规范化到 0..9
int mod10(int value) {
    value %= 10;
    if (value < 0) value += 10;
    return value;
}

// 根据前面已经确定的行，计算当前行某一格必须点击多少次
int requiredPress(int row, int col) {
    // 当前要让 row - 1 行归零。
    // 该位置会受到：
    // 1. row - 1 行自身及左右点击的影响
    // 2. row - 2 行同列点击的影响
    int value = initialBoard[row - 1][col];
    value -= press[row - 1][col];
    if (col > 0) value -= press[row - 1][col - 1];
    if (col < 2) value -= press[row - 1][col + 1];
    if (row >= 2) value -= press[row - 2][col];
    return mod10(value);
}

// 检查最后一行是否已经归零
bool lastRowIsZero() {
    for (int col = 0; col < 3; ++col) {
        int value = initialBoard[2][col];
        value -= press[2][col];
        if (col > 0) value -= press[2][col - 1];
        if (col < 2) value -= press[2][col + 1];
        value -= press[1][col];
        if (mod10(value) != 0) return false;
    }
    return true;
}

void updateAnswer() {
    int count = 0;
    string answer;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            count += press[row][col];

            char ch = char('a' + row * 3 + col);
            answer.append(press[row][col], ch);
        }
    }
    if (count < bestCount) {
        bestCount = count;
        bestAnswer = answer;
    }
}

// 按行、按格子进行 DFS
void dfs(int row, int col) {
    if (row == 3) {
        if (lastRowIsZero()) {
            updateAnswer();
        }
        return;
    }
    if (col == 3) {
        dfs(row + 1, 0);
        return;
    }
    if (row == 0) {
        // 第一行没有限制，枚举每格点击 0..9 次
        for (int times = 0; times <= 9; ++times) {
            press[row][col] = times;
            dfs(row, col + 1);
        }
    } else {
        // 第二、三行的点击次数由上一行必须归零唯一决定
        press[row][col] = requiredPress(row, col);
        dfs(row, col + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string caseLabel;
    string caseNumber;
    while (cin >> caseLabel >> caseNumber) {
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                cin >> initialBoard[row][col];
        memset(press, 0, sizeof(press));
        bestCount = INT_MAX;
        bestAnswer.clear();
        dfs(0, 0);
        if (bestCount == INT_MAX) cout << "No solution.\n";
        else cout << bestAnswer << '\n';
    }
    return 0;
}
