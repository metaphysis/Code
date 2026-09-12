#include <bits/stdc++.h>
using namespace std;

struct Movie {
    int id;
    double score;
};

bool cmpMovie(const Movie &a, const Movie &b) {
    if (fabs(a.score - b.score) > 1e-12) return a.score > b.score;
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, c;
    cin >> n >> m >> c;
    vector<vector<double>> rate(n, vector<double>(m));
    vector<vector<bool>> seen(n, vector<bool>(m, false));
    for (int k = 0; k < c; k++) {
        int u, v;
        double r;
        cin >> u >> v >> r;
        rate[u - 1][v - 1] = r;
        seen[u - 1][v - 1] = true;
    }
    vector<vector<double>> sim(m, vector<double>(m));
    for (int i = 0; i < m; i++) {
        sim[i][i] = 1.0;
        for (int j = i + 1; j < m; j++) {
            double sum = 0.0;
            bool hasCommon = false;
            for (int u = 0; u < n; u++) {
                if (seen[u][i] && seen[u][j]) {
                    double diff = rate[u][i] - rate[u][j];
                    sum += diff * diff;
                    hasCommon = true;
                }
            }
            if (hasCommon) sim[i][j] = sim[j][i] = 1.0 / (1.0 + sum);
        }
    }
    int u;
    cout << fixed << setprecision(3);
    while (cin >> u) {
        u--;
        vector<Movie> ans;
        for (int i = 0; i < m; i++) {
            if (seen[u][i]) continue;
            double top = 0.0, bottom = 0.0;
            for (int j = 0; j < m; j++) {
                if (seen[u][j] && sim[i][j] > 0.0) {
                    top += sim[i][j] * rate[u][j];
                    bottom += sim[i][j];
                }
            }
            if (bottom > 0.0) ans.push_back({i + 1, top / bottom});
        }
        sort(ans.begin(), ans.end(), cmpMovie);
        cout << "Recommendations for user " << u + 1 << ":\n";
        int limit = min(10, (int)ans.size());
        for (int i = 0; i < limit; i++)
            cout << ans[i].id << " " << ans[i].score << "\n";
        cout << "\n";
    }
    return 0;
}
