[UVa 175 Keywords](https://blog.csdn.net/metaphysis/article/details/160706502)

## 题目分析

本题要求根据给定的若干个 **兴趣配置文件**（$\texttt{Profile}$）和 **标题**（$\texttt{Title}$），判断每个标题是否被每个配置文件选中。选中的条件是：在标题中，存在至少一对来自配置文件的关键词，它们之间的单词个数 **不超过** 配置文件给定的阈值。

输入格式如下：

- 配置文件以 `P:` 开头，后面依次为一个整数阈值和至少两个小写关键词。
- 标题以 `T:` 开头，后跟一个以 `|` 结尾的字符串。标题可能跨多行，每行不超过 $80$ 个字符，总长度不超过 $255$ 个字符。
- 非字母字符被忽略，大写字母转为小写。
- 文件以一行 `#` 结束。

输出格式为：对于每个配置文件，输出其编号和选中的标题编号，编号从 $1$ 开始，标题编号按升序排列，用逗号分隔。

## 解题思路

本题的核心是 **关键词匹配** 和 **距离判断**。

### 1. 输入处理

- 读取每一行，判断行首是否为 `P:` 或 `T:`。
- 若为 `P:`，解析阈值和关键词，存入 `profiles` 和 `gaps` 数组。
- 若为 `T:`，将多行内容拼接，直到遇到 `|`，然后进行预处理：
  - 保留字母和空格，其他字符删除。
  - 大写字母转小写。
  - 按空格分词，得到标题的单词列表。
- 遇到 `#` 时停止输入。

### 2. 匹配与距离判断

对于一个配置文件 $i$ 和一个标题 $j$：

- 配置文件中可能包含多个关键词（至少 $2$ 个）。
- 我们需要判断 **是否存在一对关键词**（可以是不相邻的顺序，如第一个和第三个），它们在标题中的位置差（即中间隔的单词数）不超过阈值 $gap$。
- 具体实现方法：
  - 遍历标题中的每个单词，如果匹配到配置文件中的第 $p$ 个关键词，则向后遍历配置文件中的其他关键词 $q$（$q > p$）。
  - 在标题中，只检查距离当前单词前后 $gap + 1$ 范围内的单词（即最多间隔 $gap$ 个单词）。
  - 如果找到匹配，则返回 $\texttt{true}$。

### 3. 输出结果

按配置文件顺序输出，每个配置文件一行，包含选中标题的编号。

## 注意事项

- 标题中的单词可能重复，因此不能简单使用 $\texttt{find}$。
- 阈值表示 **中间最多可以有多少个单词**，因此搜索范围为 `[n - gap - 1, n + gap + 1]`。
- 行末的 `|` 是标题结束标志，`|` 本身不出现在标题内容中。
- 输入中 `P` 和 `T` 后的冒号后面可能有空格，需要处理。

## 代码实现

```cpp
// Keywords
// UVa ID: 175
// Verdict: Accepted
// Submission Date: 2016-02-21
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

vector<vector<string>> profiles; // 存储每个配置文件的关键词列表
vector<int> gaps;                // 存储每个配置文件的阈值
vector<vector<string>> titles;   // 存储每个标题的单词列表

// 处理配置文件
void processProfile(string line) {
    // 去掉开头的 "P:"
    line = line.substr(line.find("P:") + 2);
    string word;
    int distance;
    istringstream iss(line);
    iss >> distance;               // 读取阈值
    gaps.push_back(distance);      // 存入 gaps 数组
    vector<string> keywords;
    while (iss >> word) keywords.push_back(word); // 读取后续关键词
    profiles.push_back(keywords);  // 存入 profiles 数组
}

// 处理标题
void processTitle(string line) {
    // 去掉开头的 "T:"
    line = line.substr(line.find("T:") + 2);
    // 从后往前处理，删除非字母字符，并将大写字母转为小写
    for (int i = line.length() - 1; i >= 0; i--)
        if (isalpha(line[i])) {
            if (isupper(line[i]))
                line[i] = tolower(line[i]);
        } else if (line[i] != ' ' && line[i] != '\t') line.erase(line.begin() + i);
    // 按空格分词
    istringstream iss(line);
    vector<string> singleTitle;
    string word;
    while (iss >> word) singleTitle.push_back(word);
    titles.push_back(singleTitle);
}

// 判断第 i 个配置文件是否选中第 m 个标题
bool findKeywords(int i, int m, int gap) {
    // 遍历配置文件中的每一对关键词
    for (int j = 0; j < profiles[i].size() - 1; j++)
        for (int n = 0; n < titles[m].size(); n++) {
            // 在标题中找到匹配的第一个关键词
            if (titles[m][n] == profiles[i][j]) {
                // 遍历配置文件中后面的关键词
                for (int k = j + 1; k < profiles[i].size(); k++) {
                    // 计算搜索范围：[n - gap - 1, n + gap + 1]
                    int up = n + gap + 1;
                    int down = n - gap - 1;
                    for (int x = max(down, 0); x <= min(up, (int)(titles[m].size()) - 1); x++) {
                        if (x == n) continue; // 跳过自身
                        if (titles[m][x] == profiles[i][k]) return true; // 找到匹配
                    }
                }
            }
        }
    return false;
}

// 对所有标题进行匹配搜索，并输出结果
void searchTitle() {
    for (int i = 0; i < profiles.size(); i++) {
        cout << (i + 1) << ": ";
        bool firstPrinted = false;
        for (int j = 0; j < titles.size(); j++)
            if (findKeywords(i, j, gaps[i])) {
                if (firstPrinted == false) firstPrinted = true;
                else cout << ",";
                cout << (j + 1);
            }
        cout << "\n";
    }
}

int main() {
    cin.tie(0); cout.sync_with_stdio(false);
    string line, title;
    bool profileEnded = false;   // 标记是否已经遇到第一个标题
    while (getline(cin, line), line != "#") {
        // 尚未遇到标题，且当前行是配置文件
        if (profileEnded == false && line.find("T:") == line.npos) {
            processProfile(line);
            continue;
        } else profileEnded = true;   // 开始处理标题
        // 拼接标题内容
        title += line;
        // 遇到 '|' 表示一个标题结束
        if (line.find('|') != line.npos) {
            processTitle(title);
            title.clear();         // 清空，准备下一个标题
        }
    }
    searchTitle();
    return 0;
}
```

## 总结

本题主要考察字符串处理和子串匹配的变形应用。关键在于正确处理输入格式、单词边界以及距离判断的范围控制。实现时注意：

- 非字母字符的过滤和大小写转换。
- 标题跨行拼接。
- 距离判断的边界条件（避免数组越界）。
