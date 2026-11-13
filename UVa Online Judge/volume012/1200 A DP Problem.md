
> **摘要**：本文讲解如何求解只含变量 $x$ 的一元一次方程。核心思路是将等号两侧分别解析为 $ax+b$ 形式，合并同类项后化为 $Ax=B$，再依据 $A$、$B$ 的取值判断唯一解、无解或无穷多解，并对唯一解向下取整输出。
# 题目描述

给定一个只含变量 $x$ 的一元一次方程，求方程的解。方程中不含括号，等号两侧均由至少一个项组成，各项之间通过加号或减号连接，表达式中不允许出现一元正号或一元负号。每个项具有以下形式之一：一个整数、一个整数后紧跟变量 $x$，或者单独一个 $x$。其中，单独的 $x$ 等价于 $1x$。

如果方程存在唯一解 $s$，输出 $\lfloor s \rfloor$，即不大于 $s$ 的最大整数；如果方程无解，输出 $\texttt{IMPOSSIBLE}$；如果方程有无穷多解，输出 $\texttt{IDENTITY}$。

# 输入格式

第一行包含一个整数 $t$，表示测试用例数量，满足 $1 \le t \le 10$。

接下来 $t$ 行，每行包含一个方程，长度不超过 $255$ 个字符。方程中不含空白字符，变量始终使用小写字母 $x$ 表示，各项中出现的整数均在 $0$ 到 $1000$ 之间，包含端点。

# 输出格式

对于每个测试用例，输出一行。

若方程存在唯一解 $s$，输出 $\lfloor s \rfloor$；若方程无解，输出 $\texttt{IMPOSSIBLE}$；若方程有无穷多解，输出 $\texttt{IDENTITY}$。输出字符串区分大小写。

# 样例输入

```text
2
2x-4+5x+300=98x
x+2=2+x
```

# 样例输出

```text
3
IDENTITY
```

# 题目分析

本题的核心是解析表达式并合并同类项。由于方程只包含变量 $x$，不存在括号，也不存在乘除运算，因此等号任意一侧都能整理成 $ax+b$ 的形式。其中，$a$ 是所有含变量项的系数之和，$b$ 是所有常数项之和，每一项的贡献由它前面的加号或减号决定。虽然输入表达式的项数和排列顺序不同，但只需记录变量系数与常数和这两个值，就能完整表示一侧表达式。

设左侧表达式整理后为 $a_Lx+b_L$，右侧表达式整理后为 $a_Rx+b_R$，则原方程为：
$$
a_Lx+b_L=a_Rx+b_R
$$
将变量项移到左侧、常数项移到右侧，并令 $A=a_L-a_R$、$B=b_R-b_L$，得到：
$$
Ax=B
$$
当 $A=0$ 且 $B=0$ 时，等式对任意 $x$ 都成立，因此有无穷多解；当 $A=0$ 且 $B\ne 0$ 时，等式不成立，因此无解；当 $A\ne 0$ 时，唯一解为 $x=\frac{B}{A}$。由此，整个问题分为表达式解析与化简后分类求解两个部分。

输出要求是向下取整，不能直接用整数除法代替。例如，当唯一解为 $-\frac{3}{2}$ 时，正确答案为 $-2$，而向零截断得到的是 $-1$。因此，代码先计算浮点数形式的商，再调用 $\texttt{floor}$ 函数完成向下取整。样例中的第一个方程整理后为 $7x+296=98x$，解为 $\frac{296}{91}$，向下取整得到 $3$；第二个方程两侧整理后完全相同，因此输出 $\texttt{IDENTITY}$。

# 解题思路

首先以等号为分界，将方程拆成左右两个表达式，并分别调用 $\texttt{parse}$ 函数解析。该函数返回一个整数对，分别记录当前表达式的变量系数和常数和。输入不含一元正负号，因此每个表达式的首项都没有显式符号。为了让首项与后续各项采用相同的处理方式，解析时先在表达式最前面补上加号，再在原表达式中的每个加号或减号前插入空格。这样，通过字符串输入流依次读取，就能得到带有明确正负号的各个项。

对于读取到的每一项，先根据首字符确定符号，再移除这个符号。如果剩余部分以 $x$ 结尾，则该项是变量项，继续移除末尾的 $x$，将剩下的数字解析为系数；若移除 $x$ 后字符串为空，说明原项是单独的 $x$，系数为 $1$。如果该项不以 $x$ 结尾，则直接将其解析为常数。数字采用逐位累积的方式解析，每读入一个数位 $d$，就将当前数值 $n$ 更新为 $10n+d$。最后，将解析出的数值乘以该项符号，加入对应的变量系数或常数和。

左右两侧解析完成后，计算 $A=a_L-a_R$ 与 $B=b_R-b_L$。若 $A=0$，根据 $B$ 是否为 $0$ 分别输出 $\texttt{IDENTITY}$ 或 $\texttt{IMPOSSIBLE}$；若 $A\ne 0$，输出 $\left\lfloor\frac{B}{A}\right\rfloor$。这一过程的正确性来自等价变形：解析时，每一项都按照其符号准确计入所属的同类项，因此整理后的表达式与原表达式恒等；移项后得到的 $Ax=B$ 与原方程具有相同的解集；最后对 $A$ 与 $B$ 的分类覆盖了所有情况，因此输出结果正确。

设单个方程的长度为 $L$。题目保证输入不含空白字符，因此代码中的空白检查只进行扫描，不触发字符删除；拆分表达式、构造分项字符串和解析所有项均只需线性处理字符，所以单个测试用例的时间复杂度为 $O(L)$。解析过程中保存原字符串、辅助字符串及字符串输入流等数据，空间复杂度为 $O(L)$。对于 $t$ 个测试用例，设第 $i$ 个方程长度为 $L_i$，总时间复杂度为 $O\left(\sum_{i=1}^{t}L_i\right)$。

# 代码实现

```cpp
// A DP Problem
// UVa ID: 1200
// Verdict: Accepted
// Submission Date: 2018-03-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

pair<int, int> parse(string expression)
{
    string next = "+";
    for (auto c : expression)
    {
        if (c == '+' || c == '-')
            next += ' ';
        next += c;
    }
        
    int x = 0, coefficient = 0;
    istringstream iss(next);
    string block;
    while (iss >> block)
    {
        int sign = 1;
        if (block.front() == '-') sign = -1;
        block.erase(block.begin());
        if (block.back() == 'x')
        {
            block.pop_back();
            int n = 0;
            if (block.length() == 0) n = 1;
            else
            {
                for (auto c : block)
                    n = n * 10 + c - '0';
            }
            
            x += n * sign;
        }
        else
        {
            int n = 0;
            for (auto c : block)
                n = n * 10 + c - '0';
            coefficient += n * sign;
        }
    }
    
    return make_pair(x, coefficient);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;
    
    cin >> cases; cin.ignore(1024, '\n');
    for (int c = 1; c <= cases; c++)
    {
        getline(cin, line);
        for (int i = line.length() - 1; i >= 0; i--)
            if (isblank(line[i]))
                line.erase(line.begin() + i);

        int equal = line.find('=');
        pair<int, int> leftPart = parse(line.substr(0, equal));
        pair<int, int> rightPart = parse(line.substr(equal + 1));
        
        int x = leftPart.first - rightPart.first;
        int coefficient = rightPart.second - leftPart.second;
        
        if (x == 0)
        {
            if (coefficient == 0) cout << "IDENTITY\n";
            else cout << "IMPOSSIBLE\n";   
        }
        else
        {
            cout << (int)(floor(1.0 * coefficient / x)) << '\n';
        }
    }

    return 0;
}
```

# 总结

本题通过合并同类项，将字符串形式的方程转化为 $Ax=B$，再根据变量系数与常数值判断唯一解、无解和无穷多解。实现中的关键技巧是为首项补上加号，统一各项的符号处理；将单独的 $x$ 按系数 $1$ 处理；在输出唯一解时使用向下取整，正确处理负数结果。掌握“解析各项、汇总系数、等价化简、分类求解”的处理流程，就能在线性时间内完成此类一元一次方程的求解。
