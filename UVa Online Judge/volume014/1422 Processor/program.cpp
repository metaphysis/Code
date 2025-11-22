// Processor
// UVa ID: 1422
// Verdict: Accepted
// Submission Date: 2025-11-20
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Task {
    int start, end, work, id;
    bool operator<(const Task& other) const {
        return end > other.end;  // 最小堆：截止时间最早的优先
    }
};

bool compareByStart(const Task& a, const Task& b) {
    return a.start == b.start ? a.end < b.end : a.start < b.start;
}

bool canFinish(int speed, vector<Task>& tasks, vector<int>& workRemaining) {
    priority_queue<Task> pq;
    int idx = 0;
    int n = tasks.size();
    for (int currentTime = 0; currentTime <= 20000; currentTime++) {
        while (idx < n && tasks[idx].start == currentTime) {
            pq.push(tasks[idx]);
            idx++;
        }
        int remainingCapacity = speed;
        while (!pq.empty() && remainingCapacity > 0) {
            Task current = pq.top();
            if (currentTime >= current.end) return false;
            int processAmount = min(remainingCapacity, workRemaining[current.id]);
            workRemaining[current.id] -= processAmount;
            remainingCapacity -= processAmount;
            if (workRemaining[current.id] == 0) pq.pop();
        }
        if (idx == n && pq.empty()) break;
    }
    return true;
}

int main() {
    int testCases;
    scanf("%d", &testCases);
    while (testCases--) {
        int n;
        scanf("%d", &n);
        vector<Task> tasks(n);
        vector<int> workRemaining(n);
        int totalWork = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d", &tasks[i].start, &tasks[i].end, &tasks[i].work);
            tasks[i].id = i;
            workRemaining[i] = tasks[i].work;
            totalWork += tasks[i].work;
        }
        sort(tasks.begin(), tasks.end(), compareByStart);
        int left = 1, right = totalWork;
        int answer = right;
        while (left <= right) {
            int mid = (left + right) / 2;
            vector<int> tempWork = workRemaining;
            if (canFinish(mid, tasks, tempWork)) {
                answer = mid;
                right = mid - 1;
            } else left = mid + 1;
        }
        printf("%d\n", answer);
    }
    return 0;
}
