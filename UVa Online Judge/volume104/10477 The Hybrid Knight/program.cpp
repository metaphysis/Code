// The Hybrid Knight
// UVa ID: 10477
// Verdict: Accepted
// Submission Date: 2019-08-17
// UVa Run Time: 0.390s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 25, INF = 0x7f7f7f7f;

int N, S, B, E, D[MAXN][MAXN][4];

bool inBounds(int r, int c)
{
    return r >= 0 && r < N && c >= 0 && c < N;
}

void bfs(int sr, int sc)
{
    queue<int> R, C, S, T;
    for (int i = 0; i <= 2; i++)
        R.push(sr), C.push(sc), S.push(0), T.push(i), D[sr][sc][i] = 0;
    D[sr][sc][3] = 0;
    int r, c, s, t, nr, nc;
    // Mutant Pawn.
    int dr1[8] = {0, 0, 1, -1, 1, 1, -1, -1}, dc1[8] = {1, -1, 0, 0, 1, -1, 1, -1};
    // Knight.
    int dr2[8] = {2, 2, 1, 1, -2, -2, -1, -1}, dc2[8] = {1, -1, 2, -2, 1, -1, 2, -2};
    // Mutant Knight.
    int dr3[8] = {3, 3, 1, 1, -3, -3, -1, -1}, dc3[8] = {1, -1, 3, -3, 1, -1, 3, -3};
    while (!R.empty())
    {
        r = R.front(); R.pop();
        c = C.front(); C.pop();
        s = S.front(); S.pop();
        t = T.front(); T.pop();
        // Mutant Pawn.
        if (t == 0)
        {
            // Next move as a Knight.
            for (int k = 0; k < 8; k++)
            {
                nr = r + dr2[k], nc = c + dc2[k];
                if (inBounds(nr, nc) && D[nr][nc][1] > s + 1)
                {
                    D[nr][nc][1] = s + 1;
                    R.push(nr), C.push(nc), S.push(s + 1), T.push(1);
                }
            }
        }
        // Knight.
        else if (t == 1)
        {
            // Next move as a Mutant Knight.
            for (int k = 0; k < 8; k++)
            {
                nr = r + dr3[k], nc = c + dc3[k];
                if (inBounds(nr, nc) && D[nr][nc][2] > s + 1)
                {
                    D[nr][nc][2] = s + 1;
                    R.push(nr), C.push(nc), S.push(s + 1), T.push(2);
                }
            }
        }
        // Mutant Knight.
        else
        {
            // Next move as Mutant Pawn.
            for (int k = 0; k < 4; k++)
            {
                nr = r + dr1[k], nc = c + dc1[k];
                if (inBounds(nr, nc) && D[nr][nc][0] > s + 1)
                {
                    D[nr][nc][0] = s + 1;
                    R.push(nr), C.push(nc), S.push(s + 1), T.push(0);
                }
            }
            // Last move.
            for (int k = 4; k < 8; k++)
            {
                nr = r + dr1[k], nc = c + dc1[k];
                if (!inBounds(nr, nc)) continue;
                D[nr][nc][3] = min(D[nr][nc][3], s + 1);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1, sr, sc, er, ec;
    while (cin >> N >> S)
    {
        if (N == 0) break;
        cout << "Set " << cases++ << ":\n";
        for (int i = 1; i <= S; i++)
        {
            cin >> B >> E;
            B--, E--;
            sr = B / N, sc = B % N;
            er = E / N, ec = E % N;
            memset(D, INF, sizeof(D));
            bfs(sr, sc);
            int minD = INF;
            for (int j = 0; j <= 3; j++)
                minD = min(minD, D[er][ec][j]);
            if (minD == INF) cout << "?\n";
            else cout << minD << '\n';
        }
    }
    return 0;
}
