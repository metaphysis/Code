[UVa 251 Nondeterministic Trellis Automata](https://blog.csdn.net/metaphysis/article/details/153045390)

## 题目分析

非确定性网格自动机（$\texttt{NTA}$）是一种并行计算模型，由排列成无限三角形网格的相同有限状态处理器组成。计算从底部开始，逐层向上进行，每个处理器的状态由其两个子处理器的状态和转移表非确定性决定。输入是一个字符串，表示底部一层处理器的初始状态。如果存在某种计算路径使得顶端处理器进入接受状态，则输入被接受；否则被拒绝。

### 输入格式
- 每个 $\texttt{NTA}$ 描述以两个整数 $n$ 和 $m$ 开始，分别表示状态数和接受状态数。
- 接下来是 $n \times n$ 的转移表，按行主序给出，每个转移字符串占一行。
- 随后是一系列初始配置字符串，每个占一行，以 `#` 结束。
- 输入以 $n = 0$ 终止。

### 输出格式
- 对于每个 $\texttt{NTA}$，输出其编号（如 `NTA 1`）。
- 对于每个初始配置，输出 `accept` 或 `reject`，后跟该配置字符串。
- $\texttt{NTA}$ 描述之间输出空行。

### 关键点
- 状态用连续小写字母表示，接受状态排在最后。
- $\texttt{NTA}$ 最多有 $15$ 个状态，初始配置最多 $15$ 个字符。
- 需要模拟所有可能的非确定性计算路径，判断是否存在接受路径。

## 解题思路

本题的核心在于模拟 $\texttt{NTA}$ 的计算过程。由于存在非确定性，直接枚举所有路径会非常低效。我们采用动态规划（$\texttt{DP}$）的方法来高效地跟踪所有可能的状态。

### 动态规划状态定义

定义 $dp[i][j][k]$ 为一个字符串，表示在第 $i$ 层第 $j$ 个处理器可能处于的状态集合（用字符表示）。这里：
- $i$ 表示从底部开始的行索引（$0$ 表示顶端）。
- $j$ 表示该行中的处理器索引。
- $k$ 表示状态编号（$0$ 到 $n-1$）。

### 算法步骤

1. **初始化**：读取转移表和接受状态。
2. **处理每个初始配置**：
   - 如果长度为 $1$，直接检查是否接受。
   - 否则，初始化 $\texttt{DP}$ 数组。
   - 填充底部两层：根据输入字符串设置初始状态。
   - 自底向上计算 $\texttt{DP}$：对于每个处理器，根据其两个子处理器的可能状态和转移表，计算父处理器的可能状态。
   - 清理重复状态，避免重复计算。
3. **检查接受条件**：检查顶端处理器是否可能进入任一接受状态。

### 复杂度分析
- 状态数：$O(L^2 \cdot n)$，其中 $L$ 是输入字符串长度。
- 每个状态的计算涉及遍历子状态和转移表，总体复杂度为 $O(L^2 \cdot n^3)$，在题目限制下可接受。

## 参考代码

```cpp
// Nondeterministic Trellis Automata
// UVa ID: 251
// Verdict: Accepted
// Submission Date: 2025-10-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 清理字符串中的重复字符
void cleanup(string &s) {
    bool used[26] = {};
    int newSize = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (!used[s[i] - 'a']) {
            used[s[i] - 'a'] = true;
            s[newSize++] = s[i];
        }
    }
    s.resize(newSize);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int numStates, numAccept;
    string transitionTable[17][17];  // 转移表
    string dp[17][17][17];           // dp[i][j][k] 表示第 i 层第 j 个处理器的状态集合
    string inputStr;
    for (int caseNum = 1; cin >> numStates >> numAccept && numStates; ++caseNum) {
        if (caseNum > 1) cout << "\n";
        cout << "NTA " << caseNum << "\n";
        cin.ignore(100, '\n'); // 清除换行符
        // 读入转移表
        for (int i = 0; i < numStates; ++i) {
            for (int j = 0; j < numStates; ++j) {
                getline(cin, transitionTable[i][j]);
            }
        }
        // 构建接受状态字符串
        string acceptStates = "";
        for (int i = numStates - numAccept; i < numStates; ++i) {
            acceptStates += 'a' + i;
        }
        // 处理每个输入配置
        while (getline(cin, inputStr) && inputStr != "#") {
            int len = inputStr.length();
            // 单字符输入直接判断
            if (len == 1) {
                if (inputStr[0] - 'a' >= numStates - numAccept) {
                    cout << "accept " << inputStr << "\n";
                } else {
                    cout << "reject " << inputStr << "\n";
                }
                continue;
            }
            // 初始化 dp 数组
            for (int i = 0; i < len; ++i) {
                for (int j = 0; j <= i; ++j) {
                    for (int k = 0; k < numStates; ++k) {
                        dp[i][j][k] = "";
                    }
                }
            }
            // 初始化底部两层
            for (int j = 0; j < len - 1; ++j) {
                int state = inputStr[j] - 'a';
                dp[len - 2][j][state] = inputStr[j + 1];
            }
            // 自底向上动态规划
            for (int i = len - 3; i >= 0; --i) {
                for (int j = 0; j <= i; ++j) {
                    for (int leftState = 0; leftState < numStates; ++leftState) {
                        for (char rightChar : dp[i + 1][j][leftState]) {
                            int rightState = rightChar - 'a';
                            if (!transitionTable[leftState][rightState].empty()) {
                                for (char grandChildChar : dp[i + 1][j + 1][rightState]) {
                                    int grandChildState = grandChildChar - 'a';
                                    for (char parentChar : transitionTable[leftState][rightState]) {
                                        dp[i][j][parentChar - 'a'] += transitionTable[rightState][grandChildState];
                                    }
                                }
                            }
                        }
                    }
                    // 清理重复状态
                    for (int k = 0; k < numStates; ++k) {
                        cleanup(dp[i][j][k]);
                    }
                }
            }
            // 检查顶端是否可能为接受状态
            bool accepted = false;
            for (int topState = 0; topState < numStates; ++topState) {
                for (char childChar : dp[0][0][topState]) {
                    int childState = childChar - 'a';
                    if (transitionTable[topState][childState].find_first_of(acceptStates) != string::npos) {
                        accepted = true;
                        break;
                    }
                }
                if (accepted) break;
            }
            if (accepted) {
                cout << "accept " << inputStr << "\n";
            } else {
                cout << "reject " << inputStr << "\n";
            }
        }
    }
    return 0;
}
```

## 总结

本题通过动态规划高效地模拟了非确定性网格自动机的计算过程，避免了直接枚举所有路径的高复杂度。关键点在于正确设计 $\texttt{DP}$ 状态和转移，以及处理非确定性带来的状态集合管理。代码实现了自底向上的计算，并通过清理重复状态优化了性能。
