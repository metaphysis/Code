[UVa 264 Count on Cantor](https://blog.csdn.net/metaphysis/article/details/161308160)

## 题目分析

本题描述了康托尔（$\texttt{Georg Cantor}$）证明有理数集是可数集的一个经典方法，即通过一个特定的对角线枚举方式，将所有的正有理数排列成一个序列。题目要求对于给定的若干个位置编号（从 $1$ 开始），输出该位置上的分数值。

### 枚举规律

题目给出了如下排列方式：

$$
\frac{1}{1},\; \frac{1}{2},\; \frac{2}{1},\; \frac{3}{1},\; \frac{2}{2},\; \frac{1}{3},\; \frac{1}{4},\; \frac{2}{3},\; \frac{3}{2},\; \frac{4}{1},\; \frac{5}{1},\; \frac{4}{2},\; \frac{3}{3},\; \frac{2}{4},\; \frac{1}{5},\; \ldots
$$

观察排列规律，可以发现分数的枚举是按照斜线（对角线）方向进行的。每条斜线上分数的分子与分母之和为常数。

更具体地说：

- 第 $1$ 条斜线：$\frac{1}{1}$（和 $=2$，方向：右上 → 左下）
- 第 $2$ 条斜线：$\frac{1}{2},\; \frac{2}{1}$（和 $=3$，方向：左下 → 右上）
- 第 $3$ 条斜线：$\frac{3}{1},\; \frac{2}{2},\; \frac{1}{3}$（和 $=4$，方向：右上 → 左下）
- 第 $4$ 条斜线：$\frac{1}{4},\; \frac{2}{3},\; \frac{3}{2},\; \frac{4}{1}$（和 $=5$，方向：左下 → 右上）
- 第 $5$ 条斜线：$\frac{5}{1},\; \frac{4}{2},\; \frac{3}{3},\; \frac{2}{4},\; \frac{1}{5}$（和 $=6$，方向：右上 → 左下）

### 关键观察

设第 $n$ 条斜线（$n \ge 1$），则该斜线上分数的分子分母之和为 $n + 1$，且该斜线上的分数个数恰好为 $n$。

当 $n$ 为奇数时，斜线方向为“右上 → 左下”（即分子递减，分母递增）：
$$
\frac{n}{1},\; \frac{n-1}{2},\; \ldots,\; \frac{1}{n}
$$

当 $n$ 为偶数时，斜线方向为“左下 → 右上”（即分子递增，分母递减）：
$$
\frac{1}{n},\; \frac{2}{n-1},\; \ldots,\; \frac{n}{1}
$$

## 解题思路

### 方法一：预处理打表

由于输入范围最大为 $10^7$，可以直接预先计算出所有位置的分子和分母，存入两个大数组，然后根据输入直接查询输出。

这种做法的时间复杂度为 $\mathcal{O}(N)$，其中 $N = 10^7$，空间复杂度为 $\mathcal{O}(N)$。

### 方法二：直接数学计算

不需要预先生成所有项，而是根据输入的位置编号 $k$，确定它位于哪一条斜线。

#### 确定斜线编号

前 $n$ 条斜线包含的总项数为：
$$
S_n = 1 + 2 + \cdots + n = \frac{n(n+1)}{2}
$$

我们需要找到最小的 $n$，使得 $S_n \ge k$。可以通过解不等式：
$$
\frac{n(n+1)}{2} \ge k \quad \Rightarrow \quad n^2 + n - 2k \ge 0
$$
得到：
$$
n \ge \frac{-1 + \sqrt{1 + 8k}}{2}
$$
因此可以先计算一个初始估值 $n = \lfloor \sqrt{2k} \rfloor$，然后逐步增加直到满足条件。

#### 计算距离

定义距离 $d = S_n - k$，表示第 $k$ 项与该斜线最后一个元素之间的偏移量。

- 若 $n$ 为奇数（方向：右上 → 左下）：
  - 该斜线最后一个元素是 $\frac{n}{1}$，倒数第二个是 $\frac{n-1}{2}$，依此类推。
  - 因此从后往前数 $d$ 个位置：分子 = $n - d$，分母 = $1 + d$。
- 若 $n$ 为偶数（方向：左下 → 右上）：
  - 该斜线最后一个元素是 $\frac{1}{n}$，倒数第二个是 $\frac{2}{n-1}$，依此类推。
  - 因此从后往前数 $d$ 个位置：分子 = $1 + d$，分母 = $n - d$。

此方法时间复杂度为 $\mathcal{O}(1)$ 每次查询，运行速度非常快。

## 代码实现

### 方法一代码（预处理打表）

```cpp
// Count on Cantor
// UVa ID: 264
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int numerator[10001628], denominator[10001628];

// 预处理函数：生成所有位置的分子和分母
void initialize()
{
    // 方向标志，true 表示从左下向右上（分子递增，分母递减）
    bool fromLeftToRight = true;
    
    int left = 1, right = 1, index = 0;
    // 生成足够数量的项，最大输入为 10^7，数组开略大
    while (index < 10001628)
    {
        if (fromLeftToRight)
        {
            // 方向：左下 → 右上，分子从 1 递增到 left，分母从 left 递减到 1
            for (int i = left, j = 1; i >= 1; i--, j++)
            {
                numerator[index] = i;
                denominator[index] = j;
                index++;
            }
        }
        else
        {
            // 方向：右上 → 左下，分子从 left 递减到 1，分母从 1 递增到 right
            for (int i = 1, j = right; i <= left; i++, j--)
            {
                numerator[index] = i;
                denominator[index] = j;
                index++;
            }
        }
        
        // 切换方向
        fromLeftToRight = !fromLeftToRight;
        // 进入下一条斜线，left 和 right 均增加 1
        left++;
        right++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    // 预处理所有项
    initialize();
    
    int number;
    while (cin >> number)
    {
        cout << "TERM " << number << " IS ";
        // 数组下标从 0 开始，第 number 项对应下标 number - 1
        cout << numerator[number - 1] << "/" << denominator[number - 1] << "\n";
    }
             
    return 0;
}
```

### 方法二代码（直接数学计算）

```cpp
// Count on Cantor
// UVa ID: 264
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int number;          // 输入的位置编号
    int n;               // 斜线编号
    int distance;        // 与斜线末尾的距离
    int numerator, denominator;  // 分子和分母
    
    while (cin >> number)
    {
        // 初始估算斜线编号，n 可能偏小
        n = (int)sqrt(2 * number) - 1;
        
        // 如果前 n 条斜线的总项数小于 number，则增加 n
        while (number > n * (n + 1) / 2)
            n++;
           
        // 计算与斜线末尾的距离
        distance = n * (n + 1) / 2 - number;
        
        cout << "TERM " << number << " IS ";
        
        // 根据斜线编号的奇偶性决定分数方向
        if ((n & 1) == 0)   // n 为偶数，方向：左下 → 右上
        {
            numerator = n - distance;
            denominator = 1 + distance;
        }
        else                // n 为奇数，方向：右上 → 左下
        {
            numerator = 1 + distance;
            denominator = n - distance;
        }
        
        cout << numerator << "/" << denominator << "\n";
    }
             
    return 0;
}
```

## 总结

本题的核心在于观察康托尔枚举有理数的规律，即将所有正有理数按斜线（对角线）排列，每条斜线上分子分母之和为常数，且方向交替变化。通过确定输入位置所在的斜线以及在该斜线上的偏移量，可以直接计算出分子和分母，无需生成整个序列。
