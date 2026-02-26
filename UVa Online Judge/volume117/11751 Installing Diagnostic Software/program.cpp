// Installing Diagnostic Software
// UVa ID: 11751
// Verdict: Accepted
// Submission Date: 2026-02-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 边的结构体，big 是大节点，small 是小节点
struct Edge {
    int big;
    int small;
};

// 比较函数：先按 big 降序，big 相同时按 small 降序
bool cmp(const Edge& a, const Edge& b) {
    if (a.big != b.big) 
        return a.big > b.big;
    return a.small > b.small;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    while (cin >> n >> m && (n || m)) {
        vector<Edge> edges(m);
        vector<bool> chosen(n, false);
        
        // 读入边，并确保 big 是大节点，small 是小节点
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            if (a >= b) {
                edges[i].big = a;
                edges[i].small = b;
            } else {
                edges[i].big = b;
                edges[i].small = a;
            }
        }
        
        // 按 big 从大到小排序
        sort(edges.begin(), edges.end(), cmp);
        
        // 贪心选择：如果大节点没被选，则选小节点
        for (const auto& e : edges) {
            if (!chosen[e.big]) {
                chosen[e.small] = true;
            }
        }
        
        // 输出结果
        for (int i = 0; i < n; ++i) 
            cout << (chosen[i] ? '1' : '0');
        cout << '\n';
    }
    
    return 0;
}
