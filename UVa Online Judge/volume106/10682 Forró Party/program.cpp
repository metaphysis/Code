// Forró Party
// UVa ID: 10682
// Verdict: Accepted
// Submission Date: 2023-04-16
// UVa Run Time: 0.060s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;

struct edge { int v, w, nxt; } g[10010];
int head[510], cnt;
map<string, int> mp;
vector<string> city;

int getId(string s) {
    if (mp.count(s)) return mp[s];
    mp[s] = city.size();
    city.push_back(s);
    return mp[s];
}

int dist[510][1010];
vector<pair<int, int>> parent[510][1010];

struct block { int u, v, c; };

vector<int> path[510];

void dfs(int u, int w) {
    for (auto pr : parent[u][w]) {
        path[pr.first].push_back(u);
        if (pr.second)
            dfs(pr.first, pr.second);
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int R, cases = 0;
    while (cin >> R) {
        if (cases++) cout << '\n';
        memset(head, -1, sizeof head);
        cnt = 0;
        mp.clear();
        city.clear();
        string su, sv;
        int maxw = 0;
        for (int i = 0, w; i < R; i++) {
            cin >> su >> sv >> w;
            int u = getId(su), v = getId(sv);
            g[cnt] = edge{v, w, head[u]};
            head[u] = cnt++;
            g[cnt] = edge{u, w, head[v]};
            head[v] = cnt++;
            maxw = max(maxw, w);
        }
        cin >> su >> sv;
        int from = getId(su), to = getId(sv);
        for (int i = 0; i < city.size(); i++)
            for (int j = 0; j <= maxw; j++) {
                parent[i][j].clear();
                dist[i][j] = INF;
            }
        parent[from][0].push_back(make_pair(from, 0));
        dist[from][0] = 1;
        queue<block> q;
        q.push(block{from, 0, 1});
        while (!q.empty()) {
            block blk = q.front(); q.pop();
            for (int i = head[blk.u]; ~i; i = g[i].nxt) {
                if (g[i].w >= blk.v) {
                    if (dist[g[i].v][g[i].w] > blk.c + 1) {
                        dist[g[i].v][g[i].w] = blk.c + 1;
                        parent[g[i].v][g[i].w].clear();
                        parent[g[i].v][g[i].w].push_back(make_pair(blk.u, blk.v));
                        q.push(block{g[i].v, g[i].w, blk.c + 1});
                    } else if (dist[g[i].v][g[i].w] == blk.c + 1) {
                        parent[g[i].v][g[i].w].push_back(make_pair(blk.u, blk.v));
                    }
                }
            }
        }
        int r = INF;
        for (int i = 0; i <= maxw; i++) r = min(r, dist[to][i]);
        if (r == INF) cout << "No valid route.";
        else {
            for (int i = 0; i < city.size(); i++) path[i].clear();
            for (int i = 0; i <= maxw; i++)
                if (dist[to][i] == r)
                    dfs(to, i);
            for (int i = 0; i < city.size(); i++) sort(path[i].begin(), path[i].end());
            cout << city[from];
            while (path[from].size()) {
                from = path[from].front();
                cout << ' ' << city[from];
            }
        }
        cout << '\n';
    }
    return 0;
}
