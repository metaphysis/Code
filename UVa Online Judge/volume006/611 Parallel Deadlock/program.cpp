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
