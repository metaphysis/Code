[UVa 182 Bonus Bonds](https://blog.csdn.net/metaphysis/article/details/160890553)

## 题目分析

$\texttt{Impecunia}$ 政府通过发行 $\texttt{Bonus Bonds}$ 来筹集资金。债券编号原本是 $7$ 位数字，前面加上 $1$ 位区域代码（$1$ – $9$），后来扩展为 $10$ 位数字，其中从左向右第 $3$ 位（即从右向左第 $8$ 位）表示区域代码。中央区域的代码为 $0$，并且中央区域的编号从 $0000000001$ 开始（不能全为 $0$）。

每月每个区域独立抽奖。抽奖设备会生成 $10$ 个数字流，每个流对应一个数位。第 $1$ 个中奖号码由每个流的第 $1$ 位数字组成，第 $2$ 个中奖号码由每个流的第 $2$ 位数字组成，依此类推。设备需要调整每个流的数字分布，使其与实际已售债券在该数位上的数字分布一致。

题目要求：对于每个输入行（包含下一个待售债券的 $10$ 位编号，以及一个目标数位位置 $p$，$1 \le p \le 10$），输出一个 $10$ 行的表格，第 $i$ 行（$i = 0,1,\dots,9$）表示在该数位位置上数字 $i$ 出现的总次数。

## 解题思路

核心问题：已知从起始编号到 $N-1$ 号的所有有效债券（$N$ 为下一个待售编号），统计这些编号在指定数位（$1$ 索引，从左向右）上各数字出现的次数。

### 关键处理

1. **编号的结构**：输入是 $10$ 位数字，但第 $3$ 位是区域代码，需要将其移除才能得到真正的编号范围。例如输入 `4810000000`，第 $3$ 位是 `1`，真正的编号是 `481000000`（$9$ 位）。

2. **起始编号**：
   - 对于非中央区域（区域代码 $1$ – $9$），编号从 $0$ 开始（因为原方案中区域代码非零，编号可以从 $0$ 开始）。
   - 对于中央区域（区域代码 $0$），编号从 $0000000001$ 开始，即 $1$。

3. **计数方法**：采用数位统计的方法。对于目标数位 $p$：
   - 如果 $p = 3$（即区域代码位），该位在所有有效编号中都是固定的区域代码值，因此该数字出现次数就是有效编号的总数，其他数字出现 $0$ 次。
   - 如果 $p \neq 3$，则需要计算在该数位上每个数字出现的次数。
   
   对于非区域代码位，将其在原 $9$ 位编号中的索引 $idx$ 计算如下：
   - 若 $p < 3$，则 $idx = p – 1$
   - 若 $p > 3$，则 $idx = p – 2$
   
   然后利用数位统计公式计算每个数字 $i$（$0$ – $9$）在 $[0, N-1]$ 范围内第 $idx$ 位上出现的次数。

4. **排除无效编号**：中央区域的有效编号从 $1$ 开始，因此需要减去数字 $0$ 多算的一次（当 $i = 0$ 且区域代码为 $0$ 时，总数减 $1$）。

### 算法复杂度

对于每个输入，只需 $O(10 \times \text{位数})$ 的时间，非常高效。

## 代码实现

```cpp
// Bonus Bonds
// UVa ID: 182
// Verdict: Accepted
// Submission Date: 2017-07-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string nextBondNumber, desiredPosition;

void countTimes() {
    // 获取区域代码（第3位）和目标数位位置
    int region = nextBondNumber[2] - '0', position = stoi(desiredPosition);
    // 移除区域代码位，得到9位有效编号字符串
    nextBondNumber.erase(nextBondNumber.begin() + 2);
    long long number = stoll(nextBondNumber);

    // 特殊情况：没有有效债券
    if (number == 0 || (number == 1 && region == 0)) {
        for (int i = 1; i <= 10; i++) 
            cout << right << setw(11) << 0 << endl;
        return;
    }

    // 将 N-1 转换为数字向量，便于逐位处理
    vector<int> bn;
    for (auto c : to_string(number - 1)) 
        bn.push_back(c - '0');
    while (bn.size() < nextBondNumber.length()) 
        bn.insert(bn.begin(), 0);

    // 统计 0-9 每个数字在目标数位上出现的次数
    for (int i = 0; i <= 9; i++)
    {
        long long total = 0;

        // 情况1：目标数位是区域代码位（第3位）
        if (position == 3)
        {
            if (i == region) 
                total = number;
        }
        else
        {
            // 计算在9位编号中的索引位置
            int idx = position > 3 ? position - 2 : position - 1;

            if (idx > 0)
            {
                // 高位部分贡献
                for (int j = 0; j < idx; j++) 
                    total += bn[j] * pow(10, 7 - j);
            }
            // 当前位小于 bn[idx] 时，低位全排列
            if (i < bn[idx]) 
                total += pow(10, bn.size() - idx - 1);
            // 当前位等于 bn[idx] 时，低位取 tail+1
            if (i == bn[idx])
            {
                long long tail = 0;
                for (int j = idx + 1; j < bn.size(); j++) 
                    tail = tail * 10 + bn[j];
                total += tail;
                total += 1;
            }
        }
        
        // 中央区域需要排除全0编号
        if (i == 0 && region == 0) 
            total -= 1;

        cout << right << setw(11) << total << '\n';
    }
}

int main() {
    int cases = 0;
    while (cin >> nextBondNumber >> desiredPosition) {
        if (desiredPosition == "0") break;
        if (cases++) cout << '\n';
        countTimes();
    }
    return 0;
}
```

## 总结

本题的核心在于理解债券编号的特殊结构（区域代码嵌入在数位中）以及数位统计的技巧。通过将问题分解为 $10$ 个独立的数位统计子问题，利用数学公式 $O(1)$ 计算每个数字的出现次数，避免了枚举所有编号的低效做法。中央区域需要特殊处理起始编号为 $1$ 而非 $0$ 这一细节。
