// Shovelling Snow
// UVa ID: 10863
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.040s

#include <bits/stdc++.h>
using namespace std;

char baseGrid[21][21], tempGrid[21][21], bestGrid[21][21];
int portalPos[4];
int parent[21 * 21], dist[21 * 21];
int dirs[5] = {1, 0, -1, 0, 1};
int rowCount, colCount;

struct Comp {
    bool operator()(int a, int b) const {
        return (dist[a] == dist[b] ? a < b : dist[a] < dist[b]);
    }
};

int runBfs(int src, int dst) {
    memset(parent, -1, sizeof parent);
    memset(dist, -1, sizeof dist);
    parent[src] = src;
    dist[src] = 0;
    set<int, Comp> q;
    q.insert(src);
    while (!q.empty()) {
        int cur = *q.begin();
        q.erase(q.begin());
        if (cur == dst) break;
        for (int k = 0; k < 4; k++) {
            int ni = cur / 21 + dirs[k], nj = cur % 21 + dirs[k + 1];
            if (ni >= rowCount || ni < 0 || nj >= colCount || nj < 0 || tempGrid[ni][nj] == '#') continue;
            int nd = dist[cur] + (tempGrid[ni][nj] == 'o');
            if (dist[ni * 21 + nj] == -1 || nd < dist[ni * 21 + nj]) {
                parent[ni * 21 + nj] = cur;
                q.erase(ni * 21 + nj);
                dist[ni * 21 + nj] = nd;
                q.insert(ni * 21 + nj);
            }
        }
    }
    return dist[dst];
}

int main() {
    bool firstCase = true;
    while (cin >> colCount >> rowCount) {
        if (firstCase) firstCase = false;
        else cout << endl;
        cout << colCount << " " << rowCount << endl;
        if (!colCount) break;
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < colCount; j++) {
                cin >> baseGrid[i][j];
                if (baseGrid[i][j] >= 'A' && baseGrid[i][j] <= 'D')
                    portalPos[baseGrid[i][j] - 'A'] = i * 21 + j;
            }
        }
        int bestDiff = 1000000;
        for (int a = 0; a < 4; a++) {
            for (int b = a + 1; b < 4; b++) {
                for (int c = 0; c < 4; c++) {
                    for (int d = c + 1; d < 4; d++) {
                        for (int e = 0; e < 4; e++) {
                            for (int f = e + 1; f < 4; f++) {
                                bool good = true;
                                for (int g = 0; g < 4; g++) {
                                    if (g != a && g != b && g != c && g != d && g != e && g != f) {
                                        good = false;
                                        break;
                                    }
                                }
                                if (!good) continue;
                                if ((a == c && b == d) || (a == e && b == f) || (c == e && d == f))
                                    continue;
                                for (int i = 0; i < rowCount; i++)
                                    for (int j = 0; j < colCount; j++)
                                        tempGrid[i][j] = baseGrid[i][j];
                                runBfs(portalPos[a], portalPos[b]);
                                int cur = parent[portalPos[b]];
                                while (cur != portalPos[a]) {
                                    if (tempGrid[cur / 21][cur % 21] == 'o')
                                        tempGrid[cur / 21][cur % 21] = '.';
                                    cur = parent[cur];
                                }
                                runBfs(portalPos[c], portalPos[d]);
                                cur = parent[portalPos[d]];
                                while (cur != portalPos[c]) {
                                    if (tempGrid[cur / 21][cur % 21] == 'o')
                                        tempGrid[cur / 21][cur % 21] = '.';
                                    cur = parent[cur];
                                }
                                runBfs(portalPos[e], portalPos[f]);
                                cur = parent[portalPos[f]];
                                while (cur != portalPos[e]) {
                                    if (tempGrid[cur / 21][cur % 21] == 'o')
                                        tempGrid[cur / 21][cur % 21] = '.';
                                    cur = parent[cur];
                                }
                                int diff = 0;
                                for (int i = 0; i < rowCount; i++)
                                    for (int j = 0; j < colCount; j++)
                                        if (tempGrid[i][j] != baseGrid[i][j]) diff++;
                                if (diff < bestDiff) {
                                    bestDiff = diff;
                                    for (int i = 0; i < rowCount; i++)
                                        for (int j = 0; j < colCount; j++)
                                            bestGrid[i][j] = tempGrid[i][j];
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < colCount; j++) cout << bestGrid[i][j];
            cout << endl;
        }
    }
    return 0;
}
