[UVa 385 DNA Translation](https://blog.csdn.net/metaphysis/article/details/161673631)

## 题目描述

脱氧核糖核酸（$\texttt{DNA}$）由核苷酸碱基对组成，形成双螺旋结构。通过一系列复杂的生化过程，生物体 $\texttt{DNA}$ 中的核苷酸序列被翻译成其生命所需的蛋白质。本题的目标是编写一个计算机程序，接受一个 $\texttt{DNA}$ 链并报告由其产生的蛋白质（如果有的话）。

### 背景知识

- 核苷酸碱基：腺嘌呤（$\texttt{A}$）、胞嘧啶（$\texttt{C}$）、鸟嘌呤（$\texttt{G}$）、胸腺嘧啶（$\texttt{T}$）
- 互补配对：$\texttt{A} \leftrightarrow \texttt{T}$，$\texttt{C} \leftrightarrow \texttt{G}$
- $\texttt{DNA}$ 链通常只列出主链，互补链可通过替换互补碱基得到
- **转录**：从 $\texttt{DNA}$ 主链产生信使 $\texttt{RNA}$（$\texttt{mRNA}$），$\texttt{mRNA}$ 与互补链相同，但胸腺嘧啶（$\texttt{T}$）被尿嘧啶（$\texttt{U}$）取代
- **翻译**：$\texttt{mRNA}$ 中的碱基序列被分为三个一组（密码子），$\texttt{AUG}$ 标记蛋白质序列的开始，$\texttt{UAA}$、$\texttt{UAG}$、$\texttt{UGA}$ 标记结束

### 输入与输出

输入包含多行 $\texttt{DNA}$ 序列，每行一个，以 `*` 结束。每个给定的 $\texttt{DNA}$ 链可能是主链或互补链，可能是正向或反向顺序。起始和终止密码子不一定出现在链的末端。

对于每个输入，输出翻译得到的蛋白质（氨基酸缩写用连字符连接）。如果无法翻译出有效蛋白质，输出 `*** No translatable DNA found ***`。

### 样例输入

```
ATACTGTAATTCACTCC
CACCTGTACACAGAGGAATACTG
TTAATACGACATAATTAT
GCCTTGATATGGAGAACTCATTAGATA
AAGTGTATGTGAATTATATAAAACGGGCATGA
ATGATGATGGCCTGA
*
```

### 样例输出

```
Ser-Ile-Lys
Cys-Leu-His
Ser-Tyr
*** No translatable DNA found ***
Leu-Asn-Tyr-Ile-Lys-Arg-Ala
Met-Met-Ala
```

---

## 题目分析

### 问题的本质

这是一个**生物信息学中的 $\texttt{DNA}$ 翻译**问题。需要：
1. 考虑 $\texttt{DNA}$ 链的四种可能形式：主链正向、主链反向、互补链正向、互补链反向
2. 将 $\texttt{DNA}$ 转录为 $\texttt{mRNA}$（`T` → `U`）
3. 在 $\texttt{mRNA}$ 中寻找起始密码子 `AUG`
4. 从起始密码子后开始读取密码子，直到遇到终止密码子
5. 将密码子翻译为氨基酸缩写

### 四种链形式

对于给定的 $\texttt{DNA}$ 链 `S`，需要考虑：
- `S`（主链正向）
- `reverse(S)`（主链反向）
- `complement(S)`（互补链正向）
- `reverse(complement(S))`（互补链反向）

### 翻译过程

1. 将 $\texttt{DNA}$ 中的 `T` 替换为 `U` 得到 $\texttt{mRNA}$
2. 在 $\texttt{mRNA}$ 中查找 `AUG`
3. 从 `AUG` 后的位置开始，每次读取 3 个碱基
4. 如果遇到终止密码子（`UAA`、`UAG`、`UGA`），停止
5. 否则，将密码子翻译为氨基酸缩写

### 密码子表

使用 `map<string, string>` 存储密码子到氨基酸缩写的映射。

---

## 参考代码

```cpp
// DNS Translation
// UVa ID: 385
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// DNA 碱基互补映射
map<char, char> DNA = {{'A', 'T'}, {'T', 'A'}, {'C', 'G'}, {'G', 'C'}};

// 密码子到氨基酸缩写的映射
map<string, string> code = {
    {"UUU", "Phe"}, {"UCU", "Ser"}, {"UAU", "Tyr"}, {"UGU", "Cys"},
    {"UUC", "Phe"}, {"UCC", "Ser"}, {"UAC", "Tyr"}, {"UGC", "Cys"},
    {"UUA", "Leu"}, {"UCA", "Ser"},
    {"UUG", "Leu"}, {"UCG", "Ser"}, {"UGG", "Trp"},
    
    {"CUU", "Leu"}, {"CCU", "Pro"}, {"CAU", "His"}, {"CGU", "Arg"},
    {"CUC", "Leu"}, {"CCC", "Pro"}, {"CAC", "His"}, {"CGC", "Arg"},
    {"CUA", "Leu"}, {"CCA", "Pro"}, {"CAA", "Gln"}, {"CGA", "Arg"},
    {"CUG", "Leu"}, {"CCG", "Pro"}, {"CAG", "Gln"}, {"CGG", "Arg"},
    
    {"AUU", "Ile"}, {"ACU", "Thr"}, {"AAU", "Asn"}, {"AGU", "Ser"},
    {"AUC", "Ile"}, {"ACC", "Thr"}, {"AAC", "Asn"}, {"AGC", "Ser"},
    {"AUA", "Ile"}, {"ACA", "Thr"}, {"AAA", "Lys"}, {"AGA", "Arg"},
    {"AUG", "Met"}, {"ACG", "Thr"}, {"AAG", "Lys"}, {"AGG", "Arg"},
    
    {"GUU", "Val"}, {"GCU", "Ala"}, {"GAU", "Asp"}, {"GGU", "Gly"},
    {"GUC", "Val"}, {"GCC", "Ala"}, {"GAC", "Asp"}, {"GGC", "Gly"},
    {"GUA", "Val"}, {"GCA", "Ala"}, {"GAA", "Glu"}, {"GGA", "Gly"},
    {"GUG", "Val"}, {"GCG", "Ala"}, {"GAG", "Glu"}, {"GGG", "Gly"},
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string line;
    while (getline(cin, line), line != "*")
    {
        // 生成四种可能的 mRNA 序列
        vector<string> mRNA;
        mRNA.push_back(line);                     // 主链正向
        string rev = line;
        reverse(rev.begin(), rev.end());
        mRNA.push_back(rev);                      // 主链反向

        string comp;
        for (char c : line) 
            comp += DNA[c];
        mRNA.push_back(comp);                     // 互补链正向
        reverse(comp.begin(), comp.end());
        mRNA.push_back(comp);                     // 互补链反向

        // 将 DNA 转换为 mRNA（T → U）
        for (string& s : mRNA)
            for (char& c : s)
                if (c == 'T') c = 'U';

        bool proteinProduced = false;
        // 尝试每种 mRNA 序列
        for (int i = 0; i < mRNA.size(); i++)
        {
            string message = mRNA[i];
            size_t start = message.find("AUG");
            if (start == string::npos) continue;
            start += 3;  // 跳过起始密码子
            
            vector<string> proteins;
            bool ended = false;
            // 读取后续密码子直到遇到终止密码子
            while (start + 2 < message.length())
            {
                string block = message.substr(start, 3);
                if (block == "UAA" || block == "UAG" || block == "UGA")
                {
                    ended = true;
                    break;
                }
                if (code.find(block) != code.end())
                    proteins.push_back(code[block]);
                start += 3;
            }

            if (ended && !proteins.empty())
            {
                proteinProduced = true;
                for (size_t i = 0; i < proteins.size(); i++)
                {
                    if (i > 0) cout << "-";
                    cout << proteins[i];
                }
                cout << endl;
                break;
            }
        }

        if (!proteinProduced)
            cout << "*** No translatable DNA found ***" << endl;
    }
    
    return 0;
}
```
