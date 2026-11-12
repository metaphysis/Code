[UVa 173 Network Wars](https://blog.csdn.net/metaphysis/article/details/160701849)

## 题目分析

本题设定在 $2126$ 年，彗星 $\texttt{Swift‑Tuttle}$ 撞击地球后，网络中的部分链接被切断，同时一些 $\texttt{AI}$ 程序发生了变异。两个程序 $\texttt{Paskill}$ 和 $\texttt{Lisper}$ 在网络中移动，并遵循以下规则：

- 每个节点被首次访问时会被标记。$\texttt{Paskill}$ 标记为 $\texttt{PASKILL\_VISITED}$，$\texttt{Lisper}$ 标记为 $\texttt{LISPER\_VISITED}$。
- $\texttt{Paskill}$ 进入节点后，会激活一个修改过的 $\texttt{Prolog}$ 解释器，该解释器会反向编译并销毁任何后续进入的程序。因此 $\texttt{Paskill}$ 永远不会重复进入已访问过的节点。
- $\texttt{Lisper}$ 进入节点后，会激活一个变异为无限循环的 $\texttt{Hello World}$ 程序，使得任何其他程序（包括 $\texttt{Lisper}$ 自身）都无法再次进入该节点。因此 $\texttt{Lisper}$ 也不会重复进入已访问过的节点。
- 如果 $\texttt{Lisper}$ 试图进入一个已被 $\texttt{Paskill}$ 访问过的节点，$\texttt{Lisper}$ 会被销毁。
- 如果两个程序同时到达同一节点，它们会相互湮灭。
- 如果两个程序都无法移动，它们都会停止（被困）。
- 两个程序移动速度相同。
- 移动规则：$\texttt{Paskill}$ 从当前节点出发，**字母顺序向前**搜索相邻且**未访问**的节点（循环绕回）；$\texttt{Lisper}$ **字母顺序向后**搜索相邻节点（循环绕回），但 $\texttt{Lisper}$ 允许进入已被 $\texttt{Paskill}$ 访问过的节点（这会导致自己被销毁）。

输出要求：按照 $\texttt{Paskill}$ 优先的顺序输出终止事件及发生节点。

## 解题思路

### 1. 图的存储

节点标签为单个大写字母（$A$ 到 $Z$），共最多 $26$ 个节点。使用邻接表存储无向图。

输入格式为：
```
A:BD;C:BD;F:E;G:DEH;H:EG.AH
```
- 每个节点描述为 `节点:邻居列表`，多个描述用 `;` 分隔，以 `.` 结束。
- 之后紧跟两个起始节点：先 $\texttt{Paskill}$ 的起点，再 $\texttt{Lisper}$ 的起点。

### 2. 构造图

解析每行输入，提取每个节点的邻居。由于每条链接至少会被提及一次，但可能重复，需要在构建后对每个节点的邻居列表排序并去重。

### 3. 模拟移动

模拟的核心是交替移动（由于速度相同，每次两个程序各自移动一步）：

- 先检查当前是否在同一节点（模拟开始前及每次移动后），若是则“相互湮灭”。
- 标记当前两个节点为对应的访问状态。
- 分别为 $\texttt{Paskill}$ 和 $\texttt{Lisper}$ 计算下一步节点：
    - $\texttt{Paskill}$：从当前节点的邻居列表中，先找字母顺序大于当前节点且未访问的；若找不到，再循环从头找第一个未访问的。
    - $\texttt{Lisper}$：从当前节点的邻居列表中，先找字母顺序小于当前节点且未访问或已被 $\texttt{Paskill}$ 访问的；若找不到，再循环从末尾找第一个未访问或已被 $\texttt{Paskill}$ 访问的。
- 根据下一步节点的情况判断终止事件：
    - 若两者下一步相同 → 相互湮灭。
    - 若 $\texttt{Lisper}$ 的下一个节点已被 $\texttt{Paskill}$ 访问过 → $\texttt{Lisper}$ 被销毁。
    - 若 $\texttt{Paskill}$ 无法移动 → $\texttt{Paskill}$ 被困，此时还需检查 $\texttt{Lisper}$ 的状态。
    - 若 $\texttt{Lisper}$ 无法移动 → $\texttt{Lisper}$ 被困。
    - 否则，更新当前位置，继续下一轮移动。

### 4. 事件优先级

根据题目要求，如果多个事件同时发生，先提及 $\texttt{Paskill}$。代码中通过条件判断的顺序来体现优先级。

## 代码实现

```cpp
// Network Wars
// UVa ID: 173
// Verdict: Accepted
// Submission Date: 2016-02-21
// UVa Run Time: 0.029s
//
// 版权所有 (C) 2016, 邱秋. metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> nodes;          // 邻接表，共 26 个节点
bool initialized = false;           // 是否已初始化邻接表
int paskill, lisper;                // 当前所在节点
int visited[26];                    // 节点访问状态
const int UNVISITED = 0;            // 未访问
const int PASKILL_VISITED = 1;      // Paskill 访问过
const int LISPER_VISITED = 2;       // Lisper 访问过
const int NONE = -1;                // 无法移动

// 根据输入行构建图，并提取起始节点
void buildGraph(string line) {
    // 首次调用时初始化邻接表
    if (initialized == false) {
        for (int i = 0; i < 26; i++) {
            vector<int> connected;
            nodes.push_back(connected);
        }
        initialized = true;
    } else {
        // 后续调用时清空之前的图数据
        for (int i = 0; i < nodes.size(); i++) nodes[i].clear();
    }

    int index = 0;
    // 解析节点描述部分，直到遇到 '.'
    while (true) {
        string block;
        // 提取一个完整节点描述，如 "A:BD"
        while (line[index] != ';' && line[index] != '.') {
            if (isalpha(line[index]) || line[index] == ':') block += line[index];
            index++;
        }
        // 处理无向边：节点 block[0] 与 block[2..] 之间互连
        for (int i = 2; i < block.length(); i++) {
            nodes[block[0] - 'A'].push_back(block[i] - 'A');
            nodes[block[i] - 'A'].push_back(block[0] - 'A');
        }
        if (line[index] == '.') break; // 描述部分结束
        index++; // 跳过 ';'
    }
    // 跳过 '．'，寻找起始节点
    index++;
    while (isalpha(line[index]) == false) index++;
    paskill = line[index++] - 'A';  // Paskill 起点
    while (isalpha(line[index]) == false) index++;
    lisper = line[index++] - 'A';   // Lisper 起点
    // 对每个节点的邻居排序并去重
    for (int i = 0; i < nodes.size(); i++) {
        sort(nodes[i].begin(), nodes[i].end());
        int n = unique(nodes[i].begin(), nodes[i].end()) - nodes[i].begin();
        nodes[i].erase(nodes[i].begin() + n, nodes[i].end());
    }
}

// 计算 Paskill 下一步移动到的节点（字母顺序向前，循环绕回）
int getNodeForward() {
    // 先找比当前节点大的未访问邻居
    for (int i = 0; i < nodes[paskill].size(); i++)
        if (nodes[paskill][i] > paskill &&
            visited[nodes[paskill][i]] == UNVISITED)
            return nodes[paskill][i];
    // 若没有，则从头找第一个未访问的邻居
    for (int i = 0; i < nodes[paskill].size(); i++)
        if (visited[nodes[paskill][i]] == UNVISITED)
            return nodes[paskill][i];
    return NONE;    // 无路可走
}

// 计算 Lisper 下一步移动到的节点（字母顺序向后，循环绕回）
// 注意：Lisper 允许进入已被 Paskill 访问过的节点
int getNodeBackward() {
    // 先找比当前节点小的且未访问或已被 Paskill 访问的邻居
    for (int i = nodes[lisper].size() - 1; i >= 0; i--)
        if (nodes[lisper][i] < lisper &&
            (visited[nodes[lisper][i]] == UNVISITED ||
             visited[nodes[lisper][i]] == PASKILL_VISITED))
            return nodes[lisper][i];
    // 若没有，则从后往前找第一个未访问或已被 Paskill 访问的邻居
    for (int i = nodes[lisper].size() - 1; i >= 0; i--)
        if (visited[nodes[lisper][i]] == UNVISITED ||
            visited[nodes[lisper][i]] == PASKILL_VISITED)
            return nodes[lisper][i];
    return NONE;    // 无路可走
}

// 模拟两个程序的移动过程
void walk() {
    fill(visited, visited + 26, UNVISITED);
    while (true) {
        // 情况 1：两者在同一节点，相互湮灭
        if (paskill == lisper) {
            cout << "Both annihilated in node " << (char)('A' + paskill) << "\n";
            break;
        }
        // 标记当前节点
        visited[paskill] = PASKILL_VISITED;
        visited[lisper] = LISPER_VISITED;
        // 计算下一步
        int paskillNext = getNodeForward();
        int lisperNext = getNodeBackward();
        // 情况 2：两者都有下一步可行
        if (paskillNext != NONE && lisperNext != NONE) {
            // 情况 2.1：下一步进入同一节点 → 相互湮灭
            if (paskillNext == lisperNext) {
                cout << "Both annihilated in node " << (char)('A' + paskillNext) << "\n";
                break;
            }
            // 情况 2.2：Lisper 的下一步已被 Paskill 访问过 → Lisper 被销毁
            if (visited[lisperNext] == PASKILL_VISITED) {
                cout << "Lisper destroyed in node " << (char)('A' + lisperNext) << "\n";
                break;
            }
            // 正常移动
            paskill = paskillNext;
            lisper = lisperNext;
            continue;
        }
        // 情况 3：Paskill 无法移动
        if (paskillNext == NONE) {
            cout << "Paskill trapped in node " << (char)('A' + paskill);
            // 同时 Lisper 也无法移动 → 两者都被困
            if (lisperNext == NONE) cout << " Lisper trapped in node " << (char)('A' + lisper);
            // 或者 Paskill 被困时所在的节点正好是 Lisper 的下一步 → 相互湮灭
            else if (paskill == lisperNext) cout << " Both annihilated in node " << (char)('A' + paskill);
            // 或者 Lisper 的下一步已被 Paskill 访问过 → Lisper 被销毁
            else if (visited[lisperNext] == PASKILL_VISITED) cout << " Lisper destroyed in node " << (char)('A' + lisperNext);
            cout << "\n";
            break;
        }
        // 情况 4：Lisper 无法移动（Paskill 有下一步）
        if (lisperNext == NONE) {
            cout << "Lisper trapped in node " << (char)('A' + lisper) << "\n";
            break;
        }
    }
}

int main() {
    cin.tie(0); cout.sync_with_stdio(false);
    string line;
    while (getline(cin, line), line != "#") {
        buildGraph(line);
        walk();
    }
    return 0;
}
```

## 总结

本题模拟过程虽然规则较多，但核心是理解两个程序的移动规则和不同终止条件的优先级。实现时注意：

- 无向图的邻接表构建。
- 字母顺序的循环搜索。
- $\texttt{Lisper}$ 的特殊性：允许进入 $\texttt{Paskill}$ 访问过的节点（这会导致自己销毁）。
- 事件判断的顺序必须符合题目要求（先 $\texttt{Paskill}$）。
