// Crossing the Desert
// UVa ID: 1011
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int main() {
    int pointCount, foodLimit;
    int caseNum = 0;
    while (scanf("%d %d", &pointCount, &foodLimit) == 2 && pointCount + foodLimit) {
        double posX[50], posY[50];
        double dist[50][50];
        double best[50];
        int visited[50] = {};
        for (int i = 0; i < pointCount; i++) {
            scanf("%lf %lf", &posX[i], &posY[i]);
            best[i] = 1e+6;
        }
        for (int i = 0; i < pointCount; i++) {
            for (int j = 0; j < pointCount; j++) {
                double d = hypot(posX[i] - posX[j], posY[i] - posY[j]);
                dist[i][j] = d;
            }
        }
        best[pointCount - 1] = 0;
        for (int i = 0; i < pointCount; i++) {
            int u = -1;
            for (int j = 0; j < pointCount; j++) {
                if (visited[j] == 0 && (u == -1 || best[u] > best[j]))
                    u = j;
            }
            visited[u] = 1;
            for (int j = 0; j < pointCount; j++) {
                if (visited[j])
                    continue;
                double w = dist[u][j];
                if (foodLimit >= best[u] + 2 * w)
                    best[j] = min(best[j], best[u] + w);
                else if (foodLimit >= 3 * w) {
                    int repeatCount = ceil((best[u] - (foodLimit - 2 * w)) / (foodLimit - 3 * w));
                    best[j] = min(best[j], best[u] + repeatCount * (2 * w) + w);
                }
            }
        }
        printf("Trial %d: ", ++caseNum);
        if (best[0] != 1e+6) printf("%.0lf units of food\n", ceil(best[0]));
        else puts("Impossible");
        puts("");
    }
    return 0;
}
