// Critical Wave
// UVa ID: 10421
// Verdict: Accepted
// Submission Date: 2025-11-06
// UVa Run Time: 0.210s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

struct Point {
    int x, y;
};

// 对于给定的主轴线 a，计算能选择的最长交替序列长度
int solveForAxis(const vector<Point>& points, int axisValue) {
    // 使用映射记录每个 x 坐标是否有下线点 (axisValue - 1) 和上线点 (axisValue + 1)
    map<int, pair<bool, bool>> xCoordMap;
    
    // 遍历所有点，收集符合条件的点
    for (const auto& point : points) {
        if (point.y == axisValue - 1) {
            xCoordMap[point.x].first = true;  // 标记有下线点
        } else if (point.y == axisValue + 1) {
            xCoordMap[point.x].second = true; // 标记有上线点
        }
    }
    
    // 如果没有符合条件的点，直接返回 0
    if (xCoordMap.empty()) return 0;
    
    // 动态规划状态：以下线点/上线点结尾的最长序列长度
    int lastLower = 0, lastUpper = 0;
    
    // 按 x 坐标递增顺序处理
    for (const auto& entry : xCoordMap) {
        bool hasLower = entry.second.first;   // 当前 x 是否有下线点
        bool hasUpper = entry.second.second;  // 当前 x 是否有上线点
        
        int newLastLower = lastLower;  // 新的下线点状态
        int newLastUpper = lastUpper;  // 新的上线点状态
        
        if (hasLower && hasUpper) {
            // 情况 1：当前 x 同时有下线点和上线点，只能选择其中一个
            int candidateLower = 1;  // 选择下线点的候选值
            if (lastUpper > 0) candidateLower = lastUpper + 1;
            
            int candidateUpper = 1;  // 选择上线点的候选值
            if (lastLower > 0) candidateUpper = lastLower + 1;
            
            newLastLower = max(newLastLower, candidateLower);
            newLastUpper = max(newLastUpper, candidateUpper);
        } else if (hasLower) {
            // 情况 2：只有下线点
            if (lastUpper > 0) {
                newLastLower = max(newLastLower, lastUpper + 1);
            } else {
                newLastLower = max(newLastLower, 1);
            }
        } else if (hasUpper) {
            // 情况 3：只有上线点
            if (lastLower > 0) {
                newLastUpper = max(newLastUpper, lastLower + 1);
            } else {
                newLastUpper = max(newLastUpper, 1);
            }
        }
        
        // 更新状态
        lastLower = newLastLower;
        lastUpper = newLastUpper;
    }
    
    return max(lastLower, lastUpper);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int pointCount;
    while (cin >> pointCount) {
        vector<Point> points(pointCount);
        set<int> candidateAxisValues;
        
        // 读入点数据并生成候选的 a 值
        for (int i = 0; i < pointCount; i++) {
            cin >> points[i].x >> points[i].y;
            // 对于每个点 (x, y)，可能的 a 值为 y + 1 或 y - 1
            candidateAxisValues.insert(points[i].y + 1);
            candidateAxisValues.insert(points[i].y - 1);
        }
        
        int maxPoints = 0;
        // 遍历所有候选的 a 值，找出能包含最多点的曲线
        for (int axisValue : candidateAxisValues) {
            maxPoints = max(maxPoints, solveForAxis(points, axisValue));
        }
        
        cout << maxPoints << "\n";
    }
    
    return 0;
}
