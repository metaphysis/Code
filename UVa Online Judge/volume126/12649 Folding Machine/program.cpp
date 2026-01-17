// Folding Machine
// UVa ID: 12649
// Verdict: Accepted
// Submission Date: 2026-01-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> target;  // 目标磁带
set<vector<int>> visited;  // 已访问状态集合

// 检查当前磁带是否匹配目标（考虑反转）
bool checkMatch(const vector<int>& tape) {
    if (tape.size() != m) return false;
    
    // 检查正序匹配
    bool match1 = true;
    for (int i = 0; i < m; i++) {
        if (tape[i] != target[i]) {
            match1 = false;
            break;
        }
    }
    if (match1) return true;
    
    // 检查反序匹配
    for (int i = 0; i < m; i++) {
        if (tape[i] != target[m - 1 - i]) {
            return false;
        }
    }
    return true;
}

// 深度优先搜索
bool dfs(vector<int> tape) {
    // 如果磁带长度等于目标长度，检查是否匹配
    if (tape.size() == m) return checkMatch(tape);
    
    // 如果磁带长度小于目标长度，不可能匹配
    if (tape.size() < m) return false;
    
    // 如果已访问过该状态，跳过
    if (visited.count(tape)) return false;
    visited.insert(tape);
    
    int len = tape.size();
    
    // 尝试所有折叠位置
    for (int foldPos = 1; foldPos < len; foldPos++) {
        // 向左折叠：右侧覆盖左侧
        vector<int> newTape1;
        int i = foldPos - 1, j = foldPos;
        
        // 处理重叠部分
        while (i >= 0 && j < len) {
            newTape1.push_back(tape[i] + tape[j]);
            i--;
            j++;
        }
        
        // 处理左侧剩余部分
        while (i >= 0) {
            newTape1.push_back(tape[i]);
            i--;
        }
        
        // 处理右侧剩余部分
        while (j < len) {
            newTape1.push_back(tape[j]);
            j++;
        }
        
        // 反转结果，因为右侧覆盖了左侧
        reverse(newTape1.begin(), newTape1.end());
        
        if (dfs(newTape1)) return true;
        
        // 向右折叠：左侧覆盖右侧
        vector<int> newTape2;
        i = foldPos - 1, j = foldPos;
        
        // 处理重叠部分
        while (i >= 0 && j < len) {
            newTape2.push_back(tape[i] + tape[j]);
            i--;
            j++;
        }
        
        // 处理左侧剩余部分
        while (i >= 0) {
            newTape2.push_back(tape[i]);
            i--;
        }
        
        // 处理右侧剩余部分
        while (j < len) {
            newTape2.push_back(tape[j]);
            j++;
        }
        
        // 注意：这里不需要反转，因为左侧覆盖右侧时顺序保持不变
        
        if (dfs(newTape2)) return true;
    }
    
    return false;
}

int main() {
    // 处理多个测试用例，直到文件结束
    while (cin >> n) {
        vector<int> tape(n);
        long long sumInput = 0, sumTarget = 0;
        
        // 读入输入磁带并计算总和
        for (int i = 0; i < n; i++) {
            cin >> tape[i];
            sumInput += tape[i];
        }
        
        // 读入输出磁带并计算总和
        cin >> m;
        target.resize(m);
        for (int i = 0; i < m; i++) {
            cin >> target[i];
            sumTarget += target[i];
        }
        
        // 快速检查：总和必须相等
        if (sumInput != sumTarget) {
            cout << "N" << endl;
            continue;
        }
        
        // 特殊情况：M = 1时，只需检查总和
        if (m == 1) {
            cout << (sumInput == target[0] ? "S" : "N") << endl;
            continue;
        }
        
        // 初始化并开始搜索
        visited.clear();
        bool result = dfs(tape);
        cout << (result ? "S" : "N") << endl;
    }
    
    return 0;
}
