#include <bits/stdc++.h>
using namespace std;

struct Task {
    int startTime, basePr, pos;
    vector<pair<char, int>> inst;
};

int chooseTask(const vector<Task>& tasks, const vector<int>& owner, const vector<int>& ceiling, int curTime) {
    int taskCount = tasks.size(), resCount = owner.size() - 1, chosen = -1, topPr = -1;
    for (int i = 0; i < taskCount; ++i) {
        if (tasks[i].startTime <= curTime && tasks[i].pos < (int)tasks[i].inst.size() && tasks[i].basePr > topPr) {
            chosen = i;
            topPr = tasks[i].basePr;
        }
    }
    if (chosen == -1) return -1;
    while (true) {
        const pair<char, int>& curInst = tasks[chosen].inst[tasks[chosen].pos];
        if (curInst.first != 'L') return chosen;
        int blocker = -1, resId = curInst.second;
        for (int i = 1; i <= resCount; ++i) {
            if (owner[i] != -1 && owner[i] != chosen && (i == resId || ceiling[i] >= topPr)) {
                blocker = owner[i];
                break;
            }
        }
        if (blocker == -1) return chosen;
        chosen = blocker;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int taskCount, resCount;
    while (cin >> taskCount >> resCount) {
        vector<Task> tasks(taskCount);
        vector<int> owner(resCount + 1, -1), ceiling(resCount + 1, 0), finishTime(taskCount, 0);
        for (int i = 0; i < taskCount; ++i) {
            int instCount;
            cin >> tasks[i].startTime >> tasks[i].basePr >> instCount;
            tasks[i].pos = 0;
            tasks[i].inst.reserve(instCount);
            for (int j = 0; j < instCount; ++j) {
                string token;
                cin >> token;
                int value = stoi(token.substr(1));
                tasks[i].inst.emplace_back(token[0], value);
                if (token[0] == 'L') ceiling[value] = max(ceiling[value], tasks[i].basePr);
            }
        }
        int curTime = 0, doneCount = 0;
        while (doneCount < taskCount) {
            int chosen = chooseTask(tasks, owner, ceiling, curTime);
            if (chosen == -1) {
                int nextTime = INT_MAX;
                for (int i = 0; i < taskCount; ++i) {
                    if (tasks[i].pos < (int)tasks[i].inst.size() && tasks[i].startTime > curTime) nextTime = min(nextTime, tasks[i].startTime);
                }
                curTime = nextTime;
                continue;
            }
            Task& task = tasks[chosen];
            pair<char, int>& curInst = task.inst[task.pos];
            if (curInst.first == 'C') {
                ++curTime;
                --curInst.second;
                if (curInst.second == 0) ++task.pos;
            } else {
                if (curInst.first == 'L') owner[curInst.second] = chosen;
                else owner[curInst.second] = -1;
                ++task.pos;
            }
            if (task.pos == (int)task.inst.size()) {
                finishTime[chosen] = curTime;
                ++doneCount;
            }
        }
        for (int i = 0; i < taskCount; ++i) cout << finishTime[i] << '\n';
    }
    return 0;
}
