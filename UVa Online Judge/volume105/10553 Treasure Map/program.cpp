// Treasure Map
// UVa ID: 10553
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

// 建立方向名称到角度的映射（基于磁北，0度=磁北）
void buildDirectionMap(map<string, double>& directionMap) {
    vector<string> directions = {
        "N", "NbE", "NNE", "NEbN", "NE", "NEbE", "ENE", "EbN",
        "E", "EbS", "ESE", "SEbE", "SE", "SEbS", "SSE", "SbE",
        "S", "SbW", "SSW", "SWbS", "SW", "SWbW", "WSW", "WbS",
        "W", "WbN", "WNW", "NWbW", "NW", "NWbN", "NNW", "NbW"
    };
    double angleStep = 360.0 / 32.0;
    for (size_t i = 0; i < directions.size(); ++i) {
        directionMap[directions[i]] = i * angleStep;
    }
}

// 将角度转换为弧度
double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// 计算点到线段的距离
double pointToSegmentDistance(double px, double py, double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    
    // 如果线段长度为0，直接返回点到端点的距离
    if (dx == 0 && dy == 0) {
        return sqrt((px - x1) * (px - x1) + (py - y1) * (py - y1));
    }
    
    // 计算投影参数 t
    double t = ((px - x1) * dx + (py - y1) * dy) / (dx * dx + dy * dy);
    
    // 检查投影点是否在线段上
    if (t < 0.0) {
        // 投影点在线段起点之前，返回点到起点的距离
        return sqrt((px - x1) * (px - x1) + (py - y1) * (py - y1));
    } else if (t > 1.0) {
        // 投影点在线段终点之后，返回点到终点的距离
        return sqrt((px - x2) * (px - x2) + (py - y2) * (py - y2));
    } else {
        // 投影点在线段上，计算垂直距离
        double projX = x1 + t * dx;
        double projY = y1 + t * dy;
        return sqrt((px - projX) * (px - projX) + (py - projY) * (py - projY));
    }
}

int main() {
    map<string, double> directionMap;
    buildDirectionMap(directionMap);

    int n;
    while (cin >> n && n != 0) {
        vector<pair<string, double>> steps(n);
        for (int i = 0; i < n; ++i) {
            cin >> steps[i].first >> steps[i].second;
        }
        double magneticDeclination;
        cin >> magneticDeclination;

        // 计算宝藏的最终位置（海盗实际到达的位置）
        // 海盗基于磁北行走：实际真北方向 = 磁北方向(磁偏角) + 地图方向
        double treasureX = 0.0, treasureY = 0.0;
        for (int i = 0; i < n; ++i) {
            string direction = steps[i].first;
            double paces = steps[i].second;
            
            // 海盗实际方向 = 磁偏角 + 地图方向
            double pirateTrueAngle = magneticDeclination + directionMap[direction];
            treasureX += paces * sin(toRadians(pirateTrueAngle));
            treasureY += paces * cos(toRadians(pirateTrueAngle));
        }
        
        // 模拟寻宝者行走过程
        double seekerX = 0.0, seekerY = 0.0;
        double prevSeekerX = 0.0, prevSeekerY = 0.0;
        double minDistance = 1e9;
        
        // 初始位置的距离
        minDistance = sqrt(treasureX * treasureX + treasureY * treasureY);
        
        for (int i = 0; i < n; ++i) {
            string direction = steps[i].first;
            double paces = steps[i].second;
            
            // 保存上一步位置
            prevSeekerX = seekerX;
            prevSeekerY = seekerY;
            
            // 寻宝者认为地图方向就是真北方向
            double seekerAngle = directionMap[direction];
            seekerX += paces * sin(toRadians(seekerAngle));
            seekerY += paces * cos(toRadians(seekerAngle));
            
            // 计算当前线段与宝藏最终位置的最小距离
            double segmentDistance = pointToSegmentDistance(
                treasureX, treasureY, prevSeekerX, prevSeekerY, seekerX, seekerY);
            
            if (segmentDistance < minDistance) {
                minDistance = segmentDistance;
            }
            
            // 检查寻宝者当前位置与宝藏最终位置的距离
            double currentDistance = sqrt(
                (seekerX - treasureX) * (seekerX - treasureX) + 
                (seekerY - treasureY) * (seekerY - treasureY));
            
            if (currentDistance < minDistance) {
                minDistance = currentDistance;
            }
        }

        cout << fixed << setprecision(2) << minDistance << endl;
    }

    return 0;
}
