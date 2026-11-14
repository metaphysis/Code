[UVa 373 Romulan Spelling](https://blog.csdn.net/metaphysis/article/details/161642327)

## 题目描述

罗慕兰人使用一种可以用英文字母和标点符号近似的语言。然而，他们的拼写规则比英语更奇怪。特别地，他们有一条规则：

**`G` 在 `P` 之前，除非在 `E` 之后，或者当发音为 `X` 时（如 `npgukbor` 或 `wpguk` 中的情况）。**

操作上，可以通过字符串 `PGUK` 在单词中出现来检测 X 发音。此外，罗慕兰人的大写规则与我们的不同，因此大写字母可以出现在单词的任何位置。

要求：给定包含罗慕兰文本的行，根据上述规则进行拼写校正。

### 输入格式

输入包含多行罗慕兰文本，每行不超过 $70$ 个字符（包括空格）。

### 输出格式

输出校正后的文本。

### 样例输入

```
I rpEpgvpd tKp wgprd tgpEp of tgp from my npgukBor sam wKo gn turn rpEgpvpd tKp wgprd tgpEp of tpg from Kgs ngpukBor Karry,
```

### 样例输出

```
I rpEpgvpd tKp wgprd tgpEp of tgp from my npgukBor sam wKo gn turn rpEgpvpd tKp wgprd tgpEp of tgp from Kgs ngpukBor Karry,
```

---

## 题目分析

### 问题的本质

这是一个**字符串局部交换**问题。需要根据规则检测并交换相邻的 `G` 和 `P`。

### 规则总结

规则说：“`G before P except after E or when pronounced X as in npgukbor or wpguk.`”

翻译为：
- 通常情况下，`G` 应该在 `P` 之前（即 `GP` 是正确的顺序）
- 例外 1：如果 `G` 在 `E` 之后，则应该是 `PG` 顺序
- 例外 2：如果单词中包含 `PGUK` 序列（发音为 X），则应该是 `PG` 顺序

注意：规则中的 `GP` 和 `PG` 是指相邻字符对。

### 大小写处理

罗慕兰语的大小写规则不同，大写字母可以出现在任何位置。因此，比较时应忽略大小写，但交换时应保留原始大小写。

### 操作方式

遍历字符串，当遇到 `G` 且下一个字符是 `P` 时，检查是否应该交换（`GP` → `PG`）：
- 如果 `G` 前面是 `E`（忽略大小写），则不应交换（已经是 `PG`？实际上是 `E G P` 时应为 `E P G`？需要仔细分析）

实际上，规则说的是“G before P except after E”，意思是：
- 正常情况下，正确的顺序是 `GP`
- 如果 `G` 前面是 `E`（即序列 `E G`），则正确顺序应是 `PG`（即 `E P G`）

因此，当遇到 `GP` 时：
- 如果 `G` 前面是 `E`，则需要交换为 `PG`
- 否则保持 `GP`

当遇到 `PG` 时：
- 如果 `G` 前面是 `E`，则保持 `PG`
- 否则应交换为 `GP`

另外，如果单词中包含 `PGUK`，则 `PG` 顺序是正确的。

---

## 参考代码

```cpp
// Romulan Spelling
// UVa ID: 373
// Verdict: Accepted
// Submission Date: 2016-07-31
// UVa Run Time: 0.020s
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
        int length = line.length();
        for (int i = 0; i < length; i++)
        {
            // 处理 G 与后面 P 的关系
            if (tolower(line[i]) == 'g')
            {
                // 检查前面是否是 P（即 PG 的情况）
                if (i > 0 && tolower(line[i - 1]) == 'p')
                {
                    // 检查是否因为 "PGUK" 而不应交换
                    if (i < length - 2 && tolower(line[i + 1]) == 'u' && tolower(line[i + 2]) == 'k')
                        ;  // PGUK 例外，不交换
                    else
                    {
                        // 向左移动 G，直到遇到不是 P 的字符
                        int j = i;
                        do
                        {
                            // 如果前面有 E，则停止（E 后的 PG 是正确的）
                            if (j > 1 && tolower(line[j - 2]) == 'e')
                                break;
                            swap(line[j - 1], line[j]);
                            j--;
                        }
                        while (j > 0 && tolower(line[j - 1]) == 'p');
                    }
                }
            }

            // 处理 P 与后面 G 的关系
            if (tolower(line[i]) == 'g')
            {
                if (i < length - 1 && tolower(line[i + 1]) == 'p')
                {
                    // 如果前面有 E，需要交换为 PG
                    if (i > 0 && tolower(line[i - 1]) == 'e')
                        swap(line[i], line[i + 1]);
                    // 如果后面是 "PGUK" 模式，需要交换为 PG
                    else if (i < length - 3 && tolower(line[i + 2]) == 'u' && tolower(line[i + 3]) == 'k')
                    {
                        swap(line[i], line[i + 1]);
                        // 如果前面还有 G 且前面是 E，继续交换
                        if (i > 1 && tolower(line[i - 1]) == 'g' && tolower(line[i - 2]) == 'e')
                            swap(line[i - 1], line[i]);
                    }
                }
            }
        }
        
        cout << line << '\n';
    }
    return 0;
}
```
