[UVa 383 Shipping Routes](https://blog.csdn.net/metaphysis/article/details/161673596)

## 题目描述

$\texttt{Slow Boat to China}$ 航运公司需要一个程序来帮助快速向潜在客户报价。运费取决于货物的大小和所需的运输段数。一个运输段连接两个仓库，但并非所有仓库之间都有直接连接，因此从一个仓库到另一个仓库可能需要多个运输段。

每个数据集包含 $1$ 到 $30$ 个仓库。每个仓库由两个大写字母标识。运输段是双向的，存在于任意两个不同的仓库之间。

运费 = 货物大小 × 所需运输段数 × $100$。

对于给定的运输请求（货物大小、始发仓库、目的仓库），程序输出最佳（最便宜）的运费，如果无法运输则输出相应信息。

### 输入格式

第一行包含整数 $T$（$1 \leq T \leq 10$），表示数据集中数据集的个数。

每个数据集的第一行包含三个整数：
- $M$（$1 \leq M \leq 30$）：仓库数量
- $N$（$0 \leq N \leq M(M-1)/2$）：运输段数量
- $P$（$0 \leq P \leq 10$）：运输请求数量

第二行包含 $M$ 个两个字母的仓库代码（大写字母），以空格分隔。

接下来 $N$ 行，每行包含两个仓库代码，表示它们之间有直接运输段。

接下来 $P$ 行，每行包含一个整数（货物大小）和两个仓库代码（始发地和目的地）。

### 输出格式

第一行输出 `SHIPPING ROUTES OUTPUT`。对于每个数据集，输出 `DATA SET X` 标题，然后 $P$ 行结果（`$cost` 或 `NO SHIPMENT POSSIBLE`）。最后一行输出 `END OF OUTPUT`。

### 样例输入

```
2
6 7 5
AA CC QR FF DD AB
AA CC
CC QR
DD CC
AA DD
AA AB
DD QR
AB DD
5 AA AB
14 DD CC
1 CC DD
2 AA FF
13 AB QR
3 0 1
AA BB CC
5 AA CC
```

### 样例输出

```
SHIPPING ROUTES OUTPUT

DATA SET 1

$500
$1400
$100
NO SHIPMENT POSSIBLE
$2600

DATA SET 2

NO SHIPMENT POSSIBLE

END OF OUTPUT
```

---

## 题目分析

### 问题的本质

这是一个**图论最短路径**问题。每个仓库是节点，运输段是边（权重为 $1$）。需要回答多个查询：给定起点和终点，求最短路径长度（运输段数），然后计算运费。

### 算法选择

- 节点数 $M \leq 30$，可以使用 $\texttt{Floyd-Warshall}$ 算法计算所有点对之间的最短路径
- 时间复杂度 $O(M^3) = 27000$，完全可行
- 或对每个查询使用 $\texttt{BFS}$，但 $P \leq 10$，$M$ 很小，两种方法均可

### 无连接处理

如果两点之间不可达，距离为无穷大，输出 `NO SHIPMENT POSSIBLE`。

### 运费计算

运费 = 货物大小 × 最短路径长度 × $100$。

---
## 参考代码

```cpp
// Shippint Routes
// UVa ID: 383
// Verdict: Accepted
// Submission Date: 2016-06-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_LEGS = 100000;  // 无穷大

int main(int argc, char *argv[])
{
    int datasets = 0, cases = 0;
    cin >> datasets;
    
    cout << "SHIPPING ROUTES OUTPUT" << endl << endl;
    
    while (datasets--)
    {
        int M, N, P;
        cin >> M >> N >> P;
        
        // 仓库代码到索引的映射
        map<string, int> warehouses;
        for (int i = 1; i <= M; i++)
        {
            string codes;
            cin >> codes;
            warehouses[codes] = i;
        }
        
        // 初始化距离矩阵
        int legs[M + 1][M + 1];
        for (int i = 1; i <= M; i++)
        {
            for (int j = 1; j <= M; j++)
                legs[i][j] = MAX_LEGS;
            legs[i][i] = 0;
        }
        
        // 读取边（运输段）
        for (int i = 1; i <= N; i++)
        {
            string start, next;
            cin >> start >> next;
            legs[warehouses[start]][warehouses[next]] = 1;
            legs[warehouses[next]][warehouses[start]] = 1;
        }
        
        // Floyd-Warshall 计算所有点对最短路径
        for (int k = 1; k <= M; k++)
            for (int i = 1; i <= M; i++)
                for (int j = 1; j <= M; j++)
                    if (legs[i][k] + legs[k][j] < legs[i][j])
                        legs[i][j] = legs[i][k] + legs[k][j];
        
        cout << "DATA SET  " << ++cases << endl << endl;
                        
        // 处理查询
        for (int i = 1; i <= P; i++)
        {
            int size;
            string start, next;
            cin >> size >> start >> next;
            
            int dist = legs[warehouses[start]][warehouses[next]];
            if (dist >= MAX_LEGS)
            {
                cout << "NO SHIPMENT POSSIBLE" << endl;
                continue;
            }
            
            cout << "$" << size * dist * 100 << endl;
        }
        
        cout << endl;
    }
    
    cout << "END OF OUTPUT" << endl;
    
    return 0;
}
```
