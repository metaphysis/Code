[UVa 290 Palindromes smordnilaP](https://blog.csdn.net/metaphysis/article/details/161386099)

## 题目描述

本题涉及由数字构成的回文数。如果一个数字从左向右读和从右向左读的序列完全相同，则称该数字为回文数。  

给定一个十进制数字 $65$，将其与它的反转数 $56$ 相加，得到 $121$，这是一个回文数。对于其他数字，可能需要重复这个步骤，直到和变成回文形式。例如数字 $87$ 的过程如下：

$$
87 \to 165 \to 726 \to 1353 \to 4884
$$

步数为 $4$。  

这个过程适用于任意进制下的任意数字。当然，步数增长非常快，因此十进制中存在需要超过 $10000$ 步的数字。题目要求：给定一个合法的 $15$ 进制数字，计算它在 **$15$ 进制到 $2$ 进制** 中每个进制下的步数。如果一个数字在某个进制下不合法（即存在某一位的值大于等于进制基数），则该进制的步数用 `?` 表示。

**输入**：若干行，每行是一个合法的 $15$ 进制整数。  

**输出**：对于每行输入，输出一行，包含 $14$ 个结果（基数从 $15$ 到 $2$ 的步数），用空格分隔。题目保证步数不超过 $100$。

**示例**：  

输入：
```
87
ED
```

输出：
```
2 2 2 2 2 4 6 ? ? ? ? ? ? ?
? ? ? ? ? ? ? ? ? ? ? ? ? ?
```

## 题目分析

本题的核心是**进制转换**与**回文模拟**。

### 1. 输入的特殊性

输入的数字是 $15$ 进制数。$15$ 进制使用的数码为 $0$–$9$ 和 $A$–$E$（其中 $A=10$，$B=11$，$C=12$，$D=13$，$E=14$）。因此，输入字符串中的每个字符都需要转换为对应的数值。

### 2. 合法性的判断

对于给定的基数 $b$（$2 \le b \le 15$），输入数字的每一位数值必须小于 $b$，否则在该基数下该数字是**非法**的，直接输出 `?`。例如，输入数字包含数码 $E=14$，则所有 $b \le 14$ 的进制下该数字均非法。

因此，首先需要找出输入数字中出现的最大数码值 $\texttt{maxDigit}$。对于所有 $b > \texttt{maxDigit}$，数字合法；对于 $b \le \texttt{maxDigit}$，数字非法。

### 3. 回文步数模拟

对于合法的进制 $b$，需要模拟“将数字与其反转数相加”的过程，直到得到回文数，并统计步数。模拟过程如下：

- 将当前数字表示为一个向量（从低位到高位或从高位到低位均可，但需保持一致）。
- 反转该向量得到反转数。
- 按照基数 $b$ 进行逐位相加并进位，得到新数字。
- 检查新数字是否为回文（即向量正反相同）。
- 重复上述步骤，直到回文出现，步数即为迭代次数。

需要注意的是，如果输入数字本身已经是回文数，则步数为 $0$。

### 4. 步数上限

题目明确说明步数不会超过 $100$，因此不需要处理无限循环或超大步数的情况。

## 解题思路

根据上述分析，解题步骤可以归纳为：

1. **读入**一行字符串，去除可能的空白字符。
2. **转换**：将字符串中的每个字符转换为数值，存入整数向量 $\texttt{digits}$ 中。
3. **计算最大值**：遍历 $\texttt{digits}$，找到最大数值 $\texttt{maxDigit}$。
4. **循环处理每个基数** $b$ 从 $15$ 到 $2$：
   - 如果 $b \le \texttt{maxDigit}$，则该基数下数字非法，输出 `?`。
   - 否则，进行回文步数模拟：
     - 用 $\texttt{digits}$ 初始化当前数字向量 $\texttt{current}$。
     - 设置步数 $\texttt{steps} = 0$。
     - 循环：
       - 如果 $\texttt{current}$ 是回文，输出 $\texttt{steps}$ 并跳出循环。
       - 否则，反转 $\texttt{current}$ 得到 $\texttt{rev}$。
       - 逐位相加并进位，结果存回 $\texttt{current}$。
       - $\texttt{steps} \leftarrow \texttt{steps} + 1$。
5. 每输出一个结果后，若当前基数不是 $2$，则输出一个空格分隔。
6. 输出换行，继续处理下一行输入。

## 复杂度分析

对于每个合法的进制 $b$，模拟过程的步数不超过 $100$，每次加法操作与数字长度相关。数字长度随着加法可能会增长，但增长缓慢。总体复杂度在题目限制下完全可行。

## 代码实现

```cpp
// Palindroms smordnilaP
// UVa ID: 290
// Verdict: Accepted
// Submission Date: 2016-05-14
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    
    while (getline(cin, line))
    {
        // 备份原始输入字符串，用于判断原数是否为回文
        string backup = line;
        reverse(line.begin(), line.end());

        // 将反转后的字符串转换为数字向量（每一位的数值）
        vector<int> digits;
        for (int i = 0; i < line.length(); i++)
        {
            if (isdigit(line[i]))
                digits.push_back(line[i] - '0');
            else
                digits.push_back(tolower(line[i]) - 'a' + 10);
        }
        
        // 找出数字中的最大数码值
        int maxDigit = 0;
        for (int i = 0; i < digits.size(); i++)
            maxDigit = max(maxDigit, digits[i]);
                        
        // 特殊情况：原始输入本身是回文数
        if (backup == line)
        {
            // 输出步数 0
            cout << "0";
            
            // 对于所有合法进制（b > maxDigit），步数为 0
            for (int i = 14; i >= max(2, (maxDigit + 1)); i--)
                cout << " 0";
        
            // 对于非法进制，输出 ?
            for (int i = max(2, (maxDigit + 1)) - 1; i >= 2; i--)
                cout << " ?";
            
            cout << endl;
                
            continue;
        }

        bool first = true;
        
        // 处理所有合法进制：从 15 到 maxDigit+1
        for (int i = 15; i >= (maxDigit + 1); i--)
        {
            vector<int> origin(digits);
            
            int step = 0;
            while (true)
            {
                // 反转当前数字
                vector<int> reversed(origin);
                reverse(reversed.begin(), reversed.end());
                
                // 按基数 i 进行逐位相加并进位
                int carry = 0;
                for (int j = 0; j < origin.size(); j++)
                {
                    carry += origin[j] + reversed[j];
                    origin[j] = carry % i;
                    carry /= i;
                }
                
                // 若最终有进位，则增加一位
                if (carry)
                    origin.push_back(carry);
                    
                step++;
                
                // 检查是否为回文
                bool isPalindrome = true;
                for (int m = 0, n = origin.size() - 1; m < n; m++, n--)
                    if (origin[m] != origin[n])
                    {
                        isPalindrome = false;
                        break;
                    }
                    
                if (isPalindrome)
                {
                    if (first)
                        first = false;
                    else
                        cout << " ";
                        
                    cout << step;
                    break;
                }
            }
        }
        
        // 处理非法进制：所有 b <= maxDigit 输出 ?
        for (int i = maxDigit; i >= 2; i--)
            cout << " ?";
        
        cout << endl;
    }
    
	return 0;
}
```

## 总结

本题的关键在于理解“给定数字是 $15$ 进制数”以及“合法性判断依赖于进制基数与数字中最大数码的比较”。模拟回文转换时，需要注意进位的处理以及回文判断的时机。题目保证步数不超过 $100$，使得模拟过程简单可控。  

此外，本题的输入只有一行一个数字，但可能存在多行输入，因此需要循环读取直到文件结束。
