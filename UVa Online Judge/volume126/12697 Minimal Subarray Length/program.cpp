// Minimal Subarray Length
// UVa ID: 12697
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long x;
        cin >> n >> x;
        vector<long long> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];

        vector<long long> prefix(n + 1, 0);
        for (int i = 1; i <= n; i++) prefix[i] = prefix[i - 1] + arr[i - 1];

        int minLen = n + 1;
        deque<int> dq;

        for (int i = 0; i <= n; i++) {
            while (!dq.empty() && prefix[i] - prefix[dq.front()] >= x) {
                minLen = min(minLen, i - dq.front());
                dq.pop_front();
            }
            while (!dq.empty() && prefix[i] <= prefix[dq.back()]) dq.pop_back();
            dq.push_back(i);
        }

        if (minLen == n + 1) cout << -1 << "\n";
        else cout << minLen << "\n";
    }

    return 0;
}
