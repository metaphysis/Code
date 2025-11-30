// VivoParc
// UVa ID: 12684
// Verdict: Accepted
// Submission Date: 2025-11-29
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 105;
vector<int> graph[MAX_N];  // 邻接表存储图
int n;  // 围栏数量
int color[MAX_N];  // 每个围栏的颜色（物种）
bool foundSolution;  // 是否已找到解

// 检查当前围栏能否涂色c
bool isValid(int enclosure, int c) {
    for (int neighbor : graph[enclosure])
        if (color[neighbor] == c) return false;
    return true;
}

// 回溯搜索
void backtrack(int current) {
    if (foundSolution) return;  // 已找到解，直接返回
    
    if (current > n) {  // 所有围栏都已着色
        foundSolution = true;
        return;
    }
    
    // 尝试4种颜色
    for (int c = 1; c <= 4; c++) {
        if (isValid(current, c)) {
            color[current] = c;  // 选择颜色c
            backtrack(current + 1);  // 处理下一个围栏
            if (foundSolution) return;  // 已找到解，直接返回
            color[current] = 0;  // 回溯
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    bool firstDataSet = true;
    
    while (cin >> n) {
        // 读取空行（除了第一个数据集）
        if (!firstDataSet) getline(cin, line);
        firstDataSet = false;
        
        // 初始化
        for (int i = 1; i <= n; i++) {
            graph[i].clear();
            color[i] = 0;
        }
        foundSolution = false;
        
        // 读取可见性限制
        getline(cin, line);  // 读取第一行后的换行符
        while (getline(cin, line)) {
            if (line.empty()) break;  // 空行表示数据集结束
            
            // 解析 "a-b" 格式
            int a, b;
            sscanf(line.c_str(), "%d-%d", &a, &b);
            
            // 添加到图中（避免重复边）
            if (find(graph[a].begin(), graph[a].end(), b) == graph[a].end()) {
                graph[a].push_back(b);
                graph[b].push_back(a);
            }
        }
        
        // 回溯搜索
        backtrack(1);
        
        // 输出结果
        for (int i = 1; i <= n; i++)
            cout << i << " " << color[i] << endl;
        
        cout << endl;  // 数据集间输出空行
    }
    
    return 0;
}
