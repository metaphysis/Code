// The House Of Santa Claus
// UVa ID: 291
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> edges(6);  // 邻接表，存储图的连接关系，顶点编号从1到5
int drawed[6][6] = { 0 };      // 边是否已绘制，drawed[i][j]=1 表示边(i,j)已走过
vector<int> path;              // 存储当前路径上的顶点序列

// 深度优先搜索，index表示当前所在顶点，visited表示已经走过的边数
void dfs(int index, int visited) {
    // 如果已经走完了全部8条边，输出当前路径
    if (visited == 8) {
        path.push_back(index);                     // 将最后一个顶点加入路径
        for (int i = 0; i < path.size(); i++)
            cout << path[i];                       // 输出顶点编号，不换行
        cout << endl;                              // 输出完一条路径后换行
        path.erase(path.end() - 1);                // 移除最后一个顶点，回溯
        return;
    }
    // 遍历当前顶点的所有邻接点
    for (int i = 0; i < edges[index].size(); i++) {
        // 如果当前边还没有被绘制过（无向图需检查两个方向）
        if (drawed[index][edges[index][i]] == 0 && drawed[edges[index][i]][index] == 0) {
            // 标记这条边为已绘制（两个方向都标记）
            drawed[index][edges[index][i]] = drawed[edges[index][i]][index] = 1;
            // 将当前顶点加入路径
            path.push_back(index);
            // 递归搜索下一个顶点，已走边数+1
            dfs(edges[index][i], visited + 1);
            // 回溯：移除当前顶点
            path.erase(path.end() - 1);
            // 回溯：清除边的标记，以便其他路径使用
            drawed[index][edges[index][i]] = 0;
            drawed[edges[index][i]][index] = 0;
        }
    }
}

int main() {
    cin.tie(0); cin.sync_with_stdio(false);
    // 构建无向图，顶点编号1~5，按照题目中房子的形状定义连接关系
    edges[1].push_back(2); edges[1].push_back(3); edges[1].push_back(5);
    edges[2].push_back(1); edges[2].push_back(3); edges[2].push_back(5);
    edges[3].push_back(1); edges[3].push_back(2); edges[3].push_back(4); edges[3].push_back(5);
    edges[4].push_back(3); edges[4].push_back(5);
    edges[5].push_back(1); edges[5].push_back(2); edges[5].push_back(3); edges[5].push_back(4);
    // 从顶点1出发，初始已走边数为0
    dfs(1, 0);
    return 0;
}
