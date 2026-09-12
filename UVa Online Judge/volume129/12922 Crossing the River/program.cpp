#include <bits/stdc++.h>
using namespace std;

int solveCase(int n, int limit, int capacity, const vector<int>& weight) {
    int total = 1 << n, fullMask = total - 1;
    vector<int> sum(total, 0), count(total, 0);
    vector<char> valid(total, 0);
    valid[0] = 0;
    for (int mask = 1; mask < total; mask++) {
        int lowBit = mask & -mask, index = __builtin_ctz(lowBit), prevMask = mask ^ lowBit;
        sum[mask] = sum[prevMask] + weight[index];
        count[mask] = count[prevMask] + 1;
        if (count[mask] <= capacity && sum[mask] <= limit)
            valid[mask] = 1;
    }
    vector<vector<int>> distance(2, vector<int>(total, -1));
    queue<pair<int, int>> bfs;
    distance[0][0] = 0;
    bfs.push({0, 0});
    while (!bfs.empty()) {
        int side = bfs.front().first, mask = bfs.front().second;
        bfs.pop();
        int currentDistance = distance[side][mask];
        if (side == 0) {
            int available = fullMask ^ mask;
            for (int group = available; group; group = (group - 1) & available) {
                if (!valid[group])
                    continue;
                int nextMask = mask | group;
                if (distance[1][nextMask] != -1)
                    continue;
                distance[1][nextMask] = currentDistance + 1;
                if (nextMask == fullMask)
                    return distance[1][nextMask];
                bfs.push({1, nextMask});
            }
        } else {
            for (int group = mask; group; group = (group - 1) & mask) {
                if (!valid[group])
                    continue;
                int nextMask = mask ^ group;
                if (distance[0][nextMask] != -1)
                    continue;
                distance[0][nextMask] = currentDistance + 1;
                bfs.push({0, nextMask});
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, limit, capacity;
    while (cin >> n >> limit >> capacity) {
        vector<int> weight(n);
        for (int i = 0; i < n; i++)
            cin >> weight[i];
        cout << solveCase(n, limit, capacity, weight) << '\n';
    }
    return 0;
}
