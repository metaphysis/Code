[UVa 149 Forests](https://blog.csdn.net/metaphysis/article/details/157510422)

## 题目分析

这道题来源于一个常见的观察现象：在森林中，当你站在某个位置观察时，远处的树木可能会被近处的树木遮挡，导致你无法看清远处的树木。题目中给出了一个数学模型：树木被抽象为直径相同的圆柱体，它们的中心位于一个单位间距的无限矩形网格上。观察者站在某个坐标点 $(x, y)$ 上，用一只眼睛观察。只有当一棵树在观察者眼中所张的视角大于 $0.01$ 度，并且它的树干没有被更近的树木遮挡时，这棵树才是可见的。

**关键点：**
- 树木直径 $d$ 满足 $0.1 \le d \le x, y \le 1-d$。
- 网格是无限的，但题目通过坐标缩放保证了输入坐标在 $[0,1]$ 之间。
- 需要计算从给定观察点可以看到的树木数量。

## 解题思路

由于网格是无限的，直接枚举所有树木是不可能的。我们需要找到一种有效的方法来判断哪些树是可见的。

### 1. 几何模型
每棵树是一个直径为 $d$ 的圆柱体。观察者位于 $O(x, y)$，树木中心位于网格点 $T(i, j)$。要判断 $T$ 是否可见，需要考虑：
- 视角大小：树木在观察者眼中的张角必须大于 $0.01$ 度。
- 遮挡关系：如果存在另一棵树 $N$ 比 $T$ 更接近观察者，并且从 $O$ 到 $T$ 的视线被 $N$ 的树干遮挡，那么 $T$ 不可见。

### 2. 遮挡判定
对于两棵树 $N$（近）和 $F$（远），我们需要判断 $N$ 是否遮挡了 $F$。这可以通过计算角度来判断：
设：
- $a = |ON|^2$
- $b = |OF|^2$
- $c = |NF|^2$
- $A = \arcsin(d / (2\sqrt{a}))$（$N$ 树干的半张角）
- $B = \arcsin(d / (2\sqrt{b}))$（$F$ 树干的半张角）
- $\cos C = (a + b - c) / (2\sqrt{a}\sqrt{b})$，$C = \arccos(\cos C)$（$O$ 到两棵树中心的夹角）

如果 $C - A - B \le 0.01$ 度（转换为弧度比较），则 $N$ 遮挡了 $F$。

### 3. 枚举范围
由于网格无限，但树木大小固定，观察点位置有限，实际上只需要检查一定范围内的树木即可：
- 将坐标乘以 $100$ 转换为整数网格，便于计算。
- 将平面分为四个象限，每个象限内按“深度”（距离观察点的网格层数）逐步向外检查。
- 对于每一层，检查该层的角点和边上的树木是否可见。
- 设置最大深度为 $10$，这足以覆盖所有可能可见的树木。

### 4. 实现细节
- 使用 `isObscured` 函数判断两棵树之间的遮挡关系。
- 使用 `isVisible` 函数判断一棵树是否被当前层内的任何更近的树遮挡。
- 主函数循环读取输入，对每个测试用例调用 `visibleTrees` 计算可见树木数量并输出。

## 代码实现

```cpp
// Forests
// UVa ID: 149
// Verdict: Accepted
// Submission Date: 2016-02-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = 3.14159265358;
struct point {
    double x, y;
};
double diameter, x, y;
point base[4] = { {100, 100}, {0, 100}, {0, 0}, {100, 0} };
int steps[4][2] = { {100, 100}, {-100, 100}, {-100, -100}, {100, -100} };
int subSteps[8][2] =
    { {-100, 0}, {0, -100}, {100, 0}, {0, -100}, {100, 0}, {0, 100}, {-100, 0},
    {0, 100} };
double maxCos = cos(0.01 / 180 * PI);

bool isObscured(point near, point far) {
    double a = pow(x - near.x, 2) + pow(y - near.y, 2);
    double b = pow(x - far.x, 2) + pow(y - far.y, 2);
    double c = pow(near.x - far.x, 2) + pow(near.y - far.y, 2);
    double A = asin(diameter / 2 / sqrt(a));
    double B = asin(diameter / 2 / sqrt(b));
    double cosC = (a + b - c) / (2 * sqrt(a) * sqrt(b));
    // 因为余弦的值域为[-1, 1]，故绝对值大于 1 的值取反余弦会得到一个非数值（NAN），
    // 而且题目中提到当角度大于 0.01 度时人眼才能区分，因此需要设定一个阈值。
    // 此处是关键，否则很可能 Wrong Answer。
    if (cosC >= maxCos) return true;
    double C = acos(cosC);
    return ((C - A - B) * 180 / PI) <= 0.01f;
}

bool isVisible(point tree, int depth, int quadrant) {
    for (int subDepth = 0; subDepth < depth; subDepth++) {
        point corner =
            {base[quadrant].x + subDepth * steps[quadrant][0],
                base[quadrant].y + subDepth * steps[quadrant][1]};
        if (isObscured(corner, tree)) return false;
        for (int j = 2 * quadrant; j < 2 * (quadrant + 1); j++) 
            for (int k = 0; k < subDepth; k++) {
                point vertex = {corner.x + subSteps[j][0] * (k + 1),
                        corner.y + subSteps[j][1] * (k + 1)};
                if (isObscured(vertex, tree)) return false;
            }
    }
    return true;
}

int visibleTrees() {
    int count = 0;
    for (int depth = 0; depth <= 10; depth++)
        for (int i = 0; i < 4; i++) {
            point corner = {base[i].x + depth * steps[i][0], base[i].y + depth * steps[i][1]};
            if (isVisible(corner, depth, i)) count++;
            for (int j = 2 * i; j < 2 * (i + 1); j++)
                for (int k = 0; k < depth; k++) {
                    point tree = {corner.x + subSteps[j][0] * (k + 1), corner.y + subSteps[j][1] * (k + 1)};
                    if (isVisible(tree, depth, i)) count++;
                }
        }
    return count;
}

int main() {
    while (cin >> diameter >> x >> y) {
        diameter = (int)(diameter * 100);
        x = (int)(x * 100), y = (int)(y * 100);
        if (diameter == 0 && x == 0 && y == 0) break;
        cout << visibleTrees() << endl;
    }
    return 0;
}
```

## 总结

本题的关键在于将无限网格问题转化为有限范围内的几何遮挡判断。通过合理的枚举顺序和角度计算，可以在有限时间内得到正确结果。代码中使用了整数运算以提高精度和效率，同时注意处理了角度比较的边界情况，避免了因浮点误差导致的错误。
