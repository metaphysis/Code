// Dead Or Not - That Is The Question
// UVa IDs: 286
// Verdict: Accetped
// Submission Date: 2016-06-04
// UVa Run Time: 0.120s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

// The problem statement is not so clear.
// When a pawn is in the 8th row, do I have to count it as any potentially promoted piece?
// NO, you can assume that potential promotion already took place. so, a pawn in the 8th row is just a pawn.
// The input is given as row by row, first a1 - h1, then a2 - h2, etc.

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

char chessboard[8][8];
int offset[16][2] = {
    {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {-1, -1}, {1, -1}, {1, 1}, {-1, 1},
    {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}
};


bool check(int blackKingX, int blackKingY)
{
    // horizontal or vertical, rook or queen or pawn or king
    for (int i = 0; i < 4; i++)
    {
        int x = blackKingX + offset[i][0], y = blackKingY + offset[i][1];
        int step = 0;
        while (x >= 0 && y >= 0 && x < 8 && y < 8)
        {
            step++;
            if (chessboard[x][y] == ' ')
            {
                x += offset[i][0], y += offset[i][1];
                continue;
            }
            
            if (chessboard[x][y] == 'r' || chessboard[x][y] == 'q')
                return true;
            
            if (chessboard[x][y] == 'k' && step == 1)
                return true;
                    
            break;
        }
    }
    
    // diagonal, bishop or queen or pawn or king
    for (int i = 4; i < 8; i++)
    {
        int x = blackKingX + offset[i][0], y = blackKingY + offset[i][1];
        int step = 0;
        while (x >= 0 && y >= 0 && x < 8 && y < 8)
        {
            step++;
            
            if (chessboard[x][y] == ' ')
            {
                x += offset[i][0], y += offset[i][1];
                continue;
            }
                
            if (chessboard[x][y] == 'b' || chessboard[x][y] == 'q')
                return true;
            
            if (chessboard[x][y] == 'p' && step == 1 && x < blackKingX)
                return true;
                
            if (chessboard[x][y] == 'k' && step == 1)
                return true;
                    
            break;
        }
    }
    
    // knight
    for (int i = 8; i < 16; i++)
    {
        int x = blackKingX + offset[i][0], y = blackKingY + offset[i][1];
        if (x >= 0 && y >= 0 && x < 8 && y < 8)
        { 
            if (chessboard[x][y] == 'n')
                return true;
        }
    }
    
    return false;
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        int blackKingX, blackKingY;
        for (int i = 0; i < line.length(); i++)
        {
            chessboard[i / 8][i % 8] = line[i];
            if (line[i] == 'K')
            {
                blackKingX = i / 8;
                blackKingY = i % 8;
            }
            
            //cout << line[i];
            //if (i % 8 == 7)
                //cout << endl;
        }
        
        bool checkmate = check(blackKingX, blackKingY);
        bool next_checkmate = true;
        chessboard[blackKingX][blackKingY] = ' ';
        for (int i = 0; i < 8; i++)
        {
            int x = blackKingX + offset[i][0], y = blackKingY + offset[i][1];
            if (x >= 0 && y >= 0 && x < 8 && y < 8)
            {
                next_checkmate = check(x, y);
                if (!next_checkmate)
                    break;
            }
        }
        
        if (checkmate && next_checkmate)
            cout << "checkmate" << endl;
        else if (!checkmate && next_checkmate)
            cout << "draw" << endl;
        else
            cout << "game is not over" << endl;
    }
	return 0;
}
