[UVa 119 Greedy Gift Givers](https://blog.csdn.net/metaphysis/article/details/156644609)

## 题目描述

本题要求模拟一群朋友之间的礼物赠送情况，计算每个人最终的净收入（或净支出）。每个人会准备一定金额用于送礼，并将这笔钱平均分给他要送礼的所有人（只取整数部分，余数自己保留）。我们需要计算每个人最终收到的总金额减去送出的总金额，即其净收益（或净损失）。

输入包含多组数据，每组数据包含：

1.  人数 $n$（不超过 $10$ 人）。
2.  $n$ 个人的姓名（小写字母，长度不超过 $12$）。
3.  接下来的 $n$ 行，每行表示一个人的送礼信息：送礼者姓名、准备的金额、送礼人数、接收者姓名列表。

输出对于每组数据，按照输入顺序输出每个人的姓名及其净收益（正数为收入多于支出，负数为支出多于收入）。组与组之间用空行隔开。

## 输入输出样例

**输入示例**  
```
5
dave laura oven vick amr
dave 200 3 laura oven vick
oven 500 1 dave
amr 150 2 vick oven
laura 0 2 amr vick
vick 0 0
3
liz steve dave
liz 30 1 steve
steve 55 2 liz dave
dave 0 2 steve liz
```

**输出示例**  
```
dave 302
laura 66
oven -359
vick 141
amr -150

liz -3
steve -24
dave 27
```

## 题目分析

这是一个模拟类问题，主要考察对题目描述的理解和细节处理能力。关键在于正确模拟“平均分配礼物金额并保留余数”的过程。

### 核心规则

1.  **平均分配**：若送礼者准备了 $moneyGive$ 元，要送给 $nReceivers$ 个人，则每人得到 $\lfloor \frac{moneyGive}{nReceivers} \rfloor$ 元（整数除法）。送礼者自己保留余数 $moneyGive \mod nReceivers$。
2.  **净收益计算**：对于每个人，净收益 $=$ 收到的总金额 $-$ 送出的总金额。
3.  **输出顺序**：必须按照输入中名字首次出现的顺序输出。
4.  **组间空行**：除最后一组外，每组输出后跟一个空行。

### 解题思路

我们可以使用一个映射（`map`）来记录每个人的净收益，并额外用一个数组保存初始输入顺序。

1.  **读取人数 $n$**。
2.  **记录姓名顺序**：用一个数组 `name[]` 顺序存储姓名，并用 `map<string, int>` 初始化每个人的净收益为 $0$。
3.  **模拟送礼过程**：
    *   对于每个送礼者，读取其姓名、准备金额 $moneyGive$ 和接收人数 $nReceivers$。
    *   若 $nReceivers > 0$，计算每人分得金额 $amount = moneyGive / nReceivers$（整数除法）。
    *   更新接收者的净收益：`money[receiver] += amount`。
    *   更新送礼者的净收益：`money[giver] -= amount * nReceivers`（即减去送出的总金额）。
    *   注意：送礼者保留的余数 $moneyGive \mod nReceivers$ 不需要处理，因为这部分既没有送出也没有收到，不影响净收益。
4.  **按顺序输出结果**。
5.  **处理多组数据**：组间输出空行，注意最后一组后不输出多余空行。

### 细节处理

-   当 $nReceivers = 0$ 时，送礼者不送出任何钱，也不应更新其净收益（代码中通过条件判断避免除零或无效计算）。
-   使用 `map` 可以快速通过姓名查找并更新净收益。
-   输出时空行控制：可以使用一个标志变量 `printBlankLine`，从第二组开始输出前先打印空行。

## 代码实现

```cpp
// Greedy Gift Givers
// UVa ID: 119
// Verdict: Accepted
// Submission Date: 2011-11-26
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 简单的模拟题。

#include <bits/stdc++.h>
using namespace std;
#define MAXN 15
map< string, int> money;
string name[MAXN];
int main (int argc, char const* argv[]) {
    int n, moneyGive, nReceivers;
    string giver, receiver;
    bool printBlankLine = false;
    while (cin >> n) {
        if (printBlankLine) cout << endl;
        else printBlankLine = true;
        money.clear();
        for (int i = 0; i < n; i++) {
            cin >> name[i];
            money[name[i]] = 0;
        }
        for (int i = 1; i <= n; i++) {
            cin >> giver >> moneyGive >> nReceivers;
            for (int j = 1; j <= nReceivers; j++) {
                cin >> receiver;
                money[receiver] += (moneyGive / nReceivers);
            }
            if (nReceivers) money[giver] -= (moneyGive / nReceivers * nReceivers);
        }
        for (int i = 0; i < n; i++) cout << name[i] << " " << money[name[i]] << endl;
    }
    return 0;
}
```

## 复杂度分析

- **时间复杂度**：对于每组数据，处理 $n$ 个人的送礼信息，每次更新接收者收益为 $O(1)$（`map` 操作），总时间复杂度 $O(n \cdot m)$，其中 $m$ 为平均送礼人数。由于 $n \leq 10$，该算法非常高效。
- **空间复杂度**：$O(n)$ 用于存储姓名和净收益映射。

## 总结

本题是一个典型的模拟题，重点在于理解题目描述的分配规则和输出要求。通过使用 `map` 维护每个人的净收益，并用数组记录初始顺序，可以简洁地实现题目要求。注意处理边界情况（如送礼人数为 $0$）和输出格式（组间空行）即可。
