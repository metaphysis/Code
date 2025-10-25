// Eat or not to Eat?
// UVa ID: 10273
// Verdict: Accepted
// Submission Date: 2025-10-25
// UVa Run Time: 0.530s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int testCaseCount;
    cin >> testCaseCount;
    while (testCaseCount--) {
        int cowCount;
        cin >> cowCount;
        vector<int> period(cowCount);
        vector<vector<int>> milkProduction(cowCount);
        
        // 读取每头牛的周期和产奶量数据
        for (int i = 0; i < cowCount; i++) {
            cin >> period[i];
            milkProduction[i].resize(period[i]);
            for (int j = 0; j < period[i]; j++) {
                cin >> milkProduction[i][j];
            }
        }
        
        vector<bool> isAlive(cowCount, true);
        int aliveCount = cowCount;
        int lastEatenDay = 0;
        int daysWithoutEating = 0;
        const int MAX_DAYS_WITHOUT_EATING = 2520; // 1 到 10 的最小公倍数
        
        // 模拟每一天
        for (int currentDay = 1; ; currentDay++) {
            // 终止条件：没有存活牛或长时间未吃牛
            if (aliveCount == 0) break;
            if (daysWithoutEating > MAX_DAYS_WITHOUT_EATING) break;
            
            // 找出当天存活牛中的最小产奶量
            int minMilkToday = INT_MAX;
            for (int i = 0; i < cowCount; i++) {
                if (isAlive[i]) {
                    int todayMilk = milkProduction[i][(currentDay - 1) % period[i]];
                    if (todayMilk < minMilkToday) {
                        minMilkToday = todayMilk;
                    }
                }
            }
            
            // 统计产奶量等于最小值的牛的数量
            int minMilkCount = 0;
            int candidateCow = -1;
            for (int i = 0; i < cowCount; i++) {
                if (isAlive[i]) {
                    int todayMilk = milkProduction[i][(currentDay - 1) % period[i]];
                    if (todayMilk == minMilkToday) {
                        minMilkCount++;
                        candidateCow = i;
                    }
                }
            }
            
            // 如果只有一头牛产奶量最小，则吃掉它
            if (minMilkCount == 1) {
                isAlive[candidateCow] = false;
                aliveCount--;
                lastEatenDay = currentDay;
                daysWithoutEating = 0;
            } else {
                daysWithoutEating++;
            }
        }
        
        // 输出结果
        cout << aliveCount << " " << lastEatenDay << endl;
    }
    return 0;
}
