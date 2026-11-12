[UVa 168 Theseus and the Minotaur](https://blog.csdn.net/metaphysis/article/details/158808231)

## 题目描述

忒修斯与弥诺陶洛斯的传说是一个经典的希腊神话故事。在这个问题中，我们需要模拟忒修斯追逐弥诺陶洛斯的场景。迷宫由一系列洞穴组成，洞穴之间由通道连接，其中一些通道是单向的。

当忒修斯听到弥诺陶洛斯从某个通道接近时，他会点燃一支蜡烛开始追逐。每经过 $k$ 个洞穴，忒修斯就会在当前位置留下一支点燃的蜡烛。弥诺陶洛斯在进入一个洞穴时，会按照特定顺序检查所有出口，选择第一个**不会直接通向有蜡烛的洞穴**的出口逃离。需要注意的是，由于忒修斯手持点燃的蜡烛，弥诺陶洛斯永远不会从它进入的通道原路返回。

当弥诺陶洛斯无法找到任何可用的出口时，它就被困住了。

## 输入格式

输入包含多行，每行描述一个场景，格式如下：

```
A:BCD;B:AD;D:BG;F:H;G:DEH;E:FGH;H:EG;C:AD. A C 3
#
```

- 分号分隔的每个部分 `X:ABC` 表示从洞穴 $X$ 出发可以到达的洞穴 $A, B, C$，顺序即为弥诺陶洛斯检查出口的顺序。
- 最后的部分 `.A C 3` 表示：
  - 第一个字母 $A$：弥诺陶洛斯最初所在的洞穴
  - 第二个字母 $C$：忒修斯最初所在的洞穴
  - 数字 $3$：参数 $k$，即每隔 $k$ 个洞穴放置一支蜡烛
- 输入以单独的一行 `#` 结束。

## 输出格式

对于每个迷宫，输出一行，包含：
- 按放置顺序列出放置蜡烛的洞穴，每个字母后跟一个空格
- 一个斜杠 `/` 后跟弥诺陶洛斯被困的洞穴

例如：`D F G /E`

## 解题思路

### 1. 问题分析

这是一个典型的**图遍历模拟**问题。我们需要：
1. 构建迷宫的有向图结构
2. 按照规则模拟忒修斯的追逐过程
3. 记录放置蜡烛的洞穴
4. 确定弥诺陶洛斯最终被困的位置

### 2. 数据结构设计

- 使用邻接表存储图：$\texttt{vector<vector<int>> caverns(26)}$，因为洞穴用大写字母 $A$ 到 $Z$ 表示
- 使用布尔数组 $\texttt{lighted[26]}$ 标记哪些洞穴有蜡烛
- 使用整型变量记录当前位置：
  - $\texttt{minotaur}$：弥诺陶洛斯当前所在洞穴
  - $\texttt{theseus}$：忒修斯当前所在洞穴
- 使用 $\texttt{steps}$ 记录自从上次放置蜡烛后经过的步数

### 3. 输入解析

输入字符串的处理分为几步：
1. 去除空格和制表符
2. 将 `.` 和 `;` 替换为空格，便于分割
3. 分割得到各个部分，前 $n-1$ 个部分是图的边信息，最后一个部分是初始状态
4. 对于每个边信息 `X:ABC`，将 $X$ 到 $A$、$X$ 到 $B$、$X$ 到 $C$ 的边加入邻接表
5. 从最后一个部分解析出：
   - 第 $1$ 个字符：弥诺陶洛斯起始位置
   - 第 $2$ 个字符：忒修斯起始位置
   - 剩余字符：数字 $k$

### 4. 模拟追逐过程

模拟的核心循环：

```cpp
while (true) {
    bool trapped = true;
    // 弥诺陶洛斯寻找出口
    for (int i = 0; i < caverns[minotaur].size(); i++) {
        int next = caverns[minotaur][i];
        // 出口不能有蜡烛，且不能是忒修斯进入的通道
        if (!lighted[next] && next != theseus) {
            // 更新位置
            theseus = minotaur;
            minotaur = next;
            trapped = false;
            break;
        }
    }
    
    if (trapped) {
        // 弥诺陶洛斯被困
        cout << "/" << char('A' + minotaur) << "\n";
        break;
    } else {
        // 步数计数，检查是否需要放置蜡烛
        if (++steps == k) {
            cout << char('A' + theseus) << " ";
            lighted[theseus] = true;
            steps = 0;
        }
    }
}
```

### 5. 关键细节

- **蜡烛放置时机**：当忒修斯进入一个洞穴（即他刚追到的位置）时，如果这是第 $k$ 步，他就在**这个洞穴**放置蜡烛。注意：放置蜡烛的是忒修斯**当前所在的洞穴**，而不是弥诺陶洛斯的洞穴。
- **步数计算**：每次弥诺陶洛斯成功移动一步，步数 $+1$。当步数达到 $k$ 时，在忒修斯当前所在位置放置蜡烛并重置步数。
- **出口检查规则**：弥诺陶洛斯按照输入给定的顺序检查出口。它不能选择：
  - 有蜡烛的洞穴（$\texttt{lighted[next] == true}$）
  - 忒修斯刚进入的通道（$\texttt{next == theseus}$）

### 6. 示例解析

以题目给出的示例为例：
- 图结构：$A \to B,C,D$；$B \to A,D$；$D \to B,G$；$F \to H$；$G \to D,E,H$；$E \to F,G,H$；$H \to E,G$；$C \to A,D$
- 初始位置：弥诺陶洛斯在 $A$，忒修斯在 $C$，$k = 3$

模拟过程：
1. 忒修斯从 $C$ 追到 $A$，弥诺陶洛斯从 $A$ 到 $B$（步数 $1$）
2. 忒修斯从 $A$ 到 $B$，弥诺陶洛斯从 $B$ 到 $D$（步数 $2$）
3. 忒修斯从 $B$ 到 $D$，弥诺陶洛斯从 $D$ 到 $G$（步数 $3$，在 $D$ 放置蜡烛）
4. 忒修斯从 $D$ 到 $G$，弥诺陶洛斯从 $G$ 到 $E$（步数 $1$）
5. 忒修斯从 $G$ 到 $E$，弥诺陶洛斯从 $E$ 到 $F$（步数 $2$）
6. 忒修斯从 $E$ 到 $F$，弥诺陶洛斯从 $F$ 到 $H$（步数 $3$，在 $F$ 放置蜡烛）
7. 忒修斯从 $F$ 到 $H$，弥诺陶洛斯从 $H$ 到 $E$（步数 $1$）
8. 忒修斯从 $H$ 到 $E$，弥诺陶洛斯从 $E$ 到 $G$（步数 $2$）
9. 忒修斯从 $E$ 到 $G$，弥诺陶洛斯从 $G$ 到 $H$（步数 $3$，在 $G$ 放置蜡烛）
10. 忒修斯从 $G$ 到 $H$，弥诺陶洛斯从 $H$ 到 $E$（步数 $1$）
11. 忒修斯从 $H$ 到 $E$，弥诺陶洛斯在 $E$ 检查出口：
    - $F$：有蜡烛（在步骤 $6$ 放置）
    - $G$：有蜡烛（在步骤 $9$ 放置）
    - $H$：有蜡烛？不，$H$ 没有蜡烛，但这是它进入的通道（忒修斯在 $E$，来自 $H$），所以不能选
    - 没有可用出口，被困在 $E$

输出：$D$ $F$ $G$ $/E$

## 代码实现

```cpp
// Theseus and the Minotaur
// UVa ID: 168
// Verdict: Accepted
// Submission Date: 2016-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> caverns;
bool initialized = false;
int theseus, minotaur, k, lighted[26];

void buildGraph(string line) {
    for (int i = 0; i < caverns.size(); i++) caverns[i].clear();
    for (int i = line.length() - 1; i >= 0; i--) {
        if (line[i] == ' ' || line[i] == '\t') line.erase(line.begin() + i);
        if (line[i] == '.' || line[i] == ';') line[i] = ' ';
    }

    istringstream iss(line);
    vector<string> blocks;
    string block;
    while (iss >> block) blocks.push_back(block);

    for (int i = 0; i < blocks.size() - 1; i++)
        for (int j = 2; j < blocks[i].length(); j++)
            caverns[blocks[i][0] - 'A'].push_back(blocks[i][j] - 'A');

    minotaur = blocks.back()[0] - 'A';
    theseus = blocks.back()[1] - 'A';

    k = 0;
    int index = 2;
    while (index < blocks.back().length()) {
        k = k * 10 + (blocks.back()[index] - '0');
        index++;
    }
}

void startPursuit() {
    fill(lighted, lighted + 26, false);

    int steps = 0;
    while (true) {
        bool trapped = true;
        for (int i = 0; i < caverns[minotaur].size(); i++)
            if (lighted[caverns[minotaur][i]] == false && caverns[minotaur][i] != theseus) {
                theseus = minotaur;
                minotaur = caverns[minotaur][i];
                trapped = false;
                break;
            }

        if (trapped) {
            cout << '/' << (char)('A' + minotaur) << '\n';
            break;
        } else {
            if (++steps == k) {
                cout << (char)('A' + theseus) << ' ';
                lighted[theseus] = true;
                steps = 0;
            }
        }
    }
}

int main() {
    for (int i = 0; i < 26; i++) {
        vector<int> cavern;
        caverns.push_back(cavern);
    }
    string line;
    while (getline(cin, line), line != "#") {
        buildGraph(line);
        startPursuit();
    }
    return 0;
}
```

## 复杂度分析

- 时间复杂度：$O(n \times m)$，其中 $n$ 是洞穴数量（最多 $26$），$m$ 是每个洞穴的出口数量。由于洞穴数量固定且很小，实际运行时间可以视为常数。
- 空间复杂度：$O(26 + m)$，用于存储图和标记数组。

## 注意事项

1. 输入处理时要注意字符串末尾可能有多余的空格
2. 数字 $k$ 可能不止一位数，需要完整解析
3. 输出格式要求严格：蜡烛洞穴后跟一个空格，然后斜杠，最后是被困洞穴，不要额外输出空格或换行

## 总结

本题是一个有趣的模拟问题，核心在于准确理解追逐规则并正确实现状态转移。通过仔细模拟每一步，我们可以得到正确的结果。虽然题目背景是神话故事，但本质上是一个**有向图上的状态模拟**问题。
