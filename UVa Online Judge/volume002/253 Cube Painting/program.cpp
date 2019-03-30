// Cube Painting
// UVa ID: 253
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);

    int transform[24][6] = {
        {1, 2, 3, 4, 5, 6}, {1, 4, 2, 5, 3, 6},
        {1, 5, 4, 3, 2, 6}, {1, 3, 5, 2, 4, 6},
        {2, 6, 3, 4, 1, 5}, {2, 4, 6, 1, 3, 5},
        {2, 1, 4, 3, 6, 5}, {2, 3, 1, 6, 4, 5},
        {3, 1, 2, 5, 6, 4}, {3, 2, 6, 1, 5, 4},
        {3, 6, 5, 2, 1, 4}, {3, 5, 1, 6, 2, 4},
        {4, 1, 5, 2, 6, 3}, {4, 5, 6, 1, 2, 3},
        {4, 6, 2, 5, 1, 3}, {4, 2, 1, 6, 5, 3},
        {5, 1, 3, 4, 6, 2}, {5, 3, 6, 1, 4, 2},
        {5, 6, 4, 3, 1, 2}, {5, 4, 1, 6, 3, 2},
        {6, 2, 4, 3, 5, 1}, {6, 4, 5, 2, 3, 1},
        {6, 5, 3, 4, 2, 1}, {6, 3, 2, 5, 4, 1}
    };

    string line;
    while (getline(cin, line))
    {
        string first = line.substr(0, 6);
        string second = line.substr(6, 6);

        bool found = false;
        for (int i = 0; i < 24; i++)
        {
            string temp;
            for (int j = 0; j < 6; j++)
                temp.append(1, first[transform[i][j] - 1]);

            if (temp == second)
            {
                found = true;
                break;
            }
        }

        if (found)
            cout << "TRUE\n";
        else
            cout << "FALSE\n";
    }

    return 0;
}
