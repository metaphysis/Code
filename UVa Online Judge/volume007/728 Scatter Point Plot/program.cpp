// Scatter Point Plot
// UVa ID: 728
// Verdict: Accepted
// Submission Date: 2026-07-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int tc = 0; tc < T; ++tc) {
        int lowX, incX, lowY, incY;
        cin >> lowX >> incX;
        cin >> lowY >> incY;
        vector<vector<int>> cnt(20, vector<int>(12, 0));
        string line;
        cin.ignore(128, '\n'); // 跳过 incY 后的换行符
        while (getline(cin, line)) {
            if (line.empty()) break; // 空行表示当前数据集结束
            int p = line.find(',');
            int x = stoi(line.substr(0, p));
            int y = stoi(line.substr(p + 1));
            // 四舍五入到最近的刻度（.5 向上取整）
            int xi = (2 * (x - lowX) + incX) / (2 * incX);
            int yi = (2 * (y - lowY) + incY) / (2 * incY);
            // 忽略超出 X 或 Y 轴范围的点（仅检查上界，下界未检查但实际数据通常合法）
            if (yi > 19 || xi > 11) continue;
            cnt[yi][xi]++;
        }
        // 输出 20 行（从 Y 最大值到最小值）
        for (int yi = 19; yi >= 0; --yi) {
            int yVal = lowY + yi * incY;
            string ystr = to_string(yVal);
            string row = string(4 - ystr.size(), ' ') + ystr + ':';
            int last = 5; // 当前行已占用的列数
            // 每个 X 刻度占 5 列
            for (int xi = 0, cln = 10; xi < 12; xi++, cln += 5) {
                if (cnt[yi][xi] > 0) {
                    string s = to_string(cnt[yi][xi]);
                    int ending = cln;
                    // 数字超过 2 位则扩展一列
                    if (s.size() > 2) ending++;
                    row += string(ending - last - s.length(), ' ') + s;
                    last = ending;
                } else {
                    row += string(cln - last, ' ');
                    last = cln;
                }
            }
            while (!row.empty() && row.back() == ' ') row.pop_back();
            cout << row << '\n';
        }
        // 输出 X 轴网格线：前面 4 个空格 + 固定格式
        string gridLine = string(4, ' ') + "+----+----+----+----+----+----+----+----+----+----+----+----+";
        cout << gridLine << '\n';
        // 输出 X 轴标签（左对齐，占 5 列）
        string xRow = string(5, ' ');
        int last = 5;
        for (int xi = 0, cln = 10; xi < 12; xi++, cln += 5) {
            int xVal = lowX + xi * incX;
            string label = to_string(xVal);
            int ending = cln;
            if (label.size() > 2) ending++;
            xRow += string(ending - last - label.length(), ' ') + label;
            last = ending;
        }
        while (!xRow.empty() && xRow.back() == ' ') xRow.pop_back();
        cout << xRow << '\n';
        // 数据集之间输出空行（最后一个不输出）
        if (tc != T - 1) cout << '\n';
    }
    return 0;
}
