// Carl the Ant
// UVa ID: 1028
// Verdict: Accepted
// Submission Date: 2026-06-15
// UVa Run Time: 0.060s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}, OFFSET = 100;

struct Ant { int x, y, walked, wait, dir, done; };

int N, M, D;
int cnt, finished, born, now, ex, ey;
int road[210 * 210], smell[210][210], occupied[210][210][4], order[110], wait[110];
Ant ants[110];

void initialize() {
    memset(occupied, -1, sizeof occupied);
    cin >> N >> M >> D;
    int cx = 0, cy = 0;
    cnt = 0;
    for (int i = 0; i < N; i++) {
        int nx, ny;
        cin >> nx >> ny;
        int d;
        if (cx > nx) d = 0;
        else if (cy < ny) d = 1;
        else if (cx < nx) d = 2;
        else d = 3;
        while (cx != nx || cy != ny) {
            road[cnt++] = d;
            cx += dx[d], cy += dy[d];
        }
    }
    finished = born = 0;
}

void simulate() {
    memset(wait, 0, sizeof wait);
    for (int i = 0; i < born; i++) if (!ants[i].done) {
        int x = ants[i].x, y = ants[i].y;
        for (int d = 0; d < 4; d++) {
            int t = occupied[x][y][d];
            if (t >= 0)
                if (ants[t].wait > ants[i].wait || (ants[t].wait == ants[i].wait && ants[t].walked > ants[i].walked)) {
                    wait[i] = 1;
                    break;
                }
        }
    }
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < born; i++) if (!wait[i] && !ants[i].done) {
            int d = smell[ants[i].x][ants[i].y];
            int x = ants[i].x + dx[d], y = ants[i].y + dy[d];
            int t = occupied[x][y][d];
            if (t >= 0 && wait[t]) { wait[i] = changed = 1; continue; }
        }
    } while (changed);
    for (int i = 0; i < born; i++)
        if (!ants[i].done)
            if (!wait[i]) {
                ants[i].walked++;
                ants[i].wait = 0;
                occupied[ants[i].x][ants[i].y][ants[i].dir] = -1;
            } else ants[i].wait++;
    for (int i = 0; i < born; i++)
        if (!wait[i] && !ants[i].done) {
            int x = ants[i].x, y = ants[i].y;
            if (x == OFFSET && y == OFFSET && i != born - 1) occupied[OFFSET][OFFSET][smell[OFFSET][OFFSET]] = i + 1;
            int d = smell[x][y];
            ants[i].x += dx[d], ants[i].y += dy[d], ants[i].dir = d;
            if (ants[i].x == ex && ants[i].y == ey) {
                order[finished++] = i;
                ants[i].done = 1;
            } else occupied[ants[i].x][ants[i].y][d] = i;
        }
}

void solve(int cs, int T) {
    initialize();
    int cx = OFFSET, cy = OFFSET;
    ex = ey = -1;
    for (now = 0; finished < M; now++) {
        if (now < cnt) {
            smell[cx][cy] = road[now];
            cx += dx[road[now]], cy += dy[road[now]];
            if (now == cnt - 1) ex = cx, ey = cy;
        }
        if (now % D == 0 && born < M) {
            int sd = smell[OFFSET][OFFSET];
            if (occupied[OFFSET][OFFSET][sd]) occupied[OFFSET][OFFSET][sd] = born;
            ants[born++] = {OFFSET, OFFSET, 0, 0, sd, 0};
        }
        simulate();
    }
    cout << "Case " << cs << ":\n";
    cout << "Carl finished the path at time " << ants[0].walked + 1 << '\n';
    cout << "The ants finished in the following order:\n";
    for (int i = 0; i < M; i++) cout << order[i] << " \n"[i == M - 1];
    cout << "The last ant finished the path at time " << now + 1 << '\n';
    if (cs < T) cout << '\n';
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++) solve(cs, T);
    return 0;
}
