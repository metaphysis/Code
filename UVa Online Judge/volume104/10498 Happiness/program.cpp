// Happiness
// UVa ID: 10498
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const double EPS = 1e-9;
const double INF = 1e+15;

// 单纯形法求解线性规划
double simplex(vector<vector<double>> A, vector<double> b, vector<double> c) {
    int m = A.size();    // 约束个数
    int n = c.size();    // 决策变量个数
    
    // 构造单纯形表 [目标函数行 | 约束行]
    vector<vector<double>> tableau(m + 1, vector<double>(n + m + 1, 0.0));
    
    // 设置目标函数行 (最大化 c^T x 转化为最小化 -c^T x)
    for (int j = 0; j < n; j++) {
        tableau[0][j] = -c[j];
    }
    
    // 设置约束行和松弛变量
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            tableau[i + 1][j] = A[i][j];
        }
        // 添加松弛变量 (Ax <= b 转化为 Ax + s = b, s >= 0)
        tableau[i + 1][n + i] = 1.0;
        tableau[i + 1][n + m] = b[i];  // RHS
    }
    
    // 单纯形主循环
    while (true) {
        // 选择入基变量：目标函数行中负值最小的列
        int pivot_col = -1;
        for (int j = 0; j < n + m; j++) {
            if (tableau[0][j] < -EPS) {
                if (pivot_col == -1 || tableau[0][j] < tableau[0][pivot_col]) {
                    pivot_col = j;
                }
            }
        }
        
        // 如果目标函数行无负值，达到最优解
        if (pivot_col == -1) break;
        
        // 选择出基变量：最小比率检验
        int pivot_row = -1;
        double min_ratio = INF;
        for (int i = 1; i <= m; i++) {
            if (tableau[i][pivot_col] > EPS) {
                double ratio = tableau[i][n + m] / tableau[i][pivot_col];
                if (ratio < min_ratio - EPS) {
                    min_ratio = ratio;
                    pivot_row = i;
                }
            }
        }
        
        // 无界解情况
        if (pivot_row == -1) return INF;
        
        // 旋转操作：以 tableau[pivot_row][pivot_col] 为主元
        double pivot_val = tableau[pivot_row][pivot_col];
        
        // 标准化主元行
        for (int j = 0; j <= n + m; j++) {
            tableau[pivot_row][j] /= pivot_val;
        }
        
        // 消去其他行中的入基变量
        for (int i = 0; i <= m; i++) {
            if (i == pivot_row) continue;
            double factor = tableau[i][pivot_col];
            for (int j = 0; j <= n + m; j++) {
                tableau[i][j] -= factor * tableau[pivot_row][j];
            }
        }
    }
    
    // 返回最优值（在单纯形表的右上角）
    return tableau[0][n + m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m) {
        // 读取物品单价
        vector<double> prices(n);
        for (int i = 0; i < n; i++) {
            cin >> prices[i];
        }
        
        // 读取参赛者幸福感数据
        vector<vector<double>> happiness(m, vector<double>(n));
        vector<double> totalHappiness(m);
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> happiness[i][j];
            }
            cin >> totalHappiness[i];
        }
        
        // 构造线性规划问题
        vector<vector<double>> A(m, vector<double>(n));
        vector<double> b(m);
        vector<double> c(n);
        
        // 约束矩阵 A 和右侧向量 b
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = happiness[i][j];
            }
            b[i] = totalHappiness[i];
        }
        
        // 目标函数系数 (总花费 = m × 单价 × 数量)
        for (int j = 0; j < n; j++) {
            c[j] = m * prices[j];
        }
        
        // 求解线性规划
        double maxCost = simplex(A, b, c);
        
        // 处理数值误差和向上取整
        if (maxCost < EPS) maxCost = 0;
        int result = static_cast<int>(ceil(maxCost - 1e-9));
        
        cout << "Nasa can spend " << result << " taka.\n";
    }
    
    return 0;
}
