// Numbering Paths
// UVa ID: 125
// Verdict: Accepted
// Submission Date: 2015-11-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2015，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>

using namespace std;

#define MAXV 31

int matrix[MAXV][MAXV];
int largest;

void floyd()
{
    for (int k = 0; k <= largest; k++)
        for (int i = 0; i <= largest; i++)
            for (int j = 0; j <= largest; j++)
                matrix[i][j] += matrix[i][k] * matrix[k][j];
                
    for (int k = 0; k <= largest; k++)
        if (matrix[k][k])
            for (int i = 0; i <= largest; i++)
                for (int j = 0; j <= largest; j++)
                    if (matrix[i][k] && matrix[k][j])
                        matrix[i][j] = -1;
}

int main(int ac, char *av[])
{
    int intersections;
    int cases = 0;
    int start, end;
    while (cin >> intersections)
    {
        largest = 0;
        memset(matrix, 0, sizeof(matrix));
        
        for (int i = 1; i <= intersections; i++)
        {
            cin >> start >> end;
            matrix[start][end] = 1;
            largest = max(largest, max(start, end));
        }
            
        floyd();
        
        cout << "matrix for city " << cases++ << endl;
        for (int i = 0; i <= largest; i++)
        {
            cout << matrix[i][0];
            for (int j = 1; j <= largest; j++)
                cout << " " << matrix[i][j];
            cout << endl;
        }
    }

    return 0;
}
