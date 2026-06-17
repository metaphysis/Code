// Merging Maps
// UVa ID: 1033
// Verdict: Accepted
// Submission Date: 2026-06-17
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Map { int id, nr, nc; vector<string> g; };
struct Match { int s, r, c; bool ok; };

int getScore(const Map& a, const Map& b, int r, int c) {
    int s = 0;
    for (int i = 0; i < a.nr; ++i)
        for (int j = 0; j < a.nc; ++j) {
            if (a.g[i][j] == '-') continue;
            int x = i - r, y = j - c;
            if (x < 0 || x >= b.nr || y < 0 || y >= b.nc || b.g[x][y] == '-') continue;
            if (a.g[i][j] != b.g[x][y]) return -1;
            ++s;
        }
    return s;
}

Map merge(const Map& a, const Map& b, int r, int c, int id) {
    int minR = min(0, r), maxR = max(a.nr - 1, b.nr - 1 + r);
    int minC = min(0, c), maxC = max(a.nc - 1, b.nc - 1 + c);
    Map map{id, maxR - minR + 1, maxC - minC + 1,
            vector<string>(maxR - minR + 1, string(maxC - minC + 1, '-'))};
    for (int i = 0; i < a.nr; ++i)
        for (int j = 0; j < a.nc; ++j)
            if (a.g[i][j] != '-') map.g[i - minR][j - minC] = a.g[i][j];
    for (int i = 0; i < b.nr; ++i)
        for (int j = 0; j < b.nc; ++j)
            if (b.g[i][j] != '-') map.g[i + r - minR][j + c - minC] = b.g[i][j];
    return map;
}

Match getBestMatch(const Map& a, const Map& b) {
    Match best{0, 0, 0, false};
    // 枚举所有可能的偏移量
    for (int r = -(b.nr - 1); r <= a.nr - 1; ++r)
        for (int c = -(b.nc - 1); c <= a.nc - 1; ++c) {
            int s = getScore(a, b, r, c);
            if (s < 0) continue;
            if (s > best.s || (s == best.s && (r < best.r || (r == best.r && c < best.c))))
                best = {s, r, c, true};
        }
    return best;
}

void print(const Map& m) {
    cout << "    MAP " << m.id << ":\n    +" << string(m.nc, '-') << "+\n";
    for (auto& row : m.g) cout << "    |" << row << "|\n";
    cout << "    +" << string(m.nc, '-') << "+\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, cs = 0;
    while (cin >> n && n) {
        if (cs) cout << '\n';
        vector<Map> maps;
        for (int i = 1; i <= n; ++i) {
            Map m{i, 0, 0, {}};
            cin >> m.nr >> m.nc;
            m.g.resize(m.nr);
            cin.ignore(128, '\n');
            for (int r = 0; r < m.nr; ++r) {
                string line;
                getline(cin, line);
                m.g[r] = line.substr(0, m.nc);
            }
            maps.push_back(m);
        }
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        for (int nxt = n + 1; idx.size() > 1; ++nxt) {
            int bs = -1, bi = -1, bj = -1, br = 0, bc = 0;
            for (int i = 0; i < (int)idx.size(); ++i)
                for (int j = i + 1; j < (int)idx.size(); ++j) {
                    Match m = getBestMatch(maps[idx[i]], maps[idx[j]]);
                    if (!m.ok || m.s == 0) continue;
                    int curMin = min(maps[idx[i]].id, maps[idx[j]].id);
                    int bestMin = (bi == -1) ? INT_MAX : min(maps[idx[bi]].id, maps[idx[bj]].id);
                    if (m.s > bs || (m.s == bs && (curMin < bestMin ||
                        (curMin == bestMin && max(maps[idx[i]].id, maps[idx[j]].id) < max(maps[idx[bi]].id, maps[idx[bj]].id))))) {
                        bs = m.s; bi = i; bj = j; br = m.r; bc = m.c;
                    }
                }
            if (bs == -1 || bi == -1) break;
            Map merged = merge(maps[idx[bi]], maps[idx[bj]], br, bc, nxt);
            maps.push_back(merged);
            vector<int> ni;
            for (int i = 0; i < (int)idx.size(); ++i)
                if (i != bi && i != bj) ni.push_back(idx[i]);
            ni.push_back(maps.size() - 1);
            idx = ni;
        }
        cout << "Case " << ++cs << '\n';
        for (int i = 0; i < (int)idx.size(); ++i) {
            if (i) cout << '\n';
            print(maps[idx[i]]);
        }
    }
    return 0;
}
