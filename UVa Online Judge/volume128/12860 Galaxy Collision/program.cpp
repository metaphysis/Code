// Galaxy Collision
// UVa ID: 12860
// Verdict: Accepted
// Submission Date: 2026-01-
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

struct Point {
    int x, y, id;
    Point(int x = 0, int y = 0, int id = 0) : x(x), y(y), id(id) {}
    bool operator<(const Point& other) const { return x < other.x; }
};

vector<Point> points;
vector<int> g[MAXN];
int color[MAXN];

inline long long getDist(const Point& a, const Point& b) {
    long long dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// 分组优化：按x坐标分组，每组内按y排序
vector<int> groupByX[500005];

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        points.resize(n);
        for (int i = 0; i < n; ++i) {
            g[i].clear();
            color[i] = 0;
        }
        for (int i = 0; i <= 500000; ++i) groupByX[i].clear();
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &points[i].x, &points[i].y);
            points[i].id = i;
            groupByX[points[i].x].push_back(i);
        }
        for (int x = 1; x <= 500000; ++x) {
            if (groupByX[x].empty()) continue;
            for (int dx = -5; dx <= 5; ++dx) {
                int nx = x + dx;
                if (nx < 1 || nx > 500000) continue;
                for (int i : groupByX[x]) {
                    Point& p1 = points[i];
                    for (int j : groupByX[nx]) {
                        if (j <= i) continue;
                        Point& p2 = points[j];
                        if (abs(p1.y - p2.y) > 5) continue;
                        if (getDist(p1, p2) <= 25) {
                            g[i].push_back(j);
                            g[j].push_back(i);
                        }
                    }
                }
            }
        }
        vector<pair<int, int>> components;
        for (int i = 0; i < n; ++i)
            if (color[i] == 0) {
                int cnt1 = 0, cnt2 = 0;
                queue<int> q;
                q.push(i);
                color[i] = 1;
                cnt1++;
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    int c = color[u];
                    for (int v : g[u]) {
                        if (color[v] == 0) {
                            color[v] = 3 - c;
                            if (color[v] == 1) cnt1++;
                            else cnt2++;
                            q.push(v);
                        }
                    }
                }
                components.push_back({cnt1, cnt2});
            }
        bitset<50005> dp;
        dp[0] = 1;
        for (auto& [a, b] : components) dp = (dp << a) | (dp << b);
        int r = n;
        for (int i = 0; i <= n; ++i)
            if (dp[i]) {
                r = min(r, min(i, n - i));
                if (r == 0) break;
            }
        printf("%d\n", r);
    }
    return 0;
}
