// Folding My T-Shirt
// UVa ID: 10416
// Verdict: Accepted
// Submission Date: 2025-11-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1e-8;

// 浮点数比较函数
int dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

typedef Point Vector;

// 向量运算
Vector operator-(Point a, Point b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator+(Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }

// 计算中点
Point getMiddle(Point a, Point b) { 
    return Point((a.x + b.x) / 2, (a.y + b.y) / 2); 
}

// 判断点是否在直线上
bool isOnLine(Point p, Point a, Point b) { 
    return dcmp(cross(a - p, b - p)) == 0; 
}

bool checkSymmetry(vector<Point>& points) {
    int n = points.size();
    
    // 情况1：检查每条边作为对称轴
    for (int i = 0; i < n; i++) {
        // 当前边的中点和方向向量
        Point edgeMid = getMiddle(points[i], points[(i + 1) % n]);
        Vector edgeDir = points[(i + 1) % n] - points[i];
        
        // 初始化对称检查的索引
        int leftIdx = (i - 1 + n) % n;
        int rightIdx = (i + 2) % n;
        bool isValid = true;
        
        // 检查所有相对的边中点连线是否垂直于当前边
        while (leftIdx != i && isValid) {
            Point oppositeMid = getMiddle(points[leftIdx], points[rightIdx]);
            
            // 如果中点连线不垂直于边方向，则不是对称轴
            if (dcmp(dot(oppositeMid - edgeMid, edgeDir)) != 0) {
                isValid = false;
            }
            
            // 移动索引：向左和向右各移动一个位置
            leftIdx = (leftIdx - 1 + n) % n;
            rightIdx = (rightIdx + 1) % n;
        }
        
        if (isValid) return true;
    }
    
    // 情况2：当顶点数为偶数时，检查顶点对称轴
    if (n % 2 == 0) {
        int half = n / 2;
        
        for (int i = 0; i < n; i++) {
            Point p1 = points[i];
            Point p2 = points[(i + half) % n];
            Vector axisDir = p1 - p2;  // 对称轴方向
            
            int leftIdx = (i - 1 + n) % n;
            int rightIdx = (i + 1) % n;
            bool isValid = true;
            
            // 检查直到遇到对面的顶点
            while (leftIdx != ((i + half) % n) && isValid) {
                Point edgeMid = getMiddle(points[leftIdx], points[rightIdx]);
                
                // 必须同时满足两个条件：
                // 1. 边中点在对称轴上
                // 2. 边方向与对称轴垂直
                bool condition1 = isOnLine(edgeMid, p1, p2);
                bool condition2 = (dcmp(dot(axisDir, points[leftIdx] - points[rightIdx])) == 0);
                
                if (!(condition1 && condition2)) {
                    isValid = false;
                }
                
                leftIdx = (leftIdx - 1 + n) % n;
                rightIdx = (rightIdx + 1) % n;
            }
            
            if (isValid) return true;
        }
    }
    
    return false;
}

int main() {
    int testCases;
    cin >> testCases;
    
    while (testCases--) {
        int n;
        cin >> n;
        vector<Point> polygon(n);
        for (int i = 0; i < n; i++) {
            cin >> polygon[i].x >> polygon[i].y;
        }
        cout << (checkSymmetry(polygon) ? "Yes" : "No") << endl;
    }
    
    return 0;
}
