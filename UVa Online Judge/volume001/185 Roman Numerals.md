[UVa 185 Roman Numerals](https://blog.csdn.net/metaphysis/article/details/160891037)

## 题目分析

本题要求判断给定的罗马数字算式在两种规则下的正确性：

1. **罗马数字算术规则**：判断算式是否满足罗马数字的减法表示法规则，并且数值计算正确。
2. **阿拉伯数字编码规则**：将每个罗马字母映射为 $0$ - $9$ 的一个数字，不同字母映射到不同数字，判断是否存在映射使得算式成立（数字不能有前导零，不能单独为零）。

输入格式为 `A + B = C`，其中 $A$、$B$、$C$ 是合法的罗马数字（长度不超过 $9$）。需要输出两个单词，第一个表示罗马算术是否正确（`Correct` / `Incorrect`），第二个表示阿拉伯编码是否存在解（`impossible` / `valid` / `ambiguous`）。

## 解题思路

### 第一部分：罗马算术判断

判断罗马数字算术是否正确，分两步：

1. 检查 $A$、$B$、$C$ 是否符合合法的罗马数字表示法（本题采用标准减法表示法，如 $4$ 写作 `IV` 而非 `IIII`）。
2. 将三个罗马数字转换为数值，验证 $A + B = C$ 是否成立。

罗马数字转数值的规则：从左到右扫描，如果当前字母的值小于右边字母的值，则做减法（加右边减当前），否则直接累加。

### 第二部分：阿拉伯数字编码判断

这是一个带约束的字母到数字的映射问题，使用回溯法（$\texttt{DFS}$）枚举所有可能的映射：

1. 收集算式中出现的所有不同罗马字母（最多 $7$ 个：`IVXLCDM`）。
2. 为这些字母分配 $0$ - $9$ 中不同的数字。
3. 约束条件：
   - 每个罗马数字的首字母不能映射到 $0$（无前导零）。
   - 映射后的数值不能为 $0$（零不会单独出现）。
4. 枚举所有合法映射，统计使 $A + B = C$ 成立的映射个数：
   - 个数为 $0$ → `impossible`
   - 个数为 $1$ → `valid`
   - 个数 $\ge 2$ → `ambiguous`

由于最大字母数为 $7$，全排列数为 $P(10, 7) = 604800$，可以接受。但为了效率，可以在找到两个解后提前终止。

## 代码实现

```cpp
// Roman Numerals
// UVa ID: 185
// Verdict: Accepted
// Submission Date: 2016-03-13
// UVa Run Time: 0.100s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 存储算式分解后的三个部分
string leftPart, rightPart, lastPart;

// 罗马数字的列分类：左列（I,X,C,M）可重复最多3次，右列（V,L,D）最多1次
string leftColumn = "IXCM", rightColumn = "VLD", allRoman = "IVXLCDM";

// 各罗马字母对应的数值
int numbers[] = {1, 5, 10, 50, 100, 500, 1000};

// 正则表达式：用于验证罗马数字是否符合标准减法表示法
string pattern = R"(^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$)";
regex romanExp(pattern, regex_constants::ECMAScript);

// 判断一个字符串是否为合法的标准罗马数字
bool isRoman(string &roman) {
    return regex_match(roman, romanExp);
}

// 将合法的罗马数字转换为整数值
int romanToNumber(string roman) {
    int number = 0, index = 0;
    while (index < roman.length() - 1) {
        int first = allRoman.find(roman[index]);
        int second = allRoman.find(roman[index + 1]);

        // 如果左边小于右边，则做减法
        if (numbers[first] < numbers[second]) {
            number += numbers[second] - numbers[first];
            index += 2;
        } else {
            number += numbers[first];
            index++;
        }
    }
    // 处理最后一个字符
    if (index < roman.length())
        number += numbers[allRoman.find(roman[index])];

    return number;
}

// 解析输入行，提取 A、B、C 三个部分
void parse(string &line) {
    int plusIndex = line.find('+');
    int equalIndex = line.find('=');

    leftPart = line.substr(0, plusIndex);
    rightPart = line.substr(plusIndex + 1, equalIndex - plusIndex - 1);
    lastPart = line.substr(equalIndex + 1);
}

// 判断罗马算术是否正确
string Roman() {
    // 任一字符串不是合法罗马数字，则算式不正确
    if (!isRoman(leftPart) || !isRoman(rightPart) || !isRoman(lastPart))
        return "Incorrect";
    return (romanToNumber(leftPart) + romanToNumber(rightPart) ==
        romanToNumber(lastPart)) ? "Correct" : "Incorrect";
}

// 用于回溯搜索的全局变量
int times = 0;          // 找到的解的个数
bool finished = false;  // 是否提前终止搜索
set<string> solutions;  // 存储映射关系，避免重复计数
vector<int> digits;     // 当前映射的数字
vector<bool> used;      // 数字是否已被使用
string matchNeed;       // 算式中出现的不同罗马字母

// 将映射后的阿拉伯数字字符串转换为整数
int arabicToNumber(string arabic) {
    int number = 0;
    for (int i = 0; i < arabic.length(); i++)
        number = number * 10 + digits[matchNeed.find(arabic[i])];
    return number;
}

// 深度优先搜索枚举所有可能的映射
void backtrack(int index) {
    if (finished)
        return;

    // 所有字母都已分配数字
    if (index == matchNeed.length()) {
        int leftNumber, rightNumber, lastNumber;

        // 检查前导零：每个罗马数字的首字母不能映射到0
        leftNumber = digits[matchNeed.find(leftPart[0])];
        rightNumber = digits[matchNeed.find(rightPart[0])];
        lastNumber = digits[matchNeed.find(lastPart[0])];

        if (leftNumber == 0 || rightNumber == 0 || lastNumber == 0)
            return;

        // 转换为整数
        leftNumber = arabicToNumber(leftPart);
        rightNumber = arabicToNumber(rightPart);
        lastNumber = arabicToNumber(lastPart);

        // 零不能单独出现（数值不能为0）
        if (leftNumber == 0 || rightNumber == 0 || lastNumber == 0)
            return;

        // 检查算式是否成立
        if (leftNumber + rightNumber == lastNumber) {
            // 记录映射关系，用于去重
            string pair;
            for (int i = 0; i < matchNeed.length(); i++) {
                pair += matchNeed[i];
                pair += (char)(digits[i] + '0');
            }

            if (solutions.count(pair) == 0) {
                solutions.insert(pair);
                times++;
            }
        }

        // 找到至少两个解时提前终止
        if (times >= 2) finished = true;

        return;
    }

    // 为当前位置的字母分配一个未使用的数字
    for (int i = 0; i < used.size(); i++)
        if (used[i] == false) {
            used[i] = true;
            digits[index] = i;
            backtrack(index + 1);
            used[i] = false;
        }
}

// 判断阿拉伯数字编码的可能性
string Arabic(string &line) {
    // 初始化：收集算式中出现的所有不同罗马字母
    digits.clear();
    matchNeed.clear();
    for (int i = 0; i < allRoman.length(); i++)
        if (line.find(allRoman[i]) != line.npos) {
            matchNeed += allRoman[i];
            digits.push_back(0);
        }

    // 初始化数字使用标记
    used.clear();
    for (int i = 0; i <= 9; i++) used.push_back(false);

    // 重置搜索状态
    solutions.clear();
    finished = false;
    times = 0;
    
    // 开始回溯枚举
    backtrack(0);

    // 根据解的个数返回结果
    if (times == 0) return "impossible";
    else if (times == 1) return "valid";
    else return "ambiguous";
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);

    string line;
    while (getline(cin, line), line != "#") {
        // 去除行中的空白字符
        for (int i = line.length() - 1; i >= 0; i--)
            if (isblank(line[i]))
                line.erase(line.begin() + i);
        
        parse(line);
        cout << Roman() << " " << Arabic(line) << "\n";
    }

    return 0;
}
```

## 总结

本题综合考查了字符串处理、正则表达式、数值转换以及回溯搜索。关键在于：

- 罗马数字的合法表示校验使用正则表达式最为简洁。
- 阿拉伯编码部分需要仔细处理前导零和零值约束。
- 回溯搜索时通过提前终止（找到两个解即退出）可以显著提高效率。
