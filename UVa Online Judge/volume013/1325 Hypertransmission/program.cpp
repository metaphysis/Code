// Hypertransmission
// UVa ID: 1325
// Verdict: Accepted
// Submission Date: 2026-04-25
// UVa Run Time: 0.360s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Planet {
    int x, y, z, p;
};

struct Event {
    double dist;
    int a, b;      // 行星对 (a, b)，a < b
    int type;      // 0: 派别相同，1: 派别不同
};

bool eventLess(const Event& e1, const Event& e2) {
    return e1.dist < e2.dist;
}

void solve(int N, vector<Planet>& planets) {
    vector<Event> events;

    // 生成所有行星对事件
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            long long dx = planets[i].x - planets[j].x;
            long long dy = planets[i].y - planets[j].y;
            long long dz = planets[i].z - planets[j].z;
            double d = sqrt(dx * dx + dy * dy + dz * dz);
            if (planets[i].p == planets[j].p) {
                events.push_back({d, i, j, 0}); // 相同派别
            } else {
                events.push_back({d, i, j, 1}); // 不同派别
            }
        }
    }
    sort(events.begin(), events.end(), eventLess);

    // 初始状态 R = 0，每个行星只能收到自己
    vector<int> sameCount(N, 1);   // 包括自身
    vector<int> diffCount(N, 0);
    vector<bool> isUnstable(N, false);
    int curD = 0;

    for (int i = 0; i < N; ++i) {
        if (sameCount[i] < diffCount[i]) {
            isUnstable[i] = true;
            curD++;
        }
    }

    int bestD = curD;
    double bestR = 0.0;

    size_t idx = 0;
    while (idx < events.size()) {
        double curDist = events[idx].dist;
        vector<Event> batch;
        // 收集所有距离为 curDist 的事件（容差 1e-9）
        while (idx < events.size() && fabs(events[idx].dist - curDist) < 1e-9) {
            batch.push_back(events[idx]);
            idx++;
        }

        // 应用这批事件，更新计数
        for (const Event& e : batch) {
            // 更新行星 a
            bool wasUnstableA = isUnstable[e.a];
            if (e.type == 0) {
                sameCount[e.a]++;
            } else {
                diffCount[e.a]++;
            }
            bool nowUnstableA = (sameCount[e.a] < diffCount[e.a]);
            if (wasUnstableA && !nowUnstableA) curD--;
            else if (!wasUnstableA && nowUnstableA) curD++;
            isUnstable[e.a] = nowUnstableA;

            // 更新行星 b
            bool wasUnstableB = isUnstable[e.b];
            if (e.type == 0) {
                sameCount[e.b]++;
            } else {
                diffCount[e.b]++;
            }
            bool nowUnstableB = (sameCount[e.b] < diffCount[e.b]);
            if (wasUnstableB && !nowUnstableB) curD--;
            else if (!wasUnstableB && nowUnstableB) curD++;
            isUnstable[e.b] = nowUnstableB;
        }

        // 更新最优解
        if (curD > bestD) {
            bestD = curD;
            bestR = curDist;
        }
    }

    printf("%d\n%.4lf\n", bestD, bestR);
}

int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        vector<Planet> planets(N);
        for (int i = 0; i < N; ++i) {
            scanf("%d%d%d%d", &planets[i].x, &planets[i].y, &planets[i].z, &planets[i].p);
        }
        solve(N, planets);
    }
    return 0;
}

