#include <bits/stdc++.h>
using namespace std;

struct Cut {
    int x1, y1, x2, y2;
};

long long solve() {
    int n;
    cin >> n;
    vector<Cut> cuts(n);
    vector<int> xs, ys;
    int minX = 1000000000, maxX = -1000000000, minY = 1000000000, maxY = -1000000000;
    for (int i = 0; i < n; i++) {
        cin >> cuts[i].x1 >> cuts[i].y1 >> cuts[i].x2 >> cuts[i].y2;
        xs.push_back(cuts[i].x1);
        xs.push_back(cuts[i].x2);
        ys.push_back(cuts[i].y1);
        ys.push_back(cuts[i].y2);
        minX = min(minX, min(cuts[i].x1, cuts[i].x2));
        maxX = max(maxX, max(cuts[i].x1, cuts[i].x2));
        minY = min(minY, min(cuts[i].y1, cuts[i].y2));
        maxY = max(maxY, max(cuts[i].y1, cuts[i].y2));
    }
    xs.push_back(minX - 1);
    xs.push_back(maxX + 1);
    ys.push_back(minY - 1);
    ys.push_back(maxY + 1);
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int xCount = xs.size(), yCount = ys.size();
    int cellX = xCount - 1, cellY = yCount - 1;
    vector<vector<char>> vWall(xCount, vector<char>(cellY, 0));
    vector<vector<char>> hWall(cellX, vector<char>(yCount, 0));
    for (int i = 0; i < n; i++) {
        if (cuts[i].x1 == cuts[i].x2) {
            int xIndex = lower_bound(xs.begin(), xs.end(), cuts[i].x1) - xs.begin();
            int lowY = min(cuts[i].y1, cuts[i].y2), highY = max(cuts[i].y1, cuts[i].y2);
            for (int y = 0; y < cellY; y++)
                if (ys[y] >= lowY && ys[y + 1] <= highY) vWall[xIndex][y] = 1;
        } else {
            int yIndex = lower_bound(ys.begin(), ys.end(), cuts[i].y1) - ys.begin();
            int lowX = min(cuts[i].x1, cuts[i].x2), highX = max(cuts[i].x1, cuts[i].x2);
            for (int x = 0; x < cellX; x++)
                if (xs[x] >= lowX && xs[x + 1] <= highX) hWall[x][yIndex] = 1;
        }
    }
    vector<vector<char>> visited(cellX, vector<char>(cellY, 0));
    queue<pair<int, int>> que;
    visited[0][0] = 1;
    que.push({0, 0});
    while (!que.empty()) {
        int curX = que.front().first, curY = que.front().second;
        que.pop();
        if (curX + 1 < cellX && !visited[curX + 1][curY] && !vWall[curX + 1][curY]) {
            visited[curX + 1][curY] = 1;
            que.push({curX + 1, curY});
        }
        if (curX > 0 && !visited[curX - 1][curY] && !vWall[curX][curY]) {
            visited[curX - 1][curY] = 1;
            que.push({curX - 1, curY});
        }
        if (curY + 1 < cellY && !visited[curX][curY + 1] && !hWall[curX][curY + 1]) {
            visited[curX][curY + 1] = 1;
            que.push({curX, curY + 1});
        }
        if (curY > 0 && !visited[curX][curY - 1] && !hWall[curX][curY]) {
            visited[curX][curY - 1] = 1;
            que.push({curX, curY - 1});
        }
    }
    long long answer = 0;
    for (int x = 0; x < xCount; x++) {
        for (int y = 0; y < cellY; y++) {
            if (!vWall[x][y]) continue;
            bool canSee = false;
            if (x > 0 && visited[x - 1][y]) canSee = true;
            if (x < cellX && visited[x][y]) canSee = true;
            if (canSee) answer += ys[y + 1] - ys[y];
        }
    }
    for (int x = 0; x < cellX; x++) {
        for (int y = 0; y < yCount; y++) {
            if (!hWall[x][y]) continue;
            bool canSee = false;
            if (y > 0 && visited[x][y - 1]) canSee = true;
            if (y < cellY && visited[x][y]) canSee = true;
            if (canSee) answer += xs[x + 1] - xs[x];
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--)
        cout << solve() << '\n';
    return 0;
}
