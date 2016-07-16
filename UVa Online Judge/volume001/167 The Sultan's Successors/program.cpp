// The Sultan's Successors
// UVa ID: 167
// Verdict: Accepted
// Submission Date: 2016-02-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int number[64];
int chessboard[8][8];
vector < int > column;
vector< vector < int > > positions;
int steps[4][2] = { {1, 1}, {-1, -1}, {1, -1}, {-1, 1} };

bool isSolution()
{
    fill(chessboard[0], chessboard[0] + 64, false);
    
    for (int i = 0; i < 8; i++)
        chessboard[i][column[i]] = true;

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (chessboard[i][j])
            {
                for (int k = 0; k < 4; k++)
                {
                    int ii = i, jj = j;
                    
                    ii += steps[k][0];
                    jj += steps[k][1];
                    
                    while (0 <= ii && ii <= 7 && 0 <= jj && jj <= 7)
                    {
                        if (chessboard[ii][jj])
                            return false;
                            
                        ii += steps[k][0];
                        jj += steps[k][1];
                    }
                }
            }
        
    return true;
}

void backtrack()
{
    for (int i = 0; i < 8; i++)
        column.push_back(i);
    do
    {
        if (isSolution())
        {
            vector < int > solution;
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    if (chessboard[i][j])
                        solution.push_back(i * 8 + j);
            positions.push_back(solution);
        }
        
    } while (next_permutation(column.begin(), column.end()));
}

int findMaxSum()
{
    int maxSum = 0;
    for (int i = 0; i < positions.size(); i++)
    {
        int sum = 0;
        for (int j = 0; j < positions[i].size(); j++)
            sum += number[positions[i][j]];
        maxSum = max(sum, maxSum);
    }
    return maxSum;
}

int main(int argc, char* argv[])
{
    int k;
    cin >> k;
    
    backtrack();
    
    while (k--)
    {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                cin >> number[i * 8 + j];
        cout << setw(5) << right << findMaxSum() << endl;
    }
    
	return 0;
}
