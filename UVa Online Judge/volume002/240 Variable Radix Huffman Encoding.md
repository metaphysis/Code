UVa 240 Variable Radix Huffman Encoding](https://blog.csdn.net/metaphysis/article/details/161245610)

## 题目分析

本题是经典哈夫曼编码问题的一种扩展。在标准的哈夫曼编码中，我们每次合并两个频率最小的节点（$R = 2$），而在可变基数哈夫曼编码中，每次合并 $R$ 个频率最小的节点，其中 $R$ 是目标字母表的大小（取值范围为 $2$ 到 $10$）。

### 核心要点

1. **编码规则**：每次将 $R$ 个频率最小的符号（或组合符号）合并为一个新节点，新节点的频率为这些节点频率之和。合并时，为这 $R$ 个节点分配目标符号 $0$ 到 $R-1$，其中频率最小的节点分配 $0$，次小的分配 $1$，依此类推。若频率相同，则字母表中靠前者分配较小的目标符号。

2. **虚拟符号的处理**：由于每次合并将 $R$ 个节点变为 $1$ 个节点，总共会减少 $R-1$ 个节点。为了使最终能够恰好合并为 $1$ 个节点，初始节点数 $N$ 应满足：
   
   $$N = k \times (R-1) + R, \quad k \text{ 为非负整数}$$
   
   如果 $N$ 不满足该条件，需要添加频率为 $0$ 的虚拟符号。这些虚拟符号不参与最终输出，在比较时被视为“晚于”任何真实字母。

3. **比较规则**：当频率相同时，选择索引较小的节点（即字母表中出现较早的字母）。对于组合符号，其“索引”取组合中最早字母的索引。

4. **编码构建**：编码是从叶子节点向根节点反向构建的。每次合并时，在当前节点的编码前添加对应的目标符号，最后得到的编码即为哈夫曼编码。

5. **平均长度计算**：
   
   $$\text{平均长度} = \frac{\sum_{i=1}^{N} f_i \times len_i}{\sum_{i=1}^{N} f_i}$$
   
   其中 $len_i$ 是第 $i$ 个符号的编码长度，$f_i$ 是频率。

## 解题思路

### 数据结构设计

为了实现可变基数哈夫曼编码，我们需要设计两个结构体：

- `symbol`：表示原始符号，包含频率、字母和编码字符串。
- `node`：表示哈夫曼树中的节点，包含索引、频率和该节点包含的所有符号列表。

使用优先队列（最小堆）来维护当前所有节点，以便每次快速取出频率最小的 $R$ 个节点。

### 算法步骤

#### 第一步：读取输入并初始化

对每组数据，读取 $R$、$N$ 和 $N$ 个频率值。将每个字母 $A, B, C, \ldots$ 封装为节点并放入优先队列中。

```cpp
for (int i = 0; i < N; i++) {
    cin >> frequency;
    symbol aSymbol;
    aSymbol.frequency = frequency;
    aSymbol.letter = 'A' + i;
    node aNode;
    aNode.index = i;
    aNode.frequency = frequency;
    aNode.symbols.push_back(aSymbol);
    H.push(aNode);
}
```

#### 第二步：添加虚拟符号

计算需要添加的虚拟符号数量。根据公式 $N = k \times (R-1) + R$，当 $N - R$ 除以 $R-1$ 有余数时，需要添加虚拟符号。

```cpp
int nullNumber = N - R;
if (nullNumber <= 0) {
    while (nullNumber < 0) {
        node aNode;
        aNode.index = N;
        aNode.frequency = 0;
        H.push(aNode);
        nullNumber++;
    }
} else {
    nullNumber %= (R - 1);
    if (nullNumber > 0) {
        while (nullNumber < (R - 1)) {
            node aNode;
            aNode.index = N;
            aNode.frequency = 0;
            H.push(aNode);
            nullNumber++;
        }
    }
}
```

虚拟符号的索引统一设为 $N$（大于任何真实字母的索引），这样可以保证在频率相同时，虚拟符号被排在真实字母之后。

#### 第三步：构建哈夫曼树

当优先队列中节点数大于 $1$ 时，重复以下操作：

1. 从优先队列中取出 $R$ 个频率最小的节点（如果队列中不足 $R$ 个，则取全部）。
2. 计算这些节点的频率之和，作为新节点的频率。
3. 记录这些节点中最小的索引，作为新节点的索引（用于比较）。
4. 为每个被取出的节点中的每个符号，在其编码前添加对应的目标符号（$0$ 到 $R-1$）。
5. 将所有符号收集到一个新的符号列表中，创建新节点并压入优先队列。

```cpp
while (H.size() > 1) {
    node last;
    last.index = H.top().index;
    int frequencies = 0;
    vector<symbol> collection;
    
    for (int i = 0; i < R; i++) {
        node front = H.top();
        H.pop();
        
        if (front.index < last.index)
            last.index = front.index;
        
        frequencies += front.frequency;
        
        for (int j = 0; j < front.symbols.size(); j++) {
            string code = front.symbols[j].code;
            code.insert(code.begin(), '0' + i);
            front.symbols[j].code = code;
            collection.push_back(front.symbols[j]);
        }
    }
    
    last.frequency = frequencies;
    last.symbols = collection;
    H.push(last);
}
```

#### 第四步：输出结果

从优先队列中取出最终的根节点，对其中的符号按字母顺序排序，然后计算平均编码长度并输出。

```cpp
node result = H.top();
sort(result.symbols.begin(), result.symbols.end());

int total = 0, frequencies = 0;
for (int i = 0; i < result.symbols.size(); i++) {
    total += result.symbols[i].frequency * result.symbols[i].code.length();
    frequencies += result.symbols[i].frequency;
}

double aveLength = (double)total / frequencies;
cout << "Set " << ++cases << "; average length ";
cout << fixed << setprecision(2) << aveLength << endl;
for (int i = 0; i < result.symbols.size(); i++) {
    cout << "    " << result.symbols[i].letter;
    cout << ": " << result.symbols[i].code << endl;
}
cout << endl;
```

### 比较器的设计

优先队列默认是最大堆，我们想要的是最小堆，因此重载 `operator<` 使其按频率升序排列，频率相同时按索引升序排列：

```cpp
bool operator<(node y) const {
    if (frequency != y.frequency)
        return frequency > y.frequency;
    else
        return index > y.index;
}
```

## 复杂度分析

- 时间复杂度：假设 $N$ 为符号个数，每次合并减少 $R-1$ 个节点，总共需要合并 $\frac{N-1}{R-1}$ 次，每次合并需要 $O(\log N)$ 的优先队列操作，总时间复杂度为 $O(N \log N)$。
- 空间复杂度：$O(N)$，用于存储节点和符号信息。

## 示例验证

以题目中的第一个样例输入为例：

```
2 5 5 10 20 25 40
```

- $R = 2$，$N = 5$，频率为 $5, 10, 20, 25, 40$。
- 按照算法构建哈夫曼树，得到编码：$\texttt{A: 1100}$，$\texttt{B: 1101}$，$\texttt{C: 111}$，$\texttt{D: 10}$，$\texttt{E: 0}$。
- 平均长度：$\frac{4 \times 5 + 4 \times 10 + 3 \times 20 + 2 \times 25 + 1 \times 40}{5+10+20+25+40} = \frac{20 + 40 + 60 + 50 + 40}{100} = \frac{210}{100} = 2.10$。

与样例输出完全一致。

## 注意事项

1. 虚拟符号的添加逻辑需要仔细处理，确保最终节点数满足合并条件。
2. 编码拼接是反向的：每次在编码字符串的**开头**添加新的目标符号。
3. 输出格式要求每个测试用例后有一个空行，字母与编码之间要有冒号和空格。
4. 平均长度需要四舍五入保留两位小数。

## 完整代码

```cpp
// Variable Radix Huffman Encoding
// UVa ID: 240
// Verdict: Accepted
// Submission Date: 2016-05-25
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 符号结构体，表示原始字母及其编码
struct symbol
{
    int frequency;          // 频率
    char letter;            // 字母（A, B, C, ...）
    string code;            // 哈夫曼编码

    // 按字母顺序排序
    bool operator<(symbol y) const
    {
        return letter < y.letter;
    }
};

// 树节点结构体，表示哈夫曼树中的节点
struct node
{
    int index;                      // 节点的索引（用于比较）
    int frequency;                  // 节点频率
    vector<symbol> symbols;         // 该节点包含的所有符号

    // 优先队列的比较器（最小堆）
    bool operator<(node y) const
    {
        if (frequency != y.frequency)
            return frequency > y.frequency;     // 频率小的优先级高
        else
            return index > y.index;             // 索引小的优先级高
    }
};

int main(int argc, char *argv[])
{
    int R, N, cases = 0;

    while (cin >> R, R)                         // 读取R，若R=0则结束
    {
        cin >> N;                               // 读取符号个数

        priority_queue<node> H;                 // 优先队列（最小堆）

        int frequency;
        // 读取N个频率，创建对应的节点
        for (int i = 0; i < N; i++)
        {
            cin >> frequency;

            symbol aSymbol;
            aSymbol.frequency = frequency;
            aSymbol.letter = 'A' + i;           // 字母从A开始

            node aNode;
            aNode.index = i;                    // 索引即字母序号
            aNode.frequency = frequency;
            aNode.symbols.push_back(aSymbol);

            H.push(aNode);
        }

        // 添加虚拟符号（频率为0），使节点数满足合并条件
        int nullNumber = N - R;

        if (nullNumber <= 0)
        {
            // 节点数不足R，需要添加虚拟符号直到节点数为R
            while (nullNumber < 0)
            {
                node aNode;
                aNode.index = N;                // 虚拟符号索引设为N（大于任何真实字母）
                aNode.frequency = 0;
                H.push(aNode);
                nullNumber++;
            }
        }
        else
        {
            // 计算需要补充的虚拟符号数量
            nullNumber %= (R - 1);
            if (nullNumber > 0)
            {
                while (nullNumber < (R - 1))
                {
                    node aNode;
                    aNode.index = N;
                    aNode.frequency = 0;
                    H.push(aNode);
                    nullNumber++;
                }
            }
        }

        // 构建哈夫曼树，直到只剩一个节点（根节点）
        while (H.size() > 1)
        {
            node last;
            last.index = H.top().index;          // 初始化索引

            int frequencies = 0;                 // 合并后的频率和
            vector<symbol> collection;           // 收集所有符号

            // 取出频率最小的R个节点
            for (int i = 0; i < R; i++)
            {
                node front = H.top();
                H.pop();

                // 更新最小索引（用于比较）
                if (front.index < last.index)
                    last.index = front.index;

                frequencies += front.frequency;

                // 为每个符号的编码添加前缀（目标符号）
                for (int j = 0; j < front.symbols.size(); j++)
                {
                    string code = front.symbols[j].code;
                    code.insert(code.begin(), '0' + i);   // 在开头添加字符
                    front.symbols[j].code = code;
                    collection.push_back(front.symbols[j]);
                }
            }

            // 创建新节点并压入优先队列
            last.frequency = frequencies;
            last.symbols = collection;
            H.push(last);
        }

        // 获取根节点中的符号列表
        node result = H.top();
        sort(result.symbols.begin(), result.symbols.end());   // 按字母排序

        // 计算平均编码长度
        int total = 0, frequencies = 0;
        for (int i = 0; i < result.symbols.size(); i++)
        {
            total += result.symbols[i].frequency * result.symbols[i].code.length();
            frequencies += result.symbols[i].frequency;
        }

        double aveLength = (double)total / frequencies;
        cout << "Set " << ++cases << "; average length ";
        cout << fixed << setprecision(2) << aveLength << endl;

        // 输出每个字母及其哈夫曼编码
        for (int i = 0; i < result.symbols.size(); i++)
        {
            cout << "    " << result.symbols[i].letter;
            cout << ": " << result.symbols[i].code << endl;
        }
        cout << endl;
    }

    return 0;
}
```
