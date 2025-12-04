// Midnight Cowboy
// UVa ID: 12487
// Verdict: Accepted
// Submission Date: 2025-12-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 105;
const double EPS = 1e-8;
vector<int> graph[MAX_N];      // 邻接表存储树
double mat[MAX_N][MAX_N + 1];  // 增广矩阵
double prob[MAX_N];            // 概率解

// 高斯消元求解线性方程组
void gaussElimination(int n) {
    for (int i = 1; i <= n; i++) {
        // 寻找主元（最大绝对值）
        int pivot = i;
        for (int j = i + 1; j <= n; j++)
            if (fabs(mat[j][i]) > fabs(mat[pivot][i]))
                pivot = j;
        
        // 交换当前行与主元行
        if (pivot != i)
            for (int j = 1; j <= n + 1; j++)
                swap(mat[i][j], mat[pivot][j]);
        
        // 如果主元接近零，跳过（实际上在本题中不会发生）
        if (fabs(mat[i][i]) > EPS) {
            // 消去下方行的第i列
            for (int j = i + 1; j <= n; j++) {
                double factor = mat[j][i] / mat[i][i];
                for (int k = i; k <= n + 1; k++)
                    mat[j][k] -= factor * mat[i][k];
            }
        }
    }
    
    // 回代求解
    for (int i = n; i >= 1; i--) {
        if (fabs(mat[i][i]) < EPS) continue;  // 零行，解不唯一（本题不会）
        double sum = 0.0;
        for (int j = i + 1; j <= n; j++)
            sum += mat[i][j] * prob[j];
        prob[i] = (mat[i][n + 1] - sum) / mat[i][i];
    }
}

int main() {
    int N, A, B, C;
    // 处理多个测试用例直到文件结束
    while (cin >> N >> A >> B >> C) {
        // 初始化邻接表
        for (int i = 1; i <= N; i++)
            graph[i].clear();
        
        // 读入N-1条边，构建树
        for (int i = 0; i < N - 1; i++) {
            int X, Y;
            cin >> X >> Y;
            graph[X].push_back(Y);
            graph[Y].push_back(X);
        }
        
        // 初始化增广矩阵为零
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N + 1; j++)
                mat[i][j] = 0.0;
        
        // 根据每个节点的类型建立方程
        for (int u = 1; u <= N; u++) {
            int deg = graph[u].size();  // 度数（邻居数）
            
            if (u == B) {
                // p[B] = 1
                mat[u][u] = 1.0;
                mat[u][N + 1] = 1.0;
            } else if (u == C) {
                // p[C] = 0
                mat[u][u] = 1.0;
                mat[u][N + 1] = 0.0;
            } else {
                // 普通节点：deg(u)*p[u] - sum(p[neighbors]) = 0
                mat[u][u] = deg;
                for (int v : graph[u])
                    mat[u][v] = -1.0;    // 邻居系数为-1
                mat[u][N + 1] = 0.0;     // 常数项为0
            }
        }
        
        // 高斯消元求解
        gaussElimination(N);
        
        // 输出从起点A出发先到B的概率
        cout << fixed << setprecision(6) << prob[A] << endl;
    }
    return 0;
}
