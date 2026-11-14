[UVa 349 Transferable Voting (II)](https://blog.csdn.net/metaphysis/article/details/161557739)

## 题目描述

可转移投票制（$\texttt{Transferable Vote}$）要求获胜候选人获得**绝对多数**（超过一半）的选票。为了实现这一目标，每位选民按偏好顺序列出所有候选人。因此，如果有 $c$ 位候选人竞争一个职位，每位选民的选票必须包含 $c$ 个选择，从第一选择到第 $c$ 选择。

在本题中，需要判断选举的获胜者（如果有的话）。无效选票将被丢弃，但会记录其数量。选票无效的情况包括：
- 选择不唯一（不能将同一候选人列为第一和第二选择）
- 任何选择不合法（不在 $1$ 到 $c$ 范围内）

### 选举规则

1. 计算有效选票数，获胜所需票数为 $\lfloor \text{有效选票数}/2 \rfloor + 1$
2. 统计每位候选人的第一选择票数
3. 如果有候选人获得足够票数，该候选人获胜
4. 否则，淘汰第一选择票数最少的候选人（如有多个并列最少，选择任意一个淘汰）
5. 将被淘汰候选人的选票转移给这些选票上的下一个有效选择
6. 重复步骤 2-5 直到产生获胜者或出现平局

### 输入格式

每个选举以一行包含 $c$（候选人数量）和 $n$（选民数量）开始。最后一个选举后跟一行 `0 0`。接下来 $n$ 行，每行包含 $c$ 个非负整数（每位选民的偏好顺序）。

### 输出格式

对于每个选举：
- 输出选举编号
- 如果有无效选票，输出无效选票数量
- 输出获胜者或平局信息

### 样例输入

```
3 12
1 2 4
1 3 2
3 2 1
3 2 1
1 2 3
2 3 1
3 2 1
3 1 1
3 2 1
1 2 3
1 3 2
2 3 1
3 12
1 2 4
1 3 2
3 2 1
3 2 1
1 2 3
2 3 1
3 2 1
3 1 1
3 2 1
1 2 3
1 3 2
2 3 1
3 2 1
3 1 1
3 2 1
1 2 3
1 3 2
2 1 3
4 15
4 3 1 2
4 1 2 3
3 1 4 2
1 3 2 4
4 1 2 3
3 4 2 1
2 4 3 1
3 2 1 4
3 1 4 2
1 4 2 3
3 4 1 2
3 2 1 4
4 1 3 2
3 2 1 4
4 2 1 4
0 0
```

### 样例输出

```
Election #1
   2 bad ballot(s)
   Candidate 3 is elected.
Election #2
   2 bad ballot(s)
   The following candidates are tied: 1 3
Election #3
   1 bad ballot(s)
   Candidate 3 is elected.
```

---

## 题目分析

### 问题的本质

这是一个**即时决选投票**（$\texttt{Instant-Runoff Voting}$）或**排序投票**的模拟问题。需要按照可转移投票制规则模拟选举过程。

### 关键步骤

1. **选票验证**：检查每张选票是否包含 $1$ 到 $c$ 的每个数字恰好一次
2. **统计第一选择**：统计每张选票当前首选候选人的票数
3. **获胜判定**：如果有候选人得票超过半数，获胜
4. **淘汰最低得票者**：找出得票最少的候选人（可能多个）
5. **转移选票**：将被淘汰候选人的选票中的第一选择移除，下一选择成为新的第一选择
6. **平局处理**：如果所有剩余候选人得票相同，则平局

### 特殊情况

- $c = 1$：只有一个候选人，直接获胜
- 所有选票都无效：没有有效选票，无法产生获胜者（但题目未明确，实际不会发生）

---
## 参考代码

```cpp
// Transferable Voting (II)
// UVa ID: 349
// Verdict: Accepted
// Submission Date: 2016-07-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int c, n, cases = 0;
    while (cin >> c >> n)
    {
        if (c == 0 && n == 0) break;
        
        int selected, invalidVotes = 0;
        vector<vector<int>> votes;  // 存储有效选票
        
        // 读取并验证选票
        for (int i = 1; i <= n; i++)
        {
            set<int> cache;          // 用于检测重复
            vector<int> aVote;
            bool invalid = false;
            
            for (int j = 1; j <= c; j++)
            {
                cin >> selected;
                if (selected > c || selected == 0 || cache.count(selected) > 0)
                    invalid = true;
                else
                {    
                    aVote.push_back(selected);
                    cache.insert(selected);
                }
            }
            
            if (invalid)
                invalidVotes++;
            else
                votes.push_back(aVote);
        }
        
        // 输出选举编号和无效选票数
        cout << "Election #" << ++cases << endl;
        if (invalidVotes > 0)
            cout << "   " << invalidVotes << " bad ballot(s)" << endl;
        
        // 特殊情况：只有一个候选人
        if (c == 1)
        {
            cout << "   Candidate 1 is elected." << endl;
            continue;
        }
        
        // 获胜所需票数
        int totalVotes = votes.size() / 2 + 1;
        map<int, int> voteCounter;

        // 模拟选举过程
        while (true)
        {
            int lowest = votes.size();  // 当前最低得票数
            voteCounter.clear();
            
            // 统计第一选择票数
            for (int i = 0; i < votes.size(); i++)
                if (votes[i].size())
                    voteCounter[votes[i].front()]++;

            // 检查是否有获胜者
            bool winnerIsHere = false;
            for (auto counter : voteCounter)
            {
                lowest = min(lowest, counter.second);
                if (counter.second >= totalVotes)
                {
                    winnerIsHere = true;
                    cout << "   Candidate " << counter.first << " is elected." << endl;
                    break;
                }
            }

            if (winnerIsHere)
                break;
            
            // 检查是否平局
            bool tie = true;
            for (auto counter : voteCounter)
                if (counter.second != lowest)
                {
                    tie = false;
                    break;
                }
                
            if (tie)
            {
                cout << "   The following candidates are tied:";
                for (auto counter : voteCounter)
                    cout << " " << counter.first;
                cout << endl;
                break;
            }
            
            // 淘汰得票最少的候选人（每次只淘汰一个）
            for (auto counter : voteCounter)
                if (counter.second == lowest)
                {
                    // 将被淘汰候选人的选票中的第一选择移除
                    for (int i = 0; i < votes.size(); i++)
                        if (votes[i].front() == counter.first)
                            votes[i].erase(votes[i].begin());
                    break;  // 每次只淘汰一个候选人
                }
        }
    }
    
    return 0;
}
```
