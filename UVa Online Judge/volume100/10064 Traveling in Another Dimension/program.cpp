// Traveling in Another Dimension
// UVa ID: 10064
// Verdict: Accepted
// Submission Date: 2026-08-02
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cout << fixed << setprecision(2);
    while (cin >> n) {
        if (n == 0) {
            cout << "-1\n";
            continue;
        }
        vector<long long> values(n);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            cin >> values[i];
            sum += values[i];
        }
        sort(values.begin(), values.end());
        long double avg = static_cast<long double>(sum) / n;
        long long median = values[(n - 1) / 2];
        cout << avg << ' ' << static_cast<long double>(median) << '\n';
    }
    return 0;
}
