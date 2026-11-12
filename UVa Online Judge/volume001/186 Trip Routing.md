[UVa 186 Trip Routing](https://blog.csdn.net/metaphysis/article/details/160910444)

## 题目分析

本题是一个典型的最短路径问题。加州汽车俱乐部（CCC）希望为会员提供旅行路线服务，需要根据给定的高速公路段信息，计算两个城市之间的最短路线。

**输入**分为两部分：

1. **地图数据**：包含若干条公路段，每行格式为 `起点城市,终点城市,路线名称,里程` 。以空行结束。
2. **查询数据**：每行一个查询，格式为 `出发城市,目标城市` 。保证两个城市都出现在地图数据中，且存在连通路径。以文件结束符结束。

**输出**要求：每个查询输出一份报告，格式与样例完全一致。每份报告前空两行（包括第一份报告）。

**数据规模**：最多 $100$ 个城市，最多 $200$ 条公路段，最短路径总里程可存入 $16$ 位整数。

## 解题思路

### 核心算法

由于需要计算**单源最短路径**，且图是无向加权图（公路段是双向的），我们可以使用 **$\texttt{Dijkstra}$ 算法**。题目保证边权为正整数，$\texttt{Dijkstra}$ 算法在此场景下是最优选择。

### 数据结构设计

- **城市索引映射**：使用 `map<string, int>` 将城市名称映射为整数索引，方便存储和访问。
- **邻接表存储**：使用 `vector<vector<segment>> routes` 存储图。每个 `segment` 结构体包含：
  - `index`：邻接城市的索引
  - `startCity`、`endCity`：当前边的起点和终点名称（用于输出）
  - `route`：路线名称
  - `miles`：里程数
- **$\texttt{Dijkstra}$ 辅助数组**：
  - `parent`：记录最短路径中每个节点的前驱节点及对应的边索引，用于路径回溯
  - `distances`：记录起点到每个节点的最短距离
  - `visited`：标记节点是否已确定最短距离

### 路径输出

使用递归函数 `findPath` 从终点回溯到起点，按照路径顺序逐条输出。每次输出一段路段的信息：起点、终点、路线名称、里程，并累加总里程。

## 代码实现

```cpp
// Trip Routing
// UVa ID: 186
// Verdict: Accepted
// Submission Date: 2016-03-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 公路段结构体，表示一条有向边（实际存储时会存储双向）
struct segment {
    int index;          // 邻接城市在 cityName 中的索引
    string startCity;   // 起点城市名称
    string endCity;     // 终点城市名称
    string route;       // 路线名称
    int miles;          // 里程
};

vector<vector<segment>> routes;   // 邻接表，存储整个图
vector<string> cityName;           // 城市名称列表，索引即城市编号
map<string, int> cityIndex;        // 城市名称到索引的映射
vector<pair<int, int>> parent;     // 前驱节点及对应边索引，用于路径回溯
vector<int> distances;             // 最短距离
vector<bool> visited;              // 访问标记

// 去除字符串首尾的空白字符
void trim(string & line) {
    // 去除尾部空白
    for (int i = line.length() - 1; i >= 0; i--) {
        if (isblank(line[i]))
            line.erase(line.begin() + i);
        else
            break;
    }

    // 去除头部空白
    while (line.length()) {
        if (isblank(line.front()))
            line.erase(line.begin());
        else
            break;
    }
}

// 输出报告的表头
void printHeader() {
    cout << left << setw(20) << "From" << " " << left << setw(20) << "To" <<" ";
    cout << left << setw(10) << "Route" << " " << left << setw(5) << "Miles" << "\n";
    cout << string(20, '-') << " " << string(20, '-') << " ";
    cout << string(10, '-') << " " << string(5, '-') << "\n";
}

int totalMiles = 0;  // 累计总里程

// 递归回溯输出最短路径（从起点到终点）
void findPath(int start, int end) {
    // 如果不是起点，继续递归到前驱节点
    if (start != parent[end].first)
        findPath(start, parent[end].first);

    // 输出当前路段信息
    cout << left << setw(20)
         << routes[parent[end].first][parent[end].second].startCity
         << " "
         << left << setw(20)
         << routes[parent[end].first][parent[end].second].endCity
         << " "
         << left << setw(10)
         << routes[parent[end].first][parent[end].second].route
         << " "
         << right << setw(5)
         << routes[parent[end].first][parent[end].second].miles
         << "\n";

    // 累加里程
    totalMiles += routes[parent[end].first][parent[end].second].miles;
}

// 输出报告的底部（总计行）
void printFooter() {
    cout << string(53, ' ') << string(5, '-') << "\n";
    cout << string(42, ' ') << left << setw(10) << "Total";
    cout << " ";
    cout << right << setw(5) << totalMiles << "\n";
}

// Dijkstra 算法，计算从起点 start 到所有节点的最短路径
void dijkstra(int start) {
    // 初始化辅助数组
    parent.clear();
    visited.clear();
    distances.clear();

    for (int i = 0; i < routes.size(); i++) {
        parent.push_back(make_pair(-1, -1));   // 前驱初始为 -1
        visited.push_back(false);               // 未访问
        distances.push_back(numeric_limits<int>::max()); // 距离设为无穷大
    }

    distances[start] = 0;
    int minDistance;

    // 主循环，每次确定一个节点的最短距离
    while (visited[start] == false) {
        visited[start] = true;  // 标记当前节点已确定

        // 松弛操作：遍历当前节点的所有邻接边
        for (int i = 0; i < routes[start].size(); i++) {
            int index = routes[start][i].index;  // 邻接城市索引
            if (visited[index] == false) {
                if (distances[start] + routes[start][i].miles < distances[index]) {
                    distances[index] = distances[start] + routes[start][i].miles;
                    parent[index] = make_pair(start, i);  // 记录前驱节点和边索引
                }
            }
        }

        // 选择未访问节点中距离最小的节点作为下一个起点
        start = 0;
        minDistance = numeric_limits<int>::max();
        for (int i = 0; i < routes.size(); i++)
            if (visited[i] == false && minDistance > distances[i]) {
                minDistance = distances[i];
                start = i;
            }
    }
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);

    string line;

    // ========== 读取地图数据 ==========
    while (getline(cin, line)) {
        trim(line);
        if (line.length() == 0)  // 空行表示地图数据结束
            break;

        int miles;
        string startCity, endCity, road;

        // 解析 CSV 格式的行：起点,终点,路线,里程
        int first = 0, second = line.find(',', first);
        startCity = line.substr(first, second);
        first = second + 1, second = line.find(',', first);
        endCity = line.substr(first, second - first);
        first = second + 1, second = line.find(',', first);
        road = line.substr(first, second - first);
        miles = stoi(line.substr(second + 1));

        // 将起点城市加入映射（若不存在）
        if (cityIndex.count(startCity) == 0) {
            cityName.push_back(startCity);
            cityIndex[startCity] = cityName.size() - 1;
            vector<segment> segments;
            routes.push_back(segments);
        }

        // 将终点城市加入映射（若不存在）
        if (cityIndex.count(endCity) == 0) {
            cityName.push_back(endCity);
            cityIndex[endCity] = cityName.size() - 1;
            vector<segment> segments;
            routes.push_back(segments);
        }

        // 添加两条有向边（图是无向的）
        routes[cityIndex[startCity]].push_back((segment)
            {cityIndex[endCity], startCity, endCity, road, miles}
        );
        routes[cityIndex[endCity]].push_back((segment)
            {cityIndex[startCity], endCity, startCity, road, miles}
        );
    }

    // ========== 处理查询 ==========
    while (getline(cin, line)) {
        trim(line);

        // 解析查询：起点,终点
        int index = line.find(',');
        int start = cityIndex[line.substr(0, index)];
        int end = cityIndex[line.substr(index + 1)];

        // 计算最短路径
        dijkstra(start);

        // 输出报告（前空两行）
        cout << "\n\n";
        printHeader();
        totalMiles = 0;
        findPath(start, end);
        printFooter();
    }

    return 0;
}
```

## 要点总结

1. **双向存储**：由于公路段是双向的，每条输入数据需要向邻接表中添加两条方向相反的边。
2. **路径记录与回溯**：在 $\texttt{Dijkstra}$ 算法中，每次更新最短距离时同时记录前驱节点和对应的边索引，以便最终回溯输出完整路径。
3. **输出格式**：严格按照题目要求，使用 `setw` 控制字段宽度，确保对齐。每份报告前输出两个换行符。
4. **边界处理**：使用 `numeric_limits<int>::max()` 初始化距离，确保无穷大足够大。
