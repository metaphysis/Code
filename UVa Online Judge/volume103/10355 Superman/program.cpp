// Superman
// UVa ID: 10355
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y, z;
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

struct Sphere {
    Point center;
    double radius;
    Sphere(double x = 0, double y = 0, double z = 0, double r = 0) : center(x, y, z), radius(r) {}
};

Point operator-(const Point& a, const Point& b) {
    return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}

double dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double length(const Point& a) {
    return sqrt(dot(a, a));
}

double segmentSphereIntersection(const Point& p1, const Point& p2, const Sphere& s) {
    Point dir = p2 - p1;
    Point oc = p1 - s.center;
    
    double a = dot(dir, dir);
    double b = 2 * dot(oc, dir);
    double c = dot(oc, oc) - s.radius * s.radius;
    
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) return 0.0;
    
    discriminant = sqrt(discriminant);
    double t1 = (-b - discriminant) / (2 * a);
    double t2 = (-b + discriminant) / (2 * a);
    
    if (t1 > 1 || t2 < 0) return 0.0;
    
    t1 = max(t1, 0.0);
    t2 = min(t2, 1.0);
    
    if (t1 > t2) return 0.0;
    
    return (t2 - t1) * length(dir);
}

int main() {
    string cityName;
    while (cin >> cityName) {
        double x1, y1, z1, x2, y2, z2;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        Point start(x1, y1, z1), end(x2, y2, z2);
        
        int numSpheres;
        cin >> numSpheres;
        
        vector<Sphere> spheres(numSpheres);
        for (int i = 0; i < numSpheres; i++) {
            double x, y, z, r;
            cin >> x >> y >> z >> r;
            spheres[i] = Sphere(x, y, z, r);
        }
        
        double totalPathLength = length(end - start);
        double pollutedLength = 0.0;
        
        for (const Sphere& sphere : spheres) 
            pollutedLength += segmentSphereIntersection(start, end, sphere);
        
        double percentage = (pollutedLength / totalPathLength) * 100.0;
        
        cout << cityName << endl;
        cout << fixed << setprecision(2) << percentage << endl;
    }
    
    return 0;
}
