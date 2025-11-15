// Balloons in a Box
// UVa ID: 1009
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct Point {
    double x, y, z;
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

double dist(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) +
                (a.y - b.y) * (a.y - b.y) +
                (a.z - b.z) * (a.z - b.z));
}

double volume(double r) {
    return (4.0 / 3.0) * M_PI * r * r * r;
}

int main() {
    int n;
    int caseNum = 1;
    while (cin >> n && n != 0) {
        Point p1, p2;
        cin >> p1.x >> p1.y >> p1.z;
        cin >> p2.x >> p2.y >> p2.z;
        
        vector<Point> points(n);
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y >> points[i].z;
        }
        
        double boxVol = fabs((p2.x - p1.x) * (p2.y - p1.y) * (p2.z - p1.z));
        
        double maxBalloonVol = 0.0;
        
        // 枚举所有非空子集
        for (int mask = 1; mask < (1 << n); mask++) {
            vector<int> indices;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    indices.push_back(i);
                }
            }
            
            // 枚举该子集的所有排列
            do {
                vector<double> radius(n, 0.0);
                double totalVol = 0.0;
                
                for (int i = 0; i < indices.size(); i++) {
                    int idx = indices[i];
                    Point pt = points[idx];
                    
                    // distance to box sides
                    double r = min({fabs(pt.x - p1.x), fabs(pt.x - p2.x),
                                    fabs(pt.y - p1.y), fabs(pt.y - p2.y),
                                    fabs(pt.z - p1.z), fabs(pt.z - p2.z)});
                    
                    // distance to existing balloons
                    for (int j = 0; j < i; j++) {
                        int prevIdx = indices[j];
                        if (radius[prevIdx] > 0) {
                            double d = dist(pt, points[prevIdx]) - radius[prevIdx];
                            if (d > 0) {
                                r = min(r, d);
                            } else {
                                r = 0;
                                break;
                            }
                        }
                    }
                    
                    if (r > 0) {
                        radius[idx] = r;
                        totalVol += volume(r);
                    } else {
                        radius[idx] = 0;
                        // 这里不break，继续尝试放置后面的气球
                        // 因为可能这个点放不了，但后面的点还能放
                    }
                }
                
                maxBalloonVol = max(maxBalloonVol, totalVol);
                
            } while (next_permutation(indices.begin(), indices.end()));
        }
        
        double unusedVol = boxVol - maxBalloonVol;
        int result = static_cast<int>(round(unusedVol));
        
        cout << "Box " << caseNum << ": " << result << "\n\n";
        caseNum++;
    }
    
    return 0;
}
