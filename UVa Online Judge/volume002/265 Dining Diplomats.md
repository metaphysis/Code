[UVa 265 Dining Diplomats](https://blog.csdn.net/metaphysis/article/details/161308399)

## 题目分析

本题是一个**图论与搜索**问题，结合了语言兼容性和外交关系两大约束条件。题目描述了一个圆桌晚宴的场景，共有 $10$ 个座位，编号从 $1$ 到 $10$，其中座位 $1$ 固定为雇主（$\texttt{Employer}$），其余 $9$ 个座位为外交官（$\texttt{Diplomats}$）。每个外交官会 $1$ 到 $5$ 种语言，且其所属国家与其他国家有正式的外交关系。

### 约束条件

1. **语言约束**：相邻而坐的两个人必须有一种共同语言。一个人可以与左边的人用一种共同语言交流，与右边的人用另一种（或相同）共同语言交流。
2. **外交关系约束**：相邻而坐的两个人所属国家必须互相承认对方（即外交关系是对称的）。雇主与所有其他客人都有外交关系。
3. **相同国家的外交官**：来自同一国家的外交官与相同的外国国家列表有外交关系。同一国家总是与自身有外交关系。同一国家的外交官之间可能没有共同语言。

### 输入格式

输入包含多个数据集，每个数据集包含 $10$ 行（第一个为雇主，随后 $9$ 个为客人），以一个空行分隔。每行的格式为：

```cpp
国家代码(3个大写字母) 语言集合(1-5个字母) 外交关系国家列表(0-9个3字母代码)
```

例如：
```cpp
USA EF CHN GBR USR FRA FRG JPN ISR POR KOR
```
表示美国外交官，会英语（`E`）和法语（`F`），与 `CHN`、`GBR`、`USR`、`FRA`、`FRG`、`JPN`、`ISR`、`POR`、`KOR` 有外交关系。

### 输出格式

对于每个数据集：

- 如果存在解，输出 $10$ 行，每行格式为：`座位号 左边共同语言 国家代码 右边共同语言`，按座位 $1$ 到 $10$ 的顺序输出。
- 如果无解，输出 `NO SOLUTION EXISTS`。

## 解题思路

### 核心问题转化

将问题建模为**在圆桌上寻找一个哈密顿回路**（$\texttt{Hamiltonian Cycle}$）的变种。每个人是一个节点，如果两个人满足以下两个条件，则在它们之间连一条边：

1. **共同语言**：两个人的语言集合有交集。
2. **相互外交关系**：`A` 国家承认 `B` 国家，且 `B` 国家承认 `A` 国家（或两人来自同一国家）。

由于雇主固定坐在座位 $1$，我们只需要从雇主出发，找到一条经过所有 $10$ 个节点的回路，并确定每条边上使用的具体共同语言。

### 数据结构设计

```cpp
struct diplomat {
    string code;      // 国家代码
    int language;     // 语言集合的位掩码，'A'对应最低位(bit 0)
};
```

- 使用**位掩码**（$\texttt{bitmask}$）表示语言集合。每个字母 `'A'` 到 `'Z'` 映射到 $2^0$ 到 $2^{25}$。这样两个语言集合的交集可以通过按位与 `&` 快速计算。
- 使用 `map<string, set<string>> relations` 存储每个国家的外交关系列表（用 `set` 便于 $O(\log n)$ 查找）。

### 算法步骤

#### 1. 读取输入并构建数据结构

每读取一个人，解析其国家代码、语言字符串（转换为位掩码）以及外交关系国家列表。由于同一国家可能多次出现，直接按输入顺序存储到 `diplomats` 向量中，座位 $0$ 对应雇主。

#### 2. 构建邻接表

遍历所有节点对 $(i, j)$，若满足条件则双向添加边：

```cpp
bool isNext(int i, int j) {
    // 外交关系判断：同一国家 或 互相承认
    bool hasRelation = (diplomats[i].code == diplomats[j].code) ||
        (relations[diplomats[i].code].count(diplomats[j].code) > 0 &&
         relations[diplomats[j].code].count(diplomats[i].code) > 0);
    // 共同语言判断：语言位掩码有交集
    return hasRelation && (diplomats[i].language & diplomats[j].language);
}
```

#### 3. 深度优先搜索找回路

由于 $n = 10$ 较小，可以直接使用 $\texttt{DFS}$ 回溯搜索。从座位 $0$（雇主）出发，依次选择下一个座位的人选，直到填满 $10$ 个座位。

搜索的剪枝条件：
- 当前候选人必须与上一个人有边相连。
- 最后一个人必须与雇主（座位 $0$）有边相连，形成回路。

代码中的 `dfs(guest, index)` 表示：
- `guest`：当前座位上的人（节点编号）
- `index`：下一个要填充的座位编号（从 $1$ 到 $10$）

当 `index == 10` 时，检查最后一个人与雇主是否有边，若有则找到一个解。

#### 4. 确定边上使用的共同语言

给定两个相邻的人 $i$ 和 $j$，它们的共同语言集合为 `language_i & language_j`，取其中第一个（最低位）对应的字母作为输出语言：

```cpp
char getCommonLanguage(int i, int j) {
    int common = diplomats[i].language & diplomats[j].language;
    char language = 'A';
    while ((common & 1) == 0) {
        language++;
        common >>= 1;
    }
    return language;
}
```

#### 5. 输出结果

若找到解，按座位 $0$ 到 $9$ 的顺序（对应座位 $1$ 到 $10$）输出。对于座位 $i$：
- 左边共同语言：`getCommonLanguage(i-1, i)`
- 右边共同语言：`getCommonLanguage(i, i+1)`
（注意取模处理圆桌）

若搜索结束未找到解，输出 `NO SOLUTION EXISTS`。

### 时间复杂度分析

- 构建邻接表：$O(n^2 \cdot L)$，其中 $L$ 为外交关系查找时间（$O(\log m)$），$n=10$ 可忽略。
- 搜索：最坏情况下 $O((n-1)!)$，但由于约束较强，实际运行很快。

## 代码实现

```cpp
// Dining Diplomats
// UVa ID: 265
// Verdict: Accepted
// Submission Date: 2016-06-06
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct diplomat
{
    string code;       // 国家代码，3个大写字母
    int language;      // 语言集合的位掩码，每个字母对应一个二进制位
};

vector<diplomat> diplomats;          // 存储所有10个人的信息，索引0为雇主
vector<vector<int>> edges;           // 邻接表，edges[i]存储与i有边相连的节点
bool flag;                           // 是否已找到解
vector<bool> seated(10);             // 标记某节点是否已被安排座位
vector<int> table(10);               // table[i]表示座位i上的人的节点编号
map<string, set<string>> relations;  // 外交关系表，key为国家代码，value为承认的国家集合

// 判断两个人是否可以相邻就座
bool isNext(int i, int j)
{
    // 外交关系判断：
    // 1. 同一国家可以相邻
    // 2. 不同国家需要互相承认（注意：题目数据可能存在单方面承认的情况，
    //    因此需要双向判断）—— by brainfry
    bool hasRelation = false;
    if (diplomats[i].code == diplomats[j].code ||
        (relations[diplomats[i].code].count(diplomats[j].code) > 0 &&
            relations[diplomats[j].code].count(diplomats[i].code) > 0))
        hasRelation = true;

    // 同时需要共同语言
    return hasRelation && (diplomats[i].language & diplomats[j].language);
}

// 获取两个人之间用于交流的共同语言（取第一个共同语言）
char getCommonLanguage(int i, int j)
{
    int commonLanguage = diplomats[i].language & diplomats[j].language;

    // 从最低位开始找第一个为1的位，对应字母'A'、'B'、'C'...
    char language = 'A';
    while ((commonLanguage & 1) == 0)
    {
        language++;
        commonLanguage >>= 1;
    }

    return language;
}

// 深度优先搜索找哈密顿回路
// guest: 当前座位上的人的索引
// index: 下一个要安排的座位编号（1到10）
void dfs(int guest, int index)
{
    if (flag)
        return;

    // 已经安排了所有10个座位
    if (index == 10)
    {
        // 检查最后一个人与雇主（座位0）之间是否有边，形成回路
        if (count(edges[guest].begin(), edges[guest].end(), 0) > 0)
        {
            flag = true;
            // 按座位1到10的顺序输出结果
            for (int i = 0; i < 10; i++)
            {
                cout << (i + 1);
                // 左边：座位(i-1)与座位i的共同语言
                cout << " " << getCommonLanguage(table[((i - 1) + 10) % 10], table[i]);
                // 国家代码
                cout << " " << diplomats[table[i]].code;
                // 右边：座位i与座位(i+1)的共同语言
                cout << " " << getCommonLanguage(table[i], table[(i + 1) % 10]);
                cout << endl;
            }
        }

        return;
    }

    // 尝试所有与当前客人相邻且未被安排的客人
    for (int i = 0; i < edges[guest].size(); i++)
        if (seated[edges[guest][i]] == false)
        {
            seated[edges[guest][i]] = true;
            table[index] = edges[guest][i];

            dfs(edges[guest][i], index + 1);

            if (flag)
                return;

            // 回溯
            seated[edges[guest][i]] = false;
        }
}

// 为当前数据集寻找圆桌安排
void findCircle()
{
    // 构建邻接表
    edges.clear();
    edges.assign(10, vector < int >());

    for (int i = 0; i < 10; i++)
        for (int j = i + 1; j < 10; j++)
            if (isNext(i, j))
            {
                edges[i].push_back(j);
                edges[j].push_back(i);
            }

    // 深度优先搜索，从雇主（索引0）开始
    flag = false;
    fill(seated.begin(), seated.end(), false);
    table[0] = 0;      // 座位0固定为雇主
    seated[0] = true;

    dfs(0, 1);         // 从座位1开始安排

    if (flag == false)
        cout << "NO SOLUTION EXISTS" << endl;
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        if (line.length() > 0)
        {
            diplomat d;

            string language;
            istringstream iss(line);
            iss >> d.code >> language;

            // 将语言字符串转换为位掩码
            d.language = 0;
            for (int i = 0; i < language.length(); i++)
                d.language |= 1 << (language[i] - 'A');

            // 读取外交关系国家列表
            string country;
            while (iss >> country)
                relations[d.code].insert(country);

            diplomats.push_back(d);
        }
        else
        {
            // 处理完一个数据集
            findCircle();
            cout << endl;      // 数据集之间输出空行
            diplomats.clear();
            relations.clear();
        }
    }

    return 0;
}
```

## 注意事项

1. **外交关系的对称性**：题目明确指出“两个来自同一国家的外交官与相同的外国国家列表有外交关系”，但未明确保证输入数据中的外交关系列表是对称的。代码中采用了双向检查，避免因单方面承认而错误地允许相邻。

2. **共同语言的选取**：当两个外交官有多种共同语言时，可以任选一种。代码中简单地选取按字母序最小的那个（即位掩码中最低位的 $1$）。

3. **多数据集处理**：输入以空行分隔数据集，文件末尾没有空行。代码通过判断 `line.length() > 0` 来区分数据行与分隔空行。

4. **输出格式**：每个数据集输出后紧跟一个空行（最后一个数据集后也有空行），样例输出中显示了这一格式要求。
