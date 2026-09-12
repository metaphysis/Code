// The Geoduck GUI
// UVa ID: 1004
// Verdict: Accepted
// Submission Date: 2026-08-03
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

struct Geoduck {
    int dx, dy, nx, ny, now, len;
    vector<int> move;
    Geoduck() {}
    Geoduck(int dirX, int dirY, int width, int height) {
        dx = dirX;
        dy = dirY;
        nx = dx > 0 ? width - 1 : 0;
        ny = dy > 0 ? 0 : height - 1;
        int ax = abs(dx);
        int ay = abs(dy);
        int tx = dx;
        int ty = dy;
        double curY = 0.5;
        double eps = 1e-11;
        for (int i = 1; i <= ax; i++) {
            double nextY = 1.0 * ay / ax * i + 0.5 * (ax - ay) / ax;
            int nextInt = int(nextY);
            int curInt = int(curY);
            if (nextY - nextInt < eps) {
                for (int j = 0; j < nextInt - curInt - 1; j++) move.push_back(ty > 0 ? 0 : 1);
                move.push_back(tx > 0 ? 3 : 2);
                move.push_back(ty > 0 ? 0 : 1);
                curY = nextY;
            } else {
                for (int j = 0; j < nextInt - curInt; j++) move.push_back(ty > 0 ? 0 : 1);
                move.push_back(tx > 0 ? 3 : 2);
                curY = nextY;
            }
        }
        for (int j = 0; j < int(0.5 + ay) - int(curY); j++) move.push_back(ty > 0 ? 0 : 1);
        len = int(move.size());
        now = 0;
        nx = dx > 0 ? 0 : width - 1;
        ny = dy > 0 ? 0 : height - 1;
    }
    void reset(int width, int height) {
        now = 0;
        nx = dx > 0 ? 0 : width - 1;
        ny = dy > 0 ? 0 : height - 1;
    }
};

void moveNext(int &pos, int limit) { pos = (pos + 1) % limit; }
void movePrev(int &pos, int limit) { pos = (pos + limit - 1) % limit; }

void moveRobot(Geoduck &Geoduck, int width, int height) {
    int dir = Geoduck.move[Geoduck.now];
    switch (dir) {
        case 0:
            moveNext(Geoduck.ny, height);
            break;
        case 1:
            movePrev(Geoduck.ny, height);
            break;
        case 2:
            movePrev(Geoduck.nx, width);
            break;
        case 3:
            moveNext(Geoduck.nx, width);
            break;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int width, height;
    int caseId = 1;
    while (cin >> width >> height) {
        if (width == 0 && height == 0) break;
        int k;
        cin >> k;
        vector<Geoduck> robots;
        for (int i = 0; i < k; i++) {
            int dx, dy;
            cin >> dx >> dy;
            robots.push_back(Geoduck(dx, dy, width, height));
        }
        int bestCount = 0;
        int bestTime = 0;
        vector<pair<int, int> > answer;
        for (int i = 0; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                robots[i].reset(width, height);
                robots[j].reset(width, height);
                if (robots[i].nx == robots[j].nx && robots[i].ny == robots[j].ny) continue;
                vector<vector<bool> > visited(width, vector<bool>(height, false));
                int time = 1;
                int count = 0;
                bool stopA = false;
                bool stopB = false;
                while (true) {
                    if (robots[i].nx == robots[j].nx && robots[i].ny == robots[j].ny) {
                        count++;
                        break;
                    }
                    if (!stopA) {
                        visited[robots[i].nx][robots[i].ny] = true;
                        count++;
                    }
                    if (!stopB) {
                        visited[robots[j].nx][robots[j].ny] = true;
                        count++;
                    }
                    int oldAX = robots[i].nx;
                    int oldAY = robots[i].ny;
                    int oldBX = robots[j].nx;
                    int oldBY = robots[j].ny;
                    if (!stopA) moveRobot(robots[i], width, height);
                    if (!stopB) moveRobot(robots[j], width, height);
                    bool swapPos = robots[i].nx == oldBX && robots[i].ny == oldBY && robots[j].nx == oldAX && robots[j].ny == oldAY;
                    if (swapPos && !stopA && !stopB) break;
                    robots[i].now = (robots[i].now + 1) % robots[i].len;
                    robots[j].now = (robots[j].now + 1) % robots[j].len;
                    if (!stopA && visited[robots[i].nx][robots[i].ny]) stopA = true;
                    if (!stopB && visited[robots[j].nx][robots[j].ny]) stopB = true;
                    if (stopA && stopB) break;
                    time++;
                }
                if (count > bestCount || (count == bestCount && time < bestTime)) {
                    bestCount = count;
                    bestTime = time;
                    answer.clear();
                    answer.push_back(make_pair(i + 1, j + 1));
                } else if (count == bestCount && time == bestTime) {
                    answer.push_back(make_pair(i + 1, j + 1));
                }
            }
        }
        cout << "Case " << caseId << " Cells Illuminated: " << bestCount << " Minimum Time: " << bestTime << '\n';
        for (const auto &item : answer) cout << "Geoduck IDs: " << item.first << " " << item.second << '\n';
        caseId++;
    }
    return 0;
}
