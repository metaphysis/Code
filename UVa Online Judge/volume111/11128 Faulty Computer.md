
> **摘要**：本题要求在 $|x_i| < 10$ 的整数范围内，为 $6$ 个给定整数 $a_1,\dots,a_6$ 寻找一组非零系数 $x_0,\dots,x_6$，使带平方根的无理线性组合 $x_0 + \sum_{i=1}^6 x_i\sqrt{a_i}$ 的绝对值小于 $10^{-4}$。由于直接枚举 $19^7$ 种组合规模过大，本文采用**折半枚举（$\texttt{Meet-in-the-Middle}$）**：先枚举并排序前半部分 $(x_1,x_2,x_3)$ 的 $19^3$ 种取值，再枚举后半部分 $(x_4,x_5,x_6)$ 与 $x_0$，通过二分查找快速匹配，将复杂度降至 $O(19^3\log 19^3)$。

## 题目描述

给定 $6$ 个整数 $a_1, a_2, \dots, a_6$，其中 $0 \le a_i < 100$。寻找整数 $x_0, x_1, \dots, x_6$，满足 $|x_i| < 10$（$i = 0 \dots 6$）且 $\sum_{i=0}^6 |x_i| \ne 0$，使得在故障计算机的判定下，表达式

$$
x_0 + x_1\sqrt{a_1} + x_2\sqrt{a_2} + \dots + x_6\sqrt{a_6}
$$

的绝对值小于 $10^{-4}$。故障计算机将任何绝对值小于 $10^{-4}$ 的数值视为零。若有解，输出任意一组；否则输出 `No Solution.`。

## 输入格式

第一行包含一个整数 $N$（$N \le 60$），表示测试用例数。接下来 $N$ 行，每行六个整数 $a_1, a_2, \dots, a_6$。

## 输出格式

对于每个测试用例，输出一行。格式为 `Case X: x0 x1 x2 x3 x4 x5 x6`，其中 $X$ 为用例编号（从 $1$ 开始）。若无解，输出 `Case X: No Solution.`。

## 样例

**输入**

```
3
1 1 1 1 1 1
2 3 4 5 6 6
5 4 33 0 0 0
```

**输出**

```
Case 1: -9 -9 -9 0 9 9 9
Case 2: -9 -9 -5 9 9 -6 2
Case 3: -8 -4 -5 3 4 -9 -9
```

## 题目分析

本题的核心是在有限的整数范围内寻找一组系数 $x_0, \dots, x_6$，使得带平方根的无理线性组合逼近零。由于 $x_i$ 的取值范围仅为 $-9$ 到 $9$，每个变量有 $19$ 种可能，直接枚举全部 $7$ 个变量会产生 $19^7 \approx 8.9\times 10^8$ 种组合，虽然单组数据可能勉强通过，但 $N$ 最大为 $60$，总枚举量过大，无法在时限内完成。

观察方程结构：

$$
\left( x_0 + \sum_{i=1}^3 x_i\sqrt{a_i} \right) + \left( \sum_{i=4}^6 x_i\sqrt{a_i} \right) = 0.
$$

可以将变量分成两组：前半部分 $(x_1,x_2,x_3)$ 和后半部分 $(x_4,x_5,x_6)$，分别计算它们的无理组合值。对于给定的后半部分和 $x_0$，我们需要在前半部分的所有可能值中查找是否存在一个值，使得两者之和接近 $-x_0$。这是一个经典的**折半枚举（Meet-in-the-Middle）**问题。

由于前半部分只有 $19^3 = 6859$ 种可能，枚举并排序后，对每一组后半部分（同样 $6859$ 种）和 $x_0$（$19$ 种）进行二分查找，总查找次数约为 $6859 \times 19 \times \log_2 6859 \approx 1.6\times 10^6$，非常高效，完全可以满足 $N\le 60$ 的要求。

需要注意的是，浮点数计算必须使用高精度类型（如 `long double`）来避免误差累积，判断阈值设为 $10^{-4}$ 即可。

## 解题思路

### 1. 枚举前半部分

枚举所有可能的 $(x_1,x_2,x_3)$，共 $19^3$ 种组合。对于每种组合，计算

$$
A = x_1\sqrt{a_1} + x_2\sqrt{a_2} + x_3\sqrt{a_3}.
$$

将 $(A, x_1, x_2, x_3)$ 存入数组，并按 $A$ 的值从小到大排序，以便后续二分查找。

### 2. 枚举后半部分并二分查找

枚举所有可能的 $(x_4,x_5,x_6)$（同样 $19^3$ 种），计算

$$
B = x_4\sqrt{a_4} + x_5\sqrt{a_5} + x_6\sqrt{a_6}.
$$

对于每个 $x_0 \in [-9, 9]$，我们需要找到一个 $A$ 使得

$$
A + B + x_0 \approx 0 \quad\Longleftrightarrow\quad A \approx -x_0 - B.
$$

在已排序的前半部分数组中，使用二分查找（`lower_bound`）定位到最接近目标值的位置，然后检查该位置及其前一个位置（因为最接近的可能在两侧）是否满足

$$
|A + B + x_0| < 10^{-4}.
$$

若满足，则得到一组可行解，同时需要排除所有 $x_i$ 全为零的情况（因为题目要求非零解）。

### 3. 正确性与复杂度

- **正确性**：折半枚举覆盖了所有可能的 $(x_1,\dots,x_6)$ 组合，且二分查找能保证找到最接近目标的前半部分值，因此不会遗漏满足精度条件的解。
- **时间复杂度**：排序 $O(19^3 \log 19^3)$，查找 $O(19^3 \times 19 \times \log 19^3)$，单组数据约 $10^6$ 量级，对于 $N=60$ 总操作量在可接受范围内。
- **空间复杂度**：$O(19^3)$ 用于存储前半部分枚举结果。

## 代码实现

```cpp
// Faulty Computer
// UVa ID: 11128
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Entry {
    long double val;
    int x1, x2, x3;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    for (int caseNo = 1; caseNo <= N; ++caseNo) {
        int a[7];
        for (int i = 1; i <= 6; ++i) cin >> a[i];
        long double sq[7];
        for (int i = 1; i <= 6; ++i) sq[i] = sqrtl((long double)a[i]);
        vector<Entry> left;
        left.reserve(19 * 19 * 19);
        for (int x1 = -9; x1 <= 9; ++x1)
            for (int x2 = -9; x2 <= 9; ++x2)
                for (int x3 = -9; x3 <= 9; ++x3) {
                    long double v = x1 * sq[1] + x2 * sq[2] + x3 * sq[3];
                    left.push_back({v, x1, x2, x3});
                }
        sort(left.begin(), left.end(), [](const Entry& p, const Entry& q) {
            return p.val < q.val;
        });
        bool found = false;
        int ans[7];
        for (int x4 = -9; x4 <= 9 && !found; ++x4)
            for (int x5 = -9; x5 <= 9 && !found; ++x5)
                for (int x6 = -9; x6 <= 9 && !found; ++x6) {
                    long double B = x4 * sq[4] + x5 * sq[5] + x6 * sq[6];
                    for (int x0 = -9; x0 <= 9 && !found; ++x0) {
                        long double target = -x0 - B;
                        auto it = lower_bound(left.begin(), left.end(), target,
                            [](const Entry& e, const long double& v) {
                                return e.val < v;
                            });
                        auto check = [&](const Entry& e) -> bool {
                            long double expr = e.val + B + x0;
                            if (fabsl(expr) >= 1e-4L) return false;
                            if (e.x1 == 0 && e.x2 == 0 && e.x3 == 0 &&
                                x4 == 0 && x5 == 0 && x6 == 0 && x0 == 0)
                                return false;
                            ans[0] = x0;
                            ans[1] = e.x1;
                            ans[2] = e.x2;
                            ans[3] = e.x3;
                            ans[4] = x4;
                            ans[5] = x5;
                            ans[6] = x6;
                            return true;
                        };
                        if (it != left.end() && check(*it)) found = true;
                        if (!found && it != left.begin()) {
                            --it;
                            if (check(*it)) found = true;
                        }
                    }
                }
        if (found) {
            cout << "Case " << caseNo << ":";
            for (int i = 0; i < 7; ++i) cout << ' ' << ans[i];
            cout << '\n';
        } else {
            cout << "Case " << caseNo << ": No Solution.\n";
        }
    }

    return 0;
}
```

## 总结

本题的核心技巧是**折半枚举（$\texttt{Meet-in-the-Middle}$）**，它将指数级搜索空间一分为二，分别枚举并利用排序和二分查找快速匹配，从而将复杂度从 $O(19^7)$ 降至 $O(19^3 \log 19^3)$。在浮点数处理上，使用 `long double` 保证精度，并设置恰当的阈值。该思路适用于变量范围较小但组合爆炸的方程求解问题，是一种典型的空间换时间策略。同时，注意排除全零解，确保输出满足题目要求。
