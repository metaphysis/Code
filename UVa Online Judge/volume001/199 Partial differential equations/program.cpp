// Partial differential equations
// UVa ID: 199
// Verdict: Accepted
// Submission Date: 2016-03-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>

using namespace std;

int a[35][35], b[1000], v[3][3], g[3][3], boundary[4][35], f[35][35], temp[1000], n;

int main(int argc, char *argv[])
{
    int m;
    cin >> m;
    
    while (m--)
    {
        cin >> n;
        
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cin >> v[i][j];

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                cin >> g[i][j];
                
        for (int i = 0; i < 4; i++)
            for (int j = 0; j <= n; j++)
                cin >> boundary[i][j];
        
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                cin >> f[i][j];
        
        int counter = 0;
        for (int i = 2; i <= n; i++)
            for (int j = 2; j <= n; j++)
            {
                fill(temp, temp + 1000, 0);
                
                int right = 0;
                for (int x = i - 2; x <= i; x++)
                    for (int y = j - 2; y <= j; y++)
                    {
                        int left = 0;
                        if (x == 0)
                        {
                            left = v[x + 2 - i][y + 2 - j] * boundary[1][y];
                        }
                        else if (x == n)
                        {
                            left = v[x + 2 - i][y + 2 - j] * boundary[0][y];
                        }
                        else if (y == 0)
                        {
                            left = v[x + 2 - i][y + 2 - j] * boundary[2][n - x];
                        }
                        else if (y == n)
                        {
                            left = v[x + 2 - i][y + 2 - j] * boundary[3][n - x];
                        }
                        else
                        {
                            temp[(x - 1) * (n - 1) + y - 1] = v[x + 2 - i][y + 2 - j] * n * n;
                        }
                        
                        right += -left * n * n + g[x + 2 - i][y + 2 - j] * f[x][y];
                    }
                    
                b[counter++] = right;
               
                for (int k = 0; k < (n - 1) * (n - 1); k++)
                    cout << (k > 0 ? " " : "") << temp[k];
                cout << endl;
            }
            
        for (int i = 0; i < (n - 1) * (n - 1); i++)
            cout << (i > 0 ? " " : "") << b[i];
        cout << endl;
    }
    
	return 0;
}
