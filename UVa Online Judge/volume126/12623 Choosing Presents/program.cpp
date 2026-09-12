#include <bits/stdc++.h>
using namespace std;

const long long inf = LLONG_MAX / 4;

long long hungarian(const vector<vector<long long>> &cost) {
    int n = cost.size(), m = cost[0].size();
    vector<long long> u(n + 1), v(m + 1), minVal(m + 1);
    vector<int> p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<bool> used(m + 1);
        fill(minVal.begin(), minVal.end(), inf);
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            long long delta = inf;
            for (int j = 1; j <= m; ++j) if (!used[j]) {
                long long cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                if (cur < minVal[j]) {
                    minVal[j] = cur;
                    way[j] = j0;
                }
                if (minVal[j] < delta) {
                    delta = minVal[j];
                    j1 = j;
                }
            }
            for (int j = 0; j <= m; ++j) if (used[j]) {
                u[p[j]] += delta;
                v[j] -= delta;
            } else {
                minVal[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }
    long long res = -v[0];
    for (int j = 1; j <= m; ++j) if (p[j] != 0 && cost[p[j] - 1][j - 1] >= inf / 2) return -1;
    return res;
}

long long getCost(const vector<int> &ans, const vector<long long> &price, const vector<vector<bool>> &like, int n, int m) {
    vector<int> friends, gifts;
    vector<bool> used(m);
    long long fixedCost = 0;
    for (int i = 0; i < n; ++i) {
        if (ans[i] != -1) {
            used[ans[i]] = true;
            fixedCost += price[ans[i]];
        } else {
            friends.push_back(i);
        }
    }
    for (int i = 0; i < m; ++i) if (!used[i]) gifts.push_back(i);
    if (friends.empty()) return fixedCost;
    if (friends.size() > gifts.size()) return -1;
    int fn = friends.size(), gn = gifts.size();
    vector<vector<long long>> cost(fn, vector<long long>(gn, inf));
    for (int i = 0; i < fn; ++i) {
        for (int j = 0; j < gn; ++j) {
            if (like[gifts[j]][friends[i]]) cost[i][j] = price[gifts[j]];
        }
    }
    long long remainCost = hungarian(cost);
    if (remainCost == -1) return -1;
    return fixedCost + remainCost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, m;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        vector<long long> price(m);
        vector<vector<bool>> like(m, vector<bool>(n));
        for (int i = 0; i < m; ++i) {
            int cnt, id;
            cin >> price[i] >> cnt;
            for (int j = 0; j < cnt; ++j) {
                cin >> id;
                like[i][id] = true;
            }
        }
        vector<int> ans(n, -1);
        long long bestCost = getCost(ans, price, like, n, m);
        if (bestCost == -1) {
            cout << "No solution.\n";
            continue;
        }
        vector<bool> used(m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (used[j] || !like[j][i]) continue;
                ans[i] = j;
                long long curCost = getCost(ans, price, like, n, m);
                if (curCost == bestCost) {
                    used[j] = true;
                    break;
                }
                ans[i] = -1;
            }
        }
        cout << bestCost;
        for (int i = 0; i < n; ++i) cout << ' ' << ans[i];
        cout << '\n';
    }
    return 0;
}
