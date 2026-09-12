#include <bits/stdc++.h>
using namespace std;

int solve() {
    int t, cas;
    long long r, c, sr, sc, dr, dc;
    long long sum, now, rem, ans1, ans2;
    cin >> t;
    cas = 1;
    while (t--) {
        cin >> r >> c >> sr >> sc >> dr >> dc;
        cout << "Case " << cas << ": ";
        if (r < c) {
            swap(r, c);
            swap(sr, sc);
            swap(dr, dc);
        }
        if (c == 1 || (sr + sc + dr + dc) % 2 == 1) cout << "impossible\n";
        else if (abs(sr - dr) == abs(sc - dc)) cout << "1\n";
        else if (abs(sr - dr) < abs(sc - dc)) cout << "2\n";
        else {
            if (sr > dr) {
                swap(sr, dr);
                swap(sc, dc);
            }
            sum = dr - sr + sc - dc;
            now = (sum - 1) / (2 * c - 2);
            rem = (sum - 1) % (2 * c - 2);
            if (rem < 2 * (c - dc)) ans1 = 1;
            else ans1 = 2;
            ans1 += now * 2 + 1;
            sum = dr - sr + dc - sc;
            now = (sum - 1) / (2 * c - 2);
            rem = (sum - 1) % (2 * c - 2);
            if (rem < 2 * (dc - 1)) ans2 = 1;
            else ans2 = 2;
            ans2 += now * 2 + 1;
            cout << min(ans1, ans2) << '\n';
        }
        cas++;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
