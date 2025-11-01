// Team Them Up
// UVa ID: 1627
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

using namespace std;

const int MAXN = 105;

int N;
bool know[MAXN][MAXN];
vector<int> graph[MAXN];
int color[MAXN];
vector<int> comp[MAXN][2];
int compSize;

bool dfs(int u, int c, int compId) {
    color[u] = c;
    comp[compId][c - 1].push_back(u);
    for (int v : graph[u]) {
        if (color[v] == c) return false;
        if (color[v] == 0 && !dfs(v, 3 - c, compId)) return false;
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        memset(know, 0, sizeof(know));
        for (int i = 1; i <= N; i++) {
            graph[i].clear();
            int x;
            while (cin >> x && x != 0) {
                know[i][x] = true;
            }
        }

        for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                if (!know[i][j] || !know[j][i]) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        memset(color, 0, sizeof(color));
        compSize = 0;
        bool possible = true;
        for (int i = 1; i <= N; i++) {
            if (color[i] == 0) {
                comp[compSize][0].clear();
                comp[compSize][1].clear();
                if (!dfs(i, 1, compSize)) {
                    possible = false;
                    break;
                }
                compSize++;
            }
        }

        if (!possible) {
            cout << "No solution\n";
            if (T) cout << "\n";
            continue;
        }

        vector<vector<bool>> dp(compSize + 1, vector<bool>(N + 1, false));
        dp[0][0] = true;
        for (int i = 0; i < compSize; i++) {
            int s0 = comp[i][0].size();
            int s1 = comp[i][1].size();
            for (int j = 0; j <= N; j++) {
                if (dp[i][j]) {
                    dp[i + 1][j + s0] = true;
                    dp[i + 1][j + s1] = true;
                }
            }
        }

        int best = -1;
        for (int j = 0; j <= N; j++) {
            if (dp[compSize][j] && abs(j - (N - j)) >= 0) {
                if (best == -1 || abs(2 * j - N) < abs(2 * best - N)) {
                    best = j;
                }
            }
        }

        vector<bool> inTeam1(N + 1, false);
        int cur = best;
        for (int i = compSize; i > 0; i--) {
            int s0 = comp[i - 1][0].size();
            int s1 = comp[i - 1][1].size();
            if (cur >= s0 && dp[i - 1][cur - s0]) {
                for (int x : comp[i - 1][0]) inTeam1[x] = true;
                cur -= s0;
            } else {
                for (int x : comp[i - 1][1]) inTeam1[x] = true;
                cur -= s1;
            }
        }

        vector<int> team1, team2;
        for (int i = 1; i <= N; i++) {
            if (inTeam1[i]) team1.push_back(i);
            else team2.push_back(i);
        }

        cout << team1.size();
        for (int x : team1) cout << " " << x;
        cout << "\n";

        cout << team2.size();
        for (int x : team2) cout << " " << x;
        cout << "\n";

        if (T) cout << "\n";
    }
    return 0;
}
