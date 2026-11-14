[UVa 370 Bingo](https://blog.csdn.net/metaphysis/article/details/161642248)

## 题目描述

宾果游戏是美国的一项伟大消遣方式。我们的宾果版本在一个 $5 \times 5$ 的方形卡片上进行。

你的任务是：编写一个程序，接受要放置在宾果卡片单元格中的整数。然后读取“叫号”的值（可能与卡片上的数字相同，也可能不同），一次一个，直到找到宾果或叫号结束。

**宾果条件**（满足任一即可）：
1. 一行中的所有五个元素都被叫到或是 $\texttt{FREE}$
2. 一列中的所有五个元素都被叫到或是 $\texttt{FREE}$
3. 四个角元素都被叫到或是 $\texttt{FREE}$
4. 任一对角线上的五个元素都被叫到或是 $\texttt{FREE}$

**注意**：卡片中值为 $0$ 的格子是 $\texttt{FREE}$，视为已被匹配。

### 输入格式

每个测试用例的前五行每行包含五个整数（$0 \leq V \leq 99$），按从左到右的顺序填入卡片对应行。接着是一系列叫号（$1 \leq C \leq 99$），最后一行以无效的 $0$ 结束。

### 输出格式

如果在叫号结束前没有找到宾果，则输出：
```
No BINGO on this card.
```

如果找到宾果，则忽略后续叫号，输出宾果通知，然后按行升序（行相同时按列升序）列出所有构成宾果的格子信息（行、列、值）。如果同时有多个宾果，按宾果类型顺序输出（行优先、列优先、角优先、对角线优先），中间无空行。

输出格式：
```
BINGO #N
R,C,V
R,C,V
...
```

### 样例输入

```
1 2 3 4 5
11 12 13 14 15
21 22 0 24 25
31 32 33 34 35
91 92 93 94 95
21
22
24
25
99
0
1 2 3 4 5
11 12 13 14 15
21 22 0 24 25
31 32 33 34 35
91 92 93 94 95
99
98
97
96
0
```

### 样例输出

```
BINGO #1
3,1,21
3,2,22
3,3,FREE
3,4,24
3,5,25

No BINGO on this card.
```

---

## 题目分析

### 问题的本质

这是一个**游戏状态模拟**问题。需要：
1. 读取宾果卡片的 $5 \times 5$ 矩阵
2. 按顺序处理叫号
3. 每次叫号后检查是否满足任一宾果条件
4. 找到宾果后输出构成该宾果的所有格子

### 宾果条件的表示

将 $13$ 种可能的宾果条件编码为：
- 行 $0 \sim 4$：共 $5$ 种
- 列 $5 \sim 9$：共 $5$ 种
- 角（四个角）：第 $10$ 种
- 主对角线：第 $11$ 种
- 副对角线：第 $12$ 种

每个格子属于多个宾果条件。例如，格子 $(0,0)$ 属于：
- 第 $0$ 行
- 第 $5$ 列
- 角条件
- 主对角线

### 匹配状态维护

使用一个数组 `sum[13]` 记录每个宾果条件当前的“总分”。初始时，每个格子有对应数值，`sum[cond]` 初始为该条件覆盖的所有格子数值之和。每次叫号后，如果该号在卡片上，则从对应的 `sum[cond]` 中减去该数值。当某个 `sum[cond] == 0` 时，表示该条件的所有格子都已被匹配（或为 $\texttt{FREE}$）。

### $\texttt{FREE}$ 格子处理

$\texttt{FREE}$ 格子（值为 $0$）视为已匹配。在初始化时，如果格子值为 $0$，则不计入 `sum[cond]`。

---

## 参考代码

```cpp
// Bingo
// UVa ID: 370
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.210s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> sum(13);               // 每个宾果条件的当前总和
vector<int> operation(25);         // 当前卡片数值（可能被置零）
vector<int> backup(25);            // 原始卡片数值（用于输出）
map<int, vector<int>> mapping;     // 格子位置 -> 所属宾果条件
map<int, vector<int>> indexer;     // 宾果条件 -> 包含的格子位置
map<int, vector<int>> location;    // 数值 -> 该数值出现的格子位置

// 输出指定宾果条件的所有格子
void display()
{
    for (int i = 0; i < 13; i++)
    {
        if (sum[i] == 0)
        {
            // 根据宾果类型输出标题
            if (i <= 4) cout << "BINGO #1" << endl;
            else if (i <= 9) cout << "BINGO #2" << endl;
            else if (i == 10) cout << "BINGO #3" << endl;
            else cout << "BINGO #4" << endl;

            for (auto pos : indexer[i])
            {
                cout << (pos / 5 + 1) << "," << (pos % 5 + 1) << ",";
                if (backup[pos] == 0) 
                    cout << "FREE";
                else 
                    cout << backup[pos];
                cout << endl;
            }
        }
    }
}

// 检查是否已宾果
bool isBingo()
{
    for (auto element : sum)
        if (element == 0)
        {
            display();
            return true;
        }
    return false;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    // 预计算每个格子所属的宾果条件
    for (int pos = 0; pos < 25; pos++)
    {
        int i = pos / 5, j = pos % 5;
        // 行条件
        mapping[pos].push_back(i);
        indexer[i].push_back(pos);

        // 列条件
        mapping[pos].push_back(j + 5);
        indexer[j + 5].push_back(pos);

        // 主对角线
        if (i == j)
        {
            mapping[pos].push_back(11);
            indexer[11].push_back(pos);
        }

        // 副对角线
        if (i + j == 4)
        {
            mapping[pos].push_back(12);
            indexer[12].push_back(pos);
        }

        // 四个角
        if ((i == 0 && j == 0) || (i == 0 && j == 4) ||
            (i == 4 && j == 0) || (i == 4 && j == 4))
        {
            mapping[pos].push_back(10);
            indexer[10].push_back(pos);
        }
    }
    
    int number, called;
    while (cin >> number)
    {
        // 初始化
        fill(sum.begin(), sum.end(), 0);
        location.clear();
        
        int readedNumber = 0, row, column;
        do
        {
            operation[readedNumber] = number;
            backup[readedNumber] = operation[readedNumber];
            location[number].push_back(readedNumber);
            
            // 如果不是 FREE 格子，加入各条件的和
            if (number != 0) {
                for (auto pos : mapping[readedNumber])
                    sum[pos] += number;
            }
            readedNumber++;
        } while (readedNumber < 25 && (cin >> number));

        // 检查初始状态是否已宾果（理论上不会，因为 FREE 格子可能凑齐一行）
        bool ignore = isBingo();
        
        // 处理叫号
        while (cin >> called, called)
        {
            if (ignore) continue;
            for (auto located : location[called])
            {
                operation[located] = 0;
                for (auto pos : mapping[located])
                    sum[pos] -= called;
            }
            ignore = isBingo();
        }

        if (!ignore) 
            cout << "No BINGO on this card." << endl << endl;
        else 
            cout << endl;
    }

    return 0;
}
```
