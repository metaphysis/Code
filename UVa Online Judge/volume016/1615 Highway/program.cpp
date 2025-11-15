// Highway
// UVa ID: 1615
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 区间结构体，表示每个村庄对应的出口位置区间
struct VillageInterval {
    double leftEnd;  // 区间左端点
    double rightEnd; // 区间右端点
    
    // 重载小于运算符，用于按右端点排序
    bool operator<(const VillageInterval& other) const {
        return rightEnd < other.rightEnd;
    }
};

int main() {
    int highwayLength, coverDistance, villageCount;
    
    // 处理多个测试用例直到文件结束
    while (cin >> highwayLength >> coverDistance >> villageCount) {
        vector<VillageInterval> intervals;
        
        // 处理每个村庄
        for (int i = 0; i < villageCount; ++i) {
            int xPos, yPos;
            cin >> xPos >> yPos;
            
            // 计算村庄到高速公路的垂直距离
            double verticalDist = abs(yPos);
            
            // 如果垂直距离大于覆盖距离，该村庄无法被覆盖（根据题目保证不会发生）
            if (verticalDist > coverDistance) {
                continue;
            }
            
            // 计算出口在高速公路上的水平覆盖范围
            double horizontalRange = sqrt(coverDistance * coverDistance - verticalDist * verticalDist);
            
            // 计算有效的出口位置区间，限制在 [0, highwayLength] 范围内
            double intervalStart = max(0.0, xPos - horizontalRange);
            double intervalEnd = min(static_cast<double>(highwayLength), xPos + horizontalRange);
            
            intervals.push_back({intervalStart, intervalEnd});
        }
        
        // 按区间右端点升序排序
        sort(intervals.begin(), intervals.end());
        
        int exitCount = 0;          // 出口计数器
        double lastExitPos = -1.0;  // 上一个出口位置，初始化为 -1
        
        // 贪心算法：遍历所有区间
        for (const auto& interval : intervals) {
            // 如果当前区间左端点大于上一个出口位置，需要设置新出口
            if (lastExitPos < interval.leftEnd) {
                ++exitCount;
                lastExitPos = interval.rightEnd; // 在区间右端点设置出口
            }
        }
        
        // 输出结果
        cout << exitCount << endl;
    }
    
    return 0;
}
