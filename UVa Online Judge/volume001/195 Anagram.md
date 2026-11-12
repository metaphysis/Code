[UVa 195 Anagram](https://blog.csdn.net/metaphysis/article/details/160942348)

## 题目分析

本题要求给定一个字符串（可能包含大小写字母），输出其所有不重复的排列，并按字母升序排列。需要注意的是，大写字母排在小写字母之前（即 `'A' < 'a'`，`'B' < 'b'` 等）。输入的第一行是单词个数 $n$，之后 $n$ 行每行一个单词。

例如，输入字符串 `"aAb"` 的所有不重复排列按顺序输出为：

```
Aab Aba abA bAa baA
```

## 解题思路

本题的核心是生成字符串的所有不重复排列并按自定义顺序排序。直接使用 $\texttt{std::next\_permutation}$ 可以方便地生成下一个排列，但需要自定义比较函数来实现题目要求的排序规则（大写字母优先于对应的小写字母）。

### 排序规则（自定义比较函数）

比较两个字符 $x$ 和 $y$ 时：

1. 如果两者都是大写或都是小写，直接按 `ASCII` 码比较。
2. 如果 $x$ 是大写、$y$ 是小写：
   - 先将 $x$ 转为小写，若与 $y$ 相等，则 $x$ 应排在 $y$ 前面（返回 $\texttt{true}$）；
   - 否则按小写后的值比较。
3. 如果 $x$ 是小写、$y$ 是大写：
   - 先将 $y$ 转为小写，若与 $x$ 相等，则 $x$ 应排在 $y$ 后面（返回 $\texttt{false}$）；
   - 否则按小写后的值比较。

这样保证了排序结果满足题目要求。

### 去重处理

使用一个 `set<string>` 来记录已经输出过的排列，避免重复。由于 $\texttt{next\_permutation}$ 在遇到重复字符时也会生成重复的排列，因此需要手动去重。

### 算法流程

1. 读入单词个数 $n$。
2. 对每个单词，先按自定义规则排序，得到最小的排列。
3. 循环调用 $\texttt{next\_permutation}$ 生成下一个排列，若未输出过则输出并存入集合。
4. 处理完一个单词后，清空集合（或重新定义，以保证不同单词之间的去重互不影响）。

## 代码实现

```cpp
// Anagram
// UVa ID: 195
// Verdict: Accepted
// Submission Date: 2016-03-15
// UVa Run Time: 0.202s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 存储已经输出过的排列，用于去重
set < string > existed;

// 自定义比较函数，实现大写字母优先于小写字母的排序规则
bool cmp(char x, char y) {
    // 如果 x 和 y 同为大小写或同为小写，直接按 ASCII 比较
    if (isupper(x) && isupper(y) || islower(x) && islower(y))
        return x < y;

    // x 是大写，y 是小写
    if (isupper(x)) {
        x = tolower(x);      // 将 x 转为小写进行比较
        if (x == y)          // 如果相同（如 'A' 和 'a'），大写应排在前
            return true;
        else    
            return x < y;
    }
    // x 是小写，y 是大写
    else {
        y = tolower(y);      // 将 y 转为小写进行比较
        if (x == y)          // 如果相同（如 'a' 和 'A'），小写应排在后
            return false;
        else
            return x < y;
    }
    
    return false;
}

int main() {
    // 加速输入输出
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int n;          // 单词个数
    cin >> n;
    
    while (n--) {
        string line;
        cin >> line;            // 读入当前单词

        // 按自定义规则排序，得到最小的排列
        sort(line.begin(), line.end(), cmp);
        
        do {
            // 如果当前排列尚未输出过，则输出并记录
            if (existed.count(line) == 0) {
                cout << line << endl;
                existed.insert(line);
            }
        } while (next_permutation(line.begin(), line.end(), cmp));
        
        // 清空集合，以便处理下一个单词（也可以重新定义 existed）
        existed.clear();
    }
    
	return 0;
}
```

## 要点总结

- 自定义比较函数是本题的关键，需要正确处理大小写字母的混合排序。
- 使用 $\texttt{next\_permutation}$ 可以方便地生成所有排列，但需要预先对字符串排序。
- 使用 $\texttt{set}$ 可以高效去重，注意不同单词之间需要清空集合。
- 输入输出优化（$\texttt{cin.tie(0)}$ 和 $\texttt{sync\_with\_stdio(false)}$）能提高运行效率，避免超时。
