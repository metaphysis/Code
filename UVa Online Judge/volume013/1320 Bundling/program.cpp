#include <bits/stdc++.h>
using namespace std;

struct State {
    int bundles, stops, lastStop;
};

bool isBetter(const State &a, const State &b) {
    if (a.bundles != b.bundles) return a.bundles < b.bundles;
    if (a.stops != b.stops) return a.stops < b.stops;
    return a.lastStop > b.lastStop;
}

void solve() {
    int t, n;
    cin >> t >> n;
    bool can[4][1000][5] = {};
    for (int i = 0; i < t; ++i) {
        string pattern;
        int p;
        cin >> pattern >> p;
        for (int mask = 1; mask < 8; ++mask) {
            int len = 0, code = 0, stopPos = 0;
            for (int slot = 0; slot < 3; ++slot) {
                if ((mask & (1 << slot)) == 0) continue;
                ++len;
                code = code * 10 + (pattern[slot] - 'A');
                if (slot + 1 <= p) ++stopPos;
            }
            int stopId = p == 0 ? 0 : stopPos + 1;
            can[len][code][stopId] = true;
        }
    }
    vector<int> type(n + 1), dep(n + 1);
    for (int i = 1; i <= n; ++i) {
        char c;
        cin >> c >> dep[i];
        type[i] = c - 'A';
    }
    const int inf = 1000000000;
    vector<State> dp(n + 1, State{inf, inf, -1});
    dp[0] = State{0, 0, 0};
    for (int i = 0; i < n; ++i) {
        if (dp[i].bundles == inf) continue;
        int code = 0;
        for (int len = 1; len <= 3 && i + len <= n; ++len) {
            code = code * 10 + type[i + len];
            for (int stopId = 0; stopId <= len + 1; ++stopId) {
                if (!can[len][code][stopId]) continue;
                int stopPos = stopId - 1;
                for (int addStop = 0; addStop <= 1; ++addStop) {
                    if (i == 0 && addStop == 1) continue;
                    int lastStop = addStop == 1 ? i : dp[i].lastStop;
                    bool valid = true;
                    for (int offset = 0; offset < len; ++offset) {
                        if (offset == stopPos) lastStop = i + offset;
                        if (dep[i + offset + 1] > lastStop) {
                            valid = false;
                            break;
                        }
                    }
                    if (!valid) continue;
                    if (stopPos == len) lastStop = i + len;
                    State nextState{
                        dp[i].bundles + 1,
                        dp[i].stops + addStop + (stopId != 0),
                        lastStop
                    };
                    if (isBetter(nextState, dp[i + len])) dp[i + len] = nextState;
                }
            }
        }
    }
    cout << dp[n].bundles << ' ' << dp[n].stops << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int testId = 0; testId < testCount; ++testId) {
        if (testId > 0) cout << '\n';
        solve();
    }
    return 0;
}
