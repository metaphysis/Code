#include <bits/stdc++.h>
using namespace std;

const int mod = 10000;
const int maxN = 15;
const int maxM = 1 << maxN;
int n, fullMask;
int graphMask[maxN], edgeCnt[maxM], dp[maxM], powerTwo[106];

void prepareEdgeCount() {
    edgeCnt[0] = 0;
    for (int s = 1; s <= fullMask; ++s) {
        int bit = s & -s, v = __builtin_ctz(bit), rest = s ^ bit;
        edgeCnt[s] = edgeCnt[rest] + __builtin_popcount(graphMask[v] & rest);
    }
}

void countConnected() {
    dp[0] = 0;
    for (int s = 1; s <= fullMask; ++s) {
        int first = s & -s, total = powerTwo[edgeCnt[s]];
        for (int sub = (s - 1) & s; sub; sub = (sub - 1) & s) {
            if ((sub & first) == 0)
                continue;
            total -= dp[sub] * powerTwo[edgeCnt[s ^ sub]] % mod;
            if (total < 0)
                total += mod;
        }
        dp[s] = total;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int totalCase, testCase;
    cin >> totalCase;
    powerTwo[0] = 1;
    for (int i = 1; i <= 105; ++i)
        powerTwo[i] = powerTwo[i - 1] * 2 % mod;
    for (testCase = 1; testCase <= totalCase; ++testCase) {
        cin >> n;
        fullMask = (1 << n) - 1;
        for (int i = 0; i < n; ++i) {
            string row;
            cin >> row;
            graphMask[i] = 0;
            for (int j = 0; j < n; ++j)
                if (row[j] == 'Y')
                    graphMask[i] |= 1 << j;
        }
        prepareEdgeCount();
        countConnected();
        cout << "Case " << testCase << ": " << dp[fullMask] << '\n';
    }
    return 0;
}
