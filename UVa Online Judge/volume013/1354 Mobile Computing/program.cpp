// Mobile Computing
// UVa ID: 1354
// Verdict: Accepted
// Submission Date: 2025-10-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 表示一个子树的状态：重量、左半宽度、右半宽度
struct Node {
    double weight, left, right;
    Node(double w, double l, double r) : weight(w), left(l), right(r) {}
};

vector<Node> dp[1 << 6];  // dp[mask] 存储该掩码对应的所有可能子树状态
int s;                    // 石头数量
vector<int> w;            // 石头重量
double room;              // 房间宽度
bool visited[1 << 6];     // 标记状态是否已计算

// 深度优先搜索计算所有可能的子树组合
void dfs(int mask) {
    if (visited[mask]) return;  // 已计算过，直接返回
    visited[mask] = true;
    
    // 单个石头的情况
    if (__builtin_popcount(mask) == 1) {
        int i = __builtin_ctz(mask);  // 找到最低位的 1 对应的石头索引
        dp[mask].push_back(Node(w[i], 0.0, 0.0));
        return;
    }
    
    // 枚举所有非空真子集进行合并
    for (int leftMask = (mask - 1) & mask; leftMask > 0; leftMask = (leftMask - 1) & mask) {
        int rightMask = mask ^ leftMask;  // 补集作为右子树
        dfs(leftMask);   // 计算左子树
        dfs(rightMask);  // 计算右子树
        
        // 合并左右子树的所有可能组合
        for (const Node& L : dp[leftMask]) {
            for (const Node& R : dp[rightMask]) {
                double totalWeight = L.weight + R.weight;
                double a = R.weight / totalWeight;  // 左子树重心到整体重心的距离
                double b = L.weight / totalWeight;  // 右子树重心到整体重心的距离
                
                // 计算新的左右半宽度
                double leftWidth = max(a + L.left, R.left - b);
                double rightWidth = max(b + R.right, L.right - a);
                
                // 添加新状态
                dp[mask].push_back(Node(totalWeight, leftWidth, rightWidth));
            }
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> room;
        cin >> s;
        w.resize(s);
        for (int i = 0; i < s; i++) cin >> w[i];
        
        int total = (1 << s) - 1;  // 所有石头的位掩码
        // 初始化
        for (int i = 0; i <= total; i++) {
            dp[i].clear();
            visited[i] = false;
        }
        
        // 计算所有可能的组合
        dfs(total);
        
        // 寻找满足条件的最大宽度
        double best = -1.0;
        for (const Node& nd : dp[total]) {
            double width = nd.left + nd.right;
            if (width < room - 1e-9) {  // 考虑浮点精度误差
                if (width > best) best = width;
            }
        }
        
        // 输出结果
        if (best < 0) {
            cout << "-1\n";
        } else {
            cout << fixed << setprecision(15) << best << "\n";
        }
    }
    return 0;
}
