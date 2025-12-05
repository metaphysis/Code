// Advanced Causal Measurements
// UVa ID: 10619
// Verdict: Accepted
// Submission Date: 2025-12-05
// UVa Run Time: 0.920s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Event {
    int t, x;
};

// 检查对于给定的 earliestTime，是否能用 m 个原因覆盖所有事件
bool canCover(int earliestTime, const vector<Event>& events, int m) {
    vector<pair<long long, long long>> intervals; // 区间 [L, R]
    for (const auto& e : events) {
        long long radius = e.t - earliestTime;
        if (radius < 0) return false; // 该事件无法被任何时间>=earliestTime的原因覆盖
        intervals.push_back({e.x - radius, e.x + radius});
    }

    // 按右端点升序排序
    sort(intervals.begin(), intervals.end(), [](const pair<long long, long long>& a, const pair<long long, long long>& b) {
        return a.second < b.second;
    });

    int points = 0;
    long long lastPoint = -1LL << 60; // 上一个放置的点
    for (const auto& interval : intervals) {
        if (interval.first > lastPoint) { // 当前区间未被覆盖
            lastPoint = interval.second; // 在右端点放点
            points++;
            if (points > m) return false;
        }
    }
    return points <= m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseCount;
    cin >> caseCount;
    for (int caseIdx = 1; caseIdx <= caseCount; caseIdx++) {
        int n, m;
        cin >> n >> m;
        vector<Event> events(n);
        int minT = 1000000000;
        for (int i = 0; i < n; i++) {
            cin >> events[i].t >> events[i].x;
            minT = min(minT, events[i].t);
        }

        long long low = -2000000000, high = minT;
        long long answer = low;
        while (low <= high) {
            long long mid = (low + high) / 2;
            if (canCover(mid, events, m)) {
                answer = mid;
                low = mid + 1;
            } else
                high = mid - 1;
        }
        cout << "Case " << caseIdx << ": " << answer << "\n";
    }
    return 0;
}
