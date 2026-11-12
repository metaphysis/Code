[UVa 145 Gondwanaland Telecom](https://blog.csdn.net/metaphysis/article/details/157464278)

## 题目描述

$\texttt{Gondwanaland Telecom}$ 公司根据通话距离和一天中的时间段对电话呼叫进行计费。计费依据如下费率表，其中计费步长与距离相关：

| 计费步长（距离） | 白天费率（$8:00-18:00$） | 晚间费率（$18:00-22:00$） | 夜间费率（$22:00-8:00$） |
|----------------|---------------------|---------------------|---------------------|
| $A$              | $0.10$               | $0.06$               | $0.02$               |
| $B$              | $0.25$               | $0.15$               | $0.05$               |
| $C$              | $0.53$               | $0.33$               | $0.13$               |
| $D$              | $0.87$               | $0.47$               | $0.17$               |
| $E$              | $1.44$               | $0.80$               | $0.30$               |

所有费率均为每分钟通话的费用（美元）。跨越不同费率时段的通话，将按照在各时段内实际通话时间分别计费。例如，一个通话从下午 $5:58$ 开始，到下午 $6:04$ 结束，将按 $2$ 分钟白天费率和 $4$ 分钟晚间费率计费。通话时间不足一分钟不记录，且任何通话不会超过 $24$ 小时。

编写一个程序，读取通话详情，计算相应费用。

## 输入格式

输入每行包含：计费步长（大写字母 `A` 到 `E`）、被叫号码（$7$ 位数字和连字符组成的字符串，格式规范）、通话开始和结束时间，各部分之间恰好由一个空格分隔。时间以 $24$ 小时制的小时和分钟表示，小时和分钟之间用一个空格分隔，每个数字为两位。输入以单独一行包含一个 `#` 结束。

## 输出格式

输出包含：被叫号码、通话在各计费类别中的分钟数、计费步长和总费用，格式如下所示。

注意：下面示例输出的第一行并非实际输出内容，仅用于展示所需的制表格式。

**示例输入：**

```
A 183-5724 17 58 18 04
#
```

**示例输出：**

```
     183-5724     2     4     0 A    0.44
```

## 题目分析与解题思路

本题的核心在于 **时间段的划分与累加计算** 。我们需要将一个通话的时长，按照三个不同的费率时段（白天、晚间、夜间）进行拆分，然后根据给定的距离费率步长（$A$ 到 $E$）计算总费用。

### 关键点分析

1. **时间处理**  
   题目给出的时间是 $24$ 小时制，但通话可能跨越午夜（例如从 $23:50$ 到 $00:10$）。为了简化处理，我们可以将时间全部转换为**从 $00:00$ 开始的分钟数**。这样，通话的起始时间和结束时间就可以表示为一个整数（分钟数）。

2. **跨天通话**  
   如果结束时间小于开始时间，说明通话跨越了午夜，需要将结束时间加上 $1440$ 分钟（一天的总分钟数）。此外，题目明确说明“通话不会超过 $24$ 小时”，且如果开始时间等于结束时间，则视为通话 $24$ 小时（即加上 $1440$ 分钟）。

3. **费率时段划分**  
   一天中的费率时段如下：
   - 白天：$08:00 - 18:00$（分钟数：$480$ - $1079$）
   - 晚间：$18:00 - 22:00$（分钟数：$1080$ - $1319$）
   - 夜间：$22:00 - 08:00$（分钟数：$1320$ - $1439$ 和 $0$ - $479$）
   
   由于通话可能跨越午夜，我们需要考虑**两天的时段**。因此，我们可以将时段扩展为两个 $24$ 小时周期，即 $0$ 到 $2880$ 分钟。

4. **计算各时段通话分钟数**  
   我们需要计算在扩展后的时间段（从 $startMin$ 到 $endMin$）内，落在每个费率时段的总分钟数。可以通过一个辅助函数 `getAnd` 来计算两个时间段的交集分钟数，并注意**通话分钟数应减去 $1$**（因为通话的“分钟”是从开始时刻起算的整数分钟，例如从 $5:58$ 到 $6:04$，实际计费分钟为 $2$ 和 $4$，而非 $3$ 和 $5$）。

### 算法步骤

1. 读入一行数据，若为 `#` 则结束。
2. 将开始和结束时间转换为从 $00:00$ 开始的分钟数。
3. 处理跨天情况：
   - 若结束时间小于开始时间，或两者相等，则结束时间加上 $1440$ 分钟。
4. 定义三个变量分别记录白天、晚间、夜间的总分钟数。
5. 通过 `getAnd` 函数计算在扩展后的时间段内，与各费率时段（考虑两个周期）的交集分钟数，并累加。
6. 根据距离步长（$A-E$）和对应的费率表计算总费用。
7. 按格式输出结果。

### 时间复杂度

每个通话的处理时间主要花费在 `getAnd` 函数的循环上，最坏情况下需要遍历 $2880$ 分钟，因此时间复杂度为 $O(2880) = O(1)$，对于题目给定的输入规模非常高效。

## 代码实现

```cpp
// Gondwanaland Telecom
// UVa ID: 145
// Verdict: Accepted
// Submission Date: 2016-01-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// In description: "Calls less than a minute are not recorded and no call 
// may last more than 24 hours. "
// I miss the case of whole 24 hours! (start time == end time)

#include <bits/stdc++.h>
using namespace std;

int getAnd(int start1, int end1, int start2, int end2) {
    int minutes = 0;
    for (int i = start1; i <= end1; i++)
        if (i >= start2 && i <= end2)
            minutes++;
    return (minutes > 0 ? (minutes - 1) : 0);
}

int main() {
    string line, distance, number;
    int startHour, startMin, endHour, endMin;
    double cost[5][3] = {
        { 0.10, 0.06, 0.02 }, { 0.25, 0.15, 0.05 },
        { 0.53, 0.33, 0.13 }, { 0.87, 0.47, 0.17 },
        { 1.44, 0.80, 0.30 }
    };
    while (getline(cin, line), line != "#") {
        istringstream iss(line);
        iss >> distance >> number >> startHour >> startMin >> endHour >> endMin;
        startMin += startHour * 60;
        endMin += endHour * 60;
        if (endHour < startHour) endMin += 1440;
        else if (endHour == startHour && endMin < startMin) endMin += 1440;
        else if (endHour == startHour && endMin == startMin) endMin += 1440;
            
        double totalCost = 0.0;
        int dayMin = 0, eveningMin = 0, nightMin = 0;
        
        dayMin += getAnd(startMin, endMin, 480, 1080);
        dayMin += getAnd(startMin, endMin, 1920, 2520);
        eveningMin += getAnd(startMin, endMin, 1080, 1320);
        eveningMin += getAnd(startMin, endMin, 2520, 2760);
        nightMin += getAnd(startMin, endMin, 0, 480);
        nightMin += getAnd(startMin, endMin, 1320, 1920);
        nightMin += getAnd(startMin, endMin, 2760, 2880);
            
        totalCost += dayMin * cost[distance[0] - 'A'][0];
        totalCost += eveningMin * cost[distance[0] - 'A'][1];
        totalCost += nightMin * cost[distance[0] - 'A'][2];
        
        cout << setw(10) << right << number;
        cout << setw(6) << right << dayMin;
        cout << setw(6) << right << eveningMin;
        cout << setw(6) << right << nightMin;
        cout << setw(3) << right << distance;
        cout << setw(8) << right << fixed << setprecision(2) << totalCost << endl;
    }
    return 0;
}
```

## 总结

本题是一道典型的时间计算类模拟题，难点在于正确处理跨天通话和各费率时段的划分。通过将时间统一转换为分钟数，并扩展为两个周期来处理跨午夜的通话，可以大大简化计算逻辑。代码实现中需要注意边界条件，特别是开始时间等于结束时间的情况，应视为 $24$ 小时通话。
