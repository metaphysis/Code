[UVa 361 Cops and Robbers](https://blog.csdn.net/metaphysis/article/details/161611212)

## 题目描述

你要模拟一个警察与小偷的游戏。在这个游戏中，警察、小偷和其他市民被表示为二维平面上的点。如果一个市民位于三个警察构成的三角形内（包括边界），则称该市民是 **`safe`**（安全的）。如果一个市民不是 `safe`，但位于三个小偷构成的三角形内，则称该市民是 **`robbed`**（被抢的）。如果一个市民既不满足上述条件，则称其为 **`neither`**（都不是）。

给定一组警察、小偷和若干市民查询，需要高效地判断每个市民的状态。

### 输入格式

输入包含多个数据集。每个数据集的第一行包含三个非负整数 $c$、$r$、$o$：警察、小偷和其他市民的数量。$c$、$r$、$o$ 均不超过 $200$。

接下来 $c$ 行，每行包含一个警察的 $(x,y)$ 坐标。
接下来 $r$ 行，每行包含一个小偷的 $(x,y)$ 坐标。
接下来 $o$ 行，每行包含一个市民的 $(x,y)$ 坐标。

所有坐标均为 $-500$ 到 $500$ 之间的整数。每个数据集后跟一个空行。当 $c = r = o = 0$ 时，程序停止处理。

### 输出格式

对于每个数据集，首先输出一行标识数据集。对于每个市民，输出一行：

```
Citizen at (x,y) is status.
```

其中 `status` 是 `safe`、`robbed` 或 `neither`。每个数据集输出后跟一个空行。

### 样例输入

```
3 3 2
0 0
10 0
0 10
20 20
20 0
0 20
5 5
15 15

3 3 1
0 0
10 0
0 10
20 20
20 0
0 20
40 40

0 0 0
```

### 样例输出

```
Data set 1:
     Citizen at (5,5) is safe.
     Citizen at (15,15) is robbed.

Data set 2:
     Citizen at (40,40) is neither.
```

---

## 题目分析

### 问题的本质

这是一个**点在三角形内判断**问题。需要判断每个市民点是否位于任意三个警察构成的三角形内，如果不是，再判断是否位于任意三个小偷构成的三角形内。

### 关键难点

- 警察/小偷数量最多 $200$，直接枚举所有三元组 $O(200^3) = 8 \times 10^6$，再乘上市民数量（最多 $200$），总复杂度约为 $1.6 \times 10^9$，不可接受。
- 需要优化：只检查可能包含该市民的三角形。

### 优化策略

1. **排序**：按 $x$ 坐标对警察和小偷排序
2. **剪枝**：如果市民的 $x$ 坐标小于最左边警察（小偷）的 $x$ 坐标，或大于最右边警察（小偷）的 $x$ 坐标，则不可能在三角形内
3. **Y 坐标剪枝**：同样检查 Y 坐标范围
4. **限制枚举范围**：只枚举与市民 $x$ 坐标相近的警察/小偷

在代码中：
- 使用 `lower_bound` 找到第一个 $x$ 坐标 $\geq$ 市民 $x$ 的警察位置
- 只枚举从该位置开始的警察，以及前面的警察
- 当警察数量很少时（$c \leq 200$），即使 $O(c^3)$ 枚举，每个市民的复杂度为 $O(c^3)$，总复杂度 $O(o \times c^3) \approx 200 \times 8 \times 10^6 = 1.6 \times 10^9$，实际运行时间 $0.490$ 秒，说明剪枝非常有效

---
## 参考代码

```cpp
// Cops and Robbers
// UVa ID: 361
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.490s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point
{
    int x, y;
    // 按 x 排序，x 相同时按 y 排序
    bool operator<(const point &another) const
    {
        if (x != another.x)
            return x < another.x;
        else
            return y < another.y;
    }
};

vector<point> cops, robbers, citizens;
int c, r, o, minCopsY, maxCopsY, minRobbersY, maxRobbersY;

// 叉积：向量 ab 和 ac 的叉积
inline int direction(point &a, point &b, point &c)
{
    return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 判断市民是否在任意三个警察构成的三角形内
bool isSafe(int person)
{
    // 快速剪枝
    if (citizens[person].x < cops.front().x) return false;
    if (citizens[person].x > cops.back().x) return false;
    if (citizens[person].y < minCopsY) return false;
    if (citizens[person].y > maxCopsY) return false;
    
    // 找到第一个 x >= 市民 x 的警察
    int start = lower_bound(cops.begin(), cops.end(), citizens[person]) - cops.begin();
    for (int i = start; i < cops.size(); i++)
        for (int j = 0; j < i; j++)
            for (int k = j + 1; k < i; k++)
            {
                int d1 = direction(cops[i], cops[j], citizens[person]);
                int d2 = direction(cops[j], cops[k], citizens[person]);
                int d3 = direction(cops[k], cops[i], citizens[person]);
                if (d1 <= 0 && d2 <= 0 && d3 <= 0) return true;
                if (d1 >= 0 && d2 >= 0 && d3 >= 0) return true;
            }
    return false;
}

// 判断市民是否在任意三个小偷构成的三角形内
bool isRobbed(int person)
{
    if (citizens[person].x < robbers.front().x) return false;
    if (citizens[person].x > robbers.back().x) return false;
    if (citizens[person].y < minRobbersY) return false;
    if (citizens[person].y > maxRobbersY) return false;
    
    int start = lower_bound(robbers.begin(), robbers.end(), citizens[person]) - robbers.begin();
    for (int i = start; i < robbers.size(); i++)
        for (int j = 0; j < i; j++)
            for (int k = j + 1; k < i; k++)
            {
                int d1 = direction(robbers[i], robbers[j], citizens[person]);
                int d2 = direction(robbers[j], robbers[k], citizens[person]);
                int d3 = direction(robbers[k], robbers[i], citizens[person]);
                if (d1 <= 0 && d2 <= 0 && d3 <= 0) return true;
                if (d1 >= 0 && d2 >= 0 && d3 >= 0) return true;
            }
    return false;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int cases = 0, x, y;
    while (cin >> c >> r >> o)
    {
        if (c == 0 && r == 0 && o == 0) break;
        
        cops.clear();
        robbers.clear();
        citizens.clear();
        
        minCopsY = 1000, maxCopsY = -1000;
        minRobbersY = 1000, maxRobbersY = -1000;
        
        // 读取警察
        for (int i = 1; i <= c; i++)
        {
            cin >> x >> y;
            cops.push_back((point){x, y});
            minCopsY = min(minCopsY, y);
            maxCopsY = max(maxCopsY, y);
        }
        // 读取小偷
        for (int i = 1; i <= r; i++)
        {
            cin >> x >> y;
            robbers.push_back((point){x, y});
            minRobbersY = min(minRobbersY, y);
            maxRobbersY = max(maxRobbersY, y);
        }
        // 读取市民
        for (int i = 1; i <= o; i++)
        {
            cin >> x >> y;
            citizens.push_back((point){x, y});
        }
        
        // 排序
        sort(cops.begin(), cops.end());
        sort(robbers.begin(), robbers.end());
        
        cout << "Data set " << ++cases << ":" << endl;
        for (int i = 0; i < citizens.size(); i++)
        {
            cout << "     Citizen at (" << citizens[i].x << "," << citizens[i].y << ") is ";
            if (isSafe(i)) 
                cout << "safe." << endl;
            else if (isRobbed(i)) 
                cout << "robbed." << endl;
            else 
                cout << "neither." << endl;
        }
        
        cout << endl;
    }
    
    return 0;
}
```
