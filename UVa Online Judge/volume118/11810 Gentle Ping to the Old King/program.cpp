#include <bits/stdc++.h>
using namespace std;

const int maxN = 16;
const int maxMask = 1 << maxN;
const long long inf = 0x3f3f3f3f3f3f3f3fLL;

int n, m, k, primeMask;
int edgeCost[maxN][maxN];
int bitCount[maxMask], primeCount[maxMask];
long long dp[maxMask][maxN], attachCost[maxN][maxMask], partCost[maxN][maxMask];

long long getCrossCost(int mask) {
    int size = bitCount[mask], primes = primeCount[mask];
    return 1LL * primes * (n - size) + 1LL * (k - primes) * size;
}

long long solve() {
    int fullMask = (1 << n) - 1, mask, root, rest, lowBit, sub, nextRest, x;
    long long best, candidate, answer;
    memset(dp, 0x3f, sizeof(dp));
    memset(attachCost, 0x3f, sizeof(attachCost));
    memset(partCost, 0x3f, sizeof(partCost));
    for (mask = 1; mask <= fullMask; mask++) {
        lowBit = mask & -mask;
        bitCount[mask] = bitCount[mask ^ lowBit] + 1;
        primeCount[mask] = primeCount[mask ^ lowBit] + ((primeMask & lowBit) != 0);
    }
    for (root = 0; root < n; root++)
        partCost[root][0] = 0;
    for (mask = 1; mask <= fullMask; mask++) {
        for (root = 0; root < n; root++) {
            if ((mask & (1 << root)) == 0) continue;
            rest = mask ^ (1 << root);
            if (rest == 0) {
                dp[mask][root] = 0;
                continue;
            }
            lowBit = rest & -rest;
            best = inf;
            for (sub = rest; sub; sub = (sub - 1) & rest) {
                if ((sub & lowBit) == 0) continue;
                nextRest = rest ^ sub;
                candidate = attachCost[root][sub] + partCost[root][nextRest];
                if (candidate < best) best = candidate;
            }
            partCost[root][rest] = best;
            dp[mask][root] = best;
        }
        for (root = 0; root < n; root++) {
            if (mask & (1 << root)) continue;
            best = inf;
            for (x = 0; x < n; x++) {
                if ((mask & (1 << x)) == 0) continue;
                if (edgeCost[root][x] >= inf) continue;
                candidate = dp[mask][x] + 1LL * edgeCost[root][x] * getCrossCost(mask);
                if (candidate < best) best = candidate;
            }
            attachCost[root][mask] = best;
        }
    }
    answer = inf;
    for (root = 0; root < n; root++)
        if (dp[fullMask][root] < answer) answer = dp[fullMask][root];
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase, caseNumber, i, u, v, w;
    cin >> testCase;
    for (caseNumber = 1; caseNumber <= testCase; caseNumber++) {
        cin >> n >> m >> k;
        primeMask = 0;
        for (i = 0; i < k; i++) {
            cin >> u;
            primeMask |= 1 << u;
        }
        for (i = 0; i < maxN; i++)
            for (int j = 0; j < maxN; j++)
                edgeCost[i][j] = i == j ? 0 : inf;
        for (i = 0; i < m; i++) {
            cin >> u >> v >> w;
            edgeCost[u][v] = edgeCost[v][u] = w;
        }
        cout << "Case " << caseNumber << ": " << solve() << '\n';
    }
    return 0;
}
