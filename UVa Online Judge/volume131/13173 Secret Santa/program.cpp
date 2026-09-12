#include <bits/stdc++.h>
using namespace std;

int p, a;
vector<vector<int> > adj;

bool findPath(int u, int banU, int banV, vector<int>& mat, vector<int>& vis) {
    for (int v = 1; v <= p; v++) {
        if (!adj[u][v] || (u == banU && v == banV) || vis[v])
            continue;
        vis[v] = 1;
        if (mat[v] == 0 || findPath(mat[v], banU, banV, mat, vis)) {
            mat[v] = u;
            return true;
        }
    }
    return false;
}

int getMatch(int banU, int banV, vector<int>& leftMat) {
    vector<int> mat(p + 1, 0);
    int cnt = 0;
    for (int u = 1; u <= p; u++) {
        vector<int> vis(p + 1, 0);
        if (findPath(u, banU, banV, mat, vis))
            cnt++;
    }
    leftMat.assign(p + 1, 0);
    for (int v = 1; v <= p; v++)
        if (mat[v] != 0)
            leftMat[mat[v]] = v;
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> p >> a && p != 0) {
        vector<int> known(p + 1, 0);
        bool ok = true;
        for (int i = 0; i < a; i++) {
            int u, v;
            cin >> u >> v;
            if (u == v)
                ok = false;
            if (known[u] != 0 && known[u] != v)
                ok = false;
            known[u] = v;
        }
        adj.assign(p + 1, vector<int>(p + 1, 0));
        for (int u = 1; u <= p; u++) {
            if (known[u] != 0)
                adj[u][known[u]] = 1;
            else {
                for (int v = 1; v <= p; v++)
                    if (u != v)
                        adj[u][v] = 1;
            }
        }
        vector<int> baseMat;
        if (!ok || getMatch(0, 0, baseMat) != p) {
            cout << "NO\n";
            continue;
        }
        for (int u = 1; u <= p; u++) {
            vector<int> tempMat;
            if (getMatch(u, baseMat[u], tempMat) == p) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
