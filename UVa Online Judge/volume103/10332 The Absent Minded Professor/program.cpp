// The Absent Minded Professor
// UVa ID: 10332
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int N, maxVal;

bool inPoints(const vector<int>& points, int x) {
    for (int p : points) if (p == x) return true;
    return false;
}

bool dfs(multiset<int>& ms, vector<int>& points) {
    if ((int)points.size() == N) return ms.empty();
    if (ms.empty()) return false;

    int d = *ms.rbegin(); // 当前最大剩余差值

    // 候选点1：x = d（与0的距离为d）
    if (d > 0 && d < maxVal && !inPoints(points, d)) {
        map<int, int> need;
        for (int p : points) need[abs(d - p)]++;
        bool ok = true;
        for (auto& kv : need)
            if ((int)ms.count(kv.first) < kv.second) { ok = false; break; }
        if (ok) {
            for (auto& kv : need)
                for (int i = 0; i < kv.second; ++i)
                    ms.erase(ms.find(kv.first));
            points.push_back(d);
            if (dfs(ms, points)) return true;
            points.pop_back();
            for (auto& kv : need)
                for (int i = 0; i < kv.second; ++i)
                    ms.insert(kv.first);
        }
    }

    // 候选点2：x = maxVal - d（与maxVal的距离为d）
    int x2 = maxVal - d;
    if (x2 != d && x2 > 0 && x2 < maxVal && !inPoints(points, x2)) {
        map<int, int> need;
        for (int p : points) need[abs(x2 - p)]++;
        bool ok = true;
        for (auto& kv : need)
            if ((int)ms.count(kv.first) < kv.second) { ok = false; break; }
        if (ok) {
            for (auto& kv : need)
                for (int i = 0; i < kv.second; ++i)
                    ms.erase(ms.find(kv.first));
            points.push_back(x2);
            if (dfs(ms, points)) return true;
            points.pop_back();
            for (auto& kv : need)
                for (int i = 0; i < kv.second; ++i)
                    ms.insert(kv.first);
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> N) {
        int cnt = N * (N - 1) / 2;
        vector<int> diffs(cnt);
        for (int i = 0; i < cnt; ++i) cin >> diffs[i];

        sort(diffs.begin(), diffs.end());
        if (diffs.empty() || diffs[0] <= 0) {
            cout << "Incorrect Balance.\n";
            continue;
        }

        maxVal = diffs.back();
        multiset<int> ms(diffs.begin(), diffs.end());

        // 删除最大差值（对应0和maxVal之间的距离）
        auto it = ms.find(maxVal);
        if (it == ms.end()) {
            cout << "Incorrect Balance.\n";
            continue;
        }
        ms.erase(it);

        vector<int> points = {0, maxVal};

        if (dfs(ms, points)) {
            sort(points.begin(), points.end());
            for (int i = 0; i < N; ++i) {
                if (i) cout << ' ';
                cout << points[i];
            }
            cout << '\n';
        } else {
            cout << "Incorrect Balance.\n";
        }
    }
    return 0;
}
