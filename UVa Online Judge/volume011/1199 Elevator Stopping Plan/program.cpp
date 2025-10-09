// Elevator Stopping Plan
// UVa ID: 1199
// Verdict: Accepted
// Submission Date: 2025-10-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 全局变量
int passengerCount;           // 乘客数量（需要停靠的楼层数）
vector<int> targetFloors;     // 乘客目标楼层列表
vector<int> tempStops;        // 临时存储当前停靠方案
vector<int> bestStops;        // 存储最优停靠方案

/**
 * 检查在给定时间限制内是否能够服务所有乘客
 * @param timeLimit 时间限制（秒）
 * @return 是否可以在时间限制内服务所有乘客
 */
bool canServeInTime(int timeLimit) {
    // 步骤1：找到第一个无法通过纯步行到达的楼层
    // 如果乘客从1楼步行到目标楼层的时间超过时间限制，则需要电梯服务
    int firstUnservedIndex = passengerCount - 1;  // 默认从最后一个楼层开始
    for (int i = 0; i < passengerCount; i++) {
        if ((targetFloors[i] - 1) * 20 > timeLimit) {
            firstUnservedIndex = i;
            break;
        }
    }

    tempStops.clear();        // 清空临时停靠方案
    int currentTime = 0;      // 当前累计时间（秒）
    int currentFloor = 1;     // 电梯当前位置（从1楼开始）

    // 步骤2：贪心选择停靠楼层，直到所有乘客都被服务或时间不够
    while (true) {
        // 检查从当前位置到第一个未服务楼层的时间是否超过限制
        // 如果连电梯直接开过去的时间都不够，说明当前方案不可行
        if (currentTime + (targetFloors[firstUnservedIndex] - currentFloor) * 4 > timeLimit) {
            break;
        }

        // 步骤3：计算最优停靠楼层
        // 关键公式推导：
        // 约束条件：currentTime + (optimalStop - currentFloor)*4 + (targetFloor - optimalStop)*20 ≤ timeLimit
        // 整理得：optimalStop ≤ (timeLimit - currentTime + 4*currentFloor + 20*targetFloor) / 24
        int targetFloor = targetFloors[firstUnservedIndex];
        int optimalStop = (timeLimit - currentTime + 4 * currentFloor + 20 * targetFloor) / 24;
        tempStops.push_back(optimalStop);  // 记录这个停靠楼层

        // 步骤4：推进未服务乘客索引，跳过所有能被当前停靠楼层服务的乘客
        while (firstUnservedIndex < passengerCount) {
            int nextFloor = targetFloors[++firstUnservedIndex];  // 检查下一个楼层
            // 计算从当前停靠楼层服务下一个楼层的时间
            // 时间 = 当前时间 + 电梯到停靠楼层时间 + 乘客步行时间
            int serviceTime = currentTime + (optimalStop - currentFloor) * 4 + (nextFloor - optimalStop) * 20;
            if (serviceTime > timeLimit) {
                // 如果时间不够，退出循环（这个乘客不能被当前停靠楼层服务）
                break;
            }
        }

        // 步骤5：检查是否所有乘客都被服务
        if (firstUnservedIndex == passengerCount) {
            bestStops = tempStops;  // 保存最优停靠方案
            return true;            // 成功在时间限制内服务所有乘客
        }

        // 步骤6：更新电梯状态
        // 电梯移动到新的停靠楼层并停靠
        currentTime += 10 + (optimalStop - currentFloor) * 4;  // 增加停靠时间和运行时间
        currentFloor = optimalStop;  // 更新电梯位置
    }

    return false;  // 无法在时间限制内服务所有乘客
}

int main(int argc, char* argv[]) {
    // 优化输入输出
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    // 处理多个测试用例
    while (cin >> passengerCount && passengerCount != 0) {
        // 初始化变量
        targetFloors.clear();
        bestStops.clear();

        // 读取乘客目标楼层
        for (int i = 0; i < passengerCount; i++) {
            int floorNumber;
            cin >> floorNumber;
            targetFloors.push_back(floorNumber);
        }

        // 步骤1：二分搜索确定最小时间
        // 搜索范围：[0, 最高楼层*20] - 最大时间是所有乘客都步行的情况
        int lowBound = 0;
        int highBound = targetFloors[passengerCount - 1] * 20;
        int optimalTime = highBound;  // 初始化为最大可能时间

        // 二分搜索循环
        while (lowBound <= highBound) {
            int midTime = (lowBound + highBound) / 2;  // 中间时间值
            if (canServeInTime(midTime)) {
                // 如果midTime可行，尝试更小的时间
                optimalTime = midTime;
                highBound = midTime - 1;
            } else {
                // 如果midTime不可行，需要更大的时间
                lowBound = midTime + 1;
            }
        }

        // 输出结果
        // 第一行：最优时间
        cout << optimalTime << endl;
        // 第二行：停靠楼层数量 + 停靠楼层列表
        cout << bestStops.size();
        for (int i = 0; i < bestStops.size(); i++) {
            cout << " " << bestStops[i];
        }
        cout << endl;
    }

    return 0;
}

