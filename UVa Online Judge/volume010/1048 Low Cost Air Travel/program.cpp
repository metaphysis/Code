// Low Cost Air Travel
// UVa ID: 1048
// Verdict: Accepted
// Submission Date: 2023-11-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct block {
    int u, v, ticket;
} parent[512][512];

const int INF = 0x3f3f3f3f;
int d[512][512], visited[512][512];
map<int, int> idxer;
int idx;

int getId(int u) {
    if (idxer.count(u)) return idxer[u];
    return idxer[u] = idx++;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int NT, cases = 0;
    while (cin >> NT, NT) {
        vector<int> route[32], line;
        idx = 0;
        idxer.clear();
        int fee[32];
        for (int i = 0; i < NT; i++) {
            cin >> fee[i];
            int tcity, ncity;
            cin >> tcity;
            for (int j = 0; j < tcity; j++) {
                cin >> ncity;
                route[i].push_back(getId(ncity));
            }
        }
        int NI; cin >> NI;
        cases++;
        for (int i = 0; i < NI; i++) {
            int tcity, ncity;
            cin >> tcity;
            line.clear();
            for (int j = 0; j < tcity; j++) {
                cin >> ncity;
                line.push_back(getId(ncity));
            }
            memset(d, INF, sizeof d);
            memset(visited, 0, sizeof visited);
            int s = line.front();
            d[0][s] = 0;
            visited[0][s] = 1;
            queue<block> q;
            for (int i = 0; i < NT; i++)
                if (route[i].front() == s) {
                    parent[0][s] = block{-1, -1, i};
                    q.push(block{0, s, -1});
                }
            while (!q.empty()) {
                block b = q.front(); q.pop();
                visited[b.u][b.v] = 0;
                if (b.u + 1 == line.size()) continue;
                for (int j = 0; j < NT; j++) {
                    if (b.v != route[j].front()) continue;
                    int ci = b.u;
                    for (int k = 1; k < route[j].size(); k++) {
                        if (route[j][k] == line[ci + 1]) ci++;
                        int id = route[j][k];
                        if (d[ci][id] > d[b.u][b.v] + fee[j]) {
                            d[ci][id] = d[b.u][b.v] + fee[j];
                            parent[ci][id] = block{b.u, b.v, j + 1};
                            if (!visited[ci][id]) {
                                visited[ci][id] = 1;
                                q.push(block{ci, id, -1});
                            }
                        }
                        if (ci + 1 == line.size()) break;
                    }
                }
            }
            cout << "Case " << cases << ", Trip " << i + 1 << ": Cost = ";
            int t = line.back();
            cout << d[line.size() - 1][t] << '\n';
            cout << "  Tickets used:";
            int pi = line.size() - 1, pj = line.back();
            vector<int> path;
            while (pi || pj != s) {
                block b = block{parent[pi][pj].u, parent[pi][pj].v};
                path.push_back(parent[pi][pj].ticket);
                pi = b.u, pj = b.v;
            }
            reverse(path.begin(), path.end());
            for (auto p : path) cout << ' ' << p;
            cout << '\n';
        }
    }
    return 0;
}
