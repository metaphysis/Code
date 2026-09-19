#include <bits/stdc++.h>
using namespace std;

int pipeCount, pipeHeight[8], pipeOrder[8];
long double bestLen, centerX[8], minDist[8][8];
bool used[8];

void dfs(int depth, long double curLen) {
    if (depth == pipeCount) {
        bestLen = curLen;
        return;
    }
    for (int i = 0; i < pipeCount; ++i) {
        if (used[i]) continue;
        long double nextX = pipeHeight[i] / 2.0L, nextLen;
        for (int j = 0; j < depth; ++j) nextX = max(nextX, centerX[j] + minDist[pipeOrder[j]][i]);
        nextLen = max(curLen, nextX + pipeHeight[i] / 2.0L);
        if (nextLen >= bestLen) continue;
        used[i] = true;
        pipeOrder[depth] = i;
        centerX[depth] = nextX;
        dfs(depth + 1, nextLen);
        used[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, maxHeight;
    long double cutRatio = (2.0L - sqrtl(2.0L)) / 2.0L;
    cin >> testCount;
    cout << fixed << setprecision(12);
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        cin >> pipeCount;
        maxHeight = 0;
        bestLen = 0.0L;
        fill(used, used + 8, false);
        for (int i = 0; i < pipeCount; ++i) {
            cin >> pipeHeight[i];
            maxHeight = max(maxHeight, pipeHeight[i]);
            bestLen += pipeHeight[i];
        }
        for (int i = 0; i < pipeCount; ++i) {
            for (int j = 0; j < pipeCount; ++j) {
                long double smallH = min(pipeHeight[i], pipeHeight[j]), largeH = max(pipeHeight[i], pipeHeight[j]);
                minDist[i][j] = (smallH + largeH) / 2.0L - max(0.0L, cutRatio * largeH - (1.0L - cutRatio) * smallH);
            }
        }
        dfs(0, 0.0L);
        cout << "Case " << caseId << ": " << 8.0L * maxHeight * bestLen << '\n';
    }
    return 0;
}
