// Binary Stirling Numbers
// UVa ID: 1118
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
using namespace std;

int stirlingParity(int n, int m) {
    int diff = n - m;
    int k = (m + 1) / 2 - 1;
    return (diff & k) == 0 ? 1 : 0;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        cout << stirlingParity(n, m) << endl;
        // 题目描述中的输出要求与实际测试数据不符，实际测试数据不需要输出组间空行
        //if (t > 0) {
        //    cout << endl; // 输出之间的空行
        //}
    }
    return 0;
}
