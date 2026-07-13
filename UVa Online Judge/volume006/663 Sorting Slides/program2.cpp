// Sorting Slides
// UVa ID: 663
// Verdict: Accepted
// Submission Date: 2016-11-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 60;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV];
int tx, ty;

int dfs(int u) {
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v]) {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v])) {
                cx[u] = v;
                cy[v] = u;
                return 1;
            }
        }
    return 0;
}

int hungarian() {
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    int matches = 0;
    for (int i = 0; i < tx; i++)
        if (cx[i] == -1) {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}

struct point {
    int x, y;
};

struct rectangle {
    int xmin, xmax, ymin, ymax;
};

point points[MAXV];
rectangle rectangles[MAXV];

bool pointInBox(point p, rectangle r) {
    return p.x > r.xmin && p.x < r.xmax && p.y > r.ymin && p.y < r.ymax;
}

int main() {
    int cases = 0;
    while (cin >> ty, ty > 0) {
        tx = ty;
        for (int i = 0; i < ty; i++) {
            cin >> rectangles[i].xmin >> rectangles[i].xmax;
            cin >> rectangles[i].ymin >> rectangles[i].ymax;
        }
        for (int i = 0; i < tx; i++) cin >> points[i].x >> points[i].y;
        memset(g, 0, sizeof(g));
        for (int i = 0; i < tx; i++)
            for (int j = 0; j < ty; j++)
                if (pointInBox(points[i], rectangles[j]))
                    g[i][j] = 1;
        cout << "Heap " << ++cases << '\n';
        bool outputed = false;
        int maxMatch = hungarian();
        for (int i = 0; i < tx; i++)
            for (int j = 0; j < ty; j++)
                if (g[j][i]) {
                    g[j][i] = 0;
                    int nextMatch = hungarian();
                    if (nextMatch < maxMatch) {
                        if (outputed) cout << ' ';
                        else outputed = true;
                        cout << '(' << (char)('A' + i) << ',' << (j + 1) << ')';
                    }
                    g[j][i] = 1;
                }
        if (!outputed) cout << "none";
        cout << "\n\n";
    }
	return 0;
}
