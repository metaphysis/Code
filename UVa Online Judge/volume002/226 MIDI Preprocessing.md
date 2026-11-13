[UVa 226 MIDI Preprocessing](https://blog.csdn.net/metaphysis/article/details/161087240)

## 问题分析

$\texttt{MIDI}$（乐器数字接口）是一种用于计算机与合成乐器之间通信的标准。本题中，我们需要处理简单的 $\texttt{MIDI}$ 程序，这些程序由一系列命令组成，每条命令包含**时间单位**、**命令类型**（`ON` 或 `OFF`）和**音符编号**。

然而，许多现有音乐无法直接翻译成这种程序形式。主要存在两类问题：

1. **重复开启问题**：当一个音符已经处于 `ON` 状态时，再次发送 `ON` 命令会被忽略。修复方法是在第二个 `ON` 命令之前 $1$ 个时间单位插入一个 `OFF` 命令。

2. **同时开启和关闭问题**：当 `ON` 和 `OFF` 命令出现在同一时间单位时，处理顺序会导致问题。修复方法是将 `OFF` 命令移动到对应 `ON` 命令之前 $1$ 个时间单位。

## 解题思路

本题的核心是**按音符编号分组处理**命令，因为不同音符的命令互不影响。

### 数据结构设计

```cpp
struct command {
    int time_unit;    // 时间单位
    int switches;     // 1 表示 ON，0 表示 OFF
    int note_number;  // 音符编号
    bool valid;       // 该命令是否有效
};
```

- 使用 `buffer` 映射（音符编号 $\to$ 命令列表）来暂存每个音符的命令序列。
- 使用 `counter` 记录当前处于 `ON` 状态的命令数量，用于判断音符是否已开启。

### 处理流程

1. **读取输入**：按行读取命令，直到遇到 `-1`（程序分隔符）或 `-2$`（程序终止符）。
2. **分类处理**：
   - 若命令为 `OFF`，直接加入缓冲区，计数器减 $1$。
   - 若命令为 `ON`，需要判断是否应直接加入或触发预处理：
     - 如果当前音符已有未配对的 `ON`（$counter > 0$）或
     - 缓冲区为空或
     - 当前时间与缓冲区最后一个命令时间相同
     - 则直接将命令加入缓冲区，计数器加 $1$。
     - 否则，调用 `preprocess` 处理当前缓冲区的命令序列，然后清空缓冲区并加入当前命令。
3. **预处理函数 `preprocess`**：
   - 将连续的 `ON` 和 `OFF` 命令配对（按输入顺序）。
   - 检查配对后的命令对，如果后一个 `ON` 的时间 $\le$ 前一个 `OFF` 的时间，则调整前一个 `OFF` 的时间为后一个 `ON` 的时间减 $1$。
   - 如果调整后的 `OFF` 时间等于对应 `ON$ 的时间，则标记这两个命令为无效（应被消除）。
   - 将有效的命令收集到全局命令列表中。
4. **排序输出**：对所有有效命令按时间排序，时间相同时 `ON` 排在 `OFF` 之前（因为题目要求先处理 `ON` 再处理 `OFF`，但输出时 `ON` 在前），音符编号小的在前。最后输出分隔符 `-1` 或 `-2`。

### 排序规则

在重载 `<` 运算符时：
- 首先按时间升序排列；
- 时间相同时，`ON`（$1$）排在 `OFF`（$0$）之前；
- 若命令类型相同，则按音符编号升序排列。

## 代码实现

```cpp
// MIDI Preprocessing
// UVa ID: 226
// Verdict: Accepted
// Submission Date: 2016-06-02
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int ON = 1, OFF = 0;          // ON 和 OFF 的常量表示

// 命令结构体，表示一条 MIDI 指令
struct command
{
    int time_unit;                  // 命令执行的时间单位
    int switches;                   // 命令类型：1 = ON, 0 = OFF
    int note_number;                // 音符编号，范围 1 到 127
    bool valid;                     // 该命令是否有效（预处理后可能被标记为无效）

    // 排序运算符，用于最终输出排序
    bool operator<(command x) const
    {
        if (time_unit != x.time_unit)
            return time_unit < x.time_unit;         // 首先按时间升序
        else if (switches != x.switches)
            return switches > x.switches;           // 时间相同，ON 排在 OFF 前面
        else
            return note_number < x.note_number;     // 最后按音符编号升序
    }
};

vector<command> commands;                           // 存储所有有效命令
map<int, vector<command>> buffer;                   // 按音符编号分组的临时缓冲区
map<int, int> counter;                              // 记录每个音符当前 ON 的数量

// 预处理函数：对某个音符的命令序列进行修复
void preprocess(vector <command> &program)
{
    vector<pair<command, command>> fixed;           // 存储配对的 (ON, OFF) 命令对
    command empty;                                  // 空命令，用作占位符

    // 将 ON 和 OFF 命令按顺序配对
    for (int i = 0, currentIndex = 0; i < program.size(); i++)
    {
        if (program[i].switches == ON)              // 遇到 ON 命令，创建新的命令对
            fixed.push_back(make_pair(program[i], empty));
        else                                         // 遇到 OFF 命令，填充到当前未完成的命令对中
        {
            fixed[currentIndex].second = program[i];
            currentIndex++;
        }
    }

    // 根据规则修复命令对
    for (int i = 1; i < fixed.size(); i++)
    {
        // 情况1：后一个 ON 的时间 <= 前一个 OFF 的时间
        // 需要将前一个 OFF 的时间调整到后一个 ON 的时间减 1
        if (fixed[i].first.time_unit <= fixed[i - 1].second.time_unit)
        {
            fixed[i - 1].second.time_unit = fixed[i].first.time_unit;
            fixed[i - 1].second.time_unit--;
            fixed[i - 1].second.switches = OFF;     // 确保是 OFF 命令

            // 保留当前 ON 命令（实际上是保留其类型）
            fixed[i].first.switches = ON;
        }

        // 情况2：调整后的 OFF 时间等于对应 ON 的时间
        // 这两个命令应被消除，标记为无效
        if (fixed[i - 1].second.time_unit == fixed[i - 1].first.time_unit)
        {
            fixed[i - 1].second.valid = false;
            fixed[i].first.valid = false;
        }
    }

    // 将所有有效的命令收集到全局命令列表中
    for (int i = 0; i < fixed.size(); i++)
    {
        if (fixed[i].first.valid)
            commands.push_back(fixed[i].first);
        if (fixed[i].second.valid)
            commands.push_back(fixed[i].second);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (true)
    {
        // 重置全局变量，准备处理新的 MIDI 程序
        commands.clear(), buffer.clear(), counter.clear();

        int time_unit_in, note_number_in;
        string switches_in;

        // 读取一个程序的所有命令，直到遇到 -1 或 -2
        while (getline(cin, line), line != "-1" && line != "-2")
        {
            command aCommand;
            istringstream iss(line);
            iss >> time_unit_in >> switches_in >> note_number_in;

            aCommand.time_unit = time_unit_in;
            aCommand.switches = switches_in == "ON";    // ON 为 true (1)，OFF 为 false (0)
            aCommand.note_number = note_number_in;
            aCommand.valid = true;                      // 初始时所有命令都有效

            // 如果命令是 OFF，直接加入缓冲区并减少计数器
            if (aCommand.switches == OFF)
            {
                buffer[aCommand.note_number].push_back(aCommand);
                counter[aCommand.note_number]--;
            }
            else    // 命令是 ON
            {
                // 条件判断：是否需要立即处理当前缓冲区的命令序列
                if (counter[aCommand.note_number] > 0 ||           // 已有未配对的 ON
                    buffer[aCommand.note_number].size() == 0 ||    // 缓冲区为空
                    aCommand.time_unit == buffer[aCommand.note_number].back().time_unit)  // 时间与最后命令相同
                {
                    // 直接加入缓冲区
                    buffer[aCommand.note_number].push_back(aCommand);
                    counter[aCommand.note_number]++;
                }
                else
                {
                    // 处理当前缓冲区的所有命令
                    preprocess(buffer[aCommand.note_number]);

                    // 清空缓冲区，加入当前命令作为新序列的开始
                    buffer[aCommand.note_number].clear();
                    buffer[aCommand.note_number].push_back(aCommand);
                    counter[aCommand.note_number] = 1;
                }
            }
        }

        // 处理剩余的缓冲区命令（每个音符最后未配对的命令序列）
        for (int i = 1; i <= 127; i++)
            if (buffer[i].size() > 0)
                preprocess(buffer[i]);

        // 对所有有效命令进行排序
        sort(commands.begin(), commands.end());
        
        // 输出修复后的 MIDI 程序
        for (auto it = commands.begin(); it != commands.end(); it++)
        {
            cout << (*it).time_unit << " " << ((*it).switches ? "ON" : "OFF");
            cout << " " << (*it).note_number << "\n";
        }

        // 输出程序分隔符
        cout << line << "\n";

        // 遇到 -2 表示所有程序处理完毕
        if (line == "-2")
            break;
    }

    return 0;
}
```

## 算法复杂度

- **时间复杂度**：$O(N \log N)$，其中 $N$ 为命令总数，主要来自最终的排序操作。每个音符的预处理是线性的。
- **空间复杂度**：$O(N)$，用于存储所有命令。

## 注意事项

1. 输入中命令的时间是**非递减**的，但不同音符的命令可能交错出现，因此需要按音符分组处理。
2. 当 `ON` 和 `OFF` 同时出现在同一时间时，根据题目描述，插入 `OFF` 的时间为对应 `ON` 时间减 $1$，如果结果与前一命令冲突，则需要进一步消除。
3. 题目保证每个 `ON` 都有匹配的 `OFF`，且每个时间、每个音符最多只有一个 `ON` 和一个 `OFF`。
