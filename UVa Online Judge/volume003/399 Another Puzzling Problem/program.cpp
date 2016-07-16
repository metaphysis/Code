// Another Puzzling Problem
// UVa ID: 399
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.000s
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

struct piece
{
    int top, left, bottom, right;
    char image[30][30];
};

vector<piece> pieces;
vector<bool> visited;
int puzzle[15][15], dimension, row, column;
char picture[110][900];

bool backtrack(int depth)
{
    if (depth == dimension * dimension)
    {
        int top = 0;
        for (int height = 0; height < dimension; height++)
        {
            int left = 0;
            for (int width = 0; width < dimension; width++)
            {
                for (int r = 0; r < row; r++)
                    for (int c = 0; c < column; c++)
                        picture[top + r][left + c] = pieces[puzzle[height][width]].image[r][c];
                left += column;
            }
            top += row;
        }

        for (int i = 0; i < dimension * row; i++)
        {
            for (int j = 0; j < dimension * column; j++)
                cout << picture[i][j];
            cout << endl;
        }
        return true;
    }

    int r = depth / dimension, c = depth % dimension;
    int top = -10, left = -10, bottom = -10, right = -10;
    if (r == 0)
        top = 0;
    else
        top = -pieces[puzzle[r - 1][c]].bottom;
        
    if (c == 0)
        left = 0;
    else
        left = -pieces[puzzle[r][c - 1]].right;
        
    if (r == dimension - 1)
        bottom = 0;

    if (c == dimension - 1)
        right = 0;

    for (int i = 0; i < pieces.size(); i++)
        if (visited[i] == false && (top == -10 || pieces[i].top == top) &&
            (left == -10 || pieces[i].left == left) && (bottom == -10 || pieces[i].bottom == bottom)
            && (right == -10 || pieces[i].right == right))
        {
            visited[i] = true;
            puzzle[r][c] = i;
            if (backtrack(depth + 1))
                return true;
            visited[i] = false;
        }

    return false;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n;
    char cell;
    string line;
    istringstream iss;

    getline(cin, line);
    n = stoi(line);

    for (int i = 1; i <= n; i++)
    {
        if (i > 1)
            cout << endl;

        pieces.clear();

        getline(cin, line);
        iss.clear();
        iss.str(line);
        iss >> dimension >> row >> column;

        for (int j = 1; j <= dimension * dimension; j++)
        {
            piece aPiece;
            for (int r = 0; r < row; r++)
            {
                getline(cin, line);
                for (int c = 0; c < column; c++)
                    aPiece.image[r][c] = line[c];
            }

            getline(cin, line);
            iss.clear();
            iss.str(line);
            iss >> aPiece.top >> aPiece.left >> aPiece.bottom >> aPiece.right;
            pieces.push_back(aPiece);

            getline(cin, line);
        }

        visited.resize(dimension * dimension);
        fill(visited.begin(), visited.end(), false);

        backtrack(0);
    }

    return 0;
}
