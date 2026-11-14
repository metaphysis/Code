[UVa 335 Processing MX Records](https://blog.csdn.net/metaphysis/article/details/161544988)

## 题目描述

域名系统（$\texttt{DNS}$）的主要功能是将符号化机器名（如 `bigone.stateu.edu`）映射到对应的网络地址（如 `24.99.100.33`）。机器名的各个部分由点分隔，从右向左读取时对应树中的节点。内部节点对应域（$\texttt{domain}$）。例如，`.edu` 域下是所有美国大学和学院的机器，而加拿大的所有机器都在 `.ca` 域下。

通过提供一个或多个 $\texttt{MX}$ 记录，系统管理员可以安排 $\texttt{DNS}$ 将发往一台机器的邮件重定向到另一台机器。重定向在许多情况下是合适的，其中一个常见用途是为虚构的、具有有意义名称的机器创建邮件地址。例如，允许邮件发送到 `info.stateu.edu`，但校园内并没有名为 `info` 的物理机器。通过使用适当的 $\texttt{MX}$ 记录，可以将邮件重定向到 `bigone.stateu.edu`。

在本题中，我们将处理简化版的 $\texttt{MX}$ 记录。

### MX 记录格式

一个 $\texttt{MX}$ 记录包含三个字段（由空白字符分隔）：
- **第一字段**：源机器名（目标邮件地址的机器名）
- **第二字段**：偏好值（非负整数，数值越小优先级越高）
- **第三字段**：目标机器名（邮件实际投递的目标）

如果第一字段不存在（即行首为空格），则假定它与前一行的第一字段相同。

### 通配符记录

通配符 $\texttt{MX}$ 记录允许使用一条记录将邮件重定向到多台机器。例如：
```
*.citycc.midville.edu 0 tiny.stateu.edu
```
将任何以 `.citycc.midville.edu` 结尾的机器名的邮件重定向到 `tiny.stateu.edu`。

简化假设：通配符 `*` 只出现在符号名的第一部分，且任何符号名中不会出现超过三个点。

### 命令

在 $N$ 条 $\texttt{MX}$ 记录之后，输入包含以下命令：
- `U machine`：机器上线（$\texttt{up}$）
- `D machine`：机器下线（$\texttt{down}$）
- `A machine`：查询邮件重定向目标
- `X`：输入结束

所有机器初始为上线状态。

**注意**：$\texttt{MX}$ 记录不会被递归处理。即，如果 `first.com` 的邮件被重定向到 `second.com`，任何可能将 `second.com` 重定向到其他机器的 $\texttt{MX}$ 记录都不会在处理 `first.com` 时被检查。

### 输入格式

第一行包含整数 $N$，接下来 $N$ 行每行一个 $\texttt{MX}$ 记录。剩余行每行以 `U`、`D`、`A` 或 `X` 开头。

### 输出格式

对于每个 `A` 命令，输出一行：
```
machine => destination
```
如果没有适用的 $\texttt{MX}$ 记录，输出：
```
machine =>
```

### 样例输入

```
5
service.stateu.edu 10 tiny.stateu.edu
info.stateu.edu 0 bigone.stateu.edu
 10 tiny.stateu.edu
service.stateu.edu 5 bigone.stateu.edu
*.smallu.edu 10 service.stateu.edu
A alpha.cs.smallu.edu
A info.stateu.edu
D bigone.stateu.edu
A info.stateu.edu
A nowhere.com
X
```

### 样例输出

```
alpha.cs.smallu.edu => service.stateu.edu
info.stateu.edu => bigone.stateu.edu
info.stateu.edu => tiny.stateu.edu
nowhere.com =>
```

---

## 题目分析

### 问题的本质

这是一个**字符串匹配 + 优先级选择**问题。给定一组 $\texttt{MX}$ 记录，每条记录包含：
- 源模式（完整域名或通配符模式）
- 优先级（数值越小优先级越高）
- 目标机器

当查询一个机器名时，需要：
1. 找到所有匹配该机器名的 $\texttt{MX}$ 记录
2. 选择优先级最高（数值最小）且目标机器为**上线**状态的记录
3. 输出目标机器名；如果没有匹配，则不输出目标

### 匹配规则

- **精确匹配**：源模式与机器名完全相同
- **通配符匹配**：源模式形如 `*.domain`，匹配所有以 `.domain` 结尾的机器名

匹配优先级：在相同优先级下，精确匹配优先于通配符匹配？题目没有明确说明，但从样例可知，需要取**所有匹配记录中优先级最高的**，如果优先级相同，取哪个？题目没有要求，只需输出一个即可。

### 机器状态

- 初始所有机器为上线（$\texttt{up}$）
- `U machine` 将机器设为上线
- `D machine` 将机器设为下线

只有上线的目标机器才能被选为最终目的地。

---
## 参考代码

```cpp
// Processing MX Records
// UVa ID: 335
// Verdict: Accepted
// Submission Date: 2016-07-07
// UVa Run Time: 0.170s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 机器状态：true=在线，false=离线
map<string, bool> status;
// MX 记录索引（仅用于记录，实际未使用）
map<string, int> indexer;
// MX 记录存储：源模式 -> (优先级, 目标) 的多重映射
map<string, multimap<int, string>> records;

// 判断机器是否在线（已注册且状态为 true）
inline bool isMachineLive(string machine)
{
    return (status.find(machine) != status.end() && status[machine]);
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n, second_field;
    string line, last_first_field, first_field, third_field, machine;
    istringstream iss;

    // 读取 MX 记录数量
    getline(cin, line); n = stoi(line);

    // 读取并存储所有 MX 记录
    for (int i = 1; i <= n; i++)
    {
        getline(cin, line); 
        iss.clear(); 
        iss.str(line);
        
        // 判断第一字段是否存在（行首是否有空格）
        if (line.front() != ' ')
        {
            iss >> first_field >> second_field >> third_field;
            last_first_field = first_field;
        }
        else
        {
            iss >> second_field >> third_field;
            first_field = last_first_field;
        }

        // 存储记录
        records[first_field].insert(make_pair(second_field, third_field));
        indexer[first_field] = i;
        // 初始化机器状态为在线
        status[first_field] = true;
        status[third_field] = true;
    }

    char action;
    while (getline(cin, line), line.front() != 'X')
    {
        iss.clear(); 
        iss.str(line); 
        iss >> action >> machine;

        if (action == 'U' || action == 'D')
        {
            // 更新机器状态
            if (status.find(machine) != status.end())
                status[machine] = (action == 'U');
            // 通配符模式的状态更新
            else if (status.find("*." + machine) != status.end())
                status["*." + machine] = (action == 'U');
        }
        else if (action == 'A')
        {
            cout << machine << " =>";
            
            bool flag = false;
            int minPreference;
            string destination;

            // 1. 精确匹配
            for (auto record : records[machine])
            {
                if (isMachineLive(record.second))
                {
                    minPreference = record.first;
                    destination = record.second;
                    flag = true;
                    break;  // 由于 map 按优先级升序存储，第一个即为最优
                }
            }

            // 2. 通配符匹配：逐级检查
            for (int start = machine.find('.', 0); start != string::npos; 
                 start += 1, start = machine.find('.', start))
            {
                string next_machine = "*" + machine.substr(start);
                for (auto record : records[next_machine])
                {
                    if (isMachineLive(record.second))
                    {
                        if (!flag)
                        {
                            minPreference = record.first;
                            destination = record.second;
                            flag = true;
                        }
                        else if (record.first < minPreference)
                        {
                            minPreference = record.first;
                            destination = record.second;
                        }
                    }
                }
            }
            
            if (flag) 
                cout << " " << destination;
            cout << endl;
        }
    }

    return 0;
}
```
