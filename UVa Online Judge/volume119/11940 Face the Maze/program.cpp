// Face the Maze
// UVa ID: 11940
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

using Point = pair<int, int>;

bool inside(int n, int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

bool nearTarget(Point cur, Point target) {
    int dx = abs(cur.first - target.first), dy = abs(cur.second - target.second);
    return dx + dy == 1;
}

void printPath(const vector<Point>& path) {
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << ' ';
        cout << '(' << path[i].first << ',' << path[i].second << ')';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testNum;
    cin >> testNum;
    string line;
    getline(cin, line);
    while (testNum--) {
        do {
            getline(cin, line);
        } while (line.empty());
        stringstream ss(line);
        int n;
        ss >> n;
        vector<Point> points;
        char left, comma, right;
        int x, y;
        while (ss >> left >> x >> comma >> y >> right) points.push_back({x, y});
        Point source = points[0], target = points[1];
        vector<vector<bool>> block(n + 1, vector<bool>(n + 1, false));
        for (int i = 2; i < (int)points.size(); ++i)
            block[points[i].second][points[i].first] = true;
        vector<vector<bool>> visited(n + 1, vector<bool>(n + 1, false));
        vector<Point> stack, path;
        stack.push_back(source);
        path.push_back(source);
        visited[source.second][source.first] = true;
        int dx[4] = {0, 1, -1, 0}, dy[4] = {1, 0, 0, -1};
        while (true) {
            Point cur = stack.back();
            if (nearTarget(cur, target)) {
                path.push_back(target);
                break;
            }
            bool moved = false;
            for (int i = 0; i < 4; ++i) {
                int nx = cur.first + dx[i], ny = cur.second + dy[i];
                if (!inside(n, nx, ny) || block[ny][nx] || visited[ny][nx]) continue;
                visited[ny][nx] = true;
                stack.push_back({nx, ny});
                path.push_back({nx, ny});
                moved = true;
                break;
            }
            if (moved) continue;
            if (stack.size() == 1) break;
            stack.pop_back();
            path.push_back(stack.back());
        }
        printPath(path);
    }
    return 0;
}
