## 题目描述

$\texttt{Alice}$ 和 $\texttt{Bob}$ 使用一个密钥（即一串密码）进行私密通信。该密钥是从字符集 $S$（大小为 $n$）中选出的 $m$ 个**互不相同**的字符所组成的有序序列。  
例如，若 $S=\{1,2,3,4,5,6,7,8,9\}$ 且 $m=4$，则一个可能的密钥是 $(3,8,1,5)$。

除 $\texttt{Alice}$ 和 $\texttt{Bob}$ 外无人知晓密钥。然而间谍 $\texttt{Steve}$ 知道集合 $S$ 和密钥长度 $m$，他试图通过提交不同的猜测来推出密钥。每次猜测都会收到一个形如 $(c,w)$ 的答复，其中：

- $c$ 表示猜测中位置正确的数字个数；
- $w$ 表示猜测中存在于密钥中但位置错误的数字个数（即错位数）。

例如，对于上述密钥，有以下猜测与答复：

$$
(1,1,1,1)\rightarrow (1,0),\quad
(2,2,2,2)\rightarrow (0,0),\quad
(9,8,3,1)\rightarrow (1,2)
$$

注意：正确的猜测会得到答复 $(m,0)$。

给定 $S$、$m$ 以及若干条（任意长度）猜测‑答复记录，程序需要执行以下操作之一：

1. 宣称给定信息不足以唯一确定正确密钥；或
2. 给出正确的密钥，即那个能得到答复 $(m,0)$ 的密钥。

## 输入格式

输入文件包含多个测试用例，每个测试用例描述如下（$n\le 10,\; m\le n$）：

- 第一行给出集合 $S$，元素之间以空格分隔（不含括号）。
- 第二行给出整数 $m$。
- 接下来若干行，每行为一条猜测‑答复，格式为  
  $\langle g_1,\ldots,g_m\rangle \rightarrow \langle c,w\rangle$，其中 $g_i\in S$。  
- 每个测试用例以单独一行字符 `%` 结束。

## 输出格式

对于每个测试用例，输出一行：

- 若存在唯一满足所有记录的密钥，则按格式 $\langle s_1,\ldots,s_m\rangle$ 输出该密钥；
- 否则输出大写字母 `N`。

## 样例

输入

```
123456789
3
(1,1,1)->(0,0)
(2,2,2)->(0,0)
(3,3,3)->(0,0)
(4,4,4)->(1,0)
(5,5,5)->(0,0)
(6,6,6)->(0,0)
(7,7,7)->(1,0)
(8,8,8)->(1,0)
(4,7,8)->(1,2)
(4,8,7)->(0,3)
(8,7,4)->(0,3)
(7,8,4)->(1,2)
(8,4,7)->(1,2)
%
123456789
3
(1,1,1)->(0,0)
(2,2,2)->(0,0)
(3,3,3)->(0,0)
(4,4,4)->(1,0)
(5,5,5)->(0,0)
(6,6,6)->(0,0)
(7,7,7)->(1,0)
(8,8,8)->(1,0)
(9,9,9)->(0,0)
%
```

输出

```
(7,4,8)
N
```

## 题目分析

本题是经典的 $\texttt{Mastermind}$（猜数字）变种。密钥中的字符必须互不相同，且所有字符都属于已知集合 $S$。给定若干次猜测以及对应的 $(c,w)$ 反馈，我们需要判断能否唯一确定密钥。

最直接的思路是枚举所有可能的密钥，并逐一检查是否与所有已知反馈一致。密钥总数等于从 $n$ 个元素中选取 $m$ 个不同元素的排列数：

$$
P(n,m)=\frac{n!}{(n-m)!}
$$

由于题目限制 $n\le 10$，最大情况 $n=10,m=10$ 时 $P(10,10)=10! = 3\,628\,800$，在可接受范围内。即使存在多条猜测记录（每条记录长度 $m$），验证一个密钥的代价为 $O(m\cdot g)$，其中 $g$ 为猜测条数。最坏情况下总运算量约为 $3.6\times 10^6 \times 10 \times g$，若 $g$ 也较大可能略高，但实际输入规模下完全可行。

因此，采用**暴力枚举所有排列**并逐条验证的方法，简单可靠且无需复杂数据结构。

## 解题思路

### 1. 枚举所有合法密钥

集合 $S$ 中字符互不相同，密钥要求 $m$ 个位置上的字符也互不相同，因此合法密钥就是 $S$ 中取 $m$ 个元素的全排列。

使用深度优先搜索（$\texttt{DFS}$）生成所有排列，同时记录当前已用字符，避免重复。

### 2. 验证候选密钥

对于每个生成的排列 $\textit{key}$，依次与每一条猜测记录比较，计算该猜测对应的 $(c,w)$，并与记录值比对。

计算规则如下：

- **正确位置数 $c$**：逐位比较 $\textit{key}[i]$ 与猜测 $\textit{guess}[i]$，相同则 $c$ 加 $1$。
- **错位数 $w$**：首先统计 $\textit{key}$ 和猜测中每个字符出现的次数，取逐字符次数最小值求和，得到两个序列中共同字符的总数 $\textit{total}$。由于共同字符中包含了位置正确的那些，因此错位数 $w = \textit{total} - c$。

若所有记录均匹配，则该 $\textit{key}$ 是一个可行解。

### 3. 判断唯一性

枚举过程中维护一个解列表。若发现第二个可行解，即可提前终止枚举（因为此时不可能唯一确定），输出 `N`。

枚举结束后，若解列表为空，说明输入数据自相矛盾（实际不会出现，因为真实密钥一定满足所有记录），也输出 `N`；若恰好一个解，则输出该解。

### 4. 输入解析

每一条猜测‑答复的格式为 `(g1,g2,...,gm)->(c,w)`，其中可能包含多余空格。处理时先去除所有空白字符，再按箭头 `->` 分割左右部分，最后解析括号内的逗号分隔数值。

### 复杂度分析

- 枚举排列数：$O(P(n,m))$。
- 每个排列验证：$O(g \cdot m)$，其中 $g$ 为猜测条数。
- 总时间复杂度：$O(P(n,m) \cdot g \cdot m)$。由于 $n\le 10$，该上界在实际数据中足够小。
- 空间复杂度：$O(g \cdot m)$ 用于存储猜测记录，以及递归栈深度 $O(m)$。

## 代码实现

```cpp
// Codebreakers
// UVa ID: 777
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 2.150s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 存储单条猜测及其答复
struct Guess {
    vector<char> g; // 猜测序列
    int c, w;       // 正确位置数、错位数
};

// 解析一行猜测‑答复，填充 Guess 结构
void parseLine(const string& line, int m, Guess& guess) {
    string s;
    for (char ch : line)
        if (!isspace(ch)) s.push_back(ch); // 移除所有空白字符

    size_t arrow = s.find("->");
    string left = s.substr(0, arrow);
    string right = s.substr(arrow + 2);

    // 去掉左右括号
    left = left.substr(1, left.size() - 2);
    right = right.substr(1, right.size() - 2);

    // 解析猜测序列（逗号分隔）
    stringstream ss1(left);
    string token;
    while (getline(ss1, token, ',')) {
        if (!token.empty()) guess.g.push_back(token[0]);
    }

    // 解析 c 和 w
    stringstream ss2(right);
    vector<int> nums;
    while (getline(ss2, token, ',')) {
        nums.push_back(stoi(token));
    }
    guess.c = nums[0];
    guess.w = nums[1];
}

// 检查候选密钥是否满足所有猜测
bool checkKey(const vector<char>& key, const vector<Guess>& guesses) {
    int m = key.size();
    for (const auto& guess : guesses) {
        int c = 0, w = 0;
        // 计算正确位置数
        for (int i = 0; i < m; ++i)
            if (key[i] == guess.g[i]) ++c;

        // 统计密钥和猜测中各字符出现次数
        int cntKey[256] = {0}, cntGuess[256] = {0};
        for (char ch : key) cntKey[(unsigned char)ch]++;
        for (char ch : guess.g) cntGuess[(unsigned char)ch]++;

        // 共同字符总数
        int total = 0;
        for (int i = 0; i < 256; ++i)
            total += min(cntKey[i], cntGuess[i]);

        w = total - c; // 错位数 = 共同总数 - 正确位置数

        if (c != guess.c || w != guess.w) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (getline(cin, line)) {
        // 跳过空行
        if (line.empty()) continue;

        // 读取字符集 S
        vector<char> S;
        for (char ch : line)
            if (!isspace(ch)) S.push_back(ch);

        // 读取 m
        getline(cin, line);
        while (line.empty()) getline(cin, line);
        int m = stoi(line);

        // 读取所有猜测记录
        vector<Guess> guesses;
        while (true) {
            getline(cin, line);
            if (line.empty()) continue;
            // 去除行首空白
            size_t start = line.find_first_not_of(" \t");
            if (start == string::npos) continue;
            line = line.substr(start);
            if (line[0] == '%') break;

            Guess g;
            parseLine(line, m, g);
            guesses.push_back(g);
        }

        // 枚举所有排列（回溯）
        vector<vector<char>> solutions;
        vector<bool> used(S.size(), false);
        vector<char> cur;

        function<void()> dfs = [&]() {
            if (cur.size() == (size_t)m) {
                if (checkKey(cur, guesses))
                    solutions.push_back(cur);
                return;
            }
            for (size_t i = 0; i < S.size(); ++i) {
                if (!used[i]) {
                    used[i] = true;
                    cur.push_back(S[i]);
                    dfs();
                    cur.pop_back();
                    used[i] = false;
                    // 若已找到两个可行解，无需继续枚举
                    if (solutions.size() > 1) return;
                }
            }
        };

        dfs();

        if (solutions.size() == 1) {
            cout << "(";
            for (int i = 0; i < m; ++i) {
                if (i) cout << ",";
                cout << solutions[0][i];
            }
            cout << ")\n";
        } else {
            cout << "N\n";
        }
    }
    return 0;
}
```

## 总结

本题的核心在于利用 $n$ 很小的特点，直接枚举所有可能的排列，并逐条验证反馈。这种暴力方法实现简单，不易出错，且在当前数据规模下完全可行。

**关键点**：

- 密钥中字符互不相同，因此枚举时需使用排列而非组合，并利用回溯保证不重复。
- 计算 $(c,w)$ 时，错位数 $w$ 需先求出共同字符总数再减去正确位置数，不能直接统计错位字符个数（因为存在重复字符时统计方法不同）。
- 提前终止枚举（找到第二个可行解）可显著减少无用计算。

该解法的时间复杂度虽为指数级，但受限于 $n\le 10$，运行效率尚可，可在时限内通过，是解决此类小规模约束问题的经典策略。
