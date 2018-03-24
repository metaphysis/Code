// Robot Maps
// UVa ID: 10500
// Verdict: Accepted
// Submission Date: 2018-03-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int R, C, r, c;
    while (cin >> R >> C)
    {
        if (R == 0) break;
        cin >> r >> c;
        char maze[R][C];
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                cin >> maze[i][j];
  
        // Walk.
        int moves = 0;
        int visited[R][C] = {}, detected[R][C] = {};
        int offset[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        r--, c--;

        while (true)
        {
            visited[r][c] = detected[r][c] = 1;
            for (int k = 0; k < 4; k++)
            {
                int nextr = r + offset[k][0], nextc = c + offset[k][1];
                if (nextr >= 0 && nextr < R && nextc >= 0 && nextc < C)
                    detected[nextr][nextc] = 1;
            }
            
            bool found = false;
            for (int k = 0; k < 4; k++)
            {
                int nextr = r + offset[k][0], nextc = c + offset[k][1];
                if (nextr >= 0 && nextr < R && nextc >= 0 && nextc < C)
                {
                    if (!visited[nextr][nextc] && maze[nextr][nextc] == '0')
                    {
                        r = nextr, c = nextc;
                        found = true;
                        break;
                    }
                }
            }
            if (!found) break;
            moves++;
        }

        // Print.
        cout << '\n';
        for (int i = 0; i < R; i++)
        {
            // Roof.
            for (int j = 0; j < C; j++) cout << "|---";
            cout << "|\n";
            // Cell.
            for (int j = 0; j < C; j++)
            {
                cout << '|';
                if (detected[i][j])
                    cout << ' ' << maze[i][j] << ' ';
                else
                    cout << " ? ";
            }
            cout << "|\n";
        }
        // Last row.
        for (int j = 0; j < C; j++) cout << "|---";
            cout << "|\n";

        cout << "\nNUMBER OF MOVEMENTS: " << moves << '\n';
    }

    return 0;
}
