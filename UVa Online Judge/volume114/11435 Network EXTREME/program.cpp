#include <bits/stdc++.h>
using namespace std;

struct Packet {
    int start, end, arrive;
};

int solve() {
    int n, m, caseId = 1;
    while (cin >> n >> m && (n != 0 || m != 0)) {
        vector<int> size(n), last(n, 0);
        vector<vector<Packet>> packets(n);
        vector<long long> total(m + 1, 0);
        for (int i = 0; i < n; i++)
            cin >> size[i];
        for (int i = 1; i <= m; i++) {
            int msg, start, end;
            cin >> msg >> start >> end;
            --msg;
            packets[msg].push_back({start, end, i});
            last[msg] = i;
            total[i] = total[i - 1] + end - start + 1;
        }
        for (int i = 0; i < n; i++)
            sort(packets[i].begin(), packets[i].end(), [](const Packet &a, const Packet &b) {
                return a.start < b.start;
            });
        vector<vector<int>> prefix(n, vector<int>(m + 1, 0));
        for (int i = 0; i < n; i++) {
            int pos = 0;
            for (int u = 1; u <= m; u++) {
                while (pos < static_cast<int>(packets[i].size()) && packets[i][pos].arrive <= u)
                    pos++;
                if (pos > 0)
                    prefix[i][u] = packets[i][pos - 1].end;
            }
        }
        vector<vector<long long>> rightMax(n, vector<long long>(m + 2, LLONG_MIN));
        for (int i = 0; i < n; i++) {
            for (int u = last[i]; u >= 1; u--)
                rightMax[i][u] = max(rightMax[i][u + 1], total[u] - prefix[i][u]);
        }
        vector<int> times(1, 0);
        for (int i = 0; i < n; i++)
            times.push_back(last[i]);
        sort(times.begin(), times.end());
        times.erase(unique(times.begin(), times.end()), times.end());
        vector<long long> sizeAt(m + 1, 0);
        for (int i = 0; i < n; i++)
            sizeAt[last[i]] += size[i];
        vector<long long> done(times.size(), 0);
        for (int i = 1; i < static_cast<int>(times.size()); i++)
            done[i] = done[i - 1] + sizeAt[times[i]];
        const long long inf = (1LL << 60);
        vector<long long> dp(times.size(), inf);
        dp[0] = 0;
        for (int state = 0; state < static_cast<int>(times.size()); state++) {
            if (dp[state] == inf)
                continue;
            int currentTime = times[state];
            for (int i = 0; i < n; i++) {
                if (last[i] <= currentTime)
                    continue;
                int nextState = lower_bound(times.begin(), times.end(), last[i]) - times.begin();
                long long cost = rightMax[i][currentTime + 1] - done[state];
                cost = max(0LL, cost);
                dp[nextState] = min(dp[nextState], max(dp[state], cost));
            }
        }
        cout << "Case " << caseId++ << ": " << dp.back() << "\n\n";
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
