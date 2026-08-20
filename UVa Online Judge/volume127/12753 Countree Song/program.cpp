#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000009;
const int maxN = 512;
int comb[maxN + 1][9], ways[9][maxN + 1][maxN + 1];

void init() {
    int k, n, r, j;
    long long left, right;
    comb[0][0] = 1;
    for (r = 1; r <= maxN; r++) {
        comb[r][0] = 1;
        for (j = 1; j <= 8; j++)
            comb[r][j] = (comb[r - 1][j - 1] + comb[r - 1][j]) % mod;
    }
    for (k = 0; k <= 8; k++) {
        for (n = 0; n <= maxN; n++) {
            ways[k][n][0] = 1;
            for (r = 0; r < maxN; r++) {
                left = 0;
                right = 0;
                for (j = 1; j <= k && j <= r; j++)
                    left = (left + 1LL * comb[r][j] * ways[k][n][r - j + 1]) % mod;
                for (j = 0; j < k && j <= r; j++)
                    right = (right + 1LL * comb[r][j] * ways[k][n][r - j]) % mod;
                right = right * n % mod;
                ways[k][n][r + 1] = (right - left + mod) % mod;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, cs, d, k, i;
    long long ans;
    vector<int> cnt;
    init();
    cin >> t;
    for (cs = 1; cs <= t; cs++) {
        cin >> d >> k;
        cnt.resize(d + 1);
        for (i = 0; i <= d; i++)
            cin >> cnt[i];
        ans = 1;
        for (i = 0; i < d; i++)
            ans = ans * ways[k][cnt[i]][cnt[i + 1]] % mod;
        cout << "Case " << cs << ": " << ans << '\n';
    }
    return 0;
}
