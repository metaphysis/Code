// Circum Triangle
// UVa ID: 11186
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.670s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

const double PI = 2.0 * acos(0.0);

double degToRad(double deg) {
    return deg * PI / 180.0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int pointCount;
    double radius;
    while (cin >> pointCount >> radius && (pointCount != 0 || radius != 0)) {
        vector<double> angles(pointCount);
        for (int i = 0; i < pointCount; ++i) {
            cin >> angles[i];
        }
        
        if (pointCount < 3) {
            cout << "0\n";
            continue;
        }
        
        vector<double> radians(pointCount);
        for (int i = 0; i < pointCount; ++i) {
            radians[i] = degToRad(angles[i]);
        }
        sort(radians.begin(), radians.end());
        
        vector<double> xCoord(pointCount), yCoord(pointCount);
        for (int i = 0; i < pointCount; ++i) {
            xCoord[i] = cos(radians[i]);
            yCoord[i] = sin(radians[i]);
        }
        
        double totalArea = 0.0;
        
        for (int i = 0; i < pointCount; ++i) {
            for (int j = i + 1; j < pointCount; ++j) {
                double angleIJ = radians[j] - radians[i];
                if (angleIJ > PI) angleIJ = 2 * PI - angleIJ;
                
                double xi = xCoord[i], yi = yCoord[i];
                double xj = xCoord[j], yj = yCoord[j];
                
                // 选择指向劣弧侧的法向量
                double normalX, normalY;
                double rawAngle = radians[j] - radians[i];
                if (rawAngle > 0 && rawAngle <= PI) {
                    normalX = yi - yj;
                    normalY = xj - xi;
                } else {
                    normalX = yj - yi;
                    normalY = xi - xj;
                }
                
                int minorArcCount = 0;
                for (int k = 0; k < pointCount; ++k) {
                    if (k == i || k == j) continue;
                    
                    double xk = xCoord[k], yk = yCoord[k];
                    double deltaX = xk - xi, deltaY = yk - yi;
                    
                    if (deltaX * normalX + deltaY * normalY > 0) {
                        minorArcCount++;
                    }
                }
                
                int majorArcCount = (pointCount - 2) - minorArcCount;
                totalArea += sin(angleIJ) * (minorArcCount - majorArcCount);
            }
        }
        
        totalArea = totalArea * radius * radius / 2.0;
        cout << fixed << setprecision(0) << totalArea << "\n";
    }
    
    return 0;
}
