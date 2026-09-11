// Coalescing Continents
// UVa ID: 12352
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int h, w, sr, sc;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        vector<string> grid(20);
        for (int i = 0; i < 20; ++i) cin >> grid[i];
        vector<vector<int>> comp(20, vector<int>(20, -1));
        vector<Rect> rects;
        bool invalid = false;
        int dirR[4] = {-1, 1, 0, 0};
        int dirC[4] = {0, 0, -1, 1};
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                if (grid[i][j] != 'x' || comp[i][j] != -1) continue;
                int id = (int)rects.size();
                queue<pair<int, int>> q;
                comp[i][j] = id;
                q.push({i, j});
                int minR = i, maxR = i, minC = j, maxC = j;
                while (!q.empty()) {
                    auto p = q.front(); q.pop();
                    int r = p.first, c = p.second;
                    if (r < minR) minR = r;
                    if (r > maxR) maxR = r;
                    if (c < minC) minC = c;
                    if (c > maxC) maxC = c;
                    for (int d = 0; d < 4; ++d) {
                        int nr = r + dirR[d], nc = c + dirC[d];
                        if (nr >= 0 && nr < 20 && nc >= 0 && nc < 20 &&
                            grid[nr][nc] == 'x' && comp[nr][nc] == -1) {
                            comp[nr][nc] = id;
                            q.push({nr, nc});
                        }
                    }
                }
                for (int r = minR; r <= maxR; ++r)
                    for (int c = minC; c <= maxC; ++c)
                        if (grid[r][c] != 'x') invalid = true;
                int h = maxR - minR + 1, w = maxC - minC + 1;
                if (h > 5 || w > 5) invalid = true;
                rects.push_back({h, w, minR, minC});
            }
        }
        int total = 0;
        for (auto &r : rects) total += r.h * r.w;
        if (total != 25) invalid = true;
        if ((int)rects.size() > 5) invalid = true;
        if (invalid) {
            cout << "Case " << tc << ": invalid data\n";
            continue;
        }
        sort(rects.begin(), rects.end(), [](const Rect &a, const Rect &b) {
            return a.h * a.w > b.h * b.w;
        });
        int K = (int)rects.size();
        vector<vector<int>> masks(K);
        vector<vector<pair<int, int>>> offsets(K);
        for (int i = 0; i < K; ++i) {
            int h = rects[i].h, w = rects[i].w;
            for (int dr = 0; dr + h <= 5; ++dr) {
                for (int dc = 0; dc + w <= 5; ++dc) {
                    int mask = 0;
                    for (int r = 0; r < h; ++r)
                        for (int c = 0; c < w; ++c)
                            mask |= (1 << ((dr + r) * 5 + (dc + c)));
                    masks[i].push_back(mask);
                    offsets[i].push_back({dr, dc});
                }
            }
        }
        int fullMask = (1 << 25) - 1;
        int best = INT_MAX;
        vector<pair<int, int>> placement(K);
        function<void(int, int)> dfs = [&](int idx, int mask) {
            if (idx == K) {
                if (mask == fullMask) {
                    vector<int> a(K), b(K);
                    for (int i = 0; i < K; ++i) {
                        a[i] = rects[i].sr - placement[i].first;
                        b[i] = rects[i].sc - placement[i].second;
                    }
                    sort(a.begin(), a.end());
                    sort(b.begin(), b.end());
                    int r0 = a[K / 2], c0 = b[K / 2];
                    int cost = 0;
                    for (int i = 0; i < K; ++i) {
                        cost += abs(r0 - (rects[i].sr - placement[i].first));
                        cost += abs(c0 - (rects[i].sc - placement[i].second));
                    }
                    if (cost < best) best = cost;
                }
                return;
            }
            for (int p = 0; p < (int)masks[idx].size(); ++p) {
                if ((mask & masks[idx][p]) == 0) {
                    placement[idx] = offsets[idx][p];
                    dfs(idx + 1, mask | masks[idx][p]);
                }
            }
        };
        dfs(0, 0);
        if (best == INT_MAX) cout << "Case " << tc << ": invalid data\n";
        else cout << "Case " << tc << ": " << best << "\n";
    }
    return 0;
}
