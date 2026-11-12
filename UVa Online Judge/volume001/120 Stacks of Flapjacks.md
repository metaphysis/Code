[UVa 120 Stacks of Flapjacks](https://blog.csdn.net/metaphysis/article/details/156644658)

## 题目概述

本题要求模拟一系列煎饼叠的排序过程。给定一个煎饼叠，每个煎饼有唯一的直径（整数），且叠的顺序是从上到下给出（输入时最上面的煎饼最先出现）。排序的目标是让最大的煎饼位于底部，最小的位于顶部。

排序的唯一操作是“翻转”（$\texttt{flip}$）：将铲子插入到煎饼叠的某个位置 $k$（从底部开始计数，底部位置为 $1$），然后将从顶部到第 $k$ 个煎饼之间的所有煎饼顺序反转。一次翻转操作由参数 $k$ 表示，即要翻转的子叠的底部位置。

我们需要输出原始叠的状态，然后输出一系列翻转操作的参数（用空格分隔），最后以 $0$ 结尾，表示排序完成。

**输入格式**  
- 每个测试用例一行，表示一个煎饼叠，从上到下给出煎饼直径，以空格分隔。
- 煎饼数量在 $1$ 到 $30$ 之间，直径在 $1$ 到 $100$ 之间。
- 输入以文件结束符（$\texttt{EOF}$）结束。

**输出格式**  
- 对于每个叠，先输出原始叠（原样输出一行），然后输出一系列翻转操作，最后输出 $0$。

---

## 解题思路

本题的关键在于模拟翻转操作，并找到一种策略使得叠有序。一个直观的贪心策略如下：

1. 从最大的煎饼开始考虑，将其放到正确的位置（底部）。
2. 假设当前考虑第 $i$ 大的煎饼（$i$ 从大到小递减）：
   - 如果它已经在正确位置（即从底部数第 $i$ 个位置），则跳过。
   - 否则，先找到它在当前叠中的位置（从顶部数）。
   - 如果它不在顶部，则通过一次翻转将它翻到顶部。
   - 然后再通过一次翻转将它从顶部翻到目标位置（即从底部数第 $i$ 个位置，等价于从顶部数第 $n-i+1$ 个位置）。

这样，每次最多需要两次翻转就能将一个煎饼归位。

---

### 算法步骤

1. 读取一行输入，存储原始叠 `original`，并同时存储一个副本 `pancakes` 用于排序。
2. 对 `pancakes` 按直径升序排序，同时记录每个煎饼的原始索引。
3. 从最大直径的煎饼开始（即排序后的最后一个）：
   - 在当前叠 `original` 中找到该煎饼的位置 `marker`（通过比较原始索引）。
   - 如果 `marker` 不等于目标位置 $i$（从 $0$ 开始计数，`i` 为从大到小的索引）：
     - 若 `marker` 不在顶部（`marker != 0`），则执行 `flip(capacity - marker)` 将其翻到顶部。
     - 再执行 `flip(capacity - i)` 将其从顶部翻到目标位置。
4. 每次翻转操作后，输出翻转参数（注意输出的是从底部计数的位置）。
5. 最后输出 `0`。

---

### 复杂度分析

- 每个煎饼最多进行两次翻转，每次翻转的时间复杂度为 $O(n)$。
- 总时间复杂度：$O(n^2)$，其中 $n \leq 30$，完全可行。
- 空间复杂度：$O(n)$。

---

## 代码实现

```cpp
// Stacks of Flapjacks
// UVa ID: 120
// Verdict: Accepted
// Submission Date: 2016-04-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>
using namespace std;
	
#define MAXSIZE 30
	
struct pancake {
	int diameter;
	int index;
};
	
pancake pancakes[MAXSIZE];
pancake original[MAXSIZE];
	
bool cmp(pancake x, pancake y) {
	return x.diameter < y.diameter;
}
	
void flip(int pos, int size) {
	pancake tmp;
	int i = 0, j = size - pos;
	for (; i < j; i++, j--)
		if (original[i].diameter != original[j].diameter) {
			tmp = original[i];
			original[i] = original[j];
			original[j] = tmp;
		}
}
	
int main(int ac, char *av[]) {
    cin.tie(0); cout.sync_with_stdio(false);
    string line;
	while (getline(cin, line)) {
		// 回显。
		cout << line << endl;
	    // 读入数据。
		int capacity = 0;
		istringstream iss(line);
		while (iss >> pancakes[capacity].diameter)	{
			pancakes[capacity].index = capacity;
			original[capacity] = pancakes[capacity];
			capacity++;
		}
		// 排序。
		sort(pancakes, pancakes + capacity, cmp);
		// 执行翻转操作，若第 i 大元素未在第i位上，则先找到其序号，然后
		// 先将其翻转到顶端，然后再翻转到位置i。
		for (int i = capacity - 1; i >= 0; i--) {
			// 在当前序列中找到该元素。
			// 假如数原来的序号与当前的序号不等，需要翻转操作。
			int marker;
			for (int j = 0; j < capacity; j++)
				if (original[j].index == pancakes[i].index) {
					marker = j;
					break;
				}
	
			if (marker != i)	{
				if (marker != 0)	{
					cout << (capacity - marker) << " ";
					flip(capacity - marker, capacity);
				}
				cout << (capacity - i) << " ";
				flip(capacity - i, capacity);
			}
		}
			cout << "0" << endl;
	}
	return 0;
}
```
