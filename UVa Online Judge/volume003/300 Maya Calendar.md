[UVa 300 Maya Calendar](https://blog.csdn.net/metaphysis/article/details/161440218)

## 题目描述

玛雅文明使用了两种历法：**哈布历**（$\texttt{Haab}$）和**卓尔金历**（$\texttt{Tzolkin}$）。教授 $\texttt{M. A. Ya}$ 需要编写一个程序，将给定的哈布历日期转换为对应的卓尔金历日期。

### 哈布历（$\texttt{Haab}$）

- 一年有 $365$ 天，分为 $19$ 个月
- 前 $18$ 个月每月 $20$ 天，月份名称依次为：
  $\texttt{pop, no, zip, zotz, tzec, xul, yoxkin, mol, chen, yax, zac, ceh, mac, kankin, muan, pax, koyab, cumhu}$
- 第 $19$ 个月名为 $\texttt{uayet}$，只有 $5$ 天
- 每天用 **月份名称 + 数字** 表示，数字从 $0$ 开始编号

### 卓尔金历（$\texttt{Tzolkin}$）

- 一年有 $260$ 天，由 $13$ 个数字和 $20$ 个名称组合而成
- $20$ 个名称依次为：
  $\texttt{imix, ik, akbal, kan, chicchan, cimi, manik, lamat, muluk, ok, chuen, eb, ben, ix, mem, cib, caban, eznab, canac, ahau}$
- 数字从 $1$ 到 $13$ 循环，名称从上述列表循环
- 每天用 **数字 + 名称** 表示

### 输入格式

- 第一行：整数 $n$，表示需要转换的日期数量
- 接下来 $n$ 行：每行一个哈布历日期，格式为 `NumberOfTheDay. Month Year`
  - 其中 `NumberOfTheDay` 是一个整数（带小数点）
  - `Month` 是月份名称
  - `Year` 是年份（$< 5000$）

### 输出格式

- 第一行：输出 $n$
- 接下来 $n$ 行：每行一个卓尔金历日期，格式为 `Number NameOfTheDay Year`

### 样例

**输入**

```
3
10. zac 0
0. pop 0
10. zac 1995
```

**输出**

```
3
3 chuen 0
1 imix 0
9 cimi 2801
```

---

## 题目分析

### 问题的本质

这是一个**历法转换**问题。两种历法都使用整数天作为“绝对时间”的度量单位，因此核心思路是：

1. 将哈布历日期转换为自“世界开端”以来的绝对天数
2. 再将绝对天数转换为卓尔金历日期

两种历法的区别在于：
- 哈布历：每年固定 $365$ 天
- 卓尔金历：每年固定 $260$ 天

这意味着，只要知道从第 $0$ 年开始经过的总天数，就可以在两种历法之间任意转换。

### 哈布历 → 绝对天数

哈布历的日期格式为：`d. month y`，其中：
- $d$ 是月份中的第几天（$0 \sim 19$，$\texttt{uayet}$ 月为 $0 \sim 4$）
- $\texttt{month}$ 是月份名称
- $y$ 是年份（从 $0$ 开始）

绝对天数的计算公式为：

$$
days = y \times 365 + m \times 20 + (d + 1)
$$

其中：
- $y \times 365$：之前整年的天数
- $m \times 20$：之前整月的天数（$m$ 为月份索引，$0 \sim 18$）
- $d + 1$：当月过去的天数（因为哈布历天数从 $0$ 开始计数，所以需要 $+1$ 转换为从 $1$ 开始的天数）

> **注意**：$\texttt{uayet}$ 月只有 $5$ 天，但每月 $20$ 天的通用公式同样适用，因为在该月内 $d$ 只能取 $0 \sim 4$，不会超出范围。

### 绝对天数 → 卓尔金历

卓尔金历的周期为 $260$ 天（$13$ 个数字 × $20$ 个名称）。给定绝对天数 $\texttt{days}$，可以计算：

1. **年份**（$\texttt{year}$）：  
   由于每年的第一天对应绝对天数从 $1$ 到 $260$ 为第 $0$ 年，因此：
   $$
 year = \left\lfloor \frac{days - 1}{260} \right\rfloor
   $$
   更简洁的处理方式是：先计算 $\text{days} / 260$ 的商，再处理边界情况。

2. **数字**（$\texttt{number}$）：  
   数字从 $1$ 到 $13$ 循环，因此：
   $$
  number = (days - 1) \bmod 13 + 1
   $$

3. **名称索引**（$\texttt{name}$）：  
   名称从 $0$ 到 $19$ 循环，因此：
   $$
name\_index = (days - 1) \bmod 20
   $$

### 边界情况处理

由于绝对天数 $days$ 在计算中可能恰好是 $260$ 的整数倍，此时：
- $days / 260$ 的商比实际年份大 $1$
- 需要特殊处理：如果 $days \% 260 == 0$，则年份应减 $1$，并将 $days$ 重置为 $260$ 以便正确计算数字和名称

---

## 解题思路

### 步骤一：存储月份名称

使用两个数组分别存储哈布历的 $19$ 个月份名称和卓尔金历的 $20$ 个名称：

- `monthsOfHaab`：按顺序存放 $19$ 个月份名称
- `monthsOfTzolkin`：按顺序存放 $20$ 个名称

> **注意**：卓尔金历的名称列表在代码中从 `ahau` 开始，这是为了与原始问题的循环对应。实际计算中，只需要保证索引对应正确即可。

### 步骤二：读取输入

首先读取 $n$，输出 $n$（按题目要求第一行输出转换的日期数量）。

然后循环读取 $n$ 行，每行格式为 `d. month y`：
- `numberOfTheDay`：带小数点的数字，如 `10.`
- `month`：月份名称
- `year`：年份

### 步骤三：计算绝对天数

```cpp
int days = stoi(year) * 365;
days += (find(monthsOfHaab.begin(), monthsOfHaab.end(), month) - monthsOfHaab.begin()) * 20;
days += stoi(numberOfTheDay.substr(0, numberOfTheDay.length() - 1)) + 1;
```

- 第一行：整年天数
- 第二行：整月天数（月份索引 × $20$）
- 第三行：当月天数（去掉小数点后的数字 + $1$）

### 步骤四：转换为卓尔金历

```cpp
int yearValue = days / 260;
if (days % 260 == 0) {
    yearValue = (days - 260) / 260;
    days = 260;
}
int monthValue = days % 20;
int numberOfTheDayValue = days % 13;
if (numberOfTheDayValue == 0) numberOfTheDayValue = 13;
```

- `yearValue`：年份
- `monthValue`：名称索引（$0 \sim 19$）
- `numberOfTheDayValue`：数字（$1 \sim 13$）

### 步骤五：输出结果

按格式输出：`数字 名称 年份`

---

## 算法复杂度分析

### 时间复杂度

- 每次日期转换：$O(1)$ 查找月份索引（使用线性查找，$19$ 个元素可视为常数）
- 总时间复杂度：$O(n)$，其中 $n$ 为转换的日期数量

### 空间复杂度

- 存储月份名称数组：$O(1)$
- 总空间复杂度：$O(1)$

---

## 正确性证明

**引理 1**：哈布历日期与绝对天数之间是一一对应的。

证明：哈布历的每个日期（年、月、日）唯一确定一个整数天数。反过来，给定绝对天数，可以通过除以 $365$ 得到年份，再通过除以 $20$ 得到月份和日期。$\square$

**引理 2**：卓尔金历日期与绝对天数之间是一一对应的。

证明：卓尔金历的周期为 $260$ 天，数字和名称分别独立循环。给定绝对天数 $d$，年份为 $\lfloor (d-1)/260 \rfloor$，数字为 $(d-1) \bmod 13 + 1$，名称为 $\texttt{name}[(d-1) \bmod 20]$。$\square$

由引理 1 和引理 2，通过绝对天数作为中介，哈布历和卓尔金历之间的转换是唯一且正确的。

---

## 参考代码

```cpp
// Maya Calendar
// UVa ID: 300
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    // 哈布历的19个月份名称，按顺序排列
    vector<string> monthsOfHaab = {
        "pop", "no", "zip", "zotz", "tzec",
        "xul", "yoxkin", "mol", "chen", "yax",
        "zac", "ceh", "mac", "kankin", "muan",
        "pax", "koyab", "cumhu", "uayet"
    };
    
    // 卓尔金历的20个名称，按顺序排列
    vector<string> monthsOfTzolkin = {
        "ahau", "imix", "ik", "akbal", "kan", "chicchan",
        "cimi", "manik", "lamat", "muluk", "ok",
        "chuen", "eb", "ben", "ix", "mem",
        "cib", "caban", "eznab", "canac"
    };
    
    string numberOfTheDay, month, year;
    
    int n;
    cin >> n;               // 读取待转换的日期数量
    
    cout << n << endl;      // 输出数量
    
    // 循环处理每个日期
    while (cin >> numberOfTheDay >> month >> year)
    {
        // 1. 计算绝对天数
        //    - 整年天数
        int days = stoi(year) * 365;
        //    - 整月天数：找到月份索引，乘以20
        days += (find(monthsOfHaab.begin(), monthsOfHaab.end(), month) - monthsOfHaab.begin()) * 20;
        //    - 当月天数：去掉小数点，加1（因为哈布历从0开始计数）
        days += stoi(numberOfTheDay.substr(0, numberOfTheDay.length() - 1)) + 1;
        
        // 2. 将绝对天数转换为卓尔金历
        //    计算年份：每260天为一年
        int yearValue = days / 260;
        //    边界处理：如果正好是260的整数倍，则年份减1，天数重置为260
        if (days % 260 == 0)
        {
            yearValue = (days - 260) / 260;
            days = 260;
        }
        //    名称索引：天数对20取模
        int monthValue = days % 20;
        //    数字值：天数对13取模，结果为0时变为13
        int numberOfTheDayValue = days % 13;
        if (numberOfTheDayValue == 0) numberOfTheDayValue = 13;
        
        // 3. 输出结果：数字 名称 年份
        cout << numberOfTheDayValue << " " << monthsOfTzolkin[monthValue] << " " << yearValue << endl;
    }
    
	return 0;
}
```

---

## 总结

本题的核心在于理解**绝对天数**作为历法转换的中介。两种历法虽然结构不同，但都可以用整数天数唯一表示。

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 哈布历 → 天数 | $y \times 365 + m \times 20 + (d+1)$ |
| 天数 → 卓尔金历 | 年份：$\lfloor days/260 \rfloor$，数字：$(days-1) \bmod 13 + 1$，名称：$(days-1) \bmod 20$ |
| 边界处理 | $days$ 为 $260$ 的整数倍时需特殊处理 |
| 月份索引 | 使用线性查找（$19$ 个元素，常数时间） |

本题的解法可以直接扩展到任意两种线性周期日历之间的转换。
