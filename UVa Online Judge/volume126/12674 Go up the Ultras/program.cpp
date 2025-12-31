// Go up the Ultras
// UVa ID: 12674
// Verdict: Accepted
// Submission Date: 2025-12-24
// UVa Run Time: 0.100s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<int> h(n);
        for (int i = 0; i < n; i++) cin >> h[i];
        
        // 左边第一个严格更高的位置
        vector<int> leftHigher(n, -1);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && h[st.top()] <= h[i]) st.pop();
            if (!st.empty()) leftHigher[i] = st.top();
            st.push(i);
        }
        
        // 右边第一个严格更高的位置
        while (!st.empty()) st.pop();
        vector<int> rightHigher(n, n);
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && h[st.top()] <= h[i]) st.pop();
            if (!st.empty()) rightHigher[i] = st.top();
            st.push(i);
        }
        
        // 构建稀疏表（RMQ）用于快速查询区间最小值
        int logn = 1;
        while ((1 << logn) <= n) logn++;
        vector<vector<int>> minTable(logn, vector<int>(n));
        for (int i = 0; i < n; i++) minTable[0][i] = h[i];
        for (int k = 1; k < logn; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                minTable[k][i] = min(minTable[k - 1][i], minTable[k - 1][i + (1 << (k - 1))]);
        
        // 区间最小值查询函数
        auto rangeMin = [&](int l, int r) {
            if (l >= r) return INT_MAX;
            int k = 31 - __builtin_clz(r - l);
            return min(minTable[k][l], minTable[k][r - (1 << k)]);
        };
        
        // 计算每个山峰的突出度并找出 Ultras
        vector<int> ultras;
        for (int i = 1; i < n - 1; i++) {
            int leftMin = 0;
            if (leftHigher[i] != -1) leftMin = rangeMin(leftHigher[i] + 1, i);
            
            int rightMin = 0;
            if (rightHigher[i] != n) rightMin = rangeMin(i + 1, rightHigher[i]);
            
            int prominence;
            if (leftHigher[i] == -1 && rightHigher[i] == n) prominence = h[i];
            else prominence = h[i] - max(leftMin, rightMin);
            
            if (prominence >= 150000) ultras.push_back(i + 1);
        }
        
        // 输出结果
        if (!ultras.empty()) {
            cout << ultras[0];
            for (size_t i = 1; i < ultras.size(); i++) cout << " " << ultras[i];
        }
        cout << "\n";
    }
    return 0;
}
