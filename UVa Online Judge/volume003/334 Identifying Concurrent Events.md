[UVa 334 Identifying Concurrent Events](https://blog.csdn.net/metaphysis/article/details/161533434)

## 题目描述

在分布式计算机系统中，识别那些在时间上**并发**（即彼此之间没有时间顺序关系）的事件非常重要。一组并发事件可能同时尝试使用同一资源，这可能会引起问题。

非并发的事件可以在时间上排序。例如，如果事件 $e_1$ 总是在时间上先于事件 $e_2$，则 $e_1$ 和 $e_2$ 显然不是并发的。我们用符号 $e_1 \rightarrow e_2$ 表示 $e_1$ 先于 $e_2$。注意，先于关系具有传递性：如果 $e_1 \rightarrow e_2$ 且 $e_2 \rightarrow e_3$，则 $e_1 \rightarrow e_3$。

单个计算中的顺序事件不是并发的。例如，如果一个计算按顺序执行事件 $e_1$、$e_2$、$e_3$，则有 $e_1 \rightarrow e_2$ 和 $e_2 \rightarrow e_3$。

分布式系统中的计算通过发送消息进行通信。如果事件 $e_{\text{send}}$ 对应一个计算发送消息，事件 $e_{\text{rec}}$ 对应另一个计算接收该消息，则有 $e_{\text{send}} \rightarrow e_{\text{rec}}$（因为消息在发送之前不能被接收）。

### 输入格式

输入包含多个测试用例。每个测试用例首先是一个整数 $NC$，表示计算的数量。

对于每个计算，有一行包含一个整数 $NE_i$ 后跟 $NE_i$ 个事件名称。事件名称由 $1$ 到 $5$ 个字母数字字符组成，名称之间至少有一个空格。

在最后一个计算的事件描述之后，有一行包含一个整数 $NM$，表示计算之间发送的消息数量。

接下来 $NM$ 行，每行包含一对事件名称：发送事件和接收事件。这些名称必须在之前的事件列表中出现过。

最后一个测试用例后跟一行单独的 `0`。

### 输出格式

对于每个测试用例，输出：
- 测试用例编号
- 并发事件对的数量
- 任意两个并发事件对（如果有两个或以上）
- 如果只有一个并发事件对，只输出那一个
- 如果没有并发事件，输出相应信息

### 样例输入

```
2
2 e1 e2
2 e3 e4
1
e3 e1
3
3 one two three
2 four five
3 six seven eight
2
one four
five six
1
3 x y zee
0
2
2 alpha beta
1 gamma
1
gamma beta
0
```

### 样例输出

```
Case 1, 2 concurrent events: (e1,e4) (e2,e4)
Case 2, 10 concurrent events: (two,four) (two,five)
Case 3, no concurrent events.
Case 4, 1 concurrent events: (alpha,gamma)
```

---

## 题目分析

### 问题的本质

这是一个**偏序集**中的**不可比较元素对**计数问题。给定事件之间的偏序关系（先于关系），需要找出所有**不可比较**的事件对（即没有 $a \rightarrow b$ 也没有 $b \rightarrow a$ 的对）。

偏序关系由以下规则定义：
1. **顺序规则**：同一计算中的连续事件，前者先于后者
2. **通信规则**：消息发送事件先于对应的接收事件
3. **传递闭包**：先于关系具有传递性

### 图论建模

将每个事件视为图中的一个顶点。对于每个已知的先于关系 $a \rightarrow b$，在图中添加一条有向边 $a \rightarrow b$。

然后计算传递闭包：如果存在从 $a$ 到 $b$ 的路径，则 $a \rightarrow b$。

完成传递闭包后，检查所有事件对 $(i, j)$：
- 如果 `concurrent[i][j] == 0 && concurrent[j][i] == 0`，则 $i$ 和 $j$ 是并发的（不可比较）

### $\texttt{Floyd-Warshall}$ 算法

由于事件数量 $n \leq 200$，可以使用 $\texttt{Floyd-Warshall}$ 算法计算传递闭包：

```cpp
for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (concurrent[i][k] && concurrent[k][j])
                concurrent[i][j] = 1;
```

**注意**：此处 `concurrent` 数组名有些误导，它实际存储的是**先于关系**（precedes），而不是并发关系。

---
## 参考代码

```cpp
// Identifying Concurrent Events
// UVa ID: 334
// Verdict: Accepted
// Submission Date: 2016-08-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int nc, ne, nm, cases = 0;
    while (cin >> nc, nc)
    {
        // 事件名到索引的映射
        map<string, int> indexer;
        // 索引到事件名的映射
        map<int, string> names;
        // 先于关系矩阵（传递闭包）
        int concurrent[210][210] = {};
        int counter = 0;  // 事件总数
        string last_event, current_event;
        
        // 读取所有计算的事件序列
        for (int i = 1; i <= nc; i++)
        {
            last_event.clear();

            cin >> ne;
            for (int j = 1; j <= ne; j++)
            {
                cin >> current_event;

                // 注册新事件
                if (indexer.find(current_event) == indexer.end())
                {
                    indexer[current_event] = counter;
                    names[counter] = current_event;
                    counter++;
                }
                
                // 添加顺序关系：上一个事件 -> 当前事件
                if (last_event.length() > 0)
                    concurrent[indexer[last_event]][indexer[current_event]] = 1;
                last_event = current_event;
            }
        }
        
        // 读取消息通信关系
        cin >> nm;
        for (int j = 1; j <= nm; j++)
        {
            cin >> last_event >> current_event;
            concurrent[indexer[last_event]][indexer[current_event]] = 1;
        }
        
        // Floyd-Warshall 算法计算传递闭包
        for (int k = 0; k < counter; k++)
            for (int i = 0; i < counter; i++)
                for (int j = 0; j < counter; j++)
                    if (concurrent[i][k] && concurrent[k][j])
                        concurrent[i][j] = 1;

        // 查找并发事件对（不可比较的事件对）
        vector<pair<int, int>> concurrent_events;
        int concurrent_events_count = 0;
        for (int i = 0; i < counter; i++)
            for (int j = i + 1; j < counter; j++)
                if (!concurrent[i][j] && !concurrent[j][i])
                {
                    concurrent_events_count++;
                    // 只保留前两个并发对用于输出
                    if (concurrent_events.size() < 2)
                        concurrent_events.push_back(make_pair(i, j));
                }
                
        // 输出结果
        cout << "Case " << ++cases << ", ";
        if (concurrent_events_count == 0)
            cout << "no concurrent events.\n";
        else
        {
            cout << concurrent_events_count << " concurrent events:\n";
            for (int i = 0; i < concurrent_events.size(); i++)
            {
                cout << '(' << names[concurrent_events[i].first];
                cout << ',' << names[concurrent_events[i].second] << ") ";
            }
            cout << '\n';
        }
    }
    
    return 0;
}
```
