#include <bits/stdc++.h>
using namespace std;

const int maxN = 100;
const int maxMask = 1 << 12;
const int inf = 1e9;

int pile[maxN + 1], numMask[40];
int preMask[maxN + 1][maxMask], preValue[maxN + 1][maxMask];
int primes[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

void initMask() {
    for (int value = 1; value <= 39; value++) {
        int temp = value;
        numMask[value] = 0;
        for (int i = 0; i < 12; i++) {
            if (temp % primes[i] == 0) {
                numMask[value] |= 1 << i;
                while (temp % primes[i] == 0) temp /= primes[i];
            }
        }
    }
}

void solve(int n) {
    static int dp[maxMask], newDp[maxMask];
    for (int mask = 0; mask < maxMask; mask++) dp[mask] = inf;
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int mask = 0; mask < maxMask; mask++) newDp[mask] = inf;
        for (int mask = 0; mask < maxMask; mask++) {
            if (dp[mask] == inf) continue;
            for (int value = 1; value <= 39; value++) {
                if ((mask & numMask[value]) != 0) continue;
                int nextMask = mask | numMask[value];
                int cost = dp[mask] + abs(value - pile[i]);
                if (cost < newDp[nextMask]) {
                    newDp[nextMask] = cost;
                    preMask[i][nextMask] = mask;
                    preValue[i][nextMask] = value;
                }
            }
        }
        for (int mask = 0; mask < maxMask; mask++) dp[mask] = newDp[mask];
    }
    int endMask = 0;
    for (int mask = 1; mask < maxMask; mask++)
        if (dp[mask] < dp[endMask]) endMask = mask;
    static int answer[maxN + 1];
    for (int i = n; i >= 1; i--) {
        answer[i] = preValue[i][endMask];
        endMask = preMask[i][endMask];
    }
    static int caseId = 0;
    cout << "Case #" << ++caseId << ":";
    for (int i = 1; i <= n; i++) cout << " " << answer[i];
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    initMask();
    int n;
    while (cin >> n && n != 0) {
        for (int i = 1; i <= n; i++) cin >> pile[i];
        solve(n);
    }
    return 0;
}
