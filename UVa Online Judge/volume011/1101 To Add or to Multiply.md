
> **摘要**：本题要求构造一个由 `A`（加 $a$）和 `M`（乘 $m$）组成的最短程序，使得区间 $[p,q]$ 内的任意输入经该程序变换后都落入区间 $[r,s]$，长度相同时取字典序最小者。核心思路是将程序参数化为 $y = x \cdot m^k + a \cdot S$，把区间约束转化为整数 $S$ 的上下界 $[L_k, U_k]$，再用 $m$ 进制贪心分配系数最小化加法次数，并仅在左端点与进位点处枚举候选 $S$。由于 $m^k$ 增长迅速，乘法次数 $k$ 不超过约 $30$，整体复杂度为 $O(K^2)$，可高效求解。

## 题目描述

$\texttt{Industrial Computer Processor Company}$ 提供一种特殊的处理器，其指令集仅包含两种操作：

- `A` ：将当前数值加上 $a$ 。
- `M` ：将当前数值乘以 $m$ 。

处理器接收一个整数输入，按顺序执行若干条 `A` 和 `M` 指令（称为一个程序），输出最终结果。  
例如，对于 $a=1, m=2$ ，程序 `AAAM` 作用于输入 $2$ 的过程为：  
$2 \xrightarrow{A} 3 \xrightarrow{A} 4 \xrightarrow{A} 5 \xrightarrow{M} 10$ ，输出 $10$ 。

给定处理器参数 $a, m$ 以及四个整数 $p, q, r, s$ ，满足 $1 \le p \le q$ 且 $1 \le r \le s$ 。  
输入保证为区间 $[p, q]$ 内的任意整数，要求程序对其中每一个输入 $x$ ，其输出 $y$ 都必须落在区间 $[r, s]$ 内。  
需要构造满足条件的最短程序（操作数最少）。若最短程序不唯一，则选取字典序最小的那个（将程序视为由 `A` 和 `M` 组成的字符串）。

若不需要任何操作即可满足条件，则输出 `empty` ；若不存在任何满足条件的程序，则输出 `impossible` 。

输出格式要求将程序压缩为若干段，每段形如 `nA` 或 `nM` ，表示连续 $n$ 次相同操作，段间用空格分隔。

## 输入格式

输入包含多组测试用例。每组测试用例一行，包含六个整数 $a, m, p, q, r, s$ ，范围均为 $[1, 10^9]$ ，且满足 $p \le q$ 、 $r \le s$ 。  
输入以一行六个 `0` 结束。

## 输出格式

对于每个测试用例，输出 `Case x:` 后接满足条件的最短程序，格式见样例。若无程序则输出 `impossible` ，若空程序可行则输出 `empty` 。

## 样例

输入

```text
1 2 2 3 10 20
1 3 2 3 22 33
3 2 2 3 4 5
5 3 2 3 2 3
0 0 0 0 0 0
```

输出

```text
Case 1: 1A 2M
Case 2: 1M 2A 1M
Case 3: impossible
Case 4: empty
```

## 题目分析

本题的核心是寻找一个最短的操作序列，使得从区间 $[p, q]$ 中任意输入出发，经过该序列变换后，都落入目标区间 $[r, s]$ 。

操作序列由 `A` 和 `M` 构成。设程序中共有 $k$ 次乘法操作，它们在序列中的位置将整个程序划分为 $k+1$ 段加法操作（每段可以是零次或多次加法）。记第 $i$ 段（$0 \le i \le k$）的加法次数为 $c_i$ ，则整个程序的形式为：

$$
A^{c_0} M A^{c_1} M \cdots M A^{c_k}
$$

其中 $M$ 出现 $k$ 次，$c_i \ge 0$ 均为整数。

对于任意输入 $x$ ，经过该程序后的输出可以解析表示为：

$$
y = \left( \cdots \left( (x + c_0 a) \cdot m + c_1 a \right) \cdot m + \cdots \right) \cdot m + c_k a
$$

展开后得：

$$
y = x \cdot m^k + a \cdot \sum_{i=0}^{k} c_i \cdot m^{k-i}
$$

记 $S = \sum_{i=0}^{k} c_i \cdot m^{k-i}$ ，则输出可统一写为：

$$
y = x \cdot m^k + a \cdot S
$$

由于 $m \ge 1$ ，当 $m=1$ 时乘法无效果，需单独处理；当 $m > 1$ 时，$m^k$ 随 $k$ 增长迅速。

**条件转化**  
要求对于任意 $x \in [p, q]$ ，都有 $r \le x \cdot m^k + a \cdot S \le s$ 。  
由于函数关于 $x$ 单调递增（因为 $m^k > 0$ ），因此只需检查区间端点即可：

- 最小值：$x = p$ 时，$y_{\min} = p \cdot m^k + a \cdot S$  
- 最大值：$x = q$ 时，$y_{\max} = q \cdot m^k + a \cdot S$

所以条件等价于：

$$
r \le p \cdot m^k + a \cdot S \quad \text{且} \quad q \cdot m^k + a \cdot S \le s
$$

即：

$$
\frac{r - p \cdot m^k}{a} \le S \le \frac{s - q \cdot m^k}{a}
$$

由于 $S$ 必须是整数，且 $a > 0$ ，因此我们得到 $S$ 的可行范围：

$$
L_k = \max\left(0, \left\lceil \frac{r - p \cdot m^k}{a} \right\rceil \right) \le S \le \left\lfloor \frac{s - q \cdot m^k}{a} \right\rfloor = U_k
$$

若 $L_k > U_k$ ，则该 $k$ 值无解。

**程序长度与字典序**  
程序总操作数为 $k + \sum_{i=0}^{k} c_i$ ，即 $k + S$ （因为 $\sum c_i = S$ 当 $m=1$ 时不成立，但 $m>1$ 时该项恒等；不过此处 $S$ 是加权和，并非简单加和）。注意：对于 $m>1$ ，$S = \sum c_i m^{k-i}$ ，而总加法次数为 $\sum c_i$ 。因此程序长度并不直接等于 $k+S$ 。我们必须从 $S$ 反推出各 $c_i$ ，使得总加法次数最小。

另一方面，总长度 $N = k + \sum c_i$ ，我们希望最小化 $N$ 。在 $N$ 相同的情况下，按字符串字典序比较（`A` 小于 `M` ）。

**关键观察**  
给定 $k$ 和 $S$ ，如何分配 $c_0, c_1, \dots, c_k$ 使得 $\sum c_i$ 最小？  
因为 $S = c_0 m^k + c_1 m^{k-1} + \dots + c_k$ ，这恰好是 $S$ 在 $m$ 进制下的表示（系数可超过 $m-1$ ，但为了最小化和，我们应该尽量将 $S$ 用高位表示，因为高位权重大，可以减少系数总和）。实际上，这是一个“最少硬币数”问题，其中硬币面值为 $m^k, m^{k-1}, \dots, 1$ ，且每种面额可使用任意次。为了最小化硬币总数，最优策略是贪心使用大面额，即 $c_i = \lfloor S / m^{k-i} \rfloor$ 并依此取余。这样得到的系数序列 $c_i$ 使得 $\sum c_i$ 最小。可以证明，任何其他分配产生的系数和不会更小。

因此，对于固定的 $k$ 和 $S$ ，最小加法次数为：

$$
\textit{sum}(S) = \sum_{i=0}^{k} \left\lfloor \frac{S}{m^{k-i}} \right\rfloor
$$

（这里 $c_k$ 为最后余数）。

而程序总长度为 $N = k + \textit{sum}(S)$ 。

**字典序处理**  
在总长度相同的情况下，我们需要比较不同程序（即不同 $k$ 和 $S$ 对应的序列）的字典序。字典序比较的是由 `A` 和 `M` 组成的字符串。由于 `A` 的 ASCII 码小于 `M` ，所以字典序更小的程序倾向于在尽量靠前的位置放 `A` 。这意味着对于同样长度的程序，我们应优先选择那些较早出现 `A` 的方案。

注意到程序形式为 $A^{c_0} M A^{c_1} M \dots M A^{c_k}$ ，其中 $M$ 的位置固定（第 $c_0$ 个字符后、第 $c_0+c_1+1$ 个字符后，等等）。因此字典序比较时，我们希望 $c_0$ 尽可能大（因为开头更多 `A` 会使得字符串更小），接着是 $c_1$ 尽可能大，以此类推。换言之，在固定总加法次数和 $k$ 的情况下，我们希望 $S$ 的 $m$ 进制表示中高位系数尽可能大（贪心分配已经使得系数序列是唯一的，即贪心得到的 $c_i$ 已经是字典序最大的？需要验证）。实际上，对于给定的 $k$ 和 $S$ ，贪心分配是唯一的（因为 $m$ 进制表示唯一）。所以不存在多个 $c$ 序列产生相同的 $S$ 和 $k$ 。但可能存在不同的 $k$ 和 $S$ 组合得到相同的总长度 $N$ ，我们需要在这些组合中按实际 A/M 字符串比较。

因此，穷举所有可能的 $k$ （有限，因为 $m^k$ 不能太大），对于每个 $k$ ，在区间 $[L_k, U_k]$ 内找出使得总长度 $N = k + \text{sum}(S)$ 最小的 $S$ 。若有多个 $S$ 使 $N$ 相同，则取对应的程序字典序最小的那个。最后在所有 $k$ 中取 $N$ 最小的，若有并列则比较字典序。

**特殊情况**  
- 若 $m=1$ ，乘法无效，程序只有加法。此时 $y = x + a \cdot c_0$ ，要求对所有 $x \in [p,q]$ ，$y \in [r,s]$ 。只需 $c_0$ 满足 $r - q \le a c_0 \le s - p$ （注意取整）。最短程序即为最少的加法次数 $c_0$ ，若 $c_0=0$ 则输出 `empty` 。
- 若程序长度为 $0$ （即 $k=0, S=0$），当 $[p,q] \subseteq [r,s]$ 时可行。

**算法步骤**  
1. 读入 $a, m, p, q, r, s$ ，特判空程序。
2. 若 $m=1$ ，直接计算最小非负加法次数 $c$ 是否可行，输出。
3. 枚举 $k = 0, 1, 2, \dots$ ，直到 $q \cdot m^k > s$ （因为此时即使 $S=0$ 也超出上限）或 $m^k$ 溢出。
4. 对每个 $k$ ，计算 $L_k, U_k$ ，若 $L_k > U_k$ 则跳过。
5. 在 $[L_k, U_k]$ 中寻找使 $N(k, S) = k + \textit{sum}(S)$ 最小的 $S$ ，其中 $\textit{sum}(S)$ 为 $S$ 在 $m$ 进制下（按权重 $m^k, m^{k-1}, \dots, 1$）的系数和。
6. 由于 $S$ 可能很大，不能遍历整个区间。我们需要分析 $\textit{sum}(S)$ 的单调性。实际上，$\textit{sum}(S)$ 是 $S$ 的（带权）数位和，它随着 $S$ 增大而增大（非严格）。所以 $N$ 在 $S$ 上也是单调递增的（因为 $k$ 固定）。因此最小 $S$ 即为 $L_k$ 。但是要注意，可能存在 $S$ 增大但 $\textit{sum}(S)$ 不变（如进位导致的特殊情况），但整体上 $N$ 不减。所以最优 $S$ 应在 $L_k$ 附近。事实上，由于进位可能使得系数和减小？比如 $m=10$ ，$S=19$ 的系数和为 $1+9=10$ ，而 $S=20$ 的系数和为 $2$ ，确实更小。因此 $N$ 并非单调递增，可能在进位处出现下降。因此我们需要检查 $L_k$ 以及 $L_k$ 进位后的若干值。具体地，我们只需考虑 $L_k$ 和将 $L_k$ 的某一位进位（即加上 $m^t$）后仍不超过 $U_k$ 的那些候选。因为任何最优 $S$ 要么是 $L_k$ ，要么是在某个位置上比 $L_k$ 更大的一个进位边界（即形如 $(\lfloor L_k / m^t \rfloor + 1) \cdot m^t$）。这些候选数量为 $O(k)$ 。
7. 对于每个候选 $S$ ，计算其系数 $c_i$ ，得到总长度 $N$ ，并保存最小的 $N$ 对应的 $c$ 和 $k$ 。若 $N$ 相同，则比较程序字符串的字典序。
8. 最后输出结果，若未找到则输出 `impossible` 。

## 解题思路

### 区间映射与整数 $S$

将程序表示为 $A^{c_0} M A^{c_1} M \cdots M A^{c_k}$ ，定义 $S = \sum_{i=0}^{k} c_i m^{k-i}$ 。则输入 $x$ 的输出为 $x \cdot m^k + a \cdot S$ 。由于 $x \in [p,q]$ 且函数单调，条件等价于：

$$
L_k \le S \le U_k
$$

其中

$$
L_k = \max\left(0, \left\lceil \frac{r - p m^k}{a} \right\rceil \right), \quad U_k = \left\lfloor \frac{s - q m^k}{a} \right\rfloor
$$

### 最小化程序长度

程序总长度 $N = k + \sum_{i=0}^{k} c_i$ 。给定 $k$ 和 $S$ ，为使 $\sum c_i$ 最小，应采用贪心分配：$c_i = \lfloor S / m^{k-i} \rfloor$ 取余。记该最小和为 $f_k(S)$ 。

由于 $k$ 固定，$f_k(S)$ 随 $S$ 的变化并非严格单调（进位时可能减小），但总体趋势上升。因此最优 $S$ 一定出现在区间的左端点 $L_k$ 或某个“进位点”上。具体地，对于任意 $S \in [L_k, U_k]$ ，若 $S$ 不是 $L_k$ 也不是某个形如 $(\lfloor L_k / m^t \rfloor + 1) \cdot m^t$ 的数，则令 $S' = S - \delta$ （其中 $\delta$ 是 $S$ 在最低非零位上的单位），$S'$ 仍然在区间内且 $f_k(S') \le f_k(S)$ （因为减少了低位，系数和不增）。因此最优解必在 $L_k$ 或进位点取得。所以只需枚举 $t=0,1,\dots,k$ 候选 $S_t = (\lfloor L_k / m^t \rfloor + 1) \cdot m^t$ ，若 $S_t \le U_k$ 则考虑。

### 字典序比较

对于两个候选程序（由 $k$ 和 $c$ 决定），比较它们对应的 A/M 字符串。由于 `A` < `M` ，我们希望在同样长度下，尽量使前面的字符为 `A` 。因此字典序比较可以按以下方式模拟：依次生成两个程序的字符序列，逐个比较，直到遇到不同字符或一方结束（长度相同，所以同时结束）。若都相同则任意。

### 特殊情况处理

- $m=1$ ：乘法无效，程序只有 `A` 操作。设加法次数为 $c$ ，则输出为 $x + a c$ ，要求 $r \le x + a c \le s$ 对所有 $x \in [p,q]$ 。等价于 $r - q \le a c \le s - p$ ，故 $c$ 必须满足 $\lceil (r - q)/a \rceil \le c \le \lfloor (s - p)/a \rfloor$ 且 $c \ge 0$ 。最小 $c$ 即为左边界（若左边界为负则取 0），若可行输出对应程序，否则 `impossible`。

- 空程序：当 $p \ge r$ 且 $q \le s$ 时，程序为空即可，输出 `empty`。

## 复杂度分析

枚举 $k$ 的最大值为 $\lfloor \log_m (s/q) \rfloor$ ，由于 $s \le 10^9$ ，$m \ge 2$ 时 $k \le 30$ 左右。对于每个 $k$ ，计算 $L_k, U_k$ 并枚举 $O(k)$ 个候选 $S$ ，每个候选计算系数和 $O(k)$ 。因此总时间复杂度为 $O(K^2)$ ，其中 $K \le 30$ ，非常快。空间复杂度 $O(K)$ 。

## 代码实现

```cpp
// To Add or to Multiply
// UVa ID: 1101
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 向上取整除法，b > 0
ll ceil_div(ll a, ll b) {
    if (a >= 0) return (a + b - 1) / b;
    return a / b;   // 负数时向零取整正好是上取整
}

// 向下取整除法，b > 0
ll floor_div(ll a, ll b) {
    if (a >= 0) return a / b;
    return - ((-a + b - 1) / b);
}

// 将 c[0..k] 对应的操作序列压缩成输出格式
string makeProgram(const vector<ll>& c, int k) {
    vector<pair<char, ll>> runs;
    auto addRun = [&](char ch, ll cnt) {
        if (cnt == 0) return;
        if (!runs.empty() && runs.back().first == ch)
            runs.back().second += cnt;
        else
            runs.push_back({ch, cnt});
    };
    for (int i = 0; i <= k; ++i) {
        if (c[i] > 0) addRun('A', c[i]);
        if (i < k) addRun('M', 1);
    }
    string res;
    for (size_t i = 0; i < runs.size(); ++i) {
        if (i) res += ' ';
        res += to_string(runs[i].second) + runs[i].first;
    }
    return res;
}

// 比较两个程序（只比较原始 A/M 字符串），返回 prog1 < prog2 是否成立
bool isLessRaw(const vector<ll>& c1, int k1, const vector<ll>& c2, int k2) {
    int i1 = 0, i2 = 0;
    ll a1 = 0, a2 = 0;   // 当前段已经输出的 A 个数
    while (true) {
        char ch1 = 0, ch2 = 0;
        // 取 prog1 的下一个字符
        if (i1 <= k1) {
            if (a1 < c1[i1]) {
                ch1 = 'A';
                ++a1;
            } else {
                if (i1 == k1) {
                    // 没有更多字符
                } else {
                    ch1 = 'M';
                    ++i1;
                    a1 = 0;
                }
            }
        }
        // 取 prog2 的下一个字符
        if (i2 <= k2) {
            if (a2 < c2[i2]) {
                ch2 = 'A';
                ++a2;
            } else {
                if (i2 == k2) {
                } else {
                    ch2 = 'M';
                    ++i2;
                    a2 = 0;
                }
            }
        }
        if (ch1 == 0 && ch2 == 0) return false;   // 完全相同
        if (ch1 == 0) return true;                // prog1 先结束（总长度应相同，不会发生）
        if (ch2 == 0) return false;
        if (ch1 != ch2) return ch1 < ch2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNo = 1;
    ll a, m, p, q, r, s;
    while (cin >> a >> m >> p >> q >> r >> s) {
        if (a == 0 && m == 0 && p == 0 && q == 0 && r == 0 && s == 0) break;
        cout << "Case " << caseNo++ << ": ";
        // 空程序可用
        if (p >= r && q <= s) {
            cout << "empty\n";
            continue;
        }
        // 处理 m == 1 的情况：乘法无效，只用加法
        if (m == 1) {
            // 只有 k = 0，程序全由 A 组成
            // 需要 L = ceil((r - p) / a)，U = floor((s - q) / a)
            ll L = ceil_div(r - p, a);
            ll U = floor_div(s - q, a);
            if (L < 0) L = 0;
            if (L <= U) {
                // 选最小的加法次数，即 L
                if (L == 0) cout << "empty\n";
                else cout << L << "A\n";
            } else {
                cout << "impossible\n";
            }
            continue;
        }
        // m > 1
        ll bestN = LLONG_MAX;
        vector<ll> bestC;
        int bestK = 0;
        ll power = 1;   // m^k
        for (int k = 0; ; ++k) {
            if (k > 0) {
                if (power > s / m) break;
                power *= m;
            }
            if (q * power > s) break;   // 即使 S=0 也超出上限
            ll pPow = p * power;
            ll qPow = q * power;
            ll L = ceil_div(r - pPow, a);
            ll U = floor_div(s - qPow, a);
            if (L < 0) L = 0;
            if (U < 0 || L > U) {
                // 继续尝试更大的 k
                continue;
            }
            // 预计算 m 的各次幂，用于后续分解 S
            vector<ll> powM(k + 1, 1);
            for (int i = 1; i <= k; ++i) powM[i] = powM[i-1] * m;
            // 生成候选 S：L 以及将 L 的某低位清零并进位
            vector<ll> candidates;
            candidates.push_back(L);
            for (int t = 0; t <= k; ++t) {
                ll step = powM[t];   // m^t
                ll cand = (L / step + 1) * step;
                if (cand >= L && cand <= U) candidates.push_back(cand);
            }
            // 对每个候选计算其数字和（c_i 之和）以及总长度 N
            ll bestSum = LLONG_MAX;
            ll bestS = -1;
            for (ll S : candidates) {
                vector<ll> c(k + 1);
                ll tmp = S;
                for (int i = 0; i <= k; ++i) {
                    c[i] = tmp / powM[k - i];
                    tmp %= powM[k - i];
                }
                ll sum = 0;
                for (ll v : c) sum += v;
                if (sum < bestSum || (sum == bestSum && S > bestS)) {
                    bestSum = sum;
                    bestS = S;
                }
            }
            if (bestS == -1) continue;
            // 根据 bestS 还原 c
            vector<ll> c(k + 1);
            ll tmp = bestS;
            for (int i = 0; i <= k; ++i) {
                c[i] = tmp / powM[k - i];
                tmp %= powM[k - i];
            }
            ll N = k + bestSum;
            if (N < bestN || (N == bestN && isLessRaw(c, k, bestC, bestK))) {
                bestN = N;
                bestC = c;
                bestK = k;
            }
        }
        if (bestN == LLONG_MAX) {
            cout << "impossible\n";
        } else {
            if (bestN == 0) cout << "empty\n";
            else cout << makeProgram(bestC, bestK) << '\n';
        }
    }
    return 0;
}
```

## 总结

本题的核心在于将程序结构参数化，利用整数 $S$ 将区间约束转化为简单的上下界，并通过贪心分配系数来最小化加法次数。枚举乘法次数 $k$ 的数量级很小（因为 $m^k$ 增长迅速），使得穷举可行。在长度相同的情况下，通过模拟字符串比较实现字典序最小。

关键技巧：
- 将程序抽象为 $A$ 和 $M$ 的序列，并利用乘法分配律合并为线性函数。
- 利用 $m$ 进制表示贪心求最小系数和。
- 候选 $S$ 的选取基于进位思想，避免遍历整个区间。
- 字典序比较直接按字符序列进行，简洁有效。

本题综合了数论、贪心和搜索，是一道典型的算法设计题。
