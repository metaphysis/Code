[UVa 153 Permalex](https://blog.csdn.net/metaphysis/article/details/158569206)

## 题目分析

本题要求我们计算一个给定字符串在其所有不同排列的字典序序列中的位置。例如，字符串 $\texttt{acab}$ 的所有不同排列按字典序排序后，$\texttt{acab}$ 位于第 $5$ 位。

关键点：
1. 字符串中的字符可能重复，因此不同的排列数不是简单的阶乘。
2. 字符串长度最多 $30$ 个字符，但保证结果不超过 $2^{31}-1$。
3. 需要按字典序找出给定字符串的位置。

## 解题思路

### 1. 问题转化

假设我们有一个字符串 $s$，长度为 $n$。要求它在所有不同排列中的字典序位置，等价于：
- 统计所有字典序小于 $s$ 的不同排列的数量。
- 然后加 $1$ 得到 $s$ 的位置。

### 2. 计算方法

我们可以逐位确定：

对于第 $i$ 位（从 $0$ 开始），考虑所有可能放在这一位的字符 $c$，如果 $c$ 小于当前位字符 $s[i]$，那么以 $c$ 开头的所有排列都小于 $s$。我们需要统计以 $c$ 开头时，剩余字符能形成的不同排列数。

剩余字符能形成的不同排列数计算公式为：
$$\frac{(\text{剩余字符总数})!}{\prod_{j=0}^{25} (\text{剩余字符中字符} j \text{出现的次数})!}$$

### 3. 实现方法

代码采用了一种独特的方式来计算这个值：

- 预先计算了 $1$ 到 $30$ 的阶乘的质因数分解，存储在 $\texttt{prime}$ 数组中。
- 计算 $\frac{n!}{a!b!...}$ 时，将分子和分母的质因数分解，然后相减，最后将剩余的质因数相乘得到结果。

这种方法避免了直接计算大数，也无需处理浮点数精度问题。

### 4. 算法步骤

1. 对于当前字符串，计算它的所有不同排列的字典序位置。
2. 从第一位开始，对于每个位置，尝试所有小于当前字符的字母。
3. 统计以该字母开头时剩余字符能形成的排列数。
4. 将结果累加，最后加 $1$ 得到最终位置。

### 5. 代码实现分析

代码中的 $\texttt{fullPermutation}$ 函数计算给定字符串的全排列数：

$$\text{全排列数} = \frac{(\text{长度})!}{\prod (\text{每个字符出现次数的阶乘})}$$

$\texttt{permutation}$ 函数递归地计算小于给定字符串的排列数：
- 将当前字符串排序，然后依次将每个字符移到开头。
- 如果开头字符小于原字符串对应字符，累加以剩余字符的全排列数。
- 如果开头字符等于原字符串对应字符，递归处理剩余部分。

## 注意事项

- 需要处理重复字符，避免重复计数。代码中使用 $\texttt{set}$ 来缓存已处理过的排列开头。
- 结果要右对齐输出，宽度为 $10$。

## 代码实现

```cpp
// Permalex
// UVa ID: 153
// Verdict: Accepted
// Submission Date: 2016-02-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int prime[31][5] = {
    {0}, {0}, {1, 2}, {1, 3}, {2, 2, 2}, {1, 5}, {2, 2, 3}, {1, 7},
    {3, 2, 2, 2}, {2, 3, 3}, {2, 2, 5}, {1, 11}, {3, 2, 2, 3},
    {1, 13}, {2, 2, 7}, {2, 3, 5}, {4, 2, 2, 2, 2}, {1, 17},
    {3, 2, 3, 3}, {1, 19}, {3, 2, 2, 5}, {2, 3, 7}, {2, 2, 11}, {1, 23},
    {4, 2, 2, 2, 3}, {2, 5, 5}, {2, 2, 13}, {3, 3, 3, 3},
    {3, 2, 2, 7}, {1, 29}, {3, 2, 3, 5}
};

long long fullPermutation(string line) {
    vector<int> dividend, divisor;
    for (int i = 2; i <= line.length(); i++)
        for (int j = 1; j <= prime[i][0]; j++)
            dividend.push_back(prime[i][j]);
    int alpha[26] = {0};
    for (int i = 0; i < line.length(); i++)
    alpha[line[i] - 'a']++;
    for (int i = 0; i < 26; i++)
        for (int j = 2; j <= alpha[i]; j++)
            for (int k = 1; k <= prime[j][0]; k++)
                divisor.push_back(prime[j][k]);
    for (int i = 0; i < divisor.size(); i++)
        for (int j = 0; j < dividend.size(); j++)
            if (divisor[i] == dividend[j]) {
                dividend.erase(dividend.begin() + j);
                break;
            }
    long long product = 1;
    for (int i = 0; i < dividend.size(); i++)
        product *= dividend[i];
    return product;
}

long long int permutation(string current, string original) {
    int counter = current.length();
    long long index = 0;
    set<string> cache;
    sort(current.begin(), current.end());
    while (counter--) {
        string next(current);
        sort(next.begin() + 1, next.end());
        if (cache.find(next) == cache.end()) {
            cache.insert(next);
            if (next < original) {
                if (next.front() < original.front())
                    index += fullPermutation(current.substr(1));
                else if (current.length() > 1)
                    index += permutation(next.substr(1), original.substr(1));
            }
        }
        current += current.front();
        current.erase(0, 1);
    }
    return index;
}

int main() {
    string line, original;
    while (getline(cin, line), line != "#") {
        if (line.length() == 0) continue;
        long long index = permutation(line, line) + 1;
        cout << setw(10) << right << index << '\n';
    }
    return 0;
}
```

## 复杂度分析

- 时间复杂度：$O(n^2 \times 26)$，其中 $n$ 是字符串长度。对于每个位置，需要考虑所有可能的字符。
- 空间复杂度：$O(n)$，主要用于存储中间结果。

## 总结

本题的关键在于理解字典序排列的计数原理，以及如何处理重复字符。通过质因数分解计算组合数是一种避免大数溢出的巧妙方法。代码中使用 $\texttt{set}$ 去重确保了不会重复计数相同的排列开头。
