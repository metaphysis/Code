[UVa 284 Logic](https://blog.csdn.net/metaphysis/article/details/161360996)

## 题目分析

本题要求模拟一个逻辑电路的行为。电路被放置在一个 $10 \times 10$ 的网格中，每个格子可以包含五种操作之一：$\texttt{AND}$（`&`）、$\texttt{OR}$（`|`）、$\texttt{NOT}$（`!`）、$\texttt{Input}$（`i`）和 $\texttt{Output}$（`o`）。这些操作单元通过有向边连接，形成一个逻辑电路。

输入包含多组测试数据。对于每组数据，首先给出电路的描述：每个操作单元由坐标 `xy`（$x$ 和 $y$ 均为 $0$ 到 $9$ 的数字）和操作符组成，随后列出该单元的输出连接目标（即其输出作为哪些其他单元的输入），以 `..` 结束。所有操作单元描述完毕后，有一行 `end` 表示电路描述结束。

接下来，给出 $t$ 个测试用例，每个测试用例是一个 `01` 字符串，其长度等于输入单元（`i`）的数量，字符串的顺序与输入单元在输入中出现的顺序一致。对于每个测试用例，需要模拟电路运行，并按输出单元（`o`）的定义顺序输出每个输出单元的值。

## 解题思路

本题的核心是**对有向无环图（$\texttt{DAG}$）进行拓扑排序或深度优先遍历**，以计算每个逻辑门的输出值。电路中的每个操作单元可以视为图中的一个结点，而输出连接列表则定义了从当前结点指向其他结点的有向边。

### 方法一：迭代模拟（对应第一个代码）

这种方法模拟了信号在电路中传播的过程。具体思路如下：

1. **存储结构**：为每个格子（共 $100$ 个，因为坐标 $0-9$ 组合成 $10 \times 10$ 网格）存储：
   - 操作类型 `operators`
   - 左输入值 `leftvalue` 和右输入值 `rightvalue`（对于 $\texttt{NOT}$ 和 $\texttt{Input}$ 只使用左值）
   - 是否已更新 `updated`
   - 输出目标列表 `to`

2. **输入解析**：对于每个操作单元，其坐标 `xy` 被转换为一个索引 `(x - '0') * 10 + (y - '0')`。同时记录所有输入单元和输出单元的索引。

3. **信号传播**：
   - 首先，为当前测试用例的每个输入单元赋值（左值设为对应的输入位）。
   - 然后进行迭代传播：每次遍历所有单元，如果一个单元的输入已经就绪（对于 $\texttt{AND}$ / $\texttt{OR}$ 需要两个输入，对于 $\texttt{NOT}$ / $\texttt{Input}$ / $\texttt{Output}$ 只需要一个输入），则计算其输出值，并将该值传播到所有下游单元的输入端（如果下游单元的左值未设置则设为左值，否则设为右值）。
   - 标记该单元为已更新，并继续循环，直到某次遍历中没有新的单元被更新为止。

4. **输出结果**：根据输出单元的 `leftvalue`（即最终计算出的值）按序输出。

这种方法的本质是**广度优先的拓扑排序**，因为电路中的信号传播方向是从输入到输出。由于电路可能不是严格的树状结构（一个门可以驱动多个下游门），所以需要维护每个门的输入状态，直到所有输入都到达后再计算输出。

### 方法二：深度优先搜索（对应第二个代码）

第二种方法采用了更简洁的 $\texttt{DFS}$ 递归计算方式，思路如下：

1. **反向建图**：与第一种方法不同，这里将边反向存储。对于每个操作单元 $v$，如果它的输出连接到 $u$，则存储 $edges[u].push\_back(v)$。这样，从输出单元出发，可以通过 $\texttt{DFS}$ 反向遍历到输入单元。

2. **$\texttt{DFS}$ 计算**：
   - 对于每个尚未访问的单元（即图中所有结点），调用 `dfs(u)`。
   - 在 `dfs(u)` 中，首先标记 `visited[u] = 1`。
   - 然后根据 `u` 的操作类型，对其所有上游结点 $v$（即 $edges[u]$ 中的结点）递归调用 `dfs(v)`。
   - 递归返回后，根据收集到的上游值计算当前结点的值：
     - 若为 `!`，则取反（注意 $\texttt{NOT}$ 只有一个输入，代码中巧妙处理为 `r = !value[v]`）。
     - 若为 `|`，则对所有上游值做逻辑或。
     - 若为 `&`，则对所有上游值做逻辑与。
   - 将计算结果存入 `value[u]`。

3. **输入单元特殊处理**：输入单元在 $\texttt{DFS}$ 前已被显式赋值并标记为已访问，因此递归不会错误地重新计算它们。

4. **输出结果**：按输出单元的顺序输出 `value[output[j]]`。

这种方法的优点是不需要显式地管理输入队列，代码更加简洁。其正确性依赖于电路是 $\texttt{DAG}$（无环），因为如果有环，递归将无法终止。

## 两种方法的对比

| 特性 | 方法一（迭代模拟） | 方法二（$\texttt{DFS}$） |
|------|------------------|---------------|
| 图方向 | 正向（从输入到输出） | 反向（从输出到输入） |
| 计算顺序 | 自底向上（输入到输出） | 自顶向下（递归回溯） |
| 输入就绪判断 | 显式检查 `left/right` 值 | 递归保证上游先计算 |
| 处理 $\texttt{NOT}$ 门 | 单独分支 | 统一在循环中处理 |
| 代码长度 | 较长 | 较短 |
| 可读性 | 较直观 | 较简洁 |

## 注意事项

- 网格大小为 $10 \times 10$，坐标 $x$ 和 $y$ 都是 $0$ 到 $9$，因此最多有 $100$ 个单元。
- $\texttt{NOT}$ 门只有一个输入，在第一种方法中只使用 `leftvalue`，在第二种方法中通过反向建图也能正确处理。
- 输出列表以 `..` 结束，但同一行中可能包含多个目标坐标，需注意解析。
- 每组测试用例结束后要输出一个空行。
- 输入行末尾可能有空格，需要适当清理。

## 代码实现

以下是第一种方法的完整代码：

```cpp
// Logic
// UVa ID: 284
// Verdict: Accepted
// Submission Date: 2016-06-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct cell
{
    int index;              // 格子索引
    int leftvalue, rightvalue;  // 左输入和右输入值
    bool updated;           // 是否已计算出输出值并传播
    char operators;         // 操作类型：&, |, !, i, o
    vector <int> to;        // 输出连接的目标格子索引
};

cell grid[100];             // 10x10 = 100 个格子
vector <int> inputcell, outputcell;  // 输入单元和输出单元的索引列表

int main(int argc, char *argv[])
{
    string line;
    int cases = 0;
    getline(cin, line);
    cases = stoi(line);     // 读取电路组数

    while (cases--)
    {
        inputcell.clear(), outputcell.clear();
        
        // 初始化所有格子
        for (int i = 0; i < 100; i++)
        {
            grid[i].index = i;
            grid[i].to.clear();
        }
        
        // 读取电路描述，直到遇到 "end"
        while (getline(cin, line), line[0] != 'e')
        {
            vector <string> input;
            string word;
            istringstream iss(line);
            while (iss >> word)
                input.push_back(word);
            
            // 解析坐标和操作符
            int index = (input[0][0] - '0') * 10 + (input[0][1] - '0');
            grid[index].operators = input[0][2];
            
            // 记录输入单元和输出单元
            if (input[0][2] == 'i')
                inputcell.push_back(index);
            if (input[0][2] == 'o')
                outputcell.push_back(index);
                
            // 解析输出目标列表，直到 ".." 结束
            for (int i = 1; i < input.size() - 1; i++)
                grid[index].to.push_back((input[i][0] - '0') * 10 + (input[i][1] - '0'));
        }
        
        // 读取测试用例数量
        int t;
        getline(cin, line);
        t = stoi(line);

        // 处理每个测试用例
        for (int k = 1; k <= t; k++)
        {
            // 重置所有格子的状态
            for (int i = 0; i < 100; i++)
            {
                grid[i].leftvalue = -1;   // -1 表示尚未收到输入
                grid[i].rightvalue = -1;
                grid[i].updated = false;
            }
        
            getline(cin, line);
            
            // 去除行尾空白字符
            for (int j = line.length() - 1; j >= 0; j--)
                if (isblank(line[j]))
                    line.erase(line.begin() + j);
                else
                    break;
            
            // 为输入单元赋值
            for (int j = 0; j < line.length(); j++)
                grid[inputcell[j]].leftvalue = (line[j] == '1');
            
            // 迭代传播信号，直到没有新的更新
            bool updated;
            do
            {
                updated = false;
                for (int i = 0; i < 100; i++)
                {
                    if (grid[i].updated)
                        continue;
                    
                    // 处理输入单元
                    if (grid[i].operators == 'i')
                    {
                        if (grid[i].leftvalue >= 0)
                        {
                            for (int j = 0; j < grid[i].to.size(); j++)
                            {
                                if (grid[grid[i].to[j]].leftvalue < 0)
                                    grid[grid[i].to[j]].leftvalue = grid[i].leftvalue;
                                else
                                    grid[grid[i].to[j]].rightvalue = grid[i].leftvalue;
                            }
                            
                            grid[i].updated = true;
                            updated = true;
                        }
                    }
                    // 处理 NOT 门
                    else if (grid[i].operators == '!')
                    {
                        if (grid[i].leftvalue >= 0)
                        {
                            for (int j = 0; j < grid[i].to.size(); j++)
                            {
                                if (grid[grid[i].to[j]].leftvalue < 0)
                                    grid[grid[i].to[j]].leftvalue = !grid[i].leftvalue;
                                else
                                    grid[grid[i].to[j]].rightvalue = !grid[i].leftvalue;
                            }
                            
                            grid[i].updated = true;
                            updated = true;
                        }
                    }
                    // 处理输出单元（将输入直接传递）
                    else if (grid[i].operators == 'o')
                    {
                        if (grid[i].leftvalue >= 0)
                        {
                            for (int j = 0; j < grid[i].to.size(); j++)
                                grid[grid[i].to[j]].leftvalue = grid[i].leftvalue;
                            
                            grid[i].updated = true;
                            updated = true;
                        }
                    }
                    // 处理 AND 门
                    else if (grid[i].operators == '&')
                    {
                        if (grid[i].leftvalue >= 0 && grid[i].rightvalue >= 0)
                        {
                            int value = grid[i].leftvalue && grid[i].rightvalue;
                            for (int j = 0; j < grid[i].to.size(); j++)
                            {
                                if (grid[grid[i].to[j]].leftvalue < 0)
                                    grid[grid[i].to[j]].leftvalue = value;
                                else
                                    grid[grid[i].to[j]].rightvalue = value;
                            }
                            
                            grid[i].updated = true;
                            updated = true;
                        }
                    }
                    // 处理 OR 门
                    else if (grid[i].operators == '|')
                    {
                        if (grid[i].leftvalue >= 0 && grid[i].rightvalue >= 0)
                        {
                            int value = grid[i].leftvalue || grid[i].rightvalue;
                            for (int j = 0; j < grid[i].to.size(); j++)
                            {
                                if (grid[grid[i].to[j]].leftvalue < 0)
                                    grid[grid[i].to[j]].leftvalue = value;
                                else
                                    grid[grid[i].to[j]].rightvalue = value;
                            }
                            
                            grid[i].updated = true;
                            updated = true;
                        }
                    }
                }
            } while (updated);
            
            // 按输出单元的顺序输出结果
            for (int i = 0; i < outputcell.size(); i++)
                cout << (grid[outputcell[i]].leftvalue ? '1' : '0');
            cout << endl;
        }
        
        // 每组测试用例后输出空行
        cout << endl;
    }
    
    return 0;
}
```

以下是第二种方法的完整代码：

```cpp
// Logic
// UVa ID: 284
// Verdict: Accepted
// Submission Date: 2019-04-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;       // 最大顶点数，略大于 100

vector<int> edges[MAXV];    // 反向邻接表：edges[u] 存储输出连接到 u 的单元
int visited[MAXV];          // DFS 访问标记
int input[MAXV], idxOfInput;    // 输入单元索引列表及个数
int output[MAXV], idxOfOutput;  // 输出单元索引列表及个数
int value[MAXV];            // 每个单元的计算结果
char operation[MAXV];       // 每个单元的操作类型

// 深度优先搜索计算单元 u 的值
void dfs(int u)
{
    visited[u] = 1;
    // 根据操作类型初始化结果值
    int r = 1;
    if (operation[u] == '|') r = 0;
    
    for (auto v : edges[u])
    {
        if (!visited[v])
            dfs(v);
        // 根据门类型组合结果
        if (operation[u] == '!')
            r = !value[v];          // NOT 门只有一个输入
        else if (operation[u] == '|')
            r |= value[v];          // OR 门
        else
            r &= value[v];          // AND 门
    }
    value[u] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line, block;

    getline(cin, line);
    int cases = stoi(line);

    for (int cs = 1; cs <= cases; cs++)
    {
        // 清空反向邻接表
        for (int i = 0; i < MAXV; i++) edges[i].clear();
        idxOfInput = idxOfOutput = 0;
        
        // 读取电路描述
        while (getline(cin, line), line.front() != 'e')
        {
            istringstream iss(line);
            iss >> block;
            int v = (block[0] - '0') * 10 + (block[1] - '0');
            operation[v] = block[2];
            
            if (operation[v] == 'i')
                input[idxOfInput++] = v;
            if (operation[v] == 'o')
                output[idxOfOutput++] = v;
            
            // 读取输出目标，反向建图
            while (iss >> block)
            {
                if (block == "..") break;
                int u = (block[0] - '0') * 10 + (block[1] - '0');
                edges[u].push_back(v);   // 反向边：u 的上游是 v
            }
        }

        // 读取测试用例数量
        getline(cin, line);
        int sets = stoi(line);
        
        // 处理每个测试用例
        for (int s = 0; s < sets; s++)
        {
            getline(cin, line);

            // 重置访问标记
            memset(visited, 0, sizeof(visited));
            // 设置输入单元的值
            for (int j = 0; j < idxOfInput; j++)
            {
                value[input[j]] = line[j] - '0';
                visited[input[j]] = 1;   // 输入单元已访问，不再 DFS 计算
            }

            // 对图中所有未访问的结点执行 DFS
            for (int j = 0; j < MAXV; j++)
                if (!visited[j])
                    dfs(j);
            
            // 按输出单元的顺序输出结果
            for (int j = 0; j < idxOfOutput; j++)
                cout << value[output[j]];
            cout << '\n';
        }
        // 每组测试用例后输出空行
        cout << '\n';
    }
    
    return 0;
}
```
