#include <bits/stdc++.h>
using namespace std;

int n, target;
vector<int> deg, suf, totalMin, curMin, leftDeg;

bool checkFinal() {
    int i, pref = 0;
    for (i = 0; i < (int)leftDeg.size(); i++) {
        pref += leftDeg[i];
        if (pref > totalMin[i + 1] - curMin[i + 1]) return false;
    }
    return true;
}

bool dfs(int pos, int sum, int cnt) {
    int i;
    if (sum > target) return false;
    if (sum + suf[pos] < target) return false;
    if (cnt > n - deg[0]) return false;
    if (cnt > 0 && sum > totalMin[cnt] - curMin[cnt]) return false;
    if (pos == n) {
        if (sum != target) return false;
        return checkFinal();
    }
    for (i = 1; i <= n; i++) curMin[i] += min(i, deg[pos]);
    leftDeg.push_back(deg[pos]);
    if (dfs(pos + 1, sum + deg[pos], cnt + 1)) return true;
    leftDeg.pop_back();
    for (i = 1; i <= n; i++) curMin[i] -= min(i, deg[pos]);
    if (dfs(pos + 1, sum, cnt)) return true;
    return false;
}

bool canDraw(vector<int> input) {
    int i, j, total = 0;
    for (i = 0; i < n; i++) {
        if (input[i] < 0 || input[i] >= n) return false;
        total += input[i];
    }
    if (total % 2 != 0) return false;
    sort(input.rbegin(), input.rend());
    deg = input;
    target = total / 2;
    suf.assign(n + 1, 0);
    for (i = n - 1; i >= 0; i--) suf[i] = suf[i + 1] + deg[i];
    totalMin.assign(n + 1, 0);
    curMin.assign(n + 1, 0);
    for (i = 1; i <= n; i++) {
        for (j = 0; j < n; j++) totalMin[i] += min(i, deg[j]);
        curMin[i] = min(i, deg[0]);
    }
    leftDeg.clear();
    leftDeg.push_back(deg[0]);
    return dfs(1, deg[0], 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, caseId, i;
    cin >> testCount;
    for (caseId = 1; caseId <= testCount; caseId++) {
        cin >> n;
        vector<int> input(n);
        for (i = 0; i < n; i++) cin >> input[i];
        cout << "Case " << caseId << ": " << (canDraw(input) ? "YES" : "NO") << '\n';
    }
    return 0;
}
