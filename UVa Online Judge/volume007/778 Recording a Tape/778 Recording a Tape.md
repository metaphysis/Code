## 题目描述

给定若干种可用的盒式磁带，每种磁带具有固定的总时长（单位：分钟）。现有若干首歌曲，每首歌曲的时长以“分”和“秒”给出。要求从可用磁带中选取总时长最短的一种，使得所有歌曲能够被分配到该磁带的 $\texttt{A}$、$\texttt{B}$ 两个面中，且每一面的歌曲总时长均不超过磁带总时长的一半。输出所选磁带的时长，以及 $\texttt{A}$ 面和 $\texttt{B}$ 面分别包含的歌曲时长列表。输入包含多个测试实例，每个实例的歌曲列表以一行 `%` 结束，整个输入也以 `%` 结束。题目保证所有歌曲的时长互不相同。

## 输入格式

每个测试实例的第一行包含若干个整数，表示可用磁带的时长（单位：分钟）。  
接下来的若干行，每行包含一首歌曲的时长，格式为 `Xm Ys`，其中 `X` 和 `Y` 是非负整数，表示分钟和秒。  
实例的歌曲列表以仅包含 `%` 的一行结束。  
整个输入文件以仅包含 `%` 的一行结束。

## 输出格式

对于每个测试实例，输出：
- 第一行：所选磁带的时长（单位：分钟）。
- 第二行：`Side A`。
- 后续若干行：A 面每首歌曲的时长，格式同输入。
- 下一行：`Side B`。
- 后续若干行：B 面每首歌曲的时长。
- 最后一行：`%`。

## 样例

**输入**
```
56 90 120
20m 44s
4m 36s
7m 18s
13m 8s
9m 6s
8m 12s
%
30 45
3m 11s
4m 45s
13m 45s
6m 8s
%
```

**输出**
```
90
Side A
20m 44s
4m 36s
7m 8s
Side B
13m 8s
9m 6s
8m 12s
%
30
Side A
3m 11s
4m 45s
6m 8s
Side B
13m 45s
%
```

## 题目分析

本题本质上是一个**划分问题**：将若干首歌分成两组（$\texttt{A}$ 面和 $\texttt{B}$ 面），每组的总时长分别不超过磁带容量的一半，同时要求使用的磁带总时长尽可能短。

设所有歌曲总时长为 $S$（秒），可用磁带总时长为 $T$（秒）。磁带每面的容量为 $C = \lfloor T / 2 \rfloor$。若选择该磁带，则必须存在一个子集 $A$ 作为 $\texttt{A}$ 面，使得其总时长 $sum_A$ 满足：
- $sum_A \le C$
- $S - sum_A \le C$

即 $sum_A$ 必须落在区间 $[\max(0, S-C), \ C]$ 内。

因此，对于给定的磁带，问题转化为判断是否存在子集和落在上述区间内。由于歌曲数量不多且磁带容量有限（通常不超过数万秒），可以用 **$\texttt{0/1}$ 背包** 动态规划求解所有可能的子集和，并记录转移过程以便回溯出具体划分。

另外，对于多个可用磁带，只需按总时长升序依次尝试，第一个可行的即为答案（因为要求最短磁带）。

题目中所有歌曲时长互不相同，这一性质便于回溯时唯一确定歌曲，但即便不唯一也不影响算法正确性。

## 解题思路

### 步骤一：输入解析

- 读取一行可用磁带时长，用空格分隔，存入 `vector<int>` 并升序排序。
- 随后逐行读取歌曲时长，每行格式固定为 `Xm Ys`，通过查找字符 `'m'` 和 `'s'` 分离分钟和秒，统一转换为秒数存储。
- 遇到单独一行的 `%` 表示当前实例的歌曲列表结束。

### 步骤二：尝试磁带

对于排序后的每个磁带时长 $tapeMin$：
1. 转换为秒 $tapeSec = tapeMin \times 60$。
2. 若 $tapeSec < S$，则总时长不足，跳过。
3. 计算容量 $C = tapeSec / 2$。
4. 使用 $\texttt{0/1}$ 背包动态规划计算可达子集和。

### 步骤三：动态规划与回溯

设 $\textit{dp}[s]$ 表示能否凑出总秒数 $s$（$0 \le s \le C$）。同时维护两个辅助数组：
- $\textit{preSum}[s]$：在转移时，记录得到 $s$ 的上一个状态（即减去当前歌曲时长后的值）。
- $\textit{preIdx}[s]$：记录得到 $s$ 时最后加入的歌曲索引。

初始 $\textit{dp}[0] = \texttt{true}$。对每首歌 $i$（时长为 $d$），从 $C$ 向下遍历 $s$，若 $\textit{dp}[s-d]$ 为真且 $\textit{dp}[s]$ 为假，则更新 $\textit{dp}[s]$ 并记录前驱。

遍历结束后，在区间 $[\max(0, S-C), C]$ 内找到第一个可达和 $sum_A$，即为 A 面的总时长。若不存在，则当前磁带不可行，继续尝试下一个。

### 步骤四：构造划分

从 $sum_A$ 开始，利用 $\textit{preSum}$ 和 $\textit{preIdx}$ 反向追踪，得到 $\texttt{A}$ 面的所有歌曲索引。剩余歌曲自动归入 $\texttt{B}$ 面。

### 步骤五：输出

按题目格式输出磁带时长、$\texttt{A}$ 面列表、$\texttt{B}$ 面列表，最后输出 `%`。

### 复杂度分析

设歌曲数为 $n$，磁带容量为 $C$（秒）。每个实例的 $\texttt{DP}$ 时间复杂度为 $O(n \cdot C)$，空间复杂度为 $O(C)$。由于输入实例数量不定，但 $C$ 通常不超过几万，该复杂度是可行的。若遇到较大容量，需注意内存和运行时间，但题目未给出明确限制，此算法已足够。

## 代码实现

```cpp
// Recording a Tape
// UVa ID: 778
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 去除字符串首尾空格
static string trim(const string& s) {
    size_t l = s.find_first_not_of(" \t\n\r");
    if (l == string::npos) return "";
    size_t r = s.find_last_not_of(" \t\n\r");
    return s.substr(l, r - l + 1);
}

// 将形如 "20m 44s" 的字符串转为秒数
static int parseSongDuration(const string& line) {
    size_t mPos = line.find('m');
    size_t sPos = line.find('s');
    int minutes = 0, seconds = 0;
    if (mPos != string::npos) {
        string minStr = line.substr(0, mPos);
        minStr.erase(remove(minStr.begin(), minStr.end(), ' '), minStr.end());
        minutes = stoi(minStr);
    }
    if (sPos != string::npos) {
        string secStr = line.substr(mPos + 1, sPos - mPos - 1);
        secStr.erase(remove(secStr.begin(), secStr.end(), ' '), secStr.end());
        seconds = stoi(secStr);
    }
    return minutes * 60 + seconds;
}

// 输出一首歌的时长（原格式）
static void printSong(int totalSec) {
    int m = totalSec / 60;
    int s = totalSec % 60;
    cout << m << "m " << s << "s";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        line = trim(line);
        if (line == "%") break;   // 整个输入结束
        // 读取可用磁带时长
        vector<int> available;
        istringstream iss(line);
        int val;
        while (iss >> val) available.push_back(val);
        // 读取歌曲列表
        vector<int> songs;
        while (getline(cin, line)) {
            line = trim(line);
            if (line == "%") break;   // 当前实例结束
            songs.push_back(parseSongDuration(line));
        }
        int total = 0;
        for (int d : songs) total += d;
        int n = (int)songs.size();
        sort(available.begin(), available.end());
        // 尝试每个磁带
        for (int tapeMin : available) {
            int tapeSec = tapeMin * 60;
            if (tapeSec < total) continue;          // 总时长必须能装下
            int cap = tapeSec / 2;                  // 每面容量
            // DP: dp[s] = 是否可达，preSum[s] 记录上一个和，preIdx[s] 记录使用的歌曲索引
            vector<bool> dp(cap + 1, false);
            vector<int> preSum(cap + 1, -1);
            vector<int> preIdx(cap + 1, -1);
            dp[0] = true;
            for (int i = 0; i < n; ++i) {
                int d = songs[i];
                for (int s = cap; s >= d; --s)
                    if (!dp[s] && dp[s - d]) {
                        dp[s] = true;
                        preSum[s] = s - d;
                        preIdx[s] = i;
                    }
            }
            int lower = max(0, total - cap);
            int chosenSum = -1;
            for (int s = lower; s <= cap; ++s)
                if (dp[s]) {
                    chosenSum = s;
                    break;
                }
            if (chosenSum == -1) continue;   // 该磁带不可行，尝试下一个
            // 回溯得到 A 面的歌曲索引
            vector<int> sideA;
            int cur = chosenSum;
            while (cur > 0) {
                int idx = preIdx[cur];
                sideA.push_back(idx);
                cur = preSum[cur];
            }
            // 标记 A 面已选
            vector<bool> used(n, false);
            for (int idx : sideA) used[idx] = true;
            // 输出结果
            cout << tapeMin << "\n";
            cout << "Side A\n";
            for (int idx : sideA) {
                printSong(songs[idx]);
                cout << "\n";
            }
            cout << "Side B\n";
            for (int i = 0; i < n; ++i)
                if (!used[i]) {
                    printSong(songs[i]);
                    cout << "\n";
                }
            cout << "%\n";
            break;   // 找到最短磁带后跳出循环
        }
    }
    return 0;
}
```

## 总结

本题是一个经典的子集划分问题，与背包问题紧密相关。关键点在于：
- 将磁带时长和歌曲时长统一转换为秒，避免单位混淆。
- 利用 $\texttt{0/1}$ 背包 $\texttt{DP}$ 计算所有可达子集和，并通过前驱数组回溯构造具体划分。
- 按磁带升序尝试，保证第一个可行解即为最短磁带。
- 输出格式细节较多，需严格遵循题目要求。

该解法思路清晰，代码实现简洁，适合作为背包问题与回溯技巧的练习。在实际竞赛中，注意容量上限和输入解析的边界情况即可。
