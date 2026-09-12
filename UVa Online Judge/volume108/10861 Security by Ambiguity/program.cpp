#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> to, inCycle, expCnt;
vector<vector<int>> child;
map<vector<int>, int> treeMap, compMap;

void addVal(int val, int sign) {
    for (int p = 2; p <= val; p++) {
        while (val % p == 0) {
            expCnt[p] += sign;
            val /= p;
        }
    }
}

void addFact(int val, int sign) {
    for (int i = 2; i <= val; i++) addVal(i, sign);
}

int getTree(int u) {
    vector<int> seq;
    for (int v : child[u]) seq.push_back(getTree(v));
    sort(seq.begin(), seq.end());
    for (int i = 0, j; i < (int)seq.size(); i = j) {
        for (j = i; j < (int)seq.size() && seq[j] == seq[i]; j++);
        addFact(j - i, -1);
    }
    if (!treeMap.count(seq)) treeMap[seq] = (int)treeMap.size() + 1;
    return treeMap[seq];
}

vector<int> getCanon(vector<int> seq) {
    int len = seq.size();
    vector<int> best = seq, cur;
    for (int s = 1; s < len; s++) {
        cur.clear();
        for (int i = 0; i < len; i++) cur.push_back(seq[(s + i) % len]);
        if (cur < best) best = cur;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n && n) {
        to.assign(n, 0);
        inCycle.assign(n, 1);
        child.assign(n, vector<int>());
        expCnt.assign(n + 1, 0);
        treeMap.clear();
        compMap.clear();
        vector<int> deg(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> to[i];
            to[i]--;
            deg[to[i]]++;
        }
        queue<int> que;
        for (int i = 0; i < n; i++) if (deg[i] == 0) que.push(i);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            inCycle[u] = 0;
            if (--deg[to[u]] == 0) que.push(to[u]);
        }
        for (int i = 0; i < n; i++) if (!inCycle[i]) child[to[i]].push_back(i);
        addFact(n, 1);
        vector<int> vis(n, 0), compCnt;
        for (int i = 0; i < n; i++) {
            if (!inCycle[i] || vis[i]) continue;
            int u = i;
            vector<int> seq;
            do {
                vis[u] = 1;
                seq.push_back(getTree(u));
                u = to[u];
            } while (u != i);
            int len = seq.size(), rotCnt = 0;
            vector<int> best = getCanon(seq);
            for (int s = 0; s < len; s++) {
                bool same = true;
                for (int j = 0; j < len; j++) {
                    if (seq[j] != seq[(s + j) % len]) same = false;
                }
                if (same) rotCnt++;
            }
            addVal(rotCnt, -1);
            if (!compMap.count(best)) compMap[best] = (int)compMap.size();
            int id = compMap[best];
            if (id == (int)compCnt.size()) compCnt.push_back(0);
            compCnt[id]++;
        }
        for (int val : compCnt) addFact(val, -1);
        long long ans = 1;
        for (int p = 2; p <= n; p++) {
            for (int i = 0; i < expCnt[p]; i++) ans *= p;
        }
        cout << ans << '\n';
    }
    return 0;
}
