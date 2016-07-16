// Board Silly
// UVa ID: 395
// Verdict: Accepted
// Submission Date: 2016-07-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

char grid[8][8];
int steps[8][8][8], copies[8][8][8];
int offset[8][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {1, 1}, {1, -1}, {-1, 1}};

struct action
{
    string from, to;
    bool operator<(const action &next) const
    {
        if (from != next.from)
            return from < next.from;
        else
            return to < next.to;
    }
};

void findMove(char piece)
{
    memset(steps, 0, sizeof(steps));
    memset(copies, 0, sizeof(copies));

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (grid[i][j] == piece)
            {
                for (int d = 0; d < 8; d++)
                {
                    int next_i = i + offset[d][0], next_j = j + offset[d][1];
                    int totalPieces = 0;
                    while (next_i >= 0 && next_i < 8 && next_j >= 0 && next_j < 8)
                    {
                        if (grid[next_i][next_j] != '.')
                            totalPieces++;
                        next_i += offset[d][0], next_j += offset[d][1];
                    }
                    copies[i][j][d] = totalPieces;
                }
                
                for (int d = 0; d < 4; d++)
                {
                    steps[i][j][2 * d] = copies[i][j][2 * d] + copies[i][j][2 * d + 1] + 1;
                    steps[i][j][2 * d + 1] = copies[i][j][2 * d] + copies[i][j][2 * d + 1] + 1;
                }
            }

    vector<action> allMoves;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (grid[i][j] == piece)
            {
                for (int d = 0; d < 8; d++)
                {
                    int next_i = i + offset[d][0] * steps[i][j][d];
                    int next_j = j + offset[d][1] * steps[i][j][d];
                    
                    if (next_i >= 0 && next_i < 8 && next_j >= 0 && next_j < 8 && grid[next_i][next_j] != piece)
                    {
                        bool flag = true;
                        for (int k = 1; k < steps[i][j][d]; k++)
                            if (grid[i + offset[d][0] * k][j + offset[d][1] * k] != '.' &&
                                grid[i + offset[d][0] * k][j + offset[d][1] * k] != piece)
                            {
                                flag = false;
                                break;
                            }
                        if (flag)
                        {
                            action aAction;
                            aAction.from += ('A' + i), aAction.from += '1' + j;
                            aAction.to += ('A' + next_i), aAction.to += '1' + next_j;
                            allMoves.push_back(aAction);
                        }
                    }
                }
            }

    sort(allMoves.begin(), allMoves.end());
    for (auto aMove : allMoves)
        cout << aMove.from << "-" << aMove.to << endl;

    if (allMoves.size() == 0) cout << "No moves are possible" << endl;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    char piece;
    int counter = 0, cases = 0;

    while (cin >> piece)
    {
        grid[counter / 8][counter % 8] = piece, counter++;
        if (counter == 64) 
        {
            if (cases++) cout << endl;
            cin >> piece, findMove(piece), counter = 0;
        }
    }

	return 0;
}
