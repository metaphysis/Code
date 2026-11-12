[UVa 133 The Dole Queue](https://blog.csdn.net/metaphysis/article/details/156788486)

## 题目描述

本题模拟了一个裁员队列的过程。 $N$ 个申请人围成一个圆圈，从编号 $1$ 开始逆时针编号到 $N$ 。每天，两位官员分别从编号 $1$（逆时针方向）和编号 $N$（顺时针方向）开始数人。一位官员每次数 $k$ 个有效申请人（跳过已被选中的人），另一位官员每次数 $m$ 个有效申请人。被选中的两个人将同时离开圆圈（如果两人选中同一人，则该人仅离开一次）。重复此过程，直到所有人都被选中。要求按离开的顺序输出编号，每对编号（或单独编号）占 $3$ 字符宽，用逗号分隔，末尾不加逗号。

**输入格式**  
多组数据，每组一行三个整数 $N, k, m$ ，满足 $k, m > 0, 0 < N < 20$ 。以 `0 0 0` 结束输入。

**输出格式**  
对每组数据，输出一行，表示离开顺序，格式如上所述。

**样例输入**
```
10 4 3
0 0 0
```
**样例输出**
```
  4  8,  9  5,  3  1,  2  6, 10,  7
```

---

## 解题思路

本题是一个典型的约瑟夫环问题的变种，区别在于有两个方向同时进行数人，且每次选中的两人同时离开。由于 $N < 20$ ，数据规模很小，可以直接用数组模拟整个过程。

### 关键点分析
1. **模拟圆圈**  
   使用数组 `circle` 存储当前还在圈中的人的编号，被选中的人将其值置为 $0$ 表示离开。

2. **数人逻辑**  
   - 逆时针方向（从当前位置 `right` 开始，数 $k$ 个有效的人）
   - 顺时针方向（从当前位置 `left` 开始，数 $m$ 个有效的人）
   由于选中的人会离开，所以数人时需要跳过值为 $0$ 的位置。

3. **同时离开**  
   如果两个官员选中同一个人，只输出一次，并且只将 $n$ 减少 $1$；否则分别输出并减少 $2$。

4. **输出格式**  
   使用 `setw(3)` 控制输出宽度为 $3$ 字符，用逗号分隔不同对（或单独编号），注意末尾没有逗号。

---

## 算法步骤
1. 读入 $N, k, m$ ，若全为 $0$ 则结束。
2. 初始化数组 `circle` 为 $1$ 到 $N$。
3. 设置两个指针 `right` 和 `left`，分别表示逆时针和顺时针的起始位置。
4. 当还有人未离开时：
   - 从 `right` 开始逆时针数 $k$ 个有效位置，更新 `right` 为选中位置。
   - 从 `left` 开始顺时针数 $m$ 个有效位置，更新 `left` 为选中位置。
   - 输出 `circle[right]`（占 $3$ 字符），将其置 $0$，剩余人数减一。
   - 如果 `right != left`，输出 `circle[left]`（占 $3$ 字符），将其置 $0$，剩余人数再减一。
   - 如果还有人剩余，输出逗号。
5. 输出换行，处理下一组数据。

---

## 代码实现

```cpp
// The Dole Queue
// UVa ID: 133
// Verdict: Accepted
// Submission Date: 2015-12-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, k, m;
vector<int> circle;

// count off in counter-clockwise and return the index of target.
int findCCW(int right, int number) {
    for (int i = right; i < circle.size(); i++)
        if (circle[i] > 0 && ((--number) == 0))
            return i;
    while (true) {
        for (int i = 0; i < circle.size(); i++)
            if (circle[i] > 0 && ((--number) == 0))
                return i;
    }
}

// count off in clockwise and return the index of target.
int findCW(int left, int number) {
    for (int i = left; i >= 0; i--)
        if (circle[i] > 0 && ((--number) == 0))
            return i;
    while (true) {
        for (int i = circle.size() - 1; i >= 0; i--)
            if (circle[i] > 0 && ((--number) == 0))
                return i;
    }
}

int main() {
    setfill(' ');
    while (cin >> n >> k >> m, n || k || m) {
        circle.clear();
        for (int i = 1; i <= n; i++)
            circle.push_back(i);
        int right = 0, left = n - 1;
        while (n > 0) {
            right = findCCW(right, k);
            left = findCW(left, m);
            cout << setw(3) << circle[right];
            circle[right] = 0;
            n--;
            if (right != left) {
                cout << setw(3) << circle[left];
                circle[left] = 0;
                n--;
            }
            if (n > 0) cout << ",";
        }
        cout << endl;
    }
    return 0;
}
```

---

## 复杂度分析
- 时间复杂度：每次数人最多遍历整个数组，总复杂度为 $O(N^2)$，由于 $N \leq 20$，完全可行。
- 空间复杂度： $O(N)$。

---

## 总结
本题是一个有趣的模拟题，关键在于理解两个方向同时数人的逻辑，并处理好选中同一人的特殊情况。输出格式要求较严格，注意使用 `setw` 控制宽度和逗号的位置即可。
