#include <bits/stdc++.h>
using namespace std;

int solveCase(int n, int m, const vector<int>& pat) {
    int stateCnt = 1 << m;
    vector<int> dp(stateCnt, -1), ndp(stateCnt, -1), active, nextActive;
    dp[1] = 0;
    active.push_back(1);
    for (int i = 0; i < n; i++) {
        fill(ndp.begin(), ndp.end(), -1);
        nextActive.clear();
        for (int state : active) {
            for (int mask = 0; mask < 32; mask++) {
                int newState = 1;
                bool bad = false;
                for (int j = 0; j < m; j++) {
                    if ((state & (1 << j)) == 0)
                        continue;
                    if ((mask & pat[j]) != pat[j])
                        continue;
                    if (j + 1 == m) {
                        bad = true;
                        break;
                    }
                    newState |= 1 << (j + 1);
                }
                if (bad)
                    continue;
                int newValue = dp[state] + __builtin_popcount(mask);
                if (ndp[newState] == -1)
                    nextActive.push_back(newState);
                ndp[newState] = max(ndp[newState], newValue);
            }
        }
        dp.swap(ndp);
        active.swap(nextActive);
    }
    int ans = -1;
    for (int state : active)
        ans = max(ans, dp[state]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    for (int tc = 1; tc <= testCnt; tc++) {
        int n, m;
        cin >> n >> m;
        vector<int> pat(m);
        for (int i = 0; i < m; i++) {
            string str;
            cin >> str;
            for (int j = 0; j < 5; j++)
                pat[i] = pat[i] * 2 + str[j] - '0';
        }
        cout << "Case " << tc << ": " << solveCase(n, m, pat) << '\n';
    }
    return 0;
}
