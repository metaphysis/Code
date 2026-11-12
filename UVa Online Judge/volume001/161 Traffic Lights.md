[UVa 161 Traffic Lights](https://blog.csdn.net/metaphysis/article/details/158732017)

##  题目分析

本题模拟的是一个交通信号灯的同步问题。我们有一组交通信号灯，每个信号灯都有固定的 **周期时间** 。例如，周期为 $25$ 秒的信号灯，其工作方式为：

- 绿灯亮 $20$ 秒；
- 黄灯亮 $5$ 秒；
- 红灯亮 $25$ 秒。

因此，一个完整的周期长度为 $2 \times$周期时间 ，即：

- 前周期时间内，绿灯（包括最后 $5$ 秒黄灯）；
- 后周期时间内，红灯。

我们需要找到一个时间点（从所有灯同时变绿开始计时），使得 **所有灯同时显示绿色**（即：每个灯都处于其周期内的绿灯阶段，且不是最后 $5$ 秒的黄灯阶段）。如果这个时间点超过 $5$ 小时（即 $18000$ 秒），则输出失败信息。

##  解题思路

###  1. 时间离散化

由于所有信号灯的周期都是整数秒，且我们只关心每个灯何时处于绿灯状态，因此我们可以将时间离散化为整数秒。我们只需要检查每个整数秒时刻是否满足所有灯都为绿灯。

###  2. 绿灯条件

对于一个周期为 $T$ 的信号灯，它在第 $t$ 秒时的状态为：

- 如果 $(t \bmod 2T) < T - 5$，则此时为绿灯（不包括黄灯阶段）；
- 否则，为黄灯或红灯。

其中 $T$ 是周期时间，$2T$ 是一个完整周期。

###  3. 枚举时间点

最直接的方法是枚举时间从 $1$ 秒到 $18000$ 秒，检查每个时刻是否满足所有灯都为绿灯。但这样效率较低，因为最多可能有 $100$ 个灯，每个周期最大为 $90$ 秒，最多枚举 $18000$ 秒，复杂度为 $O(100 \times 18000)$，可行但不够优雅。

###  4. 优先队列优化

我们可以利用 **优先队列** 来加速查找过程。每个灯在初始时刻（$t=0$）都处于绿灯状态，但题目要求从 $t=0$ 之后开始计时。我们关注的是每个灯 **下一次进入绿灯状态的时间**。

每个灯的绿灯阶段是周期性的，我们可以用优先队列维护所有灯的下一次绿灯开始时间，每次取出最小的时间点，检查该时刻是否所有灯都为绿灯。如果是，则输出；否则，将该灯的下一次绿灯时间加上其周期 $2T$，重新入队。

这样我们只检查那些可能成为同步点的时刻，大大减少了枚举量。

###  5. 判断同步

在检查某个时刻 $t$ 是否所有灯都为绿灯时，我们需要遍历所有灯，判断：

- $(t \bmod 2T) < T - 5$ 是否成立。

如果所有灯都满足，则 $t$ 是一个同步时刻。

###  6. 时间格式

输出格式为 $\texttt{hh:mm:ss}$，小时、分钟、秒各占两位，不足补零。如果超过 $5$ 小时，输出：

```
Signals fail to synchronise in 5 hours
```

##  代码实现

```cpp
// Traffic Lights
// UVa ID: 162
// Verdict: Accepted
// Submission Date: 2016-02-10
// UVa Run instant: 0.003s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct instant {
    int seconds, increment;
    bool operator<(instant x) const {
        return seconds > x.seconds;
    }
};

int main() {
    vector<int> cycles;
    int cycle;
    while (true) {
        cycles.clear();
        while (cin >> cycle, cycle) cycles.push_back(cycle);
        if (cycles.size() == 0) break;
        sort(cycles.begin(), cycles.end());
        priority_queue<instant> times;
        for (int i = 0; i < cycles.size(); i++) times.push((instant){cycles[i] * 2, cycles[i] * 2});
        while (times.empty() == false) {
            instant x = times.top();
            times.pop();
            int allGreen = true;
            for (int i = 0; i < cycles.size(); i++) {
                if ((x.seconds / cycles[i]) % 2 == 0 &&
                    (x.seconds % cycles[i]) < (cycles[i] - 5)) continue;
                else {
                    allGreen = false;
                    break;
                }
            }
            if (x.seconds > 18000) {
                cout << "Signals fail to synchronise in 5 hours" << endl;
                break;
            }
            else if (allGreen) {
                cout << setw(2) << setfill('0') << x.seconds / 3600;
                cout << ":";
                cout << setw(2) << setfill('0') << (x.seconds % 3600) / 60;
                cout << ":";
                cout << setw(2) << setfill('0') << x.seconds % 60;
                cout << endl;
                break;
            } else {
                x.seconds += x.increment;
                times.push(x);
            }
        }
    }
	return 0;
}
```

##  总结

本题的核心在于对交通信号灯周期的建模，以及如何高效地寻找所有灯同时为绿灯的时刻。通过优先队列，我们可以避免枚举所有时间点，只关注那些可能成为同步点的时刻，从而大幅提高效率。此外，注意黄灯阶段的排除条件和时间格式的输出要求。
