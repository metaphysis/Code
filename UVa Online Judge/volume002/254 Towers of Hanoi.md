[UVa 254 Towers of Hanoi](https://blog.csdn.net/metaphysis/article/details/161281878)

## 题目分析

汉诺塔（$\texttt{Towers of Hanoi}$）是一个经典的递归问题。本题要求我们根据特定的最优算法，模拟汉诺塔在给定移动步数后的状态，输出三个柱子上分别有多少个盘子。

### 问题背景

标准的汉诺塔问题有 $3$ 根柱子，记为 $A$、$B$、$C$，以及 $n$ 个大小不一的盘子，初始时所有盘子都按从大到小的顺序堆叠在柱子 $A$ 上（大的在底部，小的在顶部）。目标是将整个塔从 $A$ 移动到另一根柱子上。

### 最优移动算法

题目描述了一个已知的最优解法，其最小移动次数为 $2^n - 1$。该算法的规则如下：

- **奇数步**：移动最小的盘子（编号 $1$）到循环序列 $ABCABC\ldots$ 中的下一根柱子上（即 $A \to B$，$B \to C$，$C \to A$）。
- **偶数步**：进行唯一可能的移动，且该移动不能涉及最小的盘子 $1$。

这个算法保证能在 $2^n - 1$ 步内完成整个移动过程。

### 输入输出格式

**输入**：多行数据，每行包含两个整数 $n$ 和 $m$，其中：
- $n$ 表示盘子的数量，范围 $[0, 100]$。
- $m$ 表示最后一步的移动步数，范围 $[0, 2^n - 1]$。
- 输入以一行 `0 0` 结束。

**输出**：对于每组输入，输出一行三个整数，分别表示柱子 $A$、$B$、$C$ 上的盘子数量。

**样例**：

输入：
```
3 5
64 2
8 45
0 0
```

输出：
```
1 1 1
62 1 1
4 2 2
```

## 解题思路

### 核心挑战

本题的难点在于 $n$ 最大可达 $100$，而 $2^{100} - 1$ 是一个巨大的数字（约 $10^{30}$ 量级），无法使用普通的整数类型（如 $64$ 位整数）直接存储 $m$。因此，我们必须使用大数处理技术。

另外，$m$ 可以是 $0$ 到 $2^n - 1$ 之间的任意值，我们需要模拟到第 $m$ 步结束时的状态。

### 算法设计思路

仔细观察最优移动算法，可以发现一个重要的规律：

**定理**：在最优移动策略中，每连续 $2^k$ 步移动，最大的 $k$ 个盘子会整体移动到目标柱子上。

更具体地说：
- 在第 $1, 3, 5, \ldots$ 步（奇数步）时，移动最小的盘子。
- 在第 $2, 4, 6, \ldots$ 步（偶数步）时，移动另一个盘子。

这种结构使得我们可以利用二进制分解来加速模拟，而不是一步一步地执行 $m$ 次移动（当 $m$ 很大时无法承受）。

### 基于二进制分解的模拟方法

设当前状态如下：
- 柱子编号为 $0, 1, 2$，分别对应 $A, B, C$。
- 当前最小的盘子所在位置为 $i$（即当前应从哪里开始奇数步移动）。
- 我们需要模拟剩余的移动步数。

#### 关键观察

考虑连续 $2^k$ 步移动的规律：
1. 在这 $2^k$ 步中，最小的 $k$ 个盘子（编号 $1$ 到 $k$）会“来回移动”，而第 $k+1$ 大的盘子会被移动一次。
2. 实际上，每 $2^k$ 步可以将最大的 $k$ 个盘子整体移动到下一个柱子上。

#### 算法步骤

1. **将 $m$ 转换为二进制表示**：由于 $m$ 可能很大，我们需要用字符串表示 $m$，然后将其转换为二进制形式的向量（每一位用一个整数 $0$ 或 $1$ 表示）。

2. **确定最大可移动的盘子数量**：
   - 给定一个二进制数 $m$，找出最大的 $k$，使得 $2^k - 1 \le m$。
   - 这意味着我们可以安全地将最大的 $k$ 个盘子作为一个整体移动。

3. **整体移动**：
   - 根据 $k$ 的奇偶性决定移动方向：
     - 如果 $k$ 是奇数，将最大的 $k$ 个盘子从当前位置移动到 $i+1$（模 $3$）。
     - 如果 $k$ 是偶数，将最大的 $k$ 个盘子从当前位置移动到 $i+2$（模 $3$）。
   - 更新 $m = m - (2^k - 1)$。

4. **处理剩余步数**：
   - 剩余步数必然小于 $2^k$，且此时最小的 $k$ 个盘子处于某种状态。
   - 接下来只需要处理一步移动（即移动最小的盘子或进行唯一可能的另一移动），然后更新 $m$，重复整个过程。

5. **终止条件**：当 $m = 0$ 时，模拟结束。

### 大数处理

由于 $m$ 可能非常大（最多 $100$ 位十进制数），我们需要实现：
- 十进制字符串到二进制向量的转换。
- 二进制向量的减法运算（减去 $1$ 或 $2^k - 1$）。

在代码中，`parseMovesToBinary` 函数将十进制字符串转换为二进制向量，`findMaxK` 函数找出最大的 $k$ 使得 $2^k - 1 \le m$，`subtract` 函数用于减去 $1$。

### 状态表示

使用 `vector<vector<int>> disks(3)` 表示三个柱子上的盘子，每个柱子是一个 `vector<int>`，存储盘子编号（编号越小表示盘子越小，$1$ 是最小的盘子）。初始时，所有盘子都在柱子 $0$（即 $A$）上。

## 代码实现

```cpp
// Towers of Hanoi
// UVa ID: 254
// Verdict: Accepted
// Submission Date: 2016-05-13
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 存储 m 的二进制表示（低位在末尾，高位在前）
vector<int> moves;

// 将十进制字符串 m 转换为二进制向量
void parseMovesToBinary(string m) {
    moves.clear();
    
    // 将字符串转换为数字向量，每个元素是一位十进制数字
    vector<int> digits;
    for (int i = 0; i < m.length(); i++)
        digits.push_back(m[i] - '0');
        
    // 不断除以 2，得到二进制表示
    while (digits.size()) {
        int remain = 0;
        for (int i = 0; i < digits.size(); i++) {
            digits[i] = remain * 10 + digits[i];
            remain = digits[i] % 2;
            digits[i] /= 2;
        }
        // 将余数（当前最低位）插入到二进制向量的开头
        moves.insert(moves.begin(), remain);
        
        // 去除前导零
        while (digits.size() && digits.front() == 0)
            digits.erase(digits.begin());
    }
}

// 找出最大的 k，使得 2^k - 1 <= 当前 moves 表示的数
// 同时将 moves 更新为减去 (2^k - 1) 后的结果
int findMaxK() {
    int k = moves.size();

    // 如果 m = 0，返回 0
    if (moves.size() == 0)
        return k;

    // 检查是否所有位都是 1，即 m = 2^k - 1
    bool allOne = true;
    for (int i = 0; i < moves.size(); i++)
        if (moves[i] == 0) {
            allOne = false;
            break;
        }

    // 如果 m 本身就是形如 2^k - 1 的数，直接返回 k，并将 moves 清空
    if (allOne) {
        moves.erase(moves.begin(), moves.end());
        return k;
    }

    // 否则，计算 m - (2^(k-1) - 1)
    // 实际上，当 m 不是全 1 时，最大的 k 满足 2^k - 1 <= m 就是当前二进制的长度
    // 然后从 m 中减去 (2^(k-1) - 1)
    int borrow = 0; 
    for (int i = moves.size() - 1; i >= 1; i--) {
        moves[i] -= (borrow + 1);
        if (moves[i] < 0) {
            moves[i] += 2;
            borrow = 1;
        } else borrow = 0;
    }
    moves[0] -= borrow;

    // 去除前导零
    while (moves.size() && moves.front() == 0) moves.erase(moves.begin());

    return (k - 1);
}

// 二进制减法：moves = moves - 1
void subtract() {
    vector<int> one(moves.size());

    // 构造二进制数 1（与 moves 同长度，高位补 0）
    for (int i = 0; i < one.size(); i++) one[i] = 0; 
    one.back() = 1;

    // 执行减法
    int borrow = 0; 
    for (int i = moves.size() - 1; i >= 0; i--) {
        moves[i] -= (borrow + one[i]);
        if (moves[i] < 0) {
            moves[i] += 2;
            borrow = 1;
        } else borrow = 0;
    }

    // 去除前导零
    while (moves.size() && moves.front() == 0) moves.erase(moves.begin());
}

// 三个柱子上的盘子，每个柱子用一个 vector 存储盘子编号（小号在顶部）
vector<vector<int>> disks(3);

int main() {
    int n;
    string m;  // m 用字符串存储，因为可能很大

    while (cin >> n >> m, n > 0) {
        // 将 m 转换为二进制向量
        parseMovesToBinary(m);

        // 初始化三个柱子
        disks.clear();
        disks.resize(3);

        // 初始时所有盘子都在柱子 A（索引 0）上
        // 注意：编号 1 是最小的盘子，放在 vector 的末尾（方便操作）
        for (int i = 1; i <= n; i++)
            disks[0].push_back(i);

        // i 表示当前最小盘子所在的柱子索引
        // 初始时最小盘子在 A（索引 0）上
        int i = 0, A, B, C;
        
        while (true) {
            // 找出可以整体移动的最大盘子数量 k
            int k = findMaxK();

            if (k == 0)  // 没有更多整体移动了
                break;

            // 根据 k 的奇偶性决定移动方向
            if (k % 2 == 1)  // k 为奇数，移动到 i+1
            {
                A = i, B = (i + 1) % 3, C = (i + 2) % 3;

                // 将 A 上最大的 k 个盘子整体移动到 B
                // 注意：这些盘子是 disks[A] 最前面的 k 个（因为大号盘子放在前面）
                disks[B].insert(disks[B].begin(), disks[A].begin(), disks[A].begin() + k);
                disks[A].erase(disks[A].begin(), disks[A].begin() + k);

                // 如果还有剩余步数，处理一步移动
                if (moves.size()) {
                    subtract();  // 减去 1
                    
                    // 进行唯一可能的移动（不涉及最小盘子的那个移动）
                    // 移动后，C 上的顶部盘子会移到 A 或反之
                    if (disks[C].size() == 0 || disks[C].front() > disks[A].front())
                    {
                        disks[C].insert(disks[C].begin(), disks[A].front());
                        disks[A].erase(disks[A].begin());
                    } else {
                        disks[A].insert(disks[A].begin(), disks[C].front());
                        disks[C].erase(disks[C].begin());
                    }
                }

                i = B;  // 更新最小盘子的位置
            }
            else  // k 为偶数，移动到 i+2
            {
                A = i, B = (i + 1) % 3, C = (i + 2) % 3;

                // 将 A 上最大的 k 个盘子整体移动到 C
                disks[C].insert(disks[C].begin(), disks[A].begin(), disks[A].begin() + k);
                disks[A].erase(disks[A].begin(), disks[A].begin() + k);

                // 如果还有剩余步数，处理一步移动
                if (moves.size()) {
                    subtract();  // 减去 1
                    
                    // 进行唯一可能的移动（不涉及最小盘子的那个移动）
                    if (disks[B].size() == 0 || disks[B].front() > disks[A].front()) {
                        disks[B].insert(disks[B].begin(), disks[A].front());
                        disks[A].erase(disks[A].begin());
                    } else {
                        disks[A].insert(disks[A].begin(), disks[B].front());
                        disks[B].erase(disks[B].begin());
                    }
                }
                
                i = C;  // 更新最小盘子的位置
            }
        }
        
        // 输出三个柱子上盘子的数量
        cout << disks[0].size() << " " << disks[1].size() << " " << disks[2].size() << "\n";
    }
    
    return 0;
}
```

## 算法复杂度分析

- **时间复杂度**：每次整体移动处理 $O(n)$ 级别的盘子操作，而整体移动的次数约为 $O(\log m) \approx O(n)$，因此总时间复杂度为 $O(n^2)$，对于 $n \le 100$ 完全可行。
- **空间复杂度**：$O(n)$，用于存储盘子和二进制表示。

## 总结

本题的核心在于利用汉诺塔最优解法的二进制结构，通过整体移动盘子来加速模拟，避免了一步一步迭代的低效。同时，由于 $m$ 可能非常大，必须使用大数处理技术（十进制字符串到二进制的转换以及二进制减法）。理解 $2^k$ 步移动的规律是解题的关键。
