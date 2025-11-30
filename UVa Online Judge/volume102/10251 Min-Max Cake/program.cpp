// Min-Max Cake
// UVa ID: 10251
// Verdict: Accepted
// Submission Date: 2025-11-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-12;

// 计算圆形蛋糕的最小切割面积
double minCircleArea(double radius, double distance) {
    if (distance < EPS) return PI * radius * radius / 2.0;
    double area = radius * radius * acos(distance / radius) - distance * sqrt(radius * radius - distance * distance);
    return area;
}

// 点结构体
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    double cross(const Point& p) const { return x * p.y - y * p.x; }
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    double len() const { return sqrt(x * x + y * y); }
    Point rotate90() const { return Point(-y, x); } // 逆时针旋转90度
};

// 计算多边形面积（鞋带公式）
double polygonArea(const vector<Point>& poly) {
    double area = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += poly[i].x * poly[j].y - poly[j].x * poly[i].y;
    }
    return fabs(area) / 2.0;
}

// 半平面交：求直线ab与多边形poly的交集（在直线ab的左侧）
vector<Point> halfPlaneIntersection(const vector<Point>& poly, const Point& a, const Point& b) {
    vector<Point> result;
    int n = poly.size();
    
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % n];
        
        // 判断点p1在直线的哪一侧
        double cross1 = (b - a).cross(p1 - a);
        double cross2 = (b - a).cross(p2 - a);
        
        // 如果p1在左侧，加入结果
        if (cross1 >= -EPS) result.push_back(p1);
        
        // 如果线段与直线相交，加入交点
        if (cross1 * cross2 < -EPS) {
            double t = (b - a).cross(a - p1) / (b - a).cross(p2 - p1);
            Point inter = p1 + (p2 - p1) * t;
            result.push_back(inter);
        }
    }
    
    return result;
}

// 计算方形蛋糕的最小切割面积
double minSquareArea(double side, double dx, double dy) {
    double half = side / 2.0;
    double totalArea = side * side;
    
    // 方形的四个顶点（逆时针顺序）
    vector<Point> square = {
        Point(-half, -half), Point(-half, half), 
        Point(half, half), Point(half, -half)
    };
    
    // 花的位置
    Point flower(dx, dy);
    
    double minArea = totalArea;
    
    // 考虑四个顶点与花位置的连线
    for (int i = 0; i < 4; i++) {
        Point vertex = square[i];
        
        // 情况1：连接花位置和顶点的直线作为分割线
        vector<Point> part1 = halfPlaneIntersection(square, flower, vertex);
        double area1 = polygonArea(part1);
        double area2 = totalArea - area1; // 另一部分的面积
        minArea = min(minArea, min(area1, area2));
        
        // 情况2：过花位置作该直线的垂线作为分割线
        Point dir = vertex - flower;
        Point normal = dir.rotate90(); // 垂直方向
        
        vector<Point> part3 = halfPlaneIntersection(square, flower, flower + normal);
        double area3 = polygonArea(part3);
        double area4 = totalArea - area3; // 另一部分的面积
        minArea = min(minArea, min(area3, area4));
    }
    
    return minArea;
}

int main() {
    int n;
    cin >> n;
    
    cout << fixed << setprecision(3);
    
    for (int i = 0; i < n; i++) {
        int first, second, third, fourth = 0;
        cin >> first >> second >> third;
        
        char c = cin.peek();
        if (c != '\n' && c != EOF) {
            cin >> fourth;
            // 方形蛋糕
            double area = minSquareArea(first, third, fourth);
            double volume = area * second;
            cout << volume << endl;
        } else {
            // 圆形蛋糕
            double area = minCircleArea(first, third);
            double volume = area * second;
            cout << volume << endl;
        }
    }
    
    return 0;
}
