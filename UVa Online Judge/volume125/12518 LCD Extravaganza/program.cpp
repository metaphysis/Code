// LCD Extravaganza
// UVa ID: 12518
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.020s
// https://blog.csdn.net/metaphysis/article/details/163173321

#include <bits/stdc++.h>
using namespace std;

// 传统数字 0-9 的 3x3 模板，用 '.' 表示空白
const string digitTmpl[10][3] = {
    // 0
    {" _ ", "| |", "|_|"},
    // 1
    {"   ", "  |", "  |"},
    // 2
    {" _ ", " _|", "|_ "},
    // 3
    {" _ ", " _|", " _|"},
    // 4
    {"   ", "|_|", "  |"},
    // 5
    {" _ ", "|_ ", " _|"},
    // 6
    {" _ ", "|_ ", "|_|"},
    // 7
    {" _ ", "  |", "  |"},
    // 8
    {" _ ", "|_|", "|_|"},
    // 9
    {" _ ", "|_|", " _|"}
};

// 获取放大后数字 (d, f) 在局部坐标 (y, x) 处的字符
char getChar(int d, int f, long long y, long long x) {
    const string (&tmpl)[3] = digitTmpl[d];

    // 检查竖线 '|'
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (tmpl[r][c] != '|') continue;
            int colX;
            if (c == 0) colX = 0;
            else if (c == 2) colX = f + 1;
            else continue;          // 中间列不会有竖线

            long long rowStart, rowEnd;
            if (r == 1) {           // 中间行竖线占据 f..2f-1
                rowStart = f;
                rowEnd = 2LL * f - 1;
            } else if (r == 2) {    // 底行竖线占据 0..f-1
                rowStart = 0;
                rowEnd = f - 1;
            } else continue;        // 顶行无竖线

            if (x == colX && y >= rowStart && y <= rowEnd)
                return '|';
        }
    }

    // 检查下划线 '_'
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (tmpl[r][c] != '_') continue;
            // 下划线只可能在中间列，水平扩展为 1..f
            if (x < 1 || x > f) continue;
            long long rowY;
            if (r == 0) rowY = 2LL * f;      // 顶行
            else if (r == 1) rowY = f;       // 中间行横线放在区域底部
            else rowY = 0;                   // 底行
            if (y == rowY) return '_';
        }
    }

    return '.';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N && N != 0) {
        vector<int> digits(N);
        vector<long long> factors(N);
        for (int i = 0; i < N; ++i) {
            cin >> digits[i] >> factors[i];
        }

        // 计算每个数字的宽度和起始列
        vector<long long> startCol(N), width(N);
        long long cur = 0;
        for (int i = 0; i < N; ++i) {
            startCol[i] = cur;
            width[i] = factors[i] + 2;          // f + 2 列
            cur += width[i] + 1;                // 数字宽度 + 间隔一列
        }

        int M;
        cin >> M;
        while (M--) {
            long long x, y;
            cin >> x >> y;

            // 二分查找 x 落在哪个数字区间内
            int idx = int(upper_bound(startCol.begin(), startCol.end(), x) - startCol.begin()) - 1;
            char ans = '.';
            if (idx >= 0) {
                long long localX = x - startCol[idx];
                // 确保在数字宽度内，否则该列属于间隔（点）
                if (localX < width[idx]) {
                    long long f = factors[idx];
                    long long maxRow = 2LL * f + 1;
                    // 若 y 超出该数字高度，则该位置为点
                    if (y < maxRow) {
                        ans = getChar(digits[idx], (int)f, y, localX);
                    }
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
