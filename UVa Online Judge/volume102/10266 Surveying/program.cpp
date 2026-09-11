// Surveying
// UVa ID: 10266
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.100s

#include <bits/stdc++.h>
using namespace std;

#define MAXN 128

vector<int> adj[MAXN][MAXN];

struct Survey {
    int x, y, h;
    Survey(int a = 0, int b = 0, int c = 0) : x(a), y(b), h(c) {}
};

vector<vector<Survey>> surveyGroups;
int rowCount, colCount;

int runSpfa(int startX, int startY) {
    int dist[MAXN][MAXN], visited[MAXN][MAXN] = {};
    vector<int> inQueue;
    inQueue.resize(surveyGroups.size(), 0);
    int x, y, h, id, toX, toY;
    queue<int> qx, qy, qid;
    visited[startX][startY] = 1;
    dist[startX][startY] = 0;
    for (int i = 0; i < adj[startX][startY].size(); i++) {
        int u = adj[startX][startY][i];
        qx.push(startX);
        qy.push(startY);
        qid.push(u);
        inQueue[u] = 1;
    }
    while (!qx.empty()) {
        x = qx.front(); qx.pop();
        y = qy.front(); qy.pop();
        id = qid.front(); qid.pop();
        int shiftVal = 0;
        for (int i = 0; i < surveyGroups[id].size(); i++) {
            if (surveyGroups[id][i].x == x && surveyGroups[id][i].y == y) {
                shiftVal = dist[x][y] - surveyGroups[id][i].h;
                break;
            }
        }
        for (int i = 0; i < surveyGroups[id].size(); i++) {
            toX = surveyGroups[id][i].x;
            toY = surveyGroups[id][i].y;
            h = surveyGroups[id][i].h + shiftVal;
            if (visited[toX][toY] && h != dist[toX][toY]) return 0;
            dist[toX][toY] = h;
            if (visited[toX][toY] == 0) {
                visited[toX][toY] = 1;
                for (int j = 0; j < adj[toX][toY].size(); j++) {
                    int u = adj[toX][toY][j];
                    if (inQueue[u]) continue;
                    qx.push(toX);
                    qy.push(toY);
                    qid.push(u);
                    inQueue[u] = 1;
                }
            }
        }
    }
    int allVisited = 1;
    for (int i = 1; i <= rowCount; i++) {
        for (int j = 1; j <= colCount; j++) {
            allVisited &= visited[i][j];
        }
    }
    if (allVisited) {
        for (int i = 1; i <= rowCount; i++) {
            for (int j = 1; j <= colCount; j++) {
                printf("%d%c", dist[i][j], j == colCount ? '\n' : ' ');
            }
        }
    } else {
        puts("the lack of measurements");
    }
    return 1;
}

char line[1048576 * 8];

int main() {
    int testCase, baseX, baseY;
    int x, y, h;
    scanf("%d", &testCase);
    while (testCase--) {
        scanf("%d %d", &rowCount, &colCount);
        scanf("%d %d", &baseX, &baseY);
        while (getchar() != '\n');
        for (int i = 0; i <= rowCount; i++)
            for (int j = 0; j <= colCount; j++)
                adj[i][j].clear();
        surveyGroups.clear();
        while (gets(line)) {
            if (line[0] == '\0') break;
            stringstream sin(line);
            int id = (int)surveyGroups.size();
            vector<Survey> item;
            while (sin >> x >> y >> h) {
                item.push_back(Survey(x, y, h));
                adj[x][y].push_back(id);
            }
            surveyGroups.push_back(item);
        }
        int success = runSpfa(baseX, baseY);
        if (!success) puts("conflicting measurements");
        if (testCase) puts("");
    }
    return 0;
}
