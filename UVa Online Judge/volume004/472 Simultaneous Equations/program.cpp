// Simultaneous Equations
// UVa ID: 472
// Verdict: Accepted
// Submission Date: 2026-06-25
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

// 解析一行中的复数，返回实部和虚部交替的 double 数组
vector<double> parseLine(const string& line) {
    vector<double> res;
    int i = 0;
    while (i < (int)line.size()) {
        while (i < (int)line.size() && line[i] != '(') ++i;
        if (i >= (int)line.size()) break;
        int j = i + 1;
        while (j < (int)line.size() && line[j] != ')') ++j;
        if (j >= (int)line.size()) break;
        string sub = line.substr(i + 1, j - i - 1);
        double a, b;
        sscanf(sub.c_str(), "%lf,%lf", &a, &b);
        res.push_back(a);
        res.push_back(b);
        i = j + 1;
    }
    return res;
}

// 将极小的浮点数归零，避免输出 -0.0
double normZero(double x) {
    if (fabs(x) < 5e-9) return 0.0;
    return x;
}

void solveDataset(const vector<vector<double>>& dataset, bool& first) {
    int n = dataset.size();
    int m = 2 * n;

    // 构造实数增广矩阵：m 行，m+1 列（最后一列为右端）
    vector<vector<double>> a(m, vector<double>(m + 1, 0.0));

    for (int i = 0; i < n; ++i) {
        // 实部方程：a*u - b*v = c
        for (int j = 0; j < n; ++j) {
            double real = dataset[i][2 * j];
            double imag = dataset[i][2 * j + 1];
            a[2 * i][2 * j] = real;
            a[2 * i][2 * j + 1] = -imag;
        }
        a[2 * i][m] = dataset[i][2 * n];

        // 虚部方程：b*u + a*v = d
        for (int j = 0; j < n; ++j) {
            double real = dataset[i][2 * j];
            double imag = dataset[i][2 * j + 1];
            a[2 * i + 1][2 * j] = imag;
            a[2 * i + 1][2 * j + 1] = real;
        }
        a[2 * i + 1][m] = dataset[i][2 * n + 1];
    }

    // 高斯消元（顺序消去下方）
    for (int i = 0; i < m; ++i) {
        int pivot = i;
        for (int j = i + 1; j < m; ++j) {
            if (fabs(a[j][i]) > fabs(a[pivot][i])) pivot = j;
        }
        if (fabs(a[pivot][i]) < EPS) {
            if (!first) printf("\n");
            printf("No solution\n");
            first = false;
            return;
        }
        if (pivot != i) swap(a[i], a[pivot]);

        for (int j = i + 1; j < m; ++j) {
            double factor = a[j][i] / a[i][i];
            for (int k = i; k <= m; ++k) {
                a[j][k] -= factor * a[i][k];
            }
        }
    }

    // 回代求解
    vector<double> x(m, 0.0);
    for (int i = m - 1; i >= 0; --i) {
        double sum = a[i][m];
        for (int j = i + 1; j < m; ++j) {
            sum -= a[i][j] * x[j];
        }
        x[i] = sum / a[i][i];
        x[i] = normZero(x[i]);
    }

    // 输出
    if (!first) printf("\n");
    for (int i = 0; i < n; ++i) {
        double realPart = x[2 * i];
        double imagPart = x[2 * i + 1];
        // 四舍五入保留一位小数
        double r = floor(realPart * 10 + 0.5) / 10.0;
        double im = floor(imagPart * 10 + 0.5) / 10.0;
        r = normZero(r);
        im = normZero(im);
        printf("(%.1f,%.1f)\n", r, im);
    }
    first = false;
}

int main() {
    string line;
    vector<vector<double>> dataset;
    bool first = true;

    while (getline(cin, line)) {
        bool empty = true;
        for (char c : line) {
            if (!isspace(c)) { empty = false; break; }
        }
        if (empty) {
            if (!dataset.empty()) {
                solveDataset(dataset, first);
                dataset.clear();
            }
        } else {
            vector<double> nums = parseLine(line);
            if (!nums.empty()) dataset.push_back(nums);
        }
    }
    if (!dataset.empty()) solveDataset(dataset, first);
    return 0;
}
