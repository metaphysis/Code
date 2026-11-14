[UVa 338 Long Multiplication](https://blog.csdn.net/metaphysis/article/details/161545124)

## 题目描述

在传统的“长乘法”中，我们通过将 $x$ 与 $y$ 的各个数字（从个位开始）相乘来确定两个整数 $x$ 和 $y$ 的乘积。这些乘法的结果按适当的方式排列并相加，得到最终的乘积。

这种运算的表示通常以特定方式进行。例如，计算 $123 \times 95$：

```
   123
    95
  ---
   615
  1107
  ---
  11685
```

被乘数 $x$ 和乘数 $y$ 各占一行，后面跟一条水平线。然后将 $y$ 的每一位与 $x$ 相乘的结果显示在单独的行上，后面再跟一条水平线，最后是最终乘积。

在本题中，你需要执行一系列这样的乘法，并以这种传统格式显示结果。

### 输入格式

输入数据的每一行（最后一行除外）包含两个整数 $x$ 和 $y$，由空白字符分隔。每个整数不超过 $10$ 位数字。输入数据的最后一行只包含一个 `0`，表示输入结束。

### 输出格式

对于每一对整数（即除最后一行外的每一行），以如上所示的形式输出乘法结果。每个乘法输出后跟一个空行。

如果乘数 $y$ 是一位数（或 $x=0$），则中间结果只有一行，此时省略第二条水平线和中间行，直接输出乘积。

第一条水平线的连字符数量应等于 $\max(|x|, |y|)$ 的位数。第二条水平线的连字符数量（如果产生）应等于乘积的位数。

只输出有效的数字（前导零不显示）。

### 样例输入

```
4 7
135 46
12345 862
0
123456789 0
```

### 样例输出

```
   4
   7
  --
  28

   135
    46
   ---
   810
  540
  ---
  6210

    12345
      862
     -----
     24690
     74070
    98760
    -----
    10641390

        123456789
               0
       ---------
               0
```

---

## 题目分析

### 问题的本质

这是一个**格式化输出**问题。需要按照传统长乘法的竖式格式输出两个整数的乘法过程。

### 长乘法的步骤

1. 输入两个整数 $x$ 和 $y$
2. 如果 $y=0$ 或 $x=0$，直接输出乘积为 $0$
3. 如果 $y$ 只有一位，则直接输出乘积（省略中间行）
4. 否则：
   - 输出 $x$（右对齐）
   - 输出 $y$（右对齐）
   - 输出一条水平线（连字符数量 = $\max(|x|, |y|)$）
   - 对于 $y$ 的每一位（从个位到最高位），计算 $x \times \text{该位}$，并在右侧补相应数量的 $0$，输出（右对齐）
   - 如果有多行中间结果，输出第二条水平线（连字符数量 = 乘积的位数）
   - 输出乘积

### 格式细节

- 所有数字右对齐
- 第一条水平线的长度 = $\max(|x|, |y|)$
- 第二条水平线的长度 = 乘积的位数
- 中间结果中，乘以 $0$ 的项应被省略（不显示）
- 如果中间结果只有一行，则省略第二条水平线

---

## 参考代码

```cpp
// Long Multiplication
// UVa ID: 338
// Verdict: Accepted
// Submission Date: 2016-07-05
// UVa Run Time: 0.090s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 高精度乘法，返回乘积的字符串表示
string multiplication(long long x, long long y)
{
    if (x == 0 || y == 0)
        return "0";

    // 如果两个数都在 9 位以内，直接用 64 位整数计算（安全）
    if (x <= 999999999 && y <= 999999999)
        return to_string(x * y);

    // 否则，模拟竖式乘法
    vector<string> lines;
    for (int rightSpace = 0; y > 0; y /= 10, rightSpace++)
    {
        long long temp = x * (y % 10);           // x 乘以当前位的数字
        string zz = to_string(temp) + string(rightSpace, '0');  // 补零
        reverse(zz.begin(), zz.end());           // 反转以便从低位相加
        lines.push_back(zz);
    }

    // 逐位相加
    string z;
    int carry = 0;
    for (int i = 0; i < lines.back().length(); i++)
    {
        int sum = 0;
        for (int j = 0; j < lines.size(); j++)
            if (i < lines[j].length())
                sum += lines[j][i] - '0';
        sum += carry;
        carry = sum / 10;
        z.push_back(sum % 10 + '0');
    }
    
    // 处理最高位进位
    if (carry > 0)
        z.push_back(carry + '0');
    
    // 反转回正常顺序
    reverse(z.begin(), z.end());
    
    // 去除前导零
    while (z.front() == '0') 
        z.erase(z.begin());

    return z;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    long long x, y;
    string z;

    while (cin >> x >> y)
    {
        if (x == 0 && y == 0) break;  // 输入结束标志
        
        z = multiplication(x, y);     // 计算乘积

        // 确定最大宽度
        int maxXYLength = max(to_string(x).length(), to_string(y).length());
        int maxLength = max((int)(z.length()), maxXYLength);

        // 输出第一行：被乘数
        cout << setw(maxLength) << right << x << endl;
        // 输出第二行：乘数
        cout << setw(maxLength) << right << y << endl;
        // 输出第一条水平线
        cout << setw(maxLength) << right << string(maxXYLength, '-') << endl;
        
        // 如果乘数是一位数或乘数为 0，直接输出乘积
        if (y <= 9 || x == 0)
        {
            cout << setw(maxLength) << right << z << endl;
        }
        else
        {
            // 收集中间结果（排除乘以 0 的项）
            vector<pair<int, string>> lines;
            long long tempY = y;
            for (int rightSpace = 0; tempY > 0; tempY /= 10, rightSpace++)
            {
                long long temp = x * (tempY % 10);
                if (temp == 0) continue;  // 乘以 0 的项不显示
                lines.push_back(make_pair(rightSpace, to_string(temp)));
            }

            // 如果有多行中间结果，输出它们
            if (lines.size() > 1)
            {
                for (auto line : lines)
                    cout << setw(maxLength - line.first) << right << line.second << endl;
                // 输出第二条水平线
                cout << setw(maxLength) << right << string(z.length(), '-') << endl;
            }
            // 输出乘积
            cout << z << endl;
        }
        cout << endl;  // 每个测试用例后空行
    }

    return 0;
}
```
