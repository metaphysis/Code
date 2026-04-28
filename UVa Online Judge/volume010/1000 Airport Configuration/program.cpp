// Airport Configuration
// UVa ID: 1000
// Verdict: Accepted
// Submission Date: 2026-04-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Config {
    int id;
    int load;
};

bool cmp(const Config& a, const Config& b) {
    if (a.load != b.load) return a.load < b.load;
    return a.id < b.id;
}

int main() {
    int N;
    while (cin >> N && N != 0) {
        // 乘客矩阵
        vector<vector<int>> passenger(N + 1, vector<int>(N + 1, 0));
        for (int i = 1; i <= N; i++) {
            int from;
            cin >> from;
            int k; cin >> k;
            for (int t = 0; t < k; t++) {
                int to, cnt; cin >> to >> cnt;
                passenger[from][to] = cnt;
            }
        }

        vector<Config> configs;
        int configId;
        while (cin >> configId && configId != 0) {
            vector<int> arrPerm(N), depPerm(N);
            for (int i = 0; i < N; i++) cin >> arrPerm[i];
            for (int i = 0; i < N; i++) cin >> depPerm[i];

            // 映射城市 -> 到达口索引
            vector<int> arrPos(N + 1);
            for (int i = 0; i < N; i++) arrPos[arrPerm[i]] = i;

            // 映射城市 -> 出发口索引
            vector<int> depPos(N + 1);
            for (int i = 0; i < N; i++) depPos[depPerm[i]] = i;

            int totalLoad = 0;
            for (int from = 1; from <= N; from++) {
                for (int to = 1; to <= N; to++) {
                    int cnt = passenger[from][to];
                    if (cnt > 0) {
                        int dist = abs(arrPos[from] - depPos[to]) + 1;
                        totalLoad += cnt * dist;
                    }
                }
            }

            configs.push_back({configId, totalLoad});
        }

        sort(configs.begin(), configs.end(), cmp);

        cout << "Configuration Load\n";
        for (const auto& cfg : configs) {
            printf("%5d         %d\n", cfg.id, cfg.load);
        }
    }
    return 0;
}
