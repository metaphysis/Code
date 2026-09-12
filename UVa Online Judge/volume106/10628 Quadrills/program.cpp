#include <bits/stdc++.h>
using namespace std;

struct Edge {
    unsigned long long mask;
    int type;
};

vector<Edge> edge[28];
int cellId[8][12], sqId[8][12], lab[14];
bool usedSq[14];
long long ans;

int getType(int a, int b) {
    if (a > b) swap(a, b);
    return a * 7 - a * (a - 1) / 2 + b - a;
}

long long dfs(int usedType, unsigned long long usedCell) {
    int best = -1, bestCnt = INT_MAX;
    for (int i = 0; i < 28; i++) if (!(usedType & (1 << i))) {
        int cnt = 0;
        for (const Edge &e : edge[i]) if (!(usedCell & e.mask)) cnt++;
        if (!cnt) return 0;
        if (cnt < bestCnt) best = i, bestCnt = cnt;
    }
    if (best == -1) return 1;
    long long res = 0;
    for (const Edge &e : edge[best]) if (!(usedCell & e.mask)) res += dfs(usedType | (1 << best), usedCell | e.mask);
    return res;
}

long long countWay() {
    for (int i = 0; i < 28; i++) edge[i].clear();
    for (int i = 0; i < 8; i++) for (int j = 0; j < 12; j++) if (cellId[i][j] != -1) {
        int dx[2] = {0, 1}, dy[2] = {1, 0};
        for (int k = 0; k < 2; k++) {
            int x = i + dx[k], y = j + dy[k];
            if (x >= 8 || y >= 12 || cellId[x][y] == -1) continue;
            int a = cellId[i][j], b = cellId[x][y];
            int t = getType(lab[sqId[i][j]], lab[sqId[x][y]]);
            edge[t].push_back({(1ULL << a) | (1ULL << b), t});
        }
    }
    return dfs(0, 0);
}

void genPair(int cnt) {
    int u = -1;
    for (int i = 0; i < 14; i++) if (!usedSq[i]) {
        u = i;
        break;
    }
    if (u == -1) {
        ans += countWay();
        return;
    }
    usedSq[u] = true;
    for (int v = u + 1; v < 14; v++) if (!usedSq[v]) {
        usedSq[v] = true;
        lab[u] = lab[v] = cnt;
        genPair(cnt + 1);
        usedSq[v] = false;
    }
    usedSq[u] = false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        string s[8];
        for (int i = 0; i < 8; i++) cin >> s[i];
        memset(cellId, -1, sizeof(cellId));
        memset(sqId, -1, sizeof(sqId));
        int sqCnt = 0, cellCnt = 0;
        for (int i = 0; i < 8; i++) for (int j = 0; j < 12; j++) if (s[i][j] == 'X') {
            for (int x = i; x < i + 2; x++) for (int y = j; y < j + 2; y++) {
                cellId[x][y] = cellCnt++;
                sqId[x][y] = sqCnt;
                s[x][y] = '.';
            }
            sqCnt++;
        }
        memset(usedSq, false, sizeof(usedSq));
        ans = 0;
        genPair(0);
        cout << ans << '\n';
    }
    return 0;
}
