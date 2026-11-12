[UVa 159 Word Crosses](https://blog.csdn.net/metaphysis/article/details/158611607)

## 题目描述

本题要求实现一种特殊的文字排列方式 —— 单词十字架。一个单词十字架是由一对单词构成的，其中一个水平放置，另一个垂直放置，它们共享一个公共字母。领字十字架是指公共字母在水平单词中尽可能靠前，并且在满足这一条件的前提下，在垂直单词中也尽可能靠前。

现在要求处理四个单词（两对），将它们排列成双领字十字架的形式，即两个水平单词在同一行，每个单词对都构成一个领字十字架。

## 输入与输出

**输入格式**： 多行数据，每行包含四个大写字母组成的单词（长度为 $1$ 到 $10$），单词之间用空格分隔。以单独的一行 $\texttt{\#}$ 表示输入结束。

**输出格式**： 对每组四个单词，如果能组成双领字十字架，则输出相应的图形，两个水平单词之间留三个空格。如果不能，则输出 `Unable to make two crosses`。每组输出之间用一个空行分隔。

## 样例分析

输入样例：
```cpp
MATCHES CHEESECAKE PICNIC EXCUSES
PEANUT BANANA VACUUM GREEDY
#
```

输出样例：
```cpp
 C
 H
 E
 E
 S
 E          E
 C          X
MATCHES   PICNIC
 K          U
 E          S
            E
            S

Unable to make two crosses
```

## 题目解析

### 核心问题分析

本题的核心是处理两对单词的交叉关系。对于每对单词，需要找到：
1. 在第一个单词（水平放置）中，找到尽可能靠前的字母
2. 该字母在第二个单词（垂直放置）中也出现
3. 并且该字母在第二个单词中也尽可能靠前

这种寻找方式保证了构成 $\texttt{leading word cross}$。

### 关键难点

1. **交叉点的确定**：需要同时满足两个 $\texttt{leading}$ 条件
2. **图形布局**：两个水平单词在同一行，中间留三个空格
3. **垂直单词的对齐**：需要根据交叉点的位置调整垂直单词的起始行
4. **空白处理**：输出时需要去除每行末尾的多余空格

## 解题思路

### 1. 寻找交叉点

对于第一对单词 $a$（水平）和 $b$（垂直）：
- 遍历 $a$ 的每个字符（从前往后）
- 对每个字符，检查是否在 $b$ 中出现
- 记录第一个找到的匹配位置 $(aIndex, bIndex)$

对于第二对单词 $c$（水平）和 $d$（垂直），采用同样的方法。

### 2. 布局计算

假设找到的交叉点为：
- 第一对：$aIndex$（$a$ 中的位置），$bIndex$（$b$ 中的位置）
- 第二对：$cIndex$（$c$ 中的位置），$dIndex$（$d$ 中的位置）

关键布局参数：
- 水平方向：第一水平单词从第 $0$ 列开始，第二水平单词从第 $(len(a) + 3)$ 列开始
- 垂直方向：需要确保两个垂直单词能够正确对齐，起始行偏移量由两个 $bIndex$ 和 $dIndex$ 决定

### 3. 垂直对齐处理

两个垂直单词可能长度不同，交叉点位置也不同。为了保证它们能够正确显示，需要：
- 找出两个交叉点中较大的行号作为水平单词的行
- 根据这个基准行，调整每个垂直单词的起始行

### 4. 图形生成

使用二维字符数组存储图形：
1. 放置两个水平单词
2. 放置两个垂直单词
3. 标记每行的有效结束位置
4. 逐行输出，去除末尾空格

## 代码实现

```cpp
// Word Crosses
// UVa ID: 159
// Verdict: Accepted
// Submission Date: 2016-02-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool findCrosses(string line)
{
    string a, b, c, d;
    istringstream iss(line);
    iss >> a >> b >> c >> d;
    
    //cout << a << " " << b << " " << c << " " << d << endl;
    
    int aIndex = -1, bIndex = -1;
    for (int i = 0; i < a.length(); i++)
        if ((bIndex = b.find(a[i])) != b.npos)
        {
            aIndex = i;
            break;
        }
        
    int cIndex = -1, dIndex = -1;
    for (int i = 0; i < c.length(); i++)
        if ((dIndex = d.find(c[i])) != d.npos)
        {
            cIndex = i;
            break;
        }
    
    //cout << aIndex << " " << bIndex << " " << cIndex << " " << dIndex << endl;
    
    if (aIndex >= 0 && cIndex >= 0)
    {
        char matrix[30][30] = { 0 };
        memset(matrix, ' ', sizeof(matrix));
        
        for (int i = 0; i < a.length(); i++)
            matrix[max(bIndex, dIndex)][i] = a[i];
        for (int i = 0; i < b.length(); i++)
            matrix[i + (bIndex < dIndex ? dIndex - bIndex : 0)][aIndex] = b[i];
        for (int i = 0; i < c.length(); i++)
            matrix[max(bIndex, dIndex)][a.length() + 3 + i] = c[i];
        for (int i = 0; i < d.length(); i++)
            matrix[i + (dIndex < bIndex ? bIndex - dIndex : 0)][a.length() + 3 + cIndex] = d[i];
        
        
        for (int i = 0; i < 30; i++)
            for (int j = 29; j >= 0; j--)
                if (matrix[i][j] != ' ')
                {
                    matrix[i][j + 1] = '*';
                    break;
                }
        
        int height = max(bIndex, dIndex);
        height += max(b.length() - bIndex - 1, d.length() - dIndex - 1);
        for (int i = 0; i <= height; i++)
        {
            for (int j = 0; j < (a.length() + 3 + c.length()); j++)
                if (matrix[i][j] != '*')
                    cout << matrix[i][j];
                 else
                    break;
            cout << endl;
        }
        
        return true;
    }
    
    return false;
}

int main(int argc, char* argv[])
{
    string line;
    bool printBlankLine = false;
    while (getline(cin, line), line != "#")
    {
        if (printBlankLine == false)
            printBlankLine = true;
        else
            cout << endl;
            
        if (!findCrosses(line))
            cout << "Unable to make two crosses" << endl;
    }
        
	return 0;
}
```

## 关键代码解析

### 1. 交叉点查找
```cpp
for (int i = 0; i < a.length(); i++)
    if ((bIndex = b.find(a[i])) != b.npos)
    {
        aIndex = i;
        break;
    }
```
这里利用了 $\texttt{string::find}$ 函数返回第一个匹配位置的性质，自动满足 $\texttt{leading}$ 条件。

### 2. 垂直对齐计算
```cpp
matrix[i + (bIndex < dIndex ? dIndex - bIndex : 0)][aIndex] = b[i];
```
通过条件表达式计算每个垂直单词的起始行偏移，确保两个垂直单词都能正确显示。

### 3. 末尾空格处理
```cpp
for (int j = 29; j >= 0; j--)
    if (matrix[i][j] != ' ')
    {
        matrix[i][j + 1] = '*';
        break;
    }
```
使用 $\texttt{*}$ 标记每行的有效结束位置，避免输出多余空格。

## 时间复杂度分析

- 单词长度最多为 $10$，交叉点查找复杂度为 $O(10 \times 10) = O(100)$
- 图形生成使用固定大小的 $30 \times 30$ 数组，复杂度为常数
- 总体时间复杂度为 $O(1)$，非常高效

## 注意事项

1. 两个水平单词之间必须留三个空格
2. 每组输出之间需要有一个空行（最后一组之后不需要）
3. 垂直单词可能长度不同，需要正确处理对齐
4. 如果任意一对单词无法形成十字架，则输出无法完成的信息

## 总结

本题主要考察字符串处理和图形布局能力。核心在于正确理解 $\texttt{leading word cross}$ 的定义，并处理好两个垂直单词的对齐问题。代码实现时需要注意边界条件的处理和输出格式的要求。
