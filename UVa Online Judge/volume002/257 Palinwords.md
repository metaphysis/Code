[UVa 257 Palinwords](https://blog.csdn.net/metaphysis/article/details/161283895)

## 题目分析

本题要求从输入文件中筛选出符合特定条件的单词（称为 “`Palinwords`”），并将其按出现顺序输出到输出文件中。每个单词由大写字母组成，长度不超过 $255$ 个字符。

一个单词成为 **`Palinword`** 需要满足以下条件：

1. 单词中包含 **至少两个不同的回文子串**，每个回文子串的长度 **至少为 $3$**。
2. 这两个回文子串 **不能相互包含**（即一个不能是另一个的子串），但可以 **部分重叠**。
3. 相同内容但出现在不同位置的回文子串视为 **同一个** 回文子串（位置无关）。

### 示例说明

题目描述中提到：
- 回文 `'mum'` 被嵌入在回文 `'amuma'` 中（因为 `'amuma'` 包含了 `'mum'` 作为连续子串）。
- 回文 `'aaa'` 被嵌入在回文 `'aaaa'` 中（同样存在包含关系）。

因此，如果一个单词中只有 `'aaaa'` 这一个长度为 $3$ 以上的回文，它不满足条件，因为需要 **两个不同的** 回文，且它们不能相互包含。

### 输入输出格式

- **输入**：文本文件，每行包含若干由空格分隔的单词（全大写字母），每行最多 $255$ 个字符，可能包含空行。
- **输出**：每行一个符合条件的 `Palinword`，按输入顺序输出。

### 样例分析

输入：
```
MOEILIJKHEDEN INVOER
VERNEDEREN
AMUMA AMAMA MUMMUM
AMATRAMA AAAA
ABATRABAR
DUMMY
WORDS
```

输出：
```
MOEILIJKHEDEN
VERNEDEREN
AMAMA
MUMMUM
```
## 解题思路

### 核心问题

我们需要判断一个单词中是否存在 **两个不同且互不包含** 的长度至少为 $3$ 的回文子串。

### 方法一：朴素枚举

最直接的想法是枚举所有长度 $\ge 3$ 的回文子串，然后检查是否存在满足条件的一对。但单词长度最大为 $255$，枚举所有子串的时间复杂度为 $O(n^3)$，其中 $n$ 是单词长度。$n=255$ 时，$n^3 \approx 1.66 \times 10^7$，配合回文判断，可能勉强能过，但不是最优解。

### 方法二：$\texttt{Manacher}$ 算法

$\texttt{Manacher}$ 算法可以在 $O(n)$ 时间内找出字符串中的所有回文子串（以每个位置为中心的最长回文半径）。利用 $\texttt{Manacher}$ 算法，我们可以高效地提取所有长度 $\ge 3$ 的回文子串。

#### 算法步骤

1. **预处理**：在原字符串的每个字符之间和两端插入分隔符（如 `'#'`），使得奇偶长度的回文都能统一处理。
2. **计算回文半径数组** $P[i]$，表示以位置 $i$ 为中心的最长回文半径。
3. **收集回文子串**：遍历每个中心位置，根据 $P[i]$ 可以生成从长度 $3$ 到最长半径的所有回文子串。注意只收集长度 $\ge 3$ 的回文。
4. **去重与判重**：使用集合存储已经发现的不同回文子串。当发现一个新的回文时，检查它与集合中已有的每个回文是否互不包含。若存在这样的一对，则当前单词是 `Palinword`，立即返回 $\texttt{true}$。

### 回文互不包含的判断

对于两个字符串 $A$ 和 $B$，判断它们互不包含的条件是：
- $A$ 不是 $B$ 的子串 **且** $B$ 不是 $A$ 的子串。

在代码中，使用 `string::find` 方法：
```cpp
if (palindrome.find(*it) == palindrome.npos && (*it).find(palindrome) == palindrome.npos)
```
如果 `find` 返回 `npos`，表示未找到，即不包含。

### 算法复杂度

- 预处理：$O(n)$
- 遍历生成回文：最坏情况下，每个中心可能生成 $O(P[i])$ 个回文，但总回文数实际上 $O(n^2)$ 级别。不过由于 $n=255$ 且我们只考虑长度 $\ge 3$ 的回文，且一旦找到符合条件的两个回文就提前终止，实际运行很快。
- 使用集合存储回文，插入和查找为 $O(\log m)$，其中 $m$ 为已发现的不同回文数量。

## 代码实现

```cpp
// Palinwords
// UVa ID: 257
// Verdict: Accepted
// Submission Date: 2016-05-16
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 判断一个单词是否为 Palinword
bool manacher(string word) {
    // 在字符之间插入 '#'，将奇偶长度的回文统一处理
    for (int i = word.length() - 1; i >= 0; i--)
        word.insert(word.begin() + i, '#');
    word.push_back('#');  // 在末尾也添加分隔符，方便边界处理
    
    vector<int> P(word.size());  // 回文半径数组
    set<string> palindromes;     // 存储已发现的不同回文子串（长度>=3）
    
    int center = 0, rightmost = 0, low = 0, high = 0;
    for (int i = 1; i < word.length(); i++) {
        // 利用之前计算的信息进行优化
        if (rightmost > i) {
            int j = center * 2 - i;  // i 关于 center 的对称点
            if (P[j] < (rightmost - i)) {
                P[i] = P[j];
                low = -1;  // 标记不需要扩展
            } else {
                P[i] = rightmost - i;
                high = rightmost + 1;
                low = i * 2 - high;
            }
        } else {
            P[i] = 0;
            low = i - 1;
            high = i + 1;
        }

        // 中心扩展，计算以 i 为中心的最长回文半径
        while (low >= 0 && high < word.length() && word[low] == word[high]) {
            P[i]++;
            low--;
            high++;
        }

        // 更新最右边界和对应的中心
        if ((i + P[i]) > rightmost) {
            center = i;
            rightmost = i + P[i];
        }
        
        // 如果当前中心存在长度 >=3 的回文
        if (P[i] >= 3) {
            string palindrome;
            // 中心字符可能是字母或 '#'，只取字母
            if (isalpha(word[i]))
                palindrome += word[i];

            // 从中心向外扩展，逐步构造回文子串
            // 注意：这里构造的是回文的右半部分，同时向左镜像补充
            for (int j = i + 1; j <= (i + P[i] - 1); j++)
                if (isalpha(word[j])) {
                    palindrome += word[j];
                    palindrome.insert(palindrome.begin(), word[j]);

                    // 只需要检查长度在 3 到 4 之间的回文
                    // 因为如果一个长度 >=5 的回文存在，它内部必然包含长度 3 或 4 的回文
                    // 而且题目要求两个回文互不包含，检查较短的即可
                    if (palindrome.length() >= 5)
                        break;

                    if (palindrome.length() >= 3) {
                        // 去重：如果已经存在这个回文，跳过
                        if (palindromes.count(palindrome) > 0)
                            continue;

                        // 检查新回文是否与已有回文互不包含
                        for (auto it = palindromes.begin(); it != palindromes.end(); it++)
                            // 两个条件：新回文不包含已有回文，且已有回文不包含新回文
                            if (palindrome.find(*it) == palindrome.npos &&
                                (*it).find(palindrome) == palindrome.npos)
                                    return true;  // 找到一对，即为 Palinword

                        // 将当前回文加入集合
                        palindromes.insert(palindrome);
                    }
                }
        }
    }
    
    return false;  // 未找到符合条件的两个回文
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.length() == 0)
            continue;  // 跳过空行

        string word;
        istringstream iss(line);
        while (iss >> word)
            if (manacher(word))
                cout << word << "\n";  // 输出 Palinword
    }

    return 0;
}
```

### 关键优化说明

代码中只检查长度在 $3$ 到 $4$ 之间的回文，这是因为：

- 如果一个长度 $\ge 5$ 的回文存在，它内部必然包含长度为 $3$ 或 $4$ 的回文（例如，`abcba` 包含 `bcb`）。
- 题目要求的是存在两个互不包含的回文，因此只需要考虑短回文即可，这样可以大大减少需要检查的回文数量。

## 总结

本题的核心是高效地找出字符串中的所有回文子串，并判断是否存在两个互不包含的长度至少为 $3$ 的回文子串。使用 $\texttt{Manacher}$ 算法可以在 $O(n)$ 时间内获取所有回文信息，配合集合去重和子串包含检查，能够快速完成判断。代码实现时要注意边界条件和回文构造的逻辑。
