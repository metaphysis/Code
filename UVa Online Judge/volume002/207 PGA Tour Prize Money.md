[UVa 207 PGA Tour Prize Money](https://blog.csdn.net/metaphysis/article/details/161010071)

#）题解

## 题目分析

本题是一个高尔夫球赛奖金分配问题。题目要求根据给定的总奖金（`purse`）、前 $70$ 名的奖金百分比、以及球员的比赛成绩，计算出最终获得奖金的球员名单及其应得的奖金金额。

主要规则如下：

1. 所有球员至少完成前两轮（$36$ 洞），除非被 `DQ`（取消资格）。
2. 前两轮结束后，取前 $70$ 名（含并列）晋级后两轮。
3. 晋级球员再打两轮，按 $72$ 洞总成绩排名分配奖金。
4. 奖金百分比已给定，且总和为 $100\%$。
5. 业余球员（名字后有 `*`）不能获得奖金，其“赢得”的奖金顺延给下一位非业余球员。
6. 若有并列，将对应名次的奖金池平分给并列的非业余球员。
7. 若晋级后有人 `DQ`，则只分配实际完赛的名次奖金。
8. 只输出晋级后两轮的球员，以及 `DQ` 球员（放在最后，总分栏填 `DQ`）。

## 解题思路

### 数据结构设计

定义一个结构体 `player` 存储每位球员的信息：

- 姓名、四轮成绩、总成绩、排名、完成轮数
- 是否为业余、是否并列、是否获奖、奖金金额

### 主要步骤

1. **读取输入**  
   - 先读测试用例数。
   - 对于每个用例，读入总奖金 `money` 和前 $70$ 名的奖金百分比（转换为小数存储）。
   - 读入球员人数，再逐行读取每个球员的信息，调用 `parseToPlayer` 解析成绩和业余标识。

2. **第一轮筛选（$36$ 洞晋级）**  
   - 计算完成至少两轮球员的前两轮总成绩。
   - 按总成绩升序排序，取前 $70$ 名（含并列第 $70$ 名）。

3. **第二轮筛选（$72$ 洞完赛）**  
   - 晋级球员中，完成四轮的进入最终排名。
   - 未完成四轮的放入 `DQ` 列表。

4. **奖金分配**  
   - 按 $72$ 洞总成绩升序排序。
   - 按非业余球员顺序分配奖金百分比（跳过业余）。
   - 处理并列：同一成绩的球员中，将对应名次的百分比之和除以非业余人数，再乘以总奖金。
   - 业余球员不参与奖金分配，也不在排名后加 `T`。

5. **输出**  
   - 先输出获奖球员（按排名顺序），格式严格按题目要求。
   - 再输出 `DQ` 球员（按完成轮数降序、总成绩升序、姓名升序）。

### 细节注意

- 奖金百分比读入时需除以 $100$，输出时再乘以总奖金。
- 美元金额保留两位小数。
- 并列标志 `T` 仅当 **两个或以上非业余球员** 成绩相同时才添加。
- `DQ` 球员的 `TOTAL` 列输出 `DQ`，其余轮次成绩为空（不输出数字）。
- 多用例之间输出一个空行。

## 代码实现

```cpp
// PGA Tour Prize Money
// UVa ID: 207
// Verdict: Accepted
// Submission Date: 2016-04-26
// UVa Run Time: 0.050s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int DQ = -1;  // 表示取消资格或未完成该轮

struct player {
    string name;      // 球员姓名
    int rd1, rd2, rd3, rd4; // 四轮成绩
    int total;        // 总成绩（36洞或72洞）
    int place;        // 最终排名
    int round;        // 完成的轮数
    bool amateur;     // 是否为业余球员
    bool tie;         // 是否为并列（仅非业余）
    bool prized;      // 是否获得奖金
    double prize;     // 奖金金额
};

bool printBlankLine = false;  // 控制用例间空行
vector < player > players;    // 所有球员
vector < double > percents;   // 前70名的奖金百分比（小数形式）
double money;                 // 总奖金

// 按总成绩升序，相同则按姓名升序
bool cmp(player a, player b) {
    if (a.total == b.total) return a.name < b.name;
    else return a.total < b.total;
}

// 用于DQ球员排序：先按完成轮数降序，再按cmp
bool cmp2(player a, player b) {
    if (a.round == b.round) return cmp(a, b);
    else return a.round > b.round;
}

// 主处理函数：筛选、分配奖金、输出
void allocate() {
    if (printBlankLine) cout << "\n";
    else printBlankLine = true;
        
    // 打印表头
    cout << setw(21) << left << "Player Name";
    cout << setw(10) << left << "Place";
    cout << setw(5) << left << "RD1";
    cout << setw(5) << left << "RD2";
    cout << setw(5) << left << "RD3";
    cout << setw(5) << left << "RD4";
    cout << setw(10) << left << "TOTAL";
    cout << "Money Won\n";
    cout << "-----------------------------------------------------------------------\n";
    
    // ---- 36洞晋级筛选 ----
    vector < player > dq;
    vector < player > firstcut;
    for (int i = 0; i < players.size(); i++)
        if (players[i].round >= 2) {
            players[i].total = players[i].rd1 + players[i].rd2;
            firstcut.push_back(players[i]);
        }
       
    sort(firstcut.begin(), firstcut.end(), cmp);
    // 取前70名（含并列）
    if (firstcut.size() > 70) {
        int last;
        for (last = 70; last < firstcut.size(); last++)
            if (firstcut[last].total == firstcut[69].total) continue;
            else break;
        firstcut.erase(firstcut.begin() + last, firstcut.end());
    }
    
    // ---- 72洞完赛筛选 ----
    vector < player > secondcut;
    for (int i = 0; i < firstcut.size(); i++) {
        if (firstcut[i].round >= 4) {
            firstcut[i].total += (firstcut[i].rd3 + firstcut[i].rd4);
            firstcut[i].prized = false;
            firstcut[i].tie = false;
            secondcut.push_back(firstcut[i]);
        } else dq.push_back(firstcut[i]);  // 晋级但未完成全部四轮
    }
    sort(secondcut.begin(), secondcut.end(), cmp);
    
    // ---- 分配奖金百分比（跳过业余） ----
    for (int i = 0, index = 0; i < secondcut.size() && index < 70; i++)
        if (!secondcut[i].amateur) {
            secondcut[i].prize = percents[index++];
            secondcut[i].prized = true;
        }
    
    // ---- 处理并列及最终奖金计算 ----
    for (int i = 0, place = 1; i < secondcut.size();) {
        int counter = 0, prizedPlayers = 0, noAmateurs = 0;
        double prizeAllocate = 0.0;
        // 统计相同成绩的球员
        while ((i + counter) < secondcut.size() &&
            secondcut[i + counter].total == secondcut[i].total) {
            if (!secondcut[i + counter].amateur && secondcut[i + counter].prized)
                prizedPlayers++;
            if (!secondcut[i + counter].amateur)
                noAmateurs++;
            if (secondcut[i + counter].prized)
                prizeAllocate += secondcut[i + counter].prize;
            counter++;
        }

        if (counter > 1) {
            if (prizedPlayers > 0) prizeAllocate /= noAmateurs;  // 平均分配百分比之和
            prizeAllocate *= money;           // 换算为实际奖金
            for (int j = 0; j < counter; j++) {
                secondcut[i + j].place = place;
                if (!secondcut[i + j].amateur && prizedPlayers > 0) {
                    secondcut[i + j].tie = noAmateurs > 1;  // 多于1个非业余才加T
                    secondcut[i + j].prized = true;
                    secondcut[i + j].prize = prizeAllocate;
                }
            }
            place += counter;
            i += counter;
        } else {
            secondcut[i].place = place;
            secondcut[i].tie = false;
            secondcut[i].prize *= money;
            place++;
            i++;
        }
    }
    
    // ---- 输出获奖球员 ----
    for (int i = 0; i < secondcut.size(); i++) {
        cout << setw(21) << left << secondcut[i].name;
        string standing = to_string(secondcut[i].place) + (secondcut[i].tie ? "T" : "");
        cout << setw(10) << left << standing;
        cout << setw(5) << left << secondcut[i].rd1;
        cout << setw(5) << left << secondcut[i].rd2;
        cout << setw(5) << left << secondcut[i].rd3;
        cout << setw(5) << left << secondcut[i].rd4;

        if (secondcut[i].prized) {
            cout << setw(10) << left << secondcut[i].total;
            cout << "$";
            cout << setw(9) << right << fixed << setprecision(2) << secondcut[i].prize;
        } else cout << secondcut[i].total;

        cout << "\n";
    }
    
    // ---- 输出DQ球员 ----
    // 先计算已完成的轮次总分（用于排序）
    for (int i = 0; i < dq.size(); i++)
        dq[i].total += dq[i].rd3 != DQ ? dq[i].rd3 : 0;
    
    sort(dq.begin(), dq.end(), cmp2);
    
    for (int i = 0; i < dq.size(); i++) {
        cout << setw(21) << left << dq[i].name;
        cout << setw(10) << left << "";
        cout << setw(5) << left << (dq[i].rd1 != DQ ? to_string(dq[i].rd1) : "");
        cout << setw(5) << left << (dq[i].rd2 != DQ ? to_string(dq[i].rd2) : "");
        cout << setw(5) << left << (dq[i].rd3 != DQ ? to_string(dq[i].rd3) : "");
        cout << setw(5) << left << (dq[i].rd4 != DQ ? to_string(dq[i].rd4) : "");
        cout << "DQ\n";
    }
}

// 去除字符串首尾空白
string trim(string line) {
    while (line.length() && isblank(line.back()))
        line.erase(line.end() - 1);
    while (line.length() && isblank(line.front()))
        line.erase(line.begin());
    return line;
}

// 解析一行输入为player结构体
player parseToPlayer(string line) {
    // 确保长度至少32字符，不足补空格
    while (line.length() < 32)
        line += ' ';
        
    player x;
    x.name = line.substr(0, 20);
    x.amateur = trim(x.name).back() == '*';  // 名字末尾有*表示业余
    
    x.rd1 = DQ;
    x.rd2 = DQ;
    x.rd3 = DQ;
    x.rd4 = DQ;
    x.round = 0;
    
    string rd1 = trim(line.substr(20, 3));
    string rd2 = trim(line.substr(23, 3));
    string rd3 = trim(line.substr(26, 3));
    string rd4 = trim(line.substr(29, 3));
    
    // 逐轮解析，遇到DQ则停止
    if (rd1 != "DQ")
    {
        x.rd1 = stoi(rd1);
        x.round++;
    } else return x;
        
    if (rd2 != "DQ") {
        x.rd2 = stoi(rd2);
        x.round++;
    } else return x;
           
    if (rd3 != "DQ") {
        x.rd3 = stoi(rd3);
        x.round++;
    } else return x;
    
    if (rd4 != "DQ") {
        x.rd4 = stoi(rd4);
        x.round++;
    }
            
    return x;
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int cases = 0;
    cin >> cases;
    while (cases--) {
        players.clear();
        percents.clear();
        
        cin >> money;
        double percent;
        for (int i = 1; i <= 70; i++) {
            cin >> percent;
            percents.push_back(percent / 100.0);  // 转换为小数
        }
        
        int totalPlayers;
        cin >> totalPlayers;
        cin.ignore();
        
        string line;
        for (int i = 1; i <= totalPlayers; i++) {
            getline(cin, line);
            players.push_back(parseToPlayer(line));
        }
        
        allocate();
    }
    
	return 0;
}
```
