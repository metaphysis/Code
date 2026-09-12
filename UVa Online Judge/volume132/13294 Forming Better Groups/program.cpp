#include <bits/stdc++.h>
using namespace std;

int n, d, allMask;
vector<int> grade;
vector<long long> memo;

long long dfs(int mask) {
    if (mask == allMask) return 1;
    long long &res = memo[mask];
    if (res != -1) return res;
    int i = 0;
    while (mask & (1 << i)) i++;
    res = 0;
    for (int j = i + 1; j < n; j++) {
        if (mask & (1 << j)) continue;
        for (int k = j + 1; k < n; k++) {
            if (mask & (1 << k)) continue;
            if (grade[k] - grade[i] > d) break;
            res += dfs(mask | (1 << i) | (1 << j) | (1 << k));
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> d, n || d) {
        grade.resize(n);
        for (int i = 0; i < n; i++) cin >> grade[i];
        sort(grade.begin(), grade.end());
        allMask = (1 << n) - 1;
        memo.assign(1 << n, -1);
        cout << dfs(0) << '\n';
    }
    return 0;
}
