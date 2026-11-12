[UVa 188 Perfect Hash](https://blog.csdn.net/metaphysis/article/details/160911015)

## 题目分析

本题要求为给定的单词列表构造一个**完美哈希函数**，函数形式为：

$$
\left\lfloor \frac{C}{w} \right\rfloor \bmod n
$$

其中：

- $w$ 是单词转换后的整数值（转换规则：每个字母用 $5$ 位表示，即乘以 $32$，`a` = $1$，`bz` = $2 \times 32 + 26 = 90$）
- $n$ 是单词列表的长度
- $C$ 是一个待寻找的正整数，需要尽可能小
- 哈希值必须两两不同，即构成完美哈希

题目还给出一个重要约束：**$C$ 必须是至少一个 $w_i$ 的倍数**。

## 解题思路

### 单词转换

将每个单词转换为整数：从左到右处理字母，每次将当前值乘以 $32$，再加上字母对应的数值（`a` = $1$，`b` = $2$，…，`z` = $26$）。

### 寻找最小 $C$

采用**逐步迭代**的方法：

1. 从 $C = 1$ 开始
2. 检查当前 $C$ 是否使所有哈希值互异
3. 若存在冲突（即 $\lfloor C / w_i \rfloor \bmod n = \lfloor C / w_j \rfloor \bmod n$），则需要增大 $C$
4. 冲突时的最小可尝试 $C$ 为：
   
   $$
   \min\left( \left( \left\lfloor \frac{C}{w_i} \right\rfloor + 1 \right) \cdot w_i, \left( \left\lfloor \frac{C}{w_j} \right\rfloor + 1 \right) \cdot w_j \right)
   $$
   
5. 取所有冲突中计算值的**最大值**作为下一个 $C$（因为必须同时解决所有冲突）
6. 重复直到找到可行的 $C$

**关键优化**：由于 $C$ 必须至少是某个 $w_i$ 的倍数，上述更新方法保证新 $C$ 满足该约束。

### 验证函数 $\texttt{test}$

对候选 $C$，计算每个单词的哈希值 `C / w % n`，用布尔数组标记是否出现过，若重复则返回 $\texttt{false}$，否则 $\texttt{true}$。

## 代码实现

```cpp
// Perfect Hash
// UVa ID: 188
// Verdict: Accepted
// Submission Date: 2016-03-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> words;  // 存储单词转换后的整数值

// 验证函数：检查 C 是否能产生完美的哈希函数
// 返回 true 表示所有哈希值互异，false 表示存在冲突
bool test(long long C) {
    vector<int> used;  // 标记哈希值是否已被使用
    for (int i = 0; i < words.size(); i++)
        used.push_back(false);
      
    for (int i = 0; i < words.size(); i++) {
        int remainder = C / words[i] % words.size();  // 计算哈希值
        if (used[remainder] == true)   // 冲突发生
            return false;
        else
            used[remainder] = true;
    }

    return true;
}

// 寻找最小可行 C
long long find() {
    long long C = 1;        // 从 1 开始尝试
    int n = words.size();

    do {
        long long oldC = C;  // 记录本轮初始值
        // 遍历所有单词对 (i, j)
        for (int i = 0; i < words.size() - 1; i++)
            for (int j = i + 1; j < words.size(); j++)
            {
                // 如果存在冲突，则更新 C 为当前冲突中计算的最大值
                if ((oldC / words[i] % n) == (oldC / words[j] % n))
                    C = max(C, min((oldC / words[i] + 1) * words[i],
                        (oldC / words[j] + 1) * words[j])); 
            }
    } while (test(C) == false);  // 重复直到 C 可行
    
    return C;
}

int main() {
    string line, block;
    while (getline(cin, line))  {
        istringstream iss(line);
        while (iss >> block)  {
            int number = 0;
            // 将单词转换为整数：每个字母用 5 位表示
            for (int i = 0; i < block.length(); i++)
                number = number * 32 + block[i] - 'a' + 1;
            words.push_back(number);
        }
        
        sort(words.begin(), words.end());  // 按升序排序
        
        cout << line << "\n";              // 输出原始输入行
        cout << find() << "\n\n";          // 输出 C 并跟一个空行
        
        words.clear();                     // 清空，准备处理下一行
    }
    
	return 0;
}
```

## 复杂度分析

设单词数量为 $n$（$2 \le n \le 13$），则：

- 每次验证 $\texttt{test}$ 的复杂度为 $O(n)$
- 每次迭代更新冲突的复杂度为 $O(n^2)$
- 由于 $n$ 很小，且 $C$ 增长较快，迭代次数有限，算法在实际测试中非常高效

## 总结

本题的核心在于理解了冲突处理时的 $C$ 更新策略：当 $\lfloor C/w_i \rfloor \bmod n = \lfloor C/w_j \rfloor \bmod n$ 时，两个哈希值相等，要使它们不同，必须增大 $C$ 使得其中一个的商至少增加 $1$，因此下一个候选 $C$ 为 $\min((\lfloor C/w_i \rfloor + 1) \cdot w_i, (\lfloor C/w_j \rfloor + 1) \cdot w_j)$。取所有冲突中的最大值，即可保证同时解决所有冲突。这种方法避免了盲目递增，大大提高了搜索效率。
