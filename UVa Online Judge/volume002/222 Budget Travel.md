[UVa 222 Budget Travel](https://blog.csdn.net/metaphysis/article/details/161085031)

## 题目分析

本题是一个汽车旅行预算问题。旅行者从起点出发，驾驶汽车前往目的地，沿途有若干加油站。旅行者需要支付汽油费用（每加仑价格在各加油站不同）以及每次停靠加油站时购买零食的 $2.00$ 美元。需要计算从起点到目的地所需的最小总费用（包括出发前在起点加满油箱的费用）。

驾驶规则如下：

* 出发时油箱是满的。
* 司机只在必要时停靠加油站，即当油箱内汽油超过半箱时，除非无法到达下一个加油站或目的地，否则不会停靠。
* 每次停靠都会将油箱加满，并支付 $2.00$ 美元的零食费用。
* 每笔费用四舍五入到最近的美分（即小数点后两位）。
* 只需使用足够到达下一个加油站或目的地的汽油，不需要安全余量。

## 解题思路

本题采用 $\texttt{DFS}$（深度优先搜索）进行求解。

**数据处理**：为了方便处理，将起点视为第 $0$ 个站点（距离为 $0$，价格为起点的油价），将目的地视为最后一个站点（距离为目的地距离，价格为 $0$）。沿途的加油站按距离从小到大排列，直接存入数组中。

**状态表示**：使用结构体 $\texttt{driver}$ 表示当前状态，包含当前所在加油站索引、已行驶距离和当前总花费（单位为美分，避免浮点精度问题）。

**搜索策略**：

1. 从当前站点出发，计算在满油状态下能够到达的最远距离 $end$。
2. 如果 $end$ 能够直接到达目的地，则更新最小花费。
3. 否则，遍历当前站点之后的所有可到达的加油站：
   - 计算到达该加油站消耗的汽油量和加油后的剩余行驶里程。
   - 根据规则判断是否必须停靠：如果剩余行驶里程能够到达下一个加油站，且当前油箱油量超过半箱，则可以选择不停靠（使用 $\texttt{continue}$ 跳过）。
   - 如果需要停靠，则计算本次花费（汽油费用 $\times$ 油价，四舍五入取整，加上 $200$ 美分的零食费用）。
   - 使用记忆化剪枝：如果曾经以更小花费到达过该站点，则跳过。
   - 更新状态并递归搜索。

**费用处理**：所有费用以美分为单位存储，输出时转换为美元并正确格式化小数点后两位。

## 代码实现

```cpp
// Budget Travel
// UVa ID: 222
// Verdict: Accepted
// Submission Date: 2016-05-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 加油站结构体
struct station {
    int index;                 // 站点索引
    double milesFromOrigin;    // 距离起点的距离（英里）
    double pricePerGallon;     // 每加仑价格（美分）
    int minimumCost;           // 到达该站点时的最小花费（美分）
};

// 司机状态结构体
struct driver {
    int index;                 // 当前所在站点索引
    double milesTravel;        // 已行驶距离（英里）
    int totalCost;             // 当前总花费（美分）
};

double totalDistance, capacityOfTank, costAtStart;  // 总距离、油箱容量、起点加油费用
double milesPerGallon, milesFromOrigin, pricePerGallon; // 每加仑英里数、临时变量
int counter, minimumCost;       // 加油站数量、全局最小花费

vector<station> stations;       // 所有站点（包含起点和终点）

// 深度优先搜索
void dfs(driver aDriver) {
    // 当前满油状态下能到达的最远距离
    double end = aDriver.milesTravel + capacityOfTank * milesPerGallon;
    
    // 如果能直接到达目的地
    if (end >= totalDistance) {
        // 更新最小花费
        if (minimumCost < 0 || aDriver.totalCost < minimumCost)
            minimumCost = aDriver.totalCost;
        return;
    }

    // 遍历当前站点之后的可到达站点（最后一个站点是目的地，不在此遍历）
    for (int i = aDriver.index + 1; i < stations.size() - 1; i++) {
        // 如果该站点在可到达范围内
        if (end >= stations[i].milesFromOrigin) {
            // 计算到达该站点消耗的汽油量（加仑）
            double gasolineUsed = (stations[i].milesFromOrigin - aDriver.milesTravel) / milesPerGallon;
            // 加满后能额外行驶的里程（英里）
            double travel = (capacityOfTank - gasolineUsed) * milesPerGallon;
            
            // 根据规则判断是否必须停靠：
            // 如果加满后能到达下一个加油站，且当前油量超过半箱，则可以选择不停靠
            if (travel >= (stations[i + 1].milesFromOrigin - stations[i].milesFromOrigin) &&
                2 * gasolineUsed <= capacityOfTank)
                continue;
            
            // 创建新状态
            driver newDriver = aDriver;
            // 添加本次加油费用（四舍五入到美分）
            newDriver.totalCost += round(gasolineUsed * stations[i].pricePerGallon);
            // 添加零食费用（2美元 = 200美分）
            newDriver.totalCost += 200;
            
            // 记忆化剪枝：如果曾经以更小花费到达过该站点，则跳过
            if (stations[i].minimumCost > 0 && stations[i].minimumCost < newDriver.totalCost)
                continue;
            
            // 记录到达该站点时的最小花费
            stations[i].minimumCost = newDriver.totalCost;
            // 更新状态
            newDriver.milesTravel = stations[i].milesFromOrigin;
            newDriver.index = i;
            
            // 继续递归搜索
            dfs(newDriver);
        }
        else
            break;  // 由于站点按距离排序，后面的站点距离更远，直接退出
    }
}

int main() {
    int cases = 0;
    
    while (cin >> totalDistance) {
        if (totalDistance < 0.0)
            break;
            
        stations.clear();
        
        // 读入油箱容量、每加仑英里数、起点加油费用、加油站数量
        cin >> capacityOfTank >> milesPerGallon >> costAtStart >> counter;
        
        // 添加起点作为第0个站点，费用为0（暂不记录，后续单独处理）
        stations.push_back((station){0, milesFromOrigin, pricePerGallon, 0});
        
        // 读入沿途加油站信息
        for (int i = 1; i <= counter; i++) {
            cin >> milesFromOrigin >> pricePerGallon;
            stations.push_back((station){i, milesFromOrigin, pricePerGallon, -1});
        }
        
        // 添加目的地作为最后一个站点（油价为0）
        stations.push_back((station){counter + 1, totalDistance, 0.0, -1});
        
        // 输出数据集编号
        cout << "Data Set #" << ++cases << endl;
        
        // 初始化最小花费为 -1（表示未找到）
        minimumCost = -1;
        
        // 初始化司机状态
        driver aDriver;
        aDriver.index = 0;                           // 从起点出发
        aDriver.totalCost = (int)(costAtStart * 100.0); // 起点加油费用（转换为美分）
        aDriver.milesTravel = 0.0;                   // 已行驶距离为0
        
        // 开始深度优先搜索
        dfs(aDriver);
        
        // 输出结果，格式化为美元（两位小数）
        cout << "minimum cost = $";
        cout << (minimumCost / 100);
        cout << ".";
        if (minimumCost % 100 < 10)
            cout << "0";
        cout << (minimumCost % 100);
        cout << endl;
    }
    
	return 0;
}
```
