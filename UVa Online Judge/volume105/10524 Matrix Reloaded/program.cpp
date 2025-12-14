// Matrix Reloaded
// UVa ID: 10524
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9; // 浮点数比较精度

// 高斯-约当消元求逆，不允许选主元
bool gaussJordanInverseNoPivoting(vector<vector<double>>& a) {
    int n = a.size();
    vector<vector<double>> inv(n, vector<double>(n, 0.0));
    // 初始化单位矩阵
    for (int i = 0; i < n; i++) inv[i][i] = 1.0;
    // 高斯消元，不允许选主元
    for (int i = 0; i < n; i++) {
        // 检查主元是否接近0（不允许交换行）
        if (fabs(a[i][i]) < EPS) return false;
        // 归一化当前行
        double divisor = a[i][i];
        for (int j = 0; j < n; j++) {
            a[i][j] /= divisor;
            inv[i][j] /= divisor;
        }
        // 消去其他行的当前列
        for (int j = 0; j < n; j++) {
            if (j != i && fabs(a[j][i]) > EPS) {
                double factor = a[j][i];
                for (int k = 0; k < n; k++) {
                    a[j][k] -= factor * a[i][k];
                    inv[j][k] -= factor * inv[i][k];
                }
            }
        }
    }
    // 将逆矩阵复制回a
    a = inv;
    return true;
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int n;
    while (cin >> n && n != 0) {
        vector<vector<double>> matrix(n, vector<double>(n));
        // 读入矩阵
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> matrix[i][j];
        // 复制矩阵用于计算
        vector<vector<double>> original = matrix;
        // 计算逆矩阵（不允许选主元）
        bool possible = gaussJordanInverseNoPivoting(matrix);
        if (!possible) cout << "Not possible\n";
        else {
            // 输出逆矩阵，每行元素用空格分隔
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j > 0) cout << " ";
                    cout << fixed << setprecision(6) << matrix[i][j];
                }
                cout << "\n";
            }
        }
        // 每个测试用例后输出空行
        cout << "\n";
    }
    return 0;
}
