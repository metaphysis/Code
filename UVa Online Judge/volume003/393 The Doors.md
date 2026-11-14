[UVa 393 The Doors](https://blog.csdn.net/metaphysis/article/details/161705448)

## 题目描述

你需要找到穿过一个有障碍墙的房间的最短路径长度。房间边界为 $x=0$、$x=10$、$y=0$ 和 $y=10$。路径的起点和终点始终是 $(0,5)$ 和 $(10,5)$。房间内有 $0$ 到 $18$ 堵垂直的墙，每堵墙上有两个门洞。图例展示了一个这样的房间以及最短路径。

### 输入格式

第一行包含内墙的数量 $n$。接下来 $n$ 行，每行包含五个实数：第一个数是墙的 $x$ 坐标（$0 < x < 10$），其余四个是墙上两个门洞端点的 $y$ 坐标。墙的 $x$ 坐标递增排列，每行内的 $y$ 坐标也递增排列。输入以 $n = -1$ 结束。

### 输出格式

对于每个房间，输出一行，包含最短路径长度，保留两位小数，无空格。

### 样例输入

```
1
5 4 6 7 8
2
4 2 7 8 9
7 3 4.5 6 7
-1
```

### 样例输出

```
10.00
10.06
```

---

## 题目分析

### 问题的本质

这是一个**带障碍的最短路径**问题。房间内有若干垂直墙，每堵墙上有两个门洞（开口）。需要从 $(0,5)$ 走到 $(10,5)$，不能穿过墙的实体部分，只能从门洞通过。

### 几何建模

- 将起点、终点、所有墙上门洞的端点视为图中的节点
- 如果两个节点之间的线段不与任何墙的实体部分相交，则它们之间有一条边
- 边的权重为两点间的欧氏距离
- 使用 $\texttt{Dijkstra}$ 算法求最短路径

### 关键点

- 墙的实体部分由 $[0, y_1]$、$[y_2, y_3]$、$[y_4, 10]$ 组成（门洞在 $(y_1, y_2)$ 和 $(y_3, y_4)$）
- 需要检查线段是否与墙的实体部分相交（即是否穿过墙）
- 起点 $(0,5)$，终点 $(10,5)$

---
## 参考代码

```cpp
// The Doors
// UVa ID: 393
// Verdict: Accepted
// Submission Date: 2016-07-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1E-10;

struct point {
    double x, y;
    int wall;      // 所属墙编号，0 为起点，n+1 为终点
    bool is_valid;
};

struct line {
    double a, b, c;  // ax + by + c = 0
};

struct edge {
    int to;
    double weight;
};

// 两点转直线
line pointsToLine(point start, point end) {
    line lr;
    if (fabs(start.x - end.x) <= EPSILON) {
        lr.a = 1.0;
        lr.b = 0.0;
        lr.c = -start.x;
    } else {
        lr.a = -(start.y - end.y) / (start.x - end.x);
        lr.b = 1.0;
        lr.c = -lr.a * start.x - start.y;
    }
    return lr;
}

// 计算直线在给定 x 处的 y 值
double getYAtLine(line lr, double x) {
    return (-lr.c - lr.a * x) / lr.b;
}

// 判断两条直线是否平行
bool isParallelLine(line line1, line line2) {
    return fabs(line1.a - line2.a) <= EPSILON && fabs(line1.b - line2.b) <= EPSILON;
}

// 判断两条直线是否重合
bool isSameLine(line line1, line line2) {
    return isParallelLine(line1, line2) && fabs(line1.c - line2.c) <= EPSILON;
}

// 求两直线交点
point intersect(line line1, line line2) {
    point p;
    if (isParallelLine(line1, line2)) {
        return {0.0, 0.0, false};
    }
    if (isSameLine(line1, line2)) {
        if (fabs(line1.a) > EPSILON) {
            p.x = -line1.c / line1.a;
            p.y = 0.0;
        } else {
            p.x = 0.0;
            p.y = -line1.c / line1.b;
        }
        p.is_valid = true;
        return p;
    }
    p.x = (line2.b * line1.c - line1.b * line2.c) / (line2.a * line1.b - line1.a * line2.b);
    if (fabs(line1.b) > EPSILON)
        p.y = -(line1.a * p.x + line1.c) / line1.b;
    else
        p.y = -(line2.a * p.x + line2.c) / line2.b;
    p.is_valid = true;
    return p;
}

// 包围盒测试
bool pointInBox(point p, point a, point b) {
    return (p.x >= min(a.x, b.x) - EPSILON && p.x <= max(a.x, b.x) + EPSILON &&
            p.y >= min(a.y, b.y) - EPSILON && p.y <= max(a.y, b.y) + EPSILON);
}

// 判断两点间线段是否与墙的实体部分相交
bool segmentClear(point& a, point& b, map<int, double>& walls, 
                  map<int, vector<pair<double, double>>>& doors) {
    if (a.wall >= b.wall) return false;
    // 相邻墙可直接连接
    if (b.wall == a.wall + 1) return true;
    
    line lr = pointsToLine(a, b);
    for (int k = a.wall + 1; k <= b.wall - 1; k++) {
        double y = getYAtLine(lr, walls[k]);
        bool inDoor = false;
        for (auto& door : doors[k]) {
            if (y > door.first + EPSILON && y < door.second - EPSILON) {
                inDoor = true;
                break;
            }
        }
        if (!inDoor) return false;
    }
    return true;
}

double distanceOfPoints(point& a, point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n, n >= 0) {
        // 无墙的情况
        if (n == 0) {
            cout << "10.00" << endl;
            continue;
        }
        
        map<int, double> walls;
        map<int, vector<pair<double, double>>> doors;
        vector<point> points;
        
        points.push_back({0.0, 5.0, 0, false});  // 起点
        
        // 读取墙并构建节点
        for (int i = 1; i <= n; i++) {
            double x, y1, y2, y3, y4;
            cin >> x >> y1 >> y2 >> y3 >> y4;
            walls[i] = x;
            doors[i] = {{y1, y2}, {y3, y4}};
            // 四个门洞端点
            points.push_back({x, y1, i, false});
            points.push_back({x, y2, i, false});
            points.push_back({x, y3, i, false});
            points.push_back({x, y4, i, false});
        }
        points.push_back({10.0, 5.0, n + 1, false});  // 终点
        
        // 建图
        vector<vector<edge>> edges(points.size());
        for (int i = 0; i < points.size(); i++) {
            for (int j = points.size() - 1; j >= 0; j--) {
                if (points[j].wall <= points[i].wall) break;
                if (segmentClear(points[i], points[j], walls, doors)) {
                    double dist = distanceOfPoints(points[i], points[j]);
                    edges[i].push_back({j, dist});
                    edges[j].push_back({i, dist});
                }
            }
        }
        
        // Dijkstra
        vector<double> distances(points.size(), 1e9);
        vector<bool> visited(points.size(), false);
        distances[0] = 0;
        
        for (int step = 0; step < points.size(); step++) {
            int current = -1;
            double minDist = 1e9;
            for (int i = 0; i < points.size(); i++) {
                if (!visited[i] && distances[i] < minDist) {
                    minDist = distances[i];
                    current = i;
                }
            }
            if (current == -1) break;
            visited[current] = true;
            
            for (auto& e : edges[current]) {
                if (!visited[e.to] && distances[current] + e.weight < distances[e.to]) {
                    distances[e.to] = distances[current] + e.weight;
                }
            }
        }
        
        cout << fixed << setprecision(2) << distances.back() << endl;
    }
    
    return 0;
}
```
