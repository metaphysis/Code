// The Spot Game
// UVa ID: 141
// Verdict: Accepted
// Submission Date: 2016-01-20
// UVa Run Time: 0.003s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

string rotateCW90(string matrix, int n)
{
    string newMatrix;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            newMatrix += matrix[(n - 1) * n + (i - 1) - (j - 1) * n];
    return newMatrix;
}

string rotateCCW90(string matrix, int n)
{
    string newMatrix;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            newMatrix += matrix[(n - 1) - (i - 1) + (j - 1) * n];
    return newMatrix;
}

string rotate180(string matrix)
{
    reverse(matrix.begin(), matrix.end());
    return matrix;
}

int main(int argc, char *argv[])
{
    int n, x, y;
    string line;
    map < string, int > steps;
    
    while (cin >> n, n)
    {
        int winner = 0, move = 0;
        string matrix = string(n * n, '0');
        steps.clear();
        
        for (int i = 1; i <= 2 * n; i++)
        { 
            cin >> x >> y;
            getline(cin, line);
            
            if (winner > 0) continue;
                
            matrix[(x - 1) * n + (y - 1)] = (line.find('+') != line.npos) ? '1' : '0';
            if (steps.find(matrix) != steps.end())
            {
                winner = (steps[matrix] % 2 == 1) ? 2 : 1;
                move = i;
            }
            
            string newMatrix[4] = {
                matrix,
                rotateCW90(matrix, n), rotateCCW90(matrix, n),
                rotate180(matrix)
            };
            for (int j = 0; j < 4; j++)      
                if (steps.find(newMatrix[j]) == steps.end())
                    steps.insert(make_pair(newMatrix[j], i));
        }
        
        if (winner == 0)
            cout << "Draw" << endl;
        else
            cout << "Player " << winner << " wins on move " << move << endl;
    }
    
	return 0;
}
