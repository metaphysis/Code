// Cube
// UVa ID: 10601
// Verdict: Accepted
// Submission Date: 2019-10-24
// UVa Run Time: 1.690s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int permutations[24][12] = {
    { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11},
    { 4,  3,  7, 11,  8,  0,  2, 10,  5,  1,  6,  9},
    { 5,  9,  6,  1,  0,  8, 10,  2,  4, 11,  7,  3},
    { 8, 11, 10,  9,  5,  4,  7,  6,  0,  3,  2,  1},
    { 1,  2,  3,  0,  5,  6,  7,  4,  9, 10, 11,  8},
    { 3,  0,  1,  2,  7,  4,  5,  6, 11,  8,  9, 10},
    { 2,  3,  0,  1,  6,  7,  4,  5, 10, 11,  8,  9},
    { 2,  6, 10,  7,  3,  1,  9, 11,  0,  5,  8,  4},
    { 8,  5,  0,  4, 11,  9,  1,  3, 10,  6,  2,  7},
    {10,  9,  8, 11,  7,  6,  5,  4,  2,  1,  0,  3},
    { 0,  4,  8,  5,  1,  3, 11,  9,  2,  7, 10,  6},
    {10,  7,  2,  6,  9, 11,  3,  1,  8,  4,  0,  5},
    { 6,  1,  5,  9, 10,  2,  0,  8,  7,  3,  4, 11},
    { 7, 11,  4,  3,  2, 10,  8,  0,  6,  9,  5,  1},
    {11, 10,  9,  8,  4,  7,  6,  5,  3,  2,  1,  0},
    { 9,  8, 11, 10,  6,  5,  4,  7,  1,  0,  3,  2},
    { 1,  5,  9,  6,  2,  0,  8, 10,  3,  4, 11,  7},
    { 5,  0,  4,  8,  9,  1,  3, 11,  6,  2,  7, 10},
    {11,  4,  3,  7, 10,  8,  0,  2,  9,  5,  1,  6},
    { 6, 10,  7,  2,  1,  9, 11,  3,  5,  8,  4,  0},
    { 4,  8,  5,  0,  3, 11,  9,  1,  7, 10,  6,  2},
    { 3,  7, 11,  4,  0,  2, 10,  8,  1,  6,  9,  5},
    { 7,  2,  6, 10, 11,  3,  1,  9,  4,  0,  5,  8},
    { 9,  6,  1 , 5,  8, 10,  2,  0, 11,  7,  3,  4}
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    if (0)
    {
        int visited[12] = {0};
        for (int i = 0; i < 24; i++)
        {
            cout << '[';
            for (int j = 0; j < 12; j++)
            {
                if (j) cout << ' ';
                cout << permutations[i][j] + 1;
            }
            cout << "] = ";
            memset(visited, 0, sizeof(visited));
            for (int j = 0; j < 12; j++)
                if (!visited[j])
                {
                    visited[j] = 1;
                    cout << '(';
                    cout << j + 1;
                    for (int k = permutations[i][j]; k != j; k = permutations[i][k])
                    {
                        visited[k] = 1;
                        cout << ' ' << k + 1;
                    }
                    cout << ')';
                }
            cout << '\n';
        }
    }

    int cases, rods[12];
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        memset(rods, 0, sizeof(rods));
        for (int i = 0; i < 12; i++)
        {
            cin >> rods[i];
            rods[i]--;
        };
        sort(rods, rods + 12);
        int tot = 0;
        do
        {
            for (int i = 0; i < 24; i++)
            {
                int same = 1;
                for (int j = 0; j < 12; j++)
                    if (rods[j] != rods[permutations[i][j]])
                    {
                        same = 0;
                        break;
                    }
                if (same) tot++;
            }
        }
        while (next_permutation(rods, rods + 12));
        cout << tot / 24 << '\n';
    }

    return 0;
}
