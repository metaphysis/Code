#include <bits/stdc++.h>
using namespace std;

const int dirX[4] = {-1, 1, 0, 0};
const int dirY[4] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int rowCount, colCount, caseId = 1;
    while (cin >> rowCount >> colCount) {
        if (rowCount == 0 && colCount == 0)
            break;
        vector<string> source(rowCount), target(rowCount);
        for (int i = 0; i < rowCount; i++)
            cin >> source[i];
        for (int i = 0; i < rowCount; i++)
            cin >> target[i];
        vector<vector<int> > dist(rowCount, vector<int>(colCount, -1));
        queue<pair<int, int> > que;
        bool sameFrame = true;
        for (int i = 0; i < rowCount; i++)
            for (int j = 0; j < colCount; j++) {
                if (source[i][j] != target[i][j])
                    sameFrame = false;
                if (source[i][j] == '#') {
                    dist[i][j] = 0;
                    que.push(make_pair(i, j));
                }
            }
        while (!que.empty()) {
            int curX = que.front().first, curY = que.front().second;
            que.pop();
            for (int k = 0; k < 4; k++) {
                int nextX = curX + dirX[k], nextY = curY + dirY[k];
                if (nextX < 0 || nextX >= rowCount || nextY < 0 || nextY >= colCount)
                    continue;
                if (dist[nextX][nextY] != -1)
                    continue;
                dist[nextX][nextY] = dist[curX][curY] + 1;
                que.push(make_pair(nextX, nextY));
            }
        }
        int answer = 0;
        for (int i = 0; i < rowCount; i++)
            for (int j = 0; j < colCount; j++)
                if (target[i][j] == '#')
                    answer = max(answer, dist[i][j]);
        if (!sameFrame)
            answer = max(answer, 1);
        cout << "Case " << caseId++ << ": " << answer << '\n';
    }
    return 0;
}
