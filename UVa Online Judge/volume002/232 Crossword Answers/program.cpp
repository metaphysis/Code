// Crossword Answers
// UVa ID: 232
// Verdict: Accepted
// Submission Date: 2016-05-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>

using namespace std;

char board[10][10];
int indexer[10][10], backup[10][10];

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int r, c, cases = 0;
    
    while (cin >> r >> c, r && c)
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                cin >> board[i][j];
                indexer[i][j] = 0;
                backup[i][j] = 0;
                //cout << board[i][j];
            }
            //cout << endl;
        }
        
        int counter = 1;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (board[i][j] != '*')
                {
                    if (i == 0 || j == 0 ||
                        (board[i - 1][j] == '*') || (j > 0 && board[i][j - 1] == '*'))
                        {
                            indexer[i][j] = counter++;
                            backup[i][j] = indexer[i][j];
                        }
                }
                //cout << indexer[i][j] << " ";
            }
            //cout << endl;
        }

        if (cases++)
            cout << "\n";
            
        cout << "puzzle #" << cases << ":" << "\n";
        cout << "Across" << endl;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (indexer[i][j])
                {
                    cout << setw(3) << right << indexer[i][j] << ".";
                    for (int k = j; k < c && board[i][k] != '*'; k++)
                    {
                        cout << board[i][k];
                        indexer[i][k] = 0;
                    }

                    cout << "\n";
                }
        cout << "Down" << "\n";
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (backup[i][j])
                {
                    cout << setw(3) << right << backup[i][j] << ".";
                    for (int k = i; k < r && board[k][j] != '*'; k++)
                    {
                        cout << board[k][j];
                        backup[k][j] = 0;
                    }

                    cout << "\n";
                }        
    }
    
	return 0;
}
