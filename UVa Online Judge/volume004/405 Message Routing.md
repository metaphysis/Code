[UVa 405 Message Routing](https://blog.csdn.net/metaphysis/article/details/161736854)

## 题目描述

题目模拟了 $\texttt{x.400}$ 消息处理系统中 $\texttt{MTA}$（$\texttt{Message Transfer Agent}$，消息传输代理）的路由功能。每个 $\texttt{MTA}$ 维护一个路由表，用于根据消息的 $\texttt{O/R}$ 名称（$\texttt{Originator/Recipient name}$，发件人/收件人名称）将消息转发到下一个 $\texttt{MTA}$ 或本地投递。

$\texttt{O/R}$ 名称由四个组件组成，按范围从宽到窄依次为：
- **$\texttt{C}$（$\texttt{Country}$，国家）**
- **$\texttt{ADMD}$（$\texttt{Administrative Management Domain}$，行政管理域）**
- **$\texttt{PRMD}$（$\texttt{Private Management Domain}$，私有管理域）**
- **$\texttt{O}$（$\texttt{Organization Name}$，组织名称）**

每个 $\texttt{MTA}$ 的路由表包含若干条目，每个条目指向一个相邻 $\texttt{MTA}$，并包含四个组件的匹配模式。匹配模式可以是具体字符串，也可以是通配符 `*`（匹配任意内容）。路由时，按从上到下的顺序查找第一个匹配的条目，然后将消息转发到该条目指定的 $\texttt{MTA}$。

路由可能出现的三种结果：
1. **本地投递**：如果匹配到的 $\texttt{MTA}$ 就是当前 $\texttt{MTA}$ 本身，则消息被成功投递。
2. **循环路由**：如果检测到消息曾经经过同一个 $\texttt{MTA}$（即形成环路），则产生循环路由错误。
3. **无法路由**：如果路由表中没有任何条目匹配消息的 $\texttt{O/R}$ 名称，则产生无法路由错误。

## 输入格式

每个测试场景（$\texttt{scenario}$）的输入格式如下：
- 第一行一个整数 $M$（$1 \le M \le 10$），表示该场景中 $\texttt{MTA}$ 的数量。
- 接下来依次描述每个 $\texttt{MTA}$：
  - 一行包含 $\texttt{MTA}$ 名称（$1$ 到 $10$ 个字母，左对齐，无空格）和整数 $I$（$0 \le I \le 9$），表示该 $\texttt{MTA}$ 路由表的条目数。$\texttt{MTA}$ 名称占第 $1$ 到 $10$ 列，$I$ 在第 $12$ 列。
  - 接下来 $I$ 行，每行包含：相邻 $\texttt{MTA}$ 名称（第 $1$ 到 $10$ 列），以及四个 $\texttt{O/R}$ 组件（分别在第 $15$ 到 $24$ 列、第 $30$ 到 $39$ 列、第 $45$ 到 $54$ 列、第 $60$ 到 $69$ 列）。每个组件由 $1$ 到 $10$ 个字母组成，或为单个星号 `*`（通配符）。
- 所有 $\texttt{MTA}$ 描述结束后，一行包含一个整数 $N$（$0 < N < 32768$），表示消息的数量。
- 接下来 $N$ 行，每行描述一条消息：起始 $\texttt{MTA}$ 名称（第 $1$ 到 $10$ 列）和四个 $\texttt{O/R}$ 组件（列位置同上）。消息从该起始 $\texttt{MTA}$ 开始模拟路由。

## 输出格式

对于每个场景，首先输出一行 `Scenario # X`，其中 $X$ 从 $1$ 开始递增。接下来 $N$ 行，每行对应一条消息，格式为：
```
消息编号 -- 结果描述
```
结果描述为以下三种之一：
- `delivered to MTA_NAME`
- `circular routing detected by MTA_NAME`
- `unable to route at MTA_NAME`

其中 `MTA_NAME` 替换为生成报告的 $\texttt{MTA}$ 名称。每条消息输出后，在场景末尾输出一个空行。

## 样例

输入

```
5
NAULINS   3
HOUSTON   US       SHIP     *        UH
DOWNTOWN  NAULINS  US       SHIP     *        UNO
DALLAS    US       AIR      UT       *
HOUSTON   4
HOUSTON   US       *        UH       UHDT
SANANTONIO US      BUS      UT       UTSA
DALLAS    US       AIR      UT       *
NAULINS   US       SHIP     *        UNO
DALLAS    7
DALLAS    US       *        UT       TDD
DALLAS    US       *        UT       TDA
HOUSTON   US       *        UH       *
SANANTONIO US      AIR      UT       UTSA
OKLAHOMA  US       BUS      *        OU
NAULINS   US       AIR      *        UNO
HOUSTON   US       SHIP     **
OKLAHOMA  3
OKLAHOMA  US       **       OU
DALLAS    US       AIR      **
SANANTONIO US      BUS      **
SANANTONIO 5
HOUSTON   ***      UNO
HOUSTON   US       BUS      UH       *
DALLAS    US       AIR      **
SANANTONIO US      *        UT       UTSA
OKLAHOMA  US       BUS      UH       UHDT
5
SANANTONIO US       AIR      COLLEGE  UNO
OKLAHOMA  US       BUS      UH       UHDT
DALLAS    US       SHIP     COLLEGE  UNO
NAULINS   US       AIR      COLLEGE  OU
HOUSN     US       AIR      UT       UTSA
```

输出

```
Scenario # 1
1 -- unable to route at HOUSTON
2 -- delivered to HOUSTON
3 -- delivered to NAULINS
4 -- unable to route at NAULINS
5 -- circular routing detected by DALLAS

```

## 题目分析

本题的核心是实现一个**多 $\texttt{MTA}$ 路由模拟系统**，需要处理路由表的匹配规则、循环检测和错误处理。

### 路由匹配规则

每个 $\texttt{MTA}$ 的路由表是一个有序列表（从上到下）。对于给定的消息 $\texttt{O/R}$ 名称 $(C, \textit{ADMD}, \textit{PRMD}, O)$，依次检查每个路由条目，匹配条件为：
- 条目的国家组件等于消息的国家组件，**或者**条目国家为 `*`
- **且** 条目的 $\textit{ADMD}$ 组件等于消息的 $\textit{ADMD}$，**或者**为 `*`
- **且** 条目的 $\textit{PRMD}$ 组件等于消息的 $\textit{PRMD}$，**或者**为 `*`
- **且** 条目的组织组件等于消息的组织组件，**或者**为 `*`

四个条件同时满足时，该条目匹配成功。注意 `*` 匹配任意内容（包括空？题目未明确空值情况，但所有组件均为 $1$ 到 $10$ 个字母，无空组件）。

### 路由流程

从起始 $\texttt{MTA}$ 开始，重复以下步骤：
1. 在当前 $\texttt{MTA}$ 的路由表中，按顺序查找第一个匹配的条目。
2. 如果找不到匹配条目 → **无法路由**，报告当前 $\texttt{MTA}$。
3. 如果找到匹配条目：
   - 如果目标 $\texttt{MTA}$ 就是当前 $\texttt{MTA}$ → **本地投递成功**。
   - 否则，检查是否曾经过目标 $\texttt{MTA}$（循环检测）：
     - 如果曾经经过 → **循环路由错误**，报告目标 $\texttt{MTA}$。
     - 否则，记录当前 $\texttt{MTA}$ 为已访问，移动到目标 $\texttt{MTA}$，继续循环。

### 循环检测

循环检测需要记录**已经访问过的 $\texttt{MTA}$**，但注意：**是在消息的整个路由路径中，一个 $\texttt{MTA}$ 不能出现两次**。一旦第二次到达同一个 $\texttt{MTA}$，即检测到循环。

实现时，可以用一个 $\texttt{set}$ 或 $\texttt{unordered_set}$ 记录已经经过的 $\texttt{MTA}$。每次准备转发到下一个 $\texttt{MTA}$ 时，先检查该目标 $\texttt{MTA}$ 是否已在集合中：
- 如果在 → 循环路由，报告**目标 $\texttt{MTA}$**（即检测到循环的 $\texttt{MTA}$）。
- 如果不在 → 将当前 $\texttt{MTA}$ 加入集合，然后移动到目标 $\texttt{MTA}$。

注意：起始 $\texttt{MTA}$ 是否应预先加入集合？根据题目描述“If an MTA detects that it has received a message that it has handled before”，检测发生在 $\texttt{MTA}$ 接收到消息时。因此，在进入一个新的 $\texttt{MTA}$ 时，应该先检查该 $\texttt{MTA}$ 是否已在历史中。但更简便的实现是在准备转发到下一个 $\texttt{MTA}$ 时检查目标是否已访问过（因为当前 $\texttt{MTA}$ 已经处理过，即将离开）。

参考代码的实现是在匹配到目标 $\texttt{MTA}$ 后，检查目标 $\texttt{MTA}$ 是否在 $\texttt{routed}$ 集合中（该集合记录的是已经处理过的 $\texttt{MTA}$）。注意它将当前 $\texttt{MTA}$ 加入集合，然后移动到目标 $\texttt{MTA}$。这种实现是正确的。

## 代码实现

```cpp
// Message Routing
// UVa ID: 405
// Verdict: Accepted
// Submission Date: 2016-08-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct entry
{
    string mta, country, admd, prmd, o;
};

map<string, vector<entry>> tables;

void routing(entry r)
{
    set<string> routed;
    
    while (true)
    {
        bool mta_found = false;
        for (auto t : tables[r.mta])
        {
            bool matched = t.country == r.country || t.country == "*";
            matched = matched && (t.admd == r.admd || t.admd == "*");
            matched = matched && (t.prmd == r.prmd || t.prmd == "*");
            matched = matched && (t.o == r.o || t.o == "*");
            
            if (matched)
            {
                mta_found = true;
                if (routed.find(t.mta) != routed.end())
                {
                    cout << "circular routing detected by " << t.mta << '\n';
                    return;
                }
                else if (t.mta == r.mta)
                {
                    cout << "delivered to " << r.mta << '\n';
                    return;
                }
                else
                {
                    routed.insert(r.mta);
                    r.mta = t.mta;
                }
                break;
            }
        }
        
        if (mta_found == false)
        {
            cout << "unable to route at " << r.mta << '\n';
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int M, I, N, cases = 0;
    string mta, next_mta, country, admd, prmd, o;
    
    while (cin >> M)
    {
        tables.clear();
        for (int i = 1; i <= M; i++)
        {
            cin >> mta >> I;
            for (int j = 1; j <= I; j++)
            {
                cin >> next_mta >> country >> admd >> prmd >> o;
                tables[mta].push_back((entry){next_mta, country, admd, prmd, o});
            }
        }
        
        cout << "Scenario # " << ++cases << '\n';

        cin >> N;
        for (int i = 1; i <= N; i++)
        {
            cin >> next_mta >> country >> admd >> prmd >> o;
            cout << i << " -- ";
            
            routing((entry){next_mta, country, admd, prmd, o});
        }

        cout << '\n';
    }
    
    return 0;
}
```