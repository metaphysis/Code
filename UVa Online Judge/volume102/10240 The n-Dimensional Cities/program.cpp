// The n-Dimensional Cities
// UVa ID: 10240
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int dim, dist, d;
    while (cin >> dim >> dist >> d) {
        long long V = dim + 1;
        long long edges = (V * V) / 4;                          // 最大边数，整数除法向下取整
        
        double ratio = dist / (2.0 * d);                        // 弦长与直径之比
        double arcLen = 2.0 * d * asin(ratio);                 // 单条圆弧长度
        
        long long circularEdges = edges / 2;                   // 最多圆弧数
        long long straightEdges = edges - circularEdges;       // 剩余为直线
        
        double totalLen = straightEdges * dist + circularEdges * arcLen;
        long long roundedLen = (long long)floor(totalLen + 0.5);
        
        cout << edges << " " << roundedLen << "\n";
    }
    return 0;
}
