[UVa 282 Rename](https://blog.csdn.net/metaphysis/article/details/161360506)

## 题目描述

在 $\texttt{MS-DOS}$ 和 $\texttt{Unix}$ 系统中，都存在重命名文件的命令。$\texttt{MS-DOS}$ 中使用 `rename`，而 $\texttt{Unix}$ 中使用 `mv`。两者的一个重要区别在于对通配符 `*` 的处理方式不同。

在 $\texttt{MS-DOS}$ 中，可以使用如下命令：

```bash
rename old* new*
```

这条命令会将所有以 `old` 开头的文件名中的 `old` 替换为 `new`。然而在 $\texttt{Unix}$ 中，`mv` 命令并不支持这种通配符写法。

本题要求我们编写一个程序，将 $\texttt{MS-DOS}$ 风格的 `rename` 命令转换为一系列 $\texttt{Unix}$ 风格的 `mv` 命令。

### 输入格式

- 每个数据集首先包含一个文件名列表，每行一个文件名，以单独一行的 `end` 结束。
- 随后是一系列 `rename` 命令，每行格式为 `rename wildfrom wildto`，其中 `wildfrom` 和 `wildto` 各包含恰好一个通配符 `*`。
- 命令列表以单独一行的 `end` 结束。
- 输入中不会出现重复的文件名。

### 输出格式

- 对于每条 `rename` 命令，首先原样输出该命令。
- 然后输出一系列 `mv` 命令，顺序与输入中文件名的出现顺序一致。
- 每个数据集结束后输出一个空行。

### 特殊规则

- 本题中的 `*` 可以匹配任意数量的任意可打印字符（没有 $\texttt{MS-DOS}$ 中 $8$ 字符或点号 `.` 的限制）。
- 大小写敏感（与 $\texttt{Unix}$ 一致）。
- 文件名长度限制为 $14$ 个字符。
- 每条 `rename` 命令基于**原始**的文件名列表执行，而不是上一条命令的结果。

## 解题思路

### 问题本质

将一条形如 `rename A*B C*D` 的命令，转换为若干条 `mv` 命令。对于每个匹配 `A*B` 模式的文件名，需要将其转换为 `C*D` 模式。

这里的 `A`、`B`、`C`、`D` 均为字符串（可能为空），`*` 代表一个“通配符占位符”。匹配的规则是：文件名以 `A` 开头，以 `B` 结尾，中间的部分（即 `*` 匹配的内容）可以任意长度（包括空串）。

转换后的新文件名应当为：`C` + 中间匹配的部分 + `D`。

### 核心难点：如何匹配 `*` 所对应的子串

给定一个模式 `from`（例如 `abFile*.c`）和一个文件名（例如 `abFile001.c`），我们需要找出 `*` 所匹配的具体内容。

#### 模式分解

模式 `from` 中包含恰好一个 `*`，可以将其分解为两部分：
- 前缀：`*` 之前的所有字符
- 后缀：`*` 之后的所有字符

例如：
- `abFile*.c` → 前缀 `abFile`，后缀 `.c`
- `ac*.c` → 前缀 `ac`，后缀 `.c`
- `*` → 前缀 `""`（空串），后缀 `""`（空串）

#### 匹配规则

对于文件名 `filename`，如果它能够匹配模式 `from`，则必须满足：

1. **前缀匹配**：文件名开头部分必须完全等于 `from` 的前缀
2. **后缀匹配**：文件名结尾部分必须完全等于 `from` 的后缀
3. **前缀和后缀不能重叠**：前缀匹配的结尾位置必须严格小于后缀匹配的开始位置

匹配完成后，`*` 所对应的内容就是文件名中位于前缀之后、后缀之前的子串。

例如：
- 模式 `abFile*.c`，文件名 `abFile001.c`
  - 前缀 `abFile` 匹配前 $5$ 个字符
  - 后缀 `.c` 匹配最后 $2$ 个字符
  - 中间部分为 `001`

#### 特殊情况处理

需要考虑边界情况：
- 前缀或后缀可能为空
- `*` 匹配的内容可以为空（例如 `a*` 匹配 `a`，中间部分为空）
- 文件名长度可能正好等于前缀长度 + 后缀长度，此时 `*` 匹配空串

### 算法步骤

1. **读取文件名列表**：将所有文件名存储到 `vector<string>` 中，直到遇到 `end`。

2. **处理每条 `rename` 命令**：
   - 读取 `command`、`from`、`to`
   - 输出原始命令
   - 从 `to` 中提取 `firstpart`（`*` 之前的部分）和 `secondpart`（`*` 之后的部分）
   - 遍历所有原始文件名，对每个文件名执行匹配和转换

3. **匹配和转换**：
   - 使用两个指针分别从前往后和从后往前扫描
   - 前向扫描：比较 `from` 和 `filename` 的字符，直到遇到 `*` 或不匹配
   - 后向扫描：比较 `from` 和 `filename` 的末尾字符，直到遇到 `*` 或不匹配
   - 验证匹配条件：
     - 两个扫描都正确地在 `*` 位置停止
     - 前后扫描的区间不重叠（即前缀结束位置 $i - 1$ 必须小于后缀开始位置 $j + 1$）
   - 提取中间部分：`filename[i..j]`
   - 构造新文件名：`firstpart + mid + secondpart`
   - 输出 `mv oldname newname`

### 正确性分析

这种双向扫描方法能够正确处理各种情况：
- 当 `from` 以 `*` 开头时，前缀为空，前向扫描立即遇到 `*`
- 当 `from` 以 `*` 结尾时，后缀为空，后向扫描立即遇到 `*`
- 通过比较 $i$ 和 $j$ 的值可以检测出前缀和后缀是否重叠（即模式无法匹配的情况）

时间复杂度：$O(N \times M)$，其中 $N$ 是文件名数量，$M$ 是文件名平均长度。由于文件名长度不超过 $14$，这个复杂度完全可以接受。

## 代码实现

```cpp
// Rename
// UVa ID: 282
// Verdict: Accepted
// Submission Date: 2016-06-06
// UVa Run Time: 0.120s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

string firstpart, secondpart, command, from, to;

// 匹配并转换单个文件名
void match(string& filename) {
    // 前向扫描：比较前缀
    int i = 0;
    while (i < from.length() && i < filename.length() &&  from[i] == filename[i] && from[i] != '*') i++;
    // 后向扫描：比较后缀
    int j = filename.length() - 1, k = from.length() - 1;
    while (j >= 0 && k >= 0 && filename[j] == from[k] && from[k] != '*') j--, k--;
    // 验证匹配条件：
    // 1. 前向扫描必须在 '*' 处停止
    // 2. 后向扫描也必须在 '*' 处停止
    // 3. 前后扫描的区间不能重叠
    if (from[i] != '*' || from[k] != '*' || i > j + 1) return;
    // 输出 mv 命令
    cout << "mv " << filename << " ";
    // 输出新文件名：firstpart + 中间部分 + secondpart
    cout << firstpart;
    for (int k = i; k <= j; k++) cout << filename[k];
    cout << secondpart << endl;
}

int main() {
    ios::sync_with_stdio(false);
    string line;
    vector<string> filenames;
    while (cin >> line) {
        // 读取文件名列表
        if (line != "end") filenames.push_back(line);
        else {
            // 处理 rename 命令序列
            while (cin >> command, command != "end") {
                cin >> from >> to;
                // 输出原始命令
                cout << command << " " << from << " " << to << endl;
                // 从目标模式 to 中提取 firstpart 和 secondpart
                // firstpart: '*' 之前的部分
                firstpart.clear();
                secondpart.clear();
                for (int i = 0; i < to.length() && to[i] != '*'; i++) firstpart += to[i];
                // secondpart: '*' 之后的部分
                for (int j = to.length() - 1; j >= 0 && to[j] != '*'; j--) secondpart.insert(secondpart.begin(), to[j]);
                // 对每个原始文件名进行匹配和转换
                for (int i = 0; i < filenames.size(); i++) match(filenames[i]);
            }
            // 每个数据集结束后输出空行
            cout << endl;
            // 清空文件名列表，准备处理下一个数据集
            filenames.clear();
        }
    }
	return 0;
}
```

## 总结

本题的核心在于理解 $\texttt{MS-DOS}$ 通配符 `*` 的匹配语义，并将其正确转换为 $\texttt{Unix}$ `mv` 命令序列。通过将模式分解为前缀和后缀，并利用双向扫描确定 `*` 匹配的内容，可以简洁地解决问题。代码中需要注意边界条件处理，特别是当 `*` 出现在模式开头或结尾时的情况。
