[UVa 228 Resource Allocation](https://blog.csdn.net/metaphysis/article/details/161087427)

## 题目分析

本题是一个资源分配优化问题。公司有 $d$ 个编程部门，愿意招聘最多 $p$ 名新程序员，并投入最多 $b$ 美元预算用于硬件和软件系统。每个部门对于新资源的利用能力有限，只有特定的几种有效分配方案。对于每个部门，给定若干种程序员分配选项和预算分配选项的组合，以及每种组合对应的预期代码行数增量。目标是决定每个部门分配多少新程序员和预算，使得总代码行数增量最大，且总程序员数不超过 $p$，总预算不超过 $b$。

输入包含多个测试用例，每个用例的格式为：
- 第一行：$d, p, b$
- 接下来每个部门一行或多行：首先给出程序员选项数量 $n$，然后是 $n$ 个程序员数量；接着给出预算选项数量 $k$，然后是 $k$ 个预算金额；最后是一个 $n \times k$ 的表格，表示每种组合的代码行数增量。

输出需要给出最优分配方案的总预算、总程序员数、总代码行数增量，以及每个部门的具体分配。

## 解题思路

本题数据范围较小：$d \leq 20$，每个部门的选项数 $n \leq 10$，$k \leq 10$。最坏情况下，如果直接枚举所有分配组合，总组合数为 $\prod_{i=1}^{d} (n_i \times k_i)$，最大可达 $(10 \times 10)^{20} = 100^{20}$，显然不可行。

但由于资源总量有上限（$p$ 和 $b$），考虑使用深度优先搜索（$\texttt{DFS}$）进行剪枝搜索。算法思路如下：

1. 对每个部门，记录其所有可能的程序员分配数量、预算金额及对应的代码行数。
2. 使用 $\texttt{DFS}$ 递归处理每个部门，在每一层尝试该部门所有可能的分配方案。
3. 递归过程中维护当前已分配的总程序员数、总预算和总代码行数。
4. 如果当前总程序员数超过 $p$ 或总预算超过 $b$，则剪枝跳过。
5. 当所有部门处理完毕后，更新全局最优解。
6. 使用 `visited` 数组标记部门是否已处理，`used` 数组防止同一部门的同一方案被重复使用（实际上由于部门只处理一次，这个标记可以省略，但保留以保持代码完整性）。

由于每个部门最多有 $100$ 种方案，$d \leq 20$，最坏情况下搜索树规模为 $100^{20}$，但实际剪枝后会大大减少。由于 $p$ 和 $b$ 较小，许多分支会被提前剪枝。

在输出时，注意不同测试用例之间有两个空行，每个部门之间有一个空行。

## 代码实现

```cpp
// Resource Allocation
// UVa ID: 228
// Verdict: Accepted
// Submission Date: 2016-06-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int d, p, b, n, k;
int option[25][15][15], programmer[25][15], budget[25][15];
int visited[25], used[25][15][15];
map<int, pair<int, int>> path, best;  // path存储当前搜索路径，best存储最优方案
int max_code_lines, max_programmer, max_budget;

// 深度优先搜索
// current_programmer: 当前已分配的总程序员数
// current_budget: 当前已分配的总预算
// current_code_lines: 当前已获得的总代码行数
void dfs(int current_programmer, int current_budget, int current_code_lines)
{
    // 如果当前方案优于已知最优解，则更新最优解
    if (current_code_lines > max_code_lines)
    {
        max_code_lines = current_code_lines;
        max_programmer = current_programmer;
        max_budget = current_budget;
        best.clear();
        for (auto p : path)
            best.insert(p);
    }
    
    // 尝试为每个尚未分配的部门分配资源
    for (int i = 1; i <= d; i++)
        if (visited[i] == 0)
        {
            visited[i] = 1;
            
            // 遍历该部门的所有程序员选项和预算选项
            for (int x = 1; x <= programmer[i][0]; x++)
                for (int y = 1; y <= budget[i][0]; y++)
                {
                    // 跳过已使用的方案
                    if (used[i][x][y] == 1) continue;
                    // 剪枝：超过总资源限制则跳过
                    if (current_programmer + programmer[i][x] > p) continue;
                    if (current_budget + budget[i][y] > b) continue;
                    
                    used[i][x][y] = 1;
                    path[i] = make_pair(x, y);
                    dfs(current_programmer + programmer[i][x], 
                        current_budget + budget[i][y], 
                        current_code_lines + option[i][x][y]);
                    path.erase(i);
                    used[i][x][y] = 0;
                }
            
            visited[i] = 0;
        }
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> d, d > 0)
    {
        cin >> p >> b;
        
        // 读取每个部门的数据
        for (int i = 1; i <= d; i++)
        {
            cin >> n;
            programmer[i][0] = n;  // programmer[i][0]存储选项数量
            for (int j = 1; j <= n; j++)
                cin >> programmer[i][j];
                
            cin >> k;
            budget[i][0] = k;  // budget[i][0]存储选项数量
            for (int j = 1; j <= k; j++)
                cin >> budget[i][j];
            
            // 读取n×k的增量代码行数表格
            for (int x = 1; x <= n; x++)
                for (int y = 1; y <= k; y++)
                    cin >> option[i][x][y];
        }
        
        // 输出控制：两个测试用例之间打印两个空行
        if (cases)
            cout << endl << endl;
        cout << "Optimal resource allocation problem #" << ++cases << endl;

        // 初始化并执行搜索
        memset(visited, 0, sizeof(visited));
        memset(used, 0, sizeof(used));
        max_code_lines = 0, max_programmer = 0, max_budget = 0;
        dfs(0, 0, 0);
        
        // 输出总结果
        cout << endl;
        cout << "Total budget: $" << max_budget << endl;
        cout << "Total new programmers: " << max_programmer << endl;
        cout << "Total productivity increase: " << max_code_lines << endl;
        
        // 输出每个部门的分配详情
        for (int i = 1; i <= d; i++)
        {
            cout << endl;
            cout << "Division #" << i << " resource allocation:" << endl;
            cout << "Budget:  $" << budget[i][best[i].second] << endl;
            cout << "Programmers: " << programmer[i][best[i].first] << endl;
            cout << "Incremental lines of code: " 
                 << option[i][best[i].first][best[i].second] << endl;
        }
    }
    
	return 0;
}
```
