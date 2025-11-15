// Peter Takes a Tramway
// UVa ID: 10423
// Verdict: Accepted
// Submission Date: 2025-11-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    int t;
    int caseNum = 1;
    
    while (cin >> t && t != 0) {
        vector<pair<int, int>> departures; // (出发时间, 电车线路)
        
        // 读取所有电车线路信息
        for (int i = 0; i < t; i++) {
            int tramId;
            char colon;
            cin >> tramId >> colon;
            int depTime;
            while (cin >> depTime && depTime != -1) departures.push_back({depTime, tramId});
        }
        
        // 按出发时间排序
        sort(departures.begin(), departures.end());
        
        int m, n;
        cin >> m >> n;
        
        // 找到Peter在0号站坐的电车
        int startIndex = -1;
        for (int i = 0; i < departures.size(); i++)
            if (departures[i].first >= m) {
                startIndex = i;
                break;
            }
        
        // 如果m时刻之后没有电车，就坐第二天第一辆
        if (startIndex == -1) startIndex = 0;
        
        // 计算最终乘坐的电车
        // 从0号站到n号站需要换乘n次
        // 每次换乘都坐时间序列中的下一辆
        int totalDepartures = departures.size();
        int finalIndex = (startIndex + n - 1) % totalDepartures;
        int finalTram = departures[finalIndex].second;
        
        cout << "Case " << caseNum << ": Peter arrives at stop " << n << " by tram " << finalTram << "." << endl;
        caseNum++;
    }
    
    return 0;
}
