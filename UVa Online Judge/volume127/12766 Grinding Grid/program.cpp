// Grinding GridGrinding Grid
// UVa ID: 12766
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 1.9830s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Block {
    int minR, maxR, minC, maxC;
};

class DSU {
public:
    vector<int> parent, minR, maxR, minC, maxC;
    DSU(int n, const vector<int>& p) {
        parent.resize(n + 1);
        minR.resize(n + 1); maxR.resize(n + 1);
        minC.resize(n + 1); maxC.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
            minR[i] = maxR[i] = i;
            minC[i] = maxC[i] = p[i];
        }
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        parent[rb] = ra;
        minR[ra] = min(minR[ra], minR[rb]);
        maxR[ra] = max(maxR[ra], maxR[rb]);
        minC[ra] = min(minC[ra], minC[rb]);
        maxC[ra] = max(maxC[ra], maxC[rb]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> p(N + 1);
        for (int i = 1; i <= N; ++i) cin >> p[i];
        DSU dsu(N, p);
        for (int i = 1; i < N; ++i)
            if (abs(p[i] - p[i + 1]) == 1)
                dsu.unite(i, i + 1);
        vector<Block> blocks;
        for (int i = 1; i <= N; ++i)
            if (dsu.find(i) == i)
                blocks.push_back({dsu.minR[i], dsu.maxR[i], dsu.minC[i], dsu.maxC[i]});
        sort(blocks.begin(), blocks.end(), [](const Block& a, const Block& b) {
            return a.minR < b.minR;
        });
        int i = 0;
        while (i < (int)blocks.size() - 1) {
            Block& cur = blocks[i];
            Block& nxt = blocks[i + 1];
            bool rowAdj = (cur.maxR + 1 == nxt.minR);
            bool colAdj = (cur.maxC + 1 == nxt.minC) || (nxt.maxC + 1 == cur.minC);
            if (rowAdj && colAdj) {
                cur.maxR = nxt.maxR;
                cur.minC = min(cur.minC, nxt.minC);
                cur.maxC = max(cur.maxC, nxt.maxC);
                blocks.erase(blocks.begin() + i + 1);
                if (i > 0) --i;
            } else ++i;
        }
        bool ok = false;
        if (blocks.size() == 1) {
            const Block& b = blocks[0];
            if (b.minR == 1 && b.maxR == N && b.minC == 1 && b.maxC == N) ok = true;
        }
        cout << (ok ? "yes" : "no") << '\n';
    }
    return 0;
}
