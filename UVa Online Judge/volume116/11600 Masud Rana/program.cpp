// Masud Rana 
// UVa ID: 11600
// Verdict: Accepted
// Submission Date: 2025-11-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;
int n, m;
int parent[MAXN];
int compSize[MAXN];

int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }

void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (compSize[x] < compSize[y]) swap(x, y);
    parent[y] = x;
    compSize[x] += compSize[y];
}

map<pair<int, vector<int>>, double> dp;

double solve(int currentSize, vector<int> otherComps) {
    if (otherComps.empty()) return 0.0;
    sort(otherComps.begin(), otherComps.end());
    auto state = make_pair(currentSize, otherComps);
    if (dp.count(state)) return dp[state];
    int totalChoices = n - 1;
    double sameCompProb = (currentSize - 1.0) / totalChoices;
    double expectedOther = 0.0;
    for (int i = 0; i < otherComps.size(); i++) {
        double prob = otherComps[i] * 1.0 / totalChoices;
        vector<int> newOtherComps(otherComps);
        int newCurrentSize = currentSize + otherComps[i];
        newOtherComps.erase(newOtherComps.begin() + i);
        expectedOther += prob * (1.0 + solve(newCurrentSize, newOtherComps));
    }
    double result = (sameCompProb + expectedOther) / (1.0 - sameCompProb);
    return dp[state] = result;
}

int main() {
    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; caseNum++) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            compSize[i] = 1;
        }
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            unite(a, b);
        }
        map<int, int> compMap;
        int startCompRoot = find(1);
        for (int i = 1; i <= n; i++) compMap[find(i)]++;
        int currentSize = compMap[startCompRoot];
        vector<int> otherComps;
        for (auto& it : compMap)
            if (it.first != startCompRoot)
                otherComps.push_back(it.second);
        dp.clear();
        double expectedDays = solve(currentSize, otherComps);
        cout << "Case " << caseNum << ": " << fixed << setprecision(8) << expectedDays << endl;
    }
    return 0;
}
