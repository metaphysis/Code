[UVa 345 It's Ir-Resist-Able](https://blog.csdn.net/metaphysis/article/details/161557158)

## 题目描述

电阻器是电子电路中的常见元件。每个电阻器有两个端子，当电流流过电阻器时，部分电流转化为热量，从而“抵抗”电流的流动。电阻器对电流的抵抗程度用一个正数值表示，称为电阻值，单位是欧姆（$\texttt{Ohms}$）。

当两个电阻器**串联**时，等效电阻等于各电阻值之和。当两个电阻器**并联**时，等效电阻的倒数等于各电阻倒数之和。

在本题中，给定一个电阻网络（由若干电阻器及其连接点组成），需要计算两个指定点之间的等效电阻。

### 输入格式

输入包含多个测试用例。每个测试用例以一行三个整数 $N$、$A$、$B$ 开始：
- $N$：电阻器数量（不超过 $30$）
- $A$、$B$：需要计算等效电阻的两个端点标签

接下来 $N$ 行，每行包含两个整数（连接点标签）和一个实数（电阻值）。

输入以 $N = A = B = 0$ 结束。

### 输出格式

对于每个测试用例，输出一行，包含用例编号和等效电阻（保留两位小数），格式如样例所示。

### 样例输入

```
2 1 3
1 2 100
2 3 200
2 1 2
1 2 100
1 2 150
6 1 6
1 2 500
1 3 15
3 4 40
3 5 100
4 6 60
5 6 50
0 0 0
```

### 样例输出

```
Case 1: 300.00 Ohms
Case 2: 60.00 Ohms
Case 3: 75.00 Ohms
```

---

## 题目分析

### 问题的本质

这是一个**电阻网络分析**问题。给定一个由电阻器组成的网络，需要计算两个节点之间的等效电阻。由于电阻网络可能包含复杂的串并联组合（甚至更复杂的桥式结构），需要使用**节点电压法**（$\texttt{nodal analysis}$）结合基尔霍夫定律求解。

### 基尔霍夫定律

- **基尔霍夫电流定律（$\texttt{KCL}$）**：流入任一节点的电流代数和为零
- **基尔霍夫电压定律（$\texttt{KVL}$）**：任一回路中电压降的代数和为零

### 节点电压法

选取一个参考节点（电压为 $0$），其他节点的电压为未知量。对于每个节点，根据 $\texttt{KCL}$ 建立方程：

$$
\sum_{j} \frac{V_i - V_j}{R_{ij}} = 0
$$

其中 $R_{ij}$ 是节点 $i$ 和 $j$ 之间的电阻（如果有多个电阻并联，需先合并）。

### 边界条件

在本问题中：
- 设起点 $A$ 的电压为 $V_A = 1000$（任意正数）
- 设终点 $B$ 的电压为 $V_B = 0$
- 其他节点的电压为未知量

### 求解过程

1. 建立节点电压方程组
2. 使用高斯消元法求解各节点电压
3. 计算从 $B$ 节点流出的总电流 $I$（或流入 $A$ 的电流）
4. 等效电阻 $R_{eq} = (V_A - V_B) / I$

---

## 解题思路

### 步骤一：离散化节点标签

电阻器的连接点标签是任意正整数，需要映射到 $0 \sim C-1$ 的连续索引。

```cpp
map<int, int> indexer;
for (int i = 0; i < N; i++) {
    cin >> X >> Y >> R;
    if (indexer.find(X) == indexer.end()) indexer[X] = label++;
    if (indexer.find(Y) == indexer.end()) indexer[Y] = label++;
}
```

### 步骤二：合并并联电阻

对于同一对节点之间可能有多条并联电阻，需要先合并：

```cpp
resistor[idxX][idxY] += 1.0 / R;
resistor[idxY][idxX] += 1.0 / R;
```

计算等效电阻时，取倒数：

```cpp
for (int i = 0; i < C; i++)
    for (int j = 0; j < C; j++)
        if (resistor[i][j] > 0)
            resistor[i][j] = 1.0 / resistor[i][j];
```

### 步骤三：建立节点电压方程

对于每个节点（除 $A$ 和 $B$ 外），根据 $\texttt{KCL}$ 建立方程：

$$
\sum_{j} \frac{V_i - V_j}{R_{ij}} = 0
$$

整理得：

$$
\left(\sum_{j} \frac{1}{R_{ij}}\right) V_i - \sum_{j} \frac{1}{R_{ij}} V_j = 0
$$

在矩阵中：
- 对角线元素 `matrix[i][i]` 减去 $\frac{1}{R_{ij}}$
- 非对角线元素 `matrix[i][j]` 加上 $\frac{1}{R_{ij}}$

### 步骤四：设置边界条件

对于 $A$ 和 $B$ 节点，其电压已知，不需要建立 $\texttt{KCL}$ 方程。将它们的方程设为：

```cpp
matrix[idxA][idxA] = 1.0;
matrix[idxB][idxB] = 1.0;
voltage[idxA] = 1000.0;
voltage[idxB] = 0.0;
```

### 步骤五：高斯消元求解

使用列主元高斯消元法求解线性方程组 $Ax = b$。

### 步骤六：计算总电流和等效电阻

从 $B$ 节点计算流入的总电流：

```cpp
double current = 0.0;
for (int node = 0; node < C; node++)
    if (resistor[node][idxB] > EPSILON)
        current += (voltage[node] - voltage[idxB]) / resistor[node][idxB];
```

等效电阻：

```cpp
Req = (voltage[idxA] - voltage[idxB]) / current;
```

---

## 参考代码

```cpp
// It's Ir-Resist-Able!
// UVa ID: 345
// Verdict: Accepted
// Submission Date: 2016-11-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;
const double EPSILON = 1e-8;

// 不考虑其他连接点影响时，两个连接点间的阻值
double resistor[MAXN][MAXN];

// 各个连接点的电势
double voltage[MAXN];

// 列主元高斯消元法求解线性方程组 Ax = b
bool gaussianElimination(vector<vector<double>> &A, vector<double> &b)
{
    int n = A.size();
    // 将 b 作为增广矩阵的最后一列
    for (int i = 0; i < n; i++) 
        A[i].push_back(b[i]);

    for (int i = 0; i < n; i++)
    {
        // 选取主元（绝对值最大的行）
        int pivot = i;
        for (int j = i; j < n; j++)
            if (fabs(A[j][i]) > fabs(A[pivot][i])) 
                pivot = j;
        swap(A[i], A[pivot]);

        // 矩阵奇异
        if (fabs(A[i][i]) < EPSILON) 
            return false;

        // 将主元归一化
        for (int j = i + 1; j <= n; j++) 
            A[i][j] /= A[i][i];

        // 消去其他行的当前列
        for (int j = 0; j < n; j++)
            if (i != j)
                for (int k = i + 1; k <= n; k++) 
                    A[j][k] -= A[j][i] * A[i][k];
    }

    // 提取解
    for (int i = 0; i < n; i++) 
        b[i] = A[i][n];
    
    return true;
}

int main(int argc, char *argv[])
{
    int N, A, B, X, Y, cases = 0;
    double R;

    while (cin >> N >> A >> B, N > 0)
    {
        cout << "Case " << ++cases << ": ";

        // 初始化电阻矩阵
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                resistor[i][j] = 0.0;

        // 离散化节点标签
        map<int, int> indexer;
        int label = 0;
        
        for (int i = 0; i < N; i++)
        {
            cin >> X >> Y >> R;

            if (indexer.find(X) == indexer.end()) 
                indexer[X] = label++;
            if (indexer.find(Y) == indexer.end()) 
                indexer[Y] = label++;
            
            // 合并并联电阻：存储电导（1/R）
            resistor[indexer[X]][indexer[Y]] += 1.0 / R;
            resistor[indexer[Y]][indexer[X]] += 1.0 / R;
        }

        int C = indexer.size();

        // 将电导转换回电阻
        for (int i = 0; i < C; i++)
            for (int j = 0; j < C; j++)
                if (resistor[i][j] > EPSILON)
                    resistor[i][j] = 1.0 / resistor[i][j];
                else
                    resistor[i][j] = 0.0;

        // 构建节点电压方程组
        vector<vector<double>> matrix(C, vector<double>(C, 0.0));
        vector<double> voltage(C, 0.0);

        // 设置边界条件：起点电压 1000，终点电压 0
        int idxA = indexer[A], idxB = indexer[B];
        voltage[idxA] = 1000.0;
        voltage[idxB] = 0.0;

        // 起点和终点的方程简化为 V = 已知值
        matrix[idxA][idxA] = matrix[idxB][idxB] = 1.0;

        // 为其他节点建立 KCL 方程
        for (int node = 0; node < C; node++)
        {
            if (node == idxA || node == idxB) 
                continue;

            for (int other = 0; other < C; other++)
            {
                if (resistor[node][other] > EPSILON)
                {
                    double conductance = 1.0 / resistor[node][other];
                    matrix[node][other] += conductance;
                    matrix[node][node] -= conductance;
                }
            }
        }

        // 求解节点电压
        gaussianElimination(matrix, voltage);

        // 计算从终点 B 流出的总电流
        double current = 0.0;
        for (int node = 0; node < C; node++)
            if (resistor[node][idxB] > EPSILON)
                current += (voltage[node] - voltage[idxB]) / resistor[node][idxB];

        // 欧姆定律计算等效电阻
        if (fabs(current) < EPSILON)
            cout << "0.00 Ohms\n";
        else
        {
            cout << fixed << setprecision(2);
            cout << (voltage[idxA] - voltage[idxB]) / current;
            cout << " Ohms\n";
        }
    }

    return 0;
}
```
