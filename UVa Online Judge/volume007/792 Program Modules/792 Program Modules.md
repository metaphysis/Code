## 题目描述

给定一个程序中的所有函数及其直接调用关系，定义关系 $A \rightarrow B$ 表示函数 $A$ 直接调用 $B$，$A \Rightarrow B$ 表示 $A$ 可传递地调用 $B$（直接或间接）。已知 $\rightarrow$ 是 $\Rightarrow$ 的子集，且 $\Rightarrow$ 具有传递性。  
现需要将所有函数划分为若干模块，满足：

1. 若 $A \Rightarrow B$ 且 $B \Rightarrow A$，则 $A$ 与 $B$ 必须在同一模块。
2. 任意两个不满足上述条件的函数必须分属不同模块。

要求输出所有模块，每个模块内的函数名按字典序升序排列，模块按第一个元素（最小函数名）的字典序升序排列。每组数据输出后跟一个空行。

## 输入格式

输入包含若干组数据，每组数据代表一个待模块化的程序。每组数据格式为：

```
(Fun1 Fun11 ... Fun1n1)(Fun2 Fun21 ... Fun2n2)... (Funm Funm1 ... Funmn m).
```

其中每个括号项表示源函数 $Fun_i$ 直接调用其后所有函数 $Fun_{ij}$（$j = 1..n_i$）。  
函数名由字母组成，区分大小写。括号之间、函数名之间可以有任意数量的空格、制表符或换行。  
每组数据以句点 `.` 结尾，输入正确（每个函数恰好出现在一个项的左侧，同一项内函数名互不相同）。  
如果一组数据不含任何括号，则表示空函数集（例如仅一个 `.`）。

## 输出格式

对于每组数据，输出若干行，每行一个模块内的函数名（升序排列，空格分隔）。  
模块之间按各自最小函数名的字典序升序输出。  
每组数据的输出结束后必须输出一个空行（即使该组没有函数，也要输出一个空行）。

## 样例

**输入**
```
.

(a a) (a b) (b).

(a b c) (b a e) (c d) 
(d d) (e b).
```

**输出**
```

a
b

a b e
c
d

```

## 题目分析

规则 $\texttt{1}$ 和规则 $\texttt{2}$ 共同定义了模块的划分标准：若两个函数相互可达（即 $A \Rightarrow B$ 且 $B \Rightarrow A$），则它们必须在同一模块；否则绝对不能在同一模块。这正是有向图中**强连通分量（$\texttt{Strongly Connected Component}$, $\texttt{SCC}$）** 的定义。  
因此，将每个函数看作节点，直接调用关系 $A \rightarrow B$ 看作从 $A$ 到 $B$ 的有向边，则一个模块即对应一个强连通分量。  
由于 $\Rightarrow$ 是 $\rightarrow$ 的传递闭包，同一强连通分量内的任意两个节点相互可达，符合规则 1；不同强连通分量之间的节点不存在双向可达路径，符合规则 $\texttt{2}$。

因此，问题转化为：给定有向图，求所有强连通分量，并按题目要求排序输出。

## 解题思路

### 图构建

首先需从输入中提取每个函数及其直接调用列表。输入为自由格式，但以句点 `.` 分隔每组数据。  
我们可以先读入整个数据集（直到遇到 `.`）为一个字符串，再通过查找括号 `(` 和 `)` 来提取每个括号内的内容。每个括号内部是一个空格分隔的单词序列，第一个单词为源函数，其余为目标函数。  
为每个函数分配唯一编号，建立邻接表。

### 强连通分量求解

使用 $\texttt{Tarjan}$ 算法求 $\texttt{SCC}$。该算法通过一次深度优先搜索（$\texttt{DFS}$），记录每个节点的 $\textit{dfn}$（访问次序）和 $\textit{low}$（能回溯到的最早祖先）。当 $\textit{dfn}[u] = \textit{low}[u]$ 时，栈中从栈顶到 $u$ 的所有节点构成一个强连通分量。  
复杂度为 $O(V + E)$，其中 $V$ 为函数数，$E$ 为直接调用边数。

### 排序与输出

每个 $\texttt{SCC}$ 内部函数名按字典序排序，整个 $\texttt{SCC}$ 列表按其最小函数名的字典序排序。  
输出时，每个 $\texttt{SCC}$ 占一行，函数名用空格分隔，末尾换行。每组数据结束后额外输出一个空行。

### 复杂度分析

- 解析输入：每个字符或单词读入一次，时间复杂度 $O(\text{输入总长度})$。
- 建图：每个括号项处理一次，总边数 $E$，时间复杂度 $O(E)$。
- $\texttt{Tarjan}$：$O(V + E)$。
- 排序：每个 $\texttt{SCC}$ 内部排序，总代价 $O(\sum k_i \log k_i) \le O(V \log V)$；外部排序 $O(C \log C)$，$C$ 为 $\texttt{SCC}$ 数量，$C \le V$。
- 总时间复杂度 $O(V + E + V \log V)$，空间复杂度 $O(V + E)$。

## 代码实现

```cpp
// Program Modules
// UVa ID: 792
// Verdict: Accepted
// Submission Date: 2026-07-09
// UVa Run Time: 0.300s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<string> splitByWhitespace(const string& s) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (ss >> token) tokens.push_back(token);
    return tokens;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string data, token;
    while (cin >> token) {
        data = token;
        while (1) {
            if (token.back() == '.') break;
            cin >> token;
            data += ' ' + token;
        }
        vector<string> names;
        unordered_map<string, int> idMap;
        vector<vector<int>> g;
        auto getNode = [&](const string& name) -> int {
            auto it = idMap.find(name);
            if (it != idMap.end()) return it->second;
            int newId = (int)names.size();
            idMap[name] = newId;
            names.push_back(name);
            g.push_back({});
            return newId;
        };
        size_t pos = 0;
        while (true) {
            size_t left = data.find('(', pos);
            if (left == string::npos) break;
            size_t right = data.find(')', left + 1);
            string inner = data.substr(left + 1, right - left - 1);
            vector<string> tokens = splitByWhitespace(inner);
            if (tokens.empty()) {
                pos = right + 1;
                continue;
            }
            int srcId = getNode(tokens[0]);
            for (size_t i = 1; i < tokens.size(); ++i) {
                int tId = getNode(tokens[i]);
                g[srcId].push_back(tId);
            }
            pos = right + 1;
        }
        int n = names.size();
        vector<int> dfn(n, 0), low(n, 0), sccId(n, -1), stk;
        vector<char> inStack(n, 0);
        int timer = 0, sccCnt = 0;
        function<void(int)> tarjan = [&](int u) {
            dfn[u] = low[u] = ++timer;
            stk.push_back(u);
            inStack[u] = 1;
            for (int v : g[u]) {
                if (!dfn[v]) {
                    tarjan(v);
                    low[u] = min(low[u], low[v]);
                } else if (inStack[v]) {
                    low[u] = min(low[u], dfn[v]);
                }
            }
            if (low[u] == dfn[u]) {
                ++sccCnt;
                while (true) {
                    int v = stk.back(); stk.pop_back();
                    inStack[v] = 0;
                    sccId[v] = sccCnt;
                    if (v == u) break;
                }
            }
        };
        for (int i = 0; i < n; ++i) if (!dfn[i]) tarjan(i);
        vector<vector<string>> sccNodes(sccCnt + 1);
        for (int i = 0; i < n; ++i) sccNodes[sccId[i]].push_back(names[i]);
        for (int i = 1; i <= sccCnt; ++i) sort(sccNodes[i].begin(), sccNodes[i].end());
        vector<int> order(sccCnt);
        iota(order.begin(), order.end(), 1);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return sccNodes[a][0] < sccNodes[b][0];
        });
        for (int idx : order) {
            for (int j = 0; j < (int)sccNodes[idx].size(); ++j) {
                if (j) cout << ' ';
                cout << sccNodes[idx][j];
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;
}
```

## 总结

本题本质是图论中的强连通分量求解，直接应用 $\texttt{Tarjan}$ 算法即可。  
关键点在于正确解析输入格式，将自由格式的括号表达式转化为有向图。  
输出部分需注意排序规则（模块内升序、模块间按最小元素升序）和每组数据后的空行。  
此题提醒我们，复杂问题往往能归结为经典算法，只要准确建模，实现并不困难。
