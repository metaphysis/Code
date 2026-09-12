#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, k, ans, st;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        vector<int> x(n);
        for (int i = 0; i < n; i++) cin >> x[i];
        sort(x.begin(), x.end());
        ans = 1;
        st = 0;
        for (int i = 1; i < n; i++) {
            if (x[i] - x[i - 1] > k) {
                ans = max(ans, i - st);
                st = i;
            } else if (i + 1 < n && x[i + 1] - x[i - 1] > k) {
                ans = max(ans, i - st + 1);
                st = i;
            }
        }
        ans = max(ans, n - st);
        cout << ans << '\n';
    }
    return 0;
}
