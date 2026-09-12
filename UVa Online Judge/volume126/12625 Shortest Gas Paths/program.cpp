#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);

void floyd(vector<vector<long long>>& dis, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dis[i][k] == inf) continue;
            for (int j = 0; j < n; j++) {
                if (dis[k][j] == inf) continue;
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}

int solve() {
    int n, r, q;
    cin >> n >> r >> q;
    vector<char> type(n);
    vector<int> gasId(n, -1), gas;
    for (int i = 0; i < n; i++) {
        cin >> type[i];
        if (type[i] == 'G') {
            gasId[i] = gas.size();
            gas.push_back(i);
        }
    }
    vector<vector<long long>> allDis(n, vector<long long>(n, inf));
    for (int i = 0; i < n; i++) allDis[i][i] = 0;
    for (int i = 0; i < r; i++) {
        int v, w, c;
        cin >> v >> w >> c;
        v--;
        w--;
        allDis[v][w] = min(allDis[v][w], (long long)c);
        allDis[w][v] = min(allDis[w][v], (long long)c);
    }
    floyd(allDis, n);
    int gasCnt = gas.size();
    vector<vector<long long>> gasDis(gasCnt, vector<long long>(gasCnt, inf));
    for (int i = 0; i < gasCnt; i++) {
        gasDis[i][i] = 0;
        for (int j = 0; j < gasCnt; j++) {
            if (allDis[gas[i]][gas[j]] <= 100) gasDis[i][j] = allDis[gas[i]][gas[j]];
        }
    }
    floyd(gasDis, gasCnt);
    vector<vector<long long>> toGas(n, vector<long long>(gasCnt, inf));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < gasCnt; j++) {
            if (allDis[i][gas[j]] <= 100) toGas[i][j] = allDis[i][gas[j]];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < gasCnt; j++) {
            for (int k = 0; k < gasCnt; k++) {
                if (toGas[i][k] == inf || gasDis[k][j] == inf) continue;
                toGas[i][j] = min(toGas[i][j], toGas[i][k] + gasDis[k][j]);
            }
        }
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        long long ans = inf;
        if (allDis[a][b] <= 100) ans = allDis[a][b];
        for (int i = 0; i < gasCnt; i++) {
            if (toGas[a][i] == inf) continue;
            if (allDis[gas[i]][b] > 100) continue;
            ans = min(ans, toGas[a][i] + allDis[gas[i]][b]);
        }
        if (ans == inf) cout << "NO GAS PATH\n";
        else cout << ans << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    for (int caseNo = 1; caseNo <= testCnt; caseNo++) {
        cout << "CASE " << caseNo << '\n';
        solve();
    }
    return 0;
}
