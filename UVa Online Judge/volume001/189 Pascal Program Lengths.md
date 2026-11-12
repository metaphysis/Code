[UVa 189 Pascal Program Lengths](https://blog.csdn.net/metaphysis/article/details/160911156)

## 题目分析

本题要求计算 $\texttt{Turbo Pascal}$ 程序的长度，长度由若干类 $\texttt{token}$ 的数量决定，包括：

- 保留字（$\texttt{reserved words}$）
- 标识符（$\texttt{identifiers}$）
- 常量（$\texttt{constants}$）
- 左括号 `(` 和左方括号 `[`
- 运算符：`+`、`-`、`*`、`/`、`=`、`<`、`>`、`<=`、`>=`、`<>`、`@`、`^`、`:=`

需要特别注意的是：

1. **注释**：使用 `{}` 界定，不嵌套，注释内容完全忽略。
2. **字符串常量**：使用单引号 `'` 界定，字符串中的 `''` 表示一个单引号字符。
3. **数字常量**：包括整数、实数、科学计数法形式以及十六进制常量（以 `$` 开头）。
4. **标识符**：以字母或下划线 `_` 开头，后跟字母、数字或下划线。
5. **子范围**：`lower..upper` 形式中的 `..` 不是单独 token，而是两个 `.` 字符（但 `.` 不在计数范围内）。
6. **`+` 和 `-`**：尽可能视为运算符，例如 `x := -3` 中的 `-` 是运算符。

## 解题思路

本题的核心是对 $\texttt{Pascal}$ 源代码进行一次扫描，识别出所有需要计数的 $\texttt{token}$，同时忽略注释、字符串内容等其他字符。

一种可行的策略是 **多阶段扫描**：

1. **预处理**：将全部代码合并为一个字符串，并转换为小写，便于后续匹配保留字和标识符。
2. **移除注释**：扫描字符串，将 `{` 到 `}` 之间的内容替换为空格。
3. **处理字符串常量**：扫描字符串，将 `'` 到 `'` 之间的内容替换为空格，同时注意 `''` 转义。遇到字符串常量时，需要为字符串本身计数 $1$ 次（字符串常量属于常量的一种）。
4. **计数括号和方括号**：扫描字符串，遇到 `(` 或 `[` 则计数器加 $1$，将这些字符替换为空格。
5. **计数标识符和保留字**：在 `begin` 之前的部分扫描标识符（因为变量声明只出现在 `begin` 之前），记录去重后的标识符列表，然后在全文中计数这些标识符的每次出现。
6. **计数数字常量**：扫描字符串，识别十六进制、整数、实数、科学计数法形式的数字常量，每次识别一个常量则计数器加 $1$。
7. **计数运算符**：依次匹配题目中给出的所有运算符，每次匹配成功则计数器加 $1$。
8. **处理剩余标识符**：扫描剩余字符串，识别可能遗漏的标识符（例如保留字）并计数。

最终输出格式为：`Program by 姓名 contains 数量 units.`

## 代码实现

```cpp
// Pascal Program Lengths
// UVa ID: 189
// Verdict: Accepted
// Submission Date: 2016-04-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 存储整个程序的源代码
string program;

// 需要计数的运算符列表，按长度从长到短排列便于匹配
string operators[13] = {
    "<=", ">=", "<>", ":=", "@", "^", "+", "-", "*", "/", "=", "<", ">",
};

// 计算程序长度（单位数）
int count() {
    int counter = 0;

    // 统一转换为小写，便于后续匹配
    for (int i = 0; i < program.length(); i++)
        if (isalpha(program[i]))
            program[i] = tolower(program[i]);

    // 第一阶段：处理注释 {} 和字符串常量
    int index = 0;
    while (index < program.length()) {
        // 处理注释
        if (program[index] == '{') {
            program[index++] = ' ';
            while (index < program.length()) {
                char current = program[index];
                program[index] = ' ';
                if (current == '}')
                    break;
                index++;
            }
        }
        // 处理字符串常量
        else if (program[index] == '\'') {
            counter++;                    // 字符串常量作为一个 token 计数
            program[index++] = ' ';
            while (index < program.length()) {
                if (program[index] == '\'') {
                    // 两个连续单引号表示一个单引号字符，属于字符串内容
                    if (program[index + 1] == '\'') {
                        program[index] = ' ';
                        program[index + 1] = ' ';
                        index += 2;
                    } else {
                        program[index] = ' ';
                        break;            // 字符串结束
                    }
                } else program[index++] = ' ';
            }
        }
        index++;
    }

    // 第二阶段：计数左括号和左方括号，右括号和右方括号忽略
    index = 0;
    while (index < program.length()) {
        if (program[index] == '(' || program[index] == '[') {
            counter++;
            program[index] = ' ';
        } else if (program[index] == ')' || program[index] == ']') {
            program[index] = ' ';
        }
        index++;
    }

    // 第三阶段：在 BEGIN 之前收集标识符（变量名、类型名等）
    index = 0;
    int last = program.find("begin");
    if (last == program.npos)
        last = program.length();          // 如果没有 begin，则扫描整个程序
    vector<string> variables;
    while (index < last) {
        // 标识符：字母或下划线开头
        if (isalpha(program[index]) || program[index] == '_') {
            string block;
            block += program[index];
            counter++;                    // 每个标识符计数一次
            program[index++] = ' ';
            while (index < last)
                if (isalpha(program[index]) || isdigit(program[index]) || program[index] == '_') {
                    block += program[index];
                    program[index++] = ' ';
                }
                else
                    break;
            variables.push_back(block);
        }
        index++;
    }

    // 第四阶段：在全文中查找这些标识符的每次出现并计数
    index = 0;
    while (index < variables.size()) {
        int next = program.find(variables[index]);
        while (next != program.npos) {
            // 检查是否为独立单词（边界不是字母、数字、下划线）
            if (isalpha(program[next - 1]) == false &&
                isdigit(program[next - 1]) == false &&
                program[next - 1] != '_' &&
                isalpha(program[next + variables[index].length()]) == false &&
                isdigit(program[next + variables[index].length()]) == false &&
                program[next + variables[index].length()] != '_') {
                counter++;
                for (int i = 0; i < variables[index].length(); i++)
                    program[next + i] = ' ';
            }
            next += variables[index].length();
            next = program.find(variables[index], next);
        }
        index++;
    }

    // 第五阶段：处理数字常量
    index = 0;
    while (index < program.length()) {
        // 十六进制常量：以 $ 开头
        if (program[index] == '$') {
            counter++;
            program[index++] = ' ';
            while (index < program.length()) {
                char current = program[index];
                if (isdigit(current) || (current >= 'a' && current <= 'f')) program[index++] = ' ';
                else break;
            }
        } // 十进制数字常量（整数、实数、科学计数法）
        else if (isdigit(program[index])) {
            counter++;
            program[index++] = ' ';
            // 整数部分
            while (index < program.length())
                if (isdigit(program[index])) program[index++] = ' ';
                else break;

            // 小数部分（可选）
            if (index < program.length() && program[index] == '.') {
                program[index++] = ' ';
                while (index < program.length())
                    if (isdigit(program[index])) program[index++] = ' ';
                    else break;
            }

            // 指数部分（可选）
            if (index < program.length() && program[index] == 'e') {
                program[index++] = ' ';
                if (program[index] == '+' || program[index] == '-') program[index++] = ' ';
                while (index < program.length() && isdigit(program[index])) program[index++] = ' ';
            }
        }

        index++;
    }

    // 第六阶段：处理运算符
    for (int i = 0; i < 13; i++) {
        int start = 0;
        int next = program.find(operators[i], start);
        while (next != program.npos) {
            counter++;
            for (int j = 0; j < operators[i].length(); j++) program[next + j] = ' ';
            start = next + operators[i].length();
            next = program.find(operators[i], start);
        }
    }

    // 第七阶段：处理剩余的标识符（如保留字）
    index = 0;
    while (index < program.length()) {
        if (isalpha(program[index]) || program[index] == '_') {
            counter++;
            program[index++] = ' ';
            while (index < program.length())
                if (isalpha(program[index]) || isdigit(program[index]) || program[index] == '_') program[index++] = ' ';
                else break;
        }
        index++;
    }

    return counter;
}

// 输出结果
void output(string name) {
    int units = count();
    cout << "Program by " << name << " contains " << units << " units.\n";
}

int main() {
    string line;
    while (getline(cin, line)) {
        string firstTwoColumns = line.substr(0, 2);
        // 遇到 ~~ 表示程序结束，输出结果并清空
        if (firstTwoColumns == "~~") {
            output(line.substr(2));
            program.clear();
        } else {
            // 将每行代码拼接，用空格分隔保证 token 边界正确
            program += line;
            program += ' ';
        }
    }

    return 0;
}
```
