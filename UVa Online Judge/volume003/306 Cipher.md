[UVa 306 Cipher](https://blog.csdn.net/metaphysis/article/details/161445975)

## 题目描述

$\texttt{Bob}$ 和 $\texttt{Alice}$ 开始使用一种全新的编码方案。他们选择了一个由 $n$ 个不同整数组成的密钥 $a_1, a_2, \dots, a_n$，其中 $1 \leq a_i \leq n$。编码原理如下：

将消息写在密钥下方，使得消息中的字符与密钥中的数字对齐。位置 $i$ 处的字符在加密后出现在位置 $a_i$ 处。然后，对加密后的消息以相同的方式再次加密。这个过程重复 $k$ 次。经过 $k$ 次加密后，他们交换消息。

消息长度总是 $\leq n$。如果消息短于 $n$，则在末尾添加空格以使其长度达到 $n$。

要求：编写程序，读取密钥，然后读取一系列由 $k$ 和消息组成的对，输出经过 $k$ 次加密后的消息。

### 输入格式

输入文件由多个数据块组成。每个数据块的第一行包含一个整数 $n$（$0 < n \leq 200$）。下一行包含 $n$ 个两两不同的整数，每个整数在 $1$ 到 $n$ 之间。接下来的若干行每行包含一个整数 $k$ 和一个 $\texttt{ASCII}$ 字符消息（用空格分隔）。数据块以单独一行 `0` 结束。最后一个数据块之后还有单独一行 `0`。

### 输出格式

输出分为与输入块对应的块。每个块包含输入消息按相同顺序加密后的结果。每个加密消息的长度为 $n$。每个块之后输出一个空行。

### 样例输入

```
10
4 5 3 7 2 8 1 6 10 9
1 Hello Bob
1995 CERC
0
0
```

### 样例输出

```
BolHeol b
C RCE
```

---

## 题目分析

### 问题的本质

这是一个**置换的幂**问题。密钥定义了一个**置换** $\sigma$：对于位置 $i$，$\sigma(i) = a_i$。一次加密就是将消息按照置换 $\sigma$ 重新排列：

$$
\text{encrypted}[a_i] = \text{message}[i]
$$

等价地，如果我们将消息看作一个函数 $m: \{1, \dots, n\} \to \text{char}$，那么加密一次得到的新消息是 $m \circ \sigma^{-1}$。但更方便的理解是：**位置 $i$ 的字符在加密后会移动到位置 $\sigma(i)$**。

经过 $k$ 次加密后，位置 $i$ 的字符会移动到位置 $\sigma^k(i)$。

### 直接模拟的瓶颈

最直接的方法是：对每条消息，循环 $k$ 次，每次应用置换。时间复杂度为 $O(k \times n)$。但 $k$ 可能非常大（样例中 $k = 1995$，实际可能更大），直接模拟不可行。

### 置换的循环分解

置换可以分解为若干个不相交的**循环**（$\texttt{cycle}$）。例如，密钥 `4 5 3 7 2 8 1 6 10 9` 对应的置换为：

- $1 \to 4 \to 7 \to 1$：循环长度为 $3$
- $2 \to 5 \to 2$：循环长度为 $2$
- $3 \to 3$：循环长度为 $1$
- $6 \to 8 \to 6$：循环长度为 $2$
- $9 \to 10 \to 9$：循环长度为 $2$

在一个长度为 $L$ 的循环中，经过 $k$ 次置换后，位置 $i$ 的字符会移动到循环中的第 $(k \bmod L)$ 个位置之后。

### 快速加密

因此，不需要模拟 $k$ 次加密，只需要：
1. 找出每个位置所在的循环及其长度
2. 计算 $k \bmod L$，确定字符移动的目标位置
3. 直接构造加密后的消息

---

## 解题思路

### 步骤一：读取密钥并构建置换

密钥是一个长度为 $n$ 的排列，表示 $\sigma(i) = a_i$。读取后存储在 `key[1..n]` 中。

### 步骤二：循环分解

对于每个位置 $i$，沿着置换追踪，直到回到 $i$，记录循环中的位置序列。同时记录循环长度 `cycle[i]`。

代码中的实现方式：

```cpp
for (int i = 1; i <= n; i++)
{
    int length = 1;
    permutation[i][length] = key[i];
    for (int j = key[i]; j != i; j = key[j], permutation[i][length] = j)
        length++;
    permutation[i][0] = permutation[i][length];
    cycle[i] = length;
}
```

这里 `permutation[i][t]` 表示从位置 $i$ 出发，经过 $t$ 次置换后到达的位置。特别地，`permutation[i][0]` 存储的是经过 `cycle[i]` 次置换后回到的位置（即 $i$ 本身）。

### 步骤三：处理消息

每条消息的格式为：`k message`。由于消息可能包含空格，需要使用 `getline` 读取。但需要注意输入格式中 `k` 和消息之间用空格分隔，且消息可能为空。

处理步骤：
1. 读取整数 $k$
2. 使用 `getline` 读取剩余的行作为消息
3. 如果消息长度小于 $n$，在末尾补空格
4. 计算 `k % cycle[i]`，确定位置 $i$ 的字符应该移动到 `permutation[i][k % cycle[i]]`
5. 构造加密后的消息并输出

### 步骤四：输出格式

- 每个加密消息占一行，长度为 $n$
- 每个数据块结束后输出一个空行

---

## 算法复杂度分析

### 时间复杂度

- 循环分解：$O(n)$，因为每个位置只被访问一次
- 每条消息加密：$O(n)$
- 总复杂度：$O(n \times m)$，其中 $m$ 是消息数量

### 空间复杂度

- 存储密钥：$O(n)$
- 存储循环信息：`permutation` 数组大小为 $O(n^2)$（$200 \times 200 = 40000$），完全可行
- 消息存储：$O(n)$

---

## 正确性证明

**引理 1**：置换可以分解为若干个不相交的循环。

证明：这是置换的循环分解定理。$\square$

**引理 2**：对于长度为 $L$ 的循环，经过 $k$ 次置换后，位置 $i$ 的字符移动到循环中距 $i$ 步数为 $k \bmod L$ 的位置。

证明：在循环中，每应用一次置换，字符沿循环移动一步。经过 $k$ 步后，移动了 $k \bmod L$ 步（因为 $L$ 步后回到原位置）。$\square$

**引理 3**：`permutation[i][k % cycle[i]]` 正确给出了位置 $i$ 的字符在 $k$ 次加密后的目标位置。

证明：`permutation[i][t]` 存储从 $i$ 出发经过 $t$ 步到达的位置。由引理 2，$t = k \bmod L$ 即为所需步数。$\square$

---

## 参考代码

```cpp
// Cipher
// UVa ID: 306
// Verdict: Accepted
// Submission Date: 2016-07-01
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int key[210];           // 存储密钥置换
int cycle[210];         // 每个位置所在循环的长度
int permutation[210][210];  // permutation[i][t] 表示从 i 出发经过 t 次置换后的位置
int n, k;               // n: 置换长度, k: 加密次数
char message[210];      // 原始消息（处理后长度为 n）
char ciphered[210];     // 加密后的消息

// 找出每个位置所在的循环，并记录循环信息和步进位置
void findCycle()
{
    for (int i = 1; i <= n; i++)
    {
        int length = 1;
        // 记录第一步：从 i 到 key[i]
        permutation[i][length] = key[i];
        // 沿着置换追踪，直到回到 i
        for (int j = key[i]; j != i; j = key[j], permutation[i][length] = j)
            length++;
        // permutation[i][0] 存储经过 cycle[i] 步后的位置（即 i 本身）
        permutation[i][0] = permutation[i][length];
        cycle[i] = length;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    while (cin >> n, n)
    {
        // 读取密钥（1-based 索引）
        for (int i = 1; i <= n; i++) 
            cin >> key[i];

        // 处理该数据块中的所有消息
        while (cin >> k, k)
        {
            // 读取消息（可能包含空格）
            cin.getline(message, 210);
            
            // 计算消息的实际长度
            int number = 1;
            while (message[number] != '\0') 
                number++;
            // 如果消息长度不足 n，用空格填充
            while (number <= n) 
                message[number++] = ' ';
            message[number] = '\0';

            // 计算置换的循环分解
            findCycle();

            // 加密：位置 i 的字符移动到 permutation[i][k % cycle[i]]
            for (int i = 1; i <= n; i++) 
                ciphered[permutation[i][k % cycle[i]]] = message[i];
            
            // 输出加密后的消息
            for (int i = 1; i <= n; i++) 
                cout << ciphered[i];
            cout << "\n";
        }

        // 每个数据块后输出一个空行
        cout << "\n";
    }

    return 0;
}
```

---

## 总结

本题的核心在于：
1. **置换的循环分解**：将置换分解为若干个不相交的循环
2. **快速幂思想**：$k$ 次置换等价于在循环中移动 $k \bmod L$ 步
3. **预处理循环信息**：提前计算每个位置 $t$ 步后的目标位置

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 置换 | $a_1, a_2, \dots, a_n$ 是 $1 \sim n$ 的一个排列 |
| 循环分解 | 每个位置属于唯一的一个循环 |
| 循环长度 $L$ | 经过 $L$ 次置换后回到原位置 |
| 加密 $k$ 次 | 等价于在循环中移动 $k \bmod L$ 步 |
| 空格填充 | 消息短于 $n$ 时末尾补空格 |
| 输出格式 | 每个数据块后空行 |

### 与快速幂的类比

本题的核心技巧与**快速幂**思想类似：通过预计算置换的幂次，将 $O(k)$ 的模拟优化为 $O(\log k)$ 甚至 $O(1)$（因为 $k$ 的模数很小）。这种“置换幂”的技巧在密码学和组合数学中具有广泛应用。
