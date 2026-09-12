#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, maxN = 0;
    cin >> t;
    vector<int> val(t), ans;
    for (int i = 0; i < t; i++) {
        cin >> val[i];
        maxN = max(maxN, val[i]);
    }
    vector<unsigned long long> mark((1LL * maxN * maxN >> 6) + 1, 0);
    ans.assign(maxN + 1, 0);
    int cur = 0;
    for (int j = 1; j <= maxN; j++) {
        for (int i = 1; i <= j; i++) {
            int num = i * j, pos = num >> 6;
            unsigned long long bit = 1ULL << (num & 63);
            if ((mark[pos] & bit) == 0) {
                mark[pos] |= bit;
                cur++;
            }
        }
        ans[j] = cur + 1;
    }
    for (int i = 0; i < t; i++)
        cout << ans[val[i]] << '\n';
    return 0;
}
