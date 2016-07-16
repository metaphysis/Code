// Othello
// UVa ID: 220
// Verdict: Accepted
// Submission Date: 2016-04-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstring>
#include <stack>
#include <map>
#include <queue>
#include <set>

using namespace std;

char board[8][8], player;
string command;
int direction[8][2] = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};

void display()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << board[i][j];
        cout << endl;
    }
}

bool listMove(bool print)
{
    char another = player == 'B' ? 'W' : 'B';
    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
            if (board[x][y] == player)
            {
                for (int i = 0; i < 8; i++)
                {
                    int xx = x, yy = y;
                    int disks = 0;
                    
                    xx += direction[i][0];
                    yy += direction[i][1];
                    while (xx >= 0 && yy >= 0 && xx < 8 && yy < 8)
                    {
                        if (board[xx][yy] == another)
                            disks++;
                        else
                            break;
                            
                        xx += direction[i][0];
                        yy += direction[i][1];
                    }
                    
                    if (disks > 0 &&
                        (xx >= 0 && yy >= 0 && xx < 8 && yy < 8) &&
                        board[xx][yy] == '-')
                        board[xx][yy] = '*';
                }
            }
    
    int legalMoves = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j] == '*')
            {
                if (print && legalMoves)
                    cout << " ";
                    
                if (print)
                    cout << "(" << (i + 1) << "," << (j + 1) << ")";
                    
                legalMoves++;
                board[i][j] = '-';
            }
            
    if (print && legalMoves)
        cout << endl;
    else if (print)
        cout << "No legal move." << endl;
        
    return legalMoves > 0;
}

void makeMove(int x, int y)
{
    board[x][y] = player;
    
    char another = player == 'B' ? 'W' : 'B';
    for (int i = 0; i < 8; i++)
    {
        int xx = x, yy = y;
        int disks = 0;
        
        xx += direction[i][0];
        yy += direction[i][1];
        while (xx >= 0 && yy >= 0 && xx < 8 && yy < 8)
        {
            if (board[xx][yy] == another)
                disks++;
            else
                break;
                
            xx += direction[i][0];
            yy += direction[i][1];
        }
        
        if (disks > 0 &&
            (xx >= 0 && yy >= 0 && xx < 8 && yy < 8) &&
            board[xx][yy] == player)
        {
            xx = x;
            yy = y;
            while (disks--)
            {
                xx += direction[i][0];
                yy += direction[i][1];
                board[xx][yy] = player;
            }
        }
    }
}

void play()
{
    if (command == "L")
    {
        listMove(true);
    }
    else if (command.front() == 'M')
    {
        if (listMove(false) == false)
            player = player == 'B' ? 'W' : 'B';
            
        int x = command[1] - '0' - 1;
        int y = command[2] - '0' - 1;
        
        makeMove(x, y);
        
        //display();
        
        int black = 0, white = 0;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (board[i][j] == 'B')
                    black++;
                else if (board[i][j] == 'W')
                    white++;
        cout << "Black -" << setw(3) << right << black;
        cout << " White -" << setw(3) << right << white << endl;
         
        player = player == 'B' ? 'W' : 'B';
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int games;
    bool first = true;
    
    cin >> games;
    while (games--)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cin >> board[i][j];
                //cout << board[i][j];
            }
            //cout << endl;
        }
        
        if (first)
            first = false;
        else
            cout << endl;
            
        cin >> player;
        //cout << player << endl;
        while (cin >> command, command != "Q")
        {
            //cout << command << endl;
            play();
        }
        
        display();
    }
    
	return 0;
}
