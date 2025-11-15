// Guess
// UVa ID: 1423
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.820s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int n;
char sign[11][11]; // 存储符号矩阵，sign[i][j] 对应 S_{ij} (1<=i<=j<=n)
vector<int> a;     // 当前尝试的序列，a[1..n]
vector<int> prefix;// 前缀和数组，prefix[k] = a1+...+ak
bool found;        // 标记是否已找到解

/**
 * 检查新加入元素 a[k] 后，所有包含 k 的区间是否满足符号约束
 * 只需要检查区间 [i, k]，其中 1 <= i <= k
 */
bool check(int k) {
    for (int i = 1; i <= k; i++) {
        // 计算区间和 sum(i, k) = prefix[k] - prefix[i-1]
        int sum = prefix[k] - prefix[i - 1];
        char expected = sign[i][k]; // 符号矩阵中期望的符号
        
        // 检查实际符号是否与期望一致
        if (expected == '+' && sum <= 0) return false;
        if (expected == '-' && sum >= 0) return false;
        if (expected == '0' && sum != 0) return false;
    }
    return true;
}

/**
 * 深度优先搜索构造序列
 * k: 当前要确定第 k 个元素 a[k]
 */
void dfs(int k) {
    if (found) return; // 如果已找到解，直接返回
    if (k == n + 1) {  // 所有元素都已确定，找到解
        found = true;
        return;
    }
    
    // 根据对角线元素 S[k][k] 确定 a[k] 的取值范围
    int start, end;
    char diag = sign[k][k];
    
    if (diag == '+') {
        start = 1; end = 10;   // a[k] 为正数
    } else if (diag == '-') {
        start = -10; end = -1; // a[k] 为负数
    } else { // diag == '0'
        start = 0; end = 0;    // a[k] 必须为 0
    }
    
    // 枚举 a[k] 的所有可能取值
    for (int val = start; val <= end; val++) {
        a[k] = val;
        prefix[k] = prefix[k - 1] + val; // 更新前缀和
        
        // 只检查包含新元素的区间
        if (check(k)) {
            dfs(k + 1); // 继续确定下一个元素
            if (found) return; // 如果找到解，立即返回
        }
    }
}

int main() {
    int T;
    cin >> T; // 读取测试用例数量
    
    while (T--) {
        cin >> n; // 读取序列长度
        string s;
        cin >> s; // 读取符号矩阵字符串
        
        // 解析符号矩阵字符串，填充右上三角部分
        int idx = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                sign[i][j] = s[idx++];
            }
        }
        
        // 初始化
        a.resize(n + 1);
        prefix.resize(n + 1);
        prefix[0] = 0; // 前缀和基准
        found = false;
        
        // 开始搜索
        dfs(1);
        
        // 输出结果
        for (int i = 1; i <= n; i++) {
            if (i > 1) cout << " ";
            cout << a[i];
        }
        cout << endl;
    }
    return 0;
}
