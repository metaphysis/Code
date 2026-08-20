// Grid Speed
// UVa ID: 10671
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.180s

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const int MAXT = 210005;
const double INF = 1e100;

int n, L;
int h[MAXN], v[MAXN];
int xs, ys, xt, yt, st, et;
int dx, dy;
int scaleTime;
bool vis[MAXN][MAXN][MAXT];
double dp[MAXN][MAXN][MAXT];

int gcdInt(int a, int b) {
    return b == 0 ? a : gcdInt(b, a % b);
}

double calcFuel(int s) {
    double mpg = 80.0 - 0.03 * s * s;
    return (double)L / mpg;
}

void solveScenario(int scenarioId) {
    scanf("%d", &n);
    scanf("%d", &L);
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
    scanf("%d%d%d%d%d%d", &xs, &ys, &xt, &yt, &st, &et);

    scaleTime = 210 / gcdInt(L, 210);
    st *= scaleTime;
    et *= scaleTime;

    dx = (xs < xt) ? 1 : -1;
    dy = (ys < yt) ? 1 : -1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int t = 0; t <= et; t++) {
                vis[i][j][t] = false;
                dp[i][j][t] = INF;
            }
        }
    }

    vis[xs][ys][0] = true;
    dp[xs][ys][0] = 0.0;

    for (int t = 0; t <= et; t++) {
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++) {
                if (!vis[x][y][t]) continue;

                int nx = x + dx;
                if (nx >= 1 && nx <= n) {
                    int limit = h[y];
                    for (int s = 5; s <= limit; s += 5) {
                        int delta = scaleTime * L * 60 / s;
                        int nt = t + delta;
                        if (nt > et) continue;
                        double fuel = calcFuel(s);
                        if (!vis[nx][y][nt]) {
                            vis[nx][y][nt] = true;
                            dp[nx][y][nt] = dp[x][y][t] + fuel;
                        } else {
                            dp[nx][y][nt] = min(dp[nx][y][nt], dp[x][y][t] + fuel);
                        }
                    }
                }

                int ny = y + dy;
                if (ny >= 1 && ny <= n) {
                    int limit = v[x];
                    for (int s = 5; s <= limit; s += 5) {
                        int delta = scaleTime * L * 60 / s;
                        int nt = t + delta;
                        if (nt > et) continue;
                        double fuel = calcFuel(s);
                        if (!vis[x][ny][nt]) {
                            vis[x][ny][nt] = true;
                            dp[x][ny][nt] = dp[x][y][t] + fuel;
                        } else {
                            dp[x][ny][nt] = min(dp[x][ny][nt], dp[x][y][t] + fuel);
                        }
                    }
                }
            }
        }
    }

    int earliestTime = -1;
    double earliestFuel = INF;
    int econTime = -1;
    double econFuel = INF;

    for (int t = st; t <= et; t++) {
        if (!vis[xt][yt][t]) continue;
        if (earliestTime == -1) {
            earliestTime = t;
            earliestFuel = dp[xt][yt][t];
        } else if (t == earliestTime) {
            earliestFuel = min(earliestFuel, dp[xt][yt][t]);
        }
        if (dp[xt][yt][t] < econFuel - 1e-12) {
            econFuel = dp[xt][yt][t];
            econTime = t;
        } else if (fabs(dp[xt][yt][t] - econFuel) < 1e-12 && (econTime == -1 || t < econTime)) {
            econTime = t;
        }
    }

    printf("Scenario %d:\n", scenarioId);
    if (earliestTime == -1) {
        printf("IMPOSSIBLE\n");
    } else {
        int earMin = (earliestTime + scaleTime - 1) / scaleTime;
        int econMin = (econTime + scaleTime - 1) / scaleTime;
        printf("The earliest  arrival: %d minutes, fuel %.2f gallons\n", earMin, earliestFuel + 1e-9);
        printf("The economical travel: %d minutes, fuel %.2f gallons\n", econMin, econFuel + 1e-9);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        solveScenario(i);
    }
    return 0;
}
