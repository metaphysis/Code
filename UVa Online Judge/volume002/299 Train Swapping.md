[UVa 299 Train Swapping](https://blog.csdn.net/metaphysis/article/details/161389940)

## 题目分析

本题描述了一个经典的列车车厢重排问题。在一个老式火车站中，有一种特殊的工作称为 “列车交换员” （$\texttt{Train Swapper}$），其工作是通过交换相邻车厢的位置，将列车车厢按照编号 $1$ 到 $L$ 的顺序排列。题目要求计算将给定序列通过相邻交换排序所需的最少交换次数。

实际上，这个问题等价于 **计算一个排列的逆序对数**。因为每次交换相邻两个元素可以消除恰好一个逆序，而最少交换次数就等于原始排列中的逆序总数。

**逆序的定义**：在一个序列中，如果存在一对下标 $i < j$ 满足 $a[i] > a[j]$，则称 $(i, j)$ 为一个逆序对。

## 解题思路

题目中给出的两个代码实现了两种不同的方法来计算最少交换次数。

### 方法一：冒泡排序统计交换次数

第一个代码直接模拟了冒泡排序的过程，并在每次交换相邻元素时累加计数器。由于冒泡排序每次比较并交换相邻逆序对，最终的交换次数就等于逆序对数。

**算法步骤**：
1. 从最后一个位置开始，逐轮将当前未排序部分的最大元素 “冒泡” 到末尾。
2. 在每一轮中，从左到右比较相邻元素，如果前一个大于后一个，则交换并增加计数。
3. 最终计数即为最少交换次数。

这种方法的时间复杂度为 $O(L^2)$，由于 $L \leq 50$，完全可行。

### 方法二：依次寻找最小元素并移动到前面

第二个代码采用了另一种思路：按照编号 $1, 2, \dots, L$ 的顺序，依次将当前需要的车厢 “移动” 到序列的前面。每次找到目标车厢的当前位置，将其移动到前面所需交换的次数等于它当前的位置索引（假设从 $0$ 开始计数），然后将该车厢从序列中删除。

**算法步骤**：
1. 对于 $i$ 从 $1$ 到 $L$：
   - 在当前序列中查找数值为 $i$ 的元素，得到其下标 $j$（从 $0$ 开始）。
   - 将 $j$ 累加到答案中（因为需要将 $i$ 经过 $j$ 次相邻交换移动到最前面）。
   - 从序列中删除该元素。
2. 输出累加的总和。

这个方法本质上也是在计算逆序数，因为将元素 $i$ 移动到前面需要经过它前面的所有元素，而这些元素都与 $i$ 构成了逆序对。

### 两种方法的比较

| 方法 | 核心思想 | 时间复杂度 | 代码简洁度 |
|------|----------|------------|------------|
| 冒泡排序 | 模拟冒泡，统计交换次数 | $O(L^2)$ | 较简单 |
| 删除法 | 依次查找最小元素并删除 | $O(L^2)$ | 稍复杂 |

两种方法都能正确求解，且对于 $L \leq 50$ 的数据范围都足够高效。

## 代码实现

```cpp
// Train Swapping
// UVa ID: 299
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> trains;    // 存储当前车厢序列

// 使用冒泡排序统计最少相邻交换次数（即逆序对数）
int sortAndCount()
{
    int swaps = 0;   // 交换次数计数器
    
    // 外层循环：一共需要进行 L-1 轮冒泡
    for (int i = trains.size() - 1; i > 0; i--)
        // 内层循环：将当前轮次中最大的元素向右移动
        for (int j = 0; j < i; j++)
            // 如果相邻两个元素逆序，则交换并计数
            if (trains[j] > trains[j + 1])
            {
                swaps++;
                swap(trains[j], trains[j + 1]);
            }
    
    return swaps;    // 返回总交换次数
}

int main(int argc, char *argv[])
{
    // 加速输入输出
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int cases;    // 测试用例个数
    cin >> cases;
    
    while (cases--)
    {
        int number;    // 当前测试用例的车厢数量
        cin >> number;
        trains.clear();    // 清空向量
        
        // 读取车厢序列
        int index;
        for (int i = 1; i <= number; i++)
        {
            cin >> index;
            trains.push_back(index);
        }
        
        // 输出结果
        cout << "Optimal train swapping takes " << sortAndCount() << " swaps.\n";
    }
    
    return 0;
}
```

```cpp
// Train Swapping
// UVa ID: 299
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector < int > trains;
int cases, number;

int sortAndCount()
{
    int swaps = 0;
    for (int i = 1; i <= number; i++)
        for (int j = 0; j < trains.size(); j++)
            if (trains[j] == i)
            {
                swaps += j;
                trains.erase(trains.begin() + j);
                break;
            }
    return swaps;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    cin >> cases;
    while (cases--)
    {
        cin >> number;
        trains.clear();
        
        int index;
        for (int i = 1; i <= number; i++)
        {
            cin >> index;
            trains.push_back(index);
        }
        
        cout << "Optimal train swapping takes " << sortAndCount() << " swaps.\n";
    }
    
	return 0;
}
```
## 总结

本题的核心是识别出问题本质为 **求逆序对数**，因为相邻交换排序的最小次数等于逆序总
数。理解了这一点后，可以用多种方法求解。题目给出的 $L \leq 50$ 的限制使得 $O(L^2)$ 的算法完全足够，无需使用更高效的归并排序或树状数组等 $O(L \log L)$ 的方法。
