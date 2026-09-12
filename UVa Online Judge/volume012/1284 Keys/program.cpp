#include <bits/stdc++.h>
using namespace std;

struct State {
    int score, cost;
};

vector<int> adj[26];
vector<array<array<State, 8>, 3> > dp;
int cnt[26][2];
bool used[26];
State bad = {-1000000000, 1000000000};

void relax(State &a, State b) {
    if (b.score > a.score || (b.score == a.score && b.cost < a.cost))
        a = b;
}

void dfs(int u, int fa) {
    for (int v : adj[u])
        if (v != fa)
            dfs(v, u);
    for (int col = 0; col < 3; col++) {
        array<State, 8> cur, nxt;
        for (int mask = 0; mask < 8; mask++)
            cur[mask] = bad;
        int mask = col == 0 ? 0 : (1 << (col - 1));
        int score = col == 0 ? 0 : cnt[u][col - 1];
        cur[mask] = {score, 0};
        for (int v : adj[u]) {
            if (v == fa)
                continue;
            for (int i = 0; i < 8; i++)
                nxt[i] = bad;
            for (int a = 0; a < 8; a++) {
                if (cur[a].score < 0)
                    continue;
                for (int childCol = 0; childCol < 3; childCol++) {
                    for (int b = 0; b < 8; b++) {
                        if (dp[v][childCol][b].score < 0)
                            continue;
                        int add = 0;
                        if (childCol != col)
                            add++;
                        if (childCol != 0 && childCol != col)
                            add++;
                        State now = {cur[a].score + dp[v][childCol][b].score, cur[a].cost + dp[v][childCol][b].cost + add};
                        relax(nxt[a | b], now);
                    }
                }
            }
            cur = nxt;
        }
        for (int mask = 0; mask < 8; mask++)
            dp[u][col][mask] = cur[mask];
    }
}

void solve(int caseNum) {
    int total = 0, need = 0;
    for (int i = 0; i < 26; i++) {
        total += cnt[i][0] + cnt[i][1];
        if (cnt[i][0] > 0)
            need |= 1;
        if (cnt[i][1] > 0)
            need |= 2;
    }
    dp.assign(26, {});
    vector<int> roots;
    bool vis[26] = {};
    for (int i = 0; i < 26; i++) {
        if (!used[i] || vis[i])
            continue;
        queue<int> que;
        que.push(i);
        vis[i] = true;
        roots.push_back(i);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int v : adj[u]) {
                if (vis[v])
                    continue;
                vis[v] = true;
                que.push(v);
            }
        }
    }
    State all[8];
    for (int mask = 0; mask < 8; mask++)
        all[mask] = bad;
    all[0] = {0, 0};
    for (int root : roots) {
        dfs(root, -1);
        State nxt[8];
        for (int mask = 0; mask < 8; mask++)
            nxt[mask] = bad;
        for (int a = 0; a < 8; a++) {
            if (all[a].score < 0)
                continue;
            for (int col = 0; col < 3; col++) {
                for (int b = 0; b < 8; b++) {
                    if (dp[root][col][b].score < 0)
                        continue;
                    State now = {all[a].score + dp[root][col][b].score, all[a].cost + dp[root][col][b].cost + (col != 0)};
                    relax(nxt[a | b], now);
                }
            }
        }
        for (int mask = 0; mask < 8; mask++)
            all[mask] = nxt[mask];
    }
    cout << "Case " << caseNum << ": ";
    if (all[need].score < 0) {
        cout << "impossible\n";
        return;
    }
    int groups = (need & 1 ? 1 : 0) + (need & 2 ? 1 : 0);
    int keyOps = 2 * (total - all[need].score);
    int ringOps = all[need].cost - groups;
    cout << keyOps << " " << ringOps << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int caseNum = 1;
    while (cin >> s) {
        if (s == "0") {
            solve(caseNum++);
            for (int i = 0; i < 26; i++) {
                adj[i].clear();
                cnt[i][0] = cnt[i][1] = 0;
                used[i] = false;
            }
            continue;
        }
        char a = s[0], b = s[1];
        if (islower(a) && islower(b)) {
            int u = a - 'a', v = b - 'a';
            adj[u].push_back(v);
            adj[v].push_back(u);
            used[u] = used[v] = true;
        } else {
            char key = isupper(a) ? a : b;
            char ring = islower(a) ? a : b;
            int u = ring - 'a';
            int owner = key <= 'M' ? 0 : 1;
            cnt[u][owner]++;
            used[u] = true;
        }
    }
    return 0;
}
