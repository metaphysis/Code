// Find The Multiple
// UVa ID: 1189
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

string findMultiple(int n) {
    // 特殊情况：n=1 时直接返回 "1"
    if (n == 1) return "1";
    
    // BFS 队列，存储 (余数, 对应的数字字符串)
    queue<pair<int, string>> q;
    // 访问标记数组，记录每个余数是否已被访问
    vector<bool> visited(n, false);
    
    // 从数字 1 开始搜索
    q.push({1 % n, "1"});
    visited[1 % n] = true;
    
    while (!q.empty()) {
        // 取出队首元素
        int rem = q.front().first;
        string numStr = q.front().second;
        q.pop();
        
        // 如果余数为 0，找到解
        if (rem == 0) {
            return numStr;
        }
        
        // 尝试在当前数字末尾加 0
        int newRem = (rem * 10) % n;
        if (!visited[newRem]) {
            visited[newRem] = true;
            q.push({newRem, numStr + "0"});
        }
        
        // 尝试在当前数字末尾加 1
        newRem = (rem * 10 + 1) % n;
        if (!visited[newRem]) {
            visited[newRem] = true;
            q.push({newRem, numStr + "1"});
        }
    }
    
    return ""; // 理论上不会执行到这里
}

int main() {
    int n;
    // 读取输入直到遇到 0
    while (cin >> n && n != 0) {
        cout << findMultiple(n) << endl;
    }
    return 0;
}
