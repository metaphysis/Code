// Interpreting Control Sequences
// UVa ID: 337
// Verdict: Accepted
// Submission Date: 2016-07-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int OVERWRITE = 1, INSERT = 2;
char bitmap[10][10];
int mode = OVERWRITE, row = 0, column = 0;

void overwrite(char character)
{
    bitmap[row][column] = character;
}

void insert(char character)
{
    for (int c = 9; c > column; c--)
        bitmap[row][c] = bitmap[row][c - 1];
    bitmap[row][column] = character;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int n, cases = 0;
    string line;

    while (getline(cin, line))
    {
        n = stoi(line);
        if (n == 0)
            break;
        
        mode = OVERWRITE, row = 0, column = 0;
        memset(bitmap, ' ', sizeof(bitmap));
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            int position = 0;
            while (position < line.length())
            {
                if (line[position] == '^')
                {
                    position++;
                    if (line[position] == 'b')
                    {
                        column = 0;
                    }
                    else if (line[position] == 'c')
                    {
                        memset(bitmap, ' ', sizeof(bitmap));
                    }
                    else if (line[position] == 'd')
                    {
                        row = row < 9 ? (row + 1) : row;
                    }
                    else if (line[position] == 'e')
                    {
                        for (int c = column; c <= 9; c++)
                            bitmap[row][c] = ' ';
                    }
                    else if (line[position] == 'h')
                    {
                        row = 0, column = 0;
                    }
                    else if (line[position] == 'i')
                    {
                        mode = INSERT;
                    }
                    else if (line[position] == 'l')
                    {
                        column = column > 0 ? (column - 1) : column;
                    }
                    else if (line[position] == 'o')
                    {
                        mode = OVERWRITE;
                    }
                    else if (line[position] == 'r')
                    {
                        column = column < 9 ? (column + 1) : column;
                    }
                    else if (line[position] == 'u')
                    {
                        row = row > 0 ? (row - 1) : row;
                    }
                    else if (line[position] == '^')
                    {
                        if (mode == OVERWRITE)
                            overwrite('^');
                        else
                            insert('^');
                        column = column < 9 ? (column + 1) : column;
                    }
                    else
                    {
                        row = line[position] - '0';
                        position++;
                        column = line[position] - '0';
                    }
                }
                else
                {
                    if (mode == OVERWRITE)
                        overwrite(line[position]);
                    else
                        insert(line[position]);
                    column = column < 9 ? (column + 1) : column;
                }

                position++;
            }
        }

        cout << "Case " << ++cases << endl;
        cout << "+----------+" << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << '|';
            for (int j = 0; j < 10; j++)
                cout << bitmap[i][j];
            cout << '|' << endl;
        }
        cout << "+----------+" << endl;
    }

    return 0;
}
