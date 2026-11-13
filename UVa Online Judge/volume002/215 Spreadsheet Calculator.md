[UVa 215 Spreadsheet Calculator](https://blog.csdn.net/metaphysis/article/details/161046683)

## 题目分析

本题要求实现一个简单的电子表格计算器。电子表格是一个矩形网格，每个单元格包含一个整数或者一个表达式。表达式由整数常量、单元格引用以及 `+` 和 `-` 运算符组成，计算时遵循从左到右的结合顺序。

输入首先给出行数 $r$ 和列数 $c$，其中 $r \leq 20$，$c \leq 10$。行用大写字母 $\texttt{A}$ 到 $\texttt{T}$ 标记，列用数字 $0$ 到 $9$ 标记，因此单元格 $\texttt{A0}$ 表示第 $1$ 行第 $1$ 列。随后按行主序输入每个单元格的内容。输入以 `0 0` 结束。

输出要求分为两种情况：
1. 如果所有单元格都能成功计算（无循环引用），则输出整个表格，列号右对齐，宽度为 $6$，每行以行字母开头。
2. 如果存在循环引用导致部分单元格无法计算，则按行主序输出所有未计算单元格的标签、原始表达式，每个单元格一行。

## 解题思路

### 核心难点

本题的核心难点在于 **处理循环依赖**。例如，单元格 $\texttt{A1}$ 引用了 $\texttt{B1}$，而 $\texttt{B1}$ 又引用了 $\texttt{A1}$，这就形成了循环引用，导致无法计算出数值。

### 解决方案

我们可以采用 **带标记的深度优先搜索**（$\texttt{DFS}$） 来计算每个单元格的值：

1. **表达式预处理**：对于每个单元格的原始表达式，将运算符 `+` 和 `-` 用空格包围，以便后续使用字符串流进行拆分。注意减法运算符前的负号需要与操作数分开处理。

2. **递归求值**：定义函数 `evaluate(i, j)` 计算单元格 $(i, j)$ 的值。在求值过程中：
   - 如果当前单元格已经计算过，直接返回其值。
   - 否则，将其表达式拆分成若干项（每个项是整数或单元格引用）。
   - 对于每个项，调用 `getValue` 获取其值。如果 `getValue` 返回 `false`，说明存在循环引用，则当前单元格也无法计算。

3. **循环检测**：使用一个集合 `undefined` 记录当前递归路径上正在计算的单元格标签。当遇到一个已经在集合中的单元格引用时，说明形成了循环，此时返回 `false`。这就是典型的 $\texttt{DFS}$ 环检测方法。

4. **输出处理**：
   - 遍历所有单元格，尝试计算。如果全部成功，输出格式化表格。
   - 否则，输出所有未成功计算的单元格的原始表达式。

### 代码结构说明

- `trim(line)`：去除行末尾的空白字符。
- `split(line)`：将表达式中的运算符 `+` 和 `-` 替换为空格，便于分词。注意减法运算符前插入一个空格，使其成为独立的负号标记。
- `getValue(variable, value)`：解析一个字符串项（可能为整数或单元格引用），递归计算其数值。
- `evaluate(i, j)`：计算当前单元格的值。
- `calculate()`：主计算函数，决定最终输出格式。

## 代码实现

```cpp
// Spreadsheet Calculator
// UVa ID: 215
// Verdict: Accepted
// Submission Date: 2016-04-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cell[20][10];               // 存储每个单元格的计算结果
bool calculated[20][10];        // 标记单元格是否已成功计算
string original[20][10];        // 存储单元格的原始表达式
string expression[20][10];      // 存储预处理后的表达式（便于拆分）
int rows, columns;              // 表格的行数和列数
set<string> undefined;          // 存储当前递归路径上的单元格标签，用于检测循环引用

// 去除字符串末尾的空白字符
string trim(string line) {
    for (int i = line.length() - 1; i >= 0; i--)
        if (isblank(line[i]))
            line.erase(line.begin() + i);
    return line;
}

// 预处理表达式：将 '+' 和 '-' 替换为空格，便于字符串流拆分
string split(string line) {
    for (int i = line.length() - 1; i >= 0; i--)
    {
        if (line[i] == '+')
            line[i] = ' ';
        else if (line[i] == '-')
            line.insert(line.begin() + i, ' ');   // 在 '-' 前插入空格
    }
    return line;
}

bool evaluate(int, int);

// 获取一个操作数的值（操作数可以是整数或单元格引用）
bool getValue(string variable, int& value) {
    int sign = 1;
    if (variable[0] == '-')
    {
        sign = -1;
        variable.erase(variable.begin());
    }
    
    // 如果操作数是单元格引用（以字母开头）
    if (isalpha(variable[0]))
    {
        int ii = variable[0] - 'A';
        int jj = variable[1] - '0';
        
        if (calculated[ii][jj])
        {
            value = sign * cell[ii][jj];
            return true;
        }
        else
        {
            // 检测循环引用：如果当前单元格已在递归路径中
            if (undefined.count(variable) > 0)
                return false;
                
            undefined.insert(variable);           // 标记进入当前单元格
            if (evaluate(ii, jj))                 // 递归计算引用的单元格
            {
                undefined.erase(variable);        // 递归返回，清除标记
                calculated[ii][jj] = true;
                value = sign * cell[ii][jj];
                return true;
            }
            
            return false;
        }
    }
    // 操作数是整数常量
    else
    {
        value = sign * stoi(variable);
        return true;
    }
}

// 计算单元格 (i, j) 的值
bool evaluate(int i, int j) {
    string variable;
    vector<string> variables;
    istringstream iss(expression[i][j]);
    // 拆分预处理后的表达式，得到各个操作数
    while (iss >> variable)
        variables.push_back(variable);

    int sum = 0;
    for (int i = 0; i < variables.size(); i++)
    {
        int value;
        if (getValue(variables[i], value))
            sum += value;
        else
            return false;
    }

    cell[i][j] = sum;
    calculated[i][j] = true;

    return true;
}

// 主计算函数
void calculate() {
    int cellCalculated = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            undefined.clear();
            if (calculated[i][j] || evaluate(i, j))
                cellCalculated++;
        }

    // 所有单元格均成功计算，输出整个表格
    if (cellCalculated == rows * columns)
    {
        cout << " ";
        for (int i = 0; i < columns; i++)
            cout << setw(6) << right << i;
        cout << endl;
        
        for (int i = 0; i < rows; i++)
        {
            cout << (char)('A' + i);
            for (int j = 0; j < columns; j++)
                cout << setw(6) << right << cell[i][j];
            cout << endl;
        }
    }
    // 存在循环引用，输出所有未计算的单元格的原始表达式
    else
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                if (calculated[i][j] == false)
                    cout << (char)('A' + i) << j << ": " << original[i][j] << endl;
    }
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    string line;
    while (cin >> rows >> columns, rows && columns) {
        cin.ignore();
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
            {
                getline(cin, line);
                original[i][j] = trim(line);
                expression[i][j] = split(original[i][j]);
                calculated[i][j] = false;
                cell[i][j] = 0;
            }

        calculate();
        cout << endl;
    }
    
	return 0;
}
```
