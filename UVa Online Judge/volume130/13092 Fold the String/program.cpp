#include <bits/stdc++.h>
using namespace std;

long long solve() {
    int x, y, strLen, i, k, left, right, pos;
    long long ans, cost;
    string str;
    cin >> x >> y >> str;
    strLen = str.size();
    vector<int> d2(strLen), endPos(strLen);
    left = 0;
    right = -1;
    for (i = 0; i < strLen; i++) {
        k = i > right ? 0 : min(d2[left + right - i + 1], right - i + 1);
        while (i + k < strLen && i - k - 1 >= 0 && str[i + k] == str[i - k - 1]) k++;
        d2[i] = k--;
        if (i + k > right) {
            left = i - k - 1;
            right = i + k;
        }
    }
    for (i = 1; i < strLen; i++) endPos[i] = i + d2[i];
    const long long inf = 1LL << 60;
    vector<long long> dp(strLen + 1, inf);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> heap;
    dp[0] = 0;
    for (i = 1; i <= strLen; i++) {
        pos = i - 1;
        if (pos >= 1) heap.push({dp[pos], pos});
        while (!heap.empty() && (heap.top().second < (i + 1) / 2 || endPos[heap.top().second] < i)) heap.pop();
        dp[i] = dp[i - 1] + x;
        if (!heap.empty()) dp[i] = min(dp[i], heap.top().first + y);
    }
    ans = dp[strLen];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt, caseNo;
    cin >> testCnt;
    for (caseNo = 1; caseNo <= testCnt; caseNo++) cout << "Case " << caseNo << ": " << solve() << '\n';
    return 0;
}
