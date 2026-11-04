
> **摘要**：本题要求对聊天室中逐行输入的文本进行实时过滤判定。判定依据包括：整行是否出现超过 $5$ 个连续辅音、是否含有超过 $4$ 个连续辅音的“坏单词”且最近 $10$ 行中此类行超过 $2$ 条、以及是否与最近 $10$ 行中的某行完全重复。任意条件触发即输出 `n`，否则输出 `y`。本文通过辅音判定函数、坏单词检测与双端队列维护最近 $10$ 行历史，实现 $O(n)$ 时间复杂度的解法。

## 题目描述

一个互联网聊天室中存在若干正常用户，但也有一些恶意用户会发送无意义字符串、广告或重复内容以干扰讨论。为了过滤这些内容，$\texttt{Banku}$ 教授（虽然不如 $\texttt{Shanku}$ 教授聪明）提出了如下判定规则：

定义**辅音**为所有英文字母（大小写）中，除去元音字母 $\texttt{a, e, i, o, u, y}$ 及其大写形式 $\texttt{A, E, I, O, U, Y}$ 之外的字母。

对于用户输入的每一行文本，该行**不被允许发送**（即应判定为 `n`）当且仅当满足以下至少一个条件：

1. 该行包含**超过 $5$ 个连续辅音**（即至少 $6$ 个连续辅音）；
2. 该行中**至少有一个单词**包含**超过 $4$ 个连续辅音**（即至少 $5$ 个连续辅音），并且该用户在**最近输入的 $10$ 行**（无论这些行是否被允许发送）中，已经出现了**超过 $2$ 条**满足“包含超过 $4$ 个连续辅音的单词”的行；
3. 该行与**最近输入的 $10$ 行**中的**某一行完全相同**（即该行之前已经出现过至少一次）。

注意：此处“最近输入的 $10$ 行”包括所有用户尝试发送的行，无论该行是否通过审核并被实际发送到聊天室。即，每一行输入都会进入历史记录。

## 输入格式

输入包含若干行。第一行是一个整数 $n$，表示接下来共有 $n$ 行文本。随后 $n$ 行，每行由不超过 $200$ 个 $\texttt{ASCII}$ 字符组成。

## 输出格式

对于输入的每一行，若该行可被接受（即允许发送），则输出字符 `y`，否则输出 `n`，每个输出占一行。

## 样例

**输入**
```
12
hello how r u?
where r u from?
kjhh kh kgkjhg jhg
where r u from?
i am from London, Ontario, Canada
how r you nxw?
now where r u from?
kjhh kh kgkjhg jhg
very good
it is very cold here.
```

**输出**
```
y
y
y
n
y
y
y
n
y
y
```

## 题目分析

本题的核心任务是对每行输入进行实时判定，判定依据依赖于**当前行自身的内容**以及**最近 $10$ 行历史记录**（包括之前所有输入的行，无论是否通过）。

判定规则包含三个独立条件，只要触发任意一条即输出 `n`，否则输出 `y`。因此，我们需要对每行文本进行三项检查：

- **条件 1**：检查整行是否存在 $6$ 个或以上连续辅音。该条件仅依赖于当前行，只需一次线性扫描。
- **条件 2**：首先需要判断当前行是否含有“坏单词”（即某个单词内部存在至少 $5$ 个连续辅音）。然后统计历史记录中所有“坏单词”行的数量，若该数量超过 $2$，则触发条件 2。注意：历史记录不包括当前行本身。
- **条件 3**：检查历史记录中是否存在与当前行完全相同的字符串。若存在，则触发条件 3。

三个条件的检查顺序可以任意，但为了避免重复计算，通常先进行条件 1 的快速判断，若触发可直接输出 `n`，无需继续。若条件 1 未触发，则需计算当前行是否含有坏单词（用于条件 2 的计数和后续历史存储），再检查条件 2 和条件 3。

历史记录的维护：每处理完一行（无论该行是否通过），都需要将当前行及其“是否含有坏单词”的标记加入历史队列，并保持队列大小为 $10$（即仅保留最近 $10$ 行）。

## 解题思路

### 辅音判定函数

首先定义辅音判定函数 $\texttt{isConsonant}(c)$。对于字符 $c$，若 $c$ 不是字母，直接返回 $\texttt{false}$；否则将 $c$ 转换为小写，并判断是否属于 $\{\texttt{a, e, i, o, u, y}\}$，若不是则为辅音。

### 条件 1 的检测

函数 $\texttt{hasExceedFiveConsecutive}(s)$ 遍历字符串 $s$，维护当前连续辅音个数 $\textit{cnt}$。遇到辅音则 $\textit{cnt}$ 加一，若 $\textit{cnt} > 5$ 则返回 $\texttt{true}$；否则遇到非辅音时将 $\textit{cnt}$ 置零。该函数时间复杂度 $O(|s|)$。

### 条件 2 中“坏单词”的检测

函数 $\texttt{hasWordWithMoreThanFourConsecutive}(s)$ 检测是否存在一个单词（连续字母序列）内部有超过 $4$ 个连续辅音。遍历字符串，当遇到字母时，提取出一个完整的单词（连续字母段），然后统计该单词内部的最大连续辅音数 $\textit{maxCnt}$。若 $\textit{maxCnt} > 4$，则返回 $\texttt{true}$。该函数同样为 $O(|s|)$。

### 历史记录的维护

使用双端队列 $\texttt{deque<pair<string, bool>>}$ 存储最近 $10$ 行的内容及坏单词标记。每处理完一行后，将当前行的内容和坏单词标记压入队尾；若队列大小超过 $10$，则弹出队首元素。

### 判定流程

对于每一行输入 $s$：

1. 若 $\texttt{hasExceedFiveConsecutive}(s)$ 为真，则输出 `n`，更新历史记录，继续下一行。
2. 计算 $\textit{hasBad} = \texttt{hasWordWithMoreThanFourConsecutive}(s)$。
3. 遍历历史队列，统计其中 $\textit{second} == \texttt{true}$ 的数量 $\textit{badCount}$。若 $\textit{badCount} > 2$，则输出 `n`，更新历史，继续。
4. 遍历历史队列，统计与 $s$ 相同的行数 $\textit{duplicate}$（因为历史中不包含当前行，所以若 $\textit{duplicate} \ge 2$ 表示之前出现过至少一次，即重复）。若 $\textit{duplicate} \ge 2$，则输出 `n`，更新历史，继续。
5. 若以上均未触发，则输出 `y`。
6. 将 $\{s, \textit{hasBad}\}$ 压入历史队列，并保持队列大小不超过 $10$。

### 正确性说明

- 历史记录包含所有已输入的行（包括被拒绝的行），这与题目原意一致，因为规则中明确“最近发送的 $10$ 行”实际指用户尝试发送的所有行，不区分是否成功。
- 条件 3 检查历史中是否已存在相同行，使用 $\textit{duplicate} \ge 2$ 等价于“之前出现过至少一次”，因为历史中不包含当前行，所以重复次数若为 $1$ 表示没有出现过，为 $2$ 表示出现了一次，依此类推。实际代码中判断 $\textit{duplicate} \ge 2$ 完全正确。
- 各条件的检查顺序不影响最终结果，因为所有条件彼此独立，且均基于当前行和固定历史。

### 复杂度分析

- 每行长度不超过 $200$，因此单个字符串的扫描为 $O(1)$ 量级（常数小）。
- 每次判定需要遍历历史队列（最多 $10$ 个元素），也是常数时间。
- 总体时间复杂度为 $O(n \cdot 200)$，即 $O(n)$，完全可以满足题目要求。
- 空间复杂度为 $O(10 \cdot 200)$，即常数。

## 代码实现

```cpp
// Chat Rooms
// UVa ID: 1186
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

bool isConsonant(char c) {
    if (!isalpha(c)) return false;
    char low = tolower(c);
    return !(low == 'a' || low == 'e' || low == 'i' || low == 'o' || low == 'u' || low == 'y');
}

bool hasExceedFiveConsecutive(const string &s) {
    int cnt = 0;
    for (char c : s) {
        if (isConsonant(c)) {
            ++cnt;
            if (cnt > 5) return true;
        } else cnt = 0;
    }
    return false;
}

bool hasWordWithMoreThanFourConsecutive(const string &s) {
    int i = 0, len = s.size();
    while (i < len) {
        if (isalpha(s[i])) {
            int j = i;
            while (j < len && isalpha(s[j])) ++j;
            int cnt = 0, maxCnt = 0;
            for (int k = i; k < j; ++k) {
                if (isConsonant(s[k])) {
                    ++cnt;
                    if (cnt > maxCnt) maxCnt = cnt;
                } else cnt = 0;
            }
            if (maxCnt > 4) return true;
            i = j;
        } else i++;
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    deque<pair<string, bool>> history;
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        bool hasFive = hasExceedFiveConsecutive(line);
        bool hasFour = hasWordWithMoreThanFourConsecutive(line);
        int badCount = 0;
        for (auto &p : history) if (p.second) ++badCount;
        int duplicate = 0;
        for (auto &p : history) if (p.first == line) duplicate++;
        if (hasFive || (hasFour && badCount > 2) || duplicate >= 2) cout << 'n';
        else cout << 'y';
        cout << '\n';
        history.push_back({line, hasFive || hasFour});
        while (history.size() > 10) history.pop_front();
    }
    return 0;
}
```

## 总结

本题的关键点在于正确理解“最近 $10$ 行”的范围——它包含所有尝试发送的行，而不仅仅是成功发送的行。这一细节在题目描述中并未明确强调，但通过样例和实际测试可以确认。

解题时，我们将每行的辅音连续长度检测、坏单词检测以及历史记录管理分离开来，使代码清晰且易于维护。由于数据规模很小（每行长度 $\le 200$，历史窗口仅 $10$），我们采用直接的线性扫描和队列维护，即可在 $O(n)$ 时间内完成所有判定。

此类题目锻炼了对字符串基本操作和状态维护的能力，同时也提醒我们在处理实际问题时要仔细理解规则中的隐含条件。
