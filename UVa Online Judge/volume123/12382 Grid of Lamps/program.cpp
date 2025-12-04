// Grid of Lamps
// UVa ID: 12382
// Verdict: Accepted
// Submission Date: 2025-12-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int m, n;
        cin >> m >> n;
        
        vector<int> rowReq(m), colReq(n);
        long long sumRow = 0, sumCol = 0;
        
        for (int i = 0; i < m; i++) {
            cin >> rowReq[i];
            sumRow += rowReq[i];
        }
        
        for (int j = 0; j < n; j++) {
            cin >> colReq[j];
            sumCol += colReq[j];
        }
        
        // 行从大到小排序
        sort(rowReq.begin(), rowReq.end(), greater<int>());
        // 列从大到小排序
        sort(colReq.begin(), colReq.end(), greater<int>());
        
        long long result = max(sumRow, sumCol);
        
        // 预处理列前缀和
        vector<long long> colPrefix(n + 1, 0);
        for (int j = 0; j < n; j++) {
            colPrefix[j + 1] = colPrefix[j] + colReq[j];
        }
        
        // 计算 max_{k,l} (sumTopKRow + sumTopLCol - k*l)
        long long rowPrefix = 0;
        for (int k = 1; k <= m; k++) {
            rowPrefix += rowReq[k - 1];
            
            // 对于给定的 k，找到最大的 l 使得 colReq[l-1] >= k
            int l = 0;
            for (int j = 0; j < n; j++) {
                if (colReq[j] >= k) l = j + 1;
                else break;
            }
            
            // 对于 l 从 1 到 n，计算表达式
            for (int lj = 1; lj <= n; lj++) {
                long long colSum = colPrefix[lj];
                long long value = rowPrefix + colSum - 1LL * k * lj;
                if (value > result) result = value;
            }
        }
        
        cout << result << "\n";
    }
    
    return 0;
}
