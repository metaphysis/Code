// Eight
// UVa ID: 652
// Verdict: Accepted
// Submission Date: 2016-08-30
// UVa Run Time: 0.220s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int HASH = 201599;

struct state
{
    string matrix, moves;
    int i, j;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int offset[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    string matrix = "123456789", move = "dulr", empty;

    map<int, string> solutions[HASH];

    queue<state> unvisited;
    unvisited.push((state){matrix, empty, 2, 2});

    while (!unvisited.empty())
    {
        state current = unvisited.front();
        unvisited.pop();

        int tag = stoi(current.matrix), hash = tag % HASH;
        if (solutions[hash].find(tag) == solutions[hash].end())
        {
            solutions[hash][tag] = current.moves;

            for (int k = 0; k < 4; k++)
            {
                int nexti = current.i + offset[k][0];
                int nextj = current.j + offset[k][1];
                
                if (nexti >= 0 && nexti < 3 && nextj >= 0 && nextj < 3)
                {
                    string next = current.matrix;
                    swap(next[current.i * 3 + current.j], next[nexti * 3 + nextj]);
                    unvisited.push((state){next, current.moves + move[k], nexti, nextj});
                }
            }
        }
    }

    int cases;
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        string matrix(9, '0');
        for (int i = 0; i < 9; i++)
        {
            cin >> matrix[i];
            if (matrix[i] == 'x') matrix[i] = '9';
        }

        int tag = stoi(matrix), hash = tag % HASH;
        if (solutions[hash].find(tag) == solutions[hash].end())
            cout << "unsolvable\n";
        else
        {
            string answer = solutions[hash][tag];
            reverse(answer.begin(), answer.end());
            cout << answer << '\n';
        }
    }

	return 0;
}
