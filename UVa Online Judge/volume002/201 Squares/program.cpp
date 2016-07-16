// Squares
// UVa ID: 201
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>

using namespace std;

int row[10][10][10], column[10][10][10], n;

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    char line;
    int m, start, end, counter = 0;
    bool printAsterisks = false;
    
    while (cin >> n)
    {
        if (printAsterisks)
        {
            cout << "\n";
            cout << "**********************************\n";
            cout << "\n";
        }
        
        if (printAsterisks == false)
            printAsterisks = true;
            
        counter++;
        
        memset(row, 0, sizeof(row));
        memset(column, 0, sizeof(column));
        
        cin >> m;
        while (m--)
        {
            cin >> line >> start >> end;
            if (line == 'H')
                row[start][end][end + 1] = 1;
            else
                column[start][end][end + 1] = 1;
        }
        
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n - 2; i++)
                for (int j = i + 2; j <= n; j++)
                {
                    if (row[k][i][j - 1] && row[k][j - 1][j])
                        row[k][i][j] = 1;
                        
                    if (column[k][i][j - 1] && column[k][j - 1][j])
                        column[k][i][j] = 1;
                }
        
        cout << "Problem #" << counter << "\n";
        cout << endl;
        
        bool outputed = false;
        for (int k = 1; k <= n - 1; k++)
        {
            int total = 0;
            for (int i = 1; i <= n - k; i++)
                for (int j = 1; j <= n - k; j++)
                    if (row[i][j][j + k] && row[i + k][j][j + k] &&
                        column[j][i][i + k] && column[j + k][i][i + k])
                            total++;
             
             if (total > 0)
             {
                cout << total << " square (s) of size " << k << "\n";
                outputed = true;
             }
                            
        }
        
        if (outputed == false)
            cout << "No completed squares can be found." << "\n";     
    }
    
	return 0;
}
