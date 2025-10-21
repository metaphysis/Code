// Equilibrium Mobile
// UVa ID: 12166
// Verdict: Accepted
// Submission Date: 2025-10-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <map>
#include <cctype>
using namespace std;

string s; // 存储输入字符串
int idx;  // 当前解析位置
map<long long, int> freq; // 统计有效重量的出现频率

void dfs(int depth) {
    if (s[idx] == '[') {
        // 遇到杆，递归处理左右子树
        idx++; // 跳过 '['
        dfs(depth + 1);
        idx++; // 跳过 ','
        dfs(depth + 1);
        idx++; // 跳过 ']'
    } else {
        // 读取叶节点的重量值
        long long num = 0;
        while (idx < s.size() && isdigit(s[idx])) {
            num = num * 10 + (s[idx] - '0');
            idx++;
        }
        // 计算有效重量并更新频率
        freq[num << depth]++;
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> s;
        idx = 0;
        freq.clear();
        dfs(0); // 从深度0开始解析
        
        int total = 0, max_count = 0;
        // 统计总叶节点数和最大频率
        for (auto& p : freq) {
            total += p.second;
            if (p.second > max_count) max_count = p.second;
        }
        // 输出最少修改次数
        cout << total - max_count << endl;
    }
    return 0;
}
