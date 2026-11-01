
> **摘要**：本文讨论一道关于有理数硬币相切关系的算法题：面值为 $1/q$ 的硬币半径为 $1/(2q^2)$，圆心位于 $(p/q,\ 1/(2q^2))$，要求按半径从大到小（半径相同则按横坐标从小到大）输出与给定硬币 $M(p/q)$ 相切的前 $n$ 个硬币。文章从两圆外切的几何条件出发，通过展开并化简圆心距离与半径之和的等式，将几何问题转化为丢番图方程 $|aq-bp|=1$；随后利用 $p$ 在模 $q$ 意义下的逆元，构造出两条分母严格递增的解序列，并以归并的方式按分母、分子升序输出前 $n$ 项，同时单独处理 $q=1$ 的边界情形。配合扩展欧几里得算法求逆元，单组数据时间复杂度为 $O(\log q+n)$，空间复杂度为 $O(1)$。

# 题目描述

在有理国中，面值为 $1/q$ $\texttt{R}$ 的硬币半径为 $1/(2q^2)$。硬币 $M(p/q)$ 的圆心坐标为：

$$
\left(\frac{p}{q}, \frac{1}{2q^2}\right)
$$

其中 $p/q$ 为既约分数，且 $0 \le p/q \le 1$。现给定硬币 $M(p/q)$，需要按照半径从大到小的顺序输出前 $n$ 个与其相切的硬币。半径相同时，按照圆心横坐标从小到大的顺序输出。

# 输入格式

输入包含多组测试数据，每组数据包含三个整数 $p$、$q$、$n$。

其中，$0 \le p/q \le 1$，$1 \le q \le 10^6$，$1 \le n \le 10^3$，并且 $p/q$ 为既约分数。

# 输出格式

对于每组测试数据，输出一行包含 $n$ 个硬币名称。

每个硬币名称格式为 $M(a/b)$，相邻硬币名称之间使用一个空格分隔。

# 样例输入

```text
2 5 4
2 3 3
0 1 2
1 1 2
1 2 5
```

# 样例输出

```text
M(1/2) M(1/3) M(3/7) M(3/8)
M(1/1) M(1/2) M(3/4)
M(1/1) M(1/2)
M(0/1) M(1/2)
M(0/1) M(1/1) M(1/3) M(2/3) M(2/5)
```

# 题目分析

设当前硬币为 $M(p/q)$，另一个硬币为 $M(a/b)$。根据题意，硬币 $M(p/q)$ 的圆心为：

$$
\left(\frac{p}{q}, \frac{1}{2q^2}\right)
$$

硬币 $M(a/b)$ 的圆心为：

$$
\left(\frac{a}{b}, \frac{1}{2b^2}\right)
$$

两枚硬币外切时，两个圆心之间的距离等于半径之和。两圆心的横坐标差为：

$$
\frac{a}{b} - \frac{p}{q}
$$

两圆心的纵坐标差为：

$$
\frac{1}{2b^2} - \frac{1}{2q^2}
$$

两枚硬币半径之和为：

$$
\frac{1}{2b^2} + \frac{1}{2q^2}
$$

由圆的外切条件得到：

$$
\left(\frac{a}{b} - \frac{p}{q}\right)^2 + \left(\frac{1}{2b^2} - \frac{1}{2q^2}\right)^2 = \left(\frac{1}{2b^2} + \frac{1}{2q^2}\right)^2
$$

展开并消去相同项后，得到：

$$
\left(\frac{a}{b} - \frac{p}{q}\right)^2 = \frac{1}{b^2q^2}
$$

继续化简：

$$
\left|\frac{aq - bp}{bq}\right| = \frac{1}{bq}
$$

因此，所有与 $M(p/q)$ 相切的硬币都满足：

$$
|aq - bp| = 1
$$

这个结论将几何问题转化为求解两个一次丢番图方程：

$$
aq - bp = 1
$$

以及：

$$
aq - bp = -1
$$

由于右侧为 $1$ 或 $-1$，所以 $a$ 与 $b$ 自动互质，得到的分数 $a/b$ 必然是既约分数。

# 解题思路

当 $q > 1$ 时，方程 $aq - bp = 1$ 可以写成：

$$
bp \equiv -1 \pmod q
$$

方程 $aq - bp = -1$ 可以写成：

$$
bp \equiv 1 \pmod q
$$

由于 $p/q$ 是既约分数，因此：

$$
\gcd(p, q) = 1
$$

所以 $p$ 在模 $q$ 意义下存在逆元。设 $p$ 的模 $q$ 逆元为 $\textit{inv}$，满足：

$$
p \cdot \textit{inv} \equiv 1 \pmod q
$$

对于方程：

$$
aq - bp = 1
$$

可得：

$$
b \equiv -\textit{inv} \pmod q
$$

其最小正分母为：

$$
b_1 = q - \textit{inv}
$$

对应分子为：

$$
a_1 = \frac{b_1p + 1}{q}
$$

之后该方程的每个解都满足：

$$
b_1 \leftarrow b_1 + q
$$

对于方程：

$$
aq - bp = -1
$$

可得：

$$
b \equiv \textit{inv} \pmod q
$$

其最小正分母为：

$$
b_2 = \textit{inv}
$$

对应分子为：

$$
a_2 = \frac{b_2p - 1}{q}
$$

之后该方程的每个解都满足：

$$
b_2 \leftarrow b_2 + q
$$

两条解序列中的分母均严格递增，并且每次增加 $q$。题目要求优先输出半径更大的硬币，而硬币半径为：

$$
\frac{1}{2b^2}
$$

因此分母 $b$ 越小，半径越大。只需像归并两个有序序列一样，每次选择分母更小的硬币输出即可。若两个候选硬币分母相同，则选择分子更小的硬币，从而保证横坐标更小的硬币先输出。

当 $q = 1$ 时，输入硬币只能为 $M(0/1)$ 或 $M(1/1)$。对于 $M(0/1)$，所有相切硬币依次为：

$$
M(1/1), M(1/2), M(1/3), \ldots
$$

对于 $M(1/1)$，所有相切硬币依次为：

$$
M(0/1), M(1/2), M(2/3), \ldots
$$

因此直接按照规律输出前 $n$ 个硬币即可。

扩展欧几里得算法用于求出 $p$ 在模 $q$ 意义下的逆元，单组数据的时间复杂度为：

$$
O(\log q + n)
$$

空间复杂度为：

$$
O(1)
$$

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

long long exGcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1, g = exGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long p, q, n;
    while (cin >> p >> q >> n) {
        bool first = true;
        if (q == 1) {
            for (long long i = 1; i <= n; i++) {
                long long a = (p == 0 ? 1 : i - 1), b = i;
                if (!first) cout << ' ';
                first = false;
                cout << "M(" << a << "/" << b << ")";
            }
        } else {
            long long x, y;
            exGcd(p, q, x, y);
            long long inv = (x % q + q) % q;
            long long b1 = inv, a1 = (b1 * p - 1) / q;
            long long b2 = q - inv, a2 = (b2 * p + 1) / q;
            for (long long i = 0; i < n; i++) {
                if (b1 < b2 || (b1 == b2 && a1 <= a2)) {
                    if (!first) cout << ' ';
                    first = false;
                    cout << "M(" << a1 << "/" << b1 << ")";
                    b1 += q;
                    a1 = (b1 * p - 1) / q;
                } else {
                    if (!first) cout << ' ';
                    first = false;
                    cout << "M(" << a2 << "/" << b2 << ")";
                    b2 += q;
                    a2 = (b2 * p + 1) / q;
                }
            }
        }
        cout << '\n';
    }
    return 0;
}
```

# 总结

本题的关键是通过圆外切条件推导出：

$$
|aq - bp| = 1
$$

该条件说明所有相切硬币对应两个一次丢番图方程的整数解。利用 $p$ 在模 $q$ 意义下的逆元，可以直接构造两条分母递增的解序列。最后通过归并两个有序序列，按照分母升序、分子升序输出前 $n$ 个硬币，即可满足题目要求。
