
> **摘要**：本题给定首项为 $a$、公比为 $\frac{p}{q}$ 的无穷等比数列，要求统计满足级数和 $S=\frac{aq}{q-p}\le NEXT\_TO\_NEVER$ 的分数 $\frac{p}{q}$ 数量，分别输出 $p,q$ 互质时的数量 $s$ 与不要求互质时的数对数量 $t$。核心思路是把收敛条件与和的上界转化为线性不等式 $Np\le (N-a)q$，从而对固定 $q$ 直接确定合法 $p$ 的个数；再用 $\texttt{floorSum}$ 在 $O(\log N)$ 内完成整除求和，并用线性筛预处理莫比乌斯函数、通过莫比乌斯反演统计互质数对，单组数据总复杂度为 $O(MAXV\log N)$。

# 题目描述

给定一个首项为 $a$、公比为 $\frac{p}{q}$ 的无穷等比数列：

$$
a+a\left(\frac{p}{q}\right)+a\left(\frac{p}{q}\right)^2+a\left(\frac{p}{q}\right)^3+\cdots
$$

其中 $p$ 的取值范围为 $0 \le p \le MAXV$，$q$ 的取值范围为 $1 \le q \le MAXV$。

当公比小于 $1$ 时，等比数列收敛，其和为：

$$
S=\frac{a}{1-\frac{p}{q}}=\frac{aq}{q-p}
$$

题目要求统计满足 $S \le NEXT\_TO\_NEVER$ 的分数 $\frac{p}{q}$ 的数量。

需要分别统计以下两种情况：

- $p$ 和 $q$ 互质时，不同分数的数量，记为 $s$。
- $p$ 和 $q$ 不要求互质时，数对 $(p,q)$ 的数量，记为 $t$。

# 输入格式

每组数据占一行，包含三个整数：

$$
NEXT\_TO\_NEVER,\ a,\ MAXV
$$

数据范围如下：

$$
1000 \le NEXT\_TO\_NEVER \le 10000
$$

$$
1 \le a \le 5
$$

$$
20000 \le MAXV \le 100000
$$

输入以一行三个零结束。

# 输出格式

对于每组数据输出一行：

```text
Case k: s t
```

其中 $k$ 表示数据组编号，$s$ 表示 $p$ 和 $q$ 互质时的数量，$t$ 表示不要求互质时的数量。

# 样例输入

```text
1000 1 20000
0 0 0
```

# 样例输出

```text
Case 1: 121468930 199820000
```

# 题目分析

设：

$$
N=NEXT\_TO\_NEVER
$$

等比级数的公比为：

$$
r=\frac{p}{q}
$$

由于级数必须收敛，所以必须满足：

$$
\frac{p}{q}<1
$$

因为 $p \ge 0$ 且 $q \ge 1$，该条件等价于：

$$
p<q
$$

等比级数的和为：

$$
S=\frac{a}{1-\frac{p}{q}}=\frac{aq}{q-p}
$$

题目要求：

$$
\frac{aq}{q-p}\le N
$$

由于 $q-p>0$，两边同乘 $q-p$ 后不改变不等号方向：

$$
aq\le N(q-p)
$$

整理得到：

$$
Np\le (N-a)q
$$

令：

$$
B=N-a
$$

于是所有合法数对 $(p,q)$ 都满足：

$$
0\le p\le \left\lfloor\frac{Bq}{N}\right\rfloor
$$

同时 $1\le q\le MAXV$。

对于固定的 $q$，合法的 $p$ 有：

$$
\left\lfloor\frac{Bq}{N}\right\rfloor+1
$$

个，其中额外的 $1$ 对应 $p=0$。

因此，不要求互质时的答案为：

$$
t=\sum_{q=1}^{MAXV}
\left(
\left\lfloor\frac{Bq}{N}\right\rfloor+1
\right)
$$

直接枚举每个 $q$ 可以求出答案，但每组数据的 $MAXV$ 最大为 $100000$，且测试数据较多，因此需要使用更高效的整除求和方法。

对于互质数量，要求：

$$
\gcd(p,q)=1
$$

设 $F(L)$ 表示满足 $1\le q\le L$ 的所有合法数对数量，则：

$$
F(L)=\sum_{q=1}^{L}
\left(
\left\lfloor\frac{Bq}{N}\right\rfloor+1
\right)
$$

利用莫比乌斯函数 $\mu(d)$ 的性质：

$$
[\gcd(p,q)=1]=
\sum_{d\mid \gcd(p,q)}\mu(d)
$$

可以通过莫比乌斯反演得到互质数对数量：

$$
s=
\sum_{d=1}^{MAXV}
\mu(d)
F\left(\left\lfloor\frac{MAXV}{d}\right\rfloor\right)
$$

因此，问题转化为以下两个部分：

- 快速计算 $F(L)$。
- 预处理莫比乌斯函数 $\mu(d)$。

# 解题思路

## 快速计算整除求和

需要计算：

$$
\sum_{q=1}^{L}\left\lfloor\frac{Bq}{N}\right\rfloor
$$

代码使用 $\texttt{floorSum}$ 函数计算：

$$
\sum_{i=0}^{n-1}
\left\lfloor\frac{ai+b}{m}\right\rfloor
$$

在本题中取：

$$
n=L,\quad m=N,\quad a=B,\quad b=B
$$

于是：

$$
\sum_{i=0}^{L-1}
\left\lfloor\frac{Bi+B}{N}\right\rfloor=
\sum_{q=1}^{L}
\left\lfloor\frac{Bq}{N}\right\rfloor
$$

所以：

$$
F(L)=\texttt{floorSum}(L,N,B,B)+L
$$

$\texttt{floorSum}$ 通过不断处理商和余数，将问题规模缩小，时间复杂度为：

$$
O(\log N)
$$

## 预处理莫比乌斯函数

使用线性筛预处理 $\mu(d)$。

莫比乌斯函数的取值规则为：

- $\mu(1)=1$。
- 当 $d$ 是平方因子时，$\mu(d)=0$。
- 当 $d$ 含有不同质因子个数为 $k$ 时，$\mu(d)=(-1)^k$。

线性筛保证每个整数只被其最小质因子处理一次，因此预处理复杂度为：

$$
O(MAXV)
$$

## 计算不要求互质的数量

直接令 $L=MAXV$，得到：

$$
t=F(MAXV)
$$

代码中的计算形式为：

```text
floorSum(MAXV, N, B, B) + MAXV
```

## 计算互质数量

枚举公因子 $d$，根据莫比乌斯反演累加：

$$
s=
\sum_{d=1}^{MAXV}
\mu(d)
F\left(\left\lfloor\frac{MAXV}{d}\right\rfloor\right)
$$

当 $\mu(d)=0$ 时，该项不会影响答案，但统一计算可以保持实现简洁。

每次调用 $F(L)$ 都需要一次 $\texttt{floorSum}$，其复杂度为 $O(\log N)$。因此单组数据的总时间复杂度为：

$$
O(MAXV\log N)
$$

莫比乌斯数组、质数数组和筛选标记数组占用：

$$
O(MAXV)
$$

空间复杂度为：

$$
O(MAXV)
$$

# 代码实现

```cpp
// Next to Never
// UVa ID: 12341
// Verdict: Accepted
// Submission Date: 2026-08-28
// UVa Run Time: 0.980s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long floorSum(long long n, long long m, long long a, long long b) {
    long long ans = 0;
    while (true) {
        if (a >= m) {
            ans += (n - 1) * n * (a / m) / 2;
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }
        long long yMax = a * n + b;
        if (yMax < m)
            break;
        n = yMax / m;
        b = yMax % m;
        swap(m, a);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int maxLimit = 100000;
    vector<int> mu(maxLimit + 1), primes;
    vector<bool> isComposite(maxLimit + 1, false);
    mu[1] = 1;
    for (int i = 2; i <= maxLimit; ++i) {
        if (!isComposite[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int j = 0; j < static_cast<int>(primes.size()) && i * primes[j] <= maxLimit; ++j) {
            int value = i * primes[j];
            isComposite[value] = true;
            if (i % primes[j] == 0) {
                mu[value] = 0;
                break;
            }
            mu[value] = -mu[i];
        }
    }
    int n, a, maxV, caseId = 1;
    while (cin >> n >> a >> maxV) {
        if (n == 0 && a == 0 && maxV == 0)
            break;
        int b = n - a;
        long long total = floorSum(maxV, n, b, b) + maxV;
        long long coprime = 0;
        for (int d = 1; d <= maxV; ++d) {
            int limit = maxV / d;
            long long count = floorSum(limit, n, b, b) + limit;
            coprime += 1LL * mu[d] * count;
        }
        cout << "Case " << caseId++ << ": " << coprime << " " << total << '\n';
    }
    return 0;
}
```

# 总结

本题的核心是将等比级数和的限制转化为数对 $(p,q)$ 的线性不等式：

$$
Np\le (N-a)q
$$

对于不要求互质的情况，固定 $q$ 后可以直接确定 $p$ 的数量，并使用 $\texttt{floorSum}$ 快速计算整除求和。

对于要求互质的情况，利用莫比乌斯反演消除公共因子：

$$
s=
\sum_{d=1}^{MAXV}
\mu(d)
F\left(\left\lfloor\frac{MAXV}{d}\right\rfloor\right)
$$

最终通过线性筛预处理莫比乌斯函数，并结合对数复杂度的整除求和，完成所有数据的高效计算。
