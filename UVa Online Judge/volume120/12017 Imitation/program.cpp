// Imitation
// UVa ID: 12017
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.070s

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N, M;
        cin >> N >> M;
        vector<bitset<MAXN>> reach(N);
        for (int i = 0; i < M; ++i) {
            int x, y;
            cin >> x >> y;
            --x; --y;
            if (x != y) reach[x][y] = 1;
        }
        // 传递闭包 (Warshall + bitset)
        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                if (reach[i][k]) reach[i] |= reach[k];
        // 并查集求强连通分量
        vector<int> parent(N);
        for (int i = 0; i < N; ++i) parent[i] = i;
        function<int(int)> find = [&](int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); };
        auto unite = [&](int a, int b) { int ra = find(a), rb = find(b); if (ra != rb) parent[ra] = rb; };
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                if (reach[i][j] && reach[j][i]) unite(i, j);
        // 收集分量
        vector<int> compId(N);
        vector<vector<int>> compNodes;
        unordered_map<int, int> rootToId;
        for (int i = 0; i < N; ++i) {
            int r = find(i);
            if (rootToId.find(r) == rootToId.end()) {
                rootToId[r] = compNodes.size();
                compNodes.push_back({});
            }
            int id = rootToId[r];
            compId[i] = id;
            compNodes[id].push_back(i);
        }
        int C = compNodes.size();
        vector<int> compSize(C);
        for (int i = 0; i < C; ++i) compSize[i] = compNodes[i].size();
        // 分量间的可达矩阵
        vector<bitset<MAXN>> compReach(C);
        for (int i = 0; i < N; ++i) {
            int a = compId[i];
            for (int j = 0; j < N; ++j) {
                if (reach[i][j]) {
                    int b = compId[j];
                    if (a != b) compReach[a][b] = 1;
                }
            }
        }
        // 内部边数（最小和最大）
        long long minInternal = 0, maxInternal = 0;
        for (int k : compSize) {
            if (k > 1) minInternal += k;
            maxInternal += 1LL * k * (k - 1);
        }
        // 跨分量总边数（最大）
        long long maxCross = 0;
        for (int a = 0; a < C; ++a)
            for (int b = 0; b < C; ++b)
                if (a != b && compReach[a][b])
                    maxCross += 1LL * compSize[a] * compSize[b];
        // 计算覆盖边数（Hasse 图边数）
        vector<bitset<MAXN>> pre(C);
        for (int a = 0; a < C; ++a)
            for (int b = 0; b < C; ++b)
                if (compReach[a][b]) pre[b].set(a);
        long long coverEdges = 0;
        for (int a = 0; a < C; ++a) {
            for (int b = 0; b < C; ++b) {
                if (a != b && compReach[a][b]) {
                    bitset<MAXN> inter = compReach[a] & pre[b];
                    if (inter.none()) ++coverEdges;
                }
            }
        }
        long long minAns = minInternal + coverEdges;
        long long maxAns = maxInternal + maxCross;
        cout << "Case #" << tc << ": " << minAns << " " << maxAns << "\n";
    }
    return 0;
}
