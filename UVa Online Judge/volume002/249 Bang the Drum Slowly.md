[UVa 249 Bang the Drum Slowly](https://blog.csdn.net/metaphysis/article/details/161250523)

## 题目分析

本题题目名称与 $1973$ 年出版的同名棒球小说《Bang the Drum Slowly》相同，但内容是关于早期计算机磁鼓存储器的指令执行时间优化问题。

### 问题背景

在早期的计算机系统中，主存储器（$\texttt{primary memory}$）常采用磁鼓（$\texttt{magnetic drum}$）作为存储介质。磁鼓是一个沿水平轴旋转的圆柱体，其外表面涂有磁性材料，通过固定的读写头（$\texttt{read/write heads}$）来访问数据。

磁鼓以恒定速度旋转，数据按顺序排列在圆周的磁道上，地址从 $1$ 到 $n$ 依次排列。当磁鼓旋转时，读写头下方经过的数据字可以被访问。由于磁鼓持续旋转，一条指令执行完毕后，读写头可能已经旋转到了其他位置，此时若要读取下一条指令，可能需要等待磁鼓旋转到目标位置，这就产生了旋转延迟（$\texttt{rotational delay}$）。

为了最小化这种延迟，早期机器的设计者采用了一种巧妙的策略：在每条指令中包含一个“下一条指令地址”字段。这样，汇编器（$\texttt{assembler}$）可以在编译时计算出最优的下一条指令位置，使得当前指令执行完毕时，下一条指令恰好到达读写头下方，从而消除旋转等待时间。

### 问题描述

本题要求计算简单程序（不含循环）的平均执行时间。我们考虑单读写头、单磁道的情况。磁道上的地址从 $1$ 到 $n$ 顺序编号。所有指令的执行时间相同，具体等于磁鼓旋转经过 $t$ 个字所需的时间。注意，$t$ 不包含从磁鼓读取指令的时间，也不包含当下一指令不在“最优”地址时可能需要的额外旋转延迟，但在计算平均执行时间时必须包含这些因素。

指令分为三种类型：

1. **终端指令（$\texttt{terminal instruction}$）**：没有下一条指令地址，程序执行到此结束。
2. **无条件指令（$\texttt{unconditional instruction}$）**：只有一个下一条指令地址。
3. **条件指令（$\texttt{conditional instruction}$）**：有两个下一条指令地址，每条分支被选择的概率相等（即各 $50\%$）。

### 输入格式

每个测试用例的输入格式如下：

- 第一行包含两个整数 $n$ 和 $t$，其中 $1 < n < 50$，$0 < t < n$。
- 接下来若干行，每行表示一条指令：首先是地址（$1$ 到 $n$），然后是该指令的下一条地址数量（$0$ 表示终端指令，$1$ 表示无条件指令，$2$ 表示条件指令），接着是对应数量的分支地址。
- 最后一条指令后，以单独一行的 $0$ 表示该测试用例结束。
- 当 $n = 0$ 且 $t = 0$ 时，输入结束。

### 输出格式

对每个测试用例，输出 `Case X. Execution time = Y.YYYY`，其中 $X$ 是测试用例编号（从 $1$ 开始），$Y.YYYY$ 是平均执行时间，精确到小数点后 $4$ 位。

### 关键假设

- 每个测试用例开始时，磁鼓的位置使得地址 $1$ 处的指令即将被读取。
- 程序从地址 $1$ 开始执行。
- 读取一条指令的时间为 $1$ 个时间单位。
- 至少存在一个终端指令（保证程序能够结束）。

## 解题思路

### 时间计算模型

设当前刚刚执行完地址为 $curr$ 的指令，而下一个要执行的指令地址为 $next$。在执行 $curr$ 指令的过程中，磁鼓一直在旋转。当 $curr$ 指令执行完毕后，读写头的位置并不是在 $curr$ 所在的位置，因为从读取 $curr$ 指令到执行完毕，磁鼓又旋转了 $t$ 个字。

因此，当前指令执行完毕后，读写头的位置为：

$$
head\_position = curr + t \pmod{n}
$$

更精确地说，当 $curr + t \leq n$ 时，新位置为 $curr + t$；否则，需要循环到地址 $1$，即 $curr + t - n$。

接下来需要读取地址 $next$ 处的指令。从当前读写头位置到 $next$ 地址所需的旋转延迟计算如下：

- 若 $head\_position < next$，则旋转延迟为 $next - head\_position$。
- 若 $head\_position \ge next$，则需要旋转到末尾再从头到 $next$，延迟为 $n - head\_position + next$。

得到旋转延迟后，再加上读取指令的时间 $1$ 个时间单位，就得到了从当前指令执行完毕到 $next$ 指令开始执行的时间。实际上，题目中的 $t$ 已经包含了指令执行时间，而旋转延迟和读取时间需要单独计算。

阅读通过代码可以发现，代码中的处理方式是：先计算从当前位置（即上一条指令执行完毕后的读写头位置）到 $next$ 的旋转延迟，然后加上 $t$（当前指令执行时间），再更新当前指令为 $next$，然后加上 $t$ 来更新读写头位置，最后递归处理后续指令。

### 递归计算方法

定义函数 $\text{execute}(current, next)$ 表示：当前刚刚执行完地址为 $current$ 的指令，读写头位于某个位置，接下来要执行地址为 $next$ 的指令，从此刻开始到程序结束所需的剩余执行时间。

实际上，通过代码中的 $\text{execute}(current, next)$ 函数，$current$ 表示当前读写头的位置（是上一条指令执行完毕后的位置），$next$ 表示下一条要执行指令的地址。函数首先计算旋转延迟：从 $current$ 旋转到 $next$ 所需时间，然后加上指令执行时间 $t$，然后更新当前执行地址为 $next$，再更新读写头位置为 $\text{next} + t$（模 $n$），最后根据 $next$ 地址处的指令类型继续执行。

### 记忆化搜索

由于程序可能包含条件分支，不同路径可能到达相同的 $(current, next)$ 状态。为了避免重复计算，使用记忆化数组 $\text{memoization}[i][j]$ 存储从状态 $(i, j)$ 开始的剩余执行时间。

对于状态 $(i, j)$，其递归关系如下：

1. **旋转延迟**：从 $i$ 到 $j$ 的距离。
2. **当前指令执行时间**：$t$。
3. **当前指令执行后读写头位置**：$\text{new\_head} = (j + t) \bmod n$（若结果等于 $0$ 则取 $n$）。
4. 根据地址 $j$ 处的指令类型：
   - 若为终端指令：返回旋转延迟 $+ t$（即当前指令执行完毕，程序结束）。
   - 若为无条件指令：剩余时间 $=$ 旋转延迟 $+ t + \text{execute}(new\_head, address1)$。
   - 若为条件指令：剩余时间 $=$ 旋转延迟 $+ t + \frac{\text{execute}(new\_head, address1) + \text{execute}(new\_head, address2)}{2}$。

### 初始状态

程序开始时，地址 $1$ 处的指令即将被读取，这意味着当前读写头位置正好在地址 $1$，而还没有执行任何指令。代码中调用 $\text{execute}(0, 1)$，$0$ 是一个虚拟的当前位置，表示初始状态。从 $0$ 到 $1$ 的旋转延迟计算为 $1 - 0 = 1$（因为 $0 < 1$），这恰好对应了读取第一条指令所需的 $1$ 个时间单位。

### 示例验证

以 $\texttt{Sample Input}$ 的第一个测试用例为例：$n = 10$，$t = 5$，指令为 `1 0`，即地址 $1$ 处是终端指令。程序从地址 $1$ 开始：

- 读取第一条指令需 $1$ 个时间单位。
- 执行指令需 $t = 5$ 个时间单位。
- 指令为终端，程序结束。

总时间 $= 1 + 5 = 6.0000$，与输出一致。

其他测试用例涉及无条件跳转和条件分支，递归计算即可得到正确结果。

## 复杂度分析

- 状态数量：$n \times n = O(n^2)$，由于 $n < 50$，状态数最多 $2500$。
- 每个状态计算为 $O(1)$。
- 总时间复杂度 $O(n^2)$，空间复杂度 $O(n^2)$。

## 代码实现

```cpp
// Bang the Drum Slowly
// UVa ID: 249
// Verdict: Accepted
// Submission Date: 2016-06-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int NO_ADDRESS = -1;  // 表示没有分支地址

struct address
{
    int address1, address2;  // 存储指令的分支地址
};

vector<address> instructions;  // 指令存储，下标为指令地址
double memoization[50][50];    // 记忆化数组，memoization[i][j] 表示从状态(i, j)开始的剩余时间
int n, t;                      // n: 磁道上的字数量，t: 指令执行时间（旋转过的字数）

double execute(int, int);

// 获取从状态(current_address, next_address)开始的执行时间，使用记忆化
double getTime(int current_address, int next_address)
{
    if (memoization[current_address][next_address] <= 0.0)
        memoization[current_address][next_address] = execute(current_address, next_address);
    return memoization[current_address][next_address];
}

// 模拟程序执行，使用记忆化存储结果，否则会超时
// current_address: 当前读写头位置（上一条指令执行完毕后的位置）
// next_address: 下一条要执行指令的地址
double execute(int current_address, int next_address)
{
    // 如果已经计算过，直接返回
    if (memoization[current_address][next_address] > 0.0)
        return memoization[current_address][next_address];
        
    // 计算旋转延迟：从 current_address 旋转到 next_address 所需时间
    double elapsed = 0.0;
    if (current_address < next_address)
        elapsed += (next_address - current_address);
    else
        elapsed += (n - current_address + next_address);

    // 加上当前指令的执行时间 t
    elapsed += t;
    
    // 更新当前执行地址为 next_address
    current_address = next_address;
    
    // 当前指令执行完毕后，读写头向前移动 t 个位置
    current_address += t;
    current_address = (current_address > n) ? (current_address - n) : current_address;

    // 根据下一条指令的类型继续执行
    // 终端指令（address1 为 0 表示无分支）
    if (instructions[next_address].address1 > 0 && instructions[next_address].address2 == NO_ADDRESS)
        elapsed += getTime(current_address, instructions[next_address].address1);
    // 条件指令（有两个分支）
    else if (instructions[next_address].address1 > 0 && instructions[next_address].address2 > 0)
    {
        double time1 = getTime(current_address, instructions[next_address].address1);
        double time2 = getTime(current_address, instructions[next_address].address2);
        elapsed += (time1 + time2) / 2.0;  // 两条分支等概率，取平均值
    }
    // 终端指令的情况：address1 为 0，直接返回，不需要额外处理

    return elapsed;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int cases = 0;
    while (cin >> n >> t, n && t)  // 输入 n 和 t，均为 0 时结束
    {
        instructions.resize(n + 1);  // 地址从 1 到 n
        for (int i = 1; i <= n; i++)
        {
            instructions[i].address1 = NO_ADDRESS;
            instructions[i].address2 = NO_ADDRESS;
        }

        int indexer, addresses;
        // 读取指令，地址为 0 表示当前测试用例的指令输入结束
        while (cin >> indexer, indexer > 0)
        {
            cin >> addresses;  // 读取分支地址数量

            // 根据分支数量读取对应地址
            instructions[indexer].address1 = addresses;
            if (addresses >= 1)
                cin >> instructions[indexer].address1;
            if (addresses >= 2)
                cin >> instructions[indexer].address2;
        }

        // 初始化记忆化数组
        for (int i = 0; i < 50; i++)
            for (int j = 0; j < 50; j++)
                memoization[i][j] = 0.0;
                
        // 从初始状态开始计算平均执行时间
        // 初始读写头位于位置 1 即将读取指令，用 0 表示“当前位置”
        double execution_time = execute(0, 1);
        
        // 输出结果
        cout << "Case " << ++cases << ". Execution time = ";
        cout << fixed << setprecision(4) << execution_time << endl;
    }

    return 0;
}
```

## 总结

本题通过记忆化搜索和递归模拟磁鼓存储器的指令执行过程，计算了包含条件分支的程序的平均执行时间。关键在于正确建模旋转延迟、指令读取时间和指令执行时间的关系，并利用动态规划的思想避免重复计算。题目虽有一定复杂度，但理解磁鼓的物理特性和时间计算模型后，算法实现较为直接。
