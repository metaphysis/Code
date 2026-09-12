#include <bits/stdc++.h>
using namespace std;

struct Show {
    int start, end, fun;
};

int parseTime(const string &str) {
    int pos = str.find(':');
    int hour = stoi(str.substr(0, pos));
    int minute = stoi(str.substr(pos + 1));
    int time = hour * 60 + minute;
    if (time < 6 * 60) time += 24 * 60;
    return time;
}

int solve() {
    int n, caseNo = 1;
    while (cin >> n && n) {
        vector<Show> shows(n + 1);
        for (int i = 1; i <= n; i++) {
            string period, name;
            cin >> period >> shows[i].fun;
            getline(cin, name);
            int pos = period.find('-');
            shows[i].start = parseTime(period.substr(0, pos));
            shows[i].end = parseTime(period.substr(pos + 1));
        }
        sort(shows.begin() + 1, shows.end(), [](const Show &a, const Show &b) {
            if (a.start != b.start) return a.start > b.start;
            return a.end > b.end;
        });
        const int negInf = -1000000000;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, negInf));
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            vector<vector<int>> next = dp;
            for (int a = 0; a <= n; a++) {
                for (int b = 0; b <= n; b++) {
                    if (dp[a][b] == negInf) continue;
                    if (a == 0 || shows[i].end <= shows[a].start)
                        next[i][b] = max(next[i][b], dp[a][b] + shows[i].fun);
                    if (b == 0 || shows[i].end <= shows[b].start)
                        next[a][i] = max(next[a][i], dp[a][b] + shows[i].fun);
                }
            }
            dp.swap(next);
        }
        int ans = 0;
        for (int a = 0; a <= n; a++)
            for (int b = 0; b <= n; b++)
                ans = max(ans, dp[a][b]);
        cout << "Case " << caseNo++ << ": " << ans << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
