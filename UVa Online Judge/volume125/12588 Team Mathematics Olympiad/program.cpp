#include <bits/stdc++.h>
using namespace std;

int n, m, lowLim, highLim, baseNum;
bool need[35];
double prob[6][35];
vector<int> powerNum;
unordered_map<int, double> memo;

double dfs(int pos, int code, int ok) {
    if (pos == m) {
        int tmp = code;
        for (int i = 0; i < n; i++) {
            if (tmp % baseNum < lowLim) return -1e100;
            tmp /= baseNum;
        }
        return 0.0;
    }
    int key = code * 2 + ok;
    if (memo.count(key)) return memo[key];
    int cnt[6], tmp = code;
    for (int i = 0; i < n; i++) {
        cnt[i] = tmp % baseNum;
        tmp /= baseNum;
    }
    double ans = -1e100;
    for (int i = 0; i < n; i++) {
        if (cnt[i] == highLim) continue;
        int nextCode = code + powerNum[i];
        double cur;
        if (need[pos] && !ok) {
            cur = dfs(pos + 1, nextCode, 0);
        } else {
            cur = prob[i][pos] * (1.0 + dfs(pos + 1, nextCode, 1)) + (1.0 - prob[i][pos]) * dfs(pos + 1, nextCode, 0);
        }
        ans = max(ans, cur);
    }
    return memo[key] = ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cas = 1; cas <= t; cas++) {
        int k, x;
        cin >> n >> m;
        memset(need, false, sizeof(need));
        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> x;
            need[x - 1] = true;
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> prob[i][j];
        lowLim = m / n;
        highLim = (m + n - 1) / n;
        baseNum = highLim + 1;
        powerNum.assign(n, 1);
        for (int i = 1; i < n; i++) powerNum[i] = powerNum[i - 1] * baseNum;
        memo.clear();
        cout << "Case " << cas << ": " << fixed << setprecision(4) << dfs(0, 0, 1) << '\n';
    }
    return 0;
}
