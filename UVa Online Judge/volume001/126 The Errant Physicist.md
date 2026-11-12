[UVa 126 The Errant Physicist](https://blog.csdn.net/metaphysis/article/details/156746434)

## 题目概述

著名物理学家 $\texttt{Alfred E Neuman}$ 在处理涉及 $x$ 和 $y$ 多项式乘法的问题时经常出错，导致核弹头提前引爆，摧毁了五座大城市和几片雨林。  
你的任务是编写一个程序，正确计算两个多项式的乘积，以避免进一步的灾难。

**输入**  
- 输入数据包含若干对行，每行最多包含 $80$ 个字符。  
- 最后一行的第一个字符是 `#`，表示输入结束。  
- 每行输入一个没有空格、没有显式乘方运算符的多项式。  
- 指数为正非零无符号整数，系数为整数（可为负）。  
- 指数和系数的绝对值均不超过 $100$。  
- 每一项最多包含一个 $x$ 因子和一个 $y$ 因子。

**输出**  
- 对于每一对多项式，计算乘积并输出两行：第一行输出指数，第二行输出对应的项。  
- 两行长度相等，较短的末尾用空格补齐。  
- 输出格式需满足以下规则：  
    1. 项按 $x$ 的降序排列，$x$ 相同时按 $y$ 的升序排列。  
    2. 同类项合并。  
    3. 系数为零的项不输出。  
    4. 系数为 $1$ 时省略（常数项 $1$ 除外）。  
    5. 指数为 $1$ 时省略。  
    6. $x^0$ 和 $y^0$ 因子省略。  
    7. 项间的加减号前后各有一个空格。  
    8. 首项系数为负时，第一列输出负号，无空格；否则从第一列开始输出系数。

## 解题思路

本题的核心是多项式乘法的模拟与格式化输出。我们可以将问题分解为以下几个步骤：

1. **解析输入**  
   将每行输入按 `+` 或 `-` 拆分为单独的项。由于输入没有空格，且可能以正号或负号开头，我们需要为每项补上符号以便后续处理。

2. **解析单项式**  
   对于每一项，需要提取出：
    - 符号（正或负）
    - 系数（整数）
    - $x$ 的指数（默认为 $0$）
    - $y$ 的指数（默认为 $0$）
   
   注意系数可能省略（即为 $1$），指数也可能省略（即为 $1$）。解析时需要处理这些情况。

3. **多项式乘法**  
   使用二维数组 `coefficients[i][j]` 表示 $x^i y^j$ 项的系数。  
   遍历第一个多项式的每一项和第二个多项式的每一项，计算它们相乘后的系数，并累加到对应位置。

4. **格式化输出**  
   输出分为两行：
    - 第一行输出指数，即每个项的 $x$ 和 $y$ 的指数，按规则对齐。
    - 第二行输出具体的项（包括系数、变量和符号）。
   
   输出时需按 $x$ 降序、$y$ 升序遍历 `coefficients` 数组。对于每个非零系数项：
    - 处理符号（首项特殊处理）
    - 输出系数（注意省略 $1$）
    - 输出 $x$ 和 $y$（注意指数为 $1$ 时省略）
    - 确保两行对齐，指数和变量位置对应

5. **对齐处理**  
   由于第一行只输出数字，第二行输出变量和符号，为了保证两行等长且对齐，需要计算每个数字占用的宽度，并在输出时用空格补齐。

## 代码实现

```cpp
// The Errant Physicist
// UVa ID: 126
// Verdict: Accepted
// Submission Date: 2020-05-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

#define MAXN 210

int coefficients[MAXN][MAXN];
int part1[4], part2[4];

void getItem(vector<string>& c, string line) {
    if (line[0] != '-' && line[0] != '+')
        line = '+' + line;
    while (true) {
        int plusIndex = line.rfind('+');
        int minusIndex = line.rfind('-');
        if (plusIndex >= 0 || minusIndex >= 0) {
            c.push_back(line.substr(max(plusIndex, minusIndex)));
            line = line.substr(0, max(plusIndex, minusIndex));
        } else break;
    }
}

int getExponent(string& item, char next) {
    int exponent = 0, haveExponent = 0;
    item = item.substr(1);
    while (item.length() && item[0] != next) {
        haveExponent = 1;
        exponent = exponent * 10 + item[0] - '0';
        item = item.substr(1);
    }
    if (!haveExponent) exponent = 1;
    return exponent;
}

void getPart(string item, int part[]) {
    // 解析符号。
    part[0] = (item[0] == '-' ? -1 : 1);
    if (item[0] == '+' || item[0] == '-') item = item.substr(1);
    // 获取系数。
    int coefficient = 0;
    int haveDigit = 0;
    while (item.length() && item[0] >= '0' && item[0] <= '9') {
        haveDigit = 1;
        coefficient = coefficient * 10 + item[0] - '0';
        item = item.substr(1);
    }
    part[1] = (haveDigit == 0 ? 1 : coefficient);
    // 获取指数。
    if (item.length()) {
        char start = item[0];
        int exponent1 = 0, exponent2 = 0;
        if (start == 'x' || start == 'y') {
            char next = (start == 'x' ? 'y' : 'x');
            exponent1 = getExponent(item, next);
            if (item.length() > 0) exponent2 = getExponent(item, next);
        }
        part[2] = start == 'x' ? exponent1 : exponent2;
        part[3] = start == 'x' ? exponent2 : exponent1;
    }
}

// 将两个项目相乘。
void multiply(string term1, string term2) {
    memset(part1, 0, sizeof(part1));
    memset(part2, 0, sizeof(part2));
    getPart(term1, part1);
    getPart(term2, part2);
    coefficients[part1[2] + part2[2]][part1[3] + part2[3]] += part1[0] * part1[1] * part2[0] * part2[1];
}

string space(int n) {
    stringstream ss;
    string line;
    ss << n;
    ss >> line;
    return string(line.length(), ' ');
}

void output(bool printExponent, int n) {
    if (printExponent) cout << n;
    else cout << space(n); 
}

bool print(bool printExponent) {
    bool firstItemPrinted = false;
    for (int i = 200; i >= 0; i--)
        for (int j = 0; j <= 200; j++)
            if (coefficients[i][j] != 0) {
                if (firstItemPrinted == false) {
                    if (coefficients[i][j] < 0) cout << (printExponent ? " " : "-");
                    firstItemPrinted = true;
                } else {
                    cout << " ";
                    cout << (printExponent ? " " : ((coefficients[i][j] > 0) ? "+" : "-"));
                    cout << " ";
                }
                if (fabs(coefficients[i][j]) > 1) output(!printExponent, fabs(coefficients[i][j]));
                else if (i == 0 && j == 0) cout << (printExponent ? " " : "1");
                if (i > 0)  cout << (printExponent ? " " : "x");
                if (i > 1)  output(printExponent, i);
                if (j > 0)  cout << (printExponent ? " " : "y");
                if (j > 1)  output(printExponent, j);
            }
    return firstItemPrinted;
}

int main(int ac, char *av[]) {
    string line;
    vector<string> polynomial1, polynomial2;
    while (getline(cin, line), line != "#") {
        polynomial1.clear();
        polynomial2.clear();
        getItem(polynomial1, line);
        getline(cin, line);
        getItem(polynomial2, line);
        memset(coefficients, 0, sizeof(coefficients));
        for (int i = 0; i < polynomial1.size(); i++)
            for (int j = 0; j < polynomial2.size(); j++)
                multiply(polynomial1[i], polynomial2[j]);
        print(true);
        cout << '\n';
        bool flag = print(false);
        if (!flag) cout << 0;
        cout << '\n';
    }
	return 0;
}
```

## 总结

本题主要考察字符串解析、多项式乘法模拟和格式化输出。需要注意的细节非常多，尤其是输出格式的严格要求。通过合理设计数据结构和遍历顺序，可以高效地完成计算和输出。代码中使用二维数组存储系数，解析函数提取每项信息，乘法过程累加系数，最后按规则输出两行，确保对齐。
