// The Programmer's Hex
// UVa ID: 734
// Verdict: Accepted
// Submission Date: 2026-01-02
// UVa Run Time: 0.120s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 六边形结构体，存储标签和六个边的值
struct Hexagon {
    char label;
    int edges[6];
} hexagons[7];

int pegs[7];            // pegs[i] = 六边形索引，表示第 i 个插槽放置的六边形编号
int rotation[7];        // rotation[i] = 旋转次数，表示第 i 个插槽六边形的旋转量
bool used[7];           // 标记六边形是否已被使用

// 邻接表：g[peg] = {(相邻插槽, {我的边索引, 对方的边索引}), ...}
vector<pair<int, pair<int, int>>> g[7];

// 初始化邻接关系
void initialize() {
    // 中心插槽 0 与外围插槽的邻接关系（双向）
    g[0].push_back({1, {0, 3}}); g[1].push_back({0, {3, 0}});
    g[0].push_back({2, {1, 4}}); g[2].push_back({0, {4, 1}});
    g[0].push_back({3, {2, 5}}); g[3].push_back({0, {5, 2}});
    g[0].push_back({4, {3, 0}}); g[4].push_back({0, {0, 3}});
    g[0].push_back({5, {4, 1}}); g[5].push_back({0, {1, 4}});
    g[0].push_back({6, {5, 2}}); g[6].push_back({0, {2, 5}});
    
    // 外围插槽之间的邻接关系（双向，顺时针方向）
    g[1].push_back({2, {2, 5}}); g[2].push_back({1, {5, 2}});
    g[2].push_back({3, {3, 0}}); g[3].push_back({2, {0, 3}});
    g[3].push_back({4, {4, 1}}); g[4].push_back({3, {1, 4}});
    g[4].push_back({5, {5, 2}}); g[5].push_back({4, {2, 5}});
    g[5].push_back({6, {0, 3}}); g[6].push_back({5, {3, 0}});
    g[6].push_back({1, {1, 4}}); g[1].push_back({6, {4, 1}});
}

// 获取旋转后的边值
inline int getEdge(int h, int r, int e) {
    return hexagons[h].edges[(e + r) % 6];
}

// 检查当前插槽与已放置插槽的约束
bool checkConstraints(int peg) {
    for (auto &e : g[peg]) {
        int otherPeg = e.first;
        if (pegs[otherPeg] == -1) continue;  // 相邻插槽未放置，跳过检查
        int edgeSelf = e.second.first;
        int edgeOther = e.second.second;
        int self = getEdge(pegs[peg], rotation[peg], edgeSelf);
        int other = getEdge(pegs[otherPeg], rotation[otherPeg], edgeOther);
        if (self != other) return false;
    }
    return true;
}

// 深度优先搜索（回溯）
bool dfs(int depth) {
    if (depth == 7) return true;  // 所有插槽都已放置
    for (int h = 0; h < 7; ++h) {
        if (used[h]) continue;     // 六边形已被使用
        used[h] = true;
        pegs[depth] = h;
        // 尝试所有 6 种旋转方向
        for (int r = 0; r < 6; ++r) {
            rotation[depth] = r;
            if (checkConstraints(depth))        // 检查约束
                if (dfs(depth + 1)) return true; // 继续搜索下一层
        }
        used[h] = false;           // 回溯
        pegs[depth] = -1;
    }
    return false;
}

int main() {
    initialize();                  // 初始化邻接关系
    string line[7];
    
    while (cin >> line[0]) {       // 读取第一个六边形
        // 读取剩余六个六边形
        for (int i = 1; i <= 6; i++) cin >> line[i];
        
        // 解析六边形数据
        for (int i = 0; i < 7; ++i) {
            hexagons[i].label = 'A' + i;
            for (int j = 0; j < 6; ++j)
                hexagons[i].edges[j] = line[i][j] - '0';
        }
        
        // 初始化状态
        fill(pegs, pegs + 7, -1);
        fill(rotation, rotation + 7, 0);
        fill(used, used + 7, false);
        
        // 搜索解决方案
        if (!dfs(0)) cout << "No solution possible\n";
        else {
            // 输出解决方案
            cout << "PEG   HEX   POSITION\n";
            cout << "---   ---   --------\n";
            for (int i = 0; i < 7; ++i) {
                int h = pegs[i], r = rotation[i];
                cout << ' ' << i << string(5, ' ');
                cout << hexagons[h].label << string(5, ' ');
                for (int e = 0; e < 6; ++e) cout << getEdge(h, r, e);
                cout << '\n';
            }
        }
        
        // 输出分隔符
        cout << string(36, '*') << '\n';
        
        // 读取数据集分隔符（*）
        cin >> line[0];
    }
    
    return 0;
}
