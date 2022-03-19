// 参考：
// https://www.geeksforgeeks.org/warnsdorffs-algorithm-knights-tour-problem/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 64;

int N, SR, SC, board[MAXN][MAXN];

static int dr[8] = { 1, 1, 2, 2, -1, -1, -2, -2 };
static int dc[8] = { 2, -2, 1, -1, 2, -2, 1, -1 };

inline bool isInBounds(int r, int c)
{
    return ((r >= 0 && c >= 0) && (r < N && c < N));
}

inline bool isEmpty(int r, int c)
{
    return isInBounds(r, c) && (!board[r][c]);
}

inline int getDegree(int r, int c)
{
    int cnt = 0;
    for (int i = 0; i < 8; i++)
        if (isEmpty(r + dr[i], c + dc[i]))
            cnt++;
    return cnt;
}

bool nextMove(int *r, int *c)
{
    int minDegIdx = -1, degree, minDeg = 8, nr, nc;
    int si = rand() % 8;
    for (int i = rand() % 8, j = 0, k; j < 8; j++)
    {
        k = (i + j) % 8;
        nr = *r + dr[k], nc = *c + dc[k];
        if ((isEmpty(nr, nc)) && (degree = getDegree(nr, nc)) < minDeg)
        {
            minDegIdx = k;
            minDeg = degree;
        }
    }
    if (minDegIdx == -1) return false;
    nr = *r + dr[minDegIdx];
    nc = *c + dc[minDegIdx];
    board[nr][nc] = board[*r][*c] + 1;
    *r = nr, *c = nc;
    return true;
}

void render()
{
    //int delta = board[SR - 1][SC - 1], mod = N * N;
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
            //cout << setw(5) << right << (board[r][c] - delta + mod) % mod + 1;
            cout << setw(5) << right << board[r][c];
        cout << '\n';
    }
}

bool neighbour(int er, int ec, int sr, int sc)
{
    for (int i = 0; i < 8; i++)
        if (((er + dr[i]) == sr) && ((ec + dc[i]) == sc))
            return true;
    return false;
}

bool findOpenKnightTour()
{
    //srand(time(NULL));
    //int sr = rand() % N, sc = rand() % N;
    int r = SR - 1, c = SC - 1;
    memset(board, 0, sizeof(board));
    board[r][c] = 1;
    for (int i = 2; i <= N * N; i++)
        if (!nextMove(&r, &c))
            return false;
    //if (!neighbour(r, c, sr, sc)) return false;
    return true;
}

int main(int argc, char *argv[])
{
    int cases = 0;
    while (cin >> N >> SR >> SC)
    {
        if (cases++) cout << '\n';
        if (N == 1)
        {
            cout << "    1\n";
            continue;
        }
        if (N <= 5 || (N % 2 == 1))
        {
            cout << "No Circuit Tour.\n";
            continue;
        }
        while (!findOpenKnightTour()) {}
        render();
    }
    return 0;
}
