[UVa 166 Making Change](https://blog.csdn.net/metaphysis/article/details/158808052)

## 题目分析

这是一个经典的找零钱问题，但与普通的找零问题不同，这里涉及到**交易双方**的硬币交换。我们需要计算在购买商品时，支付和找零过程中**易手的硬币总数**的最小值。

### 问题描述

我们有新西兰的硬币体系：$5c$, $10c$, $20c$, $50c$, $\$1$, $\$2$（即 $100c$, $200c$）。顾客手中有一定数量的这些硬币（输入给出），而商家拥有无限量的所有面值的硬币。我们需要支付一定金额（总是 $5c$ 的倍数），目标是让整个交易过程中**易手的硬币总数**（顾客支付给商家的硬币数 $+$ 商家找零给顾客的硬币数）最小。

### 关键点分析

1. **交易过程**：顾客支付一定金额 $\rightarrow$ 商家找零（如果需要）
2. **易手硬币** = 顾客给出的硬币数 $+$ 商家给出的找零硬币数
3. **顾客**：硬币数量有限
4. **商家**：硬币无限，总能给出找零
5. **支付金额**：顾客可以支付**多于**商品价格的金额，以获得更优的找零组合

## 解题思路

### 1. 问题转化

由于所有面值都是 $5c$ 的倍数，我们可以将所有金额除以 $5$ 进行处理，这样面值变为：
- $5c \rightarrow 1$ 单位
- $10c \rightarrow 2$ 单位
- $20c \rightarrow 4$ 单位
- $50c \rightarrow 10$ 单位
- $$1 \rightarrow 20$ 单位
- $$2 \rightarrow 40$ 单位

这样做的好处是避免浮点数运算，提高精度和效率。

### 2. 核心思想

设：
- $P$ = 商品价格（以 $5c$ 为单位）
- $pay$ = 顾客实际支付的金额
- $change = pay - P$ = 商家需要找零的金额

则：
- 易手硬币数 = 顾客支付 $pay$ 所使用的硬币数 $+$ 商家找零 $change$ 所使用的硬币数

我们需要找到最优的 $pay$ 值，使得这个总数最小。

### 3. 支付金额的范围

顾客最多能支付的总金额 = 顾客拥有的所有硬币面值之和。因此，$pay$ 的取值范围是：
$$P \leq pay \leq totalMoney$$

### 4. 两个子问题

#### (1) 顾客支付问题
给定金额 $pay$，在顾客硬币数量有限的情况下，能否正好支付 $pay$？如果可以，最少需要多少枚硬币？

这是一个**有限硬币的找零问题**，我们可以用贪心策略，但由于硬币面值不是标准的倍数关系，贪心不一定得到最优解。不过在这个问题中，由于面值设计（$1,2,4,10,20,40$ 的组合），贪心策略是可行的（这些面值满足**规范货币系统**的性质）。代码中使用从大到小的贪心策略。

#### (2) 商家找零问题
给定金额 $change$，商家有无限硬币，找零所需的最少硬币数。

这是一个**无限硬币的找零问题**，直接用贪心策略即可（从大到小选择面值）。

### 5. 算法步骤

1. 将输入的面值和金额全部除以 $5$ 转换为整数
2. 计算顾客拥有的总金额 $totalMoney$
3. 枚举 $pay$ 从 $P$ 到 $totalMoney$
4. 对于每个 $pay$：
   - 计算 $change = pay - P$
   - 计算顾客支付 $pay$ 所需硬币数 $buyerCoins$（如果无法支付，跳过）
   - 计算商家找零 $change$ 所需硬币数 $sellerCoins$
   - 更新最小值 $minCoins = min(minCoins, buyerCoins + sellerCoins)$
5. 输出最小值（宽度为 $3$，右对齐）

### 6. 时间复杂度

- 最多枚举金额：总金额不超过 $\$5$，即 $500c$，除以 $5$ 后为 $100$ 单位
- 顾客最多 $6$ 种硬币，每种数量未知但有限
- 枚举范围：$O(totalMoney)$，在本题中非常可行

## 代码实现

```cpp
// Making Change
// UVa ID: 166
// Verdict: Accepted
// Submission Date: 2016-03-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 面值除以 5 转换后便于处理。
int denominations[6] = { 1, 2, 4, 10, 20, 40 };
int coins[6], usedCoins[6];
const int MAX_INT = numeric_limits < int >::max();
const int MIN_INT = numeric_limits < int >::min();

// 卖家找零钱，由于有足够的硬币数量，总是可以给出找零方案。
int findSellerChange(int money) {
    int count = 0;
    while (money > 0) {
        for (int i = 5; i >= 0; i--)
            if (denominations[i] <= money) {
                count++;
                money -= denominations[i];
            }
    }
    return count;
}

// 买家找零钱，由于硬币数量有限制，可能无法找零钱。
int findBuyerChange(int money) {
    int count = 0;
    fill(usedCoins, usedCoins + 6, 0);
    while (true) {
        bool found = false;
        for (int i = 5; i >= 0; i--)
            if (denominations[i] <= money && usedCoins[i] < coins[i]) {
                money -= denominations[i];
                usedCoins[i]++;
                found = true;
                count++;
                break;
            }
        if (money == 0) return count;
        if (found == false && money > 0) return MIN_INT;
    }
}

void findMinimalCoins(int money) {
    int moneyOfTotal = 0;
    for (int i = 0; i < 6; i++) moneyOfTotal += coins[i] * denominations[i];

    // 搜索所有可能的找零方案，寻找最小易手硬币数量。
    int minCoins = MAX_INT;
    for (int i = 0; i <= moneyOfTotal; i++) {
        int coinsOfBuyer = findBuyerChange(money + i);
        if (coinsOfBuyer == MIN_INT) continue;
        minCoins = min(minCoins, (coinsOfBuyer + findSellerChange(i)));
    }
    cout << setw(3) << right << minCoins << endl;
}

int main() {
    while (true) {
        // 读入顾客的硬币数量。
        int zero = 0;
        for (int i = 0; i < 6; i++) {
            cin >> coins[i];
            zero += coins[i] == 0;
        }
        if (zero == 6) break;
        // 将钱的数量转换成整数便于处理。
        double money;
        cin >> money;
        findMinimalCoins((int)(money * 100.0 + 0.5) / 5);
    }
    return 0;
}
```

## 总结

本题的关键在于理解“易手硬币”的概念，并将问题分解为顾客支付和商家找零两个子问题。通过枚举所有可能的支付金额，我们可以找到全局最优解。

需要注意的细节：
- 金额转换时避免浮点数误差
- 处理顾客无法支付的情况
- 输出格式要求（宽度 $3$，右对齐）

这道题很好地考察了贪心算法和枚举思想的结合应用。
