\## 题目描述



美国宪法规定，众议员名额应按各州人口比例分配，且每州至少一名。但由于人口并非除得尽，实际分配必须给每个州一个正整数个席位。本题要求对给定的若干州的人口数和目标总席位数，分别用四种经典分配方法（$\\texttt{Hamilton}$、$\\texttt{Jefferson}$、$\\texttt{Adams}$、$\\texttt{Webster}$）计算每个州的席位数，并指出对于每个州，哪种方法（如果有）给予该州的席位\*\*严格多于\*\*其他方法。



具体地，有 $n$ 个州（$n \\le 50$），每个州有唯一名称（恰好 $5$ 个字符）和正整数人口。对于每个目标总席位数 $H$（$H \\ge n$），输出每个州的比较结果。



\## 输入格式



输入包含多组数据。每组数据第一行为州数 $n$。若 $n = 0$ 则输入结束。



接下来 $n$ 行，每行一个州名（恰好 $5$ 个字符，从第 $1$ 列开始）和一个正整数人口（二者之间至少一个空格）。



之后是一行或多行整数，每行一个目标席位数 $H$。输入以单独的 $0$ 表示该组数据的 $H$ 列表结束。



保证 $H$ 不小于州数 $n$。



\## 输出格式



对于每组数据，先输出 `Data set k:`（$k$ 从 $1$ 开始）。



对于每个目标席位数 $H$，输出：

\- 一行 `For H representatives:`

\- 对每个州，按输入顺序输出一行，格式为：

&#x20; - 若所有方法得到的席位数相同，则输出 `州名 is favored by no method.`

&#x20; - 否则，输出 `州名 is favored by 方法1 and 方法2 ... .`，其中方法名按固定顺序 `Hamilton`、`Jefferson`、`Adams`、`Webster` 列出所有达到最大值的那些方法，方法名之间用 ` and ` 连接，末尾句点。



每个 $H$ 的输出后跟一个空行。



\## 样例



输入

```

5

Anxit 42

Bored 178

Confu 221

Dismy 117

Ecsta 72

30

5

0

0

```



输出

```

Data set 1:

For 30 representatives:

Anxit is favored by no method.

Bored is favored by Jefferson.

Confu is favored by Hamilton and Jefferson and Webster.

Dismy is favored by Hamilton and Adams and Webster.

Ecsta is favored by Adams.



For 5 representatives:

Anxit is favored by no method.

Bored is favored by no method.

Confu is favored by no method.

Dismy is favored by no method.

Ecsta is favored by no method.

```



\## 题目分析



本题的核心是\*\*议席分配\*\*问题。给定总人口 $\\textit{total}$ 和目标席位数 $H$，一个“公平”的理想分配是每个州获得 $\\textit{pop}\_i \\times H / \\textit{total}$ 个席位，但该值通常非整数。四种方法以不同方式将小数部分“舍入”或“调整”，使得总和恰好为 $H$。



\### 各方法原理



1\. \*\*$\\texttt{Hamilton}$（最大余数法）\*\*  

&#x20;  先取每个州配额的整数部分（保证至少 $1$ 席），剩余席位按小数部分从大到小分配。这是一种直观且符合直觉的方法，但可能产生“阿拉巴马悖论”（增加总席位反致某些州席位减少），但本题无需考虑。



2\. \*\*$\\texttt{Jefferson}$（向下取整除数法）\*\*  

&#x20;  寻找一个除数 $d$，使得对每个州，$\\lfloor \\textit{pop}\_i / d \\rfloor$ 的和等于 $H$。等价于“最高均值法”中分母为 $(\\text{当前席位数}+1)$ 的分配过程：初始每州 $1$ 席，反复将下一个席位给 $\\textit{pop}\_i / (\\text{当前席位数}+1)$ 最大的州。



3\. \*\*$\\texttt{Adams}$（向上取整除数法）\*\*  

&#x20;  寻找除数 $d$，使得 $\\lceil \\textit{pop}\_i / d \\rceil$ 的和等于 $H$。等价于分母为 $\\text{当前席位数}$ 的最高均值法。



4\. \*\*$\\texttt{Webster}$（四舍五入除数法）\*\*  

&#x20;  寻找除数 $d$，使得 $\\textit{pop}\_i / d$ 按四舍五入后求和等于 $H$。等价于分母为 $(2 \\times \\text{当前席位数} + 1)$ 的最高均值法（Sainte‑Laguë 方法）。



由于 $H$ 可能远大于 $n$，直接枚举除数不可行。但最高均值法用优先队列模拟分配过程，每次只增加一个席位，复杂度 $O((H-n) \\log n)$，在本题 $H$ 大小未明确但显然可接受（输入规模小）。



\### 比较规则



对于每个州，需要比较四种方法返回的席位数。如果所有方法的数值相同，则没有任何方法“给予更多”；否则，找出最大值，列出所有达到该最大值的方法名。注意必须严格大于其他方法，即如果最大值出现多次（并列第一），这些并列的方法都应列出，因为它们都比未达到最大值的其他方法多。



\## 解题思路



\### 总体框架



1\. 读入州数据。

2\. 对于每个目标席位数 $H$：

&#x20;  - 分别用四种方法计算各州席位。

&#x20;  - 对每个州比较四个值，按规则输出。



\### 各方法实现细节



\#### $\\texttt{Hamilton}$ 方法



\- 计算总人口 `total`（使用 `long long`）。

\- 对每个州 $i$，计算乘积 `prod = pop\[i] \* H`，整数部分 `q = prod / total`，余数 `rem = prod % total`。

\- 初始席位为 `max(1, q)`，并累加已分配数。

\- 将余数（即小数部分）按从大到小排序，只考虑“真实配额 ≥ 1”的州（即 `prod >= total`），依次给这些州加 $1$ 席，直到剩余席位分配完毕。



> 注意：当 `q = 0` 时，已保证至少 $1$ 席，但该州在余数分配时不参与（因为配额小于 $1$ 的州不应获得额外席位）。



\#### $\\texttt{Jefferson}$、$\\texttt{Adams}$、$\\texttt{Webster}$ 方法



三者统一用优先队列（最大堆）模拟最高均值法：



\- 初始每个州分配 $1$ 席（题目保证 $H \\ge n$）。

\- 定义“价值”函数：

&#x20; - $\\texttt{Jefferson}$：$\\textit{value} = \\textit{pop} / (\\text{当前席位} + 1)$

&#x20; - $\\texttt{Adams}$：$\\textit{value} = \\textit{pop} / \\text{当前席位}$

&#x20; - $\\texttt{Webster}$：$\\textit{value} = \\textit{pop} / (2 \\times \\text{当前席位} + 1)$

\- 重复 $H-n$ 次：弹出当前价值最大的州，为其增加 $1$ 席，重新计算该州新价值并压入堆。



由于每次弹出后该州的价值会变化，优先队列中可能残留旧值。在弹出时，检查该值是否仍等于该州当前的实际价值（用极小误差比较），若不是则丢弃并继续弹出。



\#### 比较与输出



对每个州，获得四个整数数组 `h\[i]`、`j\[i]`、`a\[i]`、`w\[i]`。计算最大值 `mx` 和最小值 `mn`。若 `mx == mn`，说明全部相等，输出 `no method`；否则，按顺序检查四个值，若等于 `mx` 则记录方法名。输出时用 ` and ` 连接。



\### 复杂度分析



\- 每次 $\\texttt{Hamilton}$ 计算 $O(n \\log n)$（排序余数）。

\- 每次最高均值法模拟 $O((H-n) \\log n)$，但 $H$ 在输入中未给出上界，但 $n \\le 50$，且席位数显然不会过大（样例中 $H$ 为 $30$ 和 $5$，实际数据应保证算法可行）。

\- 总时间复杂度：对每组数据每个 $H$，$O((H-n) \\log n + n \\log n)$，在合理范围内。

\- 空间复杂度 $O(n)$。



\## 代码实现



```cpp

// Constitutional Computing

// UVa ID: 364

// Verdict: Accepted

// Submission Date: 2026-06-24

// UVa Run Time: 0.000s

//

// 版权所有（C）2026，邱秋。metaphysis # yeah dot net



\#include <bits/stdc++.h>

using namespace std;



struct State {

&#x20;   string name;

&#x20;   long long pop;

};



// Hamilton 方法（最大余数法）

vector<int> hamilton(const vector<State>\& states, int H) {

&#x20;   int n = (int)states.size();

&#x20;   long long total = 0;

&#x20;   for (auto\& s : states) total += s.pop;

&#x20;   vector<int> reps(n);

&#x20;   int sum = 0;

&#x20;   vector<long long> rem(n);

&#x20;   for (int i = 0; i < n; ++i) {

&#x20;       long long prod = states\[i].pop \* H;

&#x20;       long long q = prod / total;          // 整数部分

&#x20;       rem\[i] = prod % total;               // 余数（小数部分的分母固定为 total）

&#x20;       reps\[i] = (int)q;

&#x20;       if (reps\[i] < 1) reps\[i] = 1;

&#x20;       sum += reps\[i];

&#x20;   }

&#x20;   int left = H - sum;

&#x20;   vector<int> idx;

&#x20;   for (int i = 0; i < n; ++i)

&#x20;       if (states\[i].pop \* H >= total) idx.push\_back(i);   // 真实配额 >= 1

&#x20;   sort(idx.begin(), idx.end(), \[\&](int a, int b) {

&#x20;       if (rem\[a] != rem\[b]) return rem\[a] > rem\[b];

&#x20;       return a < b;

&#x20;   });

&#x20;   for (int i = 0; i < left \&\& i < (int)idx.size(); ++i)

&#x20;       reps\[idx\[i]]++;

&#x20;   return reps;

}



// 通用除数法（优先队列模拟）

vector<int> divisorMethod(const vector<State>\& states, int H, function<long long(int)> denom) {

&#x20;   int n = (int)states.size();

&#x20;   vector<int> reps(n, 1);

&#x20;   if (H == n) return reps;

&#x20;   priority\_queue<pair<long double, int>> pq;

&#x20;   for (int i = 0; i < n; ++i) {

&#x20;       long double val = (long double)states\[i].pop / denom(reps\[i]);

&#x20;       pq.push({val, i});

&#x20;   }

&#x20;   int remain = H - n;

&#x20;   while (remain > 0) {

&#x20;       while (true) {

&#x20;           auto cur = pq.top(); pq.pop();

&#x20;           int i = cur.second;

&#x20;           long double curVal = (long double)states\[i].pop / denom(reps\[i]);

&#x20;           if (fabsl(cur.first - curVal) < 1e-12L) {   // 有效元素

&#x20;               reps\[i]++;

&#x20;               long double newVal = (long double)states\[i].pop / denom(reps\[i]);

&#x20;               pq.push({newVal, i});

&#x20;               remain--;

&#x20;               break;

&#x20;           }

&#x20;           // 否则丢弃过时的旧值

&#x20;       }

&#x20;   }

&#x20;   return reps;

}



// Jefferson：分母 = rep + 1

vector<int> jefferson(const vector<State>\& states, int H) {

&#x20;   return divisorMethod(states, H, \[](int rep) { return rep + 1; });

}



// Adams：分母 = rep

vector<int> adams(const vector<State>\& states, int H) {

&#x20;   return divisorMethod(states, H, \[](int rep) { return rep; });

}



// Webster：分母 = 2 \* rep + 1

vector<int> webster(const vector<State>\& states, int H) {

&#x20;   return divisorMethod(states, H, \[](int rep) { return 2LL \* rep + 1; });

}



int main() {

&#x20;   ios::sync\_with\_stdio(false);

&#x20;   cin.tie(nullptr);



&#x20;   int dataset = 1;

&#x20;   int n;

&#x20;   while (cin >> n \&\& n != 0) {

&#x20;       vector<State> states(n);

&#x20;       for (int i = 0; i < n; ++i)

&#x20;           cin >> states\[i].name >> states\[i].pop;



&#x20;       cout << "Data set " << dataset << ":\\n";

&#x20;       int H;

&#x20;       while (cin >> H \&\& H != 0) {

&#x20;           vector<int> h = hamilton(states, H);

&#x20;           vector<int> j = jefferson(states, H);

&#x20;           vector<int> a = adams(states, H);

&#x20;           vector<int> w = webster(states, H);



&#x20;           cout << "For " << H << " representatives:\\n";

&#x20;           for (int i = 0; i < n; ++i) {

&#x20;               int vals\[4] = {h\[i], j\[i], a\[i], w\[i]};

&#x20;               int mx = vals\[0], mn = vals\[0];

&#x20;               for (int k = 1; k < 4; ++k) {

&#x20;                   if (vals\[k] > mx) mx = vals\[k];

&#x20;                   if (vals\[k] < mn) mn = vals\[k];

&#x20;               }

&#x20;               vector<string> methods;

&#x20;               if (mx != mn) {   // 存在某个方法严格大于其他方法

&#x20;                   if (vals\[0] == mx) methods.push\_back("Hamilton");

&#x20;                   if (vals\[1] == mx) methods.push\_back("Jefferson");

&#x20;                   if (vals\[2] == mx) methods.push\_back("Adams");

&#x20;                   if (vals\[3] == mx) methods.push\_back("Webster");

&#x20;               }



&#x20;               cout << states\[i].name << " is favored by ";

&#x20;               if (methods.empty()) {

&#x20;                   cout << "no method.\\n";

&#x20;               } else {

&#x20;                   for (size\_t k = 0; k < methods.size(); ++k) {

&#x20;                       if (k > 0) cout << " and ";

&#x20;                       cout << methods\[k];

&#x20;                   }

&#x20;                   cout << ".\\n";

&#x20;               }

&#x20;           }

&#x20;           cout << '\\n';   // 每个代表数后空一行

&#x20;       }

&#x20;       dataset++;

&#x20;   }

&#x20;   return 0;

}

```



\## 总结



本题虽然背景复杂，但核心算法并不难，关键在于理解四种分配方法的等价最高均值实现，以及正确比较各方法结果。主要收获：



\- \*\*最高均值法的通用模拟\*\*：用优先队列按不同分母动态分配席位，避免了除法收敛问题。

\- \*\*浮点数比较\*\*：用 `fabsl` 和极小的容忍误差处理 `long double` 值的相等性，避免因精度问题导致死循环。

\- \*\*并列第一的处理\*\*：注意“更多”意味着严格大于，因此必须检查最大值与最小值是否相等，若相等则无任何方法占优。

\- \*\*输入输出细节\*\*：注意每组数据中 $H$ 以 $0$ 结束，且每个 $H$ 后要输出空行。



这种题目的实现技巧（优先队列 + 函数对象）也适用于其他类似的分配或调度问题。

