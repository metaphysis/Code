#include <bits/stdc++.h>
using namespace std;

struct Record {
    int ver, left, right;
};

int solveCase(int n, int m) {
    vector<set<int> > graph(n + 1);
    vector<int> deg(n + 1), active(n + 1, 1), nextVer(n + 1);
    vector<Record> records;
    queue<int> que;
    for (int i = 0; i < n + m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }
    for (int i = 1; i <= n; i++) {
        deg[i] = graph[i].size();
        if (deg[i] == 2) que.push(i);
    }
    int leftCount = n;
    while (leftCount > 3) {
        while (!que.empty() && (!active[que.front()] || deg[que.front()] != 2)) que.pop();
        int ver = que.front();
        que.pop();
        vector<int> nei(graph[ver].begin(), graph[ver].end());
        int left = nei[0], right = nei[1];
        records.push_back({ver, left, right});
        active[ver] = 0;
        graph[left].erase(ver);
        graph[right].erase(ver);
        graph[ver].clear();
        if (!graph[left].count(right)) {
            graph[left].insert(right);
            graph[right].insert(left);
        }
        deg[left] = graph[left].size();
        deg[right] = graph[right].size();
        if (deg[left] == 2) que.push(left);
        if (deg[right] == 2) que.push(right);
        leftCount--;
    }
    vector<int> base;
    for (int i = 1; i <= n; i++)
        if (active[i]) base.push_back(i);
    nextVer[base[0]] = base[1];
    nextVer[base[1]] = base[2];
    nextVer[base[2]] = base[0];
    for (int i = (int)records.size() - 1; i >= 0; i--) {
        int ver = records[i].ver, left = records[i].left, right = records[i].right;
        if (nextVer[left] == right) {
            nextVer[left] = ver;
            nextVer[ver] = right;
        } else {
            nextVer[right] = ver;
            nextVer[ver] = left;
        }
    }
    vector<int> pre(n + 1), ans;
    int cur = 1, first = nextVer[1];
    while (nextVer[cur] != 1) cur = nextVer[cur];
    first = min(first, cur);
    cur = 1;
    if (nextVer[1] != first) {
        for (int i = 1; i <= n; i++)
            pre[nextVer[i]] = i;
        for (int i = 0; i < n; i++) {
            ans.push_back(cur);
            cur = pre[cur];
        }
    } else {
        for (int i = 0; i < n; i++) {
            ans.push_back(cur);
            cur = nextVer[cur];
        }
    }
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cases;
    cin >> cases;
    for (int i = 0; i < cases; i++) {
        int n, m;
        cin >> n >> m;
        if (i) cout << '\n';
        solveCase(n, m);
    }
    return 0;
}
