[UVa 319 Pendulum](https://blog.csdn.net/metaphysis/article/details/161477841)

## 题目描述

考虑一个用绳子挂在墙壁钩子上的摆锤。当被推动时，这个摆锤会来回摆动。现在想象在摆锤绳子的路径上放置其他钩子。摆锤会绕过它们，甚至可能围绕它们打转。一般来说，它会遵循比之前复杂得多的路径。一段时间后，摆锤的运动将重复，摆锤将进入一个周期性轨道。需要计算摆锤完成一个周期所经过的距离。

更正式地说，我们在墙上放置一个笛卡尔坐标系。摆锤的绳子固定在原点 $(0,0)$。$x$ 轴指向右，$y$ 轴指向上。摆锤的绳子长度为 $r$。摆锤从 $(-r, 0)$ 位置释放，开始向右摆动。此外，平面上还有 $n$ 个额外的钩子，可能影响摆锤的路径。

理想假设：
- 钩子和绳子的直径为零
- 摆锤没有能量损失（如摩擦）
- 摆锤永远不会碰到钩子，只有绳子会碰到
- 绳子由某种未来材料制成，只在接触钩子处弯曲，其他地方保持刚性

由于重力作用，摆锤永远不会达到高于起始点的高度（即永远不会高于 $x$ 轴）。它要么再次达到初始高度，要么无限地绕钩子旋转。

### 输入格式

输入文件包含多个测试用例。每个测试用例以一行包含整数 $n$（钩子数量，$1 \leq n < 500$）和实数 $r$（摆绳长度）开始。接下来的 $n$ 行每行包含两个整数，表示对应钩子的 $x$ 和 $y$ 坐标。

文件以 $r = 0$ 的用例结束，该用例不处理。

### 输出格式

对于每个用例，输出一行 `Pendulum #1`、`Pendulum #2` 等。然后输出一行，包含摆锤完成一个周期所经过的距离（不计算到达轨道起点所经过的距离），精确到小数点后两位。每个测试用例后输出一个空行。

### 样例输入

```
2
16.0
3 -4
-3 -4
1
18.0
5 -12
0
0
```

### 样例输出

```
Pendulum #1
Length of periodic orbit = 87.66

Pendulum #2
Length of periodic orbit = 31.42
```

---

## 题目分析

### 问题的本质

这是一个**几何模拟**问题。摆锤从左侧水平位置释放，在重力作用下向右摆动。绳子在遇到钩子时会弯曲，绳子的一部分会“缠绕”在钩子上，从而改变有效摆长。

关键物理原理：
- 摆锤的势能守恒，因此它永远不会超过初始高度（$y = 0$）
- 绳子总是拉紧的
- 当绳子碰到钩子时，钩子到摆锤之间的绳子保持直线，而钩子到悬挂点之间的绳子则“绕过”钩子

### 运动过程

摆锤从 $(-r, 0)$ 释放。在重力作用下，它向右下方运动，然后向上摆动。由于能量守恒，它将在 $y$ 轴上的某个最高点停止（但不会超过 $y = 0$）。如果过程中没有碰到任何钩子，它会在初始高度处停止，然后反向摆回，形成一个完整的周期。

当绳子碰到钩子时，钩子成为新的“支点”。此时，有效摆长变为从钩子到摆锤的距离。摆锤继续摆动，可能会碰到更多钩子。

### 轨道类型

最终，摆锤会进入两种可能的周期性轨道：
1. **左右摆动**：在 $x$ 轴两侧来回摆动，最高点为 $y = 0$
2. **绕圈**：完全围绕一个钩子旋转（类似于圆周运动）

### 模拟方法

由于钩子数量有限，摆锤的绳子每次只会缠绕在最“外侧”的钩子上。我们可以模拟摆锤的运动，每一步确定下一个被绳子接触的钩子，然后更新有效摆长和角度范围，直到进入周期性状态。

---

## 解题思路

### 步骤一：坐标系与初始条件

- 悬挂点（主钩子）：$(0,0)$
- 初始位置：$(-r, 0)$
- 初始角度：$\theta = -\pi$（从负 $x$ 轴方向开始）

### 步骤二：钩子筛选

只有满足以下条件的钩子才可能被绳子碰到：
- 钩子在 $x$ 轴下方或 $x$ 轴上（$y \le 0$），因为摆锤永远不会高于 $x$ 轴
- 钩子到当前悬挂点的距离 ≤ 当前有效摆长

### 步骤三：确定下一个钩子

在当前位置，绳子从当前悬挂点 $O$ 延伸到摆锤 $P$。当摆锤摆动时，绳子会扫过一定的角度范围。下一个被绳子接触的钩子是在这个角度范围内**最靠近绳子**的那个。

具体来说，对于每个候选钩子 $H$：
- 计算极角 $\theta_H = \text{atan2}(H_y - O_y, H_x - O_x)$
- 这个角度必须在当前扫过的角度范围内（从上次角度到本次角度）
- 选择使绳子偏转最大的钩子（即角度变化最小的方向？实际上是选择最“靠右”的钩子）

### 步骤四：更新状态

当绳子碰到钩子 $H$ 时：
- 从 $O$ 到 $H$ 的一段绳子被“固定”在钩子上
- 新的悬挂点变为 $H$
- 新的有效摆长变为原摆长减去 $|OH|$
- 新的角度为从 $H$ 到 $P$ 的方向角
- 摆锤继续摆动

### 步骤五：终止条件

模拟终止条件：
- 如果当前摆长大于或等于悬挂点到 $x$ 轴的距离，摆锤可以到达 $x$ 轴。此时，它会在 $x$ 轴上反弹，形成左右摆动周期。轨道长度 = $2 \times$（从当前角度到 $x$ 轴的弧长）
- 如果当前摆长小于悬挂点到 $x$ 轴的距离，摆锤无法到达 $x$ 轴，它会绕悬挂点做圆周运动。轨道长度 = $2\pi \times$ 摆长

### 步骤六：轨道长度计算

在模拟过程中，累加每次摆锤摆过的弧长（$弧长 = 摆长 \times |\Delta\theta|$）。当到达 $x$ 轴或进入圆周运动时，加上最后一段弧长，然后乘以 $2$（因为左右摆动对称）得到完整周期的长度。

---

## 算法复杂度分析

### 时间复杂度

- 最多有 $n$ 个钩子
- 每一步确定下一个钩子：$O(n)$
- 最多 $O(n)$ 步（每个钩子最多被缠绕一次）
- 总复杂度：$O(n^2)$，$n < 500$，完全可行

### 空间复杂度

- 存储钩子坐标：$O(n)$
- 总空间复杂度：$O(n)$

---

## 正确性证明

**引理 1**：摆锤的运动由绳子与钩子的接触点决定。每次接触后，绳子被“缩短”，摆锤绕新支点摆动。

证明：绳子总是拉紧的，当碰到钩子时，钩子成为新的支点。由于绳子不会打滑，钩子到摆锤之间的部分保持直线。$\square$

**引理 2**：在摆锤摆动过程中，绳子每次只会碰到最“外侧”的钩子（即最靠近当前绳子方向的钩子）。

证明：如果存在多个可能的钩子，最外侧的钩子会首先被绳子碰到。$\square$

**引理 3**：模拟会在有限步内终止，因为每次有效摆长严格减小，且钩子数量有限。

证明：每次缠绕都会使有效摆长减小（减去 $|OH| > 0$），因此最多进行 $n$ 步。$\square$

**引理 4**：最终轨道要么是左右摆动（到达 $x$ 轴），要么是圆周运动（无法到达 $x$ 轴）。

证明：能量守恒决定了摆锤无法超过初始高度。如果有效摆长足够长，它可以回到 $y = 0$；否则，它会在最低点以下摆动，形成圆周运动。$\square$

---

## 参考代码

```cpp
// Pendulum
// UVa ID: 319
// Verdict: Accepted
// Submission Date: 2017-05-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7, PI = 2.0 * acos(0.0);

struct point
{
    double x, y;
};

// 计算两点间距离
double getDist(const point & p1, const point & p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// 叉积计算：向量 ab 和 ac 的叉积
double cp(const point &a, const point &b, const point &c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases = 0;
    double x1, y1, lengthOfString;

    while (cin >> n >> lengthOfString, lengthOfString > 0.0)
    {
        cout << "Pendulum #" << ++cases << '\n';

        // 钩子列表，原点（主钩子）始终在列表中
        vector<point> hooks;
        hooks.push_back(point{0.0, 0.0});

        for (int i = 0; i < n; i++)
        {
            cin >> x1 >> y1;

            // 忽略 y > 0 的钩子（摆锤无法到达）
            if (y1 > 0) continue;
            // 忽略距离超过摆长的钩子
            if (lengthOfString + EPSILON < sqrt(x1 * x1 + y1 * y1)) continue;

            hooks.push_back(point{x1, y1});
        }

        int lastHookIdx = 0;           // 当前悬挂点索引
        double lastTheta = -PI;        // 当前角度（从负 x 轴开始）
        double orbit = 0.0;            // 轨道长度

        while (true)
        {
            int nextHookIdx = -1;
            // 当前摆长下，摆锤能到达的最右角度（与 x 轴交点）
            double rightmostAngle = asin(fabs(hooks[lastHookIdx].y) / lengthOfString);

            // 寻找下一个被绳子碰到的钩子
            for (int i = 0; i < hooks.size(); i++)
            {
                if (i == lastHookIdx) continue;

                double currentDist = getDist(hooks[i], hooks[lastHookIdx]);
                if (lengthOfString + EPSILON < currentDist) continue;

                double theta = atan2(hooks[i].y - hooks[lastHookIdx].y,
                                     hooks[i].x - hooks[lastHookIdx].x);
                
                // 检查角度是否在当前摆动范围内
                if (theta - rightmostAngle > EPSILON || theta + EPSILON < lastTheta)
                {
                    if (fabs(hooks[lastHookIdx].y) < lengthOfString + EPSILON) continue;
                }

                // 选择最合适的钩子（使绳子偏转最大的）
                if (nextHookIdx == -1)
                {
                    nextHookIdx = i;
                }
                else
                {
                    double CP = cp(hooks[lastHookIdx], hooks[nextHookIdx], hooks[i]);
                    if (fabs(CP) < EPSILON)
                    {
                        // 共线时，选择距离更近的
                        double lastDist = getDist(hooks[nextHookIdx], hooks[lastHookIdx]);
                        if (lastDist + EPSILON < currentDist)
                            nextHookIdx = i;
                    }
                    else if (CP < 0)
                    {
                        nextHookIdx = i;
                    }
                }
            }

            // 没有更多钩子，进入周期性轨道
            if (nextHookIdx == -1)
            {
                if (lengthOfString < fabs(hooks[lastHookIdx].y) + EPSILON)
                {
                    // 无法到达 x 轴，做圆周运动
                    orbit = 2.0 * PI * lengthOfString;
                }
                else
                {
                    // 左右摆动
                    orbit += lengthOfString * (rightmostAngle - lastTheta);
                    orbit *= 2.0;
                }

                cout << "Length of periodic orbit = ";
                cout << fixed << setprecision(2) << orbit << "\n\n";
                break;
            }

            // 累加弧长，更新状态
            double nextTheta = atan2(hooks[nextHookIdx].y - hooks[lastHookIdx].y,
                                     hooks[nextHookIdx].x - hooks[lastHookIdx].x);
            orbit += lengthOfString * fabs(nextTheta - lastTheta);
            lengthOfString -= getDist(hooks[nextHookIdx], hooks[lastHookIdx]);
            lastHookIdx = nextHookIdx;
            lastTheta = nextTheta;
        }
    }

    return 0;
}
```

---

## 总结

本题的核心在于：
1. **几何模拟**：每次找到下一个被绳子接触的钩子
2. **状态更新**：改变悬挂点和有效摆长
3. **终止条件**：根据是否到达 $x$ 轴区分两种轨道类型

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 悬挂点 | 原点为主钩子 |
| 初始角度 | $-\pi$（从负 $x$ 轴） |
| 钩子筛选 | $y \le 0$，距离 ≤ 摆长 |
| 下一个钩子 | 使绳子偏转最大的钩子 |
| 弧长计算 | $l \times |\Delta\theta|$ |
| 轨道类型 | 左右摆动 或 圆周运动 |

### 物理直觉

摆锤的运动路径是所有可能路径中能量最小的那条。绳子的弯曲发生在钩子处，而钩子的选择由几何约束决定。这种模拟方法虽然简单，但正确反映了系统的动力学行为。
