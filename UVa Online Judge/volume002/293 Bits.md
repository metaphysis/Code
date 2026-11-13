[UVa 293 Bits](https://blog.csdn.net/metaphysis/article/details/161387510)

## 题目分析

本题要求根据给定的消息格式语法，计算每条消息在传输时所需的最少比特数。消息的格式由一种类似于编程语言类型定义的文法描述，支持记录（`record`）、数组（`array`）、字符串（`string`）、枚举（`enum`）和范围（`range`）等类型。

### 核心问题

输入包含多个测试用例，每个测试用例是一条消息定义。消息的基本结构是：

```cpp
id : type
```

我们需要根据 `type` 的具体类型，递归地计算出整个消息所需的比特数。计算规则如下：

1. **`record`**：所有字段的大小之和
2. **`array`**：元素类型的大小 × 元素个数
3. **`string`**：字符串长度 × $7$ 位（每个字符占 $7$ 位）
4. **`enum`**：能区分所有枚举值的最小比特数
5. **`range`**：能表示范围内所有整数的最小比特数

对于 **`enum`** 和 **`range`**，需要计算“最小比特数” —— 即给定 $n$ 个不同的值，需要 $\lceil \log_2 n \rceil$ 位来表示。特别地，当 $n = 1$ 时，需要 $0$ 位。

### 输入格式特点

- 输入中可能包含任意数量的空白字符（空格、制表符、换行符）
- 输入保证语法正确
- 范围 `[L .. H]` 满足 $L \le H$
- 字符串长度为正整数

---

## 解题思路

### 整体框架

由于输入格式具有递归嵌套的结构，最自然的解法是使用 **递归下降解析**。代码将整个输入读入一个字符串后，利用一个全局索引 `i` 进行扫描，根据当前字符判断类型，递归调用对应的解析函数计算比特数。

### 预处理：比特数计算函数

代码中的 `convertToBits(int length)` 函数用于计算表示 `length` 个不同值所需的最少比特数：

- 如果 `length == 1`，返回 $0$（不需要任何位即可区分）
- 否则，不断倍增直到覆盖所有值，统计所需位数

这个函数本质上是计算 $\lceil \log_2(length) \rceil$。

### 各类型解析函数

#### 1. `getRecord()`

- 遇到 `{` 时调用
- 跳过 `{`，然后循环处理每个字段
- 每个字段格式为 `id : type`，跳过 `id` 和 `:` 后调用 `getBits()` 计算该字段大小并累加
- 遇到 `}` 时结束，返回累加和

#### 2. `getArray()`

- 遇到 `a`（`array` 的首字母）时调用
- 跳过 `"array"` 字符串
- 解析范围 `[start .. end]`：
  - 处理可能的负号
  - 读取起始值和结束值
- 计算元素个数 = `end - start + 1`
- 跳过 `"of"` 后递归调用 `getBits()` 获取元素类型大小
- 返回 `个数 × 元素大小`

#### 3. `getString()`

- 遇到 `s`（`string` 的首字母）时调用
- 跳过 `"string("`
- 读取数字作为字符串长度
- 遇到 `)` 后结束
- 返回 `长度 × 7`

#### 4. `getEnum()`

- 遇到 `(` 时调用
- 统计逗号个数来确定枚举值的数量
- 遇到 `)` 后结束
- 返回 `convertToBits(枚举值个数)`

#### 5. `getRange()`

- 遇到 `[` 时调用
- 解析起始值和结束值（可能为负数）
- 计算值的个数 = `end - start + 1`
- 返回 `convertToBits(个数)`

### 主解析函数 `getBits()`

根据当前字符 `message[i]` 判断类型并调用相应函数：

| 当前字符 | 类型 | 调用函数 |
|:---:|:---:|:---:|
| `{` | record | `getRecord()` |
| `a` | array | `getArray()` |
| `s` | string | `getString()` |
| `(` | enum | `getEnum()` |
| `[` | range | `getRange()` |

### 消息处理流程

1. 读入所有非空白字符到 `message` 字符串
2. 遍历 `message`，提取消息的 `id`
3. 遇到 `:` 后调用 `getBits()` 计算该消息的总比特数
4. 输出格式化的结果

---

## 注意事项

- **空白字符处理**：代码通过 `cin >> ascii` 逐个读入非空白字符，自动过滤了空格、制表符和换行符
- **字符串长度限制**：题目规定 id 长度为 $1 \le L \le 256$，字符串长度为正整数
- **范围处理**：需要处理负数，代码中通过 `sign` 变量实现
- **边界情况**：当范围或枚举只有 $1$ 个值时，比特数为 $0$

---

## 样例验证

### 样例输入

```
3
year : [1970..2030]
team : { name : string(14) members : array [1..3] of { sex : ( male, female ) name : string(20) age : [16..30] } position : [1..40] }
jurynames : array [1..3] of string(20)
```

### 计算过程

1. **`year`**：范围 $1970$ 到 $2030$，共 $61$ 个值，$\lceil \log_2 61 \rceil = 6$ 位
2. **`team`**：需要累加各字段
   - `name`：$14 \times 7 = 98$ 位
   - `members`：数组，$3$ 个元素，每个元素是 record，内部包含：
     - `sex`：枚举 `(male, female)`，$2$ 个值，$1$ 位
     - `name`：$20 \times 7 = 140$ 位
     - `age`：范围 $16$ 到 $30$，共 $15$ 个值，$4$ 位
     子 record 合计 $1 + 140 + 4 = 145$ 位
     members 总大小 $3 \times 145 = 435$ 位
   - `position`：范围 $1$ 到 $40$，共 $40$ 个值，$6$ 位
   总计 $98 + 435 + 6 = 539$ 位
3. **`jurynames`**：$3 \times (20 \times 7) = 3 \times 140 = 420$ 位

与样例输出完全一致。

---

## 代码实现

```cpp
// Bits
// UVa ID: 293
// Verdict: Accepted
// Submission Date: 2016-06-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string message;
int i;

// 计算表示 length 个不同值所需的最少比特数
// 本质是 ceil(log2(length))，但 length == 1 时返回 0
int getBits();

int convertToBits(int length)
{
    if (length == 1)
        return 0;

    int bit = 1;
    for (int i = 2; i < length; i *= 2)
        bit++;
    return bit;
}

// 解析 record 类型：{ data+ }
// 返回 record 中所有字段的比特数之和
int getRecord()
{
    i++;  // 跳过 '{'

    int bits = 0;
    while (message[i] != '}')
    {
        // 跳过字段名，直到 ':' 
        while (message[i] != ':')
            i++;
        i++;  // 跳过 ':'
        bits += getBits();  // 递归计算字段类型的比特数
    }

    i++;  // 跳过 '}'
    return bits;
}

// 解析 array 类型：array range of type
// 返回 元素个数 × 元素类型大小
int getArray()
{
    i += 6;  // 跳过 "array"

    // 解析起始值，可能为负数
    int sign = 1;
    if (message[i] == '-')
    {
        sign = -1;
        i++;
    }
    int startLength = 0;
    while (message[i] != '.')
    {
        startLength = startLength * 10 + message[i] - '0';
        i++;
    }
    startLength *= sign;

    // 跳过 ".."
    i += 2;

    // 解析结束值，可能为负数
    sign = 1;
    if (message[i] == '-')
    {
        sign = -1;
        i++;
    }
    int endLength = 0;
    while (message[i] != ']')
    {
        endLength = endLength * 10 + message[i] - '0';
        i++;
    }
    endLength *= sign;

    // 跳过 "] of"
    i += 3;

    // 元素个数 × 元素类型大小
    return (endLength - startLength + 1) * getBits();
}

// 解析 string 类型：string(整数)
// 返回 长度 × 7
int getString()
{
    i += 7;  // 跳过 "string("

    int length = 0;
    while (message[i] != ')')
    {
        length = length * 10 + message[i] - '0';
        i++;
    }

    i++;  // 跳过 ')'
    return length * 7;
}

// 解析 enum 类型：(id, id, ...)
// 返回能区分所有枚举值的最小比特数
int getEnum()
{
    i++;  // 跳过 '('

    int length = 1;  // 枚举值个数，至少为 1
    while (message[i] != ')')
    {
        if (message[i] == ',')
            length++;
        i++;
    }

    i++;  // 跳过 ')'
    return convertToBits(length);
}

// 解析 range 类型：[L .. H]
// 返回能表示范围内所有整数的最小比特数
int getRange()
{
    i++;  // 跳过 '['

    // 解析起始值
    int sign = 1;
    if (message[i] == '-')
    {
        sign = -1;
        i++;
    }
    int startLength = 0;
    while (message[i] != '.')
    {
        startLength = startLength * 10 + message[i] - '0';
        i++;
    }
    startLength *= sign;

    // 跳过 ".."
    i += 2;

    // 解析结束值
    sign = 1;
    if (message[i] == '-')
    {
        sign = -1;
        i++;
    }
    int endLength = 0;
    while (message[i] != ']')
    {
        endLength = endLength * 10 + message[i] - '0';
        i++;
    }
    endLength *= sign;

    i++;  // 跳过 ']'
    return convertToBits(endLength - startLength + 1);
}

// 根据当前字符判断类型并递归计算比特数
int getBits()
{
    if (message[i] == '{')
        return getRecord();
    if (message[i] == 'a')
        return getArray();
    if (message[i] == 's')
        return getString();
    if (message[i] == '(')
        return getEnum();
    if (message[i] == '[')
        return getRange();
}

// 处理所有消息，输出结果
void process()
{
    i = 0;
    while (i < message.length())
    {
        cout << "A \"";
        // 输出消息 id
        while (message[i] != ':')
        {
            cout << message[i];
            i++;
        }

        i++;  // 跳过 ':'
        cout << "\" message requires " << getBits() << " bits." << endl;
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    getline(cin, line);  // 读取测试用例个数，但不使用

    char ascii;
    // 读取所有非空白字符，自动过滤空格、制表符、换行符
    while (cin >> ascii)
        message += ascii;

    process();

    return 0;
}
```
