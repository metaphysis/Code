#include <bits/stdc++.h>
using namespace std;

void calculateDp(int n, const vector<vector<int>> &like, vector<long long> &dp) {
    int fullMask = (1 << n) - 1, mask, manId, womanId;
    dp.assign(1 << n, 0);
    dp[fullMask] = 1;
    for (mask = fullMask - 1; mask >= 0; mask--) {
        manId = __builtin_popcount(static_cast<unsigned int>(mask));
        for (womanId = 0; womanId < n; womanId++)
            if (!(mask & (1 << womanId)) && like[manId][womanId])
                dp[mask] += dp[mask | (1 << womanId)];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, caseId, n, i, j, manId, womanId, currentMask, chooseWoman;
    string manName, womanName, manToken, line;
    cin >> testCount;
    for (caseId = 1; caseId <= testCount; caseId++) {
        cin >> n;
        vector<string> men(n), women(n);
        unordered_map<string, int> manIndex, womanIndex;
        for (i = 0; i < n; i++) {
            cin >> men[i];
            manIndex[men[i]] = i;
        }
        for (i = 0; i < n; i++) {
            cin >> women[i];
            womanIndex[women[i]] = i;
        }
        vector<vector<int>> rawLike(n, vector<int>(n, 0));
        for (i = 0; i < n; i++) {
            cin >> manToken;
            manName = manToken.substr(0, manToken.size() - 1);
            getline(cin, line);
            stringstream input(line);
            manId = manIndex.find(manName)->second;
            while (input >> womanName) {
                auto it = womanIndex.find(womanName);
                if (it != womanIndex.end())
                    rawLike[manId][it->second] = 1;
            }
        }
        vector<int> manOrder(n), womanOrder(n);
        iota(manOrder.begin(), manOrder.end(), 0);
        iota(womanOrder.begin(), womanOrder.end(), 0);
        sort(manOrder.begin(), manOrder.end(), [&](int left, int right) {
            return men[left] < men[right];
        });
        sort(womanOrder.begin(), womanOrder.end(), [&](int left, int right) {
            return women[left] < women[right];
        });
        vector<vector<int>> like(n, vector<int>(n, 0));
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                like[i][j] = rawLike[manOrder[i]][womanOrder[j]];
        vector<long long> dp;
        calculateDp(n, like, dp);
        cout << "Case " << caseId << ":\n";
        if (dp[0] == 0) {
            cout << "No Way\n";
            continue;
        }
        cout << dp[0] << '\n';
        currentMask = 0;
        for (i = 0; i < n; i++) {
            chooseWoman = -1;
            for (j = 0; j < n; j++)
                if (!(currentMask & (1 << j)) && like[i][j] && dp[currentMask | (1 << j)] > 0) {
                    chooseWoman = j;
                    break;
                }
            if (i > 0)
                cout << ' ';
            cout << men[manOrder[i]] << ' ' << women[womanOrder[chooseWoman]];
            currentMask |= 1 << chooseWoman;
        }
        cout << '\n';
    }
    return 0;
}
