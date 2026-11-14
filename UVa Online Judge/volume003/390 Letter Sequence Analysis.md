[UVa 390 Letter Sequence Analysis](https://blog.csdn.net/metaphysis/article/details/161705415)

## 题目描述

密码分析广泛利用语言中字母和字母序列出现的频率。例如，如果已知加密文本是英文，那么了解 `E`、`L`、`N`、`R`、`S`、`T` 是最常用的字母这一事实可以得到很多信息。如果知道常见的字母对、三字母组等，则可以获得更多信息。

对于本题，你需要编写一个程序，接受一个长度不确定的文本文件作为输入，并对文本进行字母序列分析。程序应报告长度为 $1$ 到 $5$ 的每个序列集合中出现频率最高的五个序列。即：
- 单个字符中出现频率最高的五个字符
- 字符对中出现频率最高的五个字符对
- 以此类推，直到五字符序列

程序只考虑连续的字母序列，忽略大小写（即 `a` 和 `A` 视为相同）。输出格式如示例所示。对于每个序列长度，按频率降序列出序列。如果有多个序列频率相同，则按字母顺序列出（全部大写）。如果某个长度的不同频率少于五个，则只列出尽可能多的不同频率列表。

### 输入格式

输入是一个文本文件，长度不限。

### 输出格式

对于每个序列长度（$1$ 到 $5$），输出分析结果。每个长度之间用空行分隔。

### 样例输入

```
Peter Piper Picks Pickles!
```

### 样例输出

```
Analysis for Letter Sequences of Length 1
-----------------------------------------
Frequency = 5, Sequence(s) = (P)
Frequency = 4, Sequence(s) = (E)
Frequency = 3, Sequence(s) = (I)
Frequency = 2, Sequence(s) = (C,K,R,S)
Frequency = 1, Sequence(s) = (L,T)

Analysis for Letter Sequences of Length 2
-----------------------------------------
Frequency = 3, Sequence(s) = (PI)
Frequency = 2, Sequence(s) = (CK,ER,IC,PE)
Frequency = 1, Sequence(s) = (ES,ET,IP,KL,KS,LE,TE)

Analysis for Letter Sequences of Length 3
-----------------------------------------
Frequency = 2, Sequence(s) = (ICK,PIC)
Frequency = 1, Sequence(s) = (CKL,CKS,ETE,IPE,KLE,LES,PER,PET,PIP,TER)

Analysis for Letter Sequences of Length 4
-----------------------------------------
Frequency = 2, Sequence(s) = (PICK)
Frequency = 1, Sequence(s) = (CKLE,ETER,ICKL,ICKS,IPER,KLES,PETE,PIPE)

Analysis for Letter Sequences of Length 5
-----------------------------------------
Frequency = 1, Sequence(s) = (CKLES,ICKLE,PETER,PICKL,PICKS,PIPER)
```

---

## 题目分析

### 问题的本质

这是一个**子串频率统计**问题。需要统计文本中所有长度 $1$ 到 $5$ 的连续字母子串的出现频率，并按频率和字母顺序排序输出前五个不同的频率值。

### 关键点

- 只考虑字母字符（`A`~`Z`，忽略大小写）
- 非字母字符（如空格、标点）分隔字母序列
- 统计所有连续字母子串（不仅仅是单词内的，但非字母会打断连续性）
- 输出格式：每个长度一组，按频率降序，同频率按字母升序
- 只输出频率最高的五个不同频率值（每个频率可能对应多个序列）

---
## 参考代码

```cpp
// Letter Sequence Analysis
// UVa ID: 390
// Verdict: Accepted
// Submission Date: 2016-07-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct record
{
    int frequency;
    string letters;
    bool operator<(const record &another) const
    {
        if (frequency != another.frequency)
            return frequency > another.frequency;
        else
            return letters < another.letters;
    }
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    string line;
    char element;
    
    // 读取整个输入，只保留字母并转换为大写
    cin.unsetf(ios::skipws);
    while (cin >> element)
        if (isalpha(element))
            line += toupper(element);
    
    // 统计所有长度 1-5 的连续字母子串的频率
    map<int, map<string, int>> frequencies;
    
    for (int i = 0; i < line.length(); i++)
    {
        int length = 1;
        while (length <= 5 && (i + length - 1) < line.length())
        {
            string block = line.substr(i, length);
            frequencies[length][block]++;
            length++;
        }
    }

    // 输出结果
    for (int len = 1; len <= 5; len++)
    {
        if (len > 1) cout << endl;
        cout << "Analysis for Letter Sequences of Length " << len << endl;
        cout << "-----------------------------------------" << endl;
        
        // 转换为 vector 并排序
        vector<record> records;
        for (auto& item : frequencies[len])
            records.push_back({item.second, item.first});
        sort(records.begin(), records.end());
        
        // 输出前五个不同频率
        int lastFrequency = -1, outputed = 0;
        for (int j = 0; j < records.size(); j++)
        {
            if (records[j].frequency == lastFrequency)
            {
                cout << "," << records[j].letters;
            }
            else
            {
                if (outputed >= 1) cout << ")" << endl;
                if (++outputed > 5) break;
                lastFrequency = records[j].frequency;
                cout << "Frequency = " << records[j].frequency;
                cout << ", Sequence(s) = (" << records[j].letters;
            }
        }
        if (outputed > 0 && outputed <= 5) 
            cout << ")" << endl;
    }
    
    return 0;
}
```
