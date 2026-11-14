[UVa 368 Indexing Web Pages](https://blog.csdn.net/metaphysis/article/details/161611437)

## 题目描述

编写一个程序，为小型万维网页集合创建索引。每个“页面”是一种称为 $\texttt{HTML}$（超文本标记语言）的特殊格式的文本文件。$\texttt{HTML}$ 格式包括普通文本和特殊的 $\texttt{HTML}$ 命令，这些命令总是用尖括号括起来。

你的程序需要：
1. 读取名为 `index.htm` 的 $\texttt{HTML}$ 文件
2. 读取该文件中所有被 `HREF` 命令引用的文件
3. 递归地读取这些文件引用的所有文件，直到没有新文件可读
4. 读取文件 `webpage.in` 中的单词列表
5. 对于每个单词，列出所有包含该单词的文件的文件名

### 假设条件

1. 任何左尖括号 `<` 后面最终都会有一个匹配的右尖括号 `>`
2. **单词**的定义：
   - 不在尖括号对之间
   - 只包含字母（无空格、连字符、撇号等）
   - 不是更长单词的一部分（例如 `balloon` 中不考虑 `loon`）
3. 单词最多 $25$ 个字符
4. 大小写不敏感（`Word`、`word`、`WORD` 视为相同）
5. 唯一需要关注的 $\texttt{HTML}$ 命令是 `HREF`，格式固定为 `<A HREF="filename">`，文件名不超过 $12$ 个字符，以 `.htm` 结尾
6. $\texttt{HTML}$ 文件可能相互引用或自引用，但最多 $100$ 个不同文件

### 输入格式

初始 $\texttt{HTML}$ 文件名为 `index.htm`。随后是其他文件（包括 `webpage.in`），每个文件后跟一个空行。`webpage.in` 中的单词每行一个。

### 输出格式

对于每个单词，输出：
- 如果找到：`"word" can be found in the following pages:` 后跟文件名列表（每行一个，缩进 $5$ 个空格）
- 如果未找到：`"word" can not be found in any page.`

每个单词输出后跟一个空行。

### 样例输入（简化）

```
<HTML> ... <A HREF="layout.htm"> ... </HTML>

<A bunch of gibberish and a word> ... <A HREF="index.htm"> ...
```

### 样例输出

```
"file" can be found in the following pages:
     index.htm
     layout.htm

"index" can be found in the following pages:
     index.htm

"html" can be found in the following pages:
     index.htm
     layout.htm

"recursion" can not be found in any page.

"word" can not be found in any page.

"is" can be found in the following pages:
     index.htm
     layout.htm
```

---

## 题目分析

### 问题的本质

这是一个**网络爬虫**（$\texttt{web crawler}$）的简化实现。需要：
1. 递归解析 $\texttt{HTML}$ 文件，提取所有 `href` 链接
2. 下载（读取）这些链接指向的文件
3. 对每个文件，提取其中的单词（排除 HTML 标签内容）
4. 为单词查询建立索引

### 处理流程

1. 使用队列（$\texttt{BFS}$）处理文件引用
2. 对每个文件：
   - 解析 $\texttt{HTML}$，提取单词
   - 提取 `href` 链接，将新文件加入队列
3. 读取 `webpage.in` 中的查询单词
4. 对于每个单词，查找包含该单词的文件列表

### 单词提取规则

- 忽略尖括号内的内容（$\texttt{HTML}$ 标签和注释）
- 只考虑连续的字母序列作为单词
- 单词边界由非字母字符分隔

### 大小写处理

所有单词转换为小写后再处理。

---
## 参考代码

```cpp
// Indexing Web Pages
// UVa ID: 368
// Verdict: Accepted
// Submission Date: 2019-01-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

set<string> visited;                 // 已访问的文件
vector<string> pages;                // 所有访问过的文件列表
map<string, set<string>> words;      // 文件 -> 该文件中的单词集合
queue<string> q;                     // BFS 队列
string filename, line, content;      // 当前文件名、输入行、文件内容

// 将字符串转换为小写
void tolower(string &s)
{
    for (int i = 0; i < s.length(); i++)
        s[i] = std::tolower(s[i]);
}

// 解析文件内容：提取单词和 href 链接
void process()
{
    int i = 0;
    while (i < content.length())
    {
        if (content[i] == '<')
        {
            // 处理 HTML 标签
            i++;
            string block;
            while (i < content.length() && content[i] != '>')
            {
                block += content[i];
                i++;
            }
            // 检查是否是 href 链接
            if (block.length() > 13)
            {
                if (block.substr(0, 8) == "A HREF=\"" && block.back() == '"')
                {
                    string page = block.substr(8, block.length() - 9);
                    // 如果未访问过，加入队列
                    if (visited.find(page) == visited.end())
                    {
                        visited.insert(page);
                        pages.push_back(page);
                        q.push(page);
                    }
                }
            }
        }
        else if (isalpha(content[i]))
        {
            // 提取单词（连续字母）
            string w;
            while (i < content.length() && isalpha(content[i]))
            {
                w += content[i];
                i++;
            }
            tolower(w);  // 转换为小写
            words[filename].insert(w);
        }
        else
        {
            i++;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    // BFS 遍历所有文件，从 index.htm 开始
    visited.insert("index.htm");
    pages.push_back("index.htm");
    q.push("index.htm");
    
    while (!q.empty())
    {
        filename = q.front(); q.pop();
        content.clear();
        
        // 读取文件内容（直到空行）
        while (getline(cin, line), line.length() > 0)
        {
            content += line;
            content += '\n';
        }
        
        // 解析文件内容
        process();
    }

    // 处理查询单词
    string w;
    int cases = 0;
    while (cin >> w)
    {
        if (cases++) cout << '\n';
        cout << '"' << w << '"';
        
        string lower_w = w;
        tolower(lower_w);
        
        // 查找包含该单词的文件
        vector<string> lists;
        for (auto fs : pages)
        {
            if (words[fs].find(lower_w) != words[fs].end())
                lists.push_back(fs);
        }
        
        if (lists.size() == 0)
            cout << " can not be found in any page.\n";
        else
        {
            cout << " can be found in the following pages:\n";
            for (auto ls : lists)
                cout << "     " << ls << '\n';
        }
    }

    return 0;
}
```
