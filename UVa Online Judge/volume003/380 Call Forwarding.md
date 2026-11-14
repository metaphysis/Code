[UVa 380 Call Forwarding](https://blog.csdn.net/metaphysis/article/details/161673534)

## 题目描述

得益于计算机技术，电话系统的功能在过去十年中得到了极大的增强。我们有自动菜单、复杂的应答机、电话会议功能、群组寻址等等。公司电话系统的一个常见功能是设置呼叫转移。

$\texttt{NHC}$ 公司的电话都有四位数字的分机号。员工可以通过电话界面输入信息来设置呼叫转移。输入信息包括：他们的分机号、离开时间、离开时长以及呼叫应转移到的目标分机号。

约束条件：
- 分机号为四位数字，$0000$ 和 $9999$ 保留特殊用途
- 时间以小时为单位，从每年元旦午夜 $0000$ 开始计时，最大为 $8784$（$366 \times 24$）
- 呼叫转移系统在每年年初完全重置
- 用户在 $X$ 时刻设置的时长为 $Y$ 的转移，在 $X$ 到 $X+Y$ 时间范围内有效（包含端点）
- 用户不会提交重叠时间的请求

尽管用户从自身角度输入正确、清晰、不重叠的信息，但如果请求形成循环转发（如 $A$ 转给 $B$，$B$ 转给 $C$，$C$ 转给 $A$），则会发生退化情况。此时，系统会将此类呼叫转移到特殊分机 $9999$。

### 输入格式

第一行包含整数 $N$（$1 \leq N \leq 10$），表示要模拟的呼叫转发系统数量。

每个系统由 $0$ 到 $100$ 行请求组成，格式为 `source time duration target`。一行以 `0000` 作为 `source` 表示该部分输入结束。

然后是 $1$ 条或多条呼叫记录，格式为 `time extension`，时间非递减。一行以 `9000` 作为 `time` 表示该部分输入结束。

### 输出格式

第一行输出 `CALL FORWARDING OUTPUT`。然后每个系统输出 `SYSTEM N` 标题，之后为每个呼叫输出一行，格式为 `AT dddd CALL TO dddd RINGS dddd`。最后一行输出 `END OF OUTPUT`。

### 样例输入

```
2
1111 0100 0200 2222
1111 0301 0500 4444
2222 0200 0200 3333
3333 0250 1000 1111
7777 1000 2000 7777
0000
0050 1111
0150 1111
0200 1111
0225 2222
0270 1111
0320 1111
0320 3333
0900 3000
1250 3333
1250 7777
9000
0000
3000 1111
9000
```

### 样例输出

```
CALL FORWARDING OUTPUT
SYSTEM 1
AT 0050 CALL TO 1111 RINGS 1111
AT 0150 CALL TO 1111 RINGS 2222
AT 0200 CALL TO 1111 RINGS 3333
AT 0225 CALL TO 2222 RINGS 3333
AT 0270 CALL TO 1111 RINGS 9999
AT 0320 CALL TO 1111 RINGS 4444
AT 0320 CALL TO 3333 RINGS 4444
AT 0900 CALL TO 3000 RINGS 3000
AT 1250 CALL TO 3333 RINGS 1111
AT 1250 CALL TO 7777 RINGS 9999
SYSTEM 2
AT 3000 CALL TO 1111 RINGS 1111
END OF OUTPUT
```

---

## 题目分析

### 问题的本质

这是一个**呼叫转移链追踪**问题。需要：
1. 存储每个分机在不同时间段的转发目标
2. 对于每个呼叫，根据呼叫时间确定当前有效的转移规则
3. 沿着转移链追踪，直到找到最终响铃的分机
4. 检测循环转发，将循环中的呼叫导向 $9999$

### 数据结构

使用 `map<string, vector<item>>` 存储每个分机的转发规则。每个规则包含起止时间和目标分机。

### 追踪算法

对于呼叫 `(time, extension)`：
1. 设当前分机 `current = extension`
2. 使用 `set<string>` 记录已访问的分机，用于检测循环
3. 当 `current` 有有效的转发规则时：
   - 如果 `target` 已在访问集合中，则循环，最终为 `9999`
   - 否则，将 `current` 加入集合，移动到 `target`
4. 输出最终分机

---
## 参考代码

```cpp
// Call Forwarding
// UVa ID: 380
// Verdict: Accepted
// Submission Date: 2016-07-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct item
{
    string source, time, duration, target;
    int start, end;
};

map<string, vector<item>> items;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    cout << "CALL FORWARDING OUTPUT" << endl;
    for (int i = 1; i <= cases; i++)
    {
        items.clear();
        
        cout << "SYSTEM " << i << endl;
        string source, time, duration, target, extension;
        int start, end;
        
        // 读取转发规则
        while (cin >> source, source != "0000")
        {
            cin >> time >> duration >> target;
            start = stoi(time);
            end = start + stoi(duration);
            items[source].push_back({source, time, duration, target, start, end});
        }
        
        // 处理呼叫
        while (cin >> time, time != "9000")
        {
            cin >> extension;
            
            int calling_time = stoi(time);
            string next_extension = extension;
            
            set<string> called;  // 记录已访问的分机，用于检测循环
            while (items.find(next_extension) != items.end())
            {
                bool get_out = true;
                // 查找当前分机在呼叫时间的有效转发规则
                for (auto data : items[next_extension])
                    if (calling_time >= data.start && calling_time <= data.end)
                    {
                        if (called.find(data.target) == called.end())
                        {
                            called.insert(data.target);
                            next_extension = data.target;
                            get_out = false;
                        }
                        else
                        {
                            // 发现循环
                            get_out = true;
                            next_extension = "9999";
                        }
                        break;
                    }
                    
                if (get_out)
                    break;
            }

            cout << "AT " << time << " CALL TO " << extension << " RINGS " << next_extension << endl;
        }
    }
    cout << "END OF OUTPUT" << endl;
    
    return 0;
}
```
