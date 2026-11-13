
> **摘要**：本题给定 $N$ 个消息与 $M$ 个按固定顺序到达的数据包，要求为每个消息按字节顺序、且同一消息连续输出地完成重组，求所需的最小缓冲区容量。文章从题目分析入手，指出状态只需记录“当前处理时间”而非具体已完成的消息集合，进而给出以 $total[u]$、$prefix[i][u]$、$rightMax[i][u]$ 为核心的动态规划设计，转移代价可在 $O(1)$ 内求得，总时间复杂度 $O(NM + N^2)$、空间复杂度 $O(NM)$。

# 题目描述

给定 $N$ 个消息和 $M$ 个按照固定顺序到达的数据包。每个数据包属于某个消息，并给出该数据包在消息中的起始字节位置与结束字节位置。

数据包到达后可以直接输出，也可以存入缓冲区。每个消息的数据包必须按照字节顺序输出，并且同一消息的所有数据包必须连续输出。不同消息之间的输出顺序可以任意安排。

要求计算完整重组所有消息所需的最小缓冲区容量，单位为字节。

# 输入格式

每组测试数据的第一行包含两个整数 $N$ 和 $M$，分别表示消息数量与数据包数量。

第二行包含 $N$ 个整数，第 $i$ 个整数表示第 $i$ 个消息的总字节数。

接下来有 $M$ 行，每行包含三个整数 $msg$、$start$ 和 $end$：

- $msg$ 表示数据包所属的消息编号。
- $start$ 表示数据包数据的起始字节编号。
- $end$ 表示数据包数据的结束字节编号。

当输入 $N = 0$ 且 $M = 0$ 时，输入结束。

# 输出格式

对于每组测试数据，输出测试用例编号和最小缓冲区大小。

每组输出后额外输出一个空行。

# 样例输入

```text
3 3
5 5 5
1 1 5
2 1 5
3 1 5
3 5
10 20 5
2 16 20
1 6 10
3 1 5
1 1 5
2 1 15
0 0
```

# 样例输出

```text
Case 1: 0
Case 2: 10
```

# 题目分析

每个消息由若干数据包组成，数据包的字节区间共同覆盖该消息的全部内容。数据包到达顺序由输入顺序确定，但输出顺序受到消息内部字节顺序的限制。

对于同一个消息，只有从第 $1$ 个字节开始连续到达的数据包才能直接输出。例如，消息的字节区间为 $1 \sim 10$，若区间 $6 \sim 10$ 先到达，则该数据包必须进入缓冲区；只有区间 $1 \sim 5$ 到达后，前两个数据包才能依次输出。

同一消息的所有数据包必须连续输出，因此一旦开始输出某个消息，在该消息完成之前不能切换到其他消息。此时其他消息到达的数据包都只能保存在缓冲区中。

设消息 $i$ 的最后一个数据包到达时间为 $last[i]$。当处理完第 $last[i]$ 个数据包后，消息 $i$ 的全部数据已经到达，因此消息 $i$ 一定能够完成输出。

如果当前已经完成了所有最后到达时间不超过 $t$ 的消息，则下一次可以选择任意一个满足 $last[i] > t$ 的消息开始输出。选择消息 $i$ 后，系统会持续等待到第 $last[i]$ 个数据包到达，并在此过程中尽可能输出消息 $i$ 已经连续到达的前缀数据。

因此，状态只需要记录当前已经处理到哪个“消息完成时间”，无需记录具体已经输出了哪些消息。因为最后到达时间不超过当前时间的消息都已经可以全部输出，其总字节数固定。

# 解题思路

首先记录每个数据包到达时，系统累计到达的数据总量。定义 $total[u]$ 表示前 $u$ 个数据包包含的数据总字节数。

对于每个消息，将其数据包按照起始字节位置升序排序。随后扫描所有到达时间，计算 $prefix[i][u]$，其中 $prefix[i][u]$ 表示处理完前 $u$ 个到达数据包后，消息 $i$ 已经能够连续输出的前缀长度。

若消息 $i$ 的前若干个数据包已经到达，则这些数据包覆盖的字节范围为 $1 \sim prefix[i][u]$。其余已经到达但不能输出的数据都需要保存在缓冲区中。

将所有不同的消息最后到达时间排序并去重，得到状态时间数组 $times$。其中 $times[0] = 0$，其余元素均为某个消息的最后到达时间。

定义 $\textit{dp}[k]$ 表示处理到时间 $times[k]$ 时，所有满足 $last[i] \le times[k]$ 的消息已经全部输出，此时整个过程所需的最小最大缓冲区容量。

对于状态 $k$，当前已经完成的消息总字节数记为 $done[k]$。选择消息 $i$ 进行输出时，消息 $i$ 会在时间 $last[i]$ 完成。在任意时刻 $u$，其中 $times[k] < u \le last[i]$，缓冲区中的数据量为：

$$
total[u] - done[k] - prefix[i][u]
$$

其中：

- $total[u]$ 表示已经到达的全部数据量。
- $done[k]$ 表示此前已经完成并输出的消息总数据量。
- $prefix[i][u]$ 表示当前正在输出的消息 $i$ 已经直接输出的数据量。

因此，从状态 $k$ 选择消息 $i$ 后产生的最大缓冲区占用为：

$$
cost(k, i) = \max_{times[k] < u \le last[i]} \left(total[u] - done[k] - prefix[i][u]\right)
$$

为了快速得到区间最大值，预处理：

$$
rightMax[i][u] = \max_{u \le v \le last[i]} \left(total[v] - prefix[i][v]\right)
$$

于是转移代价可以直接计算为：

$$
cost(k, i) = \max \left(0, rightMax[i][times[k] + 1] - done[k]\right)
$$

设 $next$ 为满足 $times[next] = last[i]$ 的状态编号，则状态转移为：

$$
\textit{dp}[next] = \min \left(\textit{dp}[next], \max \left(\textit{dp}[k], cost(k, i)\right)\right)
$$

最终答案为最后一个状态 $\textit{dp}[times.size() - 1]$。

预处理 $prefix[i][u]$ 的时间复杂度为 $O(NM)$，预处理 $rightMax[i][u]$ 的时间复杂度为 $O(NM)$，动态规划转移的时间复杂度为 $O(N^2)$。

总时间复杂度为：

$$
O(NM + N^2)
$$

空间复杂度为：

$$
O(NM)
$$

# 代码实现

代码使用 $\texttt{DP}$ 计算最小化后的最大缓冲区容量，并通过后缀最大值数组快速完成状态转移。

```cpp
// Network EXTREME
// UVa ID: 11435
// Verdict: Accepted
// Submission Date: 2026-08-28
// UVa Run Time: 0.090s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Packet {
    int start, end, arrive;
};

int solve() {
    int n, m, caseId = 1;
    while (cin >> n >> m && (n != 0 || m != 0)) {
        vector<int> size(n), last(n, 0);
        vector<vector<Packet>> packets(n);
        vector<long long> total(m + 1, 0);
        for (int i = 0; i < n; i++)
            cin >> size[i];
        for (int i = 1; i <= m; i++) {
            int msg, start, end;
            cin >> msg >> start >> end;
            --msg;
            packets[msg].push_back({start, end, i});
            last[msg] = i;
            total[i] = total[i - 1] + end - start + 1;
        }
        for (int i = 0; i < n; i++)
            sort(packets[i].begin(), packets[i].end(), [](const Packet &a, const Packet &b) {
                return a.start < b.start;
            });
        vector<vector<int>> prefix(n, vector<int>(m + 1, 0));
        for (int i = 0; i < n; i++) {
            int pos = 0;
            for (int u = 1; u <= m; u++) {
                while (pos < static_cast<int>(packets[i].size()) && packets[i][pos].arrive <= u)
                    pos++;
                if (pos > 0)
                    prefix[i][u] = packets[i][pos - 1].end;
            }
        }
        vector<vector<long long>> rightMax(n, vector<long long>(m + 2, LLONG_MIN));
        for (int i = 0; i < n; i++) {
            for (int u = last[i]; u >= 1; u--)
                rightMax[i][u] = max(rightMax[i][u + 1], total[u] - prefix[i][u]);
        }
        vector<int> times(1, 0);
        for (int i = 0; i < n; i++)
            times.push_back(last[i]);
        sort(times.begin(), times.end());
        times.erase(unique(times.begin(), times.end()), times.end());
        vector<long long> sizeAt(m + 1, 0);
        for (int i = 0; i < n; i++)
            sizeAt[last[i]] += size[i];
        vector<long long> done(times.size(), 0);
        for (int i = 1; i < static_cast<int>(times.size()); i++)
            done[i] = done[i - 1] + sizeAt[times[i]];
        const long long inf = (1LL << 60);
        vector<long long> dp(times.size(), inf);
        dp[0] = 0;
        for (int state = 0; state < static_cast<int>(times.size()); state++) {
            if (dp[state] == inf)
                continue;
            int currentTime = times[state];
            for (int i = 0; i < n; i++) {
                if (last[i] <= currentTime)
                    continue;
                int nextState = lower_bound(times.begin(), times.end(), last[i]) - times.begin();
                long long cost = rightMax[i][currentTime + 1] - done[state];
                cost = max(0LL, cost);
                dp[nextState] = min(dp[nextState], max(dp[state], cost));
            }
        }
        cout << "Case " << caseId++ << ": " << dp.back() << "\n\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
```

# 总结

本题的核心在于将“已经完成输出的消息集合”转换为“当前处理时间”这一状态。所有最后到达时间不超过当前时间的消息都能够完成输出，因此它们的总数据量固定，状态无需记录具体消息集合。

对于当前选择输出的消息，只有连续到达的前缀数据可以直接输出，其余到达数据与其他消息的数据共同占用缓冲区。通过预处理 $prefix[i][u]$ 和 $rightMax[i][u]$，可以在 $O(1)$ 时间内计算一次状态转移的峰值缓冲区占用，再利用 $\texttt{DP}$ 得到全局最优答案。
