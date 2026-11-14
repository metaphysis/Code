[UVa 386 Perfect Cubes](https://blog.csdn.net/metaphysis/article/details/161673646)

## 题目描述

费马大定理指出：对于 $n > 2$，不存在大于 $1$ 的整数 $a, b, c$ 满足 $a^n = b^n + c^n$。然而，对于立方的情况，我们可以找到满足 $a^3 = b^3 + c^3 + d^3$ 的整数解（例如 $12^3 = 6^3 + 8^3 + 10^3$）。

本题要求：找出所有满足 $a^3 = b^3 + c^3 + d^3$ 且 $a \leq 200$ 的整数解，其中 $b, c, d \geq 2$。

### 输出格式

按 $a$ 的非递减顺序输出，每行一个解，格式为 `Cube = a, Triple = (b,c,d)`。对于相同的 $a$，按 $b$ 的非递减顺序输出。$b$、$c$、$d$ 也应满足 $b \leq c \leq d$。

### 样例输出（部分）

```
Cube = 6, Triple = (3,4,5)
Cube = 12, Triple = (6,8,10)
Cube = 18, Triple = (2,12,16)
Cube = 18, Triple = (9,12,15)
Cube = 19, Triple = (3,10,18)
Cube = 20, Triple = (7,14,17)
Cube = 24, Triple = (12,16,20)
...
```

---

## 题目分析

### 问题的本质

这是一个**整数方程求解**问题。需要找出所有满足 $a^3 = b^3 + c^3 + d^3$ 的四元组 $(a, b, c, d)$，其中 $2 \leq b \leq c \leq d < a \leq 200$。

### 算法思路

直接枚举 $b, c, d$ 的三重循环，计算 $b^3 + c^3 + d^3$，然后检查该值是否为某个整数的立方，且该整数在 $2$ 到 $200$ 范围内，且大于 $d$。

### 枚举范围

- $b$ 从 $2$ 到 $200$
- $c$ 从 $b$ 到 $200$
- $d$ 从 $c$ 到 $200$

但注意：$a$ 必须大于 $d$，因此 $d$ 最大只需到 $199$。

### 立方根计算

使用 `cbrt` 函数计算立方根，由于浮点精度问题，需检查附近整数。

---

## 参考代码

```cpp
// Perfect Cubes
// UVa ID: 386
// Verdict: Accepted
// Submission Date: 2016-06-26
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct cube
{
    int a, b, c, d;
    bool operator<(cube x) const
    {
        if (a != x.a) return a < x.a;
        if (b != x.b) return b < x.b;
        if (c != x.c) return c < x.c;
        return d < x.d;
    }
};

int main(int argc, char *argv[])
{
    vector<cube> cubes;

    // 枚举 b, c, d
    for (int b = 2; b <= 200; b++)
        for (int c = b; c <= 200; c++)
            for (int d = c; d <= 200; d++)
            {
                int sum = b * b * b + c * c * c + d * d * d;
                // 计算立方根（考虑浮点误差）
                int a = (int)(cbrt(sum) + 0.5);
                // 检查是否满足方程且 a 大于 d 且 a 在范围内
                if (a * a * a == sum && a <= 200 && a > d)
                    cubes.push_back({a, b, c, d});
            }
    
    // 按 a, b, c, d 排序
    sort(cubes.begin(), cubes.end());
    
    // 输出结果
    for (auto group : cubes)
    {
        cout << "Cube = " << group.a << ", Triple = (";
        cout << group.b << "," << group.c << "," << group.d << ")" << endl;
    }
    
    return 0;
}
```
