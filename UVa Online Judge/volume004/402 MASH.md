[UVa 402 M*A*S*H](https://blog.csdn.net/metaphysis/article/details/161736792)

## 题目描述

$\texttt{M*A*S*H}$ 题目描述了一个彩票淘汰游戏。有 $N$ 个人排成一列，编号从 $1$ 到 $N$。主持人有一叠牌，每张牌上有一个数字（$1$ 到 $11$ 之间）。淘汰过程如下：

1. 从队伍的第一个人开始，按顺序报数 $1, 2, 3, \dots$。
2. 当报数达到当前牌的数值时，该位置的人被淘汰出列。
3. 淘汰后，从下一个人开始重新从 $1$ 报数。
4. 当队伍末尾被报完后，无论最后报到了哪个数字，都取下一张牌，然后从队伍剩余的第一个人开始继续从 $1$ 报数。
5. 重复上述过程，直到只剩下 $X$ 个人为止，这 $X$ 个人就是幸运的“回家”人选。
6. 如果 $20$ 张牌用完时剩下的人数仍多于 $X$，则所有剩余的人都是幸运的。

给定 $N$、$X$ 和 $20$ 张牌的数字，需要输出所有幸运位置（即最终剩余的人的原始编号）。

## 输入格式

输入包含多组数据，每组数据占一行。每行包含 $22$ 个整数：
- 第 $1$ 个整数 $N$（$1 \le N \le 50$），表示参与彩票的人数。
- 第 $2$ 个整数 $X$（$1 \le X \le N$），表示幸运位置的数量。
- 接下来的 $20$ 个整数，表示牌堆中从上到下的 $20$ 张牌的数值（$1$ 到 $11$ 之间）。

输入以文件结束符（$\texttt{EOF}$）终止。

## 输出格式

对于每组数据，首先输出一行 `Selection #A`，其中 $A$ 是当前数据的序号（从 $1$ 开始计数）。下一行输出所有幸运位置的编号，按升序排列，以空格分隔。每组数据输出后跟一个空行。

## 样例

输入

```
10 2 3 5 4 3 2 9 6 10 10 6 2 6 7 3 4 7 4 5 3 2
47 6 11 2 7 3 4 8 5 10 7 8 3 7 4 2 3 9 10 2 5 3
```

输出

```
Selection #1
1 8

Selection #2
1 3 16 23 31 47
```

## 题目分析

本题的核心是实现一个**循环淘汰过程**，需要模拟报数和淘汰的完整流程。由于 $N \le 50$，可以直接使用数组或链表进行模拟。

关键点在于：
1. 淘汰规则是“报数到 $k$ 则淘汰”，其中 $k$ 是当前牌的值。
2. 每淘汰一个人后，重新从 $1$ 开始报数。
3. 当队伍末尾被报完后，取下一张牌，从队伍第一个人继续。
4. 如果 $20$ 张牌用完仍未淘汰到只剩 $X$ 人，则剩余所有人都是幸运的。

### 模拟方法的选择

由于 $N$ 很小，可以使用一个数组表示队伍中的人，用 $0$ 或负值标记已被淘汰的人。每次遍历数组，跳过已淘汰的人，累计报数，达到当前牌值时淘汰该位置。

这种方法的时间复杂度为 $O(\text{剩余人数} \times \text{淘汰次数})$，最坏情况下约为 $O(N^2)$，对于 $N \le 50$ 完全可行。

### 循环与边界处理

当报数到达队伍末尾时，需要根据当前报到的数字决定下一步：
- 如果恰好有人在最后一个位置被淘汰，则从队伍第一个人重新开始。
- 否则，记录当前报到的数字，下一轮从队伍第一个人继续累加。

更简单的做法是**线性扫描**：每次从头遍历整个数组，累计有效人数，达到目标值即淘汰，然后重新扫描。这种方法虽然看起来重复扫描很多次，但由于 $N$ 很小，完全可行。

## 解题思路

### 步骤一：读取输入

每组数据包含 $22$ 个整数，可以直接使用 $\texttt{istringstream}$ 从一行中解析所有整数。将 $N$ 和 $X$ 分别存储，将接下来的 $20$ 个数存入队列 $\texttt{queue<int> cards}$ 中，以便按顺序取出使用。

### 步骤二：初始化人员数组

使用 $\texttt{vector<int> person}$ 存储初始编号，可以使用 $\texttt{iota(person.begin(), person.end(), 1)}$ 快速填充 $1$ 到 $N$。标记淘汰的方式可以将其值设为 $0$。

### 步骤三：模拟淘汰过程

设 $\textit{remaining}$ 为当前剩余人数，初始为 $N$。

当 $\textit{remaining} > X$ 且牌堆非空时：
1. 取出一张牌，其值为 $\textit{token}$。
2. 从头扫描数组 $\textit{person}$，跳过值为 $0$ 的人。
3. 维护一个计数器 $\textit{counter}$，每遇到一个未被淘汰的人，$\textit{counter}$ 加 $1$。
4. 当 $\textit{counter} == \textit{token}$ 时，淘汰当前位置的人（设为 $0$），$\textit{remaining}$ 减 $1$，然后将 $\textit{counter}$ 重置为 $0$。
5. 如果在本次扫描中 $\textit{remaining}$ 降到了 $X$，立即跳出循环（不再使用剩余的牌）。
6. 如果扫描完整个数组后 $\textit{remaining}$ 仍未降到 $X$，继续下一轮扫描（使用下一张牌）。

注意：每次淘汰后，继续从当前位置的下一个人开始报数，**不用**重置扫描位置到开头。这正是题目描述的要求：“计数继续从下一个人开始”。上述线性扫描方法中，每次淘汰后继续扫描下一个位置，自然实现了这一规则。

### 步骤四：输出结果

遍历 $\textit{person}$ 数组，输出所有非零元素（即未被淘汰的人），即为幸运位置。注意输出格式：每个数据的结果前有一行 `Selection #A`，结果后有一个空行。

### 复杂度分析

- 时间复杂度：每淘汰一个人最多扫描 $N$ 个位置，最坏淘汰 $N-X$ 个人，故总时间复杂度 $O(N \times (N - X))$，即 $O(N^2)$，$N \le 50$ 时完全可接受。
- 空间复杂度：$O(N)$。

## 代码实现

```cpp
// M*A*S*H
// UVa ID: 402
// Verdict: Accepted
// Submission Date: 2016-07-18
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, n, x;
    
    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> n >> x;
        
        queue<int> cards;
        int number;
        while (iss >> number)
            cards.push(number);
            
        vector<int> person(n);
        iota(person.begin(), person.end(), 1);
        
        int remaining = n;
        
        while (remaining > x && cards.empty() == false)
        {
            int token = cards.front();
            cards.pop();
            
            int current = 0, counter = 0;
            while (current < n)
            {
                if (person[current] > 0)
                    counter++;

                if (counter == token)
                {
                    person[current] = 0;
                    remaining--;
                    
                    if (remaining == x)
                        goto skip;
                        
                    counter = 0;
                }

                current++;
            }
        }
        
        skip:
        cout << "Selection #" << ++cases << '\n';
        
        bool first = true;
        for (int i = 0; i < person.size(); i++)
        {
            if (person[i] == 0)
                continue;
            
            if (first)
                first = false;
            else
                cout << ' ';

            cout << person[i];
        }

        cout << "\n\n";
    }
    
    return 0;
}
```

## 总结

本题是一道经典的约瑟夫问题变种，主要考察以下知识点：

1. **循环淘汰的模拟**：需要正确处理“从当前位置继续”和“淘汰后重置计数”的规则。
2. **数组标记淘汰**：使用 $0$ 标记淘汰比实际删除元素更简单，避免频繁调整数组结构。
3. **多组数据输入处理**：使用 $\texttt{getline}$ 配合 $\texttt{istringstream}$ 读取不定长整数序列。
4. **提前终止条件**：当剩余人数达到 $X$ 时，应立即停止淘汰，即使牌堆中还有剩余牌也不再使用。

本题的易错点在于：
- 淘汰后计数从 $0$ 重置，而不是从 $1$。
- 判断是否已淘汰到 $X$ 人的时机：在淘汰一人后立即检查，如果 $\textit{remaining} == X$ 则跳出循环。
- 当 $20$ 张牌用完后，无论剩余多少人，所有剩余的人都是幸运的。

本题虽然模拟过程简单，但需要仔细理解题目描述中“从下一个人继续”的细节。通过数组标记法，可以有效避免链表操作带来的复杂度，同时保证逻辑清晰。