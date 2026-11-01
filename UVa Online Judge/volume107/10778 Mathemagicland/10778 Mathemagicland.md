
> **摘要**：本文围绕一道「由初等对称多项式反求有理根」的算法题展开。文章先给出题目描述、输入输出格式与样例，随后借助韦达定理把初等对称多项式还原为以 $x_i$ 为根的多项式 $P(x)$，再通过变量替换 $y=kx$ 构造出首一整系数多项式 $Q(y)$，从而利用有理根定理把问题转化为求整数根并保留重数。解题部分给出零根处理、因子枚举构造候选值、霍纳法求值与综合除法提取重根的完整流程，并分析时间复杂度 $O(Cd)$ 与空间复杂度 $O(n)$。

# 题目描述

给定 $n$ 个未知数 $x_1,x_2,\ldots,x_n$ 的初等对称多项式 $\sigma_1,\sigma_2,\ldots,\sigma_n$，输入给出缩放后的值 $k\sigma_1,k\sigma_2,\ldots,k\sigma_n$。需要找出所有 $n$ 元组解中属于有理数集合的分量，并按照 $kx_i$ 的非降序输出。

两个解的输出结果完全相同时，它们被视为同一个解。所有不同输出结果按照字典序输出。题目中的数据保证输入和输出均在标准 $32$ 位有符号整数范围内。

# 输入格式

每组测试数据的第一行包含两个整数 $n$ 和 $k$，其中 $n > 0$，$|k| > 0$，$n < 101$，$|k| < 1001$。

第二行包含 $n$ 个整数：

$$
k\sigma_1,k\sigma_2,\ldots,k\sigma_n
$$

输入以单独一行的 $0$ 结束。

# 输出格式

对于每组测试数据，输出所有有理数分量对应的：

$$
kx_{a_1},kx_{a_2},\ldots,kx_{a_m}
$$

其中每个 $x_{a_i}$ 都是有理数，并且满足：

$$
kx_{a_1} \le kx_{a_2} \le \cdots \le kx_{a_m}
$$

每组结果占一行。不存在满足条件的解时输出 $\texttt{No solution.}$。相邻测试数据之间输出一个空行。

# 样例输入

```text
2 1
2 1
0
```

# 样例输出

```text
1 1
```

# 题目分析

初等对称多项式与多项式根之间满足韦达定理。已知 $x_1,x_2,\ldots,x_n$ 的初等对称多项式 $\sigma_1,\sigma_2,\ldots,\sigma_n$ 后，$x_1,x_2,\ldots,x_n$ 正好是以下多项式的全部根：

$$
P(x)=kx^n-k\sigma_1x^{n-1}+k\sigma_2x^{n-2}-\cdots+(-1)^nk\sigma_n
$$

输入直接给出了每一项 $k\sigma_i$。令：

$$
a_i=k\sigma_i
$$

则原多项式写为：

$$
P(x)=kx^n-a_1x^{n-1}+a_2x^{n-2}-\cdots+(-1)^na_n
$$

题目不直接要求输出 $x_i$，而是要求输出 $kx_i$。令：

$$
y_i=kx_i
$$

将 $x=\frac{y}{k}$ 代入 $P(x)$，并将等式两边同时乘以 $k^{n-1}$，得到以 $y_i$ 为根的多项式：

$$
Q(y)=y^n-a_1y^{n-1}+a_2ky^{n-2}-a_3k^2y^{n-3}+\cdots+(-1)^na_nk^{n-1}
$$

多项式 $Q(y)$ 是首一整系数多项式。根据有理根定理，首一整系数多项式的有理根必然是整数。因此，题目转化为寻找多项式 $Q(y)$ 的全部整数根，并保留每个根的重数。

当 $a_n=0$ 时，原多项式的常数项为 $0$，说明 $x=0$ 是一个根，对应 $y=0$。连续删除末尾的 $0$ 系数后，删除次数即为根 $0$ 的重数。

对于非零根，原多项式 $P(x)$ 的首项系数为 $k$，常数项为 $(-1)^na_n$。根据有理根定理，任意非零有理根可写成：

$$
x=\frac{p}{q}
$$

其中 $p$ 是 $|a_n| 的因数，$q$ 是 $|k|$ 的因数。由于：

$$
y=kx=\frac{pk}{q}
$$

枚举 $|a_n|$ 的所有正因数和 $|k|$ 的所有正因数，即可构造所有可能的 $y$ 候选值。对每个候选值及其相反数代入 $Q(y)$ 检验，值为 $0$ 时说明该候选值是整数根。

找到一个根后，需要不断使用综合除法将该根从多项式中除去，直到它不再是当前多项式的根。这个过程保证了重根会被重复记录，最终结果完全符合输出要求。

# 解题思路

首先读入 $n$、$k$ 和数组 $a$，其中 $a_i=k\sigma_i$。从数组末尾开始统计连续的 $0$，得到根 $0$ 的重数，并将这些零根先记录到答案中。

然后构造首一整系数多项式 $Q(y)$ 的系数。第 $i$ 项系数的绝对值为：

$$
|a_i| \cdot |k|^{i-1}
$$

其符号由 $(-1)^i$ 决定。多项式次数最大为 $100$，幂次和乘法产生的中间结果可能超过 $64$ 位整数范围，因此使用 $\texttt{boost::multiprecision::cpp\_int}$ 保存多项式系数和霍纳法求值结果。

设处理后的常数项绝对值为 $|a_d|$，其中 $d$ 表示去除零根后的多项式次数。枚举 $|a_d|$ 的所有正因数作为分子候选值，枚举 $|k|$ 的所有正因数作为分母候选值，构造：

$$
y=\frac{pk}{q}
$$

同时加入 $y$ 和 $-y$。使用集合去重后，依次对每个候选整数代入多项式。代入结果为 $0$ 时，持续进行综合除法，并将该根加入答案数组，直到该根的全部重数都被提取完毕。

最后将零根和非零根统一排序并输出。多项式的全部有理根均已被枚举，因此不存在遗漏。处理后的多项式没有任何有理根时，答案为空，输出 $\texttt{No solution.}$。

设 $d$ 为去除零根后的多项式次数，$C$ 为候选根数量。每次霍纳法求值和综合除法均需要 $O(d)$ 时间，整体时间复杂度为：

$$
O(Cd)
$$

多项式系数、候选根和答案数组均与 $n$ 成正比，空间复杂度为：

$$
O(n)
$$

# 代码实现


```cpp
#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using BigInt = boost::multiprecision::cpp_int;

vector<long long> getDivisors(long long value) {
    vector<long long> divisors;
    for (long long i = 1; i * i <= value; ++i) {
        if (value % i == 0) {
            divisors.push_back(i);
            if (i * i != value)
                divisors.push_back(value / i);
        }
    }
    return divisors;
}

BigInt evaluate(const vector<BigInt>& coef, long long value) {
    BigInt result = 0;
    for (const BigInt& item : coef)
        result = result * value + item;
    return result;
}

vector<BigInt> divideRoot(const vector<BigInt>& coef, long long root) {
    int degree = static_cast<int>(coef.size()) - 1;
    vector<BigInt> quotient(degree);
    quotient[0] = coef[0];
    for (int i = 1; i < degree; ++i)
        quotient[i] = coef[i] + quotient[i - 1] * root;
    return quotient;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    bool firstCase = true;
    while (cin >> n && n != 0) {
        cin >> k;
        vector<long long> value(n + 1);
        for (int i = 1; i <= n; ++i)
            cin >> value[i];
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        int degree = n;
        while (degree > 0 && value[degree] == 0)
            --degree;
        int zeroCount = n - degree;
        if (degree == 0) {
            for (int i = 0; i < zeroCount; ++i) {
                if (i > 0)
                    cout << ' ';
                cout << 0;
            }
            cout << '\n';
            continue;
        }
        vector<BigInt> coef(degree + 1);
        coef[0] = 1;
        BigInt power = 1;
        for (int i = 1; i <= degree; ++i) {
            BigInt item = value[i] * power;
            if (i % 2 == 1)
                coef[i] = -item;
            else
                coef[i] = item;
            power *= k;
        }
        long long constantValue = llabs(value[degree]);
        long long leadingValue = llabs(k);
        vector<long long> numeratorDivisors = getDivisors(constantValue);
        vector<long long> denominatorDivisors = getDivisors(leadingValue);
        set<long long> candidates;
        for (long long numerator : numeratorDivisors) {
            for (long long denominator : denominatorDivisors) {
                long long positiveRoot = numerator * k / denominator;
                long long negativeRoot = -positiveRoot;
                candidates.insert(positiveRoot);
                candidates.insert(negativeRoot);
            }
        }
        vector<long long> rationalRoots;
        for (long long root : candidates) {
            if (evaluate(coef, root) != 0)
                continue;
            vector<BigInt> current = coef;
            while (current.size() > 1 && evaluate(current, root) == 0) {
                rationalRoots.push_back(root);
                current = divideRoot(current, root);
            }
        }
        sort(rationalRoots.begin(), rationalRoots.end());
        vector<long long> answer;
        for (int i = 0; i < zeroCount; ++i)
            answer.push_back(0);
        for (long long root : rationalRoots)
            answer.push_back(root);
        sort(answer.begin(), answer.end());
        if (answer.empty()) {
            cout << "No solution.\n";
        } else {
            for (int i = 0; i < static_cast<int>(answer.size()); ++i) {
                if (i > 0)
                    cout << ' ';
                cout << answer[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
```

# 总结

本题的核心是利用韦达定理将初等对称多项式转换为根多项式，再通过变量替换将输出目标 $kx_i$ 转化为首一整系数多项式的根。首一整系数多项式的有理根必为整数，因此只需枚举有限个因子构造候选值。综合除法用于处理重复根，$\texttt{cpp\_int}$ 用于避免高次多项式计算中的整数溢出。
