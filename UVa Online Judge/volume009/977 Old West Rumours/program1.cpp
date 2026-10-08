// Old West Rumours
// UVa ID: 977
// Verdict: Accepted
// Submission Date: 2026-10-09
// UVa Run Time: 0.180s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

const int inf = 1000000000;

struct Label {
    ull mask;
    int time;
};

struct Candidate {
    int town, arrival, travel;
};

int townCount, routeCount, answer, reachableCount;
ull reachMask;
vector<int> stopTime, rumorTime;
vector<vector<int>> rumorDist, billyDist;
vector<vector<Label>> labels;

void floyd(vector<vector<int>>& dist) {
    for (int k = 0; k < townCount; ++k) {
        for (int i = 0; i < townCount; ++i) {
            if (dist[i][k] == inf) continue;
            for (int j = 0; j < townCount; ++j) {
                if (dist[k][j] == inf) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

bool addLabel(ull mask, int town, int time) {
    vector<Label>& cur = labels[town];
    for (const Label& label : cur)
        if (label.time <= time && (label.mask | mask) == label.mask) return false;
    int writePos = 0;
    for (int i = 0; i < (int)cur.size(); ++i) {
        if (time <= cur[i].time && (mask | cur[i].mask) == mask) continue;
        cur[writePos++] = cur[i];
    }
    cur.resize(writePos);
    cur.push_back({mask, time});
    return true;
}

void search(ull mask, int town, int time, int savedCount) {
    answer = max(answer, savedCount);
    if (answer == reachableCount) return;
    if (!addLabel(mask, town, time)) return;
    Candidate candidates[64];
    int candidateCount = 0;
    ull remaining = reachMask & ~mask;
    // 直接选择下一座要处理的城市，中途经过的城市无需建立状态。
    while (remaining) {
        int v = __builtin_ctzll(remaining);
        remaining &= remaining - 1;
        int travel = billyDist[town][v];
        if (travel == inf || time > rumorTime[v] - travel) continue;
        candidates[candidateCount++] = {v, time + travel, travel};
    }
    // 当前已经来不及处理的城市，以后也不可能再处理。
    if (savedCount + candidateCount <= answer) return;
    sort(candidates, candidates + candidateCount, [](const Candidate& a, const Candidate& b) {
        if (a.travel != b.travel) return a.travel < b.travel;
        return a.town < b.town;
    });
    for (int i = 0; i < candidateCount; ++i) {
        const Candidate& next = candidates[i];
        search(mask | (1ULL << next.town), next.town,
               next.arrival + stopTime[next.town], savedCount + 1);
        // 当前状态的乐观上界已经达到，无需继续探索其他顺序。
        if (answer >= savedCount + candidateCount) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> townCount >> routeCount) {
        if (townCount == 0 && routeCount == 0) break;
        stopTime.assign(townCount, 0);
        rumorDist.assign(townCount, vector<int>(townCount, inf));
        billyDist.assign(townCount, vector<int>(townCount, inf));
        labels.assign(townCount, vector<Label>());
        for (int i = 0; i < townCount; ++i) {
            cin >> stopTime[i];
            rumorDist[i][i] = 0;
            billyDist[i][i] = 0;
        }
        for (int i = 0; i < routeCount; ++i) {
            int u, v, t;
            cin >> u >> v >> t;
            int travel = t / 2;
            rumorDist[u][v] = min(rumorDist[u][v], t);
            rumorDist[v][u] = min(rumorDist[v][u], t);
            billyDist[u][v] = min(billyDist[u][v], travel);
            billyDist[v][u] = min(billyDist[v][u], travel);
        }
        floyd(rumorDist);
        floyd(billyDist);
        rumorTime = rumorDist[0];
        reachMask = 0;
        for (int i = 0; i < townCount; ++i)
            if (rumorTime[i] != inf) reachMask |= 1ULL << i;
        reachableCount = __builtin_popcountll(reachMask);
        answer = 0;
        // 城市零也作为可选目标，自动包含处理和不处理起点两种情况。
        search(0ULL, 0, 0, 0);
        cout << answer << '\n';
    }
    return 0;
}
