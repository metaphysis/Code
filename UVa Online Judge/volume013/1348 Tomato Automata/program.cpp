#include <bits/stdc++.h>
using namespace std;

struct Cmd {
    string typ;
    int a, b;
};

struct Loop {
    int s, e, p;
    long long cnt, val;
    bool inf;
};

struct Solver {
    int n;
    vector<Cmd> cmd;
    vector<Loop> lp;
    vector<int> own;
    vector<vector<int>> child;
    vector<vector<int>> startAt;

    pair<bool, long long> calc(int q) {
        int key = q + 1;
        int l = q == -1 ? 1 : lp[q].s;
        int r = q == -1 ? n : lp[q].e;
        vector<pair<int, int>> items;
        for (int i = l; i <= r; i++)
            if (own[i] == q)
                items.push_back({i, i});
        for (int v : child[key])
            items.push_back({lp[v].s, -v - 1});
        sort(items.begin(), items.end());
        int m = (int)items.size();
        vector<int> lineId(n + 2, -1), weight(m), bad(m, 0);
        vector<vector<int>> graph(m);
        for (int i = 0; i < m; i++) {
            int pos = items[i].first;
            lineId[pos] = i;
            if (items[i].second >= 0) {
                weight[i] = 1;
            } else {
                int v = -items[i].second - 1;
                weight[i] = (int)lp[v].val;
                bad[i] = lp[v].inf;
            }
        }
        auto getId = [&](int x) {
            return lineId[x];
        };
        auto getNext = [&](int x) {
            int y = x + 1;
            if (q != -1 && y == r + 1) return -1;
            if (q == -1 && y == n + 1) y = 1;
            return getId(y);
        };
        for (int i = 0; i < m; i++) {
            int pos = items[i].first;
            if (items[i].second < 0) {
                int v = -items[i].second - 1;
                int nextPos = lp[v].e + 1;
                if (q == -1 && nextPos == n + 1) nextPos = 1;
                if (q != -1 && nextPos == r + 1) continue;
                graph[i].push_back(getId(nextPos));
                continue;
            }
            if (q != -1 && pos == r) continue;
            if (cmd[pos].typ == "ifgo") {
                graph[i].push_back(getId(cmd[pos].a));
                graph[i].push_back(getNext(pos));
            } else if (cmd[pos].typ == "jump") {
                graph[i].push_back(getId(cmd[pos].a));
            } else if (cmd[pos].typ == "pass") {
                graph[i].push_back(getNext(pos));
            }
        }
        int src = getId(l);
        vector<int> reach(m, 0), indeg(m, 0), topo;
        queue<int> que;
        que.push(src);
        reach[src] = 1;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            if (bad[u]) return {true, 0};
            for (int v : graph[u])
                if (v != -1 && !reach[v]) {
                    reach[v] = 1;
                    que.push(v);
                }
        }
        int reachCnt = 0;
        for (int i = 0; i < m; i++)
            if (reach[i]) {
                reachCnt++;
                for (int v : graph[i])
                    if (v != -1 && reach[v])
                        indeg[v]++;
            }
        for (int i = 0; i < m; i++)
            if (reach[i] && indeg[i] == 0)
                que.push(i);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            topo.push_back(u);
            for (int v : graph[u])
                if (v != -1 && reach[v] && --indeg[v] == 0)
                    que.push(v);
        }
        if ((int)topo.size() != reachCnt) return {true, 0};
        vector<long long> dp(m, 0);
        for (int i = (int)topo.size() - 1; i >= 0; i--) {
            int u = topo[i];
            dp[u] = weight[u];
            for (int v : graph[u])
                if (v != -1 && reach[v])
                    dp[u] = max(dp[u], (long long)weight[u] + dp[v]);
        }
        return {false, dp[src]};
    }

    string run(vector<string> lines) {
        n = (int)lines.size();
        cmd.assign(n + 1, {"", 0, 0});
        lp.clear();
        for (int i = 1; i <= n; i++) {
            stringstream ss(lines[i - 1]);
            ss >> cmd[i].typ;
            for (char &c : cmd[i].typ)
                c = (char)tolower(c);
            if (cmd[i].typ == "ifgo" || cmd[i].typ == "jump")
                ss >> cmd[i].a;
            else if (cmd[i].typ == "loop") {
                ss >> cmd[i].a >> cmd[i].b;
                lp.push_back({cmd[i].a, i, -1, cmd[i].b, 0, false});
            }
        }
        int k = (int)lp.size();
        vector<int> order(k), stackLoop;
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int x, int y) {
            if (lp[x].s != lp[y].s) return lp[x].s < lp[y].s;
            return lp[x].e > lp[y].e;
        });
        child.assign(k + 1, vector<int>());
        for (int v : order) {
            while (!stackLoop.empty() && lp[stackLoop.back()].e < lp[v].s)
                stackLoop.pop_back();
            lp[v].p = stackLoop.empty() ? -1 : stackLoop.back();
            child[lp[v].p + 1].push_back(v);
            stackLoop.push_back(v);
        }
        startAt.assign(n + 1, vector<int>());
        for (int i = 0; i < k; i++)
            startAt[lp[i].s].push_back(i);
        own.assign(n + 1, -1);
        stackLoop.clear();
        for (int i = 1; i <= n; i++) {
            while (!stackLoop.empty() && lp[stackLoop.back()].e < i)
                stackLoop.pop_back();
            for (int v : startAt[i])
                stackLoop.push_back(v);
            own[i] = stackLoop.empty() ? -1 : stackLoop.back();
        }
        sort(order.begin(), order.end(), [&](int x, int y) {
            return lp[x].e - lp[x].s < lp[y].e - lp[y].s;
        });
        for (int v : order) {
            pair<bool, long long> res = calc(v);
            lp[v].inf = res.first;
            if (!res.first)
                lp[v].val = res.second * lp[v].cnt;
        }
        pair<bool, long long> res = calc(-1);
        if (res.first) return "infinity";
        return to_string(res.second);
    }
};

bool isBlank(const string &s) {
    for (char c : s)
        if (!isspace((unsigned char)c))
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solver solver;
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        if (isBlank(line)) {
            if (!lines.empty()) {
                cout << solver.run(lines) << '\n';
                lines.clear();
            }
        } else {
            lines.push_back(line);
        }
    }
    if (!lines.empty())
        cout << solver.run(lines) << '\n';
    return 0;
}
