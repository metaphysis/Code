// Return of the Jedi
// UVa ID: 10224
// Verdict: Accepted
// Submission Date: 2025-10-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 常量定义
const double PI = 2 * acos(0.0);          // 圆周率
const double INF = 1e20;                  // 无穷大
const double EPS = 1e-9;                  // 浮点数比较容差
const double SPEED = 200.0;               // 速度：200英里/小时

// 二维点结构体
struct Point {
    double x, y;
};

// 圆形结构体（代表树）
struct Circle {
    Point center;           // 圆心坐标
    double radius;          // 半径
    vector<int> arcPoints;  // 该圆上的切点在图中的索引
};

// 全局变量
Point graphNodes[512];              // 图中所有节点（起点、终点、切点）
double adjacencyMatrix[512][512];   // 邻接矩阵，存储节点间距离
int nodeCount;                      // 图中节点总数
int treeCount;                      // 树的数量

Circle trees[20];                   // 所有树的信息

/**
 * 计算两点间的欧几里得距离
 */
double distanceBetween(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

/**
 * 计算向量oa和ob的叉积
 * 用于判断点相对于线段的位置关系
 */
double crossProduct(const Point &o, const Point &a, const Point &b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

/**
 * 检查两点之间是否可见（不被任何树阻挡）
 * 原理：对于每个树，计算圆心到线段的垂距
 * 如果垂距小于半径且垂足在线段上，则被阻挡
 */
bool isVisible(const Point &a, const Point &b) {
    // 如果两点重合，直接返回可见
    if (distanceBetween(a, b) < EPS) {
        return true;
    }
    
    // 检查所有树是否阻挡了这条线段
    for (int i = 0; i < treeCount; i++) {
        const Circle &currentTree = trees[i];
        const Point &treeCenter = currentTree.center;
        
        // 计算圆心到线段ab的垂直距离
        double perpendicularDistance = fabs(crossProduct(a, b, treeCenter)) / distanceBetween(a, b);
        
        // 如果垂距小于半径，可能被阻挡
        if (perpendicularDistance < currentTree.radius - EPS) {
            // 计算圆心到线段两个端点的向量点积，判断垂足是否在线段上
            double dot1 = (treeCenter.x - a.x) * (b.x - a.x) + (treeCenter.y - a.y) * (b.y - a.y);
            double dot2 = (treeCenter.x - b.x) * (a.x - b.x) + (treeCenter.y - b.y) * (a.y - b.y);
            
            // 如果两个点积都为正，说明垂足在线段上，线段穿过圆的内部
            if (dot1 > EPS && dot2 > EPS) {
                return false;  // 被阻挡
            }
        }
    }
    return true;  // 未被任何树阻挡
}

/**
 * 构建图结构：
 * 1. 检查起点到终点的直接路径
 * 2. 计算起点/终点到每个树的切点
 * 3. 计算树与树之间的切点
 * 4. 连接所有可见的切点
 * 5. 计算同一圆上的弧长
 */
void buildGraph() {
    // 第一步：检查起点到终点的直接路径是否可行
    if (isVisible(graphNodes[0], graphNodes[1])) {
        double dist = distanceBetween(graphNodes[0], graphNodes[1]);
        adjacencyMatrix[0][1] = adjacencyMatrix[1][0] = dist;
        return;  // 如果直接路径可行，直接返回
    }
    
    // 第二步：计算起点和终点到每个树的切点
    for (int pointIndex = 0; pointIndex < 2; pointIndex++) {
        for (int treeIndex = 0; treeIndex < treeCount; treeIndex++) {
            Point currentPoint = graphNodes[pointIndex];
            Circle currentTree = trees[treeIndex];
            
            // 计算当前点到圆心的角度
            double angleToCenter = atan2(currentPoint.y - currentTree.center.y, 
                                       currentPoint.x - currentTree.center.x);
            // 计算切线与圆心连线的夹角
            double tangentAngle = acos(currentTree.radius / distanceBetween(currentPoint, currentTree.center));
            
            // 计算两个切点（左右各一个）
            for (int direction = -1; direction <= 1; direction += 2) {
                Point tangentPoint;
                tangentPoint.x = currentTree.center.x + currentTree.radius * cos(angleToCenter + direction * tangentAngle);
                tangentPoint.y = currentTree.center.y + currentTree.radius * sin(angleToCenter + direction * tangentAngle);
                
                // 如果当前点到切点可见，则添加到图中
                if (isVisible(currentPoint, tangentPoint)) {
                    trees[treeIndex].arcPoints.push_back(nodeCount);  // 记录切点属于哪个圆
                    graphNodes[nodeCount] = tangentPoint;             // 存储切点坐标
                    double distToTangent = distanceBetween(currentPoint, tangentPoint);
                    adjacencyMatrix[pointIndex][nodeCount] = adjacencyMatrix[nodeCount][pointIndex] = distToTangent;
                    nodeCount++;  // 节点计数增加
                }
            }
        }
    }
    
    // 第三步：计算树与树之间的切点（外公切线和内公切线）
    for (int firstTree = 0; firstTree < treeCount; firstTree++) {
        for (int secondTree = 0; secondTree < treeCount; secondTree++) {
            if (firstTree == secondTree) continue;  // 跳过同一个树
            
            Point centerA = trees[firstTree].center;
            Point centerB = trees[secondTree].center;
            double angleBetweenCenters = atan2(centerB.y - centerA.y, centerB.x - centerA.x);
            
            // 计算外公切线和内公切线
            for (int sign = -1; sign <= 1; sign += 2) {
                // 计算余弦值，用于确定切线角度
                double cosValue = (trees[firstTree].radius + sign * trees[secondTree].radius) / distanceBetween(centerA, centerB);
                cosValue = max(-1.0, min(1.0, cosValue)); // 限制在[-1,1]范围内
                double angleDelta = acos(cosValue);       // 计算角度差
                
                // 计算两个切点方向
                for (int direction = -1; direction <= 1; direction += 2) {
                    Point tangentPoint;
                    tangentPoint.x = centerA.x + trees[firstTree].radius * cos(angleBetweenCenters + direction * angleDelta);
                    tangentPoint.y = centerA.y + trees[firstTree].radius * sin(angleBetweenCenters + direction * angleDelta);
                    
                    // 将切点添加到图中
                    trees[firstTree].arcPoints.push_back(nodeCount);
                    graphNodes[nodeCount++] = tangentPoint;
                    
                    // 如果角度差为0，只有一个切点，跳出内层循环
                    if (fabs(angleDelta) < EPS) {
                        break;
                    }
                }
            }
        }
    }
    
    // 第四步：连接所有可见的切点（直线段）
    for (int i = 2; i < nodeCount; i++) {
        for (int j = i + 1; j < nodeCount; j++) {
            if (isVisible(graphNodes[i], graphNodes[j])) {
                double dist = distanceBetween(graphNodes[i], graphNodes[j]);
                adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = dist;
            }
        }
    }
    
    // 第五步：计算同一圆上切点之间的弧长
    for (int treeIndex = 0; treeIndex < treeCount; treeIndex++) {
        vector<int> &arcPoints = trees[treeIndex].arcPoints;  // 该圆上的所有切点
        int pointCount = arcPoints.size();
        
        // 遍历该圆上的所有切点对
        for (int i = 0; i < pointCount; i++) {
            for (int j = i + 1; j < pointCount; j++) {
                Point pointA = graphNodes[arcPoints[i]];
                Point pointB = graphNodes[arcPoints[j]];
                Point treeCenter = trees[treeIndex].center;
                
                // 计算两点与圆心形成的夹角
                double dotProduct = (pointA.x - treeCenter.x) * (pointB.x - treeCenter.x) + 
                                  (pointA.y - treeCenter.y) * (pointB.y - treeCenter.y);
                double cosAngle = dotProduct / (trees[treeIndex].radius * trees[treeIndex].radius);
                cosAngle = max(-1.0, min(1.0, cosAngle)); // 限制在有效范围内
                
                double angle = acos(cosAngle);           // 计算夹角（弧度）
                double arcLength = angle * trees[treeIndex].radius;  // 计算弧长
                
                // 在邻接矩阵中记录弧长
                adjacencyMatrix[arcPoints[i]][arcPoints[j]] = adjacencyMatrix[arcPoints[j]][arcPoints[i]] = arcLength;
            }
        }
    }
    
    // 设置邻接矩阵对角线为0（节点到自身的距离为0）
    for (int i = 0; i < nodeCount; i++) {
        adjacencyMatrix[i][i] = 0;
    }
}

/**
 * 使用Dijkstra算法计算起点到终点的最短路径
 * 由于节点数较少（最多512），使用简单的数组实现
 */
double findShortestPath() {
    double minDistance[512];  // 存储起点到各节点的最短距离
    bool visited[512];        // 标记节点是否已访问
    memset(visited, 0, sizeof(visited));
    
    // 初始化距离数组
    for (int i = 0; i < nodeCount; i++) {
        minDistance[i] = INF;
    }
    minDistance[0] = 0;  // 起点到自身的距离为0
    
    // Dijkstra算法主循环
    while (true) {
        // 寻找未访问节点中距离最小的节点
        int currentNode = -1;
        for (int i = 0; i < nodeCount; i++) {
            if (!visited[i] && (currentNode == -1 || minDistance[i] < minDistance[currentNode])) {
                currentNode = i;
            }
        }
        
        // 如果没有可访问节点或已到达终点，退出循环
        if (currentNode == -1 || currentNode == 1) {
            break;
        }
        
        visited[currentNode] = true;  // 标记当前节点为已访问
        
        // 更新当前节点所有邻居的距离
        for (int neighbor = 0; neighbor < nodeCount; neighbor++) {
            minDistance[neighbor] = min(minDistance[neighbor], minDistance[currentNode] + adjacencyMatrix[currentNode][neighbor]);
        }
    }
    
    return minDistance[1];  // 返回到达终点的最短距离
}

/**
 * 主函数：处理多个测试用例
 */
int main() {
    int testCases;
    cin >> testCases;
    
    nodeCount = 512; // 初始化最大节点数
    
    for (int caseNum = 1; caseNum <= testCases; caseNum++) {
        // 测试用例之间的空行（除第一个外）
        if (caseNum != 1) {
            cout << endl;
        }
        
        // 初始化邻接矩阵为无穷大
        for (int i = 0; i < nodeCount; i++) {
            for (int j = 0; j < nodeCount; j++) {
                adjacencyMatrix[i][j] = INF;
            }
        }
        
        // 读取输入数据
        Point start, end;
        cin >> treeCount >> start.x >> start.y >> end.x >> end.y;
        
        // 初始化图节点：起点为0，终点为1
        nodeCount = 2;
        graphNodes[0] = start;
        graphNodes[1] = end;
        
        // 读取树的信息（坐标和直径，转换为半径）
        for (int i = 0; i < treeCount; i++) {
            cin >> trees[i].center.x >> trees[i].center.y >> trees[i].radius;
            trees[i].radius /= 2;  // 直径转半径
            trees[i].arcPoints.clear();  // 清空切点列表
        }
        
        // 构建图并计算最短路径
        buildGraph();
        double shortestPath = findShortestPath();
        double travelTime = shortestPath * 3600.0 / SPEED;  // 转换为秒
        
        // 输出结果，保留两位小数
        cout << fixed << setprecision(2) << travelTime << endl;
    }
    
    return 0;
}
