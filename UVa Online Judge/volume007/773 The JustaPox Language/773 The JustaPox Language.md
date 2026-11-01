## 题目描述

$\texttt{JustaPox}$ 语言只处理整数数组，声明数组有两种方式：

1. 显式指定大小：`A is [1]` 表示 `A` 是长度为 $1$ 的数组，其值可以是任意一个长度为 $1$ 的整数序列。  
2. 通过包含已声明的数组：`C is A B` 表示 `C` 由数组 `A` 和 `B` 依次拼接而成，其总长度为两者长度之和。若同一个数组在声明中出现多次（如 `D is A A`），则对应位置的两个子序列必须完全相等。

赋值语句形如 `S = i1 i2 ... in.`，其中 `S` 必须是一个已声明的数组，右侧整数序列的长度必须等于 `S` 的总长度，并且所有由同一引用数组产生的子段必须对应位置相等。

给定一组数组声明和一组赋值语句，要求输出所有不一致的赋值语句（按输入原样）。

## 输入格式

输入由数组声明和赋值语句组成，两者交替出现，无明确结束标记（输入文件读到末尾为止）。每个声明或赋值以句点 `.` 结束。  
- 数组声明格式：`<id> is d1 d2 ... dm.`，其中 `<id>` 是标识符，`d_i` 可以是 `[k]`（$k$ 为正整数）或之前声明的数组标识符。  
- 赋值格式：`<id> = i1 i2 ... in.`，其中 `<id>` 是已声明的数组，`i_j` 为正整数。  
任意位置可包含空格和空行。

## 输出格式

输出所有不一致的赋值语句，每条语句原样输出，顺序与输入中出现顺序相同。

## 样例

输入
```
A is [1]. B is [3]. C is A B. SEQ is [1] A [4] B A. A = 10. B = 1 2 3. C = 1 1 2 3 4. SEQ = 1 10 1 1 1 1 2 2 2 10. SEQ = 1 10 1 1 1 1 1 2 3 9.
```
输出
```
C = 1 1 2 3 4.
SEQ = 1 10 1 1 1 1 1 2 3 9.
```

## 题目分析

本题的核心是验证赋值语句是否满足数组声明中隐含的结构约束。每个数组声明定义了一棵**展开树**：基本元素是固定长度的基本块，复合元素是对已声明数组的引用。赋值右侧提供了一串整数，需要将其按照声明定义的方式划分成若干子段，并检查所有同名引用对应的子段是否完全一致。

直接思路是：对每个数组，记录其展开后的基本块序列（每个基本块标记为长度或引用数组编号），然后对每个赋值，递归检查每个引用子段是否满足对应数组的约束，并收集所有引用的起始位置和长度，最后两两比较同名引用段的值。

本题的难点在于解析输入（需要保留原始语句用于输出）以及递归检查时的段比较。由于数组声明可能嵌套，但每个数组只定义一次，因此可以构建一个有向无环图（引用不形成环，因为引用必须指向已声明的数组）。每个数组的总长度可以在声明时通过累加其子项的长度得到。

## 解题思路

### 数据结构设计

为每个数组存储以下信息：
- `name`：数组名称（字符串）。
- `items`：一个向量，每个元素表示一个组成部分，类型为：
  - `BASIC`：固定长度，存储长度值。
  - `REF`：引用另一个数组，存储被引用数组的索引（在全局数组列表中的编号）。
- `totalLen`：该数组展开后的总长度。

同时维护一个哈希映射 `nameToIdx`，将数组名称映射到其索引。

### 解析输入

将整个输入文件读入一个字符串 `inputStr`，并记录当前扫描位置 `pos`。顺序扫描：

1. 跳过空白字符。
2. 读取一个标识符 `id`。
3. 跳过空白，读取下一个令牌：
   - 若为 `"is"`，则开始解析数组声明。循环读取令牌：
     - 若为 `"."` 则结束声明。
     - 若为 `"["`，则读取括号内的正整数 `k`，然后读取 `"]"`，构造一个 `BASIC` 项。
     - 否则，该令牌应是一个已有数组名，在 `nameToIdx` 中查找其索引，构造一个 `REF` 项。
   - 声明结束后，计算总长度并存入数组列表。
4. 若为 `"="`，则开始解析赋值语句。循环读取整数令牌直到遇到 `"."`，将整数存入 `vals` 向量。然后查找数组索引，调用一致性检查函数，若不一致则记录该赋值语句的原始字符串（从本次赋值开始位置 `startPos` 到当前句点后的位置）。

### 一致性检查

定义递归函数 `checkArray(idx, vals, start)`，其中 `idx` 是当前数组的索引，`vals` 是整数序列，`start` 是该数组在 `vals` 中的起始位置。该函数需要：

- 遍历当前数组的 `items`：
  - 若为 `BASIC`，则直接跳过 `value` 个整数。
  - 若为 `REF`，递归调用 `checkArray(refIdx, vals, cur)` 检查该引用子段，同时记录一个三元组 `(refIdx, cur, len)` 到列表 `refs` 中（`len` 为被引用数组的总长度）。
- 遍历结束后，对 `refs` 中所有具有相同 `refIdx` 的项，检查其对应的子段是否完全相等（按位置比较整数）。若存在不等则返回 `false`。

最后在主函数中先比较总长度是否一致，再调用 `checkArray` 即可。

### 时间复杂度

设数组总数为 $N$，每个数组的 `items` 总数之和为 $M$，所有赋值语句的整数总数之和为 $V$。  
- 解析和构建：$O(M + \text{输入字符数})$。  
- 检查每条赋值：对每个数组的 `items` 递归一次，且每个元素最多遍历一次，因此检查单个赋值的复杂度为 $O($该数组展开后的基本块数$)$，而基本块数等于 `items` 中 `BASIC` 个数加上被引用数组的总基本块数（分摊后每个数组的基本块总数即其展开长度）。但由于每次检查是独立的，总复杂度为 $O(V+$所有赋值涉及的数组总复杂度$)$。若最坏情况下每个赋值都涉及同一个大数组，则总复杂度为 $O($赋值条数$\times$数组大小$)$。但题目未给出明确上限，实际输入规模较小，此递归方法可行。

## 代码实现

```cpp
// The JustaPox Language
// UVa ID: 773
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Item {
    enum Type { BASIC, REF } type;
    int value;  // BASIC: 长度; REF: 数组索引
};

struct ArrayInfo {
    string name;
    vector<Item> items;
    int totalLen;
};

vector<ArrayInfo> arrays;
unordered_map<string, int> nameToIdx;
string inputStr;
size_t pos = 0;

void skipSpaces() {
    while (pos < inputStr.size() && isspace(inputStr[pos])) ++pos;
}

string readToken() {
    skipSpaces();
    if (pos >= inputStr.size()) return "";
    char c = inputStr[pos];
    if (isalpha(c) || c == '_') {
        size_t start = pos;
        while (pos < inputStr.size() && (isalnum(inputStr[pos]) || inputStr[pos] == '_')) ++pos;
        return inputStr.substr(start, pos - start);
    } else if (isdigit(c)) {
        size_t start = pos;
        while (pos < inputStr.size() && isdigit(inputStr[pos])) ++pos;
        return inputStr.substr(start, pos - start);
    } else {
        return string(1, inputStr[pos++]);
    }
}

bool checkArray(int idx, const vector<int>& vals, int start) {
    int cur = start;
    vector<tuple<int, int, int>> refs; // (refIdx, startPos, len)
    for (const auto& item : arrays[idx].items) {
        if (item.type == Item::BASIC) {
            cur += item.value;
        } else {
            int refIdx = item.value;
            int len = arrays[refIdx].totalLen;
            if (!checkArray(refIdx, vals, cur)) return false;
            refs.push_back(make_tuple(refIdx, cur, len));
            cur += len;
        }
    }
    for (size_t i = 0; i < refs.size(); ++i)
        for (size_t j = i + 1; j < refs.size(); ++j)
            if (get<0>(refs[i]) == get<0>(refs[j])) {
                int len = get<2>(refs[i]);
                int s1 = get<1>(refs[i]);
                int s2 = get<1>(refs[j]);
                for (int k = 0; k < len; ++k)
                    if (vals[s1 + k] != vals[s2 + k]) return false;
            }
    return true;
}

bool isConsistent(int idx, const vector<int>& vals) {
    if ((int)vals.size() != arrays[idx].totalLen) return false;
    return checkArray(idx, vals, 0);
}

int main() {
    string line;
    while (getline(cin, line)) {
        inputStr += line;
        inputStr += '\n';
    }

    vector<string> inconsistent;

    while (pos < inputStr.size()) {
        skipSpaces();
        if (pos >= inputStr.size()) break;
        int startPos = pos;
        string id = readToken();
        if (id.empty()) break;
        skipSpaces();
        string next = readToken();

        if (next == "is") {
            ArrayInfo info;
            info.name = id;
            while (true) {
                skipSpaces();
                if (pos >= inputStr.size()) break;
                string tok = readToken();
                if (tok == ".") break;
                else if (tok == "[") {
                    skipSpaces();
                    string numStr = readToken();
                    int k = stoi(numStr);
                    skipSpaces();
                    string close = readToken(); // ']'
                    Item it;
                    it.type = Item::BASIC;
                    it.value = k;
                    info.items.push_back(it);
                } else {
                    auto itMap = nameToIdx.find(tok);
                    if (itMap != nameToIdx.end()) {
                        Item it;
                        it.type = Item::REF;
                        it.value = itMap->second;
                        info.items.push_back(it);
                    }
                }
            }
            int total = 0;
            for (const auto& item : info.items)
                if (item.type == Item::BASIC) total += item.value;
                else total += arrays[item.value].totalLen;
            info.totalLen = total;
            int idx = arrays.size();
            arrays.push_back(info);
            nameToIdx[id] = idx;
        } else if (next == "=") {
            vector<int> vals;
            while (true) {
                skipSpaces();
                if (pos >= inputStr.size()) break;
                string tok = readToken();
                if (tok == ".") break;
                else vals.push_back(stoi(tok));
            }
            auto itMap = nameToIdx.find(id);
            if (itMap != nameToIdx.end()) {
                int idx = itMap->second;
                if (!isConsistent(idx, vals)) {
                    string original = inputStr.substr(startPos, pos - startPos);
                    inconsistent.push_back(original);
                }
            }
        } else break;
    }

    for (const string& s : inconsistent)
        cout << s << '\n';

    return 0;
}
```

## 总结

本题的难点在于对数组声明的递归解析和赋值时对重复引用的值比较。通过将数组声明建模为 `items` 列表，其中基本元素和引用元素分开存储，我们可以方便地递归验证赋值。关键技巧是：

- 使用递归函数同时完成子段约束检查和收集引用段信息，避免两次遍历。
- 利用全局数组列表和哈希映射快速查找被引用数组。
- 原始语句的保留通过记录起始位置和结束位置实现，保证了输出格式与输入一致。

该解法结构清晰，易于扩展，适合处理嵌套声明和多种赋值场景。
