#include <bits/stdc++.h>
using namespace std;

struct City {
    long double x, y;
};

struct Distance {
    long long value;
    string text;
};

bool dfs(int pos, int edgeCount, long long sum, long long target, const vector<vector<Distance>>& roads, const vector<long long>& minSum, const vector<long long>& maxSum, int start, vector<int>& path) {
    if (pos == edgeCount) return sum == target;
    if (sum + minSum[pos] > target || sum + maxSum[pos] < target) return false;
    for (int k = 0; k < (int)roads[start + pos].size(); k++) {
        long long nextSum = sum + roads[start + pos][k].value;
        if (nextSum > target) continue;
        path.push_back(k);
        if (dfs(pos + 1, edgeCount, nextSum, target, roads, minSum, maxSum, start, path)) return true;
        path.pop_back();
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    bool firstCase = true;
    while (cin >> n) {
        vector<City> cities(n);
        vector<vector<Distance>> roads(n - 1);
        for (int i = 0; i < n; i++) {
            cin >> cities[i].x >> cities[i].y;
            if (i == n - 1) continue;
            int m;
            cin >> m;
            roads[i].resize(m);
            for (int j = 0; j < m; j++) {
                cin >> roads[i][j].text;
                roads[i][j].value = stoll(roads[i][j].text);
            }
        }
        if (!firstCase) cout << '\n';
        firstCase = false;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                long double dx = cities[i].x - cities[j].x;
                long double dy = cities[i].y - cities[j].y;
                long long target = llroundl(sqrtl(dx * dx + dy * dy));
                int edgeCount = j - i;
                vector<long long> minSum(edgeCount + 1, 0), maxSum(edgeCount + 1, 0);
                for (int k = edgeCount - 1; k >= 0; k--) {
                    int roadIndex = i + k;
                    minSum[k] = LLONG_MAX;
                    maxSum[k] = LLONG_MIN;
                    for (const Distance& distance : roads[roadIndex]) {
                        minSum[k] = min(minSum[k], distance.value + minSum[k + 1]);
                        maxSum[k] = max(maxSum[k], distance.value + maxSum[k + 1]);
                    }
                }
                vector<int> path;
                if (!dfs(0, edgeCount, 0, target, roads, minSum, maxSum, i, path)) continue;
                cout << i + 1 << ' ' << j + 1;
                for (int k = 0; k < (int)path.size(); k++) cout << ' ' << roads[i + k][path[k]].text;
                cout << '\n';
            }
        }
    }
    return 0;
}
