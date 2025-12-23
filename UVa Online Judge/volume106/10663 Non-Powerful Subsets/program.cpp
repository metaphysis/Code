// Non-Powerful Subsets
// UVa ID: 10663
// Verdict: Accepted
// Submission Date: 2025-12-15
// UVa Run Time: 0.620s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXSUM = 500600;

bool isPower[MAXSUM];

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    // 预处理所有幂数（N^M，N>=2，M>=2）
    for (int n = 2; n * n < MAXSUM; n++) {
        int v = n * n;
        while (v < MAXSUM) {
            isPower[v] = true;
            v *= n;
        }
    }
    
    int a, b;
    while (cin >> a >> b) {
        unordered_set<int> sums[2];  // 两个集合交替使用
        vector<int> r;               // 结果集合
        int u = 0, v = 1;            // 当前和下一个集合的索引
        
        for (int n = a; n <= b; n++) {
            if (isPower[n]) continue;  // n本身是幂数，跳过
            
            // 检查是否安全：对于所有当前和s，s+n不能是幂数
            bool safe = true;
            for (auto s : sums[u]) {
                if (isPower[s + n]) {
                    safe = false;
                    break;
                }
            }
            if (!safe) continue;
            
            // 安全，加入结果
            r.push_back(n);
            
            // 更新子集和集合
            sums[v].clear();
            for (auto s : sums[u]) {
                sums[v].insert(s);
                sums[v].insert(s + n);
            }
            sums[v].insert(n);
            
            // 交换当前和下一个集合
            swap(u, v);
        }
        
        // 输出结果
        if (!r.empty()) {
            cout << r[0];
            for (size_t i = 1; i < r.size(); ++i) {
                cout << ' ' << r[i];
            }
        }
        cout << '\n';
    }
    return 0;
}
