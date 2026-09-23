#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007;

int calcNext(int n, const int vals[]) {
    long long nSq = 1LL * n * n, weight = 1, sum = 0;
    long long coef[8] = {
        0,
        -3 * nSq,
        2 * nSq - 7,
        2 * nSq - 10LL * n + 20,
        -3 * nSq + 22LL * n - 41,
        nSq - 14LL * n + 39,
        2LL * n - 12,
        1
    };
    int limit = min(7, n);
    for (int j = 1; j <= limit; j++) {
        coef[j] %= mod;
        if (coef[j] < 0) coef[j] += mod;
        sum += coef[j] * weight % mod * vals[(n - j) & 7] % mod;
        if (j < limit) {
            long long nextSq = 1LL * (n - j) * (n - j) % mod;
            weight = weight * nextSq % mod;
        }
    }
    return (mod - sum % mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<pair<int, int>> queries;
    int n, queryId = 0, current = 0, vals[8] = {1};
    while (cin >> n) queries.emplace_back(n, queryId++);
    vector<int> answers(queryId);
    sort(queries.begin(), queries.end());
    for (const auto &query : queries) {
        while (current < query.first) {
            current++;
            vals[current & 7] = calcNext(current, vals);
        }
        answers[query.second] = vals[current & 7];
    }
    for (int answer : answers) cout << answer << '\n';
    return 0;
}
