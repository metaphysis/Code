[UVa 239 Time and Motion](https://blog.csdn.net/metaphysis/article/details/161212923)

## 题目分析

本题模拟了一种名为 “球钟” 的计时装置。该装置通过钢球在轨道上的移动来记录时间，其核心机制如下：

*   一个队列存放待使用的钢球。
*   三个栈（或轨道）分别表示分钟指示器（可容纳 $4$ 个球）、五分钟指示器（可容纳 $11$ 个球）和小时指示器（可容纳 $11$ 个可移动球，外加 $1$ 个固定球，用于显示 $1$ 到 $12$ 小时）。
*   每分钟，从队列头部取出一个球，并将其放入分钟指示器栈中。
*   当分钟指示器栈满（已有 $4$ 个球）时，放入第 $5$ 个球会触发该轨道的倾斜。此时，分钟栈中的 $4$ 个球按照**后进先出（$\texttt{LIFO}$）** 的顺序返回队列末尾，而触发倾斜的第 $5$ 个球则被移动到五分钟指示器栈中。
*   五分钟指示器和小时指示器的运作逻辑与此类似，满溢后会将球按 $\texttt{LIFO}$ 顺序退回队列，并将当前球移动到下一级轨道。

题目要求，对于给定的初始钢球数量 $N$（范围在 $27$ 到 $7000$ 之间），计算出球钟的钢球序列在经过多少**天**（以 $24$ 小时为周期，即 $1440$ 分钟）后，会首次回到其初始的排列顺序。

## 解题思路

解决这个问题的关键在于找到状态重复的周期。直接模拟直到状态重复可能会非常耗时，但通过观察，我们可以利用置换群（$\texttt{Permutation Group}$）的理论来高效求解。

1.  **模拟一个完整周期**：我们首先模拟一天（$24 \times 60 = 1440$ 分钟）的球钟运作。初始时，队列中包含编号为 $0$ 到 $N-1$ 的球。经过 $1440$ 次“取球-放球”操作后，队列中的球会形成一个全新的排列。此时，队列前端的球，就是最初位于位置 $i$ 的球经过一天后的新位置。我们记录这个映射关系，得到一个长度为 $N$ 的置换数组 `permutation`，其中 `permutation[i]` 表示原始第 `i` 个球在一天后所在的位置。

2.  **寻找循环节**：整个球钟的状态变化可以看作是一个置换的不断应用。根据置换群的性质，整个系统回到初始状态所需的最小周期，等于所有独立循环节长度的**最小公倍数（$\texttt{LCM}$）**。
    *   我们将 `permutation` 数组分解成若干个不相交的循环。例如，一个循环 $i \to permutation[i] \to permutation[permutation[i]] \to \dots \to i$ 的长度记为 `length`。
    *   该循环中的球每经过 `length` 天就会回到各自的原位。

3.  **计算结果**：最终所需的天数 `days` 就是所有循环节长度的 $\texttt{LCM}$。由于结果可能非常大，需要使用 $64$ 位整数（$\texttt{long long}$）来存储。在计算 $\texttt{LCM}(a, b)$ 时，为了防止溢出，我们采用公式 $\texttt{LCM}(a, b) = a / \texttt{GCD}(a, b) \times b$ 进行计算。

## 代码实现

```cpp
// Tempus et mobilius. Time and motion
// UVa ID: 239
// Verdict: Accepted
// Submission Date: 2016-05-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 计算最大公约数（GCD）
long long gcd(long long x, long long y)
{
    long long t;
    while (x % y)
    {
        t = x;
        x = y;
        y = t % y;
    }
    return y;
}

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n, n)
    {
        queue<int> balls;          // 待处理的球的队列
        stack<int> minute, five, hour; // 分钟、五分钟、小时指示器（栈）

        // 初始化：将编号为0到n-1的球放入队列
        for (int i = 0; i < n; i++)
            balls.push(i);

        // 模拟一天（24小时 = 1440分钟）的球钟运作
        for (int i = 0; i < 24 * 60; i++)
        {
            // 每分钟从队列头部取出一个球
            int ball = balls.front();
            balls.pop();

            // 放入分钟指示器栈
            if(minute.size() < 4)
                minute.push(ball);
            else // 分钟指示器已满（已有4个球）
            {
                // 将分钟栈中的4个球按后进先出顺序退回队列末尾
                while (minute.empty() == false)
                {
                    balls.push(minute.top());
                    minute.pop();
                }
                    
                // 将触发倾斜的第5个球放入五分钟指示器栈
                if (five.size() < 11)
                    five.push(ball);
                else // 五分钟指示器已满（已有11个球）
                {
                    // 将五分钟栈中的11个球按后进先出顺序退回队列末尾
                    while (five.empty() == false)
                    {
                        balls.push(five.top());
                        five.pop();
                    }
                        
                    // 将触发倾斜的第12个球放入小时指示器栈
                    if (hour.size() < 11)
                        hour.push(ball);
                    else // 小时指示器已满（已有11个可移动球）
                    {
                        // 将小时栈中的11个球按后进先出顺序退回队列末尾
                        while (hour.empty() == false)
                        {
                            balls.push(hour.top());
                            hour.pop();
                        }
                        
                        // 触发倾斜的第12个球也退回队列末尾
                        balls.push(ball);
                    }
                }
            }
        }

        // 经过一天的模拟后，balls队列中存储了新的排列。
        // permutation[i] 记录了原始第i个球在一天后的位置。
        int permutation[7010], visited[7010] = {};

        // 从队列中读取这个置换映射
        for (int i = 0; i < n; i++)
        {
            permutation[i] = balls.front();
            balls.pop();
        }
            
        // 计算所有循环节长度的最小公倍数（LCM）
        long long days = 1;
        for (int i = 0; i < n; i++)
            if (visited[i] == 0) // 找到一个未访问的球，即一个新循环的起点
            {
                int length = 1;   // 记录当前循环的长度
                visited[i] = 1;
                
                // 沿着置换追踪，直到回到起点
                for (int j = permutation[i]; j != i; j = permutation[j])
                {
                    visited[j] = 1;
                    length++;
                }
                
                // 计算当前总天数与当前循环长度的最小公倍数
                // 使用公式 LCM(a, b) = a / GCD(a, b) * b 防止溢出
                days = days / gcd(days, length) * length;
            }

        // 按照题目要求的格式输出结果
        cout << n << " balls cycle after " << days << " days.\n";
    }

    return 0;
}
```
