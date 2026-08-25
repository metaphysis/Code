#include <bits/stdc++.h>
using namespace std;

const int DR[] = {-1, 1, 0, 0};
const int DC[] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w, h;
    bool firstCase = true;
    while (cin >> w >> h) {
        int u, d, l, r;
        cin >> u >> d >> l >> r;
        double prob[4] = {u / 100.0, d / 100.0, l / 100.0, r / 100.0};

        vector<string> grid(h);
        for (int i = 0; i < h; ++i) cin >> grid[i];

        vector<vector<int>> id(h, vector<int>(w, -1));
        vector<pair<int,int>> states;
        vector<pair<int,int>> targets;
        vector<vector<int>> targetId(h, vector<int>(w, -1));

        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                if (grid[r][c] == '.') {
                    id[r][c] = (int)states.size();
                    states.push_back({r, c});
                } else if (grid[r][c] == 'T') {
                    targetId[r][c] = (int)targets.size();
                    targets.push_back({r, c});
                }
            }
        }

        int N = (int)states.size();
        int band = w + 2;
        int full = 2 * band + 1;
        vector<vector<double>> A(N, vector<double>(full, 0.0));
        vector<double> b(N, 0.0);

        for (int i = 0; i < N; ++i) A[i][band] = 1.0;

        for (int idx = 0; idx < N; ++idx) {
            int r = states[idx].first, c = states[idx].second;
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + DR[dir], nc = c + DC[dir];
                double p = prob[dir];
                if (p == 0.0) continue;
                int i = idx;
                if (nr < 0 || nr >= h || nc < 0 || nc >= w || grid[nr][nc] == 'X') {
                } else if (grid[nr][nc] == 'T') {
                    continue;
                } else {
                    i = id[nr][nc];
                }
                int offset = idx - i + band;
                if (offset >= 0 && offset < full) {
                    A[i][offset] -= p;
                }
            }
        }

        int firstRowDots = 0;
        for (int c = 0; c < w; ++c) if (grid[0][c] == '.') firstRowDots++;
        double initProb = 1.0 / firstRowDots;
        for (int c = 0; c < w; ++c) {
            if (grid[0][c] == '.') {
                int idx = id[0][c];
                b[idx] = initProb;
            }
        }

        for (int k = 0; k < N; ++k) {
            double pivot = A[k][band];
            for (int i = k + 1; i < N && i - k <= band; ++i) {
                double factor = A[i][k - i + band] / pivot;
                if (fabs(factor) < 1e-18) continue;
                int maxJ = min(N - 1, k + band);
                maxJ = min(maxJ, i + band);
                for (int j = k; j <= maxJ; ++j) {
                    A[i][j - i + band] -= factor * A[k][j - k + band];
                }
                b[i] -= factor * b[k];
            }
        }

        vector<double> y(N);
        for (int i = N - 1; i >= 0; --i) {
            double sum = b[i];
            int maxJ = min(N - 1, i + band);
            for (int j = i + 1; j <= maxJ; ++j) {
                sum -= A[i][j - i + band] * y[j];
            }
            y[i] = sum / A[i][band];
        }

        vector<double> ans(targets.size(), 0.0);
        for (int idx = 0; idx < N; ++idx) {
            int r = states[idx].first, c = states[idx].second;
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + DR[dir], nc = c + DC[dir];
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
                if (grid[nr][nc] == 'T') {
                    int tid = targetId[nr][nc];
                    if (tid != -1) {
                        ans[tid] += y[idx] * prob[dir];
                    }
                }
            }
        }

        if (!firstCase) cout << "\n";
        firstCase = false;
        cout << fixed << setprecision(9);
        for (double val : ans) {
            cout << val << "\n";
        }
    }
    return 0;
}
