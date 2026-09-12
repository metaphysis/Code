// Happy Robot 
// UVa ID: 12825
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);

void updateState(long long &minX, long long &maxX, long long &minY, long long &maxY, long long curMinX, long long curMaxX, long long curMinY, long long curMaxY) {
    minX = min(minX, curMinX);
    maxX = max(maxX, curMaxX);
    minY = min(minY, curMinY);
    maxY = max(maxY, curMaxY);
}

void moveState(int dir, long long minX, long long maxX, long long minY, long long maxY, long long nextMinX[], long long nextMaxX[], long long nextMinY[], long long nextMaxY[]) {
    static const int dx[] = {1, 0, -1, 0};
    static const int dy[] = {0, 1, 0, -1};
    updateState(nextMinX[dir], nextMaxX[dir], nextMinY[dir], nextMaxY[dir], minX + dx[dir], maxX + dx[dir], minY + dy[dir], maxY + dy[dir]);
}

void turnState(int dir, long long minX, long long maxX, long long minY, long long maxY, long long nextMinX[], long long nextMaxX[], long long nextMinY[], long long nextMaxY[]) {
    updateState(nextMinX[dir], nextMaxX[dir], nextMinY[dir], nextMaxY[dir], minX, maxX, minY, maxY);
}

void solve(const string &commands, int caseId) {
    long long minX[4], maxX[4], minY[4], maxY[4];
    for (int dir = 0; dir < 4; dir++) {
        minX[dir] = minY[dir] = inf;
        maxX[dir] = maxY[dir] = -inf;
    }
    minX[0] = maxX[0] = minY[0] = maxY[0] = 0;
    for (char command : commands) {
        long long nextMinX[4], nextMaxX[4], nextMinY[4], nextMaxY[4];
        for (int dir = 0; dir < 4; dir++) {
            nextMinX[dir] = nextMinY[dir] = inf;
            nextMaxX[dir] = nextMaxY[dir] = -inf;
        }
        for (int dir = 0; dir < 4; dir++) {
            if (minX[dir] == inf) continue;
            if (command == 'L' || command == '?') turnState((dir + 1) % 4, minX[dir], maxX[dir], minY[dir], maxY[dir], nextMinX, nextMaxX, nextMinY, nextMaxY);
            if (command == 'R' || command == '?') turnState((dir + 3) % 4, minX[dir], maxX[dir], minY[dir], maxY[dir], nextMinX, nextMaxX, nextMinY, nextMaxY);
            if (command == 'F' || command == '?') moveState(dir, minX[dir], maxX[dir], minY[dir], maxY[dir], nextMinX, nextMaxX, nextMinY, nextMaxY);
        }
        for (int dir = 0; dir < 4; dir++) {
            minX[dir] = nextMinX[dir];
            maxX[dir] = nextMaxX[dir];
            minY[dir] = nextMinY[dir];
            maxY[dir] = nextMaxY[dir];
        }
    }
    long long ansMinX = inf, ansMaxX = -inf, ansMinY = inf, ansMaxY = -inf;
    for (int dir = 0; dir < 4; dir++) {
        ansMinX = min(ansMinX, minX[dir]);
        ansMaxX = max(ansMaxX, maxX[dir]);
        ansMinY = min(ansMinY, minY[dir]);
        ansMaxY = max(ansMaxY, maxY[dir]);
    }
    cout << "Case " << caseId << ": " << ansMinX << ' ' << ansMaxX << ' ' << ansMinY << ' ' << ansMaxY << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string commands;
    int caseId = 1;
    while (cin >> commands) solve(commands, caseId++);
    return 0;
}
