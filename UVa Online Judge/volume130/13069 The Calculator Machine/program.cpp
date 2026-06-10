// The Calculator Machine
// UVa ID: 13069
// Verdict: Accepted
// Submission Date: 2026-06-11
// UVa Run Time: 0.120s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 广度优先搜索求从 start 到 target 的最少按键次数
int bfs(int start, int target) {
    if (start == target) return 0;
    vector<int> visited(10000, 0);
    queue<pair<int, int>> q;
    q.push({start, 0});
    visited[start] = 1;
    
    while (!q.empty()) {
        int cur = q.front().first;
        int steps = q.front().second;
        q.pop();
        
        // 操作1: 加1
        int nxt = (cur + 1) % 10000;
        if (nxt == target) return steps + 1;
        if (!visited[nxt]) { visited[nxt] = 1; q.push({nxt, steps + 1}); }
        
        // 操作2: 乘2
        nxt = (cur * 2) % 10000;
        if (nxt == target) return steps + 1;
        if (!visited[nxt]) { visited[nxt] = 1; q.push({nxt, steps + 1}); }
        
        // 操作3: 除以3（整数除法）
        nxt = cur / 3;
        if (nxt == target) return steps + 1;
        if (!visited[nxt]) { visited[nxt] = 1; q.push({nxt, steps + 1}); }
    }
    return -1; // 理论上不会执行到这里，因为图强连通
}

int main() {
    int start, target;
    // 读取所有测试用例，每行两个整数
    while (cin >> start >> target) cout << bfs(start, target) << '\n';
    return 0;
}
