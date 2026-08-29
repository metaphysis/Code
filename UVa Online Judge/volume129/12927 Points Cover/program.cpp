#include <bits/stdc++.h>
using namespace std;

const int MaxCoordinate = 50000;

vector<int> graph[MaxCoordinate + 1];
int leftMatch[MaxCoordinate + 1], rightMatch[MaxCoordinate + 1], leftDist[MaxCoordinate + 1];

bool bfs(int leftCount) {
    queue<int> que;
    int i;
    for (i = 1; i <= leftCount; i++) {
        if (leftMatch[i] == 0) {
            leftDist[i] = 0;
            que.push(i);
        } else
            leftDist[i] = -1;
    }
    bool found = false;
    while (!que.empty()) {
        int left = que.front();
        que.pop();
        for (int right : graph[left]) {
            int nextLeft = rightMatch[right];
            if (nextLeft == 0)
                found = true;
            else if (leftDist[nextLeft] == -1) {
                leftDist[nextLeft] = leftDist[left] + 1;
                que.push(nextLeft);
            }
        }
    }
    return found;
}

bool dfs(int left) {
    for (int right : graph[left]) {
        int nextLeft = rightMatch[right];
        if (nextLeft == 0 || (leftDist[nextLeft] == leftDist[left] + 1 && dfs(nextLeft))) {
            leftMatch[left] = right;
            rightMatch[right] = left;
            return true;
        }
    }
    leftDist[left] = -1;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    while (testCount--) {
        int pointCount;
        cin >> pointCount;
        vector<pair<int, int>> points;
        points.reserve(pointCount);
        int maxX = 0, maxY = 0;
        for (int i = 0; i < pointCount; i++) {
            int x, y;
            cin >> x >> y;
            points.push_back({x, y});
            maxX = max(maxX, x);
            maxY = max(maxY, y);
        }
        for (int i = 1; i <= maxX; i++)
            graph[i].clear();
        sort(points.begin(), points.end());
        points.erase(unique(points.begin(), points.end()), points.end());
        for (pair<int, int> point : points)
            graph[point.first].push_back(point.second);
        fill(leftMatch, leftMatch + maxX + 1, 0);
        fill(rightMatch, rightMatch + maxY + 1, 0);
        int matching = 0;
        while (bfs(maxX)) {
            for (int i = 1; i <= maxX; i++)
                if (leftMatch[i] == 0 && dfs(i))
                    matching++;
        }
        cout << matching << '\n';
    }
    return 0;
}
