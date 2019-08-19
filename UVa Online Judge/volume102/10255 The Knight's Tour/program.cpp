// The Knight's Tour
// UVa ID: 10255
// Verdict: TLE
// Submission Date: 2019-08-19
// UVa Run Time: 3.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 64, INF = 0x3f3f3f3f;

struct point {
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
};

const int offset[8][2] = {
    {-2, -1}, {-2, 1}, {-1, 2}, {1, 2},
    {2, 1}, {2, -1}, {-1, -2}, {1, -2}
};

int visited[MAXN][MAXN];
int NR, NC, NT, cnt[MAXN][MAXN];
vector<point> path;

bool cmp(point &a, point &b) { return cnt[a.x][b.y] < cnt[b.x][b.y]; }

// 使用“过时”的“后继方格”数量，效率较低，会超时。
bool dfs(int r, int c, int depth)
{
    if (depth == NT) {
        path.push_back(point(r, c));
        return true;
    }
    int tot = 0;
    point ps[9];
    for (int i = 0; i < 8; i++) {
        int nr = r + offset[i][0], nc = c + offset[i][1];
        if (nr < 0 || nr >= NR || nc < 0 || nc >= NC) continue;
        if (visited[nr][nc]) continue;
        ps[tot++] = point(nr, nc);
    }
    if (!tot) return false;
    sort(ps, ps + tot, cmp);
    for (int i = 0; i < tot; i++)
    {
        visited[ps[i].x][ps[i].y] = 1;
        if (dfs(ps[i].x, ps[i].y, depth + 1)) {
            path.push_back(point(r, c));
            return true;
        }
        visited[ps[i].x][ps[i].y] = 0;
    }
    return false;
}

// 实时更新“后继方格”数量。
bool dfs1(int r, int c, int depth)
{
    if (depth == NT) {
        path.push_back(point(r, c));
        return true;
    }

    srand(time(NULL));
    int minIdx = -1, degree = INF;
    for (int i = 0, j = rand() % 8, k; i < 8; i++) {
        k = (i + j) % 8;
        int nr = r + offset[k][0], nc = c + offset[k][1];
        if (nr < 0 || nr >= NR || nc < 0 || nc >= NC) continue;
        if (visited[nr][nc]) continue;
        cnt[nr][nc]--;
        if (degree > cnt[nr][nc])
        {
            degree = cnt[nr][nc];
            minIdx = k;
        }
    }
    if (minIdx == -1) return false;

    visited[r + offset[minIdx][0]][c + offset[minIdx][1]] = 1;
    if (dfs1(r + offset[minIdx][0], c + offset[minIdx][1], depth + 1)) {
        path.push_back(point(r, c));
        return true;
    }
    visited[r + offset[minIdx][0]][c + offset[minIdx][1]] = 0;
    for (int i = 0; i < 8; i++) {
        int nr = r + offset[i][0], nc = c + offset[i][1];
        if (nr < 0 || nr >= NR || nc < 0 || nc >= NC) continue;
        if (visited[nr][nc]) continue;
        cnt[nr][nc]++;
    }

    return false;
}

bool knightTour(int W, int H, int SR, int SC)
{
    NC = W, NR = H, NT = W * H;

    for (int r = 0; r < NR; r++)
        for (int c = 0; c < NC; c++) {
            cnt[r][c] = 0;
            for (int i = 0; i < 8; i++) {
                int nr = r + offset[i][0], nc = c + offset[i][1];
                if (nr < 0 || nr >= NR || nc < 0 || nc >= NC) continue;
                cnt[r][c]++;
            }
        }

    path.clear();
    memset(visited, 0, sizeof(visited));
    visited[SR - 1][SC - 1] = 1;
    bool r = dfs1(SR - 1, SC - 1, 1);
    if (path.size()) reverse(path.begin(), path.end());
    return r;
}

int main(int argc, char *argv[])
{
    int cases = 0, N, W, H, SR, SC;
    while (cin >> N >> SR >> SC) {
        if (cases++) cout << '\n';
        if (N == 1)
        {
            cout << "    1\n";
            continue;
        }
        if (N <= 5 || N % 2 == 1)
        {
            cout << "No Circuit Tour.\n";
            continue;
        }
        W = H = N;
        while (!knightTour(W, H, SR, SC)) {}
        int board[H][W] = {0};
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                board[path[i * W + j].x][path[i * W + j].y] = i * W + j + 1;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (j) cout << ' ';
                cout << setw(5) << right << board[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}
