# 题目描述

题目给出一个由四个 $16$ 位明文分组和四个 $16$ 位密钥分组构成的分组加密过程。每组输入包含一个 $64$ 位密文和一个 $64$ 位密钥，要求按照加密过程的逆过程恢复 $8$ 个明文字符。

题目描述中的运算包括异或、模 $2^{16}$ 加法和 $16$ 位循环左移。通过逆向推导可以得到常数时间的解密过程。

# 输入格式

输入包含多组数据，每组数据占一行，包含一个由 $16$ 个十六进制数字组成的密文和一个由 $16$ 个十六进制数字组成的密钥，中间由空白字符分隔。输入持续到文件结束。

# 输出格式

每组数据输出一行解密得到的 $8$ 个明文字符。

# 样例输入

```text
85bfa0242caa796e 1111222233334444
4c0d17279cbf4222 abcdabcdabcdabcd
```

# 样例输出

```text
TEACHERS
STUDENTS
```

# 题目分析

题面给出的加密流程将明文拆成 $4$ 个 $16$ 位分组，记为 $M_1,M_2,M_3,M_4$，密钥也拆成 $4$ 个 $16$ 位分组，记为 $K_1,K_2,K_3,K_4$。加密过程在这些分组上进行异或、模 $2^{16}$ 加法和循环移位。解密时，异或操作用异或自身撤销，加法用模 $2^{16}$ 减法撤销，循环左移用循环右移撤销。

按照题面图示直接推导，可以利用异或运算的抵消性质恢复中间变量。例如，若 $A_{10}=A_1\oplus A_9$ 且 $A_{11}=A_3\oplus A_9$，则 $A_{10}\oplus A_{11}=A_1\oplus A_3=A_5$。同理，可以从对应的输出分组中恢复其他异或组合，再按逆向顺序还原所有中间分组及明文。

不过，邮件指出，在线判题程序与题面图示并不完全一致。因此，直接照题面图示编写的解密代码虽然符合图示推导，却不符合实际判题程序。通过在线测试的实现必须采用邮件列出的实际运算规则、密钥移位量和字符打包顺序。下面先给出题面图示对应的推导及原始实现，再说明实际通过代码与它的差异。

# 解题思路

## 按题面图示推导

以下推导对应题面图示的运算关系。所有分组均为 $16$ 位数，加法结果模 $2^{16}$。

首先从输出端逆向恢复：

$$
\begin{aligned}
A_{10} &= \operatorname{ror}(C_1,K_4) \\
A_{13} &= C_2-K_3 \\
A_{11} &= C_3\oplus K_2 \\
A_{14} &= \operatorname{ror}(C_4,K_1)
\end{aligned}
$$

其中，$\operatorname{ror}$ 表示 $16$ 位循环右移，移位量按 $16$ 取模。

由 $A_5=A_1\oplus A_3$、$A_{10}=A_1\oplus A_9$ 和 $A_{11}=A_3\oplus A_9$，可得：

$$
A_5=A_{10}\oplus A_{11}
$$

又因为 $A_7$ 是 $A_5$ 循环左移 $K_1+K_2$ 位的结果，所以可以恢复 $A_7$。此外，由 $A_{13}=A_2\oplus A_{12}$ 和 $A_{14}=A_4\oplus A_{12}$，可得：

$$
A_6=A_2\oplus A_4=A_{13}\oplus A_{14}
$$

于是：

$$
A_9=\operatorname{rol}\big((A_7+A_6)\bmod 2^{16},K_3+K_4\big)
$$

其中，$\operatorname{rol}$ 表示 $16$ 位循环左移。得到 $A_9$ 后，逐步恢复：

$$
\begin{aligned}
A_1 &= A_{10}\oplus A_9 \\
A_3 &= A_{11}\oplus A_9 \\
A_{12} &= A_7\oplus A_9 \\
A_2 &= A_{13}\oplus A_{12} \\
A_4 &= A_{14}\oplus A_{12}
\end{aligned}
$$

最后逆向顶层运算：

$$
\begin{aligned}
M_1 &= \operatorname{ror}(A_1,K_1) \\
M_2 &= A_2-K_2 \\
M_3 &= A_3\oplus K_3 \\
M_4 &= \operatorname{ror}(A_4,K_4)
\end{aligned}
$$

这套推导与题面所示的关系一一对应。原始实现如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

uint32_t leftRotate(uint32_t value, uint32_t shift) {
    value &= 0xffff;
    shift %= 16;
    if (shift == 0) return value;
    return ((value << shift) | (value >> (16 - shift))) & 0xffff;
}

uint32_t rightRotate(uint32_t value, uint32_t shift) {
    value &= 0xffff;
    shift %= 16;
    if (shift == 0) return value;
    return ((value >> shift) | (value << (16 - shift))) & 0xffff;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string cipher, key;
    while (cin >> cipher >> key) {
        uint32_t c1 = stoul(cipher.substr(0, 4), nullptr, 16), c2 = stoul(cipher.substr(4, 4), nullptr, 16), c3 = stoul(cipher.substr(8, 4), nullptr, 16), c4 = stoul(cipher.substr(12, 4), nullptr, 16);
        uint32_t k1 = stoul(key.substr(0, 4), nullptr, 16), k2 = stoul(key.substr(4, 4), nullptr, 16), k3 = stoul(key.substr(8, 4), nullptr, 16), k4 = stoul(key.substr(12, 4), nullptr, 16);
        uint32_t a10 = rightRotate(c1, k4), a13 = (c2 + 65536 - k3) & 0xffff, a11 = c3 ^ k2, a14 = rightRotate(c4, k1);
        uint32_t a5 = a10 ^ a11, a6 = a13 ^ a14;
        uint32_t a7 = leftRotate(a5, k1 + k2), a9 = leftRotate((a7 + a6) & 0xffff, k3 + k4);
        uint32_t a1 = a10 ^ a9, a3 = a11 ^ a9, a12 = a7 ^ a9;
        uint32_t a2 = a13 ^ a12, a4 = a14 ^ a12;
        uint32_t m1 = rightRotate(a1, k1), m2 = (a2 + 65536 - k2) & 0xffff, m3 = a3 ^ k3, m4 = rightRotate(a4, k4);
        cout << char((m1 >> 8) & 0xff) << char(m1 & 0xff);
        cout << char((m2 >> 8) & 0xff) << char(m2 & 0xff);
        cout << char((m3 >> 8) & 0xff) << char(m3 & 0xff);
        cout << char((m4 >> 8) & 0xff) << char(m4 & 0xff) << '\n';
    }
    return 0;
}
```

## 实际判题程序的处理逻辑

邮件指出，在线判题程序实际使用的流程与题面图示存在两类差异，字符打包方式也与原始实现不同。通过的代码必须以邮件给出的实际流程为准。

第一，明文字符按小端顺序打包。对于一对字符 $m_{2i}$ 和 $m_{2i+1}$，分组值为：

$$
M_i=\operatorname{uint8}(m_{2i})+
\big(\operatorname{uint8}(m_{2i+1})\ll 8\big)
$$

恢复字符时，先输出 $M_i$ 的低 $8$ 位，再输出高 $8$ 位。因此，实际代码中的字符输出顺序与按高字节在前的原始实现相反。

第二，实际流程中的若干运算符与图示不同。顶层第三路和底层第三路均使用模 $2^{16}$ 加法；中间层中，$z_2$ 使用 $y_1+y_2$，而不是异或。循环移位量也不是题面图示中的密钥加和，而是取对应密钥异或结果的低 $4$ 位。

令密文分组为 $C_0,C_1,C_2,C_3$，密钥分组为 $K_0,K_1,K_2,K_3$。实际加密流程的底层逆变换为：

$$
\begin{aligned}
b_1 &= \operatorname{ror}(C_0,K_3\mathbin{\&}15) \\
b_2 &= C_1-K_2 \\
b_3 &= C_2-K_1 \\
b_4 &= \operatorname{ror}(C_3,K_0\mathbin{\&}15)
\end{aligned}
$$

在中间层，$b_1\oplus b_3$ 可以消去两路中相同的 $y_2$，$b_2\oplus b_4$ 可以消去两路中相同的 $z_2$：

$$
\begin{aligned}
x_1 &= b_1\oplus b_3 \\
x_2 &= b_2\oplus b_4 \\
y_1 &= \operatorname{rol}(x_1,(K_0\oplus K_1)\mathbin{\&}15) \\
y_2 &= \operatorname{rol}\big((y_1+x_2)\bmod 2^{16},(K_2\oplus K_3)\mathbin{\&}15\big) \\
z_2 &= (y_1+y_2)\bmod 2^{16}
\end{aligned}
$$

据此恢复顶层输入：

$$
\begin{aligned}
a_1 &= b_1\oplus y_2 \\
a_2 &= b_2\oplus z_2 \\
a_3 &= b_3\oplus y_2 \\
a_4 &= b_4\oplus z_2
\end{aligned}
$$

最后撤销实际流程中的顶层运算：

$$
\begin{aligned}
M_0 &= \operatorname{ror}(a_1,K_0\mathbin{\&}15) \\
M_1 &= a_2-K_1 \\
M_2 &= a_3-K_2 \\
M_3 &= \operatorname{ror}(a_4,K_3\mathbin{\&}15)
\end{aligned}
$$

所有减法均按模 $2^{16}$ 计算。通过这一逆向流程可以直接解密，不需要查表，单组数据的时间复杂度为 $O(1)$。

# 代码实现

实际提交时应使用以下代码。它按照实际判题程序的加密规则解密，并使用小端顺序输出字符。

```cpp
#include <bits/stdc++.h>
using namespace std;

uint32_t leftRotate(uint32_t value, uint32_t shift) {
    value &= 0xffff;
    shift &= 15;
    if (shift == 0) return value;
    return ((value << shift) | (value >> (16 - shift))) & 0xffff;
}

uint32_t rightRotate(uint32_t value, uint32_t shift) {
    value &= 0xffff;
    shift &= 15;
    if (shift == 0) return value;
    return ((value >> shift) | (value << (16 - shift))) & 0xffff;
}

uint32_t parseWord(const string &value, int position) {
    return stoul(value.substr(position, 4), nullptr, 16);
}

string decrypt(const string &cipher, const string &key) {
    uint32_t c1 = parseWord(cipher, 0), c2 = parseWord(cipher, 4), c3 = parseWord(cipher, 8), c4 = parseWord(cipher, 12);
    uint32_t k1 = parseWord(key, 0), k2 = parseWord(key, 4), k3 = parseWord(key, 8), k4 = parseWord(key, 12);
    uint32_t b1 = rightRotate(c1, k4), b2 = (c2 + 65536 - k3) & 0xffff, b3 = (c3 + 65536 - k2) & 0xffff, b4 = rightRotate(c4, k1);
    uint32_t x1 = b1 ^ b3, x2 = b2 ^ b4;
    uint32_t y1 = leftRotate(x1, k1 ^ k2), y2 = leftRotate((y1 + x2) & 0xffff, k3 ^ k4);
    uint32_t z2 = (y1 + y2) & 0xffff;
    uint32_t a1 = b1 ^ y2, a2 = b2 ^ z2, a3 = b3 ^ y2, a4 = b4 ^ z2;
    uint32_t m1 = rightRotate(a1, k1), m2 = (a2 + 65536 - k2) & 0xffff, m3 = (a3 + 65536 - k3) & 0xffff, m4 = rightRotate(a4, k4);
    string message;
    message += char(m1 & 0xff);
    message += char((m1 >> 8) & 0xff);
    message += char(m2 & 0xff);
    message += char((m2 >> 8) & 0xff);
    message += char(m3 & 0xff);
    message += char((m3 >> 8) & 0xff);
    message += char(m4 & 0xff);
    message += char((m4 >> 8) & 0xff);
    return message;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string cipher, key;
    while (cin >> cipher >> key)
        cout << decrypt(cipher, key) << '\n';
    return 0;
}
```

每组数据只需解析固定长度的密文和密钥，并执行固定数量的 $16$ 位运算，因此时间复杂度为 $O(1)$。除输入字符串和输出字符串外，只使用固定数量的变量，空间复杂度为 $O(1)$。

# 总结

本题的关键是先确定实际加密流程，再对每一层按相反顺序逆向恢复。异或组合可以利用相同项抵消，循环左移通过循环右移撤销，加法通过模 $2^{16}$ 减法撤销。实际通过代码与题面图示版本的主要差异是若干加法与异或运算、移位量定义，以及明文分组采用小端字符打包；这些差异必须同时处理。
