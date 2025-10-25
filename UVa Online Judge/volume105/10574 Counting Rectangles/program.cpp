// Counting Rectangles
// UVa ID: 10574
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.420s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int testCount;
    cin >> testCount;
    
    for (int caseNum = 1; caseNum <= testCount; caseNum++) {
        int pointCount;
        cin >> pointCount;
        
        // 按 y 坐标分组存储 x 坐标
        map<int, vector<int>> yToXMap;
        
        for (int i = 0; i < pointCount; i++) {
            int x, y;
            cin >> x >> y;
            yToXMap[y].push_back(x);
        }
        
        // 统计水平线段 (x1, x2) 的出现次数
        map<pair<int, int>, int> segmentCount;
        
        // 遍历每个 y 坐标对应的点集
        for (auto& yGroup : yToXMap) {
            vector<int>& xList = yGroup.second;
            // 对 x 坐标排序
            sort(xList.begin(), xList.end());
            int xSize = xList.size();
            
            // 枚举所有可能的水平线段
            for (int i = 0; i < xSize; i++) {
                for (int j = i + 1; j < xSize; j++) {
                    // x1 < x2
                    segmentCount[{xList[i], xList[j]}]++;
                }
            }
        }
        
        // 计算矩形总数
        long long totalRectangles = 0;
        for (auto& segment : segmentCount) {
            long long count = segment.second;
            // 每 k 条相同水平线段可形成 C(k, 2) 个矩形
            totalRectangles += count * (count - 1) / 2;
        }
        
        cout << "Case " << caseNum << ": " << totalRectangles << "\n";
    }
    
    return 0;
}
