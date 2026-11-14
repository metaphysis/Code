[UVa 369 Combinations](https://blog.csdn.net/metaphysis/article/details/161611459)

## 题目描述

计算从 $N$ 个物品中取 $M$ 个的组合数 $C(N, M) = \frac{N!}{(N-M)! \times M!}$ 的精确值。

### 输入格式

输入包含一行或多行，每行包含两个整数 $N$ 和 $M$（$5 \leq N \leq 100$，$5 \leq M \leq 100$，$M \leq N$）。最后一行以 `0 0` 结束。

### 输出格式

对于每对 $(N, M)$，输出：

```
N things taken M at a time is C exactly.
```

### 样例输入

```
100 6
20 5
18 6
0 0
```

### 样例输出

```
100 things taken 6 at a time is 1192052400 exactly.
20 things taken 5 at a time is 15504 exactly.
18 things taken 6 at a time is 18564 exactly.
```

---

## 题目分析

### 问题的本质

这是一个**组合数计算**问题。需要精确计算 $C(N, M)$，其中 $N, M \leq 100$。

### 直接计算的挑战

直接计算阶乘 $N!$ 会导致数字非常巨大（$100!$ 有 $158$ 位），但最终结果 $C(N, M)$ 在 $32$ 位整数范围内。因此需要一种方法避免中间结果溢出。

### 解决思路

使用**质因数分解**法：
1. 将 $C(N, M)$ 表示为质因数的乘积形式
2. 计算分子和分母中每个质数的指数
3. 相减得到最终指数
4. 计算乘积

### 质因数分解的优势

- 中间结果不会溢出（因为最终结果在 $32$ 位范围内，但中间乘积可能超过）
- 使用大整数或边乘边除可避免溢出，但质因数分解更直观

---
## 参考代码

```cpp
// Combinations
// UVa ID: 369
// Verdict: Accepted
// Submission Date: 2016-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 100 以内的质数
vector<int> primes = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
    61, 67, 71, 73, 79, 83, 89, 97
};

// 计算 n! 的质因数分解，结果存储在 factors 映射中
void getPrimes(int n, map<int, int>& factors)
{
    for (int i = 2; i <= n; i++)
    {
        int t = i;
        // 对每个数进行质因数分解
        for (auto p : primes)
        {
            while (t % p == 0)
            {
                factors[p]++;
                t /= p;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int N, M;
    while (cin >> N >> M, N && M)
    {
        map<int, int> factorsOfN;      // N! 的质因数
        map<int, int> factorsOfN_M;    // (N-M)! 的质因数
        map<int, int> factorsOfM;      // M! 的质因数
        
        // 初始化
        for (auto p : primes)
        {
            factorsOfN[p] = 0;
            factorsOfN_M[p] = 0;
            factorsOfM[p] = 0;
        }

        // 计算各个阶乘的质因数分解
        getPrimes(N, factorsOfN);
        getPrimes(N - M, factorsOfN_M);
        getPrimes(M, factorsOfM);

        // C(N,M) = N! / ((N-M)! * M!)
        // 减去分母的质因数
        for (auto p : factorsOfN_M)
            if (p.second > 0)
                factorsOfN[p.first] -= factorsOfN_M[p.first];

        for (auto p : factorsOfM)
            if (p.second > 0)
                factorsOfN[p.first] -= factorsOfM[p.first];

        // 计算最终乘积
        long long product = 1;
        for (auto p : factorsOfN)
            if (p.second > 0)
                product *= pow(p.first, p.second);

        cout << N << " things taken " << M << " at a time is ";
        cout << product << " exactly." << endl;
    }

    return 0;
}
``
