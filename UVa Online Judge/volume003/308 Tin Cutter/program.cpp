// Tin Cutter
// UVa ID: 308
// Verdict: Accepted
// Submission Date: 2025-10-11
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

/* 
 * 网格墙标记数组 gridWalls[x][y][direction]
 * 表示在网格点(x,y)在指定方向上是否有墙阻挡
 * 方向: 0=上(up), 1=下(down), 2=左(left), 3=右(right)
 */
int gridWalls[512][512][4] = {};

// 四个方向的移动增量: 上, 下, 左, 右
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

/**
 * 在网格上绘制一条切割线
 * @param startX 起点x坐标(离散化后)
 * @param startY 起点y坐标(离散化后)
 * @param endX   终点x坐标(离散化后)
 * @param endY   终点y坐标(离散化后)
 */
void drawCutLine(int startX, int startY, int endX, int endY) {
    if (startX == endX) {
        // 垂直线: 在线段两侧标记上下方向的墙
        for (int y = startY; y < endY; y++) {
            gridWalls[startX][y][0] = 1;      // 当前点的上方有墙
            gridWalls[startX - 1][y][1] = 1;  // 相邻点的下方有墙
        }
    } else {
        // 水平线: 在线段两侧标记左右方向的墙
        for (int x = startX; x < endX; x++) {
            gridWalls[x][startY][2] = 1;      // 当前点的左方有墙
            gridWalls[x][startY - 1][3] = 1;  // 相邻点的右方有墙
        }
    }
}

// 区域标记数组，记录每个网格点属于哪个连通区域
int regionMap[512][512] = {};

/**
 * 深度优先搜索标记连通区域
 * @param x 当前点的x坐标
 * @param y 当前点的y坐标
 * @param regionId 要标记的区域ID
 * @param maxX 网格的最大x坐标
 * @param maxY 网格的最大y坐标
 */
void markConnectedRegion(int x, int y, int regionId, int maxX, int maxY) {
    // 边界检查
    if (x < 0 || y < 0 || x > maxX || y > maxY) return;
    // 如果该点已经被标记过，则返回
    if (regionMap[x][y]) return;
    // 标记当前点为当前区域
    regionMap[x][y] = regionId;
    // 向四个方向探索
    for (int direction = 0; direction < 4; direction++) {
        // 如果当前方向有墙阻挡，则跳过
        if (gridWalls[x][y][direction]) continue;
        // 递归探索相邻点
        markConnectedRegion(x + dx[direction], y + dy[direction], regionId, maxX, maxY);
    }
}

// 并查集相关数组
int parent[512], ranks[512];

/**
 * 初始化并查集
 * @param n 元素数量
 */
void initUnionFind(int n) {
    for (int i = 0; i <= n; i++) {
        parent[i] = i;  // 每个元素的父节点初始化为自己
        ranks[i] = 1;    // 每个集合的秩初始化为1
    }
}

/**
 * 查找元素所在的集合根节点（带路径压缩）
 * @param x 要查找的元素
 * @return 元素所在集合的根节点
 */
int findRoot(int x) { return parent[x] == x ? x : (parent[x] = findRoot(parent[x])); }

/**
 * 合并两个集合
 * @param x 第一个元素
 * @param y 第二个元素
 * @return 如果成功合并返回1，如果已经在同一集合返回0
 */
int unionSets(int x, int y) {
    x = findRoot(x);
    y = findRoot(y);
    if (x != y) {
        // 按秩合并，将小树合并到大树下
        if (ranks[x] > ranks[y]) {
            parent[y] = x;
            ranks[x] += ranks[y];
        } else {
            parent[x] = y;
            ranks[y] += ranks[x];
        }
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int numCuts;
    int startX[105], startY[105], endX[105], endY[105];
    while (scanf("%d", &numCuts) == 1 && numCuts != 0) {
        // 初始化数组
        memset(gridWalls, 0, sizeof(gridWalls));
        memset(regionMap, 0, sizeof(regionMap));
        // 用于坐标离散化的映射表
        map<int, int> xCoordMap, yCoordMap;
        // 读取所有切割线段并预处理
        for (int i = 0; i < numCuts; i++) {
            scanf("%d %d %d %d", &startX[i], &startY[i], &endX[i], &endY[i]);
            // 确保线段端点有序：起点坐标小于终点坐标
            if (startX[i] == endX[i]) {
                // 垂直线：确保y坐标有序
                if (startY[i] > endY[i]) swap(startY[i], endY[i]);
            } else {
                // 水平线：确保x坐标有序
                if (startX[i] > endX[i]) swap(startX[i], endX[i]);
            }
            // 记录所有出现的坐标值用于离散化
            xCoordMap[startX[i]] = xCoordMap[endX[i]] = 0;
            yCoordMap[startY[i]] = yCoordMap[endY[i]] = 0;
        }
        // 离散化x坐标：将原始坐标映射到连续的网格索引
        int gridSizeX = 1;
        for (map<int, int>::iterator it = xCoordMap.begin(); it != xCoordMap.end(); it++) {
            it->second = gridSizeX++;
        }
        // 离散化y坐标
        int gridSizeY = 1;
        for (map<int, int>::iterator it = yCoordMap.begin(); it != yCoordMap.end(); it++) {
            it->second = gridSizeY++;
        }
        // 在离散化后的网格上绘制所有切割线
        for (int i = 0; i < numCuts; i++) {
            int discreteStartX = xCoordMap[startX[i]];
            int discreteStartY = yCoordMap[startY[i]];
            int discreteEndX = xCoordMap[endX[i]];
            int discreteEndY = yCoordMap[endY[i]];
            drawCutLine(discreteStartX, discreteStartY, discreteEndX, discreteEndY);
        }
        // 使用DFS标记所有连通区域
        int regionCount = 0;
        // 首先标记外部区域（从网格边界开始）
        markConnectedRegion(0, 0, ++regionCount, gridSizeX, gridSizeY);
        // 标记剩余的所有内部区域
        for (int x = 0; x <= gridSizeX; x++) {
            for (int y = 0; y <= gridSizeY; y++) {
                if (regionMap[x][y] == 0) {
                    markConnectedRegion(x, y, ++regionCount, gridSizeX, gridSizeY);
                }
            }
        }
        // 使用并查集合并相邻的区域
        int totalRegions = regionCount;
        initUnionFind(regionCount);
        // 遍历所有网格点，合并相邻的连通区域
        for (int x = 0; x <= gridSizeX; x++) {
            for (int y = 0; y <= gridSizeY; y++) {
                for (int direction = 0; direction < 4; direction++) {
                    int neighborX = x + dx[direction];
                    int neighborY = y + dy[direction];
                    // 检查相邻点是否在网格范围内
                    if (neighborX < 0 || neighborY < 0 || neighborX > gridSizeX || neighborY > gridSizeY) {
                        continue;
                    }
                    // 跳过外部区域（区域1是外部区域）
                    if (regionMap[x][y] == 1 || regionMap[neighborX][neighborY] == 1) {
                        continue;
                    }
                    // 合并相邻的连通区域，成功合并则减少区域计数
                    totalRegions -= unionSets(regionMap[x][y], regionMap[neighborX][neighborY]);
                }
            }
        }
        // 输出孔洞的数量：总区域数 - 外部区域(1个)
        printf("%d\n", totalRegions - 1);
    }
    return 0;
}
