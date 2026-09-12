#include <bits/stdc++.h>
using namespace std;

int n;
int deg[105];
int revPos[105][105];
vector<int> roomNext[105];
vector<int> stateCls[105];

vector<int> getStateKey(int u, int p) {
    vector<int> key;
    int v = roomNext[u][p];
    int start = revPos[v][u];
    for (int i = 0; i < deg[v]; i++)
        key.push_back(stateCls[v][(start + i) % deg[v]]);
    return key;
}

vector<int> getRoomKey(int u) {
    vector<int> src, best;
    for (int i = 0; i < deg[u]; i++)
        src.push_back(stateCls[u][i]);
    if (src.empty())
        return src;
    best = src;
    for (int s = 1; s < deg[u]; s++) {
        vector<int> cur;
        for (int i = 0; i < deg[u]; i++)
            cur.push_back(src[(s + i) % deg[u]]);
        if (cur < best)
            best = cur;
    }
    return best;
}

void buildClass() {
    for (int i = 1; i <= n; i++)
        stateCls[i].assign(deg[i], 0);
    while (true) {
        map<vector<int>, int> idMap;
        vector<int> newCls[105];
        int idCnt = 0;
        for (int i = 1; i <= n; i++)
            newCls[i].resize(deg[i]);
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < deg[i]; j++) {
                vector<int> key = getStateKey(i, j);
                if (!idMap.count(key))
                    idMap[key] = idCnt++;
                newCls[i][j] = idMap[key];
            }
        }
        bool same = true;
        for (int i = 1; i <= n; i++)
            if (newCls[i] != stateCls[i])
                same = false;
        for (int i = 1; i <= n; i++)
            stateCls[i] = newCls[i];
        if (same)
            break;
    }
}

void solveCase() {
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;
        deg[i] = k;
        roomNext[i].resize(k);
        for (int j = 0; j < k; j++)
            cin >> roomNext[i][j];
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < deg[i]; j++)
            revPos[i][roomNext[i][j]] = j;
    buildClass();
    map<vector<int>, vector<int> > groups;
    for (int i = 1; i <= n; i++)
        groups[getRoomKey(i)].push_back(i);
    vector<vector<int> > ans;
    for (map<vector<int>, vector<int> >::iterator it = groups.begin(); it != groups.end(); ++it)
        if (it->second.size() >= 2)
            ans.push_back(it->second);
    sort(ans.begin(), ans.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[0] < b[0];
    });
    if (ans.empty()) {
        cout << "none\n";
        return;
    }
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) {
            if (j > 0)
                cout << ' ';
            cout << ans[i][j];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool first = true;
    while (cin >> n) {
        if (!first)
            cout << '\n';
        first = false;
        solveCase();
    }
    return 0;
}
