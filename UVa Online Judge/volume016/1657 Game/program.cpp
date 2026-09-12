#include <bits/stdc++.h>
using namespace std;

vector<int> getCount(const vector<pair<int, int>>& state, bool bySum, int n) {
    vector<int> count(bySum ? 2 * n + 1 : n * n + 1, 0);
    for (const auto& p : state) {
        int key = bySum ? p.first + p.second : p.first * p.second;
        ++count[key];
    }
    return count;
}

void removeKnown(vector<pair<int, int>>& state, bool bySum, int n) {
    vector<int> count = getCount(state, bySum, n);
    vector<pair<int, int>> nextState;
    for (const auto& p : state) {
        int key = bySum ? p.first + p.second : p.first * p.second;
        if (count[key] > 1) nextState.push_back(p);
    }
    state = nextState;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        vector<pair<int, int>> state;
        for (int x = 1; x <= n; ++x)
            for (int y = x + 1; y <= n; ++y)
                state.push_back({x, y});
        for (int i = 0; i < m; ++i)
            removeKnown(state, i % 2 == 0, n);
        bool bySum = m % 2 == 0;
        vector<int> count = getCount(state, bySum, n);
        vector<pair<int, int>> answer;
        for (const auto& p : state) {
            int key = bySum ? p.first + p.second : p.first * p.second;
            if (count[key] == 1) answer.push_back(p);
        }
        cout << answer.size() << '\n';
        for (const auto& p : answer)
            cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}
