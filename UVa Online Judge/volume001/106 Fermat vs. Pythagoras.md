
> **摘要**：本文解析 $\texttt{UVa 106「Fermat vs. Pythagoras」}$ 一题，要求在 $N \leq 10^6$ 范围内统计本原勾股三元组的个数，以及不属于任何勾股三元组的正整数个数。文章从勾股三元组的生成公式出发，利用 $x=m^2-n^2,\ y=2mn,\ z=m^2+n^2$ 直接枚举互质且一奇一偶的 $(m,n)$ 对，再通过倍数标记法覆盖所有非本原三元组，最终以 $O(N \log N)$ 的复杂度高效求解。

## 题目描述

本题源于费马大定理的一个特例：当 $n=2$ 时，寻找所有满足 $x^{2}+y^{2}=z^{2}$ 的正整数三元组 $(x,y,z)$，且 $x<y<z \leq N$。题目要求计算两个值：

1. **相对质数三元组数量**：即满足 $x<y<z \leq N$，且 $\gcd(x,y,z)=1$ 的三元组个数。
2. **不在任何三元组中出现的正整数个数**：即所有 $\leq N$ 的正整数中，不属于任何满足 $x^{2}+y^{2}=z^{2}$ 的三元组 $(x,y,z)$ 的数的个数。

输入包含多行，每行一个正整数 $N \leq 10^6$，输出对应两个整数，以空格分隔。

---

## 题目分析与解题思路

### 1. 基本数学背景

已知 $x^{2}+y^{2}=z^{2}$ 的正整数解称为**勾股三元组**。所有本原勾股三元组（即 $\gcd(x,y,z)=1$）可以由以下公式生成：

$$
x = m^{2} - n^{2},\quad y = 2mn,\quad z = m^{2} + n^{2}
$$

其中：
- $m > n > 0$，
- $\gcd(m,n)=1$，
- $m$ 与 $n$ 为一奇一偶（否则 $x,y,z$ 会有公因子 $2$）。

### 2. 算法设计

我们不需要枚举所有可能的 $x,y,z$（那样会超时），而是直接枚举生成本原勾股三元组的 $(m,n)$ 对。

**步骤**：

1. **枚举 $(m,n)$ 对**：
   - 令 $m$ 从 $1$ 到 $\sqrt{N}$，
   - 对于每个 $m$，令 $n$ 从 $1$ 到 $m-1$，且满足：
     - $\gcd(m,n)=1$，
     - $m$ 与 $n$ 一奇一偶。
   - 计算 $x = m^{2} - n^{2}$，$y = 2mn$，$z = m^{2} + n^{2}$。
   - 如果 $z \leq N$，则 $(x,y,z)$ 是一个本原三元组。

2. **标记三元组中的数**：
   - 对于每个本原三元组，其所有倍数（即 $kx, ky, kz$，其中 $k \geq 1$ 且 $kz \leq N$）都是勾股三元组。
   - 使用一个布尔数组 `used` 标记所有出现在三元组中的数。

3. **计数**：
   - 本原三元组的数量即为所求的第一个答案。
   - 遍历 $1$ 到 $N$，统计未被标记的数的数量，即为第二个答案。

### 3. 时间复杂度

枚举的 $(m,n)$ 对数量为 $O(N)$，因为 $m$ 最大约为 $\sqrt{N}$，每个 $m$ 对应的 $n$ 数量也约为 $m$，总和约为 $O(N)$。标记倍数的时间复杂度为 $O(N \log N)$（调和级数），总体可在规定时间内完成。

---

## 代码实现

```cpp
// Fermat vs. Pythagoras
// UVa ID: 106
// Verdict: Accepted
// Submission Date: 2011-11-21
// UVa Run Time: 0.236s
//
// 版权所有（C）2011,邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000001

bool used[MAXN];

int gcd(int a, int b) {
    return a < b ? gcd(b, a) : (b ? gcd(b, a % b) : a);
}

int main() {
    int n, limit, x, y, z;

    while (cin >> n) {
        for (int i = 1; i <= n; i++) used[i] = false;

        limit = floor(sqrt(n));
        
        int total = 0;
        for (int i = 1; i < limit; i++)
            for (int j = i + 1; j <= limit; j += 2)
                if ((z = (i * i + j * j)) <= n && gcd(i, j) == 1) {
                    x = j * j - i * i;
                    y = 2 * i * j;

                    total++;
                    for (int start = 1; z * start <= n; start++)
                        used[x * start] = used[y * start] = used[z * start] = true;
                }

        int unused = 0;
        for (int i = 1; i <= n; i++)
            if (!used[i])
                unused++;

        cout << total << " " << unused << endl;
    }

    return 0;
}
```

---

## 总结

本题通过数学公式生成所有本原勾股三元组，避免了直接枚举 $x,y,z$ 的高时间复杂度。利用倍数标记法，可以高效地统计出所有出现在三元组中的数，进而得到不在任何三元组中的数的个数。这种方法在 $N \leq 10^6$ 的范围内可以高效运行。

> **关键点**：理解本原勾股三元组的生成公式，并利用倍数标记法避免重复计算。
