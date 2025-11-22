// Neon Sign
// UVa ID: 1510
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.200s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<vector<int>> color(n + 1, vector<int>(n + 1, 0));
    // 读取输入，构建颜色矩阵
    for (int i = 1; i <= n - 1; i++)
      for (int j = i + 1; j <= n; j++)
        cin >> color[i][j];
    
    // 统计每个顶点的红边和蓝边数量
    vector<int> redCount(n + 1, 0), blueCount(n + 1, 0);
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) {
        if (i == j) continue;
        int c;
        if (i < j) c = color[i][j];
        else c = color[j][i];
        if (c == 1) redCount[i]++;
        else blueCount[i]++;
      }
    
    // 计算总三角形数
    long long totalTriangles = (long long)n * (n - 1) * (n - 2) / 6;
    // 计算非单色三角形数
    long long nonMono = 0;
    for (int i = 1; i <= n; i++)
      nonMono += (long long)redCount[i] * blueCount[i];
    nonMono /= 2;
    
    // 计算单色三角形数
    long long mono = totalTriangles - nonMono;
    cout << mono << endl;
  }
  return 0;
}
