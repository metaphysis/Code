#include <bits/stdc++.h>
using namespace std;

int n, m, target;
vector<vector<int> > rows;
map<tuple<int, int, int, int>, long double> memo;

long double dfs(int line, int cur, int dir, int rev) {
    if (cur == target)
        return 1.0L;
    tuple<int, int, int, int> state = make_tuple(line, cur, dir, rev);
    if (memo.count(state))
        return memo[state];
    int nextLine = line + dir;
    if (nextLine < 0 || nextLine >= m) {
        if (rev)
            return memo[state] = 0.0L;
        return memo[state] = dfs(line, cur, -dir, 1);
    }
    vector<int> cand;
    for (int player : rows[nextLine])
        if (player < cur)
            cand.push_back(player);
    if (cand.empty()) {
        if (rev)
            return memo[state] = 0.0L;
        return memo[state] = dfs(line, cur, -dir, 1);
    }
    long double ans = 0.0L;
    for (int player : cand)
        ans += dfs(nextLine, player, dir, rev);
    ans /= cand.size();
    return memo[state] = ans;
}

long double getProb(int line, int dir, int cur) {
    memo.clear();
    return dfs(line, cur, dir, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        cin >> n;
        m = 2 * n - 1;
        rows.assign(m, vector<int>());
        for (int i = 0; i < m; ++i) {
            int cnt = i < n ? i + 1 : m - i;
            rows[i].resize(cnt);
            for (int &player : rows[i])
                cin >> player;
        }
        cin >> target;
        long double q1 = getProb(0, 1, rows[0][0]);
        long double q2 = getProb(m - 1, -1, rows[m - 1][0]);
        long double ans = 1.0L - (1.0L - q1) * (1.0L - q2);
        long long result = static_cast<long long>(ans * 1000000000.0L);
        cout << result << '\n';
    }
    return 0;
}
