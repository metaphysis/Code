[UVa 128 Software CRC](https://blog.csdn.net/metaphysis/article/details/156751137)

## 题目描述

你在一家大量使用个人电脑的公司工作。老板 $\texttt{Penny Pincher}$ 博士一直想将这些电脑连接起来，但又不愿意花钱购买你建议的以太网卡。你无意中提到每台 $\texttt{PC}$ 都自带一个异步串行口（无需额外费用），于是老板抓住机会，让你编写必要的软件来实现 $\texttt{PC}$ 间的通信。

你了解到通信过程中容易出错，典型的解决方案是在每条消息末尾附加错误校验信息，以便接收程序能检测到传输错误（大多数情况下）。经过研究，你决定采用**$\texttt{CRC}$（循环冗余校验）**作为错误校验机制，并向老板提交了如下方案：

### $\texttt{CRC}$ 生成机制
待传输的消息被视为一个很长的正二进制数。消息的第一个字节是该二进制数的最高有效字节，第二个字节是次高有效字节，依此类推。这个二进制数称为 $m$（$\texttt{message}$）。实际传输的不是 $m$ ，而是一个新消息 $m_2$ ，它由 $m$ 和紧随其后的两字节 $\texttt{CRC}$ 值组成。

$\texttt{CRC}$ 值的选取原则是：$m_2$ 除以某个 $16$ 位值 $g$（生成器）的余数为 $0$。这样接收程序只需将收到的消息除以 $g$ ，若余数为 $0$ 就认为没有发生传输错误。

你在书中发现大多数建议的 $g$ 值都是奇数，但没有其他明显规律，因此你选择了 $g = 34943$（十进制）作为生成器。

你的任务是设计一个算法，计算任意待发送消息对应的 $\texttt{CRC}$ 值，并编写程序进行测试。

### 输入格式
每行输入包含不超过 $1024$ 个 $\texttt{ASCII}$ 字符（每行字符不包括换行符）。  
输入以第一列为 `#` 的行结束。

### 输出格式
对每个输入行，计算该行消息的 $\texttt{CRC}$ 值，并以十六进制形式输出两个字节的 $\texttt{CRC}$ 值（中间用空格分隔）。  
注意每个 $\texttt{CRC}$ 值应在 $0$ 到 $34942$（十进制）范围内。

---

## 题目分析与解题思路

本题的核心是计算给定消息的 $16$ 位 $\texttt{CRC}$ 校验码，使得附加 $\texttt{CRC}$ 后的整个消息（视为一个大整数）能被 $g = 34943$ 整除。

### 数学模型

设消息 $m$ 由 $k$ 个字节组成：$b_{k-1}, b_{k-2}, \dots, b_0$（其中 $b_{k-1}$ 是最高有效字节）。  
将 $m$ 视为一个 $256$ 进制的数，即：

$$
m = b_{k-1} \cdot 256^{k-1} + b_{k-2} \cdot 256^{k-2} + \dots + b_0 \cdot 256^0
$$

附加两字节 $\texttt{CRC}$ 值 $c$（$0 \le c < 65536$）后，得到新消息：

$$
m_2 = m \cdot 65536 + c
$$

要求 $m_2 \mod g = 0$，即：

$$
(m \cdot 65536 + c) \mod g = 0
$$

因此：

$$
c = (g - (m \cdot 65536) \mod g) \mod g
$$

注意 $c$ 应输出为两个字节，即 $c$ 在 $0$ 到 $65535$ 之间，但题目保证 $g = 34943$，所以 $c < g$，自然满足。

### 算法设计

直接计算 $m$ 可能非常大（最多 $1024$ 字节，即 $2^{8192}$ 量级），必须边读边模 $g$ 运算。

我们可以从最低有效字节开始计算 $m \mod g$：

设当前余数为 $r$（初始为 $0$），逐个处理字节 $b_i$（从最后一个字节开始向前）：

$$
r = (r + b_i \cdot 256^i) \mod g
$$

但 $256^i$ 也会很大，需要预先计算 $256^i \mod g$ 的模幂值。

可以预先计算了一个数组 `modular[i]` ，其中：

`modular[i] = (65536 * 256^i) mod g`

注意这里 `65536 = 256^2` ，是因为在计算 $m \cdot 65536$ 时，相当于将 $m$ 左移 $16$ 位（即乘以 $65536$）。代码中从最低字节开始累加时，直接使用了 `modular[j]` ，其中 $j$ 是当前字节的索引（从 $0$ 开始）。

### 计算步骤

1. 预处理 `modular[0..1024]`，其中 `modular[0] = 65536 mod g`，`modular[i] = (modular[i-1] * 256) mod g`。
2. 对每个输入行（非空且不以 `#` 开头）：
   - 从字符串末尾开始向前遍历（即从最低有效字节向最高有效字节）。
   - 对于位置 $j$（从 $0$ 开始）的字符 `line[i]`，累加 `(line[i] * modular[j]) mod g` 到余数 `residue`。
   - 遍历完成后，`residue` 即为 $(m \cdot 65536) \mod g$。
   - 计算 `c = (g - residue) mod g`。
   - 将 `c` 转换为两个字节的十六进制输出。

### 边界情况
- 空行：$\texttt{CRC}$ 值为 `00 00`。
- 输入结束：第一列为 `#` 的行。

---

## 代码实现

```cpp
// Software CRC
// UVa ID: 128
// Verdict: Accepted
// Submission Date: 2015-12-01
// UVa Run Time: 0.352s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD_BASE = 34943;

int modular[1030];

// 预处理 modular 数组：modular[i] = (65536 * 256^i) % MOD_BASE
void generateModular() {
    modular[0] = 65536 % MOD_BASE;
    for (int i = 1; i <= 1024; i++)
        modular[i] = (modular[i - 1] * 256) % MOD_BASE;
}

// 将16位CRC值转换为两个字节的十六进制形式输出
void intToHex(int residue) {
    string hex = "0123456789ABCDEF";
    cout << hex[residue / 256 / 16];
    cout << hex[residue / 256 % 16];
    cout << " ";
    cout << hex[(residue % 256) / 16];
    cout << hex[residue % 256 % 16];
    cout << endl;
}

// 计算一行消息的CRC并输出
void softwareCRC(string line) {
    int residue = 0;
    // 从最低有效字节开始累加
    for (int i = line.length() - 1, j = 0; i >= 0; i--, j++)
        residue += (line[i] * modular[j] % MOD_BASE);
    // 计算CRC值
    residue = (MOD_BASE - residue % MOD_BASE) % MOD_BASE;
    intToHex(residue);
}

int main() {
    generateModular();
    string line;
    while(getline(cin, line)) {
        if (line.length() == 0) {
            cout << "00 00" << endl;
            continue;
        }
        if (line[0] == '#') break;
        softwareCRC(line);
    }
    return 0;
}
```

---

## 样例说明

输入：

```
this is a test
A
#
```

输出：

```
77 FD
00 00
0C 86
```

- 第一行消息 `"this is a test"` 的 $\texttt{CRC}$ 为 `0x77FD`。
- 第二行 `"A"` 的CRC为 `0x0C86`。
- 空行输出 `00 00`。

---

## 总结

本题是一个典型的 $\texttt{CRC}$ 校验码计算问题，关键在于理解消息被视为一个大整数，以及模运算在避免大数计算中的应用。通过预处理 $256^i \mod g$ 的值，可以高效地逐字节计算余数，最终得到两字节的 $\texttt{CRC}$ 校验码。
