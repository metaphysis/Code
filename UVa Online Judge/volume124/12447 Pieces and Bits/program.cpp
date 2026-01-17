// Pieces and Bits
// UVa ID: 12447
// Verdict: Accepted
// Submission Date: 2026-01-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    int visited[1 << 16]; // 访问标记数组，最多 2^16 = 65536 个元素
    
    while (t--) {
        int n;
        cin >> n;
        int bit = 0;              // 当前数，从 0 开始
        int cnt = 0;              // 已输出的数的个数
        int total = (1 << n);     // 总个数 2^n
        
        memset(visited, 0, sizeof visited); // 初始化访问标记
        
        while (cnt < total) {
            cout << bit << '\n';      // 输出当前数
            visited[bit] = 1;         // 标记已访问
            cnt++;
            
            // 尝试所有可能的位，寻找下一个未访问的数
            for (int i = 0; i < n; i++) {
                // 保留第 i 位，其他位取反
                int nxt = (bit ^ ((1 << n) - 1)) ^ (1 << i);
                if (visited[nxt]) continue; // 已访问过，跳过
                bit = nxt;                  // 找到下一个数
                break;
            }
        }
    }
    
    return 0;
}
