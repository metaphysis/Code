[UVa 343 What Base Is This](https://blog.csdn.net/metaphysis/article/details/161557143)

## 题目描述

在位置记数法中，数字的位置表示该数字在数值中的权重。例如，在十进制数 $362$ 中，$2$ 的权重为 $10^0$，$6$ 的权重为 $10^1$，$3$ 的权重为 $10^2$，因此数值为 $3 \times 10^2 + 6 \times 10^1 + 2 \times 10^0 = 362$。同样的机制也适用于其他进制。虽然大多数人认为他们每天遇到的数字都是用十进制表示的，但其他进制也是可能的。特别地，九进制或十四进制下的 $362$ 与十进制下的 $362$ 代表完全不同的数值。

对于本题，程序将处理一系列整数对。设整数对的两个成员为 $X$ 和 $Y$。程序需要确定 $X$ 的最小可能进制和 $Y$ 的最小可能进制（通常与 $X$ 的不同），使得 $X$ 和 $Y$ 代表相同的数值。

例如，考虑整数 $12$ 和 $5$。如果两者都用十进制，它们显然不相等。但假设 $12$ 是三进制数，$5$ 是六进制数：三进制的 $12$ 等于 $1 \times 3^1 + 2 \times 3^0 = 5$（十进制），而任何进制下的 $5$ 都等于 $5$（十进制）。因此，$12$ 和 $5$ 可以相等，只要为它们选择正确的进制！

### 输入格式

输入数据的每一行包含一对整数 $X$ 和 $Y$，由一个或多个空格分隔；每行前后也可能有空格，应被忽略。$X$ 和 $Y$ 的进制范围是 $1$ 到 $36$（含），且不需要相同。在表示这些数字时，数字 $0 \sim 9$ 具有通常的十进制含义。大写字母 $A \sim Z$ 分别表示数字 $10 \sim 35$。

### 输出格式

对于输入中的每一对整数，输出类似示例所示的消息。如果无论如何选择进制（每个数的进制在 $2$ 到 $36$ 之间），两个数都无法相等，则输出相应的消息。

### 样例输入

```
12 5
10 A
12 34
123 456
1 2
10 2
```

### 样例输出

```
12 base 3 = 5 base 6
10 base 10 = A base 11
12 base 17 = 34 base 5
123 is not equal to 456 in any base 2..36
1 is not equal to 2 in any base 2..36
10 base 2 = 2 base 3
```

---

## 题目分析

### 问题的本质

这是一个**进制转换与数值比较**问题。给定两个字符串（可能包含数字和字母 $A \sim Z$），需要找出进制 $b_X$ 和 $b_Y$（$2 \leq b_X, b_Y \leq 36$），使得 $X$ 在 $b_X$ 进制下的数值等于 $Y$ 在 $b_Y$ 进制下的数值。

### 进制范围

- 最小进制：由字符串中的最大数字决定。例如，如果字符串包含数字 $9$，则最小进制至少为 $10$；如果包含字母 $A$，则最小进制至少为 $11$。
- 最大进制：$36$（因为字母最大为 $Z$，代表 $35$）

### 特殊考虑

- 当字符串为单个数字（如 `1`、`2`）时，它在任何进制下的值都相同，但最小进制为 $2$（因为进制 $1$ 无效）
- 注意：题目描述中提到进制范围为 $1$ 到 $36$，但根据常识，进制至少为 $2$（单数字 `0` 或 `1` 在进制 $1$ 下也有定义，但通常不考虑）。示例中输出为 `base 2..36`，说明只考虑 $2$ 到 $36$。

### 算法思路

枚举 $X$ 的所有可能进制（从最小进制到 $36$），计算其十进制值，存于集合中。同样枚举 $Y$ 的所有可能进制，计算其十进制值。然后寻找一个共同值。如果有多个，选择使 $X$ 的进制最小的那个（题目要求最小可能进制）。

---
## 参考代码

```cpp
// What Base Is This?
// UVa ID: 343
// Verdict: Accepted
// Submission Date: 2016-06-27
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string X, Y;
    string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    map<char, int> key;
    
    // 建立字符到数值的映射
    for (int i = 0; i < digits.length(); i++)
        key.insert(make_pair(digits[i], i));
        
    while (cin >> X >> Y)
    {
        set<long long> Xs, Ys;                 // 存储所有可能的数值
        map<int, long long> valueXs, valueYs;  // 进制 -> 数值 映射
        
        // 计算 X 的最小可能进制
        int baseX = 0;
        for (char c : X)
            baseX = max(baseX, key[c] + 1);
        baseX = max(baseX, 2);
        
        // 枚举 X 的所有可能进制
        for (int bx = baseX; bx <= 36; bx++)
        {
            long long value = 0;
            for (char c : X)
                value = value * bx + key[c];
            valueXs[bx] = value;
            Xs.insert(value);
        }
        
        // 计算 Y 的最小可能进制
        int baseY = 0;
        for (char c : Y)
            baseY = max(baseY, key[c] + 1);
        baseY = max(baseY, 2);
        
        // 枚举 Y 的所有可能进制
        for (int by = baseY; by <= 36; by++)
        {
            long long value = 0;
            for (char c : Y)
                value = value * by + key[c];
            valueYs[by] = value;
            Ys.insert(value);
        }
        
        // 寻找匹配的数值
        bool flag = false;
        for (int bx = baseX; bx <= 36; bx++)
        {
            if (Ys.find(valueXs[bx]) != Ys.end())
            {
                // 找到匹配，找出 Y 对应的进制
                for (int by = baseY; by <= 36; by++)
                    if (valueYs[by] == valueXs[bx])
                    {
                        cout << X << " base " << bx << " = ";
                        cout << Y << " base " << by << endl;
                        break;
                    }
                
                flag = true;
                break;
            }
        }
        
        if (!flag)
        {
            cout << X << " is not equal to " << Y << " in any base 2..36" << endl;
        }
    }
    
    return 0;
}
```
