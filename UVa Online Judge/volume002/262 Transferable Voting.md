[UVa 262 Transferable Voting](https://blog.csdn.net/metaphysis/article/details/161306647)

## 题目分析

本题模拟了一种特殊的选举计票系统——**可转移投票**（$\texttt{Transferable Voting}$）系统。在该系统中，选民需要对候选人进行排序投票，然后通过多轮计票和淘汰机制来确定最终的获胜者。

### 投票规则

1. **投票方式**：选民输入候选人编号（$1$、$2$、$3$ …）来表示偏好顺序。例如，“$2\ 5$”表示第一选择是 $2$ 号候选人，第二选择是 $5$ 号候选人。

2. **有效选票**：
   - 选票上的所有数字必须是有效的候选人编号。
   - 同一数字不能重复出现。
   - 满足上述条件的选票称为**有效选票**，否则为**废票**。

3. **计票规则**：
   - 每轮统计所有有效选票的**第一选择**（即选票上的第一个未被淘汰的候选人）。
   - 如果有候选人得票数超过有效选票总数的一半，则该候选人胜出。
   - 否则，淘汰得票最少的候选人（可能有多个），然后将这些候选人从所有选票中删除，相当于将选票上后面的候选人**提升**到前面。
   - 重复上述过程，直到产生胜者或所有候选人均被淘汰（选举无结果）。

4. **淘汰顺序**：如果一轮中有多名候选人同时被淘汰，按输入中候选人出现的顺序输出淘汰信息。

### 输入输出格式

**输入**：
- 第一行是测试用例个数。
- 每个测试用例包含候选人列表和选票列表，两者之间有一个空行。
- 候选人列表：每行格式为“编号. 姓名”，编号从 $1$ 开始递增。
- 选票列表：每行是若干空格分隔的整数，直到文件结束。

**输出**：
- 每轮淘汰信息。
- 最终结果（胜者或 `indecisive`）。
- 有效选票和废票统计。

## 解题思路

### 核心数据结构

```cpp
map<int, string> names;        // 编号 -> 候选人姓名
set<int> candidates;           // 所有候选人编号
vector<vector<int>> ballots; // 所有有效选票
int spoiled;                   // 废票计数
```

### 算法流程

#### 1. 读取候选人信息

读取每行直到空行，解析编号和姓名：
- 查找点号位置，分割编号和姓名
- 将编号映射到姓名，同时维护候选人集合

#### 2. 读取并验证选票

对于每张选票：
- 读取一行整数
- 检查每个数字是否在候选人集合中
- 检查是否有重复数字
- 如果验证通过，存入 `ballots`；否则 `spoiled++`

#### 3. 计票与淘汰循环

```cpp
while (true) {
    // 统计当前所有有效选票的第一选择
    map<int, int> counter;
    for (auto ballot : ballots) {
        if (!ballot.empty()) {
            counter[ballot.front()]++;
        }
    }
    
    // 计算最小得票和最大得票
    int minCounter = ballots.size(), maxCounter = 0;
    for (auto &p : counter) {
        minCounter = min(minCounter, p.second);
        maxCounter = max(maxCounter, p.second);
    }
    
    // 检查是否有胜者（得票超过一半）
    if (maxCounter > ballots.size() / 2) {
        // 输出胜者
        break;
    }
    
    // 找出所有得票最少的候选人
    vector<int> eliminated;
    for (auto &p : counter) {
        if (p.second == minCounter) {
            eliminated.push_back(p.first);
            candidates.erase(p.first);
            
            // 从所有选票中删除该候选人
            for (auto &ballot : ballots) {
                ballot.erase(remove(ballot.begin(), ballot.end(), p.first), ballot.end());
            }
        }
    }
    
    // 按编号排序后输出淘汰信息
    sort(eliminated.begin(), eliminated.end());
    for (int id : eliminated) {
        cout << names[id] << " with " << counter[id] << " votes is eliminated." << endl;
    }
    
    // 只剩一个候选人时自动胜出
    if (candidates.size() == 1) {
        cout << "The winner of the election is " << names[*candidates.begin()] << "." << endl;
        break;
    }
    
    // 没有候选人了
    if (candidates.empty()) {
        tie = true;
        break;
    }
}
```

### 关键细节处理

1. **选票更新**：淘汰候选人后，需要从所有选票中移除该编号，后续计票时直接取 `front()` 即可获得新的第一选择。

2. **自动胜出**：当只剩下 $1$ 名候选人时，无论其得票数是否过半，自动胜出。这需要特殊处理。

3. **边缘情况**：
   - 所有选票均为废票时，有效选票数量为 $0$，按规则应宣布选举无结果。
   - 无候选人的情况（输入格式错误时需注意）。

4. **输出顺序**：淘汰信息按候选人原始输入顺序输出，因此需要对编号排序。

## 代码实现

```cpp
// Transferable Voting 
// UVa ID: 262
// Verdict: Accepted
// Submission Date: 2016-06-08
// UVa Run Time: 0.070s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<int, string> names;          // 候选人编号到姓名的映射
vector< vector<int> > ballots;   // 存储所有有效选票
set<int> candidates;             // 当前未被淘汰的候选人集合
int spoiled;                     // 废票数量

// 核心计票函数
void voting()
{
    bool tie = false;            // 标志选举是否无结果
    while (true)
    {
        // 统计当前所有有效选票的第一选择得票数
        map<int, int> counter;
        for (auto i = candidates.begin(); i != candidates.end(); i++)
            counter[(*i)] = 0;
            
        for (auto i = ballots.begin(); i != ballots.end(); i++)
            if (!(*i).empty())
                counter[(*i).front()]++;
                
        // 找出当前得票的最小值和最大值
        int minCounter = ballots.size(), maxCounter = 0;
        for (auto i = counter.begin(); i != counter.end(); i++)
        {
            minCounter = min(minCounter, (*i).second);
            maxCounter = max(maxCounter, (*i).second);
        }

        // 如果有候选人得票超过有效票数的一半，胜出
        if (maxCounter > ballots.size() / 2)
        {
            for (auto i = counter.begin(); i != counter.end(); i++)
                if ((*i).second == maxCounter)
                {
                    cout << "The winner of the election is ";
                    cout << names[(*i).first] << "." << endl;
                    break;
                }
                
            break;
        }
        
        // 找出得票最少的候选人（可能有多人）
        vector <int> eliminated;
        for (auto i = counter.begin(); i != counter.end(); i++)
            if ((*i).second == minCounter)
            {
                eliminated.push_back((*i).first);
                candidates.erase((*i).first);
                
                // 从所有选票中移除被淘汰的候选人
                for (auto j = ballots.begin(); j != ballots.end(); j++)
                    for (int k = (*j).size() - 1; k >= 0; k--)
                        if ((*j)[k] == (*i).first)
                            (*j).erase((*j).begin() + k);
                            
            }
        
        // 按候选人原始顺序（编号顺序）输出淘汰信息
        sort(eliminated.begin(), eliminated.end());
        for (int i = 0; i < eliminated.size(); i++)
        {
            cout << names[eliminated[i]] << " with ";
            cout << counter[eliminated[i]] << " votes is eliminated." << endl;
        }
        
        // 如果只剩一名候选人，他自动胜出，无论得票数多少
        if (candidates.size() == 1)
        {
            cout << "The winner of the election is ";
            cout << names[*(candidates.begin())] << "." << endl;
            break;
        }
        
        // 没有候选人了，选举无结果
        if (candidates.empty())
        {
            tie = true;
            break;
        }
    }
    
    // 输出最终结果
    if (tie)
        cout << "The election was indecisive." << endl;
    cout << "There were " << ballots.size() << " valid ballots and ";
    cout << spoiled << " spoiled ballots." << endl;
    
}

int main(int argc, char *argv[])
{
    string line;
    int cases = (getline(cin, line), stoi(line));   // 读取测试用例个数
    
    // 读取第一个空行
    getline(cin, line);

    while (cases--)
    {
        // 读取候选人列表
        names.clear();
        candidates.clear();
        ballots.clear();
        while (getline(cin, line), line.length() > 0)
        {
            int index = line.find('.');
            int number = stoi(line.substr(0, index));
            string name = line.substr(index + 2);
            names.insert(make_pair(number, name));
            candidates.insert(number);
        }
        
        // 读取选票列表
        spoiled = 0;
        while (getline(cin, line))
        {
            if (line.length() > 0)
            {
                istringstream iss(line);
                vector<int> aBallot;
                set<int> existed;
                int number;
                bool is_spoiled = false;
                while (iss >> number)
                {
                    // 检查候选人编号是否有效且未重复出现
                    if (candidates.count(number) > 0 && existed.count(number) == 0)
                    {
                        aBallot.push_back(number);
                        existed.insert(number);
                    }
                    else
                    {
                        is_spoiled = true;
                        break;
                    }
                }
                
                if (is_spoiled == false)
                    ballots.push_back(aBallot);
                else
                    spoiled++;
            }
            else
                break;
        }
        
        // 处理只有一名候选人的特殊情况
        if (ballots.size() == 0 && names.size() == 1)
        {
            cout << "The winner of the election is ";
            cout << (*(names.begin())).second << "." << endl;
            cout << "There were 0 valid ballots and " << spoiled;
            cout << " spoiled ballots." << endl;
        }
        else
            voting();
        
        // 测试用例之间输出空行
        if (cases)
            cout << endl;
    }
    
	return 0;
}
```

## 复杂度分析

- **时间复杂度**：每轮淘汰至少一名候选人，最多 $n$ 轮（$n$ 为候选人数）。每轮遍历所有有效选票（最多 $1000$ 张）和每张选票上的偏好（最多 $n$ 个），总体复杂度为 $O(n^2 \cdot m)$，其中 $m$ 为选票数。在题目限制下完全可以接受。

- **空间复杂度**：$O(n \cdot m)$，存储所有选票信息。
