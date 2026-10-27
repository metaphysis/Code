## 题目描述

给定 $10$ 块长度为 $5$ 的 $01$ 板，每块板描述了一条长度为 $5$ 的缝隙序列，其中 `0` 表示深缝，`1` 表示浅缝。  
将这些板中的 $5$ 块作为**水平板**，其余 $5$ 块作为**垂直板**，并排布成一个 $5 \times 5$ 的格子。水平板放在 $5$ 个行位置，垂直板放在 $5$ 个列位置。要求每个交叉点处的两个缝隙深度互补：若水平板在该列的值为 $0$，则垂直板在该行的值必须为 $1$；反之亦然。  

求在所有可能的板划分、排列和翻转（板可以左右翻转，即 $01$ 串反转）下，**本质不同**的配置数量。旋转和镜像视为同一种配置。

## 输入格式

输入包含多组测试数据，每组数据占一行，包含 $10$ 个长度为 $5$ 的 $01$ 字符串，相邻字符串之间用空格分隔。  
每个 $01$ 串表示一块板的缝隙描述。  
输入以单独一行 `END` 结束。

## 输出格式

对于每组测试数据，输出一行一个整数，表示本质不同的配置数量。

## 样例

输入

```
10000 01000 00100 11000 01100 11111 01110 11100 10110 11110
10101 01000 00000 11001 01100 11101 01110 11100 10110 11010
END
```

输出

```
40
6
```

## 题目分析

本题的核心是：在 $10$ 块板中选出 $5$ 块作为水平板，其余 $5$ 块作为垂直板，然后分别对水平板和垂直板进行排列，并允许每块板选择是否左右翻转，使得所有交叉点满足互补条件。最后需要统计在旋转和镜像意义下互不相同的配置数。

直接枚举所有可能的划分、排列和翻转会得到天文数字，但 $10$ 块板的数量适中，可以通过剪枝回溯和归一化去重解决。

关键难点在于：
1. **枚举方式**：需要一种高效的搜索顺序，能够尽早发现不合法分支并剪枝。
2. **去重处理**：旋转和镜像会使同一配置产生多个等价表示，需要归一化或利用对称性破缺来保证唯一性。
3. **板的翻转**：对称板（左右翻转后相同）的翻转不会产生新板，需要避免重复计数。

## 解题思路

### 枚举策略：交替回溯

由于 $5$ 个水平行和 $5$ 个垂直列相互制约，我们采用**交替放置**的方式：依次放置行 $0$，列 $0$，行 $1$，列 $1$，…，行 $4$，列 $4$。每放置一个行或列时，立即检查它与已放置部分是否冲突，若冲突则回溯。这种顺序能够尽早剪枝，大大减少搜索空间。

### 板翻转控制

对于每一块板，我们预先计算其原始值 $\textit{original}[i]$ 和左右翻转值 $\textit{reversed}[i]$。若两者相同，则该板为**对称板**，翻转不会产生新板，因此搜索时只尝试原始方向；若不同，则尝试原始和翻转两个方向。

### 归一化去重

当 $10$ 个行和列全部放置完毕时，我们得到一个完整的 $5 \times 5$ 水平矩阵（每个 $H[r]$ 是第 $r$ 行的 $5$ 位值）。将其编码为一个 $25$ 位整数，然后应用 $8$ 个二面体群变换（$4$ 个旋转 + $4$ 个镜像），取字典序最小的 $25$ 位字符串作为该配置的规范表示，插入集合 $\texttt{all}$。这保证了**旋转**等价被消除。

### 镜像重复处理

由于我们在枚举中没有固定水平/垂直的角色（即任意 $5$ 块板都可以作为水平板），**水平镜像**（左右翻转整个格子）会将一个配置变换为另一个配置，而这两个配置在归一化后可能得到不同的字符串（因为镜像交换了水平板和垂直板的角色），但它们在物理上是同一种配置。因此，每个本质配置会被计数两次，最终答案应为 $\displaystyle \frac{|\texttt{all}|}{2}$。

### 正确性说明

- **完备性**：枚举覆盖了所有可能的水平板集合、排列和翻转，垂直板由剩余板匹配，因此所有合法配置都会被生成。
- **无漏解**：交替回溯保证了每个合法布局至少被访问一次。
- **无重解**：通过归一化和最终除以 $2$，消除了旋转和镜像引起的重复。

### 复杂度分析

- 搜索树节点数：最坏情况约为 $\binom{10}{5} \times 5! \times 2^5 \approx 10^6$，但剪枝大幅减少了实际访问量。
- 归一化：每次对 $25$ 位整数做 $8$ 次变换，开销极小。
- 总时间复杂度：$O(\text{实际访问节点数} \times 8)$，在 $10$ 组测试数据下运行时间远小于 $1$ 秒。
- 空间复杂度：$O(\text{去重集合大小})$，最多为本质配置数，不超过 $10^4$。

## 代码实现

```cpp
// Lattice Practices
// UVa ID: 687
// Verdict: Accepted
// Submission Date: 2026-07-05
// UVa Run Time: 0.230s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int original[10], reversed[10], H[5], V[5];
bool symmetry[10], used[10];

int getReverse(int x) {
    int y = 0;
    for (int i = 0; i < 5; ++i)
        if (x & (1 << i)) y |= (1 << (4 - i));
    return y;
}

int toMask(const string &s) {
    int x = 0;
    for (int i = 0; i < 5; ++i)
        if (s[i] == '1') x |= (1 << i);
    return x;
}

bool checkRow(int r) {
    for (int c = 4; c >= 0; c--) {
        if (V[c] == -1) continue;
        int hb = (H[r] >> c) & 1;
        int vb = (V[c] >> r) & 1;
        if (hb + vb != 1) return false;
    }
    return true;
}

bool checkCln(int c) {
    for (int r = 4; r >= 0; r--) {
        if (H[r] == -1) continue;
        int hb = (H[r] >> c) & 1;
        int vb = (V[c] >> r) & 1;
        if (hb + vb != 1) return false;
    }
    return true;
}

pair<int,int> transform(int op, int r, int c) {
    switch(op) {
        case 0: return {r, c};
        case 1: return {c, 4 - r};
        case 2: return {4 - r, 4 - c};
        case 3: return {4 - c, r};
        case 4: return {r, 4 - c};
        case 5: return {4 - r, c};
        case 6: return {c, r};
        case 7: return {4 - c, 4 - r};
    }
    return {r, c};
}

string toString(int bits) {
    string s;
    for (int r = 0; r < 5; ++r)
        for (int c = 0; c < 5; ++c)
            s += (bits & (1 << (r * 5 + c))) ? '1' : '0';
    return s;
}

set<string> all;

void normalize() {
    int bits = 0;
    for (int i = 0; i < 5; i++) bits |= H[i] << (5 * i);
    string best = toString(bits);
    for (int op = 1; op < 8; ++op) {
        int nb = 0;
        for (int r = 0; r < 5; ++r)
            for (int c = 0; c < 5; ++c)
                if (bits & (1 << (r * 5 + c))) {
                    auto p = transform(op, r, c);
                    nb |= (1 << (p.first * 5 + p.second));
                }
        string s = toString(nb);
        if (s < best) best = s;
    }
    all.insert(best);
}

void dfs(int step) {
    if (step == 10) {
        normalize();
        return;
    }
    if (step % 2 == 0) {
        int r = step / 2;
        if (H[r] != -1) {
            dfs(step + 1);
            return;
        }
        for (int id = 0; id < 10; ++id) {
            if (used[id]) continue;
            used[id] = true;
            H[r] = original[id];
            if (checkRow(r))
                dfs(step + 1);
            H[r] = -1;
            used[id] = false;
            if (!symmetry[id]) {
                used[id] = true;
                H[r] = reversed[id];
                if (checkRow(r))
                    dfs(step + 1);
                H[r] = -1;
                used[id] = false;
            }
        }
    } else {
        int c = step / 2;
        if (V[c] != -1) {
            dfs(step + 1);
            return;
        }
        for (int id = 0; id < 10; ++id) {
            if (used[id]) continue;
            used[id] = true;
            V[c] = original[id];
            if (checkCln(c))
                dfs(step + 1);
            V[c] = -1;
            used[id] = false;
            if (!symmetry[id]) {
                used[id] = true;
                V[c] = reversed[id];
                if (checkCln(c))
                    dfs(step + 1);
                V[c] = -1;
                used[id] = false;
            }
        }
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string token;
    while (cin >> token) {
        if (token == "END") break;
        vector<int> boards(10);
        boards[0] = toMask(token);
        for (int i = 1; i < 10; ++i) {
            cin >> token;
            boards[i] = toMask(token);
        }
        for (int i = 0; i < 10; ++i) {
            original[i] = boards[i];
            reversed[i] = getReverse(original[i]);
            symmetry[i] = (original[i] == reversed[i]);
        }
        all.clear();
        memset(used, 0, sizeof(used));
        for (int i = 0; i < 5; ++i) H[i] = V[i] = -1;
        dfs(0);
        cout << all.size() / 2 << '\n';
    }
    return 0;
}
```

## 总结

本题的核心技巧是**交替回溯 + 二面体群归一化 + 镜像除以二**。  
- 交替回溯利用行与列的互补约束进行强剪枝，避免指数级枚举。  
- 归一化通过 $8$ 个变换取最小字符串，简洁地消除了旋转重复。  
- 由于枚举中没有固定水平/垂直角色，镜像会导致双重计数，输出时除以 $2$ 即得正确结果。  

这种策略在面对小规模组合计数（如 $5 \times 5$ 格子）且要求去重时非常有效，也适用于类似“棋盘覆盖”、“拼图计数”等问题。  
最终代码简洁高效，通过了在线评测的所有测试数据。
