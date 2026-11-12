[UVa 130 Roman Roulette](https://blog.csdn.net/metaphysis/article/details/156751790)

## 题目描述

这是一个关于约瑟夫问题变种的问题。题目背景源于历史学家弗拉维奥·约瑟夫斯的记载：在公元 $67$ 年的罗马-犹太冲突中，约瑟夫斯与 $40$ 名同伴被困在一个洞穴中。为了避免被俘，他们决定围成一个圈，按照一定规则轮流自杀。传统说法是，从某个人开始，顺时针数到第 $3$ 个人就杀掉，直到只剩一人。约瑟夫斯通过计算找到了自己存活的位置。

在本题中，规则稍有不同：

*   $n > 0$ 个人围成一个圆圈，顺时针编号为 $1$ 到 $n$ 。你的编号是 $1$ 。
*   给定一个起始编号 $i$ 和一个步长 $k$ ($k > 0$) 。
*   从 $i$ 开始，顺时针数 $k$ 个人，杀掉这个人。
*   然后，从被杀害者左边的人开始，再顺时针数 $k$ 个人，选中的人负责埋葬死者，然后回到死者的位置上。
*   接着，从刚才那个埋葬者的左边的人开始，继续顺时针数 $k$ 个人并杀掉，重复这个过程，直到只剩一个人。

题目要求：对于给定的 $n$ 和 $k$ ，你的程序需要找出 **起始编号 $i$** （$1 \leq i \leq n$），使得在这个 $i$ 开始的游戏中，**编号为 $1$ 的人（也就是你）** 是最后的幸存者。

**输入格式**：每行包含两个整数 $n$ 和 $k$ 。输入以一行 `0 0` 结束。$n \leq 100$。

**输出格式**：对于每行输入，输出一个整数，即能确保你存活的安全起始位置 $i$。

**样例输入**：
```
5 2
1 5
0 0
```
**样例输出**：
```
3
1
```

## 解题思路分析

本题是一个典型的模拟 $+$ 数学推导问题。由于 $n \leq 100$，规模较小，可以直接通过模拟游戏过程来解决。核心是：对于给定的 $n$ 和 $k$，我们不知道起始位置 $i$，但我们需要找到一个 $i$，使得从 $i$ 开始执行上述规则后，编号 $1$ 的人最后存活。

一个直接的方法是：对于每个可能的起始位置 $i$ ($1 \leq i \leq n$)，都模拟一遍游戏过程，检查编号 $1$ 的人是否幸存。如果幸存，则输出这个 $i$。由于 $n \leq 100$，最坏情况模拟 $100$ 次，每次最多进行 $n-1$ 轮淘汰，每轮需要遍历寻找被杀者和埋葬者，总时间复杂度约为 $O(n^3)$，在 $n=100$ 时完全可行。

然而，我们可以采用了另一种更高效、基于“对称性”的巧妙思路：

1.  **固定起始位置为 $1$ 进行模拟**：即假设游戏从编号1的人开始数（$i=1$）。我们模拟整个游戏过程，直到只剩一个人，记录下这个幸存者的编号，记为 $s$。
2.  **利用圆的对称性推导所求的 $i$**：当我们固定从 $1$ 开始，最终幸存者是 $s$。现在，我们想知道：如果想让编号 $1$ 的人存活，应该从哪个位置 $i$ 开始？
    *   考虑一个简单的对应关系：如果我们把整个圆圈 **逆时针旋转**，使得原来编号为 $s$ 的人现在处于“起始位置”（即原来编号 $1$ 的位置），那么在这个新的旋转后的圆圈里，**从位置 $1$ 开始游戏**，最后的幸存者就会是原来编号为 $1$ 的人（因为他现在处于原来 $s$ 的位置）。
    *   如何得到这个旋转量？从编号 $1$ 的位置逆时针数到 $s$ 的位置，需要经过多少人？从 $1$ 到 $s$（顺时针编号增大），顺时针移动 $s-1$ 步到达 $s$。那么，从 $1$ **逆时针** 移动到 $s$，相当于顺时针移动 $n - (s-1) = n - s + 1$ 步。
    *   更准确地说，如果我们从编号 $x$ 开始游戏能使得编号 $1$ 存活，那么当我们固定从 $1$ 开始游戏时，幸存者 $s$ 的位置，就应该是从 $x$ 开始逆时针到 $1$ 的距离所对应的那个人。公式推导结果为：安全起始位置 $i = (n - s + 1) \bmod n + 1$。这里取模 $n$ 再加 $1$ 是为了处理 $s=1$ 时 $i=1$ 的情况。

因此，算法步骤为：
1.  对于每组 $(n, k)$。
2.  模拟游戏，设定起始被杀位置 `killed` 初始为 `(k-1) % n`（因为从编号 $1$ 开始，即下标 $0$ 开始，数 $k$ 个人，第一个被杀的是下标 `(k-1)%n`）。
3.  进行循环，直到只剩一人：
    a. 找到当前 `killed`（被杀者）。
    b. 找到埋葬者 `burier`：从被杀者左边开始，再数 $k$ 个人。
    c. 将 `burier` 的位置“移动”到 `killed` 的位置（即 `victim[killed] = victim[burier]`），然后从列表中删除 `burier` 的位置（相当于埋葬者占据了死者的位置，原埋葬者位置空出）。
    d. 更新下一次计数的起点 `killed` 为当前 `killed` 位置的下一个位置（顺时针方向）。
4.  模拟结束后，得到幸存者编号 $s$。
5.  输出安全起始位置 $i = (n - s + 1) \bmod n + 1$。

## 代码实现分析

以下给出了三种能够获得通过的代码，它们核心思路一致，但在数据结构和模拟细节上略有不同。

### 实现一：（使用vector，原地调整）

这是最简洁的实现。使用 `vector<int>` 动态维护当前圆圈中的人。
*   `killed` 记录当前轮次要被杀的人的下标。
*   计算 `burier` 时，考虑从 `killed` 左边开始数 $k$ 个人，由于 `burier` 不能是 `killed` 自己，所以计算时需要跳过 `killed` 位置。代码通过 `(burier + (burier >= killed)) % victim.size()` 来调整，确保在删除 `burier` 元素后，`killed` 指向正确的新元素。
*   删除 `burier` 后，更新 `killed` 为下一轮起点。

### 实现二：（使用固定数组，标记法）

使用固定大小数组 `circle`，用 `0` 标记该位置的人已离开圆圈（被杀或已移动）。
*   定义了 `findCW` 函数，从给定 `start` 下标开始，顺时针数 `count` 个 **还在圈内** 的人，返回其下标。这里通过两层循环模拟环形遍历。
*   模拟过程：先找到被杀者 `killed`，将其标记为 `0`。再找到埋葬者 `burier`，将 `burier` 的值赋给 `killed` 位置（埋葬者移动到死者位置），然后将 `burier` 标记为 `0`。
*   下一轮起点 `killed` 设为 `(killed + 1) % n`。
*   最后遍历数组找到幸存者编号 $s$。

### 实现三：（使用 $\texttt{vector}$，标记法）

与实现二类似，但使用 `vector<int>` 而非固定数组，逻辑几乎相同，只是将数组操作改为 $\texttt{vector}$ 操作。

## 总结

本题的关键在于理解约瑟夫问题的变种规则，并利用对称性将“寻找安全起始位置”转化为“固定起始位置模拟求幸存者，再通过公式转换”。三种实现都采用了这一核心思想，主要区别在于数据结构的选择和模拟过程中下标处理的细节。由于数据规模小，三种方法都能在时间内高效运行。

---

## 参考代码

### 代码一

```cpp
// Roman Roulette
// UVa ID: 130
// Verdict: Accepted
// Submission Date: 2015-12-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    while (cin >> n >> k, n || k) {
        vector < int > victim;
        for (int i = 1; i <= n; i++) victim.push_back(i);
        int killed = (k - 1) % victim.size(), burier;
        while (victim.size() > 1) {
            burier = (killed - 1 + k) % (victim.size() - 1);
            burier = (burier + (burier >= killed)) % victim.size();
            victim[killed] = victim[burier];
            victim.erase(victim.begin() + burier);
            killed = (killed - (burier < killed) + k) % victim.size();
        }
        cout << (n - victim.front() + 1) % n + 1 << endl;
    }
    return 0;
}
```

### 代码二

```cpp
// Roman Roulette
// UVa ID: 130
// Verdict: Accepted
// Submission Date: 2015-12-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_NUMBER = 100;

int n, k;
int circle[MAX_NUMBER + 1];

// 模拟计数的过程。
int findCW(int start, int count) {
    for (int i = start; i < n; i++)
        if (circle[i] > 0 && ((--count) == 0))
            return i;
    while (true) {
        for (int i = 0; i < n; i++)
            if (circle[i] > 0 && ((--count) == 0))
                return i;
    }
}

// 找到幸存者的编号。
int findSurvivor() {
    for (int i = 0; i < n; i++)
        if (circle[i] > 0)
            return circle[i];
}

int main() {
    int counter;
    while (cin >> n >> k, n || k) {
        counter = n;
        for (int i = 1; i <= n; i++)
            circle[i - 1] = i;
        int killed = 0, burier;
        while (counter > 1) {
            killed = findCW(killed, k);
            circle[killed] = 0;
            burier = findCW(killed, k);
            circle[killed] = circle[burier];
            circle[burier] = 0;
            // 根据题意，往顺时针方向移动一个位置开始下一轮计数。
            killed = (killed + 1) % n;
            counter--;
        }
        // 根据环形对称，假设幸存者的编号为s，那么从编号为1的人往逆时针
        // 方向数s个人，然后从此位置开始计数，则幸存者为原编号为1的人。
        cout << (n - findSurvivor() + 1) % n + 1 << endl;
    }
    return 0;
}
```

### 代码三

```cpp
// Roman Roulette
// UVa ID: 130
// Verdict: Accepted
// Submission Date: 2015-12-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> circle;

// 模拟计数的过程。
int findCW(int start, int count) {
    for (int i = start; i < circle.size(); i++)
        if (circle[i] > 0 && ((--count) == 0))
            return i;
    while (true) {
        for (int i = 0; i < circle.size(); i++)
            if (circle[i] > 0 && ((--count) == 0))
                return i;
    }
}

// 找到幸存者的编号。
int findSurvivor() {
    for (int i = 0; i < circle.size(); i++)
        if (circle[i] > 0)
            return circle[i];
}

int main() {
    int n, k;
    while (cin >> n >> k, n || k) {
        circle.clear();
        for (int i = 1; i <= n; i++) circle.push_back(i);
        int killed = 0, burier;
        while (n > 1) {
            killed = findCW(killed, k);
            circle[killed] = 0;
            burier = findCW(killed, k);
            circle[killed] = circle[burier];
            circle[burier] = 0;
            // 根据题意，往顺时针方向移动一个位置开始下一轮计数。
            killed = (killed + 1) % circle.size();
            n--;
        }
        // 根据环形对称，假设幸存者的编号为s，那么从编号为1的人往逆时针方向数s
        // 个人，然后从此位置开始计数，则幸存者为原编号为1的人。
        cout << (circle.size() - findSurvivor() + 1) % circle.size() + 1 << endl;
    }
    return 0;
}
```
