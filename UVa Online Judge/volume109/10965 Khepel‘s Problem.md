
> **摘要**：本题给定一个 $m \times n$ 的矩形花园，其中若干格子放置了洒水器。每个洒水器按“朝当前方向喷水 $p$ 秒、旋转 $1$ 秒”的方式循环工作，喷水范围为沿当前方向距离不超过 $R$ 的格子。要求在时间区间 $[a, b]$ 内，统计既不含洒水器、也不会被任何洒水器喷到的格子总数。核心思路是利用喷水过程的周期性（周期 $T = p + 1$），将“某方向在 $[a, b]$ 内是否喷过水”转化为对 $jT$ 的整数不等式与模 $4$ 同余判定，再逐格标记被覆盖的格子，最终统计剩余安全格子数。时间复杂度 $O(k \cdot 4 \cdot R_{\max} + mn)$。

## 题目描述

$\texttt{Khepel}$ 是一只生活在 $m \times n$ 矩形花园中的猫，花园中某些格子放置了洒水器。每个洒水器在任一时刻只能朝一个方向喷水，其工作方式如下：

- 朝当前方向持续喷水 $p$ 秒；
- 停止喷水，然后花费 $1$ 秒顺时针旋转 $90^\circ$；
- 转向新方向后继续喷水，如此循环。

每个洒水器有固定的喷水范围 $R$，表示它能沿当前方向覆盖到距离自身位置不超过 $R$ 个格子的所有格子（不包括自身所在格）。所有洒水器在时间 $0$ 开始时即按初始方向开始喷水。

$\texttt{Khepel}$ 希望在某段时间 $[a, b]$ 内睡觉，但他不能睡在洒水器所在的格子，也不能睡在任何会被洒水器喷到的格子（即使在区间内仅被喷过一次也不行）。给定花园尺寸、洒水器参数以及时间段 $[a, b]$，求该时间段内始终干燥且不含洒水器的格子总数。

## 输入格式

输入包含多个测试用例。每个测试用例的第一行包含三个整数 $m, n, k$，分别表示花园的行数、列数和洒水器数量，满足 $1 \le m, n \le 100$，$0 \le k \le 1000$。  
接下来 $k$ 行，每行描述一个洒水器，格式为：四个整数 $r_i, c_i, p_i, R_i$ 和一个字符 $d_i$，其中：

- $1 \le r_i \le m$，$1 \le c_i \le n$ 表示洒水器所在的行列坐标（左上角为 $(1,1)$）；
- $1 \le p_i \le 10^6$ 表示每个方向的喷水持续时间（秒）；
- $R_i \ge 0$ 表示喷水范围；
- $d_i \in \{ \texttt{‘N’}, \texttt{‘S’}, \texttt{‘E’}, \texttt{‘W’} \}$ 表示初始方向，分别代表北、南、东、西。

每个测试用例的最后一行包含两个整数 $a, b$，满足 $0 \le a \le b \le 10^9$，表示 $\texttt{Khepel}$ 计划睡觉的时间区间为从时刻 $a$ 开始到时刻 $b$ 结束（闭区间）。  
输入以 $m = n = k = 0$ 结束。

## 输出格式

对于每个测试用例，输出一行一个整数，表示 $\texttt{Khepel}$ 可以安全睡觉的格子总数。

## 样例

### 样例输入
```text
100 100 1
1 1 100 1 E
0 2
0 0 0
```

### 样例输出
```text
9998
```

样例解释：花园大小为 $100 \times 100$，唯一洒水器位于 $(1,1)$，初始朝东，$p = 100$，$R = 1$。它在 $[0, 100)$ 秒内朝东喷水，覆盖 $(1,2)$，因此这两个格子均不可睡，其余 $9998$ 个格子安全。

---

## 题目分析

每个洒水器的行为具有严格的周期性。其一次完整循环包含“朝当前方向喷水 $p$ 秒”和“原地旋转 $1$ 秒”两个阶段，因此周期长度 $T = p + 1$。在第 $j$ 个周期（$j \ge 0$）中，喷水区间为 $[jT, \; jT + p)$，旋转区间为 $[jT + p, \; (j+1)T)$。方向按顺时针顺序轮转：北（$\texttt{N}$）→ 东（$\texttt{E}$）→ 南（$\texttt{S}$）→ 西（$\texttt{W}$）→ 北……，所以第 $j$ 个周期喷水时的方向由初始方向加上 $j$ 对 $4$ 取模确定。

由于喷水区间是左闭右开的，时刻点 $a$ 或 $b$ 若恰好落在喷水结束的边界上，则该时刻不喷水。时间范围 $[a, b]$ 内的任意格子，只要存在某个洒水器在某个时刻向该格子方向喷水且距离在 $R$ 以内，该格子即被判定为不可睡。因此问题转化为：对于每个方向，判断该方向对应的喷水区间是否与 $[a, b]$ 有交集，若有，则沿该方向标记所有被覆盖的格子。

本题数据规模较小（格子总数 $10^4$，洒水器总数 $10^3$），可采用直接枚举每个洒水器、每个方向、每个可达格子的方式完成标记，关键仅在于正确判定“某个方向在 $[a, b]$ 内是否至少喷过一次水”。

---

## 解题思路

#### 步骤 $\texttt{1}$. 方向与下标映射

将四个方向映射为整数索引：$0$ 表示北，$1$ 表示东，$2$ 表示南，$3$ 表示西。行坐标增量为 $(-1, 0, 1, 0)$，列坐标增量为 $(0, 1, 0, -1)$，分别对应北、东、南、西。顺时针旋转即索引 $+1$ 后对 $4$ 取模。

#### 步骤 $\texttt{2}$. 单个方向有效性的判定

对于某个洒水器，设其初始方向索引为 $\textit{init}$，周期为 $T$。考察目标方向索引 $\textit{dir}$（$0 \le \textit{dir} \le 3$）。该方向在第 $j$ 个喷水区间出现，当且仅当：

$$
j \bmod 4 = (\textit{dir} - \textit{init} + 4) \bmod 4
$$

记该模值为 $\textit{need}$。同时，该喷水区间 $[jT, \; jT + p)$ 必须与 $[a, b]$ 相交。两个区间相交的充要条件是：

- $jT \le b$（因为若 $jT > b$，则整个区间在 $b$ 之后）；
- $jT + p > a$（因为若 $jT + p \le a$，则整个区间在 $a$ 之前结束；特别地，当 $jT + p = a$ 时，时刻 $a$ 不在喷水区间内，因此必须严格大于）。

于是存在整数 $j$ 满足：

$$
a - p < jT \le b
$$

由于 $jT$ 为整数，上式等价于：

$$
a - p + 1 \le jT \le b
$$

令 $L = a - p + 1$，$U = b$。那么 $j$ 必须满足 $\lceil L / T \rceil \le j \le \lfloor U / T \rfloor$，且 $j \ge 0$。在该范围内检查是否存在 $j \equiv \textit{need} \pmod 4$ 即可。

#### 步骤 $\texttt{3}$. 标记被淋湿的格子

若某方向有效，则洒水器会沿该方向覆盖距离 $1$ 到 $R$ 的所有格子（距离 $0$ 即自身所在格，已提前标记为不可睡）。逐格向该方向前进，每到达一个在花园边界内的格子就将其标记为不可睡；一旦越界则停止（因为后续格子均越界）。

#### 步骤 $\texttt{4}$. 统计答案

维护一个 $m \times n$ 的布尔数组，初始均为可睡。遍历所有洒水器，先将其自身所在格置为不可睡，再根据有效方向标记覆盖格。最后统计数组中仍为可睡的格子数量并输出。

---

## 代码实现

```cpp
// Khepel's Problem
// UVa ID: 10965
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Sprinkler {
    int r, c, p, R, init;
};

int getDirIndex(char ch) {
    if (ch == 'N') return 0;
    if (ch == 'E') return 1;
    if (ch == 'S') return 2;
    return 3;
}

long long ceilDiv(long long a, long long b) {
    if (a >= 0) return (a + b - 1) / b;
    else return a / b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n, k;
    while (cin >> m >> n >> k) {
        if (m == 0 && n == 0 && k == 0) break;
        vector<vector<bool>> safe(m, vector<bool>(n, true));
        vector<Sprinkler> sprs;
        sprs.reserve(k);
        int dr[4] = {-1, 0, 1, 0};
        int dc[4] = {0, 1, 0, -1};
        for (int i = 0; i < k; ++i) {
            int r, c, p, R;
            char d;
            cin >> r >> c >> p >> R >> d;
            --r; --c;
            safe[r][c] = false;
            sprs.push_back({r, c, p, R, getDirIndex(d)});
        }
        long long a, b;
        cin >> a >> b;
        for (const auto &sp : sprs) {
            long long T = (long long)sp.p + 1;
            for (int dir = 0; dir < 4; ++dir) {
                int needMod = (dir - sp.init + 4) % 4;
                long long low = a - sp.p + 1;
                long long high = b;
                long long jMin = ceilDiv(low, T);
                if (jMin < 0) jMin = 0;
                long long jMax = high / T;
                if (jMin > jMax) continue;
                long long rem = (needMod - jMin % 4 + 4) % 4;
                long long first = jMin + rem;
                if (first > jMax) continue;
                for (int step = 1; step <= sp.R; ++step) {
                    int nr = sp.r + dr[dir] * step;
                    int nc = sp.c + dc[dir] * step;
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n) break;
                    safe[nr][nc] = false;
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (safe[i][j]) ++ans;
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 总结

本题的核心难点在于准确处理喷水区间与询问区间 $[a, b]$ 的交集判定，特别是区间端点处的开闭性。周期性的利用将连续时间问题转化为离散的模运算问题，避免了模拟大规模时间。由于数据规模不大，直接枚举每个洒水器的每个方向并逐格标记即可完成。

关键技巧包括：

- 将喷水过程建模为周期 $T = p + 1$，喷水方向由周期序号对 $4$ 取模决定；
- 区间相交条件转化为对 $jT$ 的不等式 $a - p < jT \le b$，并正确使用整数上下界；
- 使用布尔数组记录安全状态，最终统计答案。

该解法时间复杂度为 $O(k \cdot 4 \cdot R_{\max} + m n)$，其中 $R_{\max} \le \max(m, n)$，空间复杂度为 $O(m n)$，足以通过所有测试数据。
