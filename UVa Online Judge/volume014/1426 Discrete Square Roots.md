
> **摘要**：本题给定非负整数 $x$、模数 $N$ 以及 $x$ 模 $N$ 的一个已知离散平方根 $r$，要求求出 $x$ 模 $N$ 的全部离散平方根并按升序输出。核心思路是利用 $s^2 \equiv r^2 \pmod N$ 将问题转化为 $(s-r)(s+r)$ 被 $N$ 整除，进而枚举 $N$ 的所有因子 $d$，对每个因子构造并求解一次同余方程组，用扩展欧几里得求逆元得到特解，再按周期 $N/\gcd(d, N/d)$ 展开全部解，最后排序去重输出。算法时间复杂度为 $O(\sqrt N + \tau(N)\log N)$，在 $N < 10^9$ 范围内高效可行。

## 题目描述

一个非负整数 $x$ 的离散平方根（模 $N$）是指一个非负整数 $r$，满足  
$0 \le r < N$ 且 $r^2 \equiv x \pmod N$，其中 $N$ 是一个给定的正整数。

已知任意正实数恰有两个平方根，但非负整数的离散平方根个数可能多于两个。例如，当 $N = 12$ 时，$1$ 的离散平方根为 $1,5,7,11$，共四个。

本题给定三个整数 $x, N, r$，其中 $r$ 是 $x$ 模 $N$ 的一个已知离散平方根（即 $r^2 \equiv x \pmod N$），要求找出 $x$ 的所有离散平方根，并按升序输出。

---

## 输入格式

输入包含多组测试用例。  
每组测试用例占一行，包含三个整数 $x, N, r$，满足：

- $1 \le x < N$
- $2 \le N < 10^9$
- $1 \le r < N$

且保证 $r$ 是 $x$ 的一个离散平方根。  
输入以一行 `0 0 0` 结束。

---

## 输出格式

对于每组测试用例，输出一行，格式为：

`Case 编号: 平方根列表`

其中编号从 $\texttt{1}$ 开始，平方根列表按递增顺序排列，相邻数字之间用一个空格分隔。

---

## 样例

**输入**
```
1 12 1
4 15 2
0 0 0
```

**输出**
```
Case 1:1 5 7 11
Case 2:2 7 8 13
```

---

## 题目分析

已知一个解 $r$，要求所有 $s \in [0, N-1]$ 使得 $s^2 \equiv x \pmod N$。由于 $r^2 \equiv x \pmod N$，等价条件为 $s^2 \equiv r^2 \pmod N$，即

$$
N \mid (s^2 - r^2) = (s - r)(s + r).
$$

令 $d$ 为 $N$ 的任意因子，则上式成立的一个充分必要条件（在整数分解意义上）是：存在某个因子 $d$ 使得

$$
d \mid (s - r) \quad \text{且} \quad \frac{N}{d} \mid (s + r).
$$

这是因为对于任意满足 $N \mid (s-r)(s+r)$ 的 $s$，取 $d = \gcd(N, s-r)$，则 $d \mid (s-r)$ 且 $N/d \mid (s+r)$（因为 $N/\gcd(N, s-r)$ 必然整除 $(s+r)$，可由 $N$ 整除乘积及最大公约数性质推出）。反之，若存在这样的 $d$，则显然 $N \mid (s-r)(s+r)$。

因此，枚举 $N$ 的所有因子 $d$，并对每个 $d$ 求解同余方程组：

$$
\begin{cases}
s \equiv r \pmod d,\\
s \equiv -r \pmod {N/d}.
\end{cases}
$$

该方程组有解当且仅当两个同余式在模 $\gcd(d, N/d)$ 下相容，即

$$
r \equiv -r \pmod{\gcd(d, N/d)} \quad \Longleftrightarrow \quad 2r \equiv 0 \pmod{\gcd(d, N/d)}.
$$

若该条件成立，则方程组有解，且解模 $\operatorname{lcm}(d, N/d)$ 唯一。由于 $\operatorname{lcm}(d, N/d) = \dfrac{d \cdot (N/d)}{\gcd(d, N/d)} = \dfrac{N}{g}$，其中 $g = \gcd(d, N/d)$，因此所有解可表示为

$$
s = s_0 + k \cdot \frac{N}{g}, \quad k = 0, 1, \dots, g-1,
$$

其中 $s_0$ 是任意一个特解（可取模 $N/g$ 后的最小非负剩余）。枚举所有因子 $d$ 并收集所有符合条件的 $s$，最后排序去重即得到答案。

---

## 解题思路

**步骤 $\texttt{1}$.** 对 $N$ 进行质因数分解，生成 $N$ 的所有正因子，存入数组 $\textit{divs}$。

**步骤 $\texttt{2}$.** 对于每个因子 $d$：

- 计算 $m = N / d$ 和 $g = \gcd(d, m)$。
- 若 $(2 \cdot r) \bmod g \ne 0$，则跳过该 $d$。
- 否则，求解同余方程组。将两个同余式合并为一个关于 $t$ 的线性同余方程：  
  令 $s = r + d \cdot t$（由 $s \equiv r \pmod d$ 得来），代入 $s \equiv -r \pmod m$ 得  
  $$r + d \cdot t \equiv -r \pmod m \quad \Longrightarrow \quad d \cdot t \equiv -2r \pmod m.$$  
  设 $g = \gcd(d, m)$，则方程有解条件已满足。约去 $g$，得  
  $$(d/g) \cdot t \equiv (-2r/g) \pmod {m/g}.$$  
  令 $a = d/g$，$b = m/g$，$c = (-2r/g) \bmod b$，则需解 $a \cdot t \equiv c \pmod b$。由于 $\gcd(a, b) = 1$，可通过求 $a$ 模 $b$ 的逆元 $a^{-1}$ 得到 $t_0 = c \cdot a^{-1} \bmod b$。  
- 特解 $s_0 = (r + d \cdot t_0) \bmod L$，其中 $L = N / g$（即 $\operatorname{lcm}(d, m)$）。
- 然后枚举 $k = 0, 1, \dots, g-1$，得到所有解 $s = s_0 + k \cdot L$，将其加入答案集合。

**步骤 $\texttt{3}$.** 对答案集合排序并去重，按格式输出。

该算法枚举了 $N$ 的所有因子，因子个数在 $N < 10^9$ 时最多约为 $1344$ 个（实际远小于此），因此枚举量完全可行。每组因子需要一次扩展欧几里得求逆元，整体复杂度为 $O(\tau(N) \log N)$，其中 $\tau(N)$ 为因子个数。

---

## 复杂度分析

- **时间复杂度**：质因数分解 $O(\sqrt N)$，因子个数为 $\tau(N)$。对每个因子进行扩展欧几里得运算，单次 $O(\log N)$，故总时间复杂度为 $O(\sqrt N + \tau(N) \log N)$，在给定 $N < 10^9$ 下非常高效。
- **空间复杂度**：存储因子和答案均为 $O(\tau(N))$，可视为常数级别。

---

## 代码实现

```cpp
// Discrete Square Roots
// UVa ID: 1426
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll modInverse(ll a, ll m) {
    if (m == 1) return 0;
    ll x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}

vector<pair<ll, int>> factorize(ll n) {
    vector<pair<ll, int>> fac;
    for (ll p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            int e = 0;
            while (n % p == 0) { n /= p; ++e; }
            fac.push_back({p, e});
        }
    }
    if (n > 1) fac.push_back({n, 1});
    return fac;
}

void genDivs(int idx, ll cur, const vector<pair<ll, int>> &fac, vector<ll> &divs) {
    if (idx == (int)fac.size()) { divs.push_back(cur); return; }
    ll p = fac[idx].first;
    int e = fac[idx].second;
    ll mul = 1;
    for (int i = 0; i <= e; ++i) {
        genDivs(idx + 1, cur * mul, fac, divs);
        mul *= p;
    }
}

ll gcd(ll a, ll b) {
    while (b) { ll t = a % b; a = b; b = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll x, N, r;
    int caseNo = 1;
    while (cin >> x >> N >> r) {
        if (x == 0 && N == 0 && r == 0) break;

        vector<pair<ll, int>> fac = factorize(N);
        vector<ll> divs;
        genDivs(0, 1, fac, divs);

        vector<ll> ans;
        for (ll d : divs) {
            ll m = N / d;
            ll g = gcd(d, m);
            if ((2 * r) % g != 0) continue;

            ll c = ((-2 * r) % m + m) % m;
            ll a = d / g;
            ll b = m / g;
            ll c2 = c / g;

            ll inv = modInverse(a, b);
            ll t0 = (c2 * inv) % b;
            ll L = N / g;
            ll s0 = (r + d * t0) % L;

            for (ll k = 0; k < g; ++k) {
                ll s = s0 + k * L;
                ans.push_back(s);
            }
        }

        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        cout << "Case " << caseNo++ << ":";
        for (ll v : ans) cout << " " << v;
        cout << "\n";
    }
    return 0;
}
```

---

## 总结

本题的核心是将平方同余问题转化为线性同余方程组的求解，借助已知解 $r$ 将 $s^2 \equiv r^2$ 分解为 $(s-r)(s+r)$ 被 $N$ 整除，然后通过枚举 $N$ 的因子 $d$ 建立 $s$ 的两个同余条件。该方法避免了暴力枚举 $[0, N-1]$，利用因子个数较少的性质实现了高效求解。

关键技巧在于：

- 利用已知解构造同余方程组，而不是直接开方。
- 通过因子分解将判定条件分解为若干子问题，每个子问题都是标准的一次同余方程，可用扩展欧几里得求解。
- 注意处理解的周期性和去重，确保最终输出有序且不重复。

该解法对 $N$ 的范围（$< 10^9$）具有良好的适应性，是解决离散平方根问题的通用方法。
