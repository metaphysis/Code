#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ULL;

struct point {
    int x, y;
    point (int x = 0, int y = 0): x(x), y(y) {}
};

const int offset[8][2] = {
    {-2, -1}, {-2, 1}, {-1, 2}, {1, 2},
    {2, 1}, {2, -1}, {-1, -2}, {1, -2}
};

ULL SUCCEED;
int NR, NC, cnt[8][8];
vector<point> path;

bool cmp(point &a, point &b) { return cnt[a.x][b.y] < cnt[b.x][b.y]; }

bool dfs(int r, int c, ULL mask)
{
    if (mask == SUCCEED) {
        path.push_back(point(r, c));
        return true;
    }

    int tot = 0;
    point ps[9];
    for (int i = 0; i < 8; i++) {
        int nr = r + offset[i][0], nc = c + offset[i][1];
        if (nr < 0 || nr >= NR || nc < 0 || nc >= NC) continue;
        if (mask & (1ULL << (nr * NC + nc))) continue;
        ps[tot++] = point(nr, nc);
    }
    if (!tot) return false;
    sort(ps, ps + tot, cmp);
    for (int i = 0; i < tot; i++)
        if (dfs(ps[i].x, ps[i].y, mask | (1ULL << (ps[i].x * NC + ps[i].y)))) {
            path.push_back(point(r, c));
            return true;
        }
    return false;
}

void knightTour(int W, int H, int SR, int SC)
{
    NC = W, NR = H;
    SUCCEED = (1ULL << (NR * NC - 1)) + ((1ULL << (NR * NC - 1)) - 1ULL);

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
    dfs(SR - 1, SC - 1, 1ULL << (SR * SC - 1));
    if (path.size()) reverse(path.begin(), path.end());
}

int main(int argc, char *argv[])
{
    int cases = 0, W, H, SR, SC;
    while (cin >> W >> H >> SR >> SC) {
        if (cases++) cout << '\n';
        knightTour(W, H, SR, SC);
        if (path.size()) {
            int board[H][W] = {0};
            for (int i = 0; i < H; i++)
                for (int j = 0; j < W; j++)
                    board[path[i * W + j].x][path[i * W + j].y] = i * W + j + 1;
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    if (j) cout << ' ';
                    cout << setw(2) << right << board[i][j];
                }
                cout << '\n';
            }
        }
        else cout << "No solution.\n";
    }
    return 0;
}
