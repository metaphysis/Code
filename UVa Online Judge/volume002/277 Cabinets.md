[UVa 277 Cabinets](https://blog.csdn.net/metaphysis/article/details/161333665)

## 题目分析

本题要求编写一个程序，将制造商 $\texttt{Woodcraft}$ 提供的橱柜电子目录数据，重新格式化为符合 $\texttt{Well‑Built Cabinet Distributors, Inc.}$ 库存软件要求的格式。

输入是一个逗号分隔的 `ASCII` 文件，每条记录包含 $5$ 个字段：$\texttt{Style Code}$（风格代码，$1$‑$3$ 位）、$\texttt{Style Name}$（风格名称，$0$‑$15$ 位）、$\texttt{Description}$（描述，$1$‑$15$ 位）、$\texttt{Extension}$（扩展信息，$0$‑$25$ 位）、$\texttt{Unit Price}$（单价，美元 $\times 100$，$0$‑$6$ 位）。记录按 $\texttt{Style Code}$ 升序排列。

输出同样是一个逗号分隔的 `ASCII` 文件。第一行为表头：`Item Id, Item Desc, Item Price`。随后每条输出记录包含三个字段：$\texttt{Item Id}$（$4$‑$13$ 位）、$\texttt{Item Desc}$（$1$‑$30$ 位）、$\texttt{Item Price}$（$4$‑$7$ 位，格式为 `xx.xx`）。输出记录按输入顺序生成，每条输入记录对应一条输出记录，但某些输入记录可能被拒绝（不输出）。

## 解题思路

### 第一步：处理输入中的缺失字段

题目给出的输入是逗号分隔格式，但某些字段可能为空（例如 $\texttt{Style Name}$ 或 $\texttt{Extension}$ 可以为空）。在标准的逗号分隔格式中，空字段仍然需要用逗号占位，但本题的输入样例中，空字段有时会被省略（连续两个逗号之间没有内容），导致每行的逗号数量不足 $5$ 个。

**处理方式**：读取一行后，统计该行中逗号的个数。如果逗号数量少于 $5$，则在行末尾补足逗号，使字段总数达到 $5$ 个。这样后续用逗号分割时，每个字段（包括空字段）都能被正确提取。

### 第二步：按 $\texttt{Style Code}$ 分组记录第一条的 $\texttt{Style Name}$

题目规定：若某条记录的 $\texttt{Style Name}$ 缺失，则使用同一 $\texttt{Style Code}$ 组中第一条记录的 $\texttt{Style Name}$。如果第一条记录也没有 $\texttt{Style Name}$，则拒绝该记录。

**实现方式**：维护一个字典（哈希映射）$\texttt{codeAndName}$，键为 $\texttt{Style Code}$，值为该组第一条记录的 $\texttt{Style Name}$。对于当前处理的记录：

- 若当前 $\texttt{Style Code}$ 不在字典中，则将其 $\texttt{Style Name}$（可能为空字符串）存入字典。
- 后续遇到相同 $\texttt{Style Code}$ 的记录时，若自身的 $\texttt{Style Name}$ 为空，则从字典中取出该组的 $\texttt{Style Name}$ 作为备用。

### 第三步：生成 $\texttt{Item Id}$

$\texttt{Item Id}$ 由 $\texttt{Style Code}$ 和 $\texttt{Description}$ 直接拼接而成。

- 若 $\texttt{Style Code}$ 长度不足 $3$ 个字符，则在左侧用字符 $\texttt{'0'}$ 填充至 $3$ 位。
- 拼接后若总长度超过 $13$ 个字符，则**拒绝**该记录。代码中通过限制 $\texttt{Description}$ 长度不超过 $10$ 来间接保证 $\texttt{Item Id}$ 长度不超过 $13$（因为 $\texttt{Style Code}$ 最多 $3$ 位，$\texttt{Description}$ 最多 $15$ 位，但此处采用了更严格的条件——实际应检查拼接后长度，若超过则跳过）。

### 第四步：生成 $\texttt{Item Desc}$

$\texttt{Item Desc}$ 由 $\texttt{Style Name}$、一个连字符 `-` 和 $\texttt{Extension}$ 拼接而成。

- 若当前记录的 $\texttt{Style Name}$ 为空，则使用同 $\texttt{Style Code}$ 组的第一条记录的 $\texttt{Style Name}$（从字典中获取）。若该备用名也为空，则拒绝该记录。
- 若 $\texttt{Extension}$ 非空，则拼接 `-` 和 $\texttt{Extension}$；若 $\texttt{Extension}$ 为空，则 $\texttt{Item Desc}$ 直接等于 $\texttt{Style Name}$（不加连字符）。
- 若拼接后的长度超过 $30$ 个字符，则从右侧截断至 $30$ 个字符。

### 第五步：生成 $\texttt{Item Price}$

输入中的 $\texttt{Unit Price}$ 单位为“美元 $\times 100$”，即整数形式，例如 $8900$ 表示 $\$89.00$。输出时需要转换为带两位小数的格式 `xx.xx`。

- 若价格字段为空，则输出默认值 `0.00`。
- 否则将字符串转换为整数，除以 $100$ 得到整数部分，取模 $100$ 得到小数部分。
- 格式化时，若小数部分不足 $2$ 位，则在左侧补 `0`。

### 第六步：处理被拒绝的记录

被拒绝的记录不输出任何内容，直接跳过。代码中通过以下方式实现拒绝：

- 若 $\texttt{Description}$ 长度超过 $10$（隐含 $\texttt{Item Id}$ 长度可能超过 $13$），则跳过。
- 若当前记录的 $\texttt{Style Name}$ 为空且同组第一条的 $\texttt{Style Name}$ 也为空，则跳过。

### 第七步：输入与输出格式控制

- 输入第一行为测试用例个数 $cases$，随后有一个空行。每两个测试用例之间也有一个空行。
- 对于每个测试用例，首先输出表头行 `Item Id,Item Desc,Item Price`。
- 然后循环读取非空行，每行处理一条记录，直到遇到空行（表示当前测试用例结束）。
- 两个测试用例的输出之间插入一个空行。

## 代码实现

```cpp
// Cabinets
// UVa ID: 277
// Verdict: Accepted
// Submission Date: 2016-05-26
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    getline(cin, line);                     // 读取测试用例个数
    int cases = stoi(line);                 // 转换为整数

    getline(cin, line);                     // 读取第一个测试用例之前的空行
    while (cases--)
    {
        // 输出表头
        cout << "Item Id,Item Desc,Item Price" << endl;

        // 存储每个 Style Code 组的第一条记录的 Style Name
        map<string, string> codeAndName;

        // 循环读取当前测试用例的每一条记录，直到遇到空行
        while (getline(cin, line), line.length() > 0)
        {
            // 统计当前行的逗号数量，若不足 5 个，则补足到 5 个
            int comma = count(line.begin(), line.end(), ',');
            while (comma < 5)
            {
                line.push_back(',');        // 在行尾补逗号
                comma++;
            }

            // 用逗号分割当前行，提取 5 个字段
            vector<string> item;
            istringstream iss(line);
            for (string block; getline(iss, block, ','); )
                item.push_back(block);

            // 为方便阅读，将 5 个字段分别命名
            string code = item[0], name = item[1], description = item[2];
            string extension = item[3], price = item[4];

            // 如果当前 Style Code 是第一次出现，将其 Style Name 存入字典
            if (codeAndName.count(code) == 0)
                codeAndName.insert(make_pair(code, name));

            // 如果 Description 长度超过 10，则 Item Id 可能超过 13 位，拒绝该记录
            if (description.length() > 10)
                continue;

            // 生成 Item Id：Style Code 左补零至 3 位，再拼接 Description
            string itemId = code;
            while (itemId.length() < 3)
                itemId.insert(itemId.begin(), '0');
            itemId += description;

            // 生成 Item Desc：优先使用当前记录的 Style Name
            string itemDesc = name;
            if (itemDesc.length() == 0)
            {
                // 若当前记录没有 Style Name，则使用同组第一条记录的 Style Name
                if (codeAndName[code].length() == 0)
                    continue;               // 若第一条也没有，则拒绝该记录
                else
                    itemDesc = codeAndName[code];
            }

            // 如果 Extension 非空，则拼接连字符和 Extension
            if (extension.length())
            {
                itemDesc += '-' + extension;
                // 如果超出 30 字符，则从右侧截断
                if (itemDesc.length() > 30)
                    itemDesc.erase(itemDesc.begin() + 30, itemDesc.end());
            }

            // 生成 Item Price：将整数（美元×100）转换为带两位小数的字符串
            string itemPrice = "0.00";
            if (price.length())
            {
                int cent = stoi(price);     // 将价格字符串转为整数（单位：美分）
                itemPrice = to_string(cent / 100);  // 整数部分（美元）
                cent %= 100;                // 剩余美分（0-99）
                itemPrice += '.';
                if (cent < 10)              // 美分不足两位时补零
                    itemPrice += '0';
                itemPrice += to_string(cent);
            }

            // 输出格式化后的记录
            cout << itemId << "," << itemDesc << "," << itemPrice << endl;
        }

        // 两个测试用例的输出之间插入一个空行
        if (cases)
            cout << endl;
    }

    return 0;
}
```
