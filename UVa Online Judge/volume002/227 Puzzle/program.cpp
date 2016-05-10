// Puzzle
// UVa IDs: 227
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

char board[5][5];
char direction;
int x, y;
string directions = "LARB";
int step[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

bool move()
{
    int index = directions.find(direction);
    if (index == directions.npos)
        return false;
        
    int xx = x + step[index][0];
    int yy = y + step[index][1];
    
    if (xx < 0 || xx >= 5 || yy < 0 || yy >= 5)
        return false;
        
    board[x][y] = board[xx][yy];
    board[xx][yy] = ' ';
    x = xx;
    y = yy;
    
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int cases = 0;
    char input;
    string line;
    while (cin >> input, input != 'Z')
    {
        cin.putback(input);
        for (int i = 0; i < 5; i++)
        {
            getline(cin, line);
            if (line.length() < 5)
                line = ' ' + line;
            for (int j = 0; j < line.length(); j++)
            {
                board[i][j] = line[j];
                //cout << board[i][j];
                if (line[j] == ' ')
                {
                    x = i;
                    y = j;
                }
            }
            //cout << endl;
        }
        
        if (cases++)
            cout << endl;
        
        cout << "Puzzle #" << cases << ":\n";
        
        bool invalid = false;
        //cout << "x = " << x << endl;
        //cout << "y = " << y << endl;
        while (cin >> direction, direction != '0')
        {
            if (invalid == false && move() == false)
                invalid = true;
            //cout << input;
        }
        //cout << endl;
        
        if (invalid)
            cout << "This puzzle has no final configuration." << endl;
        else
        {
            for (int i = 0; i < 5; i++)
            {
                for (int j  = 0; j < 5; j++)
                {
                    if (j > 0)
                        cout << " ";
                        
                    cout << board[i][j];
                }
                cout << "\n";
            }
        }
    }
    
	return 0;
}
