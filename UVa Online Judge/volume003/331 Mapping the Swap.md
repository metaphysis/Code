[UVa 331 Mapping the Swap](https://blog.csdn.net/metaphysis/article/details/161533140)

## 题目描述

排序一个数组可以通过交换数组中某些相邻元素对来实现。这是著名的冒泡排序的基本技术。如果我们按交换顺序列出要交换的元素对，就得到了所谓的**交换映射**。

例如，假设我们要排序数组 $A$，其元素按顺序为 $3, 2, 1$。如果该数组的下标为 $1, 2, 3$，则排序可以通过以下步骤完成：
1. 交换 $A2$ 和 $A3$ → 得到 $3, 1, 2$
2. 交换 $A1$ 和 $A2$ → 得到 $1, 3, 2$
3. 交换 $A2$ 和 $A3$ → 得到 $1, 2, 3$

如果通过指示要交换的对中第一个元素的下标来标识交换对，则此排序过程可以用交换映射 $2, 1, 2$ 来描述。

值得注意的是，可能有许多种使用相邻元素交换来排序数组的方法。之前的数组 $3, 2, 1$ 也可以通过以下方式排序：
1. 交换 $A1$ 和 $A2$ → $2, 3, 1$
2. 交换 $A2$ 和 $A3$ → $2, 1, 3$
3. 交换 $A1$ 和 $A2$ → $1, 2, 3$

对应的交换映射为 $1, 2, 1$。

对于给定的数组，存在多少种不同的交换映射？稍加思考就会发现有无穷多种交换映射，因为重复交换任意一对元素不会改变元素顺序。因此，交换映射 $1, 1, 1, 2, 1$ 也会使数组元素按升序排列。

但有多少**最小长度**的交换映射能使给定数组有序？这就是本题要回答的问题。

### 输入格式

输入数据包含任意数量的测试用例，后跟一个单独的 `0`。每个测试用例以一个整数 $n$ 开头（表示数组大小），后面跟着 $n$ 个整数值。

### 输出格式

对于每个测试用例，输出类似样例所示的消息。所有测试用例中 $n \leq 5$。

### 样例输入

```
2 9 7
2 12 50
3 3 2 1
3 9 1 5
0
```

### 样例输出

```
There are 1 swap maps for input data set 1.
There are 0 swap maps for input data set 2.
There are 2 swap maps for input data set 3.
There are 1 swap maps for input data set 4.
```

---

## 题目分析

### 问题的本质

这是一个**最小长度相邻交换排序**的计数问题。给定一个数组，需要找出所有使用**最少交换次数**将其排序为升序的相邻交换序列的数量。

### 关键点

1. **相邻交换**：每次只能交换相邻的两个元素
2. **最小长度**：只计数使用最少交换次数的序列
3. **数组大小**：$n \leq 5$，非常小，可以暴力搜索

### 与逆序数的关系

将一个数组排序为升序所需的最小相邻交换次数等于数组的**逆序数**。例如：
- $[9, 7]$：逆序数 $1$（$9 > 7$）
- $[12, 50]$：逆序数 $0$
- $[3, 2, 1]$：逆序数 $3$（$3>2$，$3>1$，$2>1$）
- $[9, 1, 5]$：逆序数 $2$（$9>1$，$9>5$）

因此，我们只需要找出所有使用恰好**逆序数**次相邻交换的排序序列。

### 搜索策略

由于 $n \leq 5$，最大逆序数为 $C(5,2) = 10$。我们可以使用深度优先搜索（$\texttt{DFS}$）：
- 每次只交换相邻的逆序对（即 $a[i] > a[i+1]$）
- 递归地进行交换
- 当数组完全有序时，记录一个有效序列

**重要**：为了保证只计数最小长度的序列，我们不需要显式地限制深度——因为每次交换只发生在逆序对上，且每次交换都会减少逆序数。当数组有序时，使用的交换次数恰好等于初始逆序数（因为每次交换恰好减少一个逆序）。

---

## 参考代码

```cpp
// Mapping the Swaps
// UVa ID: 331
// Verdict: Accepted
// Submission Date: 2016-06-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> number;  // 当前数组
int counter = 0;     // 有效交换映射计数

// 深度优先搜索，只交换相邻逆序对
void dfs()
{
    bool sorted = true;
    // 遍历所有相邻位置
    for (int i = 0; i < number.size() - 1; i++)
    {
        // 如果当前是逆序对，交换并继续搜索
        if (number[i] > number[i + 1])
        {
            sorted = false;
            swap(number[i], number[i + 1]);  // 执行交换
            dfs();                           // 递归
            swap(number[i], number[i + 1]);  // 回溯
        }
    }
    // 如果数组已有序，计数加 1
    if (sorted)
        counter++;
}

int main(int argc, char *argv[])
{
    int n, cases = 0;
    while (cin >> n, n)
    {
        number.clear();
        for (int i = 1; i <= n; i++)
        {
            int integer;
            cin >> integer;
            number.push_back(integer);
        }
        
        counter = 0;
        
        // 检查是否已经有序
        bool sorted = true;
        for (int i = 0; i < number.size() - 1; i++)
            if (number[i] > number[i + 1])
            {
                sorted = false;
                break;
            }
        
        // 如果未有序，进行 DFS 搜索
        if (!sorted)    
            dfs();
        
        cout << "There are " << counter;
        cout << " swap maps for input data set " << ++cases << "." << endl;
    }
    
    return 0;
}
```
