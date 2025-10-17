// Balanced Diet
// UVa ID: 1736
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.390s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int main() {
    int m, k;
    while (cin >> m >> k) {
        vector<long long> a(m);
        long long tot = 0;
        for (int i = 0; i < m; i++) {
            cin >> a[i];
            tot += a[i];
        }
        vector<long long> s(m, 0);
        for (int i = 0; i < k; i++) {
            int b;
            cin >> b;
            s[b - 1]++;
        }
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        for (int i = 0; i < m; i++) {
            long long next_n = ((s[i] + 1) * tot + a[i] - 1) / a[i];
            pq.push({next_n, i});
        }
        long long n = k;
        bool forever = false;
        while (true) {
            n++;
            auto [next_n, idx] = pq.top();
            if (next_n < n) {
                n = next_n;
                break;
            }
            pq.pop();
            s[idx]++;
            long long new_next_n = ((s[idx] + 1) * tot + a[idx] - 1) / a[idx];
            pq.push({new_next_n, idx});
            if (n % tot == 0) {
                forever = true;
                break;
            }
        }
        if (forever) {
            cout << "forever\n";
        } else {
            cout << n - k - 1 << "\n";
        }
    }
    return 0;
}
