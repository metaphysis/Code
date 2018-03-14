// The Domino Effect
// UVa ID: 211
// Verdict: Accepted
// Submission Date: 2016-04-28
// UVa Run Time: 0.100s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int grid[7][8], map[7][8], bone[28][2], solutions, cases = 0;
int location[2][2] = { {0, 1}, {1, 0} };

void backtrack(int matched)
{
    if (matched == 28)
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 8; j++)
                cout << setw(4) << map[i][j];
            cout << "\n";
        }
        cout << "\n";

        solutions++;

        return;
    }

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 8; j++)
            if (map[i][j] == 0 && (grid[i][j] == bone[matched][0]
                    || grid[i][j] == bone[matched][1]))
            {
                for (int m = 0; m < 2; m++)
                {
                    int ii = i + location[m][0];
                    int jj = j + location[m][1];

                    if (ii < 0 || jj < 0 || ii > 6 || jj > 7)
                        continue;

                    if (map[ii][jj] == 0 &&
                        ((grid[i][j] == bone[matched][0]
                                && grid[ii][jj] == bone[matched][1])
                            || (grid[i][j] == bone[matched][1]
                                && grid[ii][jj] == bone[matched][0])))
                    {
                        map[i][j] = matched + 1;
                        map[ii][jj] = matched + 1;
                        backtrack(matched + 1);
                        map[i][j] = 0;
                        map[ii][jj] = 0;
                    }
                }
            }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);

    for (int i = 7, x = 0, y = 0, index = 0; i >= 1; i--, x++, y++)
        for (int j = y; j <= 6; j++, index++)
        {
            bone[index][0] = x;
            bone[index][1] = j;
        }

    int number, counter = 0;
    while (cin >> number)
    {
        grid[counter / 8][counter % 8] = number;

        counter++;

        if (counter == 56)
        {
            if (cases > 0)
                cout << "\n\n\n";

            cases++;
            cout << "Layout #" << cases << ":\n";
            cout << "\n";

            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 8; j++)
                    cout << setw(4) << grid[i][j];
                cout << "\n";
            }
            cout << "\n";

            cout << "Maps resulting from layout #" << cases << " are:\n";
            cout << "\n";

            solutions = 0;
            memset(map, 0, sizeof(map));
            backtrack(0);

            cout << "There are " << solutions << " solution(s) for layout #" <<
                cases << ".\n";
            counter = 0;
        }
    }

    return 0;
}
