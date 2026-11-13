[UVa 200 Rare Order](https://blog.csdn.net/metaphysis/article/details/161002291)

## 题目分析

题目描述了一个罕见的语言，它的字符与英文字母相同（大写字母 `A` 到 `Z`），但排序规则与英文字母表不同。输入给出了一个按该语言排序规则排序的字符串列表（以 `#` 结尾），要求根据这个列表推导出该语言的字符顺序（即字母表顺序）。

例如，输入：
```
XWY
ZX
ZXY
ZXW
YWX
#
```
输出应为：
```
XZYW
```
表示该语言的字母顺序为 `X` > `Z` > `Y` > `W`。

## 解题思路

本题是一个典型的**拓扑排序**问题。我们可以将每个字符看作图中的一个节点，根据输入中相邻两个字符串的对应字符关系，推断出有向边 `u → v`（表示字符 `u` 排在字符 `v` 之前）。具体方法如下：

1. 依次比较相邻的两个字符串 `words[i]` 和 `words[i+1]`。
2. 从头开始逐位比较两个字符串，找到第一个不相同的字符位置 `j`。
3. 记 `u = words[i][j]`，`v = words[i+1][j]`，则根据字典序规则，`u` 一定排在 `v` 之前，因此添加一条有向边 `u → v`。
4. 对所有相邻字符串重复上述过程，得到一张有向无环图（题目保证输入合法，即图无环）。
5. 对该图进行拓扑排序，得到的顺序即为该语言的字母顺序。

注意：输入中并未包含所有 `26` 个大写字母，只包含出现过的字母。因此需要只对出现过的字母进行排序。

### 算法步骤

- 使用邻接表存储图。
- 统计每个节点的入度。
- 标记出现过的节点。
- 将所有入度为 $0$ 的节点入队。
- 不断取出队首节点输出，并移除其所有出边，将相应节点入度减 $1$，若入度变为 $0$ 则入队。
- 输出的节点顺序即为所求。

## 代码实现

```cpp
// Rare Order
// UVa ID: 200
// Verdict: Accepted
// Submission Date: 2017-10-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 26;  // 大写字母共26个

vector<int> g[MAXV];  // 邻接表
int degreeOfIn[MAXV]; // 入度
int visited[MAXV];    // 标记字母是否出现过

int main() {
    string word;
    vector<string> words;

    while (getline(cin, word)) {
        if (word != "#") {
            words.push_back(word); // 存储输入字符串
            continue;
        }

        // 初始化
        for (int u = 0; u < MAXV; u++) g[u].clear();
        memset(degreeOfIn, 0, sizeof(degreeOfIn));
        memset(visited, 0, sizeof(visited));

        // 依据相邻字符串推断字符顺序关系
        for (int i = 0; i < words.size() - 1; i++) {
            string &a = words[i];
            string &b = words[i + 1];
            for (int j = 0; j < min(a.length(), b.length()); j++) {
                int u = a[j] - 'A';
                int v = b[j] - 'A';
                visited[u] = visited[v] = 1; // 标记两个字母都出现过
                if (u != v) {
                    g[u].push_back(v);  // u 排在 v 之前
                    degreeOfIn[v]++;
                    break; // 只考虑第一个不同的位置
                }
            }
        }

        // 拓扑排序：队列实现 Kahn 算法
        queue<int> q;
        for (int u = 0; u < MAXV; u++)
            if (visited[u] && degreeOfIn[u] == 0)
                q.push(u);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : g[u])
                if (--degreeOfIn[v] == 0)
                    q.push(v);
            cout << (char)('A' + u);
        }
        cout << '\n';
        words.clear(); // 清空，准备处理下一组数据
    }
    return 0;
}
```

## 复杂度分析

- 设字符串个数为 $n$，每个字符串长度不超过 $20$。
- 建图过程需要遍历所有相邻字符串对，每对最多比较 $20$ 次，时间复杂度为 $O(20n)$。
- 拓扑排序遍历所有出现过的节点和边，节点数不超过 $26$，边数不超过 $25$，因此可视为常数时间。
- 整体算法非常高效，完全满足题目要求。

## 注意事项

- 输入可能包含多组数据，以 `#` 分隔，代码已支持多组输入。
- 题目保证输入合法，即必然存在唯一拓扑排序，无需考虑多种顺序的情况。
- 输出时直接按拓扑排序顺序输出字符即可，无需额外分隔符。
