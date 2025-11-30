// Rectilinear Polygon
// UVa ID: 11106
// Verdict: Accepted
// Submission Date: 2025-11-30
// UVa Run Time: 1.730s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template<>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };
}

struct Segment {
    int id, x1, x2, y;
    bool isHorizontal;
    Segment(int id, int x1, int x2, int y, bool horizontal) 
        : id(id), x1(x1), x2(x2), y(y), isHorizontal(horizontal) {}
};

// 检查多边形是否简单（无洞且不自交）
bool isSimplePolygon(vector<Segment>& horizontalSegments, vector<Segment>& verticalSegments) {
    // 构建邻接表
    unordered_map<Point, vector<Point>> graph;
    
    // 添加水平边
    for (auto& seg : horizontalSegments) {
        Point p1(seg.x1, seg.y);
        Point p2(seg.x2, seg.y);
        graph[p1].push_back(p2);
        graph[p2].push_back(p1);
    }
    
    // 添加垂直边
    for (auto& seg : verticalSegments) {
        Point p1(seg.x1, seg.y);
        Point p2(seg.x1, seg.x2);  // x2存储的是另一个y坐标
        graph[p1].push_back(p2);
        graph[p2].push_back(p1);
    }
    
    // 检查每个顶点的度数是否为2
    for (auto& entry : graph) {
        if (entry.second.size() != 2) {
            return false;
        }
    }
    
    // 检查是否形成单个环（通过DFS遍历）
    if (graph.empty()) return false;
    
    Point start = graph.begin()->first;
    unordered_set<Point> visited;
    Point current = start;
    Point prev = start;
    int count = 0;
    
    do {
        if (visited.count(current)) {
            // 提前遇到已访问点，说明有多个环
            return false;
        }
        visited.insert(current);
        count++;
        
        // 找到下一个点（排除前一个点）
        Point next;
        for (Point neighbor : graph[current]) {
            if (!(neighbor == prev)) {
                next = neighbor;
                break;
            }
        }
        
        prev = current;
        current = next;
    } while (!(current == start) && count <= graph.size());
    
    // 如果遍历了所有顶点且回到起点，说明是单个环
    return count == graph.size() && current == start;
}

// 扫描线算法检测线段是否仅相交于端点
bool checkNoImproperIntersections(vector<Segment>& horizontalSegments, 
                                  vector<Segment>& verticalSegments) {
    unordered_map<int, Segment*> verticalMap;
    for (auto& seg : verticalSegments) 
        verticalMap[seg.id] = &seg;
    
    vector<tuple<int, int, int, int>> events;
    
    for (auto& seg : horizontalSegments) {
        events.emplace_back(seg.x1, 1, seg.y, seg.id);
        events.emplace_back(seg.x2, 1, seg.y, seg.id);
    }
    
    for (auto& seg : verticalSegments) {
        int y1 = seg.y;
        int y2 = seg.x2;
        events.emplace_back(seg.x1, 0, min(y1, y2), seg.id);
        events.emplace_back(seg.x1, 2, max(y1, y2), seg.id);
    }
    
    sort(events.begin(), events.end());
    
    set<pair<int, int>> activeVertical;
    
    for (auto& event : events) {
        int x = get<0>(event);
        int type = get<1>(event);
        int y = get<2>(event);
        int id = get<3>(event);
        
        if (type == 0) {
            activeVertical.insert({y, id});
        } else if (type == 2) {
            activeVertical.erase({y, id});
        } else if (type == 1) {
            for (auto& vert : activeVertical) {
                int vertId = vert.second;
                Segment* verticalSeg = verticalMap[vertId];
                
                if (verticalSeg->x1 == x) {
                    int vertMinY = min(verticalSeg->y, verticalSeg->x2);
                    int vertMaxY = max(verticalSeg->y, verticalSeg->x2);
                    
                    if (y > vertMinY && y < vertMaxY) {
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

bool solveTestCase() {
    int n;
    cin >> n;
    vector<Point> points(n);
    map<int, int> xCount, yCount;
    
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        xCount[points[i].x]++;
        yCount[points[i].y]++;
    }
    
    for (auto& p : xCount) 
        if (p.second % 2 != 0) return false;
    for (auto& p : yCount) 
        if (p.second % 2 != 0) return false;
    
    map<int, vector<int>> byY;
    for (auto& p : points) 
        byY[p.y].push_back(p.x);
    
    vector<Segment> horizontalSegments, verticalSegments;
    int segmentId = 0;
    long long perimeter = 0;
    
    for (auto& group : byY) {
        vector<int>& xs = group.second;
        sort(xs.begin(), xs.end());
        for (size_t i = 0; i < xs.size(); i += 2) {
            int x1 = xs[i], x2 = xs[i + 1];
            horizontalSegments.emplace_back(segmentId++, x1, x2, group.first, true);
            perimeter += (x2 - x1);
        }
    }
    
    map<int, vector<int>> byX;
    for (auto& p : points) 
        byX[p.x].push_back(p.y);
    
    for (auto& group : byX) {
        vector<int>& ys = group.second;
        sort(ys.begin(), ys.end());
        for (size_t i = 0; i < ys.size(); i += 2) {
            int y1 = ys[i], y2 = ys[i + 1];
            verticalSegments.emplace_back(segmentId++, group.first, y2, y1, false);
            perimeter += (y2 - y1);
        }
    }
    
    // 检查是否无自交且是简单多边形
    if (!checkNoImproperIntersections(horizontalSegments, verticalSegments) || 
        !isSimplePolygon(horizontalSegments, verticalSegments)) {
        return false;
    }
    
    cout << perimeter << endl;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int testCases;
    cin >> testCases;
    
    while (testCases--) {
        if (!solveTestCase()) 
            cout << -1 << endl;
    }
    
    return 0;
}
