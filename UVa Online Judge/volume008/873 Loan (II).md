
> **摘要**：本文讲解等额本息还款问题的求解方法。给定本金 $P$、年利率 $R$ 与期限 $N$，通过递推关系推导出每月固定还款额公式 $A = P \cdot \dfrac{r(1+r)^N}{(1+r)^N - 1}$（$r$ 为月利率），并处理零利率边界情况 $A = P/N$。文中给出完整公式推导、解题步骤与 C++ 实现，输出保留两位小数、用例间空行。

## 题目描述

银行提供贷款服务，客户需在约定期限内偿还本金并支付利息。给定初始本金 $P$（欧元）、年利率 $R$（百分比）和贷款期限 $N$（月数），采用**等额本息**还款方式，即每月偿还固定金额 $A$，其中一部分用于支付当月利息，剩余部分用于偿还本金。要求计算 $A$ 的值，使得第 $N$ 个月还款后，本金恰好归零，且所有利息均已结清。

## 输入格式

第一行包含一个正整数 $T$，表示测试用例的数量。  
之后每个测试用例占一行，包含三个整数，依次为：  
- 初始本金 $P$（欧元）  
- 年利率 $R$（百分比，即 $6$ 表示 $6\%$）  
- 期限 $N$（月）  

输入中可能包含空行，但会被标准输入自动忽略。

## 输出格式

对于每个测试用例，输出一行，包含一个保留两位小数的浮点数，即每月应还款额（欧元）。两个连续用例的输出之间用一个空行隔开。

## 样例

输入

```
1

5000 6 36
```

输出

```
152.11
```

## 题目分析

等额本息还款的核心是：每月还款额固定，且月利率 $r$ 为年利率除以 $12$。若月利率非零，则第 $k$ 个月还款后剩余本金 $P_k$ 满足递推关系：

$$
P_k = P_{k-1} \cdot (1 + r) - A
$$

其中 $P_0 = P$，$P_N = 0$。解此递推式可得通项公式：

$$
P_N = P(1+r)^N - A \cdot \frac{(1+r)^N - 1}{r}
$$

令 $P_N = 0$，解得：

$$
A = P \cdot \frac{r(1+r)^N}{(1+r)^N - 1}
$$

该公式在 $r = 0$ 时无意义，此时月利率为零，每月只需平均偿还本金，即 $A = \dfrac{P}{N}$。

本题数据范围未明确给出，但计算仅涉及浮点运算，需注意精度。最终结果需四舍五入到“分”，即保留两位小数，使用 `printf("%.2f")` 即可满足。

## 解题思路

1. **读入测试用例数** $T$，然后对每个用例循环处理。  
2. **计算月利率**：$r = \dfrac{R / 100}{12}$。注意年利率是百分比，需先除以 $100$ 转换为小数。  
3. **判断零利率**：若 $|r| < 10^{-12}$（浮点数比较），则每月还款额为 $P / N$。  
4. **非零利率**：计算因子 $\textit{factor} = (1 + r)^N$，代入公式得到：

   $$
   A = P \cdot \frac{r \cdot \textit{factor}}{\textit{factor} - 1}
   $$

5. **输出**：使用 `printf` 控制小数点后两位，并在用例之间（除第一个外）先输出一个换行，以符合输出格式。

## 代码实现

```cpp
// Loan (II)
// UVa ID: 873
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int capital, ratePercent, months;
        cin >> capital >> ratePercent >> months;
        
        double monthlyRate = ratePercent / 100.0 / 12.0;
        double payment;
        
        if (fabs(monthlyRate) < 1e-12) {
            payment = static_cast<double>(capital) / months;
        } else {
            double factor = pow(1.0 + monthlyRate, months);
            payment = capital * monthlyRate * factor / (factor - 1.0);
        }
        
        if (caseNo > 1) cout << "\n";
        printf("%.2f\n", payment);
    }
    return 0;
}
```

## 总结

本题是等额本息还款公式的直接应用，关键在于正确理解月利率与年利率的转换，并处理零利率边界情况。浮点数计算时注意精度，使用 `pow` 函数计算幂。输出格式要求用例间空行，通过判断 `caseNo > 1` 控制即可。  
此类问题在金融计算中常见，掌握公式推导有助于快速求解。
