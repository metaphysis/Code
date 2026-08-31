#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int n, m;
        long long mod;
        cin >> n >> m >> mod;
        int localCnt[305] = {}, need[305] = {};
        for (int i = 0; i < m; i++) {
            int queuePos, favorite;
            cin >> queuePos >> favorite;
            localCnt[favorite]++;
        }
        int foreignCount = n - m, localTotal = 0;
        bool possible = true;
        for (int i = 1; i <= n; i++) {
            localTotal += localCnt[i];
            need[i] = i - localTotal;
            if (need[i] < 0) need[i] = 0;
            if (need[i] > foreignCount) possible = false;
        }
        if (!possible) {
            cout << "NO\n";
            continue;
        }
        long long comb[305][305] = {};
        for (int i = 0; i <= foreignCount; i++) {
            comb[i][0] = comb[i][i] = 1 % mod;
            for (int j = 1; j < i; j++)
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
        }
        long long dp[305] = {}, nextDp[305] = {};
        dp[0] = 1 % mod;
        for (int pos = 1; pos <= n; pos++) {
            for (int i = 0; i <= foreignCount; i++) nextDp[i] = 0;
            for (int used = 0; used <= foreignCount; used++) {
                if (dp[used] == 0) continue;
                for (int add = 0; used + add <= foreignCount; add++) {
                    int total = used + add;
                    if (total < need[pos]) continue;
                    nextDp[total] = (nextDp[total] + dp[used] * comb[foreignCount - used][add]) % mod;
                }
            }
            for (int i = 0; i <= foreignCount; i++) dp[i] = nextDp[i];
        }
        cout << "YES " << dp[foreignCount] % mod << '\n';
    }
    return 0;
}
