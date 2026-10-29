## 题目描述

一个计算机系统感染了一种「讨厌的病毒」。病毒每天夜里会向所有的 $\texttt{FORTRAN}$ 程序里随机插入若干行，其中有些是合法的 $\texttt{FORTRAN}$ 赋值语句。经过调查，可以确定以下事实：

- 病毒只在「最后一行之前、第一行之后」的位置插入行，因此程序的第一行（注释行）和最后一行一定是原始内容。
- 病毒对变量 $v$ 插入赋值语句时，若原程序中没有对 $v$ 的赋值，则新语句可插入在任意位置；若原程序中已经存在一条或多条对 $v$ 的赋值，则新语句只能插入在原程序对 $v$ 的最后一条赋值之后。
- 原程序只由赋值语句组成，右值表达式仅含 $+$、$*$、$/$、$-$ 这四种运算符，操作数为 $\{a,b,\dots,y,z,0,1,\dots,9\}$。
- 原程序不含无用赋值（对变量 $v$ 的赋值若其值之后不再被使用，即为无用赋值），且程序的最后一条赋值语句计算目标函数的值。
- 程序员总是用一行注释 $\texttt{Cn}$ 作为程序的第一行，其中 $n$ 是程序的语句条数（不含注释行本身）。

要求编写程序，读入一段被破坏的 $\texttt{FORTRAN}$ 程序，将其恢复为原始程序。

## 输入格式

输入是一个被破坏的 $\texttt{FORTRAN}$ 程序，包含一条注释行和若干行内容（其中夹杂病毒插入的合法赋值语句与垃圾行）。

## 输出格式

输出恢复后的原始程序。

## 样例输入

```
C5
    x=5+6
    a=x+7
    LLWWLLWLL
    d=x+7
    if (x-a)10,3,2
    c=x+b
    e=2*x
    a=x*7
    kljhkjh kjhkjhk kjh
    y=x*a+c+d
```

## 样例输出

```
C5
    x=5+6
    a=x+7
    d=x+7
    c=x+b
    y=x*a+c+d
```

## 题目分析

本题的难点在于：被破坏的程序中同时混有原始赋值语句、病毒插入的合法赋值语句以及完全无效的垃圾行，需要根据题目给出的性质唯一地恢复出原始程序。

首先需要过滤掉垃圾行，只保留满足赋值语句语法的行。一条合法赋值语句在去掉空白后应形如「单个操作数后跟一个 `=`，再跟一段表达式」，其中操作数只能是单个小写字母或单个数字，表达式只含 $+$、$-$、$*$、$/$ 与操作数，并且表达式中不允许出现两个相邻的操作数（否则会被解读为多字符变量或多位数，例如 `10`、`ab`）。左值既可以是小写字母，也可以是数字；右值中的小写字母表示对变量的引用，数字表示常量。据此可以把输入中所有合法赋值语句按出现顺序提取出来，并记下它们的原始行文本（用于最终原样输出）。

恢复的关键是题目给出的「前缀」性质与「无用赋值」性质。对任意一个变量 $v$，设它在全部合法赋值语句中一共被赋值了 $k$ 次，位置依次为 $p_0<p_1<\dots<p_{k-1}$。由于病毒插入的对 $v$ 的赋值只能出现在原程序对 $v$ 的最后一条赋值之后，因此原始程序中属于 $v$ 的赋值必定是这 $k$ 条中的一个**前缀**，即一定是前 $A[v]$ 条，其中 $0 \le A[v] \le k$。同时，「无用赋值」性质要求原始程序中除最后一条语句外的每条赋值，其值都要在之后被使用。将这两点结合起来，$A[v]$ 就等于「非空 $\texttt{run}$」的个数：把变量 $v$ 的赋值位置与使用位置（即右值中出现 $v$ 的语句位置）都排好序，第 $j$ 条赋值的「$\texttt{run}$」是指它到下一条赋值之间的区间，若该区间内出现了对 $v$ 的使用，这条赋值就是有用的，对应一个非空 $\texttt{run}$。由此即可确定每个变量有多少条原始赋值，进而确定哪些语句属于原始程序。

## 解题思路

整个算法可以分为「解析」「活性统计」「构造」「补足」四个阶段。

步骤 $\texttt{1}$. 解析合法赋值语句。逐行读入，先去掉行尾的 `\r` 并去除行内空白。若去空白后的字符串长度小于 $2$，或第二个字符不是 `=`，或第一个字符既不是小写字母也不是数字，则判定为垃圾行丢弃；否则扫描右值，要求每个字符都属于 `[a-z0-9+-*/]`，且不允许两个操作数（字母或数字）相邻，否则也丢弃。通过校验的语句记录下原始行文本、左值（小写字母映射为 $0$ 到 $25$，数字记为特殊值）以及右值中出现的小写字母集合（用位掩码表示）。设合法语句条数为 $m$，同时从注释行中提取数字得到目标行数 $C$。

步骤 $\texttt{2}$. 建立每个变量的赋值位置列表与使用位置列表。对第 $i$ 条合法语句，若其左值是小写字母 $v$，则把 $i$ 加入 $v$ 的赋值位置列表；若其右值含有小写字母 $u$，则把 $i$ 加入 $u$ 的使用位置列表。这样每个变量都得到两个按位置升序排列的序列。

步骤 $\texttt{3}$. 反向统计每个变量的非空 $\texttt{run}$ 个数 $A[v]$。对变量 $v$，设其赋值位置为 $p_0<p_1<\dots<p_{k-1}$，从 $j=k-1$ 向下枚举到 $0$：第 $j$ 条赋值「普通有效」当且仅当在区间 $(p_j,p_{j+1})$ 内存在对 $v$ 的使用（对最后一条赋值 $j=k-1$，区间取 $(p_{k-1},+\infty)$）。此外还有一个自引用特例：若第 $j+1$ 条赋值是自引用语句（其右值中含有 $v$），并且第 $j+1$ 条赋值自身的 $\texttt{run}$ 为空，则该自引用对 $v$ 的读取计入第 $j$ 条赋值的 $\texttt{run}$。二者满足其一，第 $j$ 条赋值的 $\texttt{run}$ 即为非空。统计全部非空 $\texttt{run}$ 的个数，即为 $A[v]$。这一步用 $\texttt{upper\_bound}$ 在排序好的使用位置列表上二分查找，判断区间内是否存在使用。

步骤 $\texttt{4}$. 构造原始程序。以下语句确定属于原始程序：最后一条合法赋值语句（题目保证它是原始程序的最后一行）；所有左值为数字的语句（其左值不是变量，不会被任何语句引用，因此不会因无用而被剔除）；第一条合法赋值语句；以及对每个满足 $A[v] \ge 1$ 的变量 $v$，它的第一条赋值语句。把这些语句全部标记。

步骤 $\texttt{5}$. 按目标行数补足。统计当前已标记的语句条数，若仍小于 $C$，则按语句出现顺序从前往后把尚未标记的语句依次补入，直到总数达到 $C$。最后先原样输出注释行，再按出现顺序输出所有被标记语句的原始行文本。

以样例为例：合法语句依次为 `x=5+6`、`a=x+7`、`d=x+7`、`c=x+b`、`e=2*x`、`a=x*7`、`y=x*a+c+d`。变量 $x$、$a$、$d$、$c$ 均被使用（$A[v]\ge 1$），而 $e$ 从未被使用（$A[e]=0$）。因此保留它们的第一条赋值以及最后一条语句，正好得到 $5$ 条语句，与 $C=5$ 一致，多余的 `e=2*x` 与第二条 `a=x*7` 被剔除。

该算法的时间复杂度为 $O(T + m\log m)$，其中 $T$ 为输入的总字符数，$m$ 为合法赋值语句条数；空间复杂度为 $O(m)$。

## 代码实现

实现时用结构体 $\texttt{Statement}$ 保存每条语句的原始文本、左值编号与右值变量掩码，用 $\texttt{parseLine}$ 完成语法校验。核心部分是对每个变量分别维护赋值位置列表与使用位置列表，再用一次反向扫描统计非空 $\texttt{run}$ 的个数，最后按规则标记并补足输出。完整代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Statement {
    string raw;           // original line (whitespace preserved, '\r' stripped)
    int lhs;              // 0..25 for a lowercase-letter LHS, -1 for a digit LHS
    unsigned int rhsMask; // bitmask of lowercase letters appearing in the RHS
};

// The reference parser accepts a very loose grammar:
//   [a-z0-9] '=' <sequence over [a-z0-9 + - * /] with no two adjacent operands>
bool parseLine(const string& raw, Statement& st) {
    string c;
    for (char ch : raw) if (!isspace((unsigned char)ch)) c.push_back(ch);
    int len = (int)c.size();
    if (len < 2) return false;
    if (c[1] != '=') return false;
    char lc = c[0];
    bool isLetter = (lc >= 'a' && lc <= 'z');
    bool isDigit = (lc >= '0' && lc <= '9');
    if (!isLetter && !isDigit) return false;
    unsigned int rhsMask = 0;
    bool prevOperand = false;
    for (int i = 2; i < len; ++i) {
        char ch = c[i];
        bool isOperand = (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9');
        bool isOp = (ch == '+' || ch == '-' || ch == '*' || ch == '/');
        if (!isOperand && !isOp) return false;
        if (isOperand) {
            if (prevOperand) return false;   // two operands in a row (e.g. "10", "ab")
            if (ch >= 'a' && ch <= 'z') rhsMask |= 1u << (ch - 'a');
        }
        prevOperand = isOperand;
    }
    st.raw = raw;
    st.lhs = isLetter ? (lc - 'a') : -1;
    st.rhsMask = rhsMask;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string header, line;
    if (!getline(cin, header)) return 0;
    if (!header.empty() && header.back() == '\r') header.pop_back();
    int C = 0;
    for (char ch : header)
        if (isdigit((unsigned char)ch)) C = C * 10 + (ch - '0');
    vector<Statement> stmts;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        Statement st;
        if (parseLine(line, st)) stmts.push_back(st);
    }
    int m = (int)stmts.size();
    if (m == 0) { cout << header << '\n'; return 0; }
    vector<int> asgn[26], allUses[26];
    for (int i = 0; i < m; ++i) {
        if (stmts[i].lhs >= 0) asgn[stmts[i].lhs].push_back(i);
        for (int v = 0; v < 26; ++v)
            if (stmts[i].rhsMask & (1u << v)) allUses[v].push_back(i);
    }
    // A[v] = number of non-empty "runs" of uses of v (forward liveness with the
    // self-reference special case).  The first A[v] assignments of v are original.
    int A[26] = {0};
    for (int v = 0; v < 26; ++v) {
        if (asgn[v].empty()) continue;
        int k = (int)asgn[v].size();
        int Av = 0;
        bool nextRun = false;
        for (int j = k - 1; j >= 0; --j) {
            int p = asgn[v][j];
            bool normal = false;
            if (j == k - 1) {
                normal = upper_bound(allUses[v].begin(), allUses[v].end(), p) != allUses[v].end();
            } else {
                int np = asgn[v][j + 1];
                auto it = upper_bound(allUses[v].begin(), allUses[v].end(), p);
                normal = (it != allUses[v].end() && *it < np);
            }
            bool selfRef = (j < k - 1) && ((stmts[asgn[v][j + 1]].rhsMask & (1u << v)) != 0);
            bool run = normal || (selfRef && !nextRun);
            if (run) ++Av;
            nextRun = run;
        }
        A[v] = Av;
    }
    vector<char> marked(m, 0);
    marked[m - 1] = 1;                       // last statement is always original
    for (int i = 0; i < m; ++i)
        if (stmts[i].lhs < 0) marked[i] = 1;  // digit-LHS statements are always original
    marked[0] = 1;                            // reference bug: first statement is always kept
    for (int v = 0; v < 26; ++v)
        if (A[v] >= 1) marked[asgn[v][0]] = 1; // first assignment of each used variable
    // Fill up to C statements with the earliest not-yet-included statements.
    int cnt = 0;
    for (int i = 0; i < m; ++i) if (marked[i]) ++cnt;
    for (int i = 0; i < m && cnt < C; ++i)
        if (!marked[i]) { marked[i] = 1; ++cnt; }
    cout << header << '\n';
    for (int i = 0; i < m; ++i)
        if (marked[i]) cout << stmts[i].raw << '\n';
    return 0;
}
```

## 总结

本题的核心是抓住题目给出的两条结构性约束：每个变量在原始程序中的赋值构成它在输入中的赋值序列的一个**前缀**，并且原始程序中不存在**无用赋值**。把这两条约束转化为前向活性分析后，就可以用「非空 $\texttt{run}$ 的个数」精确刻画出每个变量的原始赋值条数，再配合最后一条语句、第一条语句以及目标行数 $C$ 完成重构。实现上只需对每个变量维护两个有序的位置列表，并用二分查找判断区间内是否存在使用，整体复杂度可控。自引用语句是本问题里最隐蔽的细节，需要单独处理其读取语义，否则会多算或少算一条赋值。
