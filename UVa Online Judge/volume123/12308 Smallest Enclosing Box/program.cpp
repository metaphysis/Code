// Smallest Enclosing Box
// UVa ID: 12308
// Verdict: Accepted
// Submission Date: 2025-10-10
// UVa Run Time: 0.120s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <functional>

using namespace std;

const double EPS = 1e-12;        // 浮点数比较精度
const double PI = acos(-1.0);    // 圆周率

// 三维点结构体
struct Point3D {
    double x, y, z;
    Point3D() : x(0), y(0), z(0) {}
    Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
    
    // 点加法
    Point3D operator+(const Point3D& p) const {
        return Point3D(x + p.x, y + p.y, z + p.z);
    }
    
    // 点减法
    Point3D operator-(const Point3D& p) const {
        return Point3D(x - p.x, y - p.y, z - p.z);
    }
};

// 点积运算
double dot(const Point3D& a, const Point3D& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 叉积运算
Point3D cross(const Point3D& a, const Point3D& b) {
    return Point3D(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}

// 向量长度
double length(const Point3D& v) {
    return sqrt(dot(v, v));
}

// 计算点在给定方向上的投影范围
void projectPoints(const vector<Point3D>& points, const Point3D& dir, 
                   double& minVal, double& maxVal) {
    minVal = maxVal = dot(points[0], dir);
    for (int i = 1; i < points.size(); i++) {
        double val = dot(points[i], dir);
        if (val < minVal) minVal = val;
        if (val > maxVal) maxVal = val;
    }
}

// 欧拉角旋转：根据三个欧拉角生成旋转矩阵的三个正交基向量
void eulerRotation(double alpha, double beta, double gamma,
                   Point3D& u, Point3D& v, Point3D& w) {
    double ca = cos(alpha), sa = sin(alpha);
    double cb = cos(beta), sb = sin(beta);
    double cg = cos(gamma), sg = sin(gamma);
    
    // 旋转矩阵 R = Rz(gamma) * Ry(beta) * Rx(alpha)
    u.x = cb * cg;
    u.y = sa * sb * cg + ca * sg;
    u.z = -ca * sb * cg + sa * sg;
    
    v.x = -cb * sg;
    v.y = -sa * sb * sg + ca * cg;
    v.z = ca * sb * sg + sa * cg;
    
    w.x = sb;
    w.y = -sa * cb;
    w.z = ca * cb;
}

// 计算在给定旋转角度下的包围盒体积
double computeVolume(const vector<Point3D>& points, double alpha, double beta, double gamma) {
    Point3D u, v, w;
    eulerRotation(alpha, beta, gamma, u, v, w);
    
    double minU, maxU, minV, maxV, minW, maxW;
    projectPoints(points, u, minU, maxU);
    projectPoints(points, v, minV, maxV);
    projectPoints(points, w, minW, maxW);
    
    return (maxU - minU) * (maxV - minV) * (maxW - minW);
}

// 超精细局部优化：在候选解附近进行多轮逐步细化的搜索
double ultraRefinedOptimize(const vector<Point3D>& points, double alpha, double beta, double gamma) {
    double bestVolume = computeVolume(points, alpha, beta, gamma);
    double bestAlpha = alpha, bestBeta = beta, bestGamma = gamma;
    
    // 多轮逐步细化，使用极小的步长（最小到PI/100000）
    for (double step = PI / 15.0; step > PI / 100000.0; step /= 2.5) {
        bool improved = false;
        
        // 在三个欧拉角方向上进行局部搜索
        for (double da = -step; da <= step; da += step / 3.0) {
            for (double db = -step; db <= step; db += step / 3.0) {
                for (double dg = -step; dg <= step; dg += step / 3.0) {
                    double newAlpha = bestAlpha + da;
                    double newBeta = max(0.0, min(PI, bestBeta + db));  // beta限制在[0, π]
                    double newGamma = bestGamma + dg;
                    
                    double volume = computeVolume(points, newAlpha, newBeta, newGamma);
                    if (volume < bestVolume - EPS) {
                        bestVolume = volume;
                        bestAlpha = newAlpha;
                        bestBeta = newBeta;
                        bestGamma = newGamma;
                        improved = true;
                    }
                }
            }
        }
        
        // 如果没有改进且步长已经很小，提前终止
        if (!improved && step < PI / 100.0) break;
    }
    
    return bestVolume;
}

// 主算法：寻找最小体积包围盒
double minBoundingBox(const vector<Point3D>& points) {
    double minVolume = numeric_limits<double>::max();
    
    // 根据点集大小调整搜索密度
    int steps = 18;
    if (points.size() <= 6) {
        steps = 22;  // 对于小点集，使用更密集的搜索
    }
    
    // 第一阶段：中等密度搜索找到大致范围
    vector<vector<double>> candidates;
    
    // 在欧拉角空间中进行均匀采样
    for (int i = 0; i < steps; i++) {
        double alpha = 2.0 * PI * i / steps;  // alpha ∈ [0, 2π]
        for (int j = 0; j < steps; j++) {
            double beta = PI * j / steps;     // beta ∈ [0, π]
            for (int k = 0; k < steps; k++) {
                double gamma = 2.0 * PI * k / steps;  // gamma ∈ [0, 2π]
                
                double volume = computeVolume(points, alpha, beta, gamma);
                // 保存所有有希望的候选解（体积小于当前最小值的2倍）
                if (volume < minVolume * 2.0) {
                    candidates.push_back({alpha, beta, gamma, volume});
                }
                if (volume < minVolume) {
                    minVolume = volume;
                }
            }
        }
    }
    
    // 第二阶段：对大量候选解进行精细优化
    sort(candidates.begin(), candidates.end(), 
         [](const vector<double>& a, const vector<double>& b) {
             return a[3] < b[3];  // 按体积升序排序
         });
    
    // 对前30个最好的候选解进行超精细优化
    int num_to_optimize = min(30, (int)candidates.size());
    for (int i = 0; i < num_to_optimize; i++) {
        double alpha = candidates[i][0];
        double beta = candidates[i][1];
        double gamma = candidates[i][2];
        
        double volume = ultraRefinedOptimize(points, alpha, beta, gamma);
        if (volume < minVolume) {
            minVolume = volume;
        }
    }
    
    // 第三阶段：基于几何特征的搜索
    // 计算所有点对的方向向量
    vector<Point3D> directions;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            Point3D dir = points[j] - points[i];
            if (length(dir) > EPS) {
                // 归一化方向向量
                double len = length(dir);
                dir = Point3D(dir.x/len, dir.y/len, dir.z/len);
                directions.push_back(dir);
            }
        }
    }
    
    // 对每个方向向量进行精细搜索
    for (const Point3D& dir : directions) {
        // 将方向向量转换为欧拉角
        double beta = acos(dir.z);
        double gamma = atan2(dir.y, dir.x);
        
        // 围绕这个主轴进行密集旋转搜索
        for (int k = 0; k < 12; k++) {
            double alpha = 2.0 * PI * k / 12;
            double volume = computeVolume(points, alpha, beta, gamma);
            if (volume < minVolume) {
                minVolume = volume;
            }
            
            // 对好的方向进行局部优化
            if (volume < minVolume * 1.2) {
                volume = ultraRefinedOptimize(points, alpha, beta, gamma);
                if (volume < minVolume) {
                    minVolume = volume;
                }
            }
        }
    }
    
    return minVolume;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n && n != 0) {
        vector<Point3D> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y >> points[i].z;
        }
        
        double volume = minBoundingBox(points);
        cout << fixed << setprecision(2) << volume << endl;
    }
    
    return 0;
}
