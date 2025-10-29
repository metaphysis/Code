// Nuclear Plants
// UVa ID: 1367
// Verdict: Accepted
// Submission Date: 2025-10-29
// UVa Run Time: 0.140s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPS = 5 * 1e-13;  // 浮点数比较精度
const int MAX_POINTS = 200 + 5;  // 最大点数

// 浮点数比较函数
int dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    else return x < 0 ? -1 : 1;
}

const double PI = acos(-1);  // 圆周率
const double TWO_PI = PI * 2;  // 2π

// 角度归一化函数：将角度归一化到 [center - π, center + π) 范围内
double normalizeAngle(double rad, double center = PI) {
    return rad - TWO_PI * floor((rad + PI - center) / TWO_PI);
}

// 点/向量结构体
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

typedef Point Vector;  // 向量类型别名

// 向量运算重载
Vector operator + (Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (Point A, Point B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x * p, A.y * p); }
Vector operator / (Vector A, double p) { return Vector(A.x / p, A.y / p); }

// 点比较运算符（用于排序）
bool operator < (const Point& a, const Point& b) {
    return dcmp(a.x - b.x) < 0 || (dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) < 0);
}

// 点相等判断
bool operator == (Point A, Point B) {
    return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0;
}

// 向量点积
double dot(Vector A, Vector B) { return A.x * B.x + A.y * B.y; }

// 向量长度
double length(Vector A) { return sqrt(dot(A, A)); }

// 向量叉积
double cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }

// 计算向量角度
double vectorAngle(Vector v) {
    return atan2(v.y, v.x);
}

// 判断点是否在线段上
bool onSegment(const Point& p, const Point& a1, const Point& a2) {
    return dcmp(cross(a1 - p, a2 - p)) == 0 && dcmp(dot(a1 - p, a2 - p)) < 0;
}

// 计算两圆交点对应的角度（相对于圆心1）
void getCircleCircleIntersection(Point center1, double radius1, Point center2, double radius2, vector<double>& angles) {
    double distance = length(center1 - center2);
    if (dcmp(distance) == 0) return;  // 同心圆
    if (dcmp(radius1 + radius2 - distance) < 0) return;  // 相离
    if (dcmp(fabs(radius1 - radius2) - distance) > 0) return;  // 包含

    // 计算交点对应的角度
    double baseAngle = vectorAngle(center2 - center1);
    double angleDiff = acos((radius1 * radius1 + distance * distance - radius2 * radius2) / (2 * radius1 * distance));
    angles.push_back(normalizeAngle(baseAngle - angleDiff));
    angles.push_back(normalizeAngle(baseAngle + angleDiff));
}

// 获取点到直线的投影点
Point getLineProjection(Point p, Point a, Point b) {
    Vector v = b - a;
    return a + v * (dot(v, p - a) / dot(v, v));
}

// 计算直线与圆的交点对应的角度
void getLineCircleIntersection(Point lineStart, Point lineEnd, Point circleCenter, double radius, vector<double>& angles) {
    Point projection = getLineProjection(circleCenter, lineStart, lineEnd);
    double baseAngle = vectorAngle(projection - circleCenter);
    double distance = length(projection - circleCenter);
    if (dcmp(distance - radius) > 0) return;  // 不相交
    
    double angleDiff = acos(distance / radius);
    angles.push_back(baseAngle + angleDiff);
    if (dcmp(angleDiff) == 0) return;  // 相切，只有一个交点
    angles.push_back(baseAngle - angleDiff);
}

int circleCount;  // 圆的个数
int rectangleWidth, rectangleHeight;  // 矩形宽度和高度
Point circleCenters[MAX_POINTS];  // 圆心坐标数组
double circleRadii[MAX_POINTS];  // 圆半径数组

// 根据圆心和角度获取圆上的点
Point getPointOnCircle(int circleIndex, double angle) {
    return Point(circleCenters[circleIndex].x + cos(angle) * circleRadii[circleIndex], 
                circleCenters[circleIndex].y + sin(angle) * circleRadii[circleIndex]);
}

// 判断圆上某点是否可见（不在其他圆内且在矩形内）
bool isPointVisible(int circleIndex, double angle) {
    Point p = getPointOnCircle(circleIndex, angle);
    // 检查是否在矩形边界内
    if (p.x < 0 || p.y < 0 || p.x > rectangleWidth || p.y > rectangleHeight) return false;
    
    // 检查是否在其他圆内
    for (int i = 0; i < circleCount; i++) {
        // 如果是同一个圆且索引较小，跳过（避免重复计算）
        if (circleCenters[circleIndex] == circleCenters[i] && 
            dcmp(circleRadii[circleIndex] - circleRadii[i]) == 0 && i < circleIndex) 
            return false;
        // 如果点在圆内，不可见
        if (dcmp(length(p - circleCenters[i]) - circleRadii[i]) < 0) return false;
    }
    return true;
}

// 判断任意点是否可见（不在任何圆内）
bool isPointVisible(Point p) {
    for (int i = 0; i < circleCount; i++) {
        if (dcmp(length(p - circleCenters[i]) - circleRadii[i]) < 0) return false;
    }
    return true;
}

// 计算所有圆的并集面积（即禁区总面积）
double calculateForbiddenArea() {
    // 矩形四个顶点
    Point rectangleCorners[4];
    rectangleCorners[0] = Point(0, 0);
    rectangleCorners[1] = Point(rectangleWidth, 0);
    rectangleCorners[2] = Point(rectangleWidth, rectangleHeight);
    rectangleCorners[3] = Point(0, rectangleHeight);
    
    double totalForbiddenArea = 0;

    // 第一部分：计算各个圆的贡献面积
    for (int i = 0; i < circleCount; i++) {
        vector<double> criticalAngles;  // 关键角度（分割点）
        criticalAngles.push_back(0);    // 起始角度
        criticalAngles.push_back(TWO_PI); // 结束角度

        // 添加与矩形边的交点角度
        for (int j = 0; j < 4; j++) {
            getLineCircleIntersection(rectangleCorners[j], rectangleCorners[(j + 1) % 4], 
                                    circleCenters[i], circleRadii[i], criticalAngles);
        }

        // 添加与其他圆的交点角度
        for (int j = 0; j < circleCount; j++) {
            if (i == j) continue;
            getCircleCircleIntersection(circleCenters[i], circleRadii[i], 
                                      circleCenters[j], circleRadii[j], criticalAngles);
        }

        // 排序角度并处理每个区间
        sort(criticalAngles.begin(), criticalAngles.end());
        for (int j = 0; j < criticalAngles.size() - 1; j++) {
            if (criticalAngles[j + 1] - criticalAngles[j] > EPS) {
                double midAngle = (criticalAngles[j] + criticalAngles[j + 1]) / 2.0;
                // 如果区间中点可见，计算该区间对面积的贡献
                if (isPointVisible(i, midAngle)) {
                    // 三角形面积（扇形减去三角形部分）
                    totalForbiddenArea += cross(getPointOnCircle(i, criticalAngles[j]), 
                                              getPointOnCircle(i, criticalAngles[j + 1])) / 2.0;
                    // 扇形面积
                    double angleSpan = criticalAngles[j + 1] - criticalAngles[j];
                    totalForbiddenArea += circleRadii[i] * circleRadii[i] * (angleSpan - sin(angleSpan)) / 2.0;
                }
            }
        }
    }

    // 第二部分：计算矩形边界被圆覆盖的部分
    for (int i = 0; i < 4; i++) {
        Vector edgeVector = rectangleCorners[(i + 1) % 4] - rectangleCorners[i];
        double edgeLength = length(edgeVector);

        vector<double> distanceAlongEdge;  // 沿边的距离参数
        distanceAlongEdge.push_back(0);    // 起点
        distanceAlongEdge.push_back(edgeLength);  // 终点
        
        // 添加与圆的交点距离参数
        for (int j = 0; j < circleCount; j++) {
            vector<double> intersectionAngles;
            getLineCircleIntersection(rectangleCorners[i], rectangleCorners[(i + 1) % 4], 
                                    circleCenters[j], circleRadii[j], intersectionAngles);
            for (int k = 0; k < intersectionAngles.size(); k++) {
                Point intersectionPoint = getPointOnCircle(j, intersectionAngles[k]);
                distanceAlongEdge.push_back(length(intersectionPoint - rectangleCorners[i]));
            }
        }

        // 排序距离参数并生成对应的点
        sort(distanceAlongEdge.begin(), distanceAlongEdge.end());
        vector<Point> edgePoints;
        for (int j = 0; j < distanceAlongEdge.size(); j++) {
            edgePoints.push_back(rectangleCorners[i] + edgeVector * (distanceAlongEdge[j] / edgeLength));
        }

        // 计算每个区间是否被圆覆盖
        for (int j = 0; j < distanceAlongEdge.size() - 1; j++) {
            Point midpoint = (edgePoints[j] + edgePoints[j + 1]) / 2.0;
            // 如果中点被圆覆盖，计算该区间面积
            if (!isPointVisible(midpoint)) {
                totalForbiddenArea += cross(edgePoints[j], edgePoints[j + 1]) / 2.0;
            }
        }
    }

    return totalForbiddenArea;
}

int main() {
    int smallPlantCount, largePlantCount;
    
    // 处理多个测试用例
    while (cin >> rectangleWidth >> rectangleHeight >> smallPlantCount >> largePlantCount && 
           (rectangleWidth || rectangleHeight || smallPlantCount || largePlantCount)) {
        
        circleCount = 0;
        
        // 读取小核电站位置（禁区半径0.58km）
        for (int i = 0; i < smallPlantCount; i++) {
            cin >> circleCenters[circleCount].x >> circleCenters[circleCount].y;
            circleRadii[circleCount] = 0.58;
            circleCount++;
        }
        
        // 去重小核电站
        sort(circleCenters, circleCenters + smallPlantCount);
        smallPlantCount = unique(circleCenters, circleCenters + smallPlantCount) - circleCenters;
        
        // 读取大核电站位置（禁区半径1.31km）
        for (int i = 0; i < largePlantCount; i++) {
            cin >> circleCenters[smallPlantCount + i].x >> circleCenters[smallPlantCount + i].y;
            circleRadii[smallPlantCount + i] = 1.31;
        }
        
        // 去重大核电站并更新总圆数
        sort(circleCenters + smallPlantCount, circleCenters + smallPlantCount + largePlantCount);
        circleCount = unique(circleCenters + smallPlantCount, circleCenters + smallPlantCount + largePlantCount) - circleCenters;
        
        // 计算可用面积 = 矩形总面积 - 禁区总面积
        double totalArea = rectangleWidth * rectangleHeight;
        double forbiddenArea = calculateForbiddenArea();
        double availableArea = totalArea - forbiddenArea;
        
        cout << fixed << setprecision(2) << availableArea << endl;
    }
    
    return 0;
}
