[UVa 287 Text Comparison](https://blog.csdn.net/metaphysis/article/details/161118420)

## 题目分析

本题要求比较两个文本字符串，分别作为同一文本的“旧版本”和“新版本”。需要找出从旧版本到新版本所发生的所有变化，包括 **删除**、**插入** 和 **修改** 三种操作。

### 输入格式

每个测试数据包含两行，分别是新版文本 `text1` 和旧版文本 `text2`。注意输入可能带有 `text1:` 和 `text2:` 的前缀，需要去除后再处理。

### 输出格式

对于每个测试用例，按顺序输出所有变化，每条变化占一行，格式如下：

- **删除**：`pos <位置> deleted <字符数> chars “<被删除的文本>”`
- **插入**：`pos <位置> inserted <字符数> chars “<插入的文本>”`
- **修改**：`pos <位置> changed <字符数> chars from “<原文本>” to “<新文本>”`

其中，位置始终指在**旧版本**中的起始索引（从 $0$ 开始计数）。比较时**不区分大小写**，但输出时文本应转为**小写**形式。

### 样例分析

给定输入：

```
text1: This is a joke. This is not life. Don't consider it anyway...
text2: This is not a joke. This is life. Consider it thoroughly...
```

输出应为：

```
pos 8 deleted 4 chars "not "
pos 28 inserted 4 chars "not "
pos 34 inserted 6 chars "don't "
pos 46 changed 10 chars from "thoroughly" to "anyway"
```

观察到：
- 旧版本中位置 $8$ 开始的 `"not "` 在新版本中被删除
- 旧版本中位置 $28$ 处插入了 `"not "`
- 旧版本中位置 $34$ 处插入了 `"don't "`
- 旧版本中位置 $46$ 开始的 `"thoroughly"` 被修改为 `"anyway"`

注意变化是以**单词为单位**的，单词包含其后的尾随空格，但修改操作只输出单词本身（不包含标点符号如 `. . .`）。

## 解题思路

### 第一步：分词处理

直接对字符进行最长公共子序列（$\texttt{LCS}$）比较会产生碎片化问题（例如 `"thoroughly"` 可能被拆成 `"thoroughl"` 和 `"y"`）。因此需要先将文本按**单词**进行分词。

分词规则：
- 连续的字母（含单引号 `'`）构成一个单词
- 单词后面的连续空格作为该单词的一部分（用于保持位置正确）
- 标点符号（如 `.`、`,`、`!`、`?` 等）单独作为 $\texttt{token}$，其后的空格也归入该 $\texttt{token}$

这样处理后，每个 $\texttt{token}$ 都包含其后的尾随空格，确保删除和插入操作能输出正确的带空格的字符串。同时，标点符号与单词分离，使得修改操作只输出纯单词内容。

### 第二步：寻找匹配块

使用 $\texttt{LCS}$ 算法在 $\texttt{token}$ 序列上找到所有匹配的 $\texttt{token}$ 对。由于两个文本较长（不超过 $10000$ 个字符），使用经典的 $O(n \times m)$ 动态规划算法是可行的。这里 $n$ 和 $m$ 是 $\texttt{token}$ 的数量，通常远小于字符数。

状态转移方程：

$$
dp[i][j] = \begin{cases}
dp[i-1][j-1] + 1 & \text{if } token1[i-1] = token2[j-1] \\
\max(dp[i-1][j], dp[i][j-1]) & \text{otherwise}
\end{cases}
$$

其中 $dp[i][j]$ 表示 $token1$ 的前 $i$ 个元素和 $token2$ 的前 $j$ 个元素的最长公共子序列长度。

### 第三步：回溯得到匹配位置

从 $dp[n][m]$ 开始回溯，得到所有匹配的 $\texttt{token}$ 索引对 `(oldIdx, newIdx)`。这些匹配点将两个 $\texttt{token}$ 序列分割成若干段。

### 第四步：提取差异区域

相邻两个匹配点之间的区域即为差异区域：
- 从上一个匹配点之后到当前匹配点之前，旧版本中存在的 $\texttt{token}$ 构成差异段 $oldSeg$
- 新版本中存在的 $\texttt{token}$ 构成差异段 $newSeg$

### 第五步：分类输出

根据 $oldSeg$ 和 $newSeg$ 的内容进行分类：

| 情况 | 操作类型 | 输出内容 |
|------|----------|----------|
| $oldSeg$ 有非空字符，$newSeg$ 无 | 删除 | 输出 $oldSeg$（保留尾随空格） |
| $oldSeg$ 无，$newSeg$ 有非空字符 | 插入 | 输出 $newSeg$（保留尾随空格） |
| 两者都有非空字符 | 修改 | 只输出单词本身（去除尾随空格和标点），转为小写 |

### 第六步：大小写处理

比较时统一使用小写形式，输出时也统一转为小写。在分词时，每个 $\texttt{token}$ 同时保存原始文本（用于输出）和小写文本（用于比较）。

## 代码实现

```cpp
// Text Comparison
// UVa ID: 287
// Verdict: Accepted
// Submission Date: 2026-05-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Token {
    string raw;      // 原始内容（含大小写）
    string low;      // 小写内容（用于比较）
    int pos;         // 在原字符串中的起始位置
    int len;         // 长度
    bool isWord;     // 是否为单词（字母组成）
};

// 将字符串转为小写
string toLower(const string& s) {
    string res = s;
    for (char& c : res) c = tolower(c);
    return res;
}

// 分词：单词包含尾随空格，但标点单独处理
vector<Token> splitTokens(const string& s) {
    vector<Token> tokens;
    int n = s.size();
    int i = 0;
    
    while (i < n) {
        if (isalpha(s[i]) || s[i] == '\'') {
            int start = i;
            string word = "";
            while (i < n && (isalpha(s[i]) || s[i] == '\'')) {
                word += s[i];
                ++i;
            }
            // 单词后面的空格作为单词的一部分
            while (i < n && s[i] == ' ') {
                word += s[i];
                ++i;
            }
            string lowWord = toLower(word);
            string trimWord = word;
            while (!trimWord.empty() && trimWord.back() == ' ') trimWord.pop_back();
            bool isWordFlag = true;
            for (char c : trimWord) if (!isalpha(c) && c != '\'') { isWordFlag = false; break; }
            tokens.push_back({word, lowWord, start, (int)word.size(), isWordFlag});
        } else if (s[i] == ' ') {
            // 单独的空格（不应该出现，因为上面已经处理了）
            ++i;
        } else {
            // 标点符号
            int start = i;
            string punct = string(1, s[i]);
            ++i;
            // 标点后面的空格
            while (i < n && s[i] == ' ') {
                punct += s[i];
                ++i;
            }
            string lowPunct = toLower(punct);
            tokens.push_back({punct, lowPunct, start, (int)punct.size(), false});
        }
    }
    return tokens;
}

// 计算 LCS 匹配位置
vector<pair<int, int>> getLcsMatches(const vector<Token>& oldTokens, const vector<Token>& newTokens) {
    int n = oldTokens.size(), m = newTokens.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (oldTokens[i - 1].low == newTokens[j - 1].low)
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    
    vector<pair<int, int>> matches;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (oldTokens[i - 1].low == newTokens[j - 1].low) {
            matches.push_back({i - 1, j - 1});
            --i; --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    reverse(matches.begin(), matches.end());
    return matches;
}

// 去除字符串末尾的空格，并转为小写
string formatOutput(const string& s, bool keepSpace = true) {
    string res = s;
    // 转为小写
    for (char& c : res) c = tolower(c);
    // 去除末尾空格（单词本身不包含尾随空格）
    if (!keepSpace) {
        while (!res.empty() && res.back() == ' ') res.pop_back();
    }
    return res;
}

void processTestCase(const string& text1, const string& text2) {
    vector<Token> oldTokens = splitTokens(text2);
    vector<Token> newTokens = splitTokens(text1);
    
    vector<pair<int, int>> matches = getLcsMatches(oldTokens, newTokens);
    
    int oldIdx = 0, newIdx = 0;
    
    for (size_t k = 0; k <= matches.size(); ++k) {
        int oldEnd = (k < matches.size()) ? matches[k].first : oldTokens.size();
        int newEnd = (k < matches.size()) ? matches[k].second : newTokens.size();
        
        string oldStr = "", newStr = "";
        int oldStartPos = (oldIdx < oldTokens.size()) ? oldTokens[oldIdx].pos : 0;
        
        for (int i = oldIdx; i < oldEnd; ++i)
            oldStr += oldTokens[i].raw;
        for (int j = newIdx; j < newEnd; ++j)
            newStr += newTokens[j].raw;
        
        if (!oldStr.empty() || !newStr.empty()) {
            bool oldHasChar = false, newHasChar = false;
            for (char c : oldStr) if (!isspace(c)) { oldHasChar = true; break; }
            for (char c : newStr) if (!isspace(c)) { newHasChar = true; break; }
            
            if (oldHasChar && !newHasChar) {
                // 删除：输出小写形式，保留尾随空格
                cout << "pos " << oldStartPos << " deleted " << oldStr.size() 
                     << " chars \"" << formatOutput(oldStr, true) << "\"\n";
            } else if (!oldHasChar && newHasChar) {
                // 插入：输出小写形式，保留尾随空格
                cout << "pos " << oldStartPos << " inserted " << newStr.size() 
                     << " chars \"" << formatOutput(newStr, true) << "\"\n";
            } else if (oldHasChar && newHasChar) {
                // 修改：只输出单词本身（不包含尾随空格和标点），转为小写
                string oldWord = formatOutput(oldStr, false);
                string newWord = formatOutput(newStr, false);
                // 去除标点符号（只保留字母和单引号）
                string cleanOld = "", cleanNew = "";
                for (char c : oldWord) if (isalpha(c) || c == '\'') cleanOld += c;
                for (char c : newWord) if (isalpha(c) || c == '\'') cleanNew += c;
                
                cout << "pos " << oldStartPos << " changed " << oldStr.size() 
                     << " chars from \"" << cleanOld << "\" to \"" << cleanNew << "\"\n";
            }
        }
        
        if (k < matches.size()) {
            oldIdx = matches[k].first + 1;
            newIdx = matches[k].second + 1;
        }
    }
}

int main() {
    string line1, line2;
    
    while (getline(cin, line1) && getline(cin, line2)) {
        string text1, text2;
        
        size_t colonPos1 = line1.find(':');
        size_t colonPos2 = line2.find(':');
        
        if (colonPos1 != string::npos)
            text1 = line1.substr(colonPos1 + 1);
        else
            text1 = line1;
            
        if (colonPos2 != string::npos)
            text2 = line2.substr(colonPos2 + 1);
        else
            text2 = line2;
        
        if (!text1.empty() && text1[0] == ' ') text1 = text1.substr(1);
        if (!text2.empty() && text2[0] == ' ') text2 = text2.substr(1);
        
        processTestCase(text1, text2);
        cout << "\n";
    }
    
    return 0;
}
```

## 复杂度分析

- 时间复杂度：$O(N \times M)$，其中 $N$ 和 $M$ 分别为两个文本的 $\texttt{token}$ 数量。在最坏情况下（如文本全为单个字符），$N$ 和 $M$ 接近于原始字符串长度，约 $10^4$ 量级，算法可以接受。
- 空间复杂度：$O(N \times M)$，$\texttt{DP}$ 表占用主要空间。若需要进一步优化，可使用滚动数组将空间降至 $O(\min(N, M))$。
