#include <bits/stdc++.h>
using namespace std;

const int n = 8, atomCnt = 5;
int dr[4] = {-1, 0, 1, 0}, dc[4] = {0, 1, 0, -1};
int solutionCnt;
bool atom[n][n], answer[n][n];
vector<pair<int, int>> experiments;

int traceBeam(int gate) {
    int row, col, dir;
    if (gate < 8) {
        row = gate;
        col = -1;
        dir = 1;
    } else if (gate < 16) {
        row = n;
        col = gate - 8;
        dir = 0;
    } else if (gate < 24) {
        row = 23 - gate;
        col = n;
        dir = 3;
    } else {
        row = -1;
        col = 31 - gate;
        dir = 2;
    }
    bool visited[n + 2][n + 2][4] = {};
    while (true) {
        int vr = row + 1, vc = col + 1;
        if (visited[vr][vc][dir]) return -2;
        visited[vr][vc][dir] = true;
        int nextRow = row + dr[dir], nextCol = col + dc[dir];
        if (nextRow < 0) return 31 - nextCol;
        if (nextRow >= n) return 8 + nextCol;
        if (nextCol < 0) return nextRow;
        if (nextCol >= n) return 23 - nextRow;
        if (atom[nextRow][nextCol]) return -1;
        int leftDir = (dir + 3) % 4, rightDir = (dir + 1) % 4;
        int leftRow = nextRow + dr[leftDir], leftCol = nextCol + dc[leftDir];
        int rightRow = nextRow + dr[rightDir], rightCol = nextCol + dc[rightDir];
        bool hasLeft = leftRow >= 0 && leftRow < n && leftCol >= 0 && leftCol < n && atom[leftRow][leftCol];
        bool hasRight = rightRow >= 0 && rightRow < n && rightCol >= 0 && rightCol < n && atom[rightRow][rightCol];
        if (hasLeft && hasRight) {
            dir = (dir + 2) % 4;
            continue;
        }
        if (hasLeft) {
            dir = (dir + 1) % 4;
            continue;
        }
        if (hasRight) {
            dir = (dir + 3) % 4;
            continue;
        }
        row = nextRow;
        col = nextCol;
    }
}

bool matchesExperiments() {
    for (const pair<int, int> &experiment : experiments) {
        int result = traceBeam(experiment.first);
        if (result != experiment.second) return false;
    }
    return true;
}

void searchLayouts(int position, int chosen) {
    if (solutionCnt >= 2) return;
    if (chosen == atomCnt) {
        if (!matchesExperiments()) return;
        solutionCnt++;
        if (solutionCnt == 1) {
            for (int row = 0; row < n; row++)
                for (int col = 0; col < n; col++)
                    answer[row][col] = atom[row][col];
        }
        return;
    }
    if (36 - position < atomCnt - chosen) return;
    for (int index = position; index < 36; index++) {
        int row = index / 6 + 1, col = index % 6 + 1;
        atom[row][col] = true;
        searchLayouts(index + 1, chosen + 1);
        atom[row][col] = false;
        if (solutionCnt >= 2) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    for (int testCase = 0; testCase < testCnt; testCase++) {
        int experimentCnt;
        cin >> experimentCnt;
        experiments.resize(experimentCnt);
        for (pair<int, int> &experiment : experiments)
            cin >> experiment.first >> experiment.second;
        memset(atom, false, sizeof(atom));
        memset(answer, false, sizeof(answer));
        solutionCnt = 0;
        searchLayouts(0, 0);
        if (testCase > 0) cout << '\n';
        if (solutionCnt != 1) {
            cout << "NO\n";
            continue;
        }
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++)
                cout << (answer[row][col] ? '+' : '-');
            cout << '\n';
        }
    }
    return 0;
}
