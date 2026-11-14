[UVa 392 Polynomial Showdown](https://blog.csdn.net/metaphysis/article/details/161705442)

## 题目描述

给定从 $8$ 次项到常数项的多项式系数，你需要将多项式格式化为可读形式，移除不必要的字符。例如，给定系数 `0, 0, 0, 1, 22, -333, 0, 1, -1`，应输出 `x^5 + 22x^4 - 333x^3 + x - 1`。

### 格式化规则

1. 项必须按次数降序排列
2. 指数应放在 `^` 后面
3. 常数项只显示常数
4. 只显示非零系数的项，除非所有系数均为零，此时显示常数项
5. 唯一空格是二元 `+` 和 `-` 运算符两侧各一个空格
6. 首项若为正，不显示符号；若为负，显示负号（如 `-7x^2 + 30x + 66`）
7. 负项应显示为减号后跟正数（首项负除外）
8. 系数 $1$ 和 $-1$ 只在常数项显示数字，其他项只显示符号（如 `-x^3 + x^2 + 3x - 1`）

### 输入格式

输入一行或多行，每行包含 $9$ 个整数（系数，从 $8$ 次到常数项），用空格分隔。系数绝对值小于 $1000$。

### 输出格式

每行输出一个格式化后的多项式。

### 样例输入

```
0 0 0 1 22 -333 0 1 -1
0 0 0 0 0 -55 5 0 0
```

### 样例输出

```
x^5 + 22x^4 - 333x^3 + x - 1
-55x^2 + 5x
```

---

## 题目分析

### 问题的本质

这是一个**多项式字符串格式化**问题。需要根据一系列格式化规则将系数数组转换为可读的多项式字符串。

### 关键规则

| 规则 | 说明 |
|------|------|
| 首项符号 | 正不显示，负显示 `-` |
| 后续项符号 | 正显示 ` + `，负显示 ` - ` |
| 系数 1 或 -1 | 不显示数字（常数项除外） |
| 指数 1 | 不显示指数 |
| 零系数 | 不显示该项 |
| 全零 | 输出 `0` |

---

## 参考代码

```cpp
// Polynomial Showdown
// UVa ID: 392
// Verdict: Accepted
// Submission Date: 2016-06-27
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool headTermSetted = false;  // 是否已输出首项

// 输出一项
inline void term(int coefficient, int degree)
{
    // 常数项特殊处理
    if (degree == 0)
    {
        if (headTermSetted)
        {
            if (coefficient == 0) return;
            cout << (coefficient > 0 ? " + " : " - ");
            cout << abs(coefficient);
        }
        else
        {
            cout << coefficient;
        }
        return;
    }

    // 系数为 0，跳过
    if (coefficient == 0) return;
    
    // 非首项，输出符号
    if (headTermSetted)
    {
        cout << (coefficient > 0 ? " + " : " - ");
        if (abs(coefficient) > 1) cout << abs(coefficient);
    }
    else
    {
        // 首项
        if (abs(coefficient) > 1) 
            cout << coefficient;
        else if (coefficient < 0) 
            cout << "-";
    }

    // 输出 x 和指数
    cout << "x";
    if (degree > 1) 
        cout << "^" << degree;

    headTermSetted = true;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int c8, c7, c6, c5, c4, c3, c2, c1, c0;

    while (cin >> c8 >> c7 >> c6 >> c5 >> c4 >> c3 >> c2 >> c1 >> c0)
    {
        headTermSetted = false;

        term(c8, 8);
        term(c7, 7);
        term(c6, 6);
        term(c5, 5);
        term(c4, 4);
        term(c3, 3);
        term(c2, 2);
        term(c1, 1);
        term(c0, 0);

        // 如果所有系数都为零，常数项已在 term 中输出
        // term(0,0) 会输出 0
        cout << endl;
    }

    return 0;
}
```
