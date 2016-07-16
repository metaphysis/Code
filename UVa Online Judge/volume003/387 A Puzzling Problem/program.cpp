// A Puzzling Problem
// UVa ID: 387
// Verdict: Accepted
// Submission Date: 2016-07-05
// UVa Run Time: 0.170s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

vector < pair < pair < int, int >, vector < int >>> pieces;
vector < bool > visited;
int grid[4][4];

void display()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << grid[i][j];
        cout << endl;
    }
}

void pullOut(int digit)
{
    //cout << "pull out " << digit << endl;
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == (digit + 1))
                grid[i][j] = 0;
                
    //cout << "after pull out ########" << endl;
    //display();
    //cout << "after pull out ########" << endl;
}

bool pushIn(int digit, int row, int column)
{
    if (row + pieces[digit].first.first > 4 || column + pieces[digit].first.second > 4) return false;
    
    //cout << "push in ########" << endl;
    //for (int r = 0; r < pieces[digit].first.first; r++)
    //{
    //    for (int c = 0; c < pieces[digit].first.second; c++)
    //        cout << pieces[digit].second[r * pieces[digit].first.second + c];
    //    cout << endl;
    //}
    //cout << "push in ########" << endl;
    
    bool success = true;
    for (int r = 0; r < pieces[digit].first.first; r++)
        for (int c = 0; c < pieces[digit].first.second; c++)
        {
            int block = pieces[digit].second[r * pieces[digit].first.second + c];
            if (grid[row + r][column + c] == 0)
                grid[row + r][column + c] = block;
            else if (block != 0)
            {
                success = false;
                goto out;
            }
        }

  out:
    if (!success)
        pullOut(digit);

    return success;
}

bool dfs(int depth, int n)
{
    if (depth == n)
    {
        display();
        return true;
    }

    for (int i = 0; i < visited.size(); i++)
        if (!visited[i])
        {
            visited[i] = true;
            for (int row = 0; row < 4; row++)
                for (int column = 0; column < 4; column++)
                    if ((grid[row][column] == 0 || pieces[i].second.front() == 0) && pushIn(i, row, column))
                    {
                        if (dfs(depth + 1, n))
                            return true;
                        pullOut(i);
                    }
            visited[i] = false;
        }

    return false;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n, cases = 0, row, column;
    string line;

    while (cin >> n, n)
    {
        pieces.clear();

        int cell = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> row >> column;
            vector < int > matrix;
            for (int j = 1; j <= row; j++)
            {
                cin >> line;
                cell += count(line.begin(), line.end(), '1');
                for (int k = 0; k < line.length(); k++)
                {
                    if (line[k] == '1')
                        matrix.push_back(i);
                    else
                        matrix.push_back(0);
                }
            }
            pieces.push_back(make_pair(make_pair(row, column), matrix));
        }

        if (cases++)
            cout << endl;

        if (cell != 16)
        {
            cout << "No solution possible" << endl;
            continue;
        }

        visited.resize(n);
        fill(visited.begin(), visited.end(), false);
        memset(grid, 0, sizeof(grid));

        if (!dfs(0, n))
            cout << "No solution possible" << endl;
    }

    return 0;
}
