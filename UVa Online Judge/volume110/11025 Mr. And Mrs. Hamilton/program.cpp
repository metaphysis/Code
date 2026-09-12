#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, caseNo;
    cin >> testCount;
    for (caseNo = 1; caseNo <= testCount; caseNo++) {
        int n, m, speed;
        cin >> n >> m >> speed;
        vector<int> deg(n, 0);
        vector<vector<long long>> dist(n, vector<long long>(n, inf));
        int a, b;
        long long w;
        for (int i = 0; i < n; i++)
            dist[i][i] = 0;
        for (int i = 0; i < m; i++) {
            cin >> a >> b >> w;
            dist[a][b] = w;
            dist[b][a] = w;
            deg[a]++;
            deg[b]++;
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
        int full = (1 << n) - 1;
        vector<int> sumDeg(1 << n, 0);
        for (int mask = 1; mask <= full; mask++) {
            int bit = mask & -mask;
            int id = __builtin_ctz(bit);
            sumDeg[mask] = sumDeg[mask ^ bit] + deg[id];
        }
        vector<vector<long long>> dp(1 << n, vector<long long>(n, inf));
        vector<vector<vector<int>>> seq(1 << n, vector<vector<int>>(n));
        for (int i = 0; i < n; i++) {
            int mask = 1 << i;
            dp[mask][i] = 0;
            seq[mask][i].push_back(i);
        }
        for (int mask = 1; mask <= full; mask++) {
            for (int u = 0; u < n; u++) {
                if ((mask & (1 << u)) == 0 || dp[mask][u] == inf)
                    continue;
                for (int v = 0; v < n; v++) {
                    if (mask & (1 << v))
                        continue;
                    int nextMask = mask | (1 << v);
                    long long nextCost = dp[mask][u] + dist[u][v] * sumDeg[mask];
                    vector<int> nextSeq;
                    nextSeq.push_back(v);
                    nextSeq.insert(nextSeq.end(), seq[mask][u].begin(), seq[mask][u].end());
                    if (nextCost < dp[nextMask][v] || (nextCost == dp[nextMask][v] && nextSeq < seq[nextMask][v])) {
                        dp[nextMask][v] = nextCost;
                        seq[nextMask][v] = nextSeq;
                    }
                }
            }
        }
        long long weightedBack = 0;
        for (int i = 1; i < n; i++)
            weightedBack += 1LL * deg[i] * dist[i][0];
        long long numerator = dp[full][0] + weightedBack;
        long long denominator = 2LL * m * speed;
        long long common = __gcd(numerator, denominator);
        numerator /= common;
        denominator /= common;
        cout << "Case " << caseNo << ":\n";
        cout << numerator << "/" << denominator << "\n";
        for (int i = 0; i < n; i++) {
            if (i)
                cout << ' ';
            cout << seq[full][0][i];
        }
        cout << "\n";
        if (caseNo != testCount)
            cout << "\n";
    }
    return 0;
}
