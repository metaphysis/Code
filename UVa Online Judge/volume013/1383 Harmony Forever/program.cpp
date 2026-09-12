#include <bits/stdc++.h>
using namespace std;

const int maxVal = 500000;
const int lim = 710;

int best[lim + 1][lim + 1], ins[maxVal + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, cas = 0;
    while (cin >> t && t) {
        memset(best, 0, sizeof(best));
        set<int> nums;
        int cnt = 0;
        if (cas) cout << '\n';
        cout << "Case " << ++cas << ":\n";
        for (int i = 1; i <= t; i++) {
            char op;
            int x;
            cin >> op >> x;
            if (op == 'B') {
                cnt++;
                nums.insert(x);
                ins[x] = cnt;
                for (int y = 1; y <= lim; y++)
                    best[y][x % y] = cnt;
            } else {
                if (nums.empty()) {
                    cout << -1 << '\n';
                    continue;
                }
                int ans = -1;
                if (x <= lim) {
                    for (int r = 0; r < x; r++) {
                        if (best[x][r]) {
                            ans = best[x][r];
                            break;
                        }
                    }
                } else {
                    int minRem = maxVal + 1;
                    for (int base = 0; base <= maxVal; base += x) {
                        set<int>::iterator it = nums.lower_bound(base);
                        if (it == nums.end()) break;
                        if (*it < base + x) {
                            int rem = *it % x;
                            if (rem < minRem) {
                                minRem = rem;
                                ans = ins[*it];
                            } else if (rem == minRem && ins[*it] > ans) {
                                ans = ins[*it];
                            }
                        }
                    }
                }
                cout << ans << '\n';
            }
        }
    }
    return 0;
}
