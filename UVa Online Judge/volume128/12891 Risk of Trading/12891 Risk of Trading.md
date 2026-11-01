# 题目描述

有 $N$ 座西部城市和 $N$ 座东部城市，每座西部城市各有一艘船。所有船需要分别前往不同的东部城市，因此需要建立一个一一对应的配对方案。已知从西部城市 $i$ 前往东部城市 $j$ 时船被海盗攻击的概率为 $p_{i,j}$。求一种配对方案，使至少有一艘船被攻击的概率最小，并输出该最小概率的最简分数。

# 输入格式

第一行包含一个整数 $T$，表示测试数据组数。

每组测试数据的第一行包含一个整数 $N$，表示东西部城市的数量。接下来有 $N$ 行，每行包含 $N$ 个分数，第 $i$ 行第 $j$ 个分数表示概率 $p_{i,j}$。每个概率均以 $a/b$ 的形式给出，满足 $0 \le a \le b \le 40$，且分数已经约分。

# 输出格式

对于每组测试数据，输出一行一个最简分数，表示在最优配对方案下至少有一艘船被攻击的最小概率。

# 样例输入

```text
2
2
1/2 1/2
1/4 3/4
2
1/8 7/8
0/1 1/15
```

# 样例输出

```text
5/8
11/60
```

# 题目分析

对于西部城市 $i$ 和东部城市 $j$ 的一条航线，设船被攻击的概率为 $p_{i,j}$，则船安全到达的概率为

$$
q_{i,j}=1-p_{i,j}
$$

若某个配对方案将西部城市 $i$ 与东部城市 $match(i)$ 配对，则所有船都安全到达的概率为

$$
P_{safe}=\prod_{i=1}^{N}q_{i,match(i)}
$$

至少有一艘船被攻击与所有船都安全到达是互补事件，因此风险为

$$
P_{risk}=1-P_{safe}
$$

由于 $1$ 是常数，最小化 $P_{risk}$ 等价于最大化 $P_{safe}$，所以原问题转化为在所有完美匹配中最大化安全概率乘积。

直接比较多个概率乘积会导致数值不断变小，且浮点数误差会影响匹配结果。对所有正的安全概率取对数后，根据对数乘法公式有

$$
\log P_{safe}=\sum_{i=1}^{N}\log q_{i,match(i)}
$$

对数函数具有严格单调性，所以最大化安全概率乘积等价于最大化安全概率对数之和。这样，每条西部城市到东部城市的边都具有一个权值，问题转化为带权二分图最大权完美匹配问题。

当 $q_{i,j}=0$ 时，表示对应航线上的船一定会被攻击，不能直接计算对数。代码将这类边的代价设为一个足够大的正数，并使用最小权匹配形式的匈牙利算法求解。这样可以保证算法优先选择安全概率较大的边；只有在必须使用安全概率为 $0$ 的边时，才会选择这类边。

匈牙利算法维护行顶标、列顶标、当前匹配关系以及增广路径。每次将一个新的西部城市加入匹配，通过不断寻找未匹配的东部城市扩展交替路，并调整顶标，使新的可行边出现，最终得到覆盖所有西部城市和东部城市的最优完美匹配。

得到匹配关系后，不能使用对数结果恢复最终分数，因为题目要求精确输出。代码保存每条航线的安全概率分子和分母，并使用 $\texttt{cpp\_int}$ 计算所有安全概率的精确乘积。设匹配后的安全概率为

$$
P_{safe}=\frac{safeNum}{safeDen}
$$

则风险为

$$
P_{risk}=1-\frac{safeNum}{safeDen}=\frac{safeDen-safeNum}{safeDen}
$$

最后使用最大公约数约分分子和分母，得到最简结果。

# 解题思路

设安全概率分数为 $q_{i,j}=\frac{b-a}{b}$，其中输入的攻击概率为 $\frac{a}{b}$。对每条边执行以下处理：

- 保存安全概率的分子 $b-a$ 和分母 $b$，用于最后的精确计算。
- 当 $a=b$ 时，安全概率为 $0$，将匹配代价设置为一个极大的值。
- 当 $a<b$ 时，将匹配代价设置为 $-\log\left(\frac{b-a}{b}\right)$。

对代价矩阵运行最小权完美匹配形式的 $\texttt{Hungarian}$ 算法。算法结束后，数组 $matchRow[i]$ 表示西部城市 $i$ 匹配到的东部城市。

按照匹配结果逐条相乘，得到

$$
 safeNum=\prod_{i=1}^{N}(b_i-a_i),\qquad safeDen=\prod_{i=1}^{N}b_i
$$

再计算风险分数

$$
 riskNum=safeDen-safeNum
$$

设 $g=\gcd(riskNum,safeDen)$，则最终输出

$$
\frac{riskNum/g}{safeDen/g}
$$

匈牙利算法的时间复杂度为 $O(N^3)$，代价矩阵和辅助数组的空间复杂度为 $O(N^2)$。精确乘积使用多精度整数，整数运算的实际代价还与最终分子、分母的位数有关；在题目给定范围和约束下可以满足要求。

# 代码实现

```cpp
#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

struct Fraction {
    long long num, den;
};

cpp_int getGcd(cpp_int a, cpp_int b) {
    while (b != 0) {
        cpp_int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase;
    cin >> testCase;
    while (testCase--) {
        int n;
        cin >> n;
        vector<vector<long double>> cost(n + 1, vector<long double>(n + 1));
        vector<vector<Fraction>> safe(n + 1, vector<Fraction>(n + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                long long a, b;
                char slash;
                cin >> a >> slash >> b;
                safe[i][j] = {b - a, b};
                if (a == b)
                    cost[i][j] = 1e100L;
                else
                    cost[i][j] = -logl((long double)(b - a) / b);
            }
        }
        vector<long double> rowPotential(n + 1), colPotential(n + 1);
        vector<int> matchCol(n + 1), pathCol(n + 1);
        for (int i = 1; i <= n; i++) {
            matchCol[0] = i;
            int currentCol = 0;
            vector<long double> minDistance(n + 1, 1e100L);
            vector<bool> used(n + 1, false);
            do {
                used[currentCol] = true;
                int currentRow = matchCol[currentCol], nextCol = 0;
                long double delta = 1e100L;
                for (int j = 1; j <= n; j++) {
                    if (used[j])
                        continue;
                    long double currentDistance = cost[currentRow][j] - rowPotential[currentRow] - colPotential[j];
                    if (currentDistance < minDistance[j]) {
                        minDistance[j] = currentDistance;
                        pathCol[j] = currentCol;
                    }
                    if (minDistance[j] < delta) {
                        delta = minDistance[j];
                        nextCol = j;
                    }
                }
                for (int j = 0; j <= n; j++) {
                    if (used[j]) {
                        rowPotential[matchCol[j]] += delta;
                        colPotential[j] -= delta;
                    } else
                        minDistance[j] -= delta;
                }
                currentCol = nextCol;
            } while (matchCol[currentCol] != 0);
            do {
                int previousCol = pathCol[currentCol];
                matchCol[currentCol] = matchCol[previousCol];
                currentCol = previousCol;
            } while (currentCol != 0);
        }
        vector<int> matchRow(n + 1);
        for (int j = 1; j <= n; j++)
            matchRow[matchCol[j]] = j;
        cpp_int safeNum = 1, safeDen = 1;
        for (int i = 1; i <= n; i++) {
            int j = matchRow[i];
            safeNum *= safe[i][j].num;
            safeDen *= safe[i][j].den;
        }
        cpp_int riskNum = safeDen - safeNum;
        cpp_int commonDivisor = getGcd(riskNum, safeDen);
        riskNum /= commonDivisor;
        safeDen /= commonDivisor;
        cout << riskNum << "/" << safeDen << '\n';
    }
    return 0;
}
```

# 总结

本题的关键是将“至少一艘船被攻击”的概率转化为其互补事件“所有船都安全”的概率。由于风险等于 $1$ 减去安全概率，因此只需最大化所有匹配边安全概率的乘积。

通过取对数，乘积最大化被转化为权值和最大化，再利用 $\texttt{Hungarian}$ 算法求出最优完美匹配。匹配过程使用长双精度对数值进行比较，最终结果则使用 $\texttt{cpp\_int}$ 精确计算并约分，从而同时保证匹配效率和输出结果的准确性。
