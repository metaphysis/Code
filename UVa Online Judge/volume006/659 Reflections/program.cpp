// Reflections
// UVa ID: 659
// Verdict: Accepted
// Submission Date: 2025-11-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Sphere {
    int x, y, r, id;
};

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double k) const { return Point(x * k, y * k); }
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    double len2() const { return x * x + y * y; }
    double len() const { return sqrt(len2()); }
    Point normalize() const { return *this * (1.0 / len()); }
};

int n;
vector<Sphere> spheres;
Point origin, dir;

bool intersect(const Point& o, const Point& d, const Sphere& s, double& t) {
    Point oc = o - Point(s.x, s.y);
    double a = d.dot(d);
    double b = 2 * oc.dot(d);
    double c = oc.dot(oc) - s.r * s.r;
    double disc = b * b - 4 * a * c;
    if (disc < 1e-12) return false;
    
    disc = sqrt(disc);
    double t1 = (-b - disc) / (2 * a);
    double t2 = (-b + disc) / (2 * a);
    
    if (t1 > 1e-9) t = t1;
    else if (t2 > 1e-9) t = t2;
    else return false;
    
    return true;
}

int main() {
    int sceneNum = 0;
    while (cin >> n, n) {
        spheres.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> spheres[i].x >> spheres[i].y >> spheres[i].r;
            spheres[i].id = i + 1;
        }
        int x, y, dx, dy;
        cin >> x >> y >> dx >> dy;
        origin = Point(x, y);
        dir = Point(dx, dy).normalize();

        vector<int> hits;
        int lastHit = -1;
        
        // 模拟最多11次反射，以判断第10次后是否还有反射
        for (int step = 0; step < 11; step++) {
            double minT = 1e18;
            int hitSphere = -1;
            
            // 检测所有球体，找到最近的交点
            for (const auto& s : spheres) {
                if (s.id == lastHit) continue;
                
                double t;
                if (intersect(origin, dir, s, t)) {
                    if (t < minT) {
                        minT = t;
                        hitSphere = s.id;
                    }
                }
            }
            
            if (hitSphere == -1) {
                break;
            }
            
            hits.push_back(hitSphere);
            
            // 计算交点位置和反射方向
            Point hitPoint = origin + dir * minT;
            const Sphere& hit = spheres[hitSphere - 1];
            Point center(hit.x, hit.y);
            Point normal = (hitPoint - center).normalize();
            double dotVal = dir.dot(normal);
            dir = dir - normal * (2 * dotVal);
            
            origin = hitPoint;
            lastHit = hitSphere;
        }

        cout << "Scene " << ++sceneNum << endl;
        
        // 处理无反射的情况
        if (hits.empty()) {
            cout << "inf" << endl << endl;
            continue;
        }
        
        // 输出球体编号
        for (int i = 0; i < min(10, (int)hits.size()); i++) {
            if (i > 0) cout << " ";
            cout << hits[i];
        }
        
        // 根据反射次数决定输出inf还是...
        if (hits.size() <= 10) {
            cout << " inf";
        } else {
            cout << " ...";
        }
        cout << endl << endl;
    }
    return 0;
}
