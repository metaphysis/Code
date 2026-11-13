[UVa 294 Divisors](https://blog.csdn.net/metaphysis/article/details/161387998)

## 题目分析

本题要求给定若干个区间 $[L, U]$，在每个区间内找出一个数 $P$，使得 $P$ 的正因数个数 $D$ 最大。如果有多个数因数个数相同且均为最大，则选取最小的那个数。最后按照指定格式输出结果。

题目给出的数据范围是 $1 \leqslant L \leqslant U \leqslant 10^8$，且区间长度满足 $0 \leqslant U-L \leqslant 10000$。这意味着区间长度最大为 $10^4$，但单个数字本身最大可达 $10^8$。

一个最直接的想法是：对于区间内的每个数，通过试除法计算其因数个数，然后比较得出最大值。但 $10^8$ 级别的数字，如果用 $\sqrt{n}$ 的试除法（约为 $10^4$ 次运算），再乘以区间长度 $10^4$，总运算量约为 $10^8$ 次，对于 $N$ 个区间来说可能超时。因此需要更高效的算法。

## 解题思路

### 因数个数定理

根据数论知识，若一个正整数 $n$ 的质因数分解式为：

$$
n = p_1^{a_1} \cdot p_2^{a_2} \cdots p_k^{a_k}
$$

则 $n$ 的正因数个数为：

$$
d(n) = (a_1+1)(a_2+1)\cdots(a_k+1)
$$

因此，要求一个数的因数个数，只需要得到它的质因数分解形式，然后对每个指数加 $1$ 后连乘即可。

### 预处理素数表

由于 $U \leqslant 10^8$，$\sqrt{U} \approx 10000$。实际上，$31622^2 \approx 10^9$，因此只需要筛出 $31622$ 以内的所有素数，即可对 $10^8$ 以内的数进行质因数分解。

代码中取上界为 $31263$（稍大于 $31622$ 的近似值），使用埃拉托色尼筛法（ $\texttt{Sieve}$ ）得到所有素数，存储在 `primes` 向量中。

### 计算因数个数的两种方法

代码中提供了两种计算因数个数的方法：

1. **$\texttt{getCountOfDivisors1}$** ：通过集合交替存储因数。每次处理一个质因数时，将已有的因数集合中的每个数乘以该质因数，得到新的因数，然后交替存放在两个集合中。这种方法直接生成了所有因数，适用于需要实际因数的场景，但空间和时间开销较大。

2. **$\texttt{getCountOfDivisors2}$** ：利用因数个数定理，先进行质因数分解，用 `map` 记录每个质因数的指数，最后计算 $(指数_1+1) \times (指数_2+1) \times \cdots$。这种方法只关心因数个数而不关心具体是哪些因数，效率更高。

代码最终使用的是第二种方法（调用 $\texttt{getCountOfDivisors2}$ ），因为本题只需要因数个数进行比较，无需枚举因数。

### 特殊情况处理

- 当 $n=1$ 时，因数只有 $1$ 本身，返回 $1$。
- 当 $n$ 是素数时，因数只有 $1$ 和 $n$，返回 $2$。利用预处理好的素数表 `isPrime` 可以快速判断。
- 在质因数分解后，若 $n>1$ 剩余，说明剩余部分是一个大于 $31263$ 的素数，此时因数个数需要再乘 $2$。

### 主逻辑

对于每个区间 $[L, U]$，遍历区间内的每一个数 $i$，调用 $\texttt{getCountOfDivisors2}(i)$ 计算其因数个数，并与当前最大值比较。若遇到更大的因数个数，则更新最大值和对应的最小数字 $P$。

由于区间长度最大仅为 $10^4$，即使每个数的计算需要分解质因数（最多尝试 $\sqrt{10^8} \approx 10^4$ 以内的素数），总计算量也是可接受的。

## 复杂度分析

- **预处理**：筛法求素数的时间复杂度约为 $O(n \log \log n)$，其中 $n \approx 31622$，非常快。
- **单次因数个数计算**：最坏情况下需要遍历所有 $3401$ 个素数（$31622$ 以内的素数个数约为 $3401$），每次除法运算很快。对于 $10^8$ 附近的数，质因数分解很快结束。
- **整体**：对于每个区间，最多计算 $10001$ 次因数个数，每次最多约 $3401$ 次除法，总操作次数在 $3 \times 10^7$ 级别，实际运行非常迅速。

## 代码实现

```cpp
// Divisors
// UVa ID: 294
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> primes;         // 存储筛法得到的素数
int isPrime[31263];         // 标记是否为素数的数组
int N, L, U;

// 埃拉托色尼筛法，筛选出 31263 以内的所有素数
void sieve()
{
    memset(isPrime, 1, sizeof(isPrime));  // 初始化所有数为素数
    for (int i = 2; i < 31263; i++)
        if (isPrime[i])
        {
            // 将 i 的倍数标记为非素数
            for (int j = 2 * i; j < 31263; j += i) isPrime[j] = 0;
            primes.push_back(i);  // 将素数存入向量
        }
}

// 方法一：通过生成所有因数来计算因数个数（本题实际未使用）
int getCountOfDivisors1(int n)
{
    if (n == 1) return 1;                     // 1 的因数只有自身
    if (n < 31263 && isPrime[n]) return 2;    // 素数有 2 个因数

    set<int> numbers, divisors;
    numbers.insert(1);                        // 初始因数集合包含 1

    for (int i = 0; i < primes.size(); i++)
    {
        while (n % primes[i] == 0)
        {
            n /= primes[i];

            if (numbers.size())
            {
                // 将现有因数乘以当前质因子，生成新因数
                for (auto it = numbers.begin(); it != numbers.end(); it++)
                {
                    divisors.insert(*it);
                    divisors.insert(*it * primes[i]);
                }
                numbers.clear();
            }
            else
            {
                for (auto it = divisors.begin(); it != divisors.end(); it++)
                {
                    numbers.insert(*it);
                    numbers.insert(*it * primes[i]);
                }
                divisors.clear();
            }
        }

        if (n == 1) break;   // 分解完成
    }

    // 如果剩余 n > 1，说明还有一个大于 31263 的素因子
    if (n > 1) return 2;

    // 返回两个集合中较大的那个（即所有因数的数量）
    return max(numbers.size(), divisors.size());
}

// 方法二：利用质因数分解和因数个数定理，效率更高（实际使用的方法）
int getCountOfDivisors2(int n)
{
    if (n == 1) return 1;                     // 1 的因数只有自身
    if (n < 31263 && isPrime[n]) return 2;    // 素数有 2 个因数

    map<int, int> divisors;   // 记录质因子及其指数

    // 用预处理好的素数进行质因数分解
    for (int i = 0; i < primes.size(); i++)
    {
        while (n % primes[i] == 0)
        {
            n /= primes[i];
            divisors[primes[i]]++;   // 指数加 1
        }
        if (n == 1) break;
    }

    // 如果 n > 1，说明剩余部分是一个大于 31263 的素数
    if (n > 1) return 2;

    // 根据因数个数定理：(a1+1)*(a2+1)*...
    int count = 1;
    for (auto pair : divisors) count *= (pair.second + 1);

    return count;
}

// 在给定区间 [L, U] 内查找因数个数最多的数
void findNumber()
{
    int minN = L, maxCountOfDivisors = 0, countOfDivisors;

    // 遍历区间内的每一个数
    for (int i = L; i <= U; i++)
        if ((countOfDivisors = getCountOfDivisors2(i)) > maxCountOfDivisors)
        {
            maxCountOfDivisors = countOfDivisors;
            minN = i;   // 更新为当前因数个数更多的数（由于遍历是从小到大，相同个数时自然保留较小的）
        }

    // 按要求格式输出结果
    cout << "Between " << L << " and ";
    cout << U << ", " << minN << " has a maximum of ";
    cout << maxCountOfDivisors << " divisors.\n";
}

int main(int argc, char *argv[])
{
    // 加速输入输出
    cin.tie(0), cout.tie(0), cin.sync_with_stdio(false);

    sieve();   // 预处理素数表

    cin >> N;  // 读入区间个数
    while (N--)
    {
        cin >> L >> U;
        findNumber();
    }

    return 0;
}
```
