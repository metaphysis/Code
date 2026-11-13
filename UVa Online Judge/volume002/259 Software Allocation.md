[UVa 259 Software Allocation](https://blog.csdn.net/metaphysis/article/details/161284178)

## 题目分析

一个计算中心有 $10$ 台不同的计算机（编号 $0$ 至 $9$），每台计算机在同一时间只能运行一个应用程序。有 $26$ 种应用程序，名称分别为 $\texttt{A}$ 至 $\texttt{Z}$。每天会有用户提交应用程序，同一个应用程序可能被多个用户提交，此时需要为每个用户分配一台不同的计算机来运行该应用程序。每天结束后，文员会收集所有的应用程序，并为每个应用程序列出可以运行的计算机列表，然后尝试将每个应用程序分配到一个计算机上，使得每台计算机最多只运行一个应用程序。

输入文件每天包含一个或多个作业描述，每个作业描述的格式为：

1. 一个大写字母 $\texttt{A} \sim \texttt{Z}$，表示应用程序名称。
2. 一个数字 $1 \sim 9$，表示提交该应用程序的用户数量。
3. 一个空格字符。
4. 一个或多个不同的数字 $0 \sim 9$，表示该应用程序可以运行的计算机编号。
5. 一个分号 `;` 作为终止符。
6. 一个换行符。

每天的不同作业描述之间由一个空行分隔。输入文件以文件结束符结束。

输出要求：如果能够成功分配，则输出 $10$ 个字符，分别对应计算机 $0$ 至 $9$ 上分配的应用程序（用 `-` 表示该计算机未被分配任何应用程序）；否则输出一个感叹号 `!`。

## 解题思路

### 问题本质

这是一个典型的**二分图匹配**问题，或者更具体地说，是一个**多重匹配**问题。

- 二分图的一侧是计算机节点，共 $10$ 台。
- 另一侧是应用程序实例节点。由于同一个应用程序可能有多个用户（即多个实例），我们需要将每个实例看作一个独立的节点。

但实际上，我们并不需要显式地创建所有实例节点。我们可以将每个应用程序的需求数量作为该应用程序节点的“容量”，而计算机节点容量为 $1$。这本质上是一个**带容量限制的二分图匹配**问题，也称为 **$b$-匹配问题**。

### 可行分配的必要条件

在开始匹配之前，可以先进行一些快速判断，以排除明显不可行的情况：

1. **总实例数不超过计算机总数**：设 $S = \sum_{i=0}^{25} count_i$，其中 $count_i$ 是应用程序 $i$ 的用户数量。如果 $S > 10$，则不可能分配成功，因为只有 $10$ 台计算机。

2. **每个应用程序的可用计算机数量不少于其需求数量**：对于应用程序 $i$，设 $c_i$ 为其可以运行的计算机数量，如果 $count_i > c_i$，则也不可能分配成功。

这两个条件是**必要但不充分**的，还需要进一步的搜索或匹配算法来验证。

### 算法选择

由于数据规模很小（计算机只有 $10$ 台，应用程序只有 $26$ 种，每个应用程序最多 $9$ 个用户），可以使用**深度优先搜索**（$\texttt{DFS}$）进行回溯求解。

具体思路：

- 我们按计算机编号 $0$ 到 $9$ 的顺序进行决策。
- 对于当前计算机 `index`，尝试为其分配一个尚未分配完的应用程序（即该应用程序还有未分配的用户实例）。
- 如果某应用程序可以运行在当前计算机上（即该计算机在其可用列表中），并且该应用程序还有剩余需求，则将当前计算机分配给该应用程序，并递归处理下一台计算机。
- 如果找不到合适的应用程序，也可以选择将当前计算机留空（不分配任何应用程序），然后继续处理下一台计算机。
- 当处理完所有 $10$ 台计算机后，检查是否所有应用程序的需求都已满足。如果是，则找到一组可行解。

### 回溯优化的几个技巧

1. **全局变量记录解的状态**：使用 `found` 标志，一旦找到解就立即停止搜索。

2. **剪枝**：在进入回溯之前，先检查上述两个必要条件。

3. **按计算机顺序尝试**：由于计算机数量固定且很少，按顺序分配是直观且高效的。

4. **使用 `candidates` 数组**：记录每个应用程序可以运行的计算机总数，用于快速判断是否有足够资源。

### 数据结构设计

- `computer[10]`：一个向量数组，`computer[i]` 存储可以运行在计算机 $i$ 上的所有应用程序编号（$0 \sim 25$）。
- `applications[26]`：存储每个应用程序的剩余需求数量。
- `candidates[26]`：存储每个应用程序可以运行的计算机总数（预处理时统计）。
- `solution[10]`：存储最终分配结果，`solution[i]` 表示计算机 $i$ 上运行的应用程序编号，$-1$ 表示未分配。

### 输入解析

输入文件每天包含多行，空行分隔不同的测试案例。解析规则：

- 如果读取到空行，则执行当前已收集的所有作业描述的分配，然后清空数据结构，准备处理下一天。
- 如果读取到非空行，则解析该行的作业描述：
  - 第一个字符是应用程序名称。
  - 第二个字符是用户数量（数字字符）。
  - 跳过空格后，直到分号前的所有数字字符都是可运行的计算机编号。
  - 将该应用程序加入对应计算机的可用列表，同时更新需求数量。

注意：输入文件最后可能没有空行，所以在读取结束后还需要再调用一次分配函数。

## 代码实现

```cpp
// Software Allocation
// UVa ID: 259
// Verdict: Accepted
// Submission Date: 2016-05-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> computer(10);      // computer[i] 表示可以在计算机 i 上运行的所有应用程序编号
vector<int> applications(26);          // applications[i] 表示应用程序 i 当前的剩余需求数量
vector<int> candidates(26);            // candidates[i] 表示应用程序 i 可以运行的计算机总数
vector<int> solution(10);              // solution[i] 表示计算机 i 上分配的应用程序编号，-1 表示未分配

bool found = false;                    // 是否已经找到可行解

// 深度优先搜索回溯函数
// index: 当前正在处理的计算机编号（0 ~ 9）
void backtrack(int index) {
    // 已经找到解，直接返回
    if (found) return;
    // 所有计算机都已处理完毕
    if (index == 10) {
        // 检查是否所有应用程序的需求都已满足
        for (int i = 0; i < 26; i++)
            if (applications[i] > 0)
                return;
        // 找到可行解，输出结果
        found = true;
        for (int i = 0; i < 10; i++) {
            if (solution[i] == -1) cout << "_";
            else cout << (char)('A' + solution[i]);
        }
        cout << endl;
        return;
    }
    
    // 尝试为当前计算机分配一个应用程序
    for (int i = 0; i < computer[index].size(); i++) {
        int app = computer[index][i];   // 可以在该计算机上运行的应用程序
        if (applications[app] > 0) {
            // 分配该应用程序到当前计算机
            applications[app]--;
            solution[index] = app;
            backtrack(index + 1);       // 处理下一台计算机
            // 回溯，恢复状态
            solution[index] = -1;
            applications[app]++;
            // 如果已经找到解，立即返回
            if (found) return;
        }
    }
    
    // 当前计算机不分配任何应用程序（留空）
    backtrack(index + 1);
}

// 为当前测试案例进行分配
void allocate() {
    // 必要条件1：应用程序实例总数不能超过计算机数量
    int counter = 0;
    for (int i = 0; i < applications.size(); i++) counter += applications[i];
    if (counter > 10) {
        cout << "!\n";
        return;
    }
    // 必要条件2：每个应用程序的可用计算机数量不能少于其需求数量
    for (int i = 0; i < applications.size(); i++)
        if (applications[i] > candidates[i]) {
            cout << "!\n";
            return;
        }
    // 重置搜索状态并开始回溯
    found = false;
    fill(solution.begin(), solution.end(), -1);
    backtrack(0);
    // 如果回溯结束后仍未找到解，则分配失败
    if (found == false) cout << "!\n";
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    fill(candidates.begin(), candidates.end(), 0);
    string line;
    while (getline(cin, line)) {
        // 空行表示当前测试案例结束
        if (line.length() == 0) {
            allocate();
            // 清空数据结构，准备处理下一个测试案例
            for (int i = 0; i < computer.size(); i++) computer[i].clear();
            fill(applications.begin(), applications.end(), 0);
            fill(candidates.begin(), candidates.end(), 0);
        } else {
            // 解析作业描述行
            // 格式: 应用字母 数字 空格 计算机列表 分号
            char appLetter = line[0];
            int count = line[1] - '0';      // 用户数量
            int appIndex = appLetter - 'A';
            // 更新该应用程序的需求总数
            applications[appIndex] += count;
            // 解析计算机列表（从索引 3 开始，直到分号前一个字符）
            for (int i = 3; i < line.length() - 1; i++) {
                int computerId = line[i] - '0';
                // 记录该计算机可以运行的应用程序
                computer[computerId].push_back(appIndex);
                // 统计该应用程序可以运行的计算机数量
                candidates[appIndex]++;
            }
        }
    }
    // 处理最后一个测试案例（文件末尾可能没有空行）
    allocate();
    return 0;
}
```

## 总结

本题的核心是一个小规模的多重二分图匹配问题。由于数据规模极小（计算机 $10$ 台，应用程序 $26$ 种），使用 $\texttt{DFS}$ 回溯即可高效求解。代码中通过两个必要条件进行快速剪枝，进一步提高了效率。理解本题的关键在于将“每个应用程序可能有多个用户”这一需求转化为带有容量限制的匹配问题，并利用回溯搜索找到一组可行分配。
