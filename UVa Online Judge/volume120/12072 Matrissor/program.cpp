#include <bits/stdc++.h>
using namespace std;

const int inf = 1000000000;

int getAns(const vector<int> &p, const vector<vector<int>> &one, const vector<vector<vector<int>>> &mul, int n, int cap) {
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, inf));
    for (int i = 1; i <= n; i++) dp[i][i] = 0;
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            int ans = inf;
            if (one[i][j] <= cap) ans = 1;
            if (ans == 1) {
                dp[i][j] = 1;
                continue;
            }
            vector<vector<int>> part(n + 2, vector<int>(n + 1, inf));
            for (int cur = i; cur < j; cur++)
                if (dp[i][cur] < inf && dp[i][cur] + 1 < ans) part[cur][dp[i][cur]] = 0;
            for (int cur = i; cur < j; cur++) {
                for (int used = 0; used + 1 < ans && used <= n; used++) {
                    int now = part[cur][used];
                    if (now > cap) continue;
                    for (int nxt = cur + 1; nxt <= j; nxt++) {
                        int child = dp[cur + 1][nxt];
                        if (child == inf || used + child + 1 >= ans) continue;
                        int add = mul[i][cur][nxt];
                        if (now > cap - add) continue;
                        int nextCost = now + add;
                        int nextUsed = used + child;
                        if (nxt == j) ans = nextUsed + 1;
                        else if (nextCost < part[nxt][nextUsed]) part[nxt][nextUsed] = nextCost;
                    }
                }
            }
            dp[i][j] = ans;
        }
    }
    return dp[1][n] == inf ? -1 : dp[1][n];
}

void solveCase(int id) {
    int n;
    cin >> n;
    vector<int> p(n + 2);
    for (int i = 1; i <= n; i++) cin >> p[i] >> p[i + 1];
    vector<vector<int>> one(n + 2, vector<int>(n + 2, 0));
    vector<vector<vector<int>>> mul(n + 2, vector<vector<int>>(n + 2, vector<int>(n + 2, 0)));
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            one[i][j] = one[i][j - 1] + p[i] * p[j] * p[j + 1];
            for (int cur = i; cur < j; cur++) mul[i][cur][j] = p[i] * p[cur + 1] * p[j + 1];
        }
    }
    int q;
    cin >> q;
    cout << "Matrix #" << id << '\n';
    while (q--) {
        int cap;
        cin >> cap;
        int ans = getAns(p, one, mul, n, cap);
        if (ans == -1) cout << "Impossible.\n";
        else cout << ans << '\n';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int id = 1; id <= t; id++) solveCase(id);
    return 0;
}
