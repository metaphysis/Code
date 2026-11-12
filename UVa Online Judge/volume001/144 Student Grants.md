[UVa 144 Student Grants](https://blog.csdn.net/metaphysis/article/details/157464219)

## 题目理解

本题模拟了一种特殊的学生补助金发放系统。政府为了“劝阻”学生接受高等教育，设计了一套复杂的发放流程：

- 每位学生每年可获得 $40$ 美元的补助金，在其生日最近的工作日发放。
- 每天最多有 $N$（$1 \leq N \leq 25$）名学生到补助金部门排队领取。
- 发放使用一台特殊的自动取款机（$\texttt{ATM}$），机器内部有一个金库（存放大量 $1$ 美元硬币）和一个输出存储区。
- 机器只在输出存储区为空时，才会从金库向输出存储区补充硬币，且补充规则如下：
  1. 早晨开机时，输出存储区为空，立即补充 $1$ 枚硬币。
  2. 当这些硬币被取出后，下一次补充 $2$ 枚。
  3. 每次补充数量依次增加，直到达到预设上限 $k$（$1 \leq k \leq 40$），然后重置为 $1$，继续循环。
- 学生依次插入学生卡，机器将输出存储区的所有硬币支付给学生，并更新卡上记录的总金额。
- 如果学生累计领取金额不足 $40$ 美元，则取卡重新排到队尾。
- 如果本次支付后累计金额超过 $40$ 美元，则仅支付至刚好 $40$ 美元，剩余硬币留在输出存储区给下一位学生，该学生离开队伍。
- 需要计算所有学生离开队列的顺序。

## 解题思路

这是一个典型的**队列模拟**问题。我们可以将整个过程分解为以下步骤：

1. **初始化学生队列**：每个学生用结构体表示，包含 `id`（初始排队顺序）和 `withdraw`（已领取金额）。
2. **模拟硬币发放循环**：
   - 维护变量 `coins` 表示当前应发放的硬币数量（按 $1, 2, \dots, k, 1, 2, \dots$ 循环）。
   - 维护变量 `remain` 表示上一位学生领取后输出存储区剩余的硬币数（如果刚好 $40$ 美元，则 `remain = 0`；如果超出，则 `remain` 为超出部分留给下一位学生）。
   - 每次处理队首学生：
     - 计算本次可领取的硬币数 `current`：若 `remain > 0`，则直接使用 `remain`；否则从 `coins` 循环中取下一个值，并更新 `coins`（若超过 $k$ 则重置为 $1$）。
     - 若该学生 `withdraw + current >= 40`，则支付至刚好 $40$，该学生离开，记录其 `id`，并更新 `remain = withdraw + current - 40`。
     - 否则，该学生 `withdraw += current`，重新入队尾，`remain = 0`。
3. **输出离开顺序**：按离开顺序输出学生编号，每个编号占 $3$ 个字符宽度，右对齐。

## 算法复杂度

- 时间复杂度：最坏情况下每个学生可能需要多次排队才能领满 $40$ 美元，但总支付次数不超过 $N \times 40$，因此为 $O(N \times 40)$，对本题规模完全可行。
- 空间复杂度：使用队列存储学生，为 $O(N)$。

## 代码实现

```cpp
// Student Grants
// UVa ID: 144
// Verdict: Accepted
// Submission Date: 2016-01-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct student {
    int id, withdraw;
};

int main() {
    int n, k;
    while (cin >> n >> k, n || k) {
        queue<student> students;
        for (int i = 1; i <= n; i++) students.push((student){i, 0});
        int coins = 0, remain = 0;
        while (true) {
            int current = (remain > 0) ? remain : ((++coins) > k ? (coins = 1) : coins);
            if (students.empty()) break;
            student aStudent = students.front();
            students.pop();
            if ((aStudent.withdraw + current) >= 40) {
                remain = aStudent.withdraw + current - 40;
                cout << setw(3) << right << aStudent.id;
            } else {
                aStudent.withdraw += current;
                students.push(aStudent);
                remain = 0;
            }
        }
        cout << endl;
    }
    return 0;
}
```
