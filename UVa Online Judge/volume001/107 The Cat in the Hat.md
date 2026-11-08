
> **摘要**：本文围绕 $\texttt{UVa 107「The Cat in the Hat」}$ 展开，先建立「帽中猫」的递归数学模型，将问题转化为求解 $(N+1)^M = H$ 与 $N^M = W$ 中的参数 $N$ 与 $M$；随后给出基于质因数分解与最大公约数的求解思路，并讨论 $W=1$ 等特殊情况。

## 题目分析

本题描述了一个递归的“帽中猫”模型。初始有一只猫，它的身高为 $H$，它帽子中藏着 $N$ 只小猫，每只小猫的身高是它身高的 $\frac{1}{N+1}$。每只小猫（除了最小的小猫）也都以同样的方式在帽子中藏 $N$ 只更小的猫，直到猫的高度为 $1$（这些是最小的猫，它们没有帽子，必须去打扫房间）。

已知**初始猫的高度** $H$ 和**最小猫（工人猫）的数量** $W$，要求计算：
1. **未工作的猫的数量**（即身高大于 $1$ 的猫的总数）。
2. **所有猫身高的总和**（假设它们叠在一起的总高度）。

**输入**：多组数据，每组两个正整数 $H$ 和 $W$，以 `0 0` 结束。  
**输出**：对于每组，输出未工作的猫的数量和总高度。

## 数学模型

设：
- $N$：每只猫帽子中藏的小猫数量（常数）。
- $M$：递归的层数（从初始猫到最小猫的层数，初始猫在第 $0$ 层）。
- $H$：初始猫高度。
- $W$：最小猫（工人猫）数量。

根据题意：
- 第 $k$ 层猫的数量为 $N^k$。
- 第 $k$ 层猫的高度为 $\frac{H}{(N+1)^k}$。
- 当 $k = M$ 时，猫高度为 $1$，数量为 $W$。

因此有以下方程：

$$
\frac{H}{(N+1)^M} = 1 \quad \Rightarrow \quad (N+1)^M = H
$$
$$
N^M = W
$$

我们需要从 $H$ 和 $W$ 中解出 $N$ 和 $M$，然后计算：
- 未工作的猫数：所有身高大于 $1$ 的猫的数量，即 $\sum_{k=0}^{M-1} N^k$。
- 总高度：所有猫身高之和，即 $\sum_{k=0}^{M} N^k \cdot \frac{H}{(N+1)^k}$。

## 解题思路

### 特殊情况
1. **$W = 1$**：此时只有一层猫。如果 $H = 1$，则只有一只工人猫，未工作猫数为 $0$，总高度为 $1$。如果 $H > 1$，则 $N = 1$（每只猫帽子中只有一只猫），$M = \log_2(H+1)-1$（因为 $(1+1)^M = 2^M = H$）。
2. **一般情况**：$W \geq 2$，$N \geq 2$，$M \geq 1$。

### 一般情况的解法
从方程 $(N+1)^M = H$ 和 $N^M = W$ 可得：
$$
\left(\frac{N+1}{N}\right)^M = \frac{H}{W}
$$
即：
$$
\left(1 + \frac{1}{N}\right)^M = \frac{H}{W}
$$
由于 $H$ 和 $W$ 都是整数，我们可以通过对 $H$ 和 $W$ 进行质因数分解来求解 $M$ 和 $N$。

**关键观察**：
- $H$ 和 $W$ 都可以表示为 $N+1$ 和 $N$ 的 $M$ 次幂。
- 对 $H$ 和 $W$ 分别进行质因数分解，各质因数的指数都是 $M$ 的倍数。
- 而 $N$ 和 $N+1$ 互质，因此 $H$ 和 $W$ 各质因数指数的最大公约数就是 $M$。

**步骤**：
1. 对 $H$ 和 $W$ 分别质因数分解。
2. 计算 $H$ 所有质因数指数的最大公约数 $g_H$。
3. 计算 $W$ 所有质因数指数的最大公约数 $g_W$。
4. 则 $M = \gcd(g_H, g_W)$。
5. 根据 $H = (N+1)^M$，可得 $N+1 = \prod p_i^{e_i / M}$，从而求出 $N$。
6. 利用 $N$ 和 $M$ 计算未工作猫数和总高度。

### 算法实现细节
- 为了效率，预先生成 $2^{16}$ 以内的所有素数。
- 质因数分解时，对每个素数试除，记录指数。
- 计算指数最大公约数用欧几里得算法。
- 注意处理 $W=1$ 的特殊情况。

## 时间复杂度
- 素数筛法：$O(\sqrt{MAXINT} \log \log MAXINT)$。
- 每组数据质因数分解：$O(\pi(\sqrt{H}) + \pi(\sqrt{W}))$，其中 $\pi(x)$ 是小于 $x$ 的素数个数。
- 总体可接受。

## 代码实现

```cpp
// The Cat in the Hat
// UVa ID: 107
// Verdict: Accepted
// Submission Date: 2011-11-23
// UVa Run Time: 1.132s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 由于题目并未指明输入数据的范围，所以只有摸着石头过河。本题解是基于输入数据在 32
// 位整数以内的假设。
//
// 当工作的猫只有一只时，则每顶帽子内只有一只猫或者只有初始给定的那只猫。当只有初始
// 给定的那只猫时，对应的输入应该是：1，1。
// 当每顶帽子只有一只猫时，对应的输入应该是：x，1。其中 x 为 2 的幂。这两种特殊情况
// 可以分开来解决。
//
// 对于一般的情况，设帽子的嵌套层数为 M，每只帽子内的猫数量为 N，初始猫高度为 A，工
// 作的猫数量为 B，则有下列方程成立（B >= 2，N >= 2，M >= 1）：
//
// （N + 1）^M = A
//  N^M = B
//
// 那么很明显，A 和 B 均是大于 1 的合数。假如输入数据在 32 位整数范围内，那么 A 和
// B 都可以分解为小于 2^16 的素数的乘积。对于 A 的分解，假设分解式为
//
// A = a^k * b^l * c^m * ... * g^q.
//
// 那么由于 A 是一个数的 M 次幂，则必有 A 的素因子的指数都是 M 的倍数。同样的，B 的
// 素因子分解式中，各素因子的指数同样是 M 的倍数，那么 M 必为所有素因子指数的最大公
// 约数（为什么？只需证明 N + 1 和 N 的素因子分解式中所有指数的最大公约数为 1 即可，
// 用反证法证明，假设 N + 1 和 N 的素因子分解式中，所有指数的最大公约数为一个大于 1
// 的数 w，那么不妨设：N + 1 = a^w，N = b^w，有
// a^w - b^w = 1，a，b，w >= 2，且为整数
// 又由于 N + 1 > N，故有 a > b，不妨设 a = b + x
// 其中 x >= 1，那么有
// （b + x）^w - b^w = 1，由于 w >= 2，x >= 1，则根据二项式定理，上式不可能成立）。
//
// 那么可以将 A 和 B 进行素因子分解，用求所有指数最大公约数的方法求得 M，进而根据素
// 因子分解的结果求得 N。
//
// 如果输入数据超出 32 位整数范围，只要素数分解的算法不是太慢，应该也能使用此种方法
// 解决，不过随着给定数据范围的加大，素数增多，就不能使用预先生成指定范围内素数的办
// 法，应该转而寻求其他不是太低效的办法。
//
// 另外一种解题的方法是根据方程使用二分法搜索 M 和 N 的值，这种方法我没有具体尝试过。

#include <bits/stdc++.h>
using namespace std;

#define MAXINT (1 << 16)
#define MAXN 6600

int prime[MAXN], nPrime = 0, factor[MAXN];

// 素数判定。
bool isPrime(int x) {
    if (x <= 1) return false;
    if (x == 2) return true;
    if (x & 1) {
        int top = sqrt(x);
        for (int i = 3; i <= top; i += 2)
            if (x % i) continue;
            else return false;
        return true;
    } else return false;
}

// 生成指定范围内的所有素数。
void getPrime(void) {
    for (int i = 2; i <= MAXINT; i++)
        if (isPrime(i))
            prime[nPrime++] = i;
}

// 求最大公约数。
int gcd(int x, int y) { return x < y ? gcd(y, x) : (y ? gcd(y, x % y) : x); }

// 素因子分解并求指数的最大公约数。
int factoring(int x) {
    int y = 0;
    memset(factor, 0, sizeof(factor));
    for (int i = 0; i < nPrime && x > 1; i++)
        while (x % prime[i] == 0) {
            factor[i]++;
            x /= prime[i];
        }
    for (int i = 0; i < MAXN; i++)
        if (factor[i]) {
            if (y) y = gcd(y, factor[i]);
            else y = factor[i];
        }
    return y;
}

// 特例处理。
void specialCase(int initCatHeight, int workerCatsNumber) {
    if (initCatHeight == 1) cout << "0 1" << endl;
    else {
        int nest = 1;
        for (int i = 2; i < initCatHeight; i *= 2, nest++) ;
        cout << nest << " " << (pow(2, nest + 1) - 1) << endl;
    }
}

int main() {
    int nest, n;
    getPrime();
    int initCatHeight, workerCatsNumber;
    while (cin >> initCatHeight >> workerCatsNumber, initCatHeight || workerCatsNumber) {
        // 特例处理。
        if (workerCatsNumber == 1) {
            specialCase(initCatHeight, workerCatsNumber);
            continue;
        }
        // 利用素因子分解求嵌套层数。
        nest = factoring(initCatHeight);
        nest = gcd(nest, factoring(workerCatsNumber));
        // 利用素因子分解结果和嵌套层数求 N。
        n = 1;
        for (int i = 0; i < MAXN; i++)
            if (factor[i])
                n *= pow(prime[i], factor[i] / nest);
        // 求未工作的猫数量和所有猫的高度总和。
        int unworkCatsNumber = 0, totalHeight = 0;
        while (workerCatsNumber > 1) {
            workerCatsNumber /= n;
            unworkCatsNumber += workerCatsNumber;
        }
        int exponent = 1;
        while (initCatHeight >= 1) {
            totalHeight += initCatHeight * exponent;
            exponent *= n;
            initCatHeight /= (n + 1);
        }
        // 输出。
        cout << unworkCatsNumber << " " << totalHeight << endl;
    }
    return 0;
}
```

## 总结
本题是一道数学建模与数论结合的题目，关键在于从给定的 $H$ 和 $W$ 中解出 $N$ 和 $M$。通过质因数分解和最大公约数的性质，可以高效求解。需要注意处理 $W=1$ 的特殊情况。代码实现中预先生成素数表，提高了分解效率。
