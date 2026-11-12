[UVa 140 Bandwidth](https://blog.csdn.net/metaphysis/article/details/157427096)

## 题目分析

### 问题背景
给定一个无向图 $(V, E)$，其中 $V$ 是结点集合，$E$ 是边集合。现要求给出结点的一个排列（$\texttt{ordering}$），使得这个排列的“带宽”（$\texttt{bandwidth}$）最小。具体定义如下：

- 对于排列中的每个结点 $v$，其带宽定义为 $v$ 与其所有邻接结点在排列中的位置距离的最大值。
- 整个排列的带宽定义为所有结点带宽的最大值。

例如，题目图示中给出了两种排列方式，带宽分别为 $6$ 和 $5$，目标是找出所有排列中带宽最小的那一个。

### 输入格式
输入由多组数据组成，每组数据一行，以 `#` 结束。每组数据由若干个记录组成，记录之间用分号分隔。每个记录的格式为：

```
结点:邻居1邻居2...
```

结点用单个大写字母 `A` - `Z` 表示，图中结点数不超过 $8$ 个。

### 输出格式
对于每组数据，输出一行，内容为：

```
结点1 结点2 ... 结点n -> 带宽
```

若有多个排列带宽相同，输出字典序最小的那一个。

---

## 解题思路

### 关键约束
- 结点数 $\leq 8$。
- 带宽定义为**排列中任意两个相邻结点之间的最大距离**。
- 需要输出字典序最小的最优解。

### 可行解法
由于结点数最多为 $8$，可以枚举所有可能的排列，计算每个排列的带宽，并记录最小值。结点数 $8$ 的全排列共有 $8! = 40320$ 种，计算每个排列的带宽是可行的。

### 算法步骤
1. 读取一行输入，解析出所有结点及其邻接关系。
2. 存储结点列表，并排序（为了后续按字典序生成排列）。
3. 使用 `next_permutation` 枚举所有排列。
4. 对于每个排列，遍历所有边，计算相邻结点在排列中的最大距离，即带宽。
5. 记录带宽最小的排列，若带宽相同则保留字典序更小的。
6. 输出结果。

### 时间复杂度
- 枚举排列：$O(n!)$
- 计算每个排列的带宽：$O(n^2)$（因为需检查所有结点对）
- 总复杂度：$O(n! \cdot n^2)$，在 $n \leq 8$ 时完全可行。

---

## 代码实现

```cpp
// Bandwidth
// UVa ID: 140
// Verdict: Accepted
// Submission Date: 2016-01-19
// UVa Run Time: 0.079s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
string nodes;
map<char, string> neighbours;
int getBandwidth() {
    int minBandwidth = 1;
    for (int i = 0; i < nodes.length() - 1; i++)
        for (int j = i + 1; j < nodes.length(); j++)
            if (neighbours[nodes[i]].find(nodes[j]) != string::npos)
                if (abs(i - j) > minBandwidth)
                    minBandwidth = abs(i - j);
    return minBandwidth;
}

void getNeighbours(string record) {
    for (int i = 2; i < record.length(); i++) {
        neighbours[record[0]] += record[i];
        neighbours[record[i]] += record[0];
    }
}

int main() {
    string line;
    while (getline(cin, line), line != "#") {
        nodes.clear();
        neighbours.clear();
        for (int i = 0; i < line.length(); i++)
            if (isalpha(line[i]) && nodes.find(line[i]) == nodes.npos)
                nodes += line[i];
        while (line.find(';') != line.npos) {
            getNeighbours(line.substr(0, line.find(';')));
            line = line.substr(line.find(';') + 1);
        }
        getNeighbours(line);
        sort(nodes.begin(), nodes.end());
        int minBandwidth = 7;
        string minSequences;
        minSequences.assign(nodes);
        do {
            int bandwidth = getBandwidth();
            if (bandwidth < minBandwidth) {
                minSequences.assign(nodes);
                minBandwidth = bandwidth;
            }
        }
        while (next_permutation(nodes.begin(), nodes.end()));
        for (int i = 0; i < minSequences.length(); i++)
            cout << minSequences[i] << " ";
        cout << "-> " << minBandwidth << "\n";
    }
    return 0;
}
```

--- 

## 总结
本题是一个典型的**排列枚举 + 模拟计算**问题，由于结点数限制很小，可以直接使用全排列暴力求解。注意在实现时要处理好输入解析和字典序比较的细节。

如果你对图论和排列枚举类问题感兴趣，可以进一步学习**回溯剪枝**和**启发式搜索**（如模拟退火、遗传算法）在更大规模问题上的应用。
