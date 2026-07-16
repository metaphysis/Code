// Help My Brother
// UVa ID: 11033
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.260s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M, P;
    int caseNum = 1;
    while (cin >> N >> M >> P) {
        if (N == 0 && M == 0 && P == 0) break;
        // 生成所有行向量（四元组，和为N，元素1~7），按字典序排列
        vector<array<int, 4>> rows;
        for (int a = 1; a <= 7; ++a)
            for (int b = 1; b <= 7; ++b)
                for (int c = 1; c <= 7; ++c) {
                    int d = N - a - b - c;
                    if (d >= 1 && d <= 7)
                        rows.push_back({a, b, c, d});
                }
        int total = 0;
        int ans1[4][4], ans2[4][4];
        // 枚举前三行
        for (size_t i1 = 0; i1 < rows.size(); ++i1)
            for (size_t i2 = 0; i2 < rows.size(); ++i2)
                for (size_t i3 = 0; i3 < rows.size(); ++i3) {
                    int row4[4];
                    bool ok = true;
                    // 由列和确定第四行
                    for (int j = 0; j < 4; ++j) {
                        int val = N - rows[i1][j] - rows[i2][j] - rows[i3][j];
                        if (val < 1 || val > 7) { ok = false; break; }
                        row4[j] = val;
                    }
                    if (!ok) continue;
                    // 检查两条对角线
                    int diag1 = rows[i1][0] + rows[i2][1] + rows[i3][2] + row4[3];
                    int diag2 = rows[i1][3] + rows[i2][2] + rows[i3][1] + row4[0];
                    if (diag1 != N || diag2 != N) continue;
                    // 构建完整矩阵
                    int mat[4][4];
                    for (int j = 0; j < 4; ++j) mat[0][j] = rows[i1][j];
                    for (int j = 0; j < 4; ++j) mat[1][j] = rows[i2][j];
                    for (int j = 0; j < 4; ++j) mat[2][j] = rows[i3][j];
                    for (int j = 0; j < 4; ++j) mat[3][j] = row4[j];
                    // 计算乘积模 M
                    long long prod = 1;
                    for (int i = 0; i < 4; ++i)
                        for (int j = 0; j < 4; ++j)
                            prod = (prod * mat[i][j]) % M;
                    if (prod <= P) {
                        ++total;
                        if (total == 1) memcpy(ans1, mat, sizeof(ans1));
                        else if (total == 2) memcpy(ans2, mat, sizeof(ans2));
                    }
                }
        // 输出
        cout << "Set " << caseNum << ":" << endl;
        cout << total << endl;
        if (total >= 1) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) cout << ans1[i][j];
                cout << endl;
            }
            cout << "...." << endl;
        }
        if (total >= 2) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) cout << ans2[i][j];
                cout << endl;
            }
            cout << "...." << endl;
        }
        ++caseNum;
    }
    return 0;
}
