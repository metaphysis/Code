[UVa 400 Unix ls](https://blog.csdn.net/metaphysis/article/details/161736747)

## 题目描述

$\texttt{Unix ls}$ 命令需要将一组文件名按 ASCII 字符顺序排序，并格式化成多列输出。每列宽度由最长文件名决定：最后一列的宽度等于最长文件名的长度，其他列的宽度等于最长文件名长度加 $2$。总输出宽度固定为 $60$ 个字符，且列数应尽可能多，行数应尽可能少，填充时按从左到右、从上到下的顺序排列。

你的任务是实现一个程序，对每组文件名进行排序和格式化，并在每组输出前打印一行 $60$ 个短横线 `-`。

## 输入格式

输入包含若干组文件名列表。每组第一行是一个整数 $N$（$1 \le N \le 100$），表示该组有 $N$ 个文件名。接下来 $N$ 行，每行一个文件名，长度在 $1$ 到 $60$ 字符之间，由字母、数字、点（`.`）、短横（`-`）和下划线（`_`）组成。每组数据之间没有空行，输入以文件结束符（$\texttt{EOF}$）终止。

## 输出格式

对于每组文件名，首先输出一行恰好 $60$ 个短横线 `-`，然后按格式化要求输出文件名。输出时，文件名按 ASCII 升序排列，从上到下、从左到右填充。最后一列的宽度等于最长文件名的长度，其余列宽度等于最长文件名长度加 $2$。列数 $C$ 应尽量多（在总宽度不超过 $60$ 的前提下），行数 $R$ 应尽量少（$R = \lceil N / C \rceil$）。

## 样例

输入

```cpp
10
tiny
2short4me
very_long_file_name
shorter
size-1
size2
size3
much_longer_name
12345678.123
mid_size_name
12
Weaser
Alfalfa
Stimey
Buckwheat
Porky
Joe
Darla
Cotton
Butch
Froggy
Mrs_Crabapple
P.D.
19
Mr._French
Jody
Buffy
Sissy
Keith
Danny
Lori
Chris
Shirley
Marsha
Jan
Cindy
Carol
Mike
Greg
Peter
Bobby
Alice
Ruben
```

输出

```cpp
------------------------------------------------------------
12345678.123         size-1             
2short4me            size2              
mid_size_name        size3              
much_longer_name     tiny               
shorter              very_long_file_name
------------------------------------------------------------
Alfalfa        Cotton         Joe            Porky        
Buckwheat      Darla          Mrs_Crabapple  Stimey       
Butch          Froggy         P.D.           Weaser       
------------------------------------------------------------
Alice       Chris       Jan         Marsha      Ruben     
Bobby       Cindy       Jody        Mike        Shirley   
Buffy       Danny       Keith       Mr._French  Sissy     
Carol       Greg        Lori        Peter     
```

## 题目分析

本题的核心任务是将一组字符串按指定格式输出，涉及三个关键步骤：

1. **排序**：按 $\texttt{ASCII}$ 值升序排列，这与常规字符串字典序一致。
2. **计算列数和行数**：给定最长文件名长度 $\textit{maxLen}$，其他列宽度为 $\textit{maxLen} + 2$，最后一列宽度为 $\textit{maxLen}$。总宽度为 $60$，需要求解最大列数 $C$，满足：
   
   $$
   (\textit{maxLen} + 2) \times (C - 1) + \textit{maxLen} \le 60
   $$
   
   化简得：
   
   $$
   C = 1 + \left\lfloor \frac{60 - \textit{maxLen}}{\textit{maxLen} + 2} \right\rfloor
   $$
   
   行数 $R = \lceil N / C \rceil$。

3. **按列输出**：输出顺序是 **先从上到下填满第一列，再填第二列**。因此，第 $i$ 行（$0$ 索引）第 $j$ 列（$0$ 索引）对应的文件索引为：
   
   $$
   \textit{index} = j \times R + i
   $$
   
   需判断 $\textit{index} < N$ 以避免越界。最后一列（$j = C - 1$）的宽度为 $\textit{maxLen}$，其余列宽度为 $\textit{maxLen} + 2$。

## 代码实现

```cpp
// Unix ls
// UVa ID: 400
// Verdict: Accepted
// Submission Date: 2016-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        int n = stoi(line);
        
        vector<string> filenames;
        int max_length = 0;
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            string filename;
            for (int i = 0; i < line.length() && filename.length() < 60; i++)
            {
                if (isdigit(line[i]) || isalpha(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == '_')
                    filename += line[i];
            }
            if (filename.length() == 0) continue;
            max_length = max(max_length, (int)filename.length());
            filenames.push_back(filename);
        }
        
        sort(filenames.begin(), filenames.end());
        
        n = filenames.size();
        int C = 1 + (60 - max_length) / (max_length + 2);
        int R = n / C + (n % C == 0 ? 0 : 1);
        
        cout << string(60, '-') << '\n';
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                int index = j * R + i;
                if (index < n)
                    cout << setw(max_length + ((j + 1) * R + i < n ? 2 : 0)) << left << filenames[index];
            }
            cout << '\n';
        }
    }
    
	return 0;
}
```