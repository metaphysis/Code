// An Antiarithmetic Permutation
// UVa ID: 11129
// Verdict: Accepted
// Submission Date: 2025-10-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
using namespace std;

// 递归生成反等差数列排列
vector<int> antiarithmetic_permutation(int n) {
    // 基准情况：当n=1时，直接返回[0]
    if (n == 1) return {0};
    
    // 将数字按奇偶索引分成两组
    vector<int> even, odd;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            even.push_back(i);  // 偶数索引位置
        else
            odd.push_back(i);   // 奇数索引位置
    }
    
    // 递归处理左右两组
    vector<int> left = antiarithmetic_permutation(even.size());
    vector<int> right = antiarithmetic_permutation(odd.size());
    
    // 将递归结果映射回原始值并合并
    vector<int> res;
    for (int idx : left) res.push_back(even[idx]);  // 左组结果
    for (int idx : right) res.push_back(odd[idx]);  // 右组结果
    
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    // 读取输入直到遇到0
    while (cin >> n && n != 0) {
        // 生成排列
        vector<int> perm = antiarithmetic_permutation(n);
        // 输出结果
        cout << n << ":";
        for (int i = 0; i < n; i++) {
            cout << " " << perm[i];
        }
        cout << "\n";
    }
    
    return 0;
}
