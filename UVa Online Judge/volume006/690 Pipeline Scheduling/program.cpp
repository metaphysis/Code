// Pipeline Scheduling
// UVa ID: 690
// Verdict: Accepted
// Submission Date: 2025-11-20
// UVa Run Time: 1.550s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n;
bitset<320> taskMask[5];
int best;
int actualTaskLength;
bitset<320> clockMask[5];
vector<int> validDelays; // 预计算的有效延迟

// 预计算所有可能的有效延迟
void precomputeValidDelays() {
    validDelays.clear();
    for (int delay = 1; delay <= n; delay++) {
        bool valid = true;
        for (int i = 0; i < 5 && valid; i++) {
            if ((taskMask[i] & (taskMask[i] << delay)).any()) valid = false;
        }
        if (valid) validDelays.push_back(delay);
    }
    // 如果没有找到有效延迟，至少包含最小延迟1
    if (validDelays.empty()) validDelays.push_back(1);
}

bool canSchedule(int startTime) {
    for (int i = 0; i < 5; i++) {
        if ((clockMask[i] & (taskMask[i] << startTime)).any()) return false;
    }
    return true;
}

void scheduleTask(int startTime) {
    for (int i = 0; i < 5; i++) clockMask[i] |= (taskMask[i] << startTime);
}

void unscheduleTask(int startTime) {
    for (int i = 0; i < 5; i++) clockMask[i] &= ~(taskMask[i] << startTime);
}

void backtrack(int taskCount, int lastStartTime) {
    // 更紧的剪枝：理论最小时间 + 当前已用时间
    int minRemainingTime = (10 - taskCount) * validDelays[0];
    if (lastStartTime + minRemainingTime + actualTaskLength >= best) return;
    
    if (taskCount == 10) {
        best = lastStartTime + actualTaskLength;
        return;
    }
    
    // 尝试所有有效延迟
    for (int delay : validDelays) {
        int startTime = lastStartTime + delay;
        // 快速剪枝：如果已经超过最优解
        if (startTime + actualTaskLength >= best) continue;
        
        if (canSchedule(startTime)) {
            scheduleTask(startTime);
            backtrack(taskCount + 1, startTime);
            unscheduleTask(startTime);
        }
    }
}

int main() {
    while (cin >> n && n) {
        cin.ignore();
        
        for (int i = 0; i < 5; i++) {
            taskMask[i].reset();
            clockMask[i].reset();
        }
        
        actualTaskLength = 0;
        for (int i = 0; i < 5; i++) {
            string line;
            getline(cin, line);
            for (int j = 0; j < n; j++) {
                if (line[j] == 'X') {
                    taskMask[i].set(j);
                    actualTaskLength = max(actualTaskLength, j + 1);
                }
            }
        }
        
        precomputeValidDelays();
        best = INT_MAX;
        scheduleTask(0);
        backtrack(1, 0);
        cout << best << endl;
    }
    return 0;
}
