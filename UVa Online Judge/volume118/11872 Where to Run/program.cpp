// Where to Run
// UVa ID: 11872
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.240s

#include <bits/stdc++.h>
using namespace std;

const int maxN = 15;
const int maxMask = 1 << maxN;

int n, m;
int edge[maxN][maxN];
bool canVisit[maxMask][maxN];
double expectTime[maxMask][maxN];

double getExpect(int mask, int cur) {
    if (expectTime[mask][cur] > -0.5) return expectTime[mask][cur];
    int nextMask = mask ^ (1 << cur), cnt = 0;
    double sum = 5.0;
    for (int nxt = 0; nxt < n; nxt++) {
        if ((nextMask & (1 << nxt)) && edge[cur][nxt] != -1 && canVisit[nextMask][nxt]) {
            cnt++;
            sum += edge[cur][nxt] + getExpect(nextMask, nxt);
        }
    }
    if (cnt == 0) return expectTime[mask][cur] = 0.0;
    return expectTime[mask][cur] = sum / cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test;
    cin >> test;
    for (int cas = 1; cas <= test; cas++) {
        cin >> n >> m;
        memset(edge, -1, sizeof(edge));
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            edge[u][v] = edge[v][u] = w;
        }
        memset(canVisit, 0, sizeof(canVisit));
        fill(&expectTime[0][0], &expectTime[0][0] + maxMask * maxN, -1.0);
        for (int u = 0; u < n; u++) canVisit[1 << u][u] = true;
        int fullMask = (1 << n) - 1;
        for (int mask = 1; mask <= fullMask; mask++) {
            for (int u = 0; u < n; u++) {
                if (!(mask & (1 << u)) || mask == (1 << u)) continue;
                int restMask = mask ^ (1 << u);
                for (int v = 0; v < n; v++) {
                    if ((restMask & (1 << v)) && edge[u][v] != -1 && canVisit[restMask][v]) {
                        canVisit[mask][u] = true;
                        break;
                    }
                }
            }
        }
        cout << "Case " << cas << ": " << fixed << setprecision(10) << getExpect(fullMask, 0) << '\n';
    }
    return 0;
}
