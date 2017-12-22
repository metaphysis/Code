// Chessboard in FEN
// UVa ID: 10284
// Verdict: Accepted
// Submission Date: 2017-12-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char chess[8][8];
    int used[8][8];

    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        string block;
        
        memset(chess, '0', sizeof(chess));
        memset(used, 0, sizeof(used));

        int rows = 0;
        while (getline(iss, block, '/'))
        {
            int clns = 0;
            for (int i = 0; i < block.length(); i++)
            {
                if (isdigit(block[i]))
                {
                    clns += block[i] - '0';
                }
                else
                {
                    chess[rows][clns++] = block[i];
                }
            }
            rows++;
        }

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                if (chess[i][j] != '0')
                {
                    used[i][j] = 1;
                    if (chess[i][j] == 'k' || chess[i][j] == 'K')
                    {
                        int offseti[] = {-1, -1, -1, 0, 1, 1, 1, 0}, offsetj[] = {-1, 0, 1, 1, 1, 0, -1, -1};
                        for (int k = 0; k < 8; k++)
                        {
                            int ii = i + offseti[k], jj = j + offsetj[k];
                            if (ii >= 0 && ii < 8 && jj >= 0 && jj < 8)
                            {
                                used[ii][jj] = 1;
                            }
                        }
                    }
                    else if (chess[i][j] == 'q' || chess[i][j] == 'Q')
                    {
                        int offseti[] = {-1, -1, -1, 0, 1, 1, 1, 0}, offsetj[] = {-1, 0, 1, 1, 1, 0, -1, -1};
                        for (int k = 0; k < 8; k++)
                        {
                            int ii = i + offseti[k], jj = j + offsetj[k];
                            while (ii >= 0 && ii < 8 && jj >= 0 && jj < 8 && chess[ii][jj] == '0')
                            {
                                used[ii][jj] = 1;
                                ii += offseti[k], jj += offsetj[k];
                            }
                        }
                    }
                    else if (chess[i][j] == 'b' || chess[i][j] == 'B')
                    {
                        int offseti[] = {-1, -1, 1, 1}, offsetj[] = {-1, 1, 1, -1};
                        for (int k = 0; k < 4; k++)
                        {
                            int ii = i + offseti[k], jj = j + offsetj[k];
                            while (ii >= 0 && ii < 8 && jj >= 0 && jj < 8 && chess[ii][jj] == '0')
                            {
                                used[ii][jj] = 1;
                                ii += offseti[k], jj += offsetj[k];
                            }
                        }
                    }
                    else if (chess[i][j] == 'n' || chess[i][j] == 'N')
                    {
                        int offseti[] = {-2, -1, -2, -1, 1, 2, 1, 2}, offsetj[]  = {-1, -2, 1, 2, 2, 1, -2, -1};
                        for (int k = 0; k < 8; k++)
                        {
                            int ii = i + offseti[k], jj = j + offsetj[k];
                            if (ii >= 0 && ii < 8 && jj >= 0 && jj < 8)
                            {
                                used[ii][jj] = 1;
                            }
                        }
                    }
                    else if (chess[i][j] == 'r' || chess[i][j] == 'R')
                    {
                        int offseti[] = {0, -1, 0, 1}, offsetj[] = {-1, 0, 1, 0};
                        for (int k = 0; k < 4; k++)
                        {
                            int ii = i + offseti[k], jj = j + offsetj[k];
                            while (ii >= 0 && ii < 8 && jj >= 0 && jj < 8 && chess[ii][jj] == '0')
                            {
                                used[ii][jj] = 1;
                                ii += offseti[k], jj += offsetj[k];
                            }
                        }
                    }
                    else if (chess[i][j] == 'p')
                    {
                        int offseti[] = {1, 1}, offsetj[] = {-1, 1};
                        for (int k = 0; k < 2; k++)
                        {
                            int ii = i + offseti[k], jj = j + offsetj[k];
                            if (ii >= 0 && ii < 8 && jj >= 0 && jj < 8)
                            {
                                used[ii][jj] = 1;
                            }
                        }
                    }
                    else if (chess[i][j] == 'P')
                    {
                        int offseti[] = {-1, -1}, offsetj[] = {-1, 1};
                        for (int k = 0; k < 2; k++)
                        {
                            int ii = i + offseti[k], jj = j + offsetj[k];
                            if (ii >= 0 && ii < 8 && jj >= 0 && jj < 8)
                            {
                                used[ii][jj] = 1;
                            }
                        }
                    }
                }
            }

        int unused = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (!used[i][j])
                    unused++;
                    
        cout << unused << '\n';
    }

    return 0;
}
