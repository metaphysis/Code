// Going in circles on Alpha Centauri
// UVa ID: 660
// Verdict: Accepted
// Submission Date: 2026-01-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

struct Request {
    int time, origin, dest, weight;
};

struct Robot {
    int id, maxLoad, location, available;
    // 优先队列，完成时间早的机器人排在前
    bool operator < (const Robot r) const { return available > r.available; }
};

int n, m;

int clockwiseTime(int from, int to) {
    return to >= from ? to - from : n - (from - to);
}

pair<double, double> simulate() {
    vector<Robot> idling;
    priority_queue<Robot> working;
    for (int i = 0; i < m; ++i) {
        int load; cin >> load;
        working.push({i + 1, load, 1, 0});
    }
    vector<Request> appending, waiting;
    while (true) {
        int t, o, d, w; cin >> t >> o >> d >> w;
        if (t == -1) break;
        appending.push_back({t, o, d, w});
    }
    if (appending.empty()) return {0.0, 0.0};

    int cntOfRequest = appending.size();
    int startTime = appending.front().time;
    int currentTime = 0, waitTime = 0, serviceTime = 0;

    while (!waiting.empty() || !appending.empty()) {
        // 更新当前时间，取到达的请求和最早完成任务的机器人的较小值
        currentTime = INF;
        if (appending.size()) currentTime = appending.front().time;
        if (working.size()) currentTime = min(currentTime, working.top().available);
        // 将到达时间不迟于当前时间的请求放入等待队列
        while (!appending.empty() && appending.front().time <= currentTime) {
            waiting.push_back(appending.front());
            appending.erase(appending.begin());
        }
        // 将可用时间不迟于当前时间的机器人放入可用机器人队列
        while (!working.empty() && working.top().available <= currentTime) {
            idling.push_back(working.top());
            working.pop();
        }
        // 扫描当前等待请求队列，安排机器人服务
        vector<int> assigned;
        for (int i = 0; i < waiting.size(); i++) {
            int bestIdx = -1, bestId = INF, bestDist = INF;
            for (int j = 0; j < idling.size(); j++) {
                if (idling[j].maxLoad < waiting[i].weight) continue;
                int d = clockwiseTime(idling[j].location, waiting[i].origin);
                if (d < bestDist || (d == bestDist && idling[j].id < bestId)) {
                    bestDist = d;
                    bestId = idling[j].id;
                    bestIdx = j;
                }
            }
            // 找到可用机器人
            if (bestIdx >= 0) {
                // 计算服务时间
                int d1 = clockwiseTime(idling[bestIdx].location, waiting[i].origin);
                int d2 = clockwiseTime(waiting[i].origin, waiting[i].dest);
                serviceTime += d1 + 10 + d2;
                waitTime += currentTime - waiting[i].time + d1 + 10 + d2;
                // 将当前机器人放入工作机器人优先队列
                Robot robot = idling[bestIdx];
                robot.location = waiting[i].dest;
                robot.available = currentTime + d1 + 10 + d2;
                working.push(robot);
                // 从可用机器人队列移除
                idling.erase(idling.begin() + bestIdx);
                // 标记任务已服务
                assigned.push_back(i);
             }
        }
        // 将已经服务的请求从等待队列中移除
        for (auto it = assigned.rbegin(); it != assigned.rend(); it++)
            waiting.erase(waiting.begin() + *it);
    }
    // 更新服务结束时间
    while (!working.empty()) {
        currentTime = working.top().available;
        working.pop();
    }
    double averageTime = (double)waitTime / cntOfRequest;
    double utilization = (double)serviceTime / (m * (currentTime - startTime)) * 100.0;
    return {averageTime, utilization};
}

int main() {
    int T = 0;
    while (cin >> n >> m, n) {
        T++;
        auto result = simulate();
        cout << "Simulation " << T << '\n';
        cout << fixed << setprecision(3);
        cout << "Average wait time   = " << result.first << " minutes\n";
        cout << "Average utilization = " << result.second << " %\n\n";
    }
    return 0;
}
