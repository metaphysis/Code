[UVa 210 Concurrency Simulator](https://blog.csdn.net/metaphysis/article/details/161043031)

## 题目分析

本题要求模拟单处理器系统中多个程序的并发执行。系统中有最多 $10$ 个程序，每个程序由不超过 $25$ 条语句组成，语句类型包括赋值（$\texttt{assignment}$）、输出（$\texttt{output}$）、加锁（$\texttt{lock}$）、解锁（$\texttt{unlock}$）和结束（$\texttt{end}$）。共有 $26$ 个共享变量（小写字母 `a` 到 `z`），初始值为 $0$。

每个语句执行需要固定的时间单位，每个程序被分配一个时间片（$\texttt{time quantum}$）。程序在时间片内连续执行，若时间片用完但当前语句未执行完，则该语句会执行完毕后才切换。程序按先进先出（$\texttt{FIFO}$）顺序在就绪队列中等待执行。

关键机制是互斥锁：$\texttt{lock}$ 和 $\texttt{unlock}$ 成对出现，不会嵌套。当某个程序成功执行 $\texttt{lock}$ 后，其他程序尝试执行 $\texttt{lock}$ 时会被放入阻塞队列末尾，并失去当前剩余的时间片。当执行 $\texttt{unlock}$ 时，阻塞队列头部的程序被移入就绪队列头部，之后它将重新执行之前失败的 $\texttt{lock}$ 语句。

## 解题思路

### 数据结构设计

使用结构体 `statement` 表示一条语句，包含：
- `programId`：所属程序编号
- `statementType`：语句类型（用常量 $0$ 到 $4$ 表示）
- `variableName`：变量名（用于赋值和输出）
- `variableValue`：赋值的常量值

每个程序是一个 `deque<statement>` 双端队列，便于从头部取出语句执行。就绪队列 `ready` 和阻塞队列 `blocked` 也都使用 `deque` 类型。

### 模拟流程

1. **初始化**：读入测试用例数，对每个用例读入程序数、各语句执行时间、时间片大小，然后读入每个程序的语句序列。
2. **变量存储**：用数组 `valueSetted[26]` 存储 $26$ 个变量的值，初始全为 $0$。
3. **执行模拟**：
   - 从就绪队列头部取出一个程序执行。
   - 每个程序在时间片内循环执行语句，每次执行扣减相应的时间。
   - 遇到 `lock` 时检查 `isLocked` 标志：若已锁定，则将当前程序（包含剩余语句）放入阻塞队列尾部，并退出执行；否则设置 `isLocked = true` 并继续。
   - 遇到 `unlock` 时检查阻塞队列：若非空，则将阻塞队列头部的程序移入就绪队列头部，然后清除 `isLocked` 标志。
   - 遇到 `end` 时程序结束，不再放回就绪队列。
   - 若时间片用完且程序未结束、未进入阻塞队列，则放回就绪队列尾部。
4. **输出**：每次执行输出语句时，按格式 `程序编号: 变量值` 输出。

### 注意事项

- 程序执行 $\texttt{lock}$ 失败时，原语句需要保留并放回程序头部（使用 `push_front`）。
- $\texttt{unlock}$ 时移入就绪队列的应是阻塞队列头部的程序，且该程序被移入就绪队列头部（而非尾部）。
- 两个测试用例之间需输出一个空行。

## 代码实现

```cpp
// Concurrent Simulator
// UVa ID: 210
// Verdict: Accepted
// Submission Date: 2016-01-18
// UVa Run Time: 0.395s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 语句类型常量
const int ASSIGNMENT = 0;
const int OUTPUT = 1;
const int LOCK = 2;
const int UNLOCK = 3;
const int END = 4;

// 语句结构体
struct statement {
    int programId;          // 程序 ID
    int statementType;      // 语句类型
    char variableName;      // 变量名称
    int variableValue;      // 变量值（仅用于赋值语句）
};

// 每个程序是一个双端队列，存储语句序列
typedef deque<statement> program;

int timeNeeded[END + 1];    // 每种语句执行所需时间
int timeQuantum;            // 时间片包含的单位时间数
bool isLocked = false;      // 当前是否有程序成功执行了 lock
int valueSetted[26];        // 存储 26 个变量的值（a~z）

// 模拟程序执行过程
void execute(deque < program > ready) {
    deque<program> blocked;  // 阻塞队列

    while (!ready.empty()) {
        program pRunning = ready.front();  // 取出队首程序
        ready.pop_front();

        int timeRemain = timeQuantum;      // 当前程序剩余时间片
        bool intoBlockedQueue = false;     // 是否进入阻塞队列

        while (timeRemain > 0) {
            statement sCurrent = pRunning.front();  // 取出当前要执行的语句
            pRunning.pop_front();

            switch (sCurrent.statementType) {
                case ASSIGNMENT:  // 赋值语句
                    valueSetted[sCurrent.variableName - 'a'] =
                        sCurrent.variableValue;
                    break;

                case OUTPUT:  // 输出语句
                    cout << sCurrent.programId << ": ";
                    cout << valueSetted[sCurrent.variableName - 'a'] << endl;
                    break;

                case LOCK:  // 加锁语句
                    if (isLocked)  // 已有程序锁定，当前程序需阻塞
                    {
                        pRunning.push_front(sCurrent);      // 保留当前语句
                        blocked.push_back(pRunning);        // 加入阻塞队列
                        timeRemain = 0;                     // 立即结束时间片
                        intoBlockedQueue = true;
                    }
                    else isLocked = true;  // 无锁，成功加锁
                    break;

                case UNLOCK:  // 解锁语句
                    if (!blocked.empty())  // 阻塞队列非空
                    {
                        program pNext = blocked.front();
                        blocked.pop_front();
                        ready.push_front(pNext);  // 移入就绪队列头部
                    }
                    isLocked = false;  // 释放锁
                    break;

                case END:  // 程序结束
                    timeRemain = 0;  // 结束时间片，不再放回队列
                    break;
            }

            // 扣除当前语句执行所需的时间
            timeRemain -= timeNeeded[sCurrent.statementType];
        }

        // 若程序未结束且未进入阻塞队列，则放回就绪队列尾部
        if (!pRunning.empty() && !intoBlockedQueue)
            ready.push_back(pRunning);
    }
}

// 解析一行语句，转换为 statement 结构体
statement parseToStatement(string line, int programId) {
    statement s;
    s.programId = programId;

    if (line.find('=') != line.npos)  // 赋值语句
    {
        istringstream iss(line);
        string blank;

        s.statementType = ASSIGNMENT;
        iss >> s.variableName >> blank >> s.variableValue;
    }
    else if (line == "end")  // 结束语句
    {
        s.statementType = END;
    }
    else if (line == "lock")  // 加锁语句
    {
        s.statementType = LOCK;
    }
    else if (line == "unlock")  // 解锁语句
    {
        s.statementType = UNLOCK;
    }
    else  // 输出语句，格式为 "print x"
    {
        s.statementType = OUTPUT;
        s.variableName = line[line.length() - 1];
    }

    return s;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);
    string line;
    int cases, numbers;
    bool startPrintBlankLine = false;
    // 读入测试用例数
    cin >> cases;
    while (cases-- > 0) {
        // 在两个测试用例输出之间输出空行
        if (startPrintBlankLine) cout << endl;
        else startPrintBlankLine = true;
        // 读入空行（用例间的空行）
        getline(cin, line);
        // 读入程序数、各语句执行时间及时间片大小
        cin >> numbers;
        for (int i = ASSIGNMENT; i <= END; i++) cin >> timeNeeded[i];
        cin >> timeQuantum;
        cin.ignore();  // 忽略换行符
        // 读入每个程序的语句序列
        int programId = numbers;
        deque < program > ready;
        while (numbers-- > 0) {
            deque < statement > program;
            while (getline(cin, line), line != "end")
                program.push_back(parseToStatement(line, programId - numbers));
            program.push_back(parseToStatement(line, programId - numbers));
            ready.push_back(program);
        }
        // 初始化所有变量为 0
        memset(valueSetted, 0, sizeof(valueSetted));
        // 开始模拟执行
        execute(ready);
    }
    return 0;
}
```
