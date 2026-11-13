[UVa 213 Message Decoding](https://blog.csdn.net/metaphysis/article/details/161046213)

## 题目分析

本题是一种特殊的消息编码解码问题。编码方案包含两个部分：**头部（`header`）** 和**编码消息（`message`）**。

头部是一个字符串，其中的每个字符按照特定顺序映射到二进制**键（`key`）** 序列上。键序列的生成规则如下：

- 长度为 $1$ 的键有 $1$ 个：`0`
- 长度为 $2$ 的键有 $3$ 个：`00`、`01`、`10`
- 长度为 $3$ 的键有 $7$ 个：`000`、`001`、`010`、`011`、`100`、`101`、`110`
- 长度为 $n$ 的键有 $2^n - 1$ 个（排除全 $1$ 的键）

键序列按长度递增、同长度内按二进制数值递增的顺序，依次映射到头部的每个字符。头部中可能出现重复字符，这会导致多个键映射到相同字符。

编码消息由若干个**段（`segment`）** 组成：

- 每个段的前 $3$ 个比特表示该段中键的二进制长度 $L$（$1$ 到 $7$）
- 随后是若干个长度为 $L$ 的键，每个键对应头部的一个字符
- 段以 $L$ 个连续的 `1` 作为结束标记
- 整个消息以 `000` 终止（表示长度为 $0$ 的段）

消息中可能包含任意位置的换行符，需忽略。

## 解题思路

### 1. 建立键到索引的映射

由于键的最大长度为 $7$，我们可以预先计算所有可能的键（除全 $1$ 外）对应的索引值。索引从 $0$ 开始，与头部字符的位置一一对应。这样在解码时，可以直接根据键字符串查找对应的头部字符。

### 2. 处理输入

- 每个数据集的第一行是头部字符串
- 后续若干行是编码消息（可能跨多行），直到遇到下一个头部或文件结束
- 需要特殊处理空行或只有换行符的情况

### 3. 解码过程

1. 读取头部字符串
2. 累积消息行到缓冲区，去除其中的换行符
3. 循环处理消息：
   - 读取前 $3$ 位获取段长度 $L$
   - 若 $L = 0$，消息结束，输出换行并开始下一个数据集
   - 否则，继续读取长度为 $L$ 的键
   - 若遇到 $L$ 个连续的 `1`，表示该段结束，回到读取段长度的步骤
   - 否则，根据键查找头部字符并输出

### 4. 注意事项

- 使用 `bitset` 或字符串处理生成键的二进制表示
- 缓冲区可能一次性包含多个段的内容，需要循环处理
- 输出格式：每个数据集的解码结果占一行，结果之间没有空行

## 代码实现

```cpp
// Message Decoding
// UVa ID: 213
// Verdict: Accepted
// Submission Date: 2016-04-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 全局映射表：二进制键字符串 -> 对应的索引值（头部中的位置）
map<string, int> indexer;

int main() {
    // 预处理所有可能的键及其对应的索引
    // 对于长度 length = 1 到 7
    // 每个长度下可能的键数量为 (2^length - 1)，排除全1
    for (int i = 2, idx = 0, length = 1; length < 8; i *= 2, length++)
        for (int j = 0; j < (i - 1); j++)
        {
            bitset<8> n(j);                    // 将整数 j 转为二进制
            // 取低 length 位作为键，存入映射表，索引递增
            indexer[n.to_string().substr(8 - length, length)] = idx++;
        }

    string line, head, buffer;      // 输入行、头部字符串、消息缓冲区
    bool headReaded = false;        // 是否已读头部
    bool segmentEnded = false;      // 当前段是否结束
    bool segmentStartReaded = false;// 是否已读段长度
    int keyLength;                  // 当前段的键长度

    while (getline(cin, line)) {
        if (!headReaded) {
            // 读取头部字符串
            head = line;
            headReaded = true;
        } else {
            // 将每一行追加到消息缓冲区（忽略换行符，已通过 getline 移除）
            buffer += line;

        nextReading:               // 跳转标签，用于段结束时继续处理
            if (!segmentStartReaded) {
                // 缓冲区足够读取 3 位段长度时
                if (buffer.length() >= 3) {
                    // 将前 3 位二进制转为整数，表示键长度
                    keyLength = stoi(buffer.substr(0, 3), NULL, 2);
                    if (keyLength == 0) {
                        // 消息结束标志：000
                        headReaded = false;           // 准备读取下一个数据集的头部
                        segmentStartReaded = false;
                        buffer.clear();
                        cout << "\n";                 // 输出换行分隔不同数据集
                    } else {
                        // 移除已读的 3 位长度信息
                        buffer.erase(0, 3);
                        segmentStartReaded = true;    // 接下来开始读取段内键
                        segmentEnded = false;
                    }
                }
            }

            if (!segmentEnded) {
                // 不断读取长度为 keyLength 的键，直到缓冲区不够
                while (buffer.length() >= keyLength) {
                    string key = buffer.substr(0, keyLength);
                    if (key == string(keyLength, '1')) {
                        // 遇到全 1 的键，表示段结束
                        segmentEnded = true;
                        segmentStartReaded = false;
                        buffer.erase(0, keyLength);   // 移除结束标记
                        goto nextReading;             // 跳转读取下一个段的长度
                    } else {
                        // 普通键：通过映射表找到对应头部字符并输出
                        cout << head[indexer[key]];
                        buffer.erase(0, keyLength);   // 移除已处理的键
                    }
                }
            }
        }
    }

    return 0;
}
```

## 总结

本题的核心在于理解键序列的生成规则以及消息的分段结构。通过预处理建立键到索引的映射，可以高效地完成解码。输入处理需要注意忽略换行符，并正确处理跨行的消息内容。由于键长度不超过 $7$，预处理产生的映射表很小，内存和运行时间均非常充裕。
