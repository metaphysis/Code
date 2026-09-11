// Amazing Maze
// UVa ID: 12607
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 7.490s

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 100;
const int MAXN = 100;
const int MAXK = 8;
int distArr[MAXM][MAXN][4][1 << MAXK];
int dirIdxArr[MAXM][MAXN];
int treasureId[MAXM][MAXN];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int M, N, K;

struct State {
    int r, c, t, mask;
};

int bfs(int fullMask) {
    memset(distArr, -1, sizeof(distArr));
    queue<State> q;
    distArr[0][0][0][0] = 0;
    q.push({0, 0, 0, 0});
    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        int r = cur.r, c = cur.c, t = cur.t, mask = cur.mask;
        int curDist = distArr[r][c][t][mask];
        if (r == M - 1 && c == N - 1 && mask == fullMask)
            return curDist;
        int nt = (t + 1) % 4;
        if (distArr[r][c][nt][mask] == -1) {
            distArr[r][c][nt][mask] = curDist + 1;
            q.push({r, c, nt, mask});
        }
        int dir = (dirIdxArr[r][c] + t) % 4;
        int nr = r + dx[dir];
        int nc = c + dy[dir];
        if (nr >= 0 && nr < M && nc >= 0 && nc < N) {
            int newMask = mask;
            if (treasureId[nr][nc] != -1)
                newMask |= (1 << treasureId[nr][nc]);
            int nt2 = (t + 1) % 4;
            if (distArr[nr][nc][nt2][newMask] == -1) {
                distArr[nr][nc][nt2][newMask] = curDist + 1;
                q.push({nr, nc, nt2, newMask});
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    char dirMap[256];
    dirMap['N'] = 0; dirMap['E'] = 1; dirMap['S'] = 2; dirMap['W'] = 3;
    while (cin >> M >> N) {
        if (M == 0 && N == 0) break;
        for (int i = 0; i < M; ++i) {
            string row;
            cin >> row;
            for (int j = 0; j < N; ++j)
                dirIdxArr[i][j] = dirMap[(int)row[j]];
        }
        cin >> K;
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j)
                treasureId[i][j] = -1;
        for (int i = 0; i < K; ++i) {
            int r, c;
            cin >> r >> c;
            --r; --c;
            treasureId[r][c] = i;
        }
        int fullMask = (1 << K) - 1;
        cout << bfs(fullMask) << '\n';
    }
    return 0;
}
