[UVa 111 History Grading](https://blog.csdn.net/metaphysis/article/details/156641317)

## 题目描述

本题源于历史考试评分问题。学生需要将若干历史事件按时间顺序排序。完全正确的排序得满分，但对于部分排序错误的情况，需要给予部分分数。题目要求采用第二种评分方式：  
计算学生答案中**最长的相对顺序正确的子序列**的长度（子序列不必连续，但需保持事件间的相对顺序与正确答案一致）。

输入包含多组测试数据。第一行为事件数 $n$（$2 \leq n \leq 20$）。第二行给出 $n$ 个整数，表示正确答案的事件排序（注意这里是**排名**顺序，表示事件 $i$ 的正确排名为 $c_i$）。随后每行是学生的答案，格式同正确答案。

输出每个学生答案的得分，即最长符合相对顺序的子序列长度。

> **注意**：题目中涉及两个关键概念：
> - **顺序**（$\texttt{Ordering}$）：事件按时间排列的顺序。
> - **排名**（$\texttt{Ranking}$）：事件在顺序中的位置（第几位）。

例如，正确答案为 `1 2 3 4`，学生答案为 `1 3 2 4`，则最长符合的子序列为 `1 2 4` 或 `1 3 4`，长度为 $3$。

## 解题思路

问题的本质是求**最长公共子序列（$\texttt{LCS}$）**，但经过转换可变为求**最长上升子序列（$\texttt{LIS}$）**，从而降低复杂度。

### 关键转换

设正确答案的顺序为 $c_1, c_2, ..., c_n$（$c_i$ 表示事件 $i$ 的正确排名）。学生给出的排名序列为 $r_1, r_2, ..., r_n$（$r_i$ 表示学生给事件 $i$ 的排名）。

我们要找的是学生序列中相对顺序与正确答案一致的子序列。  
如果我们将正确答案看作一个从事件到其正确排名的映射（即“事件 $i$ 的正确排名为 $c_i$”），那么学生答案中的每个事件 $i$ 对应的正确排名就是 $c_i$。  
若学生答案中事件 $i$ 出现在第 $pos$ 位，则其正确排名为 $c_i$。  
我们想找学生序列中一个子序列，使得这些事件的正确排名**是递增的**。  
因此，我们将学生答案的每个位置转换为其事件的正确排名，然后在该转换后的序列中求最长上升子序列（$\texttt{LIS}$）的长度，即为所求得分。

### 算法步骤

1. 读入正确答案，建立数组 $order$，使得 $order[rank] = event$，即排名 $rank$ 对应的事件编号。
2. 对每个学生答案：
   - 将学生答案中每个位置 $i$ 的事件编号转换为该事件的正确排名，得到新序列 $events$。
   - 在 $events$ 序列上计算最长上升子序列的长度。
3. 输出每个学生答案的 $\texttt{LIS}$ 长度。

### 时间复杂度

事件数 $n \leq 20$，直接 $O(n^2)$ 的 $\texttt{LIS}$ 算法完全可行。也可使用 $O(n \log n)$ 的优化算法。

## 参考代码

以下是三种实现，它们核心思路相同，但在数据结构和 $\texttt{LIS}$ 实现细节上略有差异。

### 实现一：

此版本使用数组存储，$\texttt{LIS}$ 采用 $O(n^2)$ 的 $\texttt{DP}$ 方法。

- 数组 `order[rank] = event` 存储正确顺序。
- `getIndex` 函数用于根据事件编号查找其正确排名。
- `lis` 函数用动态规划计算最长上升子序列。

```cpp
// History Grading
// UVa ID: 111
// Verdict: Accepted
// Submission Date: 2011-11-25
// UVa Run Time: 0.052s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 可以将问题转化为求最长上升子序列的问题。

#include <bits/stdc++.h>

using namespace std;

#define MAXN 25

int order[MAXN], events[MAXN], length[MAXN], n;

int lis(void) {
	for (int i = 1; i <= n; i++) length[i] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < i; j++)
			if (events[j] < events[i] && (length[j] + 1) > length[i])
				length[i] = length[j] + 1;
	int maxLength = 1;
	for (int i = 1; i <= n; i++)
		maxLength = max(maxLength, length[i]);
	return maxLength;
}

int getIndex(int index) {
	for (int i = 1; i <= n; i++)
		if (order[i] == index)
			return i;
}

int main (int argc, char *argv[]) {
	string line;
	int index;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> index;
		order[index] = i;
	}
	cin.ignore(1024, '\n');
	while (getline(cin, line)) {
		istringstream iss(line);
		for (int i = 1; i <= n; i++) {
			iss >> index;
			events[index] = getIndex(i);
		}
		cout << lis() << endl;
	}
	return 0;
}
```

### 实现二：

与实现一类似，但使用 $\texttt{STL}$ 的 `find` 函数替代 `getIndex`，代码更简洁。

```cpp
// History Grading
// UVa ID: 111
// Verdict: Accepted
// Submission Date: 2016-02-29
// UVa Run Time: 0.003s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 25;

int order[MAXN], events[MAXN], length[MAXN], n;

int lis() {
    for (int i = 1; i <= n; i++) length[i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            if (events[j] < events[i] && (length[j] + 1) > length[i])
                length[i] = length[j] + 1;
    int maxLength = 1;
    for (int i = 1; i <= n; i++)
        maxLength = max(maxLength, length[i]);
    return maxLength;
}

int main(int argc, char *argv[]) {
    string line;
    int index;
    order[0] = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> index;
        order[index] = i;
    }
    cin.ignore(1024, '\n');
    while (getline(cin, line)) {
        istringstream iss(line);
        for (int i = 1; i <= n; i++) {
            iss >> index;
            events[index] = find(order, order + n, i) - order;
        }
        cout << lis() << endl;
    }
    return 0;
}
```

### 实现三

此版本使用 $O(n \log n)$ 的 $\texttt{LIS}$ 算法，并采用 `vector` 存储数据，代码更现代化。

```cpp
// History Grading
// UVa ID: 111
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> order, events;

int lis() {
    vector<int> M; M.push_back(events.front());
    for (auto it = events.begin() + 1; it != events.end(); it++)
        if (*it > M.back()) M.push_back(*it);
        else {
            auto location = upper_bound(M.begin(), M.end(), *it);
            *location = *it;
        }
    return M.size();
}

int main(int argc, char *argv[]) {
    int n, index; string line;
    cin >> n;
    order.resize(n); events.resize(n);
    for (int i = 1; i <= n; i++) {
        cin >> index;
        order[index - 1] = i;
    }
    cin.ignore(1024, '\n');
    while (getline(cin, line)) {
        istringstream iss(line);
        for (int i = 1; i <= n; i++) {
            iss >> index;
            events[index - 1] = find(order.begin(), order.end(), i) - order.begin();
        }
        cout << lis() << '\n';
    }
    return 0;
}
```

## 总结

本题的关键在于理解“相对顺序正确”等价于“正确排名递增”，从而将问题转化为 $\texttt{LIS}$ 问题。三种实现方法核心相同，差异主要在于：

- 实现一和实现二使用 $O(n^2)$ 的 $\texttt{DP}$ 计算 $\texttt{LIS}$，代码清晰易懂。
- 实现三使用 $O(n \log n)$ 的贪心+二分优化，效率更高，且使用 $\texttt{STL}$ 容器和算法，代码更简洁。
