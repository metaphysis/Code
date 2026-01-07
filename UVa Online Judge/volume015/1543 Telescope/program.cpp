// Telescope
// UVa ID: 1543
// Verdict: Accepted
// Submission Date: 2025-12-31
// UVa Run Time: 0.060s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = 3.14159265358979323846;
const double TWO_PI = 2.0 * PI;

// 计算最大多边形面积
double maxPolygonArea(int n, int m, vector<double>& p) {
    if (m < 3) return 0.0;
    
    // 将位置参数转换为弧度角
    vector<double> angle(n);
    for (int i = 0; i < n; ++i)
        angle[i] = p[i] * TWO_PI;
    
    double maxArea = 0.0;
    
    // 枚举第一个顶点
    for (int start = 0; start < n; ++start) {
        // 创建从start开始的角度序列，处理圆周循环
        vector<double> sortedAngles;
        for (int i = start; i < n; ++i)
            sortedAngles.push_back(angle[i]);
        for (int i = 0; i < start; ++i)
            sortedAngles.push_back(angle[i] + TWO_PI);
        
        int cnt = sortedAngles.size();
        if (cnt < m) continue;  // 点数不足
        
        // DP数组，初始化为负无穷大
        vector<vector<double>> dp(cnt, vector<double>(m + 1, -1e9));
        dp[0][1] = 0.0;  // 第一个点（起始点）单独一个点，面积为0
        
        // DP转移
        for (int k = 2; k <= m; ++k) {
            for (int i = k - 1; i < cnt; ++i) {
                for (int j = k - 2; j < i; ++j) {
                    // 计算三角形面积：0.5 * sin(角度差)
                    double triangleArea = 0.5 * sin(sortedAngles[i] - sortedAngles[j]);
                    dp[i][k] = max(dp[i][k], dp[j][k - 1] + triangleArea);
                }
            }
        }
        
        // 闭合多边形：连接最后一个顶点回到起始点
        // 起始点角度需要加上2π，因为sortedAngles[0]是原始起始点角度
        double startAngle = sortedAngles[0] + TWO_PI;
        for (int i = m - 1; i < cnt; ++i) {
            if (dp[i][m] < -1e8) continue;  // 不可达状态
            double closeArea = 0.5 * sin(startAngle - sortedAngles[i]);
            maxArea = max(maxArea, dp[i][m] + closeArea);
        }
    }
    
    return maxArea;
}

int main() {
    int n, m;
    while (cin >> n >> m, n || m) {
        vector<double> p(n);
        for (int i = 0; i < n; ++i)
            cin >> p[i];
        // 确保输入已排序，题目保证但再次排序更安全
        sort(p.begin(), p.end());
        double ans = maxPolygonArea(n, m, p);
        printf("%.6lf\n", ans);
    }
    return 0;
}
