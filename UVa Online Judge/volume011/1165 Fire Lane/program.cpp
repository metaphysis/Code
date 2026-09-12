#include <bits/stdc++.h>
using namespace std;

const int maxSize = 105;
const int maxCar = 10005;

struct Vehicle {
    int x, y, len;
    char dir;
};

int width, height, carCount, laneX;
int owner[maxSize][maxSize];
Vehicle cars[maxCar];
bool need[maxCar], removed[maxCar];

void scanPath(int id, queue<int> &que) {
    int x = cars[id].x, y = cars[id].y, len = cars[id].len;
    if (cars[id].dir == 'E') {
        for (x += len; x < width; x++)
            if (owner[y][x] != -1 && !need[owner[y][x]]) {
                need[owner[y][x]] = true;
                que.push(owner[y][x]);
            }
    } else if (cars[id].dir == 'W') {
        for (x -= len; x >= 0; x--)
            if (owner[y][x] != -1 && !need[owner[y][x]]) {
                need[owner[y][x]] = true;
                que.push(owner[y][x]);
            }
    } else if (cars[id].dir == 'S') {
        for (y += len; y < height; y++)
            if (owner[y][x] != -1 && !need[owner[y][x]]) {
                need[owner[y][x]] = true;
                que.push(owner[y][x]);
            }
    } else {
        for (y -= len; y >= 0; y--)
            if (owner[y][x] != -1 && !need[owner[y][x]]) {
                need[owner[y][x]] = true;
                que.push(owner[y][x]);
            }
    }
}

bool canMove(int id) {
    int x = cars[id].x, y = cars[id].y, len = cars[id].len;
    if (cars[id].dir == 'E') {
        for (x += len; x < width; x++)
            if (owner[y][x] != -1 && !removed[owner[y][x]])
                return false;
    } else if (cars[id].dir == 'W') {
        for (x -= len; x >= 0; x--)
            if (owner[y][x] != -1 && !removed[owner[y][x]])
                return false;
    } else if (cars[id].dir == 'S') {
        for (y += len; y < height; y++)
            if (owner[y][x] != -1 && !removed[owner[y][x]])
                return false;
    } else {
        for (y -= len; y >= 0; y--)
            if (owner[y][x] != -1 && !removed[owner[y][x]])
                return false;
    }
    return true;
}

void buildNeed() {
    queue<int> que;
    for (int y = 0; y < height; y++)
        for (int x = laneX; x < laneX + 2; x++)
            if (owner[y][x] != -1 && !need[owner[y][x]]) {
                need[owner[y][x]] = true;
                que.push(owner[y][x]);
            }
    while (!que.empty()) {
        int id = que.front();
        que.pop();
        scanPath(id, que);
    }
}

void solveCase() {
    memset(owner, -1, sizeof(owner));
    memset(need, false, sizeof(need));
    memset(removed, false, sizeof(removed));
    for (int i = 0; i < carCount; i++) {
        cin >> cars[i].x >> cars[i].y >> cars[i].len >> cars[i].dir;
        int x = cars[i].x, y = cars[i].y;
        for (int k = 0; k < cars[i].len; k++) {
            owner[y][x] = i;
            if (cars[i].dir == 'E')
                x++;
            else if (cars[i].dir == 'W')
                x--;
            else if (cars[i].dir == 'S')
                y++;
            else
                y--;
        }
    }
    buildNeed();
    int left = 0;
    for (int i = 0; i < carCount; i++)
        if (need[i])
            left++;
    int answer[maxCar], answerCount = 0;
    while (left > 0) {
        int selected = -1;
        for (int i = 0; i < carCount; i++)
            if (need[i] && !removed[i] && canMove(i)) {
                selected = i;
                break;
            }
        if (selected == -1) {
            cout << "Jammed\n";
            return;
        }
        removed[selected] = true;
        answer[answerCount++] = selected;
        left--;
    }
    for (int i = 0; i < answerCount; i++)
        cout << answer[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool firstCase = true;
    while (cin >> width >> height) {
        cin >> carCount >> laneX;
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        solveCase();
    }
    return 0;
}
