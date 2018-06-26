// Security Panel
// UVa ID: 10318
// Verdict: Accepted
// Submission Date: 2018-06-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int masks[25], best, threshold;
int ALL_BUTTONS_LIGHTED, N, R, C;

void dfs(int idx, int board, int pressed, int buttons)
{
    // Pruning: if current at i >= 3 row, then check if previous (i - 2) row all lighted.
    if (idx >= 2 * C)
    {
        int bit = (1 << ((idx / C - 1) * C)) - 1;
        if ((board & bit) != bit) return;
    }
    // Pruning: the number of buttons pressed is bigger than best solution.
    if (buttons >= threshold) return;
    // Check if all button lighted.
    if (board == ALL_BUTTONS_LIGHTED)
    {
        // Check if the current solution better.
        if (buttons < threshold) 
        {
            best = pressed;
            threshold = buttons;
        }
        return;
    }
    // Terminate DFS.
    if (idx >= N) return;
    // DFS with current button pressed or unpressed.
    dfs(idx + 1, board, pressed, buttons);
    dfs(idx + 1, board ^ masks[idx], pressed | (1 << idx), buttons + 1);
}

void setMask(int mask)
{
    int offset[9][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
        {
            masks[i * C + j] = 0;
            for (int k = 0; k < 9; k++)
            {
                int ii = i + offset[k][0], jj = j + offset[k][1];
                if (ii >= 0 && ii < R && jj >= 0 && jj < C)
                {
                    if (mask & (1 << k))
                        masks[i * C + j] |= (1 << (ii * C + jj));
                }
            }
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;

    while (cin >> R >> C)
    {
        if (R == 0) break;

        int mask = 0;
        char pattern;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                cin >> pattern;
                if (pattern == '*') mask |= (1 << (i * 3 + j));
            }

        setMask(mask);

        N = R * C, threshold = N + 1, ALL_BUTTONS_LIGHTED = (1 << N) - 1;

        dfs(0, 0, 0, 0);

        cout << "Case #" << ++cases << '\n';
        if (threshold == (N + 1)) cout << "Impossible.\n";
        else
        {
            int buttons = 1, printed = 0;
            while (best)
            {
                if (best & 1)
                {
                    if (printed++) cout << ' ';
                    cout << buttons;
                }
                best >>= 1, buttons++;
            }
            cout << '\n';
        }
    }

    return 0;
}
