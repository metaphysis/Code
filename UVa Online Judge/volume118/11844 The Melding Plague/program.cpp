// The Melding Plague
// UVa ID: 11844
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N_M, N_I, N_C, n;
    while (cin >> N_M >> N_I >> N_C >> n) {
        if (N_M == 0 && N_I == 0 && N_C == 0 && n == 0) break;
        unordered_map<string, string> mutationMap;
        bool deterministic = true;
        for (int i = 0; i < N_M; ++i) {
            string p, q;
            cin >> p >> q;
            auto it = mutationMap.find(p);
            if (it == mutationMap.end()) mutationMap[p] = q;
            else if (it->second != q) deterministic = false;
        }
        unordered_map<string, int> initConfig, cureConfig;
        for (int i = 0; i < N_I; ++i) {
            string p; int cnt;
            cin >> p >> cnt;
            if (cnt > 0) initConfig[p] += cnt;
        }
        for (int i = 0; i < N_C; ++i) {
            string p; int cnt;
            cin >> p >> cnt;
            if (cnt > 0) cureConfig[p] += cnt;
        }
        if (!deterministic) {
            cout << "Protein mutations are not deterministic\n";
            continue;
        }
        unordered_map<string, int> current = initConfig;
        bool found = false;
        for (int step = 0; step <= n; ++step) {
            // 比较当前构型与治愈构型
            if (current.size() == cureConfig.size()) {
                bool same = true;
                for (auto &kv : cureConfig) {
                    auto it = current.find(kv.first);
                    if (it == current.end() || it->second != kv.second) {
                        same = false;
                        break;
                    }
                }
                if (same) {
                    cout << "Cure found in " << step << " mutation(s)\n";
                    found = true;
                    break;
                }
            }
            if (step == n) break;
            // 执行一步突变
            unordered_map<string, int> nextConfig;
            for (auto &kv : current) {
                string p = kv.first;
                int cnt = kv.second;
                auto it = mutationMap.find(p);
                if (it != mutationMap.end()) {
                    string q = it->second;
                    nextConfig[q] += cnt;
                } else {
                    nextConfig[p] += cnt;
                }
            }
            current = move(nextConfig);
        }
        if (!found) cout << "Nostalgia for Infinity is doomed\n";
    }
    return 0;
}
