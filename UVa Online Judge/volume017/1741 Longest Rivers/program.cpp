#include <bits/stdc++.h>
using namespace std;

void solveCase(int n, int m) {
    vector<string> names(n);
    vector<int> riverNext(n), nextNode(m + 1), remaining(m + 1), answer(n);
    vector<long long> riverDist(n), edgeDist(m + 1), downDist(m + 1, -1), minDist(m + 1, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> eventQueue;
    for (int i = 0; i < n; i++) {
        cin >> names[i] >> riverNext[i] >> riverDist[i];
        remaining[riverNext[i]]++;
        eventQueue.push({riverDist[i], riverNext[i]});
    }
    for (int i = 1; i <= m; i++) {
        cin >> nextNode[i] >> edgeDist[i];
        remaining[nextNode[i]]++;
    }
    downDist[0] = 0;
    for (int i = 1; i <= m; i++) {
        if (downDist[i] != -1) continue;
        vector<int> path;
        int cur = i;
        while (downDist[cur] == -1) {
            path.push_back(cur);
            cur = nextNode[cur];
        }
        long long dist = downDist[cur];
        reverse(path.begin(), path.end());
        for (int node : path) {
            dist += edgeDist[node];
            downDist[node] = dist;
        }
    }
    vector<pair<long long, int>> queries;
    queries.reserve(n);
    for (int i = 0; i < n; i++) queries.push_back({riverDist[i] + downDist[riverNext[i]], i});
    sort(queries.begin(), queries.end());
    int shortCount = 0;
    for (const auto &query : queries) {
        long long limit = query.first;
        while (!eventQueue.empty() && eventQueue.top().first <= limit) {
            long long dist = eventQueue.top().first;
            int node = eventQueue.top().second;
            eventQueue.pop();
            minDist[node] = min(minDist[node], dist);
            remaining[node]--;
            if (node == 0 || remaining[node] > 0) {
                shortCount++;
            } else {
                long long nextDist = minDist[node] + edgeDist[node];
                eventQueue.push({nextDist, nextNode[node]});
            }
        }
        answer[query.second] = n - shortCount + 1;
    }
    for (int i = 0; i < n; i++) cout << names[i] << ' ' << answer[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) solveCase(n, m);
    return 0;
}
