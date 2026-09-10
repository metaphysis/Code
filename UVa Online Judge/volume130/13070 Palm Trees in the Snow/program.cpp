// Palm Trees in the Snow
// UVa ID: 13070
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.070s

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int W, N;
        cin >> W >> N;
        vector<int> a(N);
        for (int i = 0; i < N; ++i) cin >> a[i];

        int left = 0, standing = 0, ans = 0;
        for (int right = 0; right < N; ++right) {
            if (a[right] >= W) ++standing;
            while (standing > 5) {
                if (a[left] >= W) --standing;
                ++left;
            }
            ans = max(ans, right - left + 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
