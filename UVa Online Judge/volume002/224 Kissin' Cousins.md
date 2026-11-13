[UVa 224 Kissin' Cousins](https://blog.csdn.net/metaphysis/article/details/161085826)

## 题目分析

本题要求根据输入的亲属关系记录，回答任意两人之间的最近亲属关系。关系分为两种：

1. **直系后代关系**（`descendant-p`）：如果一个人是另一个人的祖先，$p$ 表示相隔的代数。
2. **表亲关系**（`cousin-m-n`）：两人有共同祖先但不是直系关系，$m$ 表示第几代表亲（共同祖先的代数差减 $1$），$n$ 表示相差的代数。

题目将兄弟姊妹定义为 `cousin-0-0`，这是对传统定义的一个扩展。关系比较规则为：直系关系优先于表亲关系；表亲关系中 $m$ 越小越近，$m$ 相同时 $n$ 越小越近。

## 解题思路

本题本质上是**家族树中的最近公共祖先（$\texttt{LCA}$）问题**。

### 数据结构设计

使用两个邻接表：
- $\texttt{child}$：存储从父母到孩子的有向边（正向）
- $\texttt{parent}$：存储从孩子到父母的有向边（反向）

每条边包含目标人名和关系距离 $k$（$k$ 表示第一人是第二人的第 $k$ 代后代）。

### 关系判定

**1. 直系后代判定**

从 $A$ 出发沿 $\texttt{child}$ 边 $\texttt{BFS}$ 遍历，如果能到达 $B$，则 $A$ 是 $B$ 的祖先，距离 $p$ 即为 BFS 距离。反之亦然。

**2. 表亲关系判定**

从 $A$ 和 $B$ 分别沿 $\texttt{parent}$ 边向上 $\texttt{BFS}$，记录所有祖先及其距离。寻找共同祖先，对于每个共同祖先：

$$
m = \min(d_A, d_B) - 1,\quad n = |d_A - d_B|
$$

其中 $d_A$、$d_B$ 分别为 $A$、$B$ 到共同祖先的代数距离。在所有共同祖先中取 $m$ 最小、$m$ 相同时 $n$ 最小的作为最近关系。

### 输入处理

- `#` 开头：注释行，跳过
- `R` 开头：记录关系，前 $5$ 个字符为第一人，接下来 $5$ 个字符为第二人，后面跟整数 $k$
- `F` 开头：查询两人关系
- `E` 结尾：程序结束

注意人名固定为 $5$ 个字符，可能包含空格，需要正确处理。

## 算法复杂度

- 每次 BFS 时间复杂度：$O(V + E)$，其中 $V$ 为人数，$E$ 为关系数
- 总复杂度：$O(Q \cdot (V + E))$，$Q$ 为查询次数，在本题数据范围内可接受

## 代码实现

```cpp
// Kissin' Cousins
// UVa ID: 224
// Verdict: Accepted
// Submission Date: 2016-06-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 关系结构体：存储关联的人名和间隔代数
struct relation
{
    string name;  // 关联的人名
    int k;        // 关系距离（代数）
};

// child 存储从长辈到晚辈的有向边
// parent 存储从晚辈到长辈的有向边
map<string, vector<relation>> child;
map<string, vector<relation>> parent;

// 广度优先搜索，计算从起点 start 出发到各点的距离
// distances: 存储距离结果
// edges: 使用的边表（child 或 parent）
void bfs(string start, map<string, int>& distances, map<string, vector<relation>>& edges)
{
    set<string> visited;           // 已访问集合
    queue<string> unvisited;       // BFS 队列
    
    unvisited.push(start);
    visited.insert(start);
    distances[start] = 0;
    
    while (!unvisited.empty())
    {
        string name = unvisited.front();
        unvisited.pop();
        
        // 遍历所有邻接点
        for (auto r : edges[name])
        {
            if (visited.find(r.name) == visited.end())
            {
                unvisited.push(r.name);
                visited.insert(r.name);
                // 距离累加
                distances[r.name] = distances[name] + r.k;
            }
        }
    }
}

// 判断并输出直系后代关系
// 返回值：true 表示存在直系关系，false 表示不存在
bool is_descendant(string firstname, string secondname)
{
    map<string, int> first_distances, second_distances;
    
    // 分别从两人出发，沿 child 边向下搜索
    bfs(firstname, first_distances, child);
    bfs(secondname, second_distances, child);
    
    bool flag = false;
    
    // 情况1：firstname 是 secondname 的祖先
    if (first_distances.find(secondname) != first_distances.end())
    {
        flag = true;
        cout << setw(5) << left << firstname;
        cout << " and ";
        cout << setw(5) << left << secondname;
        
        if (first_distances[secondname] == 0)
            cout << " are cousin-0-0." << endl;
        else
            cout << " are descendant-" << first_distances[secondname] << "." << endl;
    }
    // 情况2：secondname 是 firstname 的祖先
    else if (second_distances.find(firstname) != second_distances.end())
    {
        flag = true;
        cout << setw(5) << left << firstname;
        cout << " and ";
        cout << setw(5) << left << secondname;
        
        if (second_distances[firstname] == 0)
            cout << " are cousin-0-0." << endl;
        else
            cout << " are descendant-" << second_distances[firstname] << "." << endl;
    }
    
    return flag;
}

// 判断并输出表亲关系
// 返回值：true 表示存在表亲关系，false 表示不存在
bool is_cousin(string firstname, string secondname)
{
    map<string, int> first_distances, second_distances;
    
    // 分别从两人出发，沿 parent 边向上搜索祖先
    bfs(firstname, first_distances, parent);
    bfs(secondname, second_distances, parent);
    
    bool flag = false;
    int m, n;
    
    // 遍历 firstname 的所有祖先
    for (auto p : first_distances)
    {
        // 如果该祖先也是 secondname 的祖先，则为共同祖先
        if (second_distances.find(p.first) != second_distances.end())
        {
            if (flag == false)
            {
                // 计算表亲参数
                m = min(p.second, second_distances[p.first]) - 1;
                n = abs(p.second - second_distances[p.first]);
            }
            else
            {
                int mm = min(p.second, second_distances[p.first]) - 1;
                int nn = abs(p.second - second_distances[p.first]);
                
                // 选择更近的关系
                if (mm < m || (mm == m && nn < n))
                    m = mm, n = nn;
            }
            
            flag = true;
        }
    }
    
    // 输出结果
    if (flag)
    {
        cout << setw(5) << left << firstname;
        cout << " and ";
        cout << setw(5) << left << secondname;
        cout << " are cousin-" << m << "-" << n << "." << endl;
    }
    
    return flag;
}

// 去除字符串首尾的空白字符
void trim(string & name)
{
    while (isblank(name.front()))
        name.erase(name.begin());
    while (isblank(name.back()))
        name.erase(name.end() - 1);
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    string line;
    while (getline(cin, line))
    {
        trim(line);
        
        // 遇到 'E' 结束程序
        if (line.front() == 'E')
            break;
        
        // '#' 开头的行是注释，跳过
        if (line.front() == '#')
            continue;
        
        string firstname, secondname;
        
        // 解析 R 或 F 行的人名
        if (line.front() == 'R' || line.front() == 'F')
        {
            // 前 5 个字符是第一人
            for (int i = 1; i <= 5; i++)
                firstname += line[i];
            trim(firstname);
            
            // 接下来 5 个字符是第二人
            for (int i = 6; i <= 10 && i < line.length(); i++)
                secondname += line[i];
            trim(secondname);
        }
        
        // 处理关系记录
        if (line.front() == 'R')
        {
            // 定位数字起始位置（跳过可能存在的空格）
            int start = 11;
            while (!isdigit(line[start]))
                start++;
            
            // 解析整数 k
            int k = 0;
            for (int i = start; i < line.length() && isdigit(line[i]); i++)
                k = k * 10 + (line[i] - '0');
            
            // 存储双向关系
            parent[firstname].push_back((relation){secondname, k});
            child[secondname].push_back((relation){firstname, k});
        }
        
        // 处理查询
        if (line.front() == 'F')
        {
            // 先检查直系后代关系
            if (is_descendant(firstname, secondname))
                continue;
            // 再检查表亲关系
            if (is_cousin(firstname, secondname))
                continue;
            
            // 无任何关系
            cout << setw(5) << left << firstname;
            cout << " and ";
            cout << setw(5) << left << secondname;
            cout << " are not related." << endl;
        }
    }
    
    return 0;
}
```
