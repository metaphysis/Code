[UVa 401 Palindromes](https://blog.csdn.net/metaphysis/article/details/161736768)

## 题目描述

$\texttt{Palindromes}$ 题目定义了两类字符串特性：常规回文和镜像串。

- **常规回文（$\texttt{regular palindrome}$）** ：一个字符串正着读和倒着读完全相同。例如 $\texttt{"ABCDEDCBA"}$ 是回文。
- **镜像串（$\texttt{mirrored string}$）** ：将字符串中的每个字符替换为其镜像字符（如果存在），然后反转得到的字符串与原字符串相同。例如 $\texttt{"3AIAE"}$ 是镜像串，因为 $\texttt{'A'}$ 和 $\texttt{'I'}$ 的镜像是自己，$\texttt{'3'}$ 和 $\texttt{'E'}$ 互为镜像。
- **镜像回文（$\texttt{mirrored palindrome}$）** ：同时满足常规回文和镜像串条件。例如 $\texttt{"ATOYOTA"}$ 是镜像回文。

题目给出了所有合法字符及其镜像字符的映射表。注意字符 $\texttt{'0'}$（数字零）与字母 $\texttt{'O'}$ 被视为相同，但输入中只出现字母 $\texttt{'O'}$。

对于每个输入的字符串，需要判断它属于以下四种类型之一：
1. 不是回文也不是镜像串（$\texttt{is not a palindrome.}$）
2. 是常规回文但不是镜像串（$\texttt{is a regular palindrome.}$）
3. 是镜像串但不是回文（$\texttt{is a mirrored string.}$）
4. 是镜像回文（$\texttt{is a mirrored palindrome.}$）

## 输入格式

输入包含多行，每行一个字符串，长度在 $1$ 到 $20$ 之间，由合法字符组成（字母 $\texttt{A} \sim \texttt{Z}$、数字 $\texttt{1} \sim \texttt{9}$，以及字符 $\texttt{'0'}$ 被视为 $\texttt{'O'}$，但输入中只有字母 $\texttt{'O'}$）。输入以文件结束符（$\texttt{EOF}$）终止。

## 输出格式

对于每个输入字符串，输出一行包含原字符串和对应的判断结果，格式如下：

```
STRING -- is not a palindrome.
STRING -- is a regular palindrome.
STRING -- is a mirrored string.
STRING -- is a mirrored palindrome.
```

注意：
- $\texttt{STRING}$ 与 $\texttt{--}$ 之间有两个空格。
- 每个输出行之后必须再输出一个空行。

## 样例

输入

```
NOTAPALINDROME
ISAPALINILAPASI
2A3MEAS
ATOYOTA
```

输出

```
NOTAPALINDROME -- is not a palindrome.

ISAPALINILAPASI -- is a regular palindrome.

2A3MEAS -- is a mirrored string.

ATOYOTA -- is a mirrored palindrome.
```

## 题目分析

本题的核心是判断字符串是否满足回文和镜像两个条件。由于字符串长度不超过 $20$，可以直接使用双指针或反转字符串的方法进行判断，无需复杂优化。

### 回文判断

回文的定义：字符串 $\textit{s}[0 \ldots n-1]$ 满足 $\textit{s}[i] = \textit{s}[n-1-i]$ 对所有 $0 \le i < n/2$ 成立。

判断方法：
- 方法一：将字符串反转后与原字符串比较。
- 方法二：使用双指针从两端向中间扫描比较。

### 镜像判断

镜像的定义：对于每个位置 $i$，字符 $\textit{s}[i]$ 的镜像字符必须等于 $\textit{s}[n-1-i]$。

即满足：
$$
\textit{mirror}(\textit{s}[i]) = \textit{s}[n-1-i] \quad \text{对所有 } 0 \le i < n \text{ 成立}
$$

其中 $\textit{mirror}(c)$ 返回字符 $c$ 的镜像字符。如果 $c$ 没有镜像字符（如字母 $\texttt{B}$、$\texttt{C}$ 等），则该字符串不可能是镜像串。

需要注意的是：
- 镜像映射是**互逆**的，即 $\textit{mirror}(\textit{mirror}(c)) = c$（如果 $c$ 有镜像）。
- 某些字符的镜像是自己，如 $\texttt{'A'}$、$\texttt{'H'}$、$\texttt{'I'}$、$\texttt{'M'}$、$\texttt{'O'}$、$\texttt{'T'}$、$\texttt{'U'}$、$\texttt{'V'}$、$\texttt{'W'}$、$\texttt{'X'}$、$\texttt{'Y'}$、$\texttt{'1'}$、$\texttt{'8'}$。
- 某些字符互为镜像，如 $\texttt{'E'}$ 和 $\texttt{'3'}$，$\texttt{'S'}$ 和 $\texttt{'2'}$，$\texttt{'Z'}$ 和 $\texttt{'5'}$，$\texttt{'J'}$ 和 $\texttt{'L'}$。

### 四种情况的判断逻辑

设 $\textit{isPalindrome}$ 表示是否为回文，$\textit{isMirrored}$ 表示是否为镜像串，则：

| 情况 | $\textit{isPalindrome}$ | $\textit{isMirrored}$ | 输出 |
|------|------------------------|----------------------|------|
| $1$ | $\texttt{false}$ | $\texttt{false}$ | $\texttt{is not a palindrome.}$ |
| $2$ | $\texttt{true}$ | $\texttt{false}$ | $\texttt{is a regular palindrome.}$ |
| $3$ | $\texttt{false}$ | $\texttt{true}$ | $\texttt{is a mirrored string.}$ |
| $4$ | $\texttt{true}$ | $\texttt{true}$ | $\texttt{is a mirrored palindrome.}$ |

## 代码实现

```cpp
// Palindromes
// UVa ID: 401
// Verdict: Accepted
// Submission Date: 2016-07-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<char, char> mirror = {
    {'A', 'A'}, {'E', '3'}, {'3', 'E'}, {'H', 'H'}, {'I', 'I'}, {'J', 'L'},
    {'L', 'J'}, {'M', 'M'}, {'O', 'O'}, {'S', '2'}, {'2', 'S'}, {'T', 'T'},
    {'U', 'U'}, {'V', 'V'}, {'W', 'W'}, {'X', 'X'}, {'Y', 'Y'}, {'Z', '5'},
    {'5', 'Z'}, {'1', '1'}, {'8', '8'}
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        // 去除行首和行尾的空白字符
        int left = 0, right = line.length() - 1;
        while (left < line.length() && isblank(line[left])) left++;
        while (right >= 0 && isblank(line[right])) right--;
        if (left > right) continue;  // 空行跳过
        line = line.substr(left, right - left + 1);
        
        string original = line;
        
        // 判断回文
        reverse(line.begin(), line.end());
        bool is_palindrome = (line == original);
        
        // 判断镜像串
        bool is_mirror_string = true;
        for (int i = 0; i < line.length(); i++)
            if (mirror.find(line[i]) == mirror.end() || mirror[line[i]] != original[i])
            {
                is_mirror_string = false;
                break;
            }
            
        // 输出结果
        cout << original;
        if (is_palindrome && is_mirror_string) 
            cout << " -- is a mirrored palindrome.";
        else if (is_palindrome && !is_mirror_string) 
            cout << " -- is a regular palindrome.";
        else if (!is_palindrome && is_mirror_string) 
            cout << " -- is a mirrored string.";
        else 
            cout << " -- is not a palindrome.";
        cout << endl << endl;
    }
    
    return 0;
}
```