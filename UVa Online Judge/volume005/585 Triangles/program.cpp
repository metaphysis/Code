// Triangles
// UVa ID: 585
// Verdict: Accepted
// Submission Date: 2016-12-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    char grid[210][210];
    int n, height[210][210], cases = 0;
    string line;

    while (true)
    {
        getline(cin, line);
        n = stoi(line);
        if (n == 0) break;
        
        memset(grid, 0, sizeof(grid));
        for (int i = 0; i < n; i++)
        {
            getline(cin, line);
            for (int j = 0; j < line.length(); j++)
                grid[i][j] = line[j];
        }

        // 三角形的顶点在下方。
        memset(height, 0, sizeof(height));

        for (int j = 0; j < 2 * n - 1; j += 2)
            if (grid[0][j] == '-')
                height[0][j] = 1;

        for (int i = 1; i < n; i++)
            for (int j = i; j < 2 * n - 1; j += 2)
                if (grid[i][j] == '-')
                {
                    if (grid[i - 1][j] == '-')
                        height[i][j] = min(height[i - 1][j - 1], height[i - 1][j + 1]) + 1;
                    else
                        height[i][j] = 1;
                }
        
        // 三角形的顶点在上方。
        for (int i = n - 2; i >= 0; i--)
            for (int j = i + 1; j < 2 * n - 1; j += 2)
                if (grid[i][j] == '-')
                {
                    if (grid[i + 1][j] == '-')
                        height[i][j] = min(height[i + 1][j - 1], height[i + 1][j + 1]) + 1;
                    else
                        height[i][j] = 1;
                }

        int largest = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < 2 * n - 1; j++)
                largest = max(largest, height[i][j]);

        cout << "Triangle #" << ++cases << '\n';
        cout << "The largest triangle area is " << (largest * largest) << ".\n\n";
    }
    
	return 0;
}
