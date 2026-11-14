[UVa 362 18000 Seconds Remaining](https://blog.csdn.net/metaphysis/article/details/161611286)

## 题目描述

许多文件传输程序的一个功能是能够估计传输剩余时间。这些程序根据剩余的字节数和前几秒的传输速率来估计剩余时间。你需要编写一个程序来模拟这种行为。

### 输入格式

输入由多个数据集组成，每个数据集描述一个文件传输。每个数据集的第一行是一个非负整数，表示文件的大小（字节数）。后续行是每秒传输的字节数（均为非负整数）。所有传输字节的总和等于文件的大小。

输入结束由文件大小为 $0$ 的数据集表示（该数据集不处理）。

### 输出格式

每个数据集的输出应以一行开头，包含数据集编号和正在传输的文件大小。然后，在传输过程中，每 $5$ 秒输出一次估计剩余秒数的更新行。

估计剩余秒数的方法：
1. 确定前 $5$ 秒的传输速率（字节/秒）
2. 如果在此期间没有传输任何字节，则传输停滞（$\texttt{stalled}$），程序应报告此情况
3. 否则，用剩余字节数除以前 $5$ 秒的传输速率，估算剩余秒数
4. 报告剩余秒数为整数，**向上取整**

传输结束时，输出一行，显示传输所需的总秒数。

每个数据集输出后跟一个空行。

### 样例输入

```
100
10
20
20
0
10
0
10
0
10
0
20
200
60
30
100
10
50
5
5
5
5
25
0
0
0
0
0
0
0
0
0
0
1
1
1
1
1
0
```

### 样例输出

```
Output for data set 1, 100 bytes:
   Time remaining: 4 seconds
   Time remaining: 5 seconds
Total time: 11 seconds

Output for data set 2, 200 bytes:
Total time: 4 seconds

Output for data set 3, 50 bytes:
   Time remaining: 1 seconds
   Time remaining: stalled
   Time remaining: stalled
   Time remaining: 0 seconds
Total time: 20 seconds
```

---

## 题目分析

### 问题的本质

这是一个**模拟与计算**问题。需要模拟文件传输过程，每 $5$ 秒根据前 $5$ 秒的平均速率估算剩余时间。

### 关键点

- 每秒输入一个字节数（可能为 $0$）
- 每 $5$ 秒输出一次估计
- 估算公式：$\lceil \frac{\text{剩余字节}}{\text{前 5 秒字节数}} \times 5 \rceil$？实际上速率是字节/秒，剩余秒数 = 剩余字节 / 速率
- 速率 = 前 $5$ 秒的字节总数 / $5$（字节/秒）
- 因此剩余秒数 = 剩余字节 / (前 $5$ 秒字节数 / 5) = $5 \times$ 剩余字节 / 前 $5$ 秒字节数
- 向上取整

### 边界情况

- 如果前 $5$ 秒没有传输任何字节（`bytesInFiveSeconds == 0`），输出 `stalled`
- 传输结束时，需要输出总时间
- 如果传输正好在第 $5$ 秒结束时完成，是否输出估计？根据样例，在完成的那一秒不输出估计？实际上，当 `transfered == n` 时立即跳出循环，不会输出那个整秒的估计

---
## 参考代码

```cpp
// 18,000 Seconds Remaining
// UVa ID: 362
// Verdict: Accepted
// Submission Date: 2016-07-01
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    int n, transfered, bytes, bytesInFiveSeconds, seconds, cases = 0;
    while (cin >> n, n)
    {
        // 初始化
        transfered = 0;
        bytesInFiveSeconds = 0;
        seconds = 0;
        
        cout << "Output for data set " << ++cases << ", " << n << " bytes:" << "\n";

        // 逐秒处理
        while (cin >> bytes)
        {
            seconds++;
            transfered += bytes;
            bytesInFiveSeconds += bytes;

            // 每 5 秒输出一次估计
            if (seconds % 5 == 0)
            {
                cout << "   Time remaining: ";
                if (bytesInFiveSeconds == 0)
                    cout << "stalled" << "\n";
                else
                {
                    // 向上取整：(a + b - 1) / b
                    int remaining = (5 * (n - transfered) + bytesInFiveSeconds - 1) / bytesInFiveSeconds;
                    cout << remaining << " seconds" << "\n";
                }
                bytesInFiveSeconds = 0;  // 重置计数器
            }

            // 传输完成，退出循环
            if (transfered == n)
                break;
        }

        // 输出总时间
        cout << "Total time: " << seconds << " seconds" << "\n";
        cout << endl;  // 数据集间空行
    }

    return 0;
}
```
