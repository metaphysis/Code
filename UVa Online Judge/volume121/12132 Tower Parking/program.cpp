// Tower Parking
// UVa ID: 12132
// Verdict: Accepted
// Submission Date: 2026-05-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int testcases;
    scanf("%d", &testcases);
    while (testcases--) {
        int h, l;
        scanf("%d %d", &h, &l);
        
        // 记录每辆车所在的楼层和位置，车辆编号最大为 h*l
        vector<int> carFloor(2505, -1);
        vector<int> carPos(2505, -1);
        int maxCar = 0;
        
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < l; ++j) {
                int val;
                scanf("%d", &val);
                if (val != -1) {
                    carFloor[val] = i;
                    carPos[val] = j;
                    if (val > maxCar) maxCar = val;
                }
            }
        }
        
        // elevatorPos[floor] 表示电梯在该层当前连接的位置
        vector<int> elevatorPos(h, 0);
        int currentFloor = 0;  // 电梯当前所在楼层
        int totalTime = 0;
        
        for (int car = 1; car <= maxCar; ++car) {
            int targetFloor = carFloor[car];
            int targetPos = carPos[car];
            
            // 1. 电梯移动到目标楼层
            totalTime += abs(targetFloor - currentFloor) * 10;
            
            // 2. 传送带将目标车旋转到电梯位置
            int distClockwise = (targetPos - elevatorPos[targetFloor] + l) % l;
            int distCounterClockwise = (elevatorPos[targetFloor] - targetPos + l) % l;
            totalTime += min(distClockwise, distCounterClockwise) * 5;
            
            // 3. 更新该层电梯连接位置（车被取走后，电梯占据该位置）
            elevatorPos[targetFloor] = targetPos;
            
            // 4. 电梯返回第一层
            totalTime += targetFloor * 10;
            
            // 5. 更新当前楼层
            currentFloor = 0;
        }
        
        printf("%d\n", totalTime);
    }
    return 0;
}
