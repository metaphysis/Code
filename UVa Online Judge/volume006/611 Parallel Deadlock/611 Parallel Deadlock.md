## 题目描述

并行计算中，处理器间通过发送（`S`）和接收（`R`）消息进行通信。每条指令可以是阻塞（`B`）或非阻塞（`N`）模式。阻塞发送要求目标处理器执行匹配的接收才能完成，阻塞接收要求源处理器执行匹配的发送才能完成；非阻塞操作立即返回，但真正完成仍需匹配操作。消息按发送顺序接收，并在匹配双方均执行对应操作后，在当前时间步结束时完成。一个正确的程序在所有操作（包括非阻塞操作）完成后终止。

给定若干处理器及其指令序列，需要模拟执行过程，判断每个处理器是否能在有限时间内完成其全部指令，若不能，则找出阻止其完成的处理器集合。

## 输入格式

第一行是数据集个数 $T$，随后一个空行。每个数据集第一行为正整数 $P$，表示处理器个数。接下来 $P$ 个处理器，每个先占一行，包含处理器名称（单个大写字母）和指令条数 $M$，随后 $M$ 行指令。每条指令格式为 `Mode Action Target(s)`，其中 `Mode` 为 `B` 或 `N`，`Action` 为 `S` 或 `R`，`Target(s)` 为若干目标处理器名称（单个大写字母）。处理器不会与自己通信，且目标不重复。

## 输出格式

对于每个数据集，按处理器名称字母顺序输出。若处理器完成，输出 `X finishes at t=T`；若未完成，输出 `X never finishes because of Y and Z`，其中 `Y`、`Z` 等为阻止该处理器完成的处理器名称，按字母顺序排列，多个之间用 `and` 连接。每个数据集输出后（除最后一个）空一行。

## 样例

输入

```
1

4
I 5
B S B P C
N S B P C
N R B
B R P
B R C
B 2
B R I
B S I
P 3
N S I
N R I
B R I
C 4
N S I
B R I
B S P
B R I
```

输出

```
B finishes at t=4
C never finishes because of P
I never finishes because of B and C
P finishes at t=5
```

## 题目分析

本题要求模拟并行执行过程，核心挑战在于：

1. **阻塞与非阻塞**：阻塞指令会挂起处理器，直到匹配完成；非阻塞指令立即前进，但其未完成操作仍会阻塞程序终止。
2. **多目标通信**：一条发送或接收指令可指定多个目标，必须等待**所有**目标的匹配操作完成，该指令才算完成。
3. **死锁检测**：当所有未完成处理器都因等待对方而停滞，且没有新的匹配可能发生时，程序进入死锁。

直接枚举时间步模拟是自然的思路。每个时间步分为“执行”和“匹配”两个阶段。执行阶段让所有未阻塞且未完成的处理器执行下一条指令，生成对应的通信请求；匹配阶段则尝试配对同时存在的发送与接收请求。若某时间步没有执行任何新指令也没有任何匹配发生，则系统死锁。

还需注意，非阻塞操作即使立即返回，其父操作仍需收集所有目标的匹配，因此也需要维护其完成状态。

## 解题思路

### 数据结构设计

- **处理器信息**：`Processor` 结构体包含名称、指令列表、程序计数器 `ip`、是否阻塞 `blocked`、未完成的父操作列表 `pendingOps`（存储父操作 $\texttt{ID}$）、是否完成 `finished`、完成时间 `finishTime`。
- **指令**：`Instruction` 记录模式、动作、目标列表（字符数组）。
- **父操作**：`ParentOp` 记录所属处理器索引、指令索引、模式、动作、目标列表、每个目标是否已匹配（`matchedTargets` 布尔数组）、已匹配数、所需匹配数、是否完成。每个处理器执行一条指令即产生一个父操作。
- **子操作队列**：对于每一对方向 `(src, dst)`，分别维护发送队列 `sendQ[src][dst]` 和接收队列 `recvQ[src][dst]`，队列元素为 `SubOp`，包含父操作 $\texttt{ID}$ 和该子操作的目标处理器。当处理器执行发送指令时，为每个目标向 `sendQ[src][dst]` 添加一个子操作；执行接收指令时，为每个源处理器向 `recvQ[src][dst]` 添加子操作。

### 模拟过程

1. **初始化**：读取所有处理器及其指令，建立名称到索引的映射。
2. **时间步循环**（`t` 从 $1$ 开始递增）：
   - **执行阶段**：遍历所有未完成、未阻塞且程序未结束的处理器。  
     - 创建 `ParentOp`，将其 $\texttt{ID}$ 加入处理器的 `pendingOps`。  
     - 根据动作（`S` 或 `R`）和目标列表，向对应的 `sendQ` 或 `recvQ` 添加子操作。  
     - 若指令为阻塞，置 `blocked = true`；否则 `ip++`。
   - **匹配阶段**：遍历所有 $26×26$ 个方向。若发送队列和接收队列均非空，则分别取出队首子操作并配对。  
     - 对于发送子操作，其目标为 `dst`；接收子操作的目标为 `src`。  
     - 调用辅助函数 `finishParent(parentId, target)`：在父操作的目标列表中标记该 `target` 为已匹配；若所有目标均已匹配，则标记父操作完成，从所属处理器的 `pendingOps` 中移除，若该处理器正阻塞在该指令上，则解除阻塞并 `ip++`。
   - **完成检查**：遍历所有处理器，若其 `ip` 等于指令总数且 `pendingOps` 为空，则标记为完成，记录当前时间步 `t`。
   - **终止判断**：若所有处理器均完成，则退出循环；若本时间步既没有执行新指令也没有发生任何匹配，则判定为死锁，退出循环。
3. **输出**：按字母顺序排序处理器。已完成者输出完成时间；未完成者收集其所有未完成父操作中尚未匹配的目标处理器（即 `matchedTargets` 为 `false` 的目标），去重后按字母顺序输出。

### 正确性说明

- 每个时间步的执行顺序不影响匹配的正确性，因为所有新生成的请求在同一时间步内均可参与匹配（消息可在发送时间步结束时被接收）。
- 阻塞指令的解除发生在匹配完成后，因此解除后的处理器能在下一时间步执行新指令。
- 死锁检测条件“无执行且无匹配”成立时，系统确实不可能再产生任何新的通信请求或完成已有匹配，因此程序将永远停滞。

### 复杂度分析

设处理器数为 $P$（$P \le 26$），每个处理器指令数不超过 $100$，总指令数为 $O(100P)$。每个指令的目标数最多为 $P$，因此总通信子操作数为 $O(100P^2)$。时间步数受限于总操作数和死锁检测，实际模拟过程中每个处理器最多执行 $100$ 条指令，且每次匹配至少完成一个子操作，因此时间步数不超过 $O(100P^2)$。每一时间步遍历 $P$ 个处理器和 $26^2$ 个方向，故总时间复杂度为 $O(100P^2 \cdot (P + 26^2))$，在给定范围（$P \le 26$）下可接受。空间复杂度为 $O(100P^2)$，用于存储父操作和子操作队列。

## 代码实现

```cpp
// Parallel Deadlock
// UVa ID: 611
// Verdict: Accepted
// Submission Date: 2026-07-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Instruction {
    char mode, action;
    vector<char> targets;
};

struct Processor {
    char name;
    vector<Instruction> prog;
    int ip;
    bool blocked;
    vector<int> pendingOps;
    bool finished;
    int finishTime;
};

struct ParentOp {
    int procIdx, instIdx;
    char mode, action;
    vector<char> targets;
    vector<bool> matchedTargets;
    int matchedCount, requiredCount;
    bool completed;
};

struct SubOp {
    int parentId;
    char targetChar;
};

int main() {
    int datasetCnt;
    string line;
    cin >> datasetCnt;
    getline(cin, line);

    for (int ds = 0; ds < datasetCnt; ++ds) {
        while (getline(cin, line) && line.empty());
        int K = stoi(line);

        vector<Processor> procs;
        unordered_map<char, int> nameIdx;
        vector<ParentOp> parentOps;
        queue<SubOp> sendQ[26][26], recvQ[26][26];

        for (int i = 0; i < K; ++i) {
            while (getline(cin, line) && line.empty());
            istringstream iss(line);
            char name;
            int n;
            iss >> name >> n;
            Processor p;
            p.name = name;
            p.ip = 0;
            p.blocked = false;
            p.finished = false;
            p.finishTime = 0;
            for (int j = 0; j < n; ++j) {
                while (getline(cin, line) && line.empty());
                istringstream iss2(line);
                string modeStr, actionStr;
                iss2 >> modeStr >> actionStr;
                Instruction inst;
                inst.mode = modeStr[0];
                inst.action = actionStr[0];
                char target;
                while (iss2 >> target) inst.targets.push_back(target);
                p.prog.push_back(inst);
            }
            procs.push_back(p);
            nameIdx[name] = i;
        }

        int t = 0;
        while (true) {
            bool hasExecuted = false, hasMatched = false;
            ++t;

            // 执行阶段
            for (int i = 0; i < (int)procs.size(); ++i) {
                Processor &p = procs[i];
                if (p.finished || p.blocked || p.ip >= (int)p.prog.size()) continue;
                hasExecuted = true;

                Instruction &inst = p.prog[p.ip];
                ParentOp op;
                op.procIdx = i;
                op.instIdx = p.ip;
                op.mode = inst.mode;
                op.action = inst.action;
                op.targets = inst.targets;
                op.matchedTargets.assign(inst.targets.size(), false);
                op.matchedCount = 0;
                op.requiredCount = (int)inst.targets.size();
                op.completed = false;
                int parentId = (int)parentOps.size();
                parentOps.push_back(op);
                p.pendingOps.push_back(parentId);

                for (char target : inst.targets) {
                    SubOp sub;
                    sub.parentId = parentId;
                    sub.targetChar = target;
                    if (inst.action == 'S') {
                        sendQ[p.name - 'A'][target - 'A'].push(sub);
                    } else {
                        recvQ[target - 'A'][p.name - 'A'].push(sub);
                    }
                }

                if (inst.mode == 'B') p.blocked = true;
                else p.ip++;
            }

            // 匹配阶段
            auto finishParent = [&](int pid, char target) {
                ParentOp &op = parentOps[pid];
                for (int idx = 0; idx < (int)op.targets.size(); ++idx)
                    if (op.targets[idx] == target && !op.matchedTargets[idx]) {
                        op.matchedTargets[idx] = true;
                        op.matchedCount++;
                        if (op.matchedCount != op.requiredCount || op.completed) return;
                        op.completed = true;
                        Processor &p = procs[op.procIdx];
                        auto &pend = p.pendingOps;
                        pend.erase(remove(pend.begin(), pend.end(), pid), pend.end());
                        if (op.mode == 'B' && p.blocked && p.ip == op.instIdx) {
                            p.blocked = false;
                            p.ip++;
                        }
                        break;
                    }
            };

            for (int src = 0; src < 26; ++src) {
                for (int dst = 0; dst < 26; ++dst) {
                    if (sendQ[src][dst].empty() || recvQ[src][dst].empty()) continue;
                    SubOp sendSub = sendQ[src][dst].front(); sendQ[src][dst].pop();
                    SubOp recvSub = recvQ[src][dst].front(); recvQ[src][dst].pop();
                    hasMatched = true;
                    finishParent(sendSub.parentId, (char)('A' + dst));
                    finishParent(recvSub.parentId, (char)('A' + src));
                }
            }

            // 检查完成
            for (int i = 0; i < (int)procs.size(); ++i) {
                Processor &p = procs[i];
                if (!p.finished && p.ip == (int)p.prog.size() && p.pendingOps.empty()) {
                    p.finished = true;
                    p.finishTime = t;
                }
            }

            bool allDone = true;
            for (auto &p : procs) if (!p.finished) { allDone = false; break; }
            if (allDone) break;

            if (!hasExecuted && !hasMatched) break;
        }

        sort(procs.begin(), procs.end(), [](const Processor &a, const Processor &b) {
            return a.name < b.name;
        });

        for (auto &p : procs) {
            if (p.finished) {
                cout << p.name << " finishes at t=" << p.finishTime << "\n";
            } else {
                set<char> blockers;
                for (int pid : p.pendingOps) {
                    ParentOp &op = parentOps[pid];
                    if (op.completed) continue;
                    for (int idx = 0; idx < (int)op.targets.size(); ++idx)
                        if (!op.matchedTargets[idx])
                            blockers.insert(op.targets[idx]);
                }
                cout << p.name << " never finishes because of ";
                vector<char> vec(blockers.begin(), blockers.end());
                for (int i = 0; i < (int)vec.size(); ++i) {
                    if (i > 0) cout << " and ";
                    cout << vec[i];
                }
                cout << "\n";
            }
        }

        if (ds != datasetCnt - 1) cout << "\n";
    }

    return 0;
}
```

## 总结

本题通过逐时间步模拟并行通信过程，并结合队列匹配机制，正确处理了阻塞/非阻塞、多目标通信和死锁检测。关键点在于：

- 将每条指令视为一个父操作，其多个目标子操作分别入队，利用队列保证消息顺序。
- 匹配阶段遍历所有方向，仅当双方队列均非空时才配对，避免遗漏。
- 死锁检测条件简单有效：无新执行且无匹配。
- 阻止者收集需排除已匹配目标，仅统计尚未匹配的目标处理器。

该解法在题目给定约束下运行高效，代码结构清晰，适合作为并行死锁模拟的参考实现。
