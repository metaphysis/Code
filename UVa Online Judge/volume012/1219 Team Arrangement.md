
> **摘要**：本题要求从 $22$ 名候选球员中，按照给定阵型（如 $4$-$4$-$2$）为守门员、后卫、中场、前锋四个位置各选出规定人数，共 $11$ 人。选人时每个位置按球员编号升序取前若干名；随后从入选球员中选出效力记录最长者作为队长（记录长度相同则取编号较大者）。输出时队长置于首行，其余球员按守门员、后卫、中场、前锋的顺序、同位置内按编号升序排列；若某位置人数不足则输出 `IMPOSSIBLE TO ARRANGE`。核心处理包括年份区间并集统计、按编号扫描选人、队长排序与最终输出排序，整体为常数级复杂度。

# 题目描述

足球队共有 $22$ 名候选球员，每名球员具有以下信息：

- 球员编号；
- 球员姓名；
- 场上位置，包括守门员、后卫、中场和前锋；
- 在球队效力的若干年份区间。

教练给出一种比赛阵型，例如 $4$-$4$-$2$，表示需要选择 $4$ 名后卫、$4$ 名中场和 $2$ 名前锋，同时还需要选择 $1$ 名守门员。

对于每个位置，按照球员编号从小到大的顺序选择球员。选出全部球员后，从入选球员中确定队长。队长是效力记录最长的球员；如果多名球员的效力记录长度相同，则选择编号较大的球员。

要求输出最终选中的 $11$ 名球员。队长必须输出在第一行，其余球员按照守门员、后卫、中场、前锋的顺序排列，同一位置内按照编号升序排列。如果无法按照指定阵型组建球队，则输出 `IMPOSSIBLE TO ARRANGE`。

# 输入格式

输入包含多组测试数据。

每组测试数据首先包含 $22$ 行球员信息，每行格式如下：

```text
number name role year1-year1' year2-year2' ...
```

其中：

- `number` 表示球员编号，是小于 $100$ 的正整数；
- `name` 表示球员姓名，只包含字母，长度不超过 $20$；
- `role` 表示球员位置，取值为 $\texttt{G}$、$\texttt{D}$、$\texttt{M}$、$\texttt{S}$，分别表示守门员、后卫、中场和前锋；
- 每个年份区间表示球员在球队效力的连续年份，区间两端均包含在内；
- 每名球员至少有一个、最多有 $20$ 个年份区间；
- 同一名球员的年份列表中不会重复出现同一年。

接下来一行表示所需阵型，格式为：

```text
defenders-midfielders-strikers
```

其中三个数字分别表示后卫、中场和前锋人数，三者之和为 $10$，且每个数字都不为 $0$。守门员人数固定为 $1$。

输入以单独一行的 `0` 结束。

# 输出格式

对于每组测试数据：

- 如果可以组建球队，首先输出队长的信息，之后输出其他球员的信息；
- 每行输出球员编号、姓名和位置，字段之间使用一个空格；
- 队长必须位于整个输出列表的第一行；
- 其他球员按照守门员、后卫、中场、前锋的顺序输出，同一位置内按照编号升序输出；
- 如果无法完成阵型，输出 `IMPOSSIBLE TO ARRANGE`。

每组测试数据输出结束后，还需要额外输出一个空行。

# 样例输入

```text
9 PlayerA M 2000-2001 2003-2006
2 PlayerB M 2004-2006
10 PlayerC D 2001-2005
1 PlayerD D 2000-2001 2002-2004
11 PlayerE S 2003-2006
8 PlayerF M 2005-2006
22 PlayerG S 2005-2006
25 PlayerH G 2000-2001 2002-2003 2005-2006
6 PlayerI D 2003-2006
26 PlayerJ D 2003-2004 2000-2001
18 PlayerK M 2003-2004
19 PlayerL M 2000-2001 2003-2006
7 PlayerM S 2003-2006 1999-2001
21 PlayerN S 2003-2006
13 PlayerO S 2005-2006
15 PlayerP G 2001-2006
14 PlayerQ D 2003-2004
5 PlayerR S 2000-2005
20 PlayerS G 2000-2002 2003-2003
12 PlayerT M 2004-2005
3 PlayerU D 2000-2005
4 PlayerV M 2001-2004
4-4-2
0
```

# 样例输出

```text
7 PlayerM S
15 PlayerP G
1 PlayerD D
3 PlayerU D
6 PlayerI D
10 PlayerC D
2 PlayerB M
4 PlayerV M
8 PlayerF M
9 PlayerA M
5 PlayerR S

```

# 题目分析

本题的处理过程分为球员信息解析、按位置选人、确定队长和排序输出四个部分。

首先需要解析每名球员的效力年份。一个球员可能拥有多个年份区间，例如 $2000$-$2001$ 和 $2003$-$2006$。球员的效力记录长度等于所有区间并集中的年份数量，因此不能简单地将每个区间长度直接相加。代码使用数组 `year` 标记球员是否在某一年效力过，然后统计数组中被标记的年份数量，从而正确处理多个区间之间可能存在的重叠情况。

接着按照球员编号升序排列全部球员。由于题目要求每个位置的球员按照编号升序选择，因此在已经排好序的球员列表中从前往后扫描即可。对于每名球员，根据其位置判断是否还需要该位置的球员：

- 后卫数量未达到阵型要求且当前球员是后卫时，选择该球员；
- 中场数量未达到阵型要求且当前球员是中场时，选择该球员；
- 前锋数量未达到阵型要求且当前球员是前锋时，选择该球员；
- 守门员数量未达到 $1$ 且当前球员是守门员时，选择该球员。

由于扫描顺序是编号升序，且同一位置只选择前若干名球员，所以得到的球员正好满足题目的选人规则。

如果某个位置的候选人数不足，则无法完成阵型。此时直接输出 `IMPOSSIBLE TO ARRANGE`。只有守门员、后卫、中场和前锋人数都满足要求时，才进入队长确定阶段。

队长的比较规则是效力记录长度优先，记录长度越长越优先；记录长度相同时，编号越大的球员越优先。因此可以使用如下排序规则：

$$
record_a > record_b
$$

或者在记录长度相同时：

$$
number_a > number_b
$$

将入选球员按照这个规则排序后，排在最前面的球员就是队长。

确定队长后，将队长从球队列表中删除。剩余球员按照位置顺序和编号升序排序。代码中将位置映射为 $\texttt{G}$、$\texttt{D}$、$\texttt{M}$、$\texttt{S}$ 对应的下标 $0$、$1$、$2$、$3$，因此按照位置下标升序排序即可得到题目要求的输出顺序。

# 解题思路

首先读取当前测试数据的第一行。若该行仅包含 `0`，则所有输入结束；否则将这一行作为第一名球员的信息进行解析，然后继续读取剩余的 $21$ 名球员。

解析球员信息时，读取编号、姓名和位置。对于后续的每个年份区间，分别读取起始年份和结束年份，并将区间内的所有年份标记为有效年份。全部区间处理结束后，统计有效年份的数量，作为该球员的效力记录长度。

完成 $22$ 名球员的信息读取后，将球员按照编号升序排列。再读取阵型中的三个数字，分别保存为后卫人数、中场人数和前锋人数，守门员人数固定为 $1$。

从编号最小的球员开始扫描：

- 如果当前球员属于某个位置，并且该位置还没有达到要求人数，则将其加入球队；
- 如果该位置已经达到要求人数，则跳过当前球员；
- 扫描完成后，检查四个位置的实际人数是否分别满足阵型要求。

如果人数不足，则输出无法组建球队的信息，并输出一个空行。否则将球队中的球员按照队长比较规则排序，取第一名作为队长并输出。

将队长从列表中移除后，按照位置优先级和编号升序重新排序剩余球员。依次输出剩余球员，并在当前测试数据末尾输出一个空行。

设每组测试数据固定包含 $22$ 名球员。解析年份时，代码使用长度为 $10000$ 的数组，因此每名球员的年份统计时间复杂度为 $O(10000)$。球员排序的时间复杂度为 $O(22\log 22)$，选人扫描和最终排序的时间复杂度同样不超过 $O(22\log 22)$。因此每组测试数据的总时间复杂度为 $O(22\times 10000+22\log 22)$，可以视为常数级处理。空间复杂度为 $O(10000+22)$，其中 $10000$ 用于年份标记，$22$ 用于保存球员信息。

# 代码实现

```cpp
// Team Arrangement
// UVa ID: 1219
// Verdict: Accepted
// Submission Date: 2018-03-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int G = 0, D = 1, M = 2, S = 3;

string roleText = "GDMS";
map<char, int> roleIdx = {{'G', 0}, {'D', 1}, {'M', 2}, {'S', 3}};

struct player
{
    string name;
    int number, role, record;

    bool operator<(const player &p) const
    {
        return number < p.number;
    }
};

bool cmpCaptain(player p1, player p2)
{
    if (p1.record != p2.record)
        return p1.record > p2.record;
    return p1.number > p2.number;
}

bool cmpMember(player p1, player p2)
{
    if (p1.role != p2.role)
        return p1.role < p2.role;
    return p1.number < p2.number;
}

player parse(string line)
{ 
    player aPlayer;

    char letter;
    istringstream iss(line);
    iss >> aPlayer.number >> aPlayer.name >> letter;
    aPlayer.role = roleIdx[letter];

    int year[10000] = {0}, start, end;
    while (iss >> start >> letter >> end)
    {
        for (int i = start; i <= end; i++)
            year[i] = 1;
    }
    aPlayer.record = count(year, year + 10000, 1);

    return aPlayer;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    vector<player> players;

    while (getline(cin, line))
    {
        if (line == "0") break;
        players.clear();
        players.push_back(parse(line));
        for (int i = 2; i <= 22; i++)
        {
            getline(cin, line);
            players.push_back(parse(line));
        }
        sort(players.begin(), players.end());

        getline(cin, line);
        istringstream iss(line);

        char dash;
        int defenders, midfielders, strikers, goalkeepers = 1;
        iss >> defenders >> dash >> midfielders >> dash >> strikers;
        
        vector<player> team;
        int dcnt = 0, mcnt = 0, scnt = 0, gcnt = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (dcnt < defenders && players[i].role == D)
            {
                team.push_back(players[i]);
                dcnt++;
            }
            if (mcnt < midfielders && players[i].role == M)
            {
                team.push_back(players[i]);
                mcnt++;
            }
            if (scnt < strikers && players[i].role == S)
            {
                team.push_back(players[i]);
                scnt++;
            }
            if (gcnt < goalkeepers && players[i].role == G)
            {
                team.push_back(players[i]);
                gcnt++;
            }
        }
        
        if (dcnt != defenders || mcnt != midfielders || scnt != strikers || gcnt != goalkeepers)
        {
            cout << "IMPOSSIBLE TO ARRANGE\n\n";
            continue;
        }
        
        sort(team.begin(), team.end(), cmpCaptain);
        player captain = team.front();
        cout << captain.number << ' ' << captain.name << ' ' << roleText[captain.role] << '\n';

        team.erase(team.begin());
        sort(team.begin(), team.end(), cmpMember);
        for (auto member : team)
            cout << member.number << ' ' << member.name << ' ' << roleText[member.role] << '\n';
        cout << '\n';
    }

    return 0;
}
```

# 总结

本题的关键在于严格按照题目规定完成三种排序和选择：

- 先按球员编号升序扫描，分别选出各个位置最靠前的球员；
- 再按效力记录长度降序、编号降序确定队长；
- 最后按守门员、后卫、中场、前锋的顺序，并在同一位置内按编号升序输出。

年份记录必须通过逐年标记统计，才能正确处理多个年份区间。阵型可行性只需要检查四个位置的人数是否全部满足要求。整个过程不需要复杂算法，使用结构体保存球员信息并配合多次排序即可完成。
