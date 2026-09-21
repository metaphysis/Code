#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007, inf = 1000000000;

void relax(int newCost, int addWays, int &bestCost, int &bestWays) {
    if (newCost < bestCost) {
        bestCost = newCost;
        bestWays = addWays;
    } else if (newCost == bestCost) {
        bestWays += addWays;
        if (bestWays >= mod) bestWays -= mod;
    }
}

pair<int, int> solve(const string &s) {
    int n = s.size();
    vector<int> curCost(n + 1, inf), nextCost(n + 1, inf), curWays(n + 1, 0), nextWays(n + 1, 0);
    curCost[0] = 0;
    curWays[0] = 1;
    for (int i = 0; i < n; i++) {
        fill(nextCost.begin(), nextCost.end(), inf);
        fill(nextWays.begin(), nextWays.end(), 0);
        int start = s[i] == '[' ? n : 0, step = s[i] == '[' ? -1 : 1;
        for (int b = start; b >= 0 && b <= n; b += step) {
            if (curCost[b] == inf) continue;
            if (s[i] == '[') {
                if (b < n) relax(curCost[b], curWays[b], nextCost[b + 1], nextWays[b + 1]);
                if (b > 0) relax(curCost[b] + 1, curWays[b], curCost[b - 1], curWays[b - 1]);
            } else {
                if (b > 0) relax(curCost[b], curWays[b], nextCost[b - 1], nextWays[b - 1]);
                if (b < n) relax(curCost[b] + 1, curWays[b], curCost[b + 1], curWays[b + 1]);
            }
        }
        curCost.swap(nextCost);
        curWays.swap(nextWays);
    }
    int minAdd = inf, ansWays = 0;
    for (int b = 0; b <= n; b++) if (curCost[b] != inf) relax(curCost[b] + b, curWays[b], minAdd, ansWays);
    return make_pair(minAdd, ansWays);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (getline(cin, s)) {
        if (!s.empty() && s.back() == '\r') s.pop_back();
        pair<int, int> ans = solve(s);
        cout << ans.first << ' ' << ans.second << '\n';
    }
    return 0;
}
